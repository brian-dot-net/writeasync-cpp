#pragma once

#include <chrono>
#include <string>

#include <windows.h>
#include <taskschd.h>

#include <wil/com.h>

#include "date_time.h"

namespace wacpp
{

class Task
{
public:
    Task(wil::com_ptr<ITaskDefinition> task) noexcept;

    ITaskDefinition& get() noexcept;

    void set_author(LPCWSTR author);
    void set_logon_type(TASK_LOGON_TYPE logon);
    void set_settings(bool start_when_available, std::chrono::minutes wait_timeout);
    void add_time_trigger(LPCWSTR id, DateTime start, DateTime end);
    void add_exec_action(const std::wstring& path);

private:
    wil::com_ptr<ITaskDefinition> m_task;
};

}