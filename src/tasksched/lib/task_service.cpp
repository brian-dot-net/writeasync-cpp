#include "task_service.h"

namespace wacpp
{

TaskService TaskService::connect()
{
    TaskService service(wil::CoCreateInstance<ITaskService>(CLSID_TaskScheduler, CLSCTX_INPROC_SERVER));
    THROW_IF_FAILED_MSG(service.m_service->Connect({}, {}, {}, {}), "ITaskService::Connect failed");
    return service;
}

TaskFolder TaskService::get_root_folder()
{
    wil::com_ptr<ITaskFolder> pRootFolder;
    auto path = wil::make_bstr(L"\\");
    THROW_IF_FAILED_MSG(m_service->GetFolder(path.get(), pRootFolder.put()), "Cannot get Root folder pointer");
    return TaskFolder(std::move(pRootFolder));
}

Task TaskService::create_task()
{
    wil::com_ptr<ITaskDefinition> pTask;
    THROW_IF_FAILED_MSG(m_service->NewTask(0, pTask.put()), "Failed to create a new task definition");
    return Task(std::move(pTask));
}

TaskService::TaskService(wil::com_ptr<ITaskService> service) noexcept
    : m_service(std::move(service))
{}

}