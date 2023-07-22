#include <gtest/gtest.h>

#include <windows.h>

#include <wil/com.h>

#include "stub_principal.h"
#include "stub_reginfo.h"
#include "stub_settings.h"
#include "stub_taskdef.h"
#include "task.h"

using namespace std::chrono_literals;

namespace
{

struct Stub
{
    struct Data
    {
        HRESULT get_RegistrationInfo_result{};
        HRESULT put_Author_result{};
        HRESULT get_Principal_result{};
        HRESULT put_LogonType{};
        HRESULT get_Settings_result{};
    };

    class Settings : public wacpp::test::Stub_ITaskSettings
    {
    public:
        Settings(const Data& data)
            : m_data(data)
        {}

    private:
        const Data& m_data;
    };

    class Principal : public wacpp::test::Stub_IPrincipal
    {
    public:
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
            const auto hr = m_data.put_LogonType;
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
        TaskDefinition(const Data& data)
            : m_data(data)
            , m_registration_info()
            , m_principal()
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
                m_registration_info = winrt::make<Stub::RegistrationInfo>(m_data);
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
                m_principal = winrt::make<Stub::Principal>(m_data);
                m_principal.copy_to(ppPrincipal);
            }

            return hr;
        }
        CATCH_RETURN()

        STDMETHODIMP get_Settings(
            ITaskSettings** ppSettings) noexcept
        try
        {
            const auto hr = m_data.get_Settings_result;
            if (SUCCEEDED(hr))
            {
                m_settings = winrt::make<Stub::Settings>(m_data);
                m_settings.copy_to(ppSettings);
            }

            return hr;
        }
        CATCH_RETURN()

    private:
        const Data& m_data;
        winrt::com_ptr<IRegistrationInfo> m_registration_info;
        winrt::com_ptr<IPrincipal> m_principal;
        winrt::com_ptr<ITaskSettings> m_settings;
    };
};

wil::com_ptr<ITaskDefinition> make_stub_task_definition(const Stub::Data& data)
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
    Stub::Data data{
        .get_RegistrationInfo_result = E_FAIL,
        .put_Author_result = E_FAIL,
    };
    Task task(make_stub_task_definition(data));

    ASSERT_THROW(task.set_author(L"Fail 1"), wil::ResultException);

    assert_xml(task, L"<Task></Task>");

    data.get_RegistrationInfo_result = S_OK;

    ASSERT_THROW(task.set_author(L"Fail 2"), wil::ResultException);

    assert_xml(task, L"<Task></Task>");

    data.put_Author_result = S_OK;

    task.set_author(L"Some Author");

    const auto expected =
        L"<Task>"
        L"<Author>Some Author</Author>"
        L"</Task>";
    assert_xml(task, expected);
}

TEST(task_test, set_logon_type)
{
    Stub::Data data{
        .get_Principal_result = E_FAIL,
        .put_LogonType = E_FAIL,
    };
    Task task(make_stub_task_definition(data));

    ASSERT_THROW(task.set_logon_type(TASK_LOGON_PASSWORD), wil::ResultException);

    assert_xml(task, L"<Task></Task>");

    data.get_Principal_result = S_OK;

    ASSERT_THROW(task.set_logon_type(TASK_LOGON_GROUP), wil::ResultException);

    assert_xml(task, L"<Task></Task>");

    data.put_LogonType = S_OK;

    task.set_logon_type(TASK_LOGON_SERVICE_ACCOUNT);

    const auto expected =
        L"<Task>"
        L"<LogonType>5</LogonType>"
        L"</Task>";
    assert_xml(task, expected);
}

TEST(task_test, set_settings)
{
    Stub::Data data{
        .get_Settings_result = E_FAIL,
    };
    Task task(make_stub_task_definition(data));

    ASSERT_THROW(task.set_settings(false, 1min), wil::ResultException);

    data.get_Settings_result = S_OK;

    ASSERT_THROW(task.set_settings(false, 1min), wil::ResultException);

    assert_xml(task, L"<Task></Task>");
}

}