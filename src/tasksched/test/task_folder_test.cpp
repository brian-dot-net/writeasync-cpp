#include <gtest/gtest.h>

#include <unordered_map>
#include <windows.h>

#include <wil/com.h>

#include "stub_regtask.h"
#include "stub_taskfolder.h"
#include "task_folder.h"

namespace
{

struct Stub
{
    struct TaskFolderData
    {
        HRESULT RegisterTaskDefinition_result{};
    };

    class RegisteredTask : public wacpp::test::Stub_IRegisteredTask
    {
    public:
        RegisteredTask(uint64_t definition, int user_id, int logon_type, int password, int sddl)
            : m_xml()
        {
            m_xml += L"<RegisteredTask>";
            m_xml += std::format(L"<Definition>0x{:X}</Definition>", definition);
            m_xml += std::format(L"<UserId>{}</UserId>", user_id);
            m_xml += std::format(L"<LogonType>{}</LogonType>", logon_type);
            m_xml += std::format(L"<Password>{}</Password>", password);
            m_xml += std::format(L"<Sddl>{}</Sddl>", sddl);
            m_xml += L"</RegisteredTask>";
        }

        STDMETHODIMP get_Xml(
            BSTR* pXml) noexcept override
        try
        {
            auto xml = wil::make_bstr(m_xml.c_str());
            *pXml = xml.release();
            return S_OK;
        }
        CATCH_RETURN()

    private:
        std::wstring m_xml;
    };

    class TaskFolder : public wacpp::test::Stub_ITaskFolder
    {
    public:
        using Data = TaskFolderData;

        TaskFolder(const Data& data)
            : m_data(data)
            , m_tasks()
        {}

        STDMETHODIMP GetTask(
            BSTR path,
            IRegisteredTask** ppTask) noexcept override
        try
        {
            std::wstring key = path;
            auto task = m_tasks.at(key);
            task.copy_to(ppTask);
            return S_OK;
        }
        CATCH_RETURN()

        STDMETHODIMP RegisterTaskDefinition(
            BSTR path,
            ITaskDefinition* pDefinition,
            LONG flags,
            VARIANT userId,
            VARIANT password,
            TASK_LOGON_TYPE logonType,
            VARIANT sddl,
            IRegisteredTask** ppTask) noexcept override
        try
        {
            if (flags != TASK_CREATE_OR_UPDATE)
            {
                return E_NOTIMPL;
            }

            const auto hr = m_data.RegisterTaskDefinition_result;
            if (SUCCEEDED(hr))
            {
                std::wstring key = path;
                winrt::com_ptr<IRegisteredTask> task = winrt::make<RegisteredTask>(
                    reinterpret_cast<uint64_t>(pDefinition),
                    userId.vt,
                    logonType,
                    password.vt,
                    sddl.vt);
                m_tasks.insert(std::make_pair(key, task));
                task.copy_to(ppTask);
            }

            return hr;
        }
        CATCH_RETURN()

    private:
        const Data& m_data;
        std::unordered_map<std::wstring, winrt::com_ptr<IRegisteredTask>> m_tasks;
    };

    class TaskWrapper
    {
    public:
        TaskWrapper(uint64_t value)
            : m_value(value)
        {}

        ITaskDefinition& get()
        {
            // This is normally very unsafe. However, the user will never
            // call anything on this reference; it is essentially a token.
            return *reinterpret_cast<ITaskDefinition*>(m_value);
        }

    private:
        uint64_t m_value;
    };
};

wil::com_ptr<ITaskFolder> make_stub_task_folder(const Stub::TaskFolderData& data)
{
    auto ptr = winrt::make<Stub::TaskFolder>(data);
    return wil::make_com_ptr(ptr.detach());
}

wil::com_ptr<IRegisteredTask> try_get_task(wacpp::TaskFolder& folder, LPCWSTR name)
{
    auto nameb = wil::make_bstr(name);
    wil::com_ptr<IRegisteredTask> task;
    if (FAILED(folder.get().GetTask(nameb.get(), task.put())))
    {
        task.reset();
    }

    return task;
}

void assert_xml(wacpp::TaskFolder& folder, LPCWSTR name, const std::wstring& expected)
{
    auto task = try_get_task(folder, name);
    THROW_IF_NULL_ALLOC(task);

    wil::unique_bstr str{};
    THROW_IF_FAILED(task->get_Xml(str.put()));
    std::wstring actual = str.get();

    ASSERT_EQ(expected, actual);
}

}

namespace wacpp::test
{

TEST(task_folder_test, save)
{
    Stub::TaskFolderData data{
        .RegisterTaskDefinition_result = E_FAIL,
    };
    TaskFolder folder(make_stub_task_folder(data));
    Stub::TaskWrapper wrapper{0x1234};

    ASSERT_THROW(folder.save(wrapper, L"Fail1"), wil::ResultException);

    auto task = try_get_task(folder, L"Fail1");
    ASSERT_EQ(nullptr, task);

    data.RegisterTaskDefinition_result = S_OK;

    folder.save(wrapper, L"Good1");

    auto expected =
        L"<RegisteredTask>"
        L"<Definition>0x1234</Definition>"
        L"<UserId>0</UserId>"
        L"<LogonType>3</LogonType>"
        L"<Password>0</Password>"
        L"<Sddl>0</Sddl>"
        L"</RegisteredTask>";
    assert_xml(folder, L"Good1", expected);
}

}