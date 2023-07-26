#include <gtest/gtest.h>

#include <windows.h>

#include <wil/com.h>

#include "stub_tasksvc.h"
#include "task_service.h"

namespace
{

struct Stub
{
    struct TaskServiceData
    {
        HRESULT Connect_result{};
    };

    class ComTaskService : public wacpp::test::Stub_ITaskService
    {
    public:
        using Data = TaskServiceData;

        ComTaskService(const Data& data)
            : m_data(data)
            , m_connected()
        {}

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

}

namespace wacpp::test
{

TEST(task_service_test, basic_test)
{
    Stub::TaskServiceData data{
        .Connect_result = E_FAIL
    };

    ASSERT_THROW(make_stub_task_service(data), wil::ResultException);

    data.Connect_result = S_OK;

    auto service = make_stub_task_service(data);
    assert_connected(service);
}

}