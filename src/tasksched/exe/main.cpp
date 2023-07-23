#include <iostream>

#include <windows.h>

#include <wil/win32_helpers.h>

#include "date_time.h"
#include "task_folder.h"
#include "task.h"

using namespace wacpp;
using namespace std::chrono_literals;

void init_wil() noexcept
{
    // Print every log message to standard out.
    wil::SetResultLoggingCallback([](wil::FailureInfo const& failure) noexcept {
        constexpr std::size_t sizeOfLogMessageWithNul = 2048;
        wchar_t logMessage[sizeOfLogMessageWithNul];
        if (SUCCEEDED(wil::GetFailureLogString(logMessage, sizeOfLogMessageWithNul, failure)))
        {
            std::fputws(logMessage, stdout);
        }
    });
}

auto init_com()
{
    auto cleanup = wil::CoInitializeEx(COINIT_MULTITHREADED);
    THROW_IF_FAILED_MSG(CoInitializeSecurity(
        nullptr,
        -1,
        nullptr,
        nullptr,
        RPC_C_AUTHN_LEVEL_PKT_PRIVACY,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        nullptr,
        0,
        nullptr),
        "CoInitializeSecurity failed");
    return cleanup;
}

auto get_executable_path()
{
    auto windir = wil::GetEnvironmentVariableW(L"WINDIR");
    std::wstring wstrExecutablePath(windir.get());
    wstrExecutablePath += L"\\SYSTEM32\\NOTEPAD.EXE";
    return wstrExecutablePath;
}

class TaskService
{
public:
    static auto connect()
    {
        TaskService service(wil::CoCreateInstance<ITaskService>(CLSID_TaskScheduler, CLSCTX_INPROC_SERVER));
        THROW_IF_FAILED_MSG(service.m_service->Connect({}, {}, {}, {}), "ITaskService::Connect failed");
        return service;
    }

    auto get_root_folder()
    {
        wil::com_ptr<ITaskFolder> pRootFolder;
        auto path = wil::make_bstr(L"\\");
        THROW_IF_FAILED_MSG(m_service->GetFolder(path.get(), pRootFolder.put()), "Cannot get Root folder pointer");
        return TaskFolder(std::move(pRootFolder));
    }

    auto create_task()
    {
        wil::com_ptr<ITaskDefinition> pTask;
        THROW_IF_FAILED_MSG(m_service->NewTask(0, pTask.put()), "Failed to create a new task definition");
        return Task(std::move(pTask));
    }

private:
    TaskService(wil::com_ptr<ITaskService> service)
        : m_service(std::move(service))
    {}

    wil::com_ptr<ITaskService> m_service;
};

void run()
{
    auto cleanup = init_com();
    auto service = TaskService::connect();
    auto folder = service.get_root_folder();
    auto task = service.create_task();
    task.set_author(L"Author Name");
    task.set_logon_type(TASK_LOGON_INTERACTIVE_TOKEN);
    task.set_settings(true, std::chrono::minutes(5));
    task.add_time_trigger(L"Trigger1", make_date_time(2005y / 1 / 1, 12h + 5min), make_date_time(2015y / 5 / 2, 8h));
    task.add_exec_action(get_executable_path());
    folder.save(task, L"Time Trigger Test Task");
}

int main()
try
{
    init_wil();
    run();
    std::cout << "Success! Task successfully registered.\n";
}
CATCH_RETURN()