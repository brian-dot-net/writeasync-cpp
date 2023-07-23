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

private:
    TaskService(wil::com_ptr<ITaskService> service) noexcept;

    wil::com_ptr<ITaskService> m_service;
};

}