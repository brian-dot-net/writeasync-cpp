#include <gtest/gtest.h>

#include <windows.h>

#include <wil/com.h>

#include "stub_tasksvc.h"
#include "stub_taskfolder.h"
#include "task_service.h"

namespace
{

struct Stub
{
    struct TaskServiceData
    {
        HRESULT Connect_result{};
        HRESULT GetFolder_result{};
    };

    class ComTaskFolder : public wacpp::test::Stub_ITaskFolder
    {
    public:
        ComTaskFolder(const std::wstring& path)
            : m_path(path)
        {
        }

        STDMETHODIMP get_Path(
            BSTR* pPath) noexcept override
        try
        {
            auto path = wil::make_bstr(m_path.c_str());
            *pPath = path.release();
            return S_OK;
        }
        CATCH_RETURN()

    private:
        std::wstring m_path;
    };

    class ComTaskService : public wacpp::test::Stub_ITaskService
    {
    public:
        using Data = TaskServiceData;

        ComTaskService(const Data& data)
            : m_data(data)
            , m_connected()
        {}

        STDMETHODIMP GetFolder(
            BSTR path,
            ITaskFolder** ppFolder) noexcept override
        try
        {
            const auto hr = m_data.GetFolder_result;
            if (SUCCEEDED(hr))
            {
                auto folder = winrt::make<ComTaskFolder>(path);
                folder.copy_to(ppFolder);
            }

            return hr;
        }
        CATCH_RETURN()

        STDMETHODIMP Connect(
            VARIANT serverName,
            VARIANT user,
            VARIANT domain,
            VARIANT password) noexcept override
        {
            m_connected =
                (serverName.vt == 0) &&
                (user.vt == 0) &&
                (domain.vt == 0) &&
                (password.vt == 0);
            return m_data.Connect_result;
        }

        STDMETHODIMP get_Connected(
            VARIANT_BOOL* pConnected) noexcept override
        try
        {
            *pConnected = m_connected ? VARIANT_TRUE : VARIANT_FALSE;
            return S_OK;
        }
        CATCH_RETURN()

    private:
        const Data& m_data;
        bool m_connected;
    };

    class TestTaskService : public wacpp::TaskService
    {
    public:
        TestTaskService(wil::com_ptr<ITaskService> service)
            : TaskService(std::move(service))
        {}
    };
};

Stub::TestTaskService make_stub_task_service(const Stub::TaskServiceData& data)
{
    auto ptr = winrt::make<Stub::ComTaskService>(data);
    return Stub::TestTaskService(wil::make_com_ptr(ptr.detach()));
}

void assert_connected(wacpp::TaskService& service)
{
    VARIANT_BOOL b{};
    THROW_IF_FAILED(service.get().get_Connected(&b));
    ASSERT_EQ(VARIANT_TRUE, b);
}

void assert_path(wacpp::TaskFolder& folder, const std::wstring& expected)
{
    wil::unique_bstr str{};
    THROW_IF_FAILED(folder.get().get_Path(str.put()));
    std::wstring actual = str.get();

    ASSERT_EQ(expected, actual);
}

}

namespace wacpp::test
{

TEST(task_service_test, basic_test)
{
    Stub::TaskServiceData data{
        .Connect_result = E_FAIL,
        .GetFolder_result = E_FAIL,
    };

    ASSERT_THROW(make_stub_task_service(data), wil::ResultException);

    data.Connect_result = S_OK;

    auto service = make_stub_task_service(data);
    assert_connected(service);

    ASSERT_THROW(service.get_root_folder(), wil::ResultException);

    data.GetFolder_result = S_OK;

    auto folder = service.get_root_folder();
    assert_path(folder, L"\\");
}

}