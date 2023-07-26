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
    };

    class ComTaskService : public wacpp::test::Stub_ITaskService
    {
    public:
        using Data = TaskServiceData;

        ComTaskService(const Data& data)
            : m_data(data)
        {}

    private:
        const Data& m_data;
    };

    class TestTaskService : public wacpp::TaskService
    {
    public:
        TestTaskService(wil::com_ptr<ITaskService> service)
            : TaskService(std::move(service))
        {
        }
    };
};

Stub::TestTaskService make_stub_task_service(const Stub::TaskServiceData& data)
{
    auto ptr = winrt::make<Stub::ComTaskService>(data);
    return Stub::TestTaskService(wil::make_com_ptr(ptr.detach()));
}

}

namespace wacpp::test
{

TEST(task_service_test, basic_test)
{
    Stub::TaskServiceData data{};

    ASSERT_THROW(make_stub_task_service(data), wil::ResultException);
}

}