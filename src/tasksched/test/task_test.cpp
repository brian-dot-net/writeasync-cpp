#include <gtest/gtest.h>

#include <optional>
#include <vector>

#include <windows.h>

#include <wil/com.h>

#include "stub_principal.h"
#include "stub_reginfo.h"
#include "stub_settings.h"
#include "stub_taskdef.h"
#include "stub_triggers.h"
#include "task.h"

using namespace std::chrono_literals;

namespace
{

struct Stub
{
    struct RegistrationInfoData
    {
        HRESULT put_Author_result{};
    };

    struct PrincipalData
    {
        HRESULT put_LogonType_result{};
    };

    struct TaskSettingsData
    {
        HRESULT put_StartWhenAvailable_result{};
        HRESULT get_IdleSettings_result{};
        HRESULT put_WaitTimeout_result{};
    };

    struct TaskDefinitionData
    {
        HRESULT get_RegistrationInfo_result{};
        RegistrationInfoData RegistrationInfo{};

        HRESULT get_Principal_result{};
        PrincipalData Principal{};

        HRESULT get_Settings_result{};
        TaskSettingsData Settings{};

        HRESULT get_Triggers_result{};
        HRESULT ITriggerCollection_Create_result{};
        HRESULT ITimeTrigger_put_Id_result{};
    };

    class TimeTrigger : public wacpp::test::Stub_ITimeTrigger
    {
    public:
        using Data = TaskDefinitionData;

        TimeTrigger(const Data& data)
            : m_data(data)
            , m_id()
        {}

        STDMETHODIMP get_Id(
            BSTR* pId) noexcept override
        try
        {
            auto id = wil::make_bstr(m_id.c_str());
            *pId = id.release();
            return S_OK;
        }
        CATCH_RETURN()

        STDMETHODIMP put_Id(
            BSTR id) noexcept override
        try
        {
            const auto hr = m_data.ITimeTrigger_put_Id_result;
            if (SUCCEEDED(hr))
            {
                m_id = id;
            }

            return hr;
        }
        CATCH_RETURN()

    private:
        const Data& m_data;
        std::wstring m_id;
    };

    class TriggerCollection : public wacpp::test::Stub_ITriggerCollection
    {
    public:
        using Data = TaskDefinitionData;

        TriggerCollection(const Data& data)
            : m_data(data)
            , m_triggers()
        {}

        STDMETHODIMP get_Count(
            long* pCount) noexcept override
        try
        {
            *pCount = static_cast<long>(m_triggers.size());
            return S_OK;
        }
        CATCH_RETURN()

        STDMETHODIMP get_Item(
            long index,
            ITrigger** ppTrigger) noexcept override
        try
        {
            auto trigger = m_triggers.at(index);
            trigger.copy_to(ppTrigger);
            return S_OK;
        }
        CATCH_RETURN()

        STDMETHODIMP Create(
            TASK_TRIGGER_TYPE2 type,
            ITrigger** ppTrigger) noexcept override
        try
        {
            if (type != TASK_TRIGGER_TIME)
            {
                return E_NOTIMPL;
            }

            const auto hr = m_data.ITriggerCollection_Create_result;
            if (SUCCEEDED(hr))
            {
                winrt::com_ptr<ITrigger> trigger = winrt::make<Stub::TimeTrigger>(m_data);
                m_triggers.push_back(trigger);
                trigger.copy_to(ppTrigger);
            }

            return hr;
        }
        CATCH_RETURN()

    private:
        const Data& m_data;
        std::vector<winrt::com_ptr<ITrigger>> m_triggers;
    };

    class IdleSettings : public wacpp::test::Stub_IIdleSettings
    {
    public:
        using Data = TaskSettingsData;

        IdleSettings(const Data& data)
            : m_data(data)
            , m_wait_timeout()
        {}

        STDMETHODIMP get_WaitTimeout(
            BSTR* pTimeout) noexcept override
        try
        {
            auto timeout = wil::make_bstr(m_wait_timeout.c_str());
            *pTimeout = timeout.release();
            return S_OK;
        }
        CATCH_RETURN()

        STDMETHODIMP put_WaitTimeout(
            BSTR timeout) noexcept override
        try
        {
            const auto hr = m_data.put_WaitTimeout_result;
            if (SUCCEEDED(hr))
            {
                m_wait_timeout = timeout;
            }

            return hr;
        }
        CATCH_RETURN()

    private:
        const Data& m_data;
        std::wstring m_wait_timeout;
    };

    class TaskSettings : public wacpp::test::Stub_ITaskSettings
    {
    public:
        using Data = TaskSettingsData;

        TaskSettings(const Data& data)
            : m_data(data)
            , m_start_when_available()
            , m_idle_settings()
        {}

        STDMETHODIMP get_XmlText(
            BSTR* pXml) noexcept override
        try
        {
            std::wstring inner_xml{};
            if (m_start_when_available)
            {
                inner_xml += std::format(L"<StartWhenAvailable>{}</StartWhenAvailable>", *m_start_when_available);
            }

            if (m_idle_settings)
            {
                wil::unique_bstr str;
                THROW_IF_FAILED(m_idle_settings->get_WaitTimeout(str.put()));
                std::wstring wait_timeout = str.get();
                if (!wait_timeout.empty())
                {
                    inner_xml += std::format(L"<WaitTimeout>{}</WaitTimeout>", wait_timeout);
                }
            }

            std::wstring xml{};
            if (!inner_xml.empty())
            {
                xml += std::format(L"<Settings>{}</Settings>", inner_xml);
            }

            auto outer_xml = wil::make_bstr(xml.c_str());
            *pXml = outer_xml.release();

            return S_OK;
        }
        CATCH_RETURN()

        STDMETHODIMP put_StartWhenAvailable(
            VARIANT_BOOL startWhenAvailable) noexcept override
        try
        {
            const auto hr = m_data.put_StartWhenAvailable_result;
            if (SUCCEEDED(hr))
            {
                m_start_when_available = startWhenAvailable == VARIANT_TRUE;
            }

            return hr;
        }
        CATCH_RETURN()

        STDMETHODIMP get_IdleSettings(
            IIdleSettings** ppIdleSettings) noexcept override
        try
        {
            const auto hr = m_data.get_IdleSettings_result;
            if (SUCCEEDED(hr))
            {
                m_idle_settings = winrt::make<Stub::IdleSettings>(m_data);
                m_idle_settings.copy_to(ppIdleSettings);
            }

            return hr;
        }
        CATCH_RETURN()

    private:
        const Data& m_data;
        std::optional<bool> m_start_when_available;
        winrt::com_ptr<IIdleSettings> m_idle_settings;
    };

    class Principal : public wacpp::test::Stub_IPrincipal
    {
    public:
        using Data = PrincipalData;

        Principal(const Data& data)
            : m_data(data)
            , m_logon()
        {}

        STDMETHODIMP get_LogonType(
            TASK_LOGON_TYPE* pLogon) noexcept override
        try
        {
            *pLogon = m_logon;
            return S_OK;
        }
        CATCH_RETURN()

        STDMETHODIMP put_LogonType(
            TASK_LOGON_TYPE logon) noexcept override
        try
        {
            const auto hr = m_data.put_LogonType_result;
            if (SUCCEEDED(hr))
            {
                m_logon = logon;
            }

            return hr;
        }
        CATCH_RETURN()

    private:
        const Data& m_data;
        TASK_LOGON_TYPE m_logon;
    };

    class RegistrationInfo : public wacpp::test::Stub_IRegistrationInfo
    {
    public:
        using Data = RegistrationInfoData;

        RegistrationInfo(const Data& data)
            : m_data(data)
            , m_author()
        {}

        STDMETHODIMP get_XmlText(
            BSTR* pXml) noexcept override
        try
        {
            std::wstring xml{};
            if (!m_author.empty())
            {
                xml += std::format(L"<Author>{}</Author>", m_author);
            }

            auto outer_xml = wil::make_bstr(xml.c_str());
            *pXml = outer_xml.release();

            return S_OK;
        }
        CATCH_RETURN()

        STDMETHODIMP put_Author(
            BSTR author) noexcept override
        try
        {
            const auto hr = m_data.put_Author_result;
            if (SUCCEEDED(hr))
            {
                m_author = author;
            }

            return hr;
        }
        CATCH_RETURN()

    private:
        const Data& m_data;
        std::wstring m_author;
    };

    class TaskDefinition : public wacpp::test::Stub_ITaskDefinition
    {
    public:
        using Data = TaskDefinitionData;

        TaskDefinition(const Data& data)
            : m_data(data)
            , m_registration_info()
            , m_principal()
            , m_triggers()
        {}

        STDMETHODIMP get_XmlText(
            BSTR* pXml) noexcept override
        try
        {
            std::wstring xml{};
            xml += L"<Task>";

            if (m_registration_info)
            {
                wil::unique_bstr str;
                THROW_IF_FAILED(m_registration_info->get_XmlText(str.put()));
                xml += str.get();
            }

            if (m_principal)
            {
                TASK_LOGON_TYPE logon{};
                THROW_IF_FAILED(m_principal->get_LogonType(&logon));
                if (logon)
                {
                    xml += std::format(L"<LogonType>{}</LogonType>", static_cast<int>(logon));
                }
            }

            if (m_settings)
            {
                wil::unique_bstr str;
                THROW_IF_FAILED(m_settings->get_XmlText(str.put()));
                xml += str.get();
            }

            if (m_triggers)
            {
                long count{};
                THROW_IF_FAILED(m_triggers->get_Count(&count));

                std::wstring inner_xml{};
                for (long i = 0; i < count; ++i)
                {
                    wil::com_ptr<ITrigger> trigger;
                    THROW_IF_FAILED(m_triggers->get_Item(i, trigger.put()));

                    auto time_trigger = trigger.query<ITimeTrigger>();

                    inner_xml += L"<TimeTrigger>";

                    wil::unique_bstr idb{};
                    THROW_IF_FAILED(time_trigger->get_Id(idb.put()));
                    std::wstring id = idb.get();
                    if (!id.empty())
                    {
                        inner_xml += std::format(L"<Id>{}</Id>", id);
                    }

                    inner_xml += L"</TimeTrigger>";
                }

                if (!inner_xml.empty())
                {
                    xml += std::format(L"<Triggers>{}</Triggers>", inner_xml);
                }
            }

            xml += L"</Task>";

            auto outer_xml = wil::make_bstr(xml.c_str());
            *pXml = outer_xml.release();

            return S_OK;
        }
        CATCH_RETURN()

        STDMETHODIMP get_RegistrationInfo(
            IRegistrationInfo** ppRegistrationInfo) noexcept override
        try
        {
            const auto hr = m_data.get_RegistrationInfo_result;
            if (SUCCEEDED(hr))
            {
                m_registration_info = winrt::make<Stub::RegistrationInfo>(m_data.RegistrationInfo);
                m_registration_info.copy_to(ppRegistrationInfo);
            }

            return hr;
        }
        CATCH_RETURN()

        STDMETHODIMP get_Principal(
            IPrincipal** ppPrincipal) noexcept override
        try
        {
            const auto hr = m_data.get_Principal_result;
            if (SUCCEEDED(hr))
            {
                m_principal = winrt::make<Stub::Principal>(m_data.Principal);
                m_principal.copy_to(ppPrincipal);
            }

            return hr;
        }
        CATCH_RETURN()

        STDMETHODIMP get_Settings(
            ITaskSettings** ppSettings) noexcept override
        try
        {
            const auto hr = m_data.get_Settings_result;
            if (SUCCEEDED(hr))
            {
                m_settings = winrt::make<Stub::TaskSettings>(m_data.Settings);
                m_settings.copy_to(ppSettings);
            }

            return hr;
        }
        CATCH_RETURN()

        STDMETHODIMP get_Triggers(
            ITriggerCollection** ppTriggers) noexcept override
        try
        {
            const auto hr = m_data.get_Triggers_result;
            if (SUCCEEDED(hr))
            {
                m_triggers = winrt::make<Stub::TriggerCollection>(m_data);
                m_triggers.copy_to(ppTriggers);
            }

            return hr;
        }
        CATCH_RETURN()

    private:
        const Data& m_data;
        winrt::com_ptr<IRegistrationInfo> m_registration_info;
        winrt::com_ptr<IPrincipal> m_principal;
        winrt::com_ptr<ITaskSettings> m_settings;
        winrt::com_ptr<ITriggerCollection> m_triggers;
    };
};

wil::com_ptr<ITaskDefinition> make_stub_task_definition(const Stub::TaskDefinitionData& data)
{
    auto ptr = winrt::make<Stub::TaskDefinition>(data);
    return wil::make_com_ptr(ptr.detach());
}

void assert_xml(wacpp::Task& task, const std::wstring& expected)
{
    wil::unique_bstr str{};
    THROW_IF_FAILED(task.get().get_XmlText(str.put()));
    std::wstring actual = str.get();

    ASSERT_EQ(expected, actual);
}

}

namespace wacpp::test
{

TEST(task_test, set_author)
{
    Stub::TaskDefinitionData data{
        .get_RegistrationInfo_result = E_FAIL,
        .RegistrationInfo = {
            .put_Author_result = E_FAIL
        },
    };
    Task task(make_stub_task_definition(data));

    ASSERT_THROW(task.set_author(L"Fail 1"), wil::ResultException);

    assert_xml(task, L"<Task></Task>");

    data.get_RegistrationInfo_result = S_OK;

    ASSERT_THROW(task.set_author(L"Fail 2"), wil::ResultException);

    assert_xml(task, L"<Task></Task>");

    data.RegistrationInfo.put_Author_result = S_OK;

    task.set_author(L"Some Author");

    const auto expected =
        L"<Task>"
        L"<Author>Some Author</Author>"
        L"</Task>";
    assert_xml(task, expected);
}

TEST(task_test, set_logon_type)
{
    Stub::TaskDefinitionData data{
        .get_Principal_result = E_FAIL,
        .Principal {
            .put_LogonType_result = E_FAIL,
        }
    };
    Task task(make_stub_task_definition(data));

    ASSERT_THROW(task.set_logon_type(TASK_LOGON_PASSWORD), wil::ResultException);

    assert_xml(task, L"<Task></Task>");

    data.get_Principal_result = S_OK;

    ASSERT_THROW(task.set_logon_type(TASK_LOGON_GROUP), wil::ResultException);

    assert_xml(task, L"<Task></Task>");

    data.Principal.put_LogonType_result = S_OK;

    task.set_logon_type(TASK_LOGON_SERVICE_ACCOUNT);

    const auto expected =
        L"<Task>"
        L"<LogonType>5</LogonType>"
        L"</Task>";
    assert_xml(task, expected);
}

TEST(task_test, set_settings)
{
    Stub::TaskDefinitionData data{
        .get_Settings_result = E_FAIL,
        .Settings = {
            .put_StartWhenAvailable_result = E_FAIL,
            .get_IdleSettings_result = E_FAIL,
            .put_WaitTimeout_result = E_FAIL,
        }
    };
    Task task(make_stub_task_definition(data));

    ASSERT_THROW(task.set_settings(true, 1min), wil::ResultException);

    data.get_Settings_result = S_OK;

    ASSERT_THROW(task.set_settings(false, 2min), wil::ResultException);

    assert_xml(task, L"<Task></Task>");

    data.Settings.put_StartWhenAvailable_result = S_OK;

    ASSERT_THROW(task.set_settings(true, 3min), wil::ResultException);

    auto expected =
        L"<Task>"
        L"<Settings>"
        L"<StartWhenAvailable>true</StartWhenAvailable>"
        L"</Settings>"
        L"</Task>";
    assert_xml(task, expected);

    data.Settings.get_IdleSettings_result = S_OK;

    ASSERT_THROW(task.set_settings(false, 4min), wil::ResultException);

    expected =
        L"<Task>"
        L"<Settings>"
        L"<StartWhenAvailable>false</StartWhenAvailable>"
        L"</Settings>"
        L"</Task>";
    assert_xml(task, expected);

    data.Settings.put_WaitTimeout_result = S_OK;

    task.set_settings(true, 5min);

    expected =
        L"<Task>"
        L"<Settings>"
        L"<StartWhenAvailable>true</StartWhenAvailable>"
        L"<WaitTimeout>PT5M</WaitTimeout>"
        L"</Settings>"
        L"</Task>";
    assert_xml(task, expected);
}

TEST(task_test, add_time_trigger)
{
    Stub::TaskDefinitionData data{
        .get_Triggers_result = E_FAIL,
        .ITriggerCollection_Create_result = E_FAIL,
        .ITimeTrigger_put_Id_result = E_FAIL,
    };
    Task task(make_stub_task_definition(data));
    auto start = make_date_time(2020y / 1 / 2, 3h + 4min + 5s);
    auto end = make_date_time(2021y / 2 / 3, 4h + 5min + 6s);

    ASSERT_THROW(task.add_time_trigger(L"Id1", start, end), wil::ResultException);

    assert_xml(task, L"<Task></Task>");

    data.get_Triggers_result = S_OK;

    ASSERT_THROW(task.add_time_trigger(L"Id2", start, end), wil::ResultException);

    assert_xml(task, L"<Task></Task>");

    data.ITriggerCollection_Create_result = S_OK;

    ASSERT_THROW(task.add_time_trigger(L"Id3", start, end), wil::ResultException);

    auto expected =
        L"<Task>"
        L"<Triggers>"
        L"<TimeTrigger>"
        L"</TimeTrigger>"
        L"</Triggers>"
        L"</Task>";
    assert_xml(task, expected);

    data.ITimeTrigger_put_Id_result = S_OK;

    ASSERT_THROW(task.add_time_trigger(L"Id4", start, end), wil::ResultException);

    expected =
        L"<Task>"
        L"<Triggers>"
        L"<TimeTrigger><Id>Id4</Id></TimeTrigger>"
        L"</Triggers>"
        L"</Task>";
    assert_xml(task, expected);
}

}