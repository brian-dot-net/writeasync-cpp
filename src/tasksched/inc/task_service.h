#pragma once

#include "task.h"
#include "task_folder.h"

namespace wacpp
{

class TaskService
{
public:
    static TaskService connect();

    TaskFolder get_root_folder();

    Task create_task();

protected:
    TaskService(wil::com_ptr<ITaskService> service);

private:
    wil::com_ptr<ITaskService> m_service;
};

}