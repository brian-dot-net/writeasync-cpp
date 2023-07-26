#include "task_service.h"

namespace wacpp
{

TaskService TaskService::connect()
{
    return TaskService(wil::CoCreateInstance<ITaskService>(CLSID_TaskScheduler, CLSCTX_INPROC_SERVER));
}

ITaskService& TaskService::get()
{
    return *m_service;
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

TaskService::TaskService(wil::com_ptr<ITaskService> service)
    : m_service(std::move(service))
{
    THROW_IF_FAILED_MSG(m_service->Connect({}, {}, {}, {}), "ITaskService::Connect failed");
}

}