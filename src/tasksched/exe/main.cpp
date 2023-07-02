#include <chrono>
#include <format>
#include <iostream>
#include <string>
#include <vector>

#include <windows.h>
#include <taskschd.h>

#include <wil/com.h>
#include <wil/resource.h>
#include <wil/win32_helpers.h>

using namespace std::chrono_literals;

using DateTime = std::chrono::local_time<std::chrono::seconds>;

DateTime make_date_time(std::chrono::year_month_day date, std::chrono::seconds time)
{
    return std::chrono::local_time<std::chrono::days>(date) + time;
}

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

class Task
{
public:
    Task(wil::com_ptr<ITaskDefinition> task)
        : m_task(std::move(task))
    {
    }

    ITaskDefinition& get()
    {
        return *m_task.get();
    }

    void set_author(LPCWSTR author)
    {
        wil::com_ptr<IRegistrationInfo> pRegInfo;
        THROW_IF_FAILED_MSG(m_task->get_RegistrationInfo(pRegInfo.put()), "Cannot get identification pointer");
        auto value = wil::make_bstr(author);
        THROW_IF_FAILED_MSG(pRegInfo->put_Author(value.get()), "Cannot put identification info");
    }

    void set_logon_type(TASK_LOGON_TYPE logon)
    {
        wil::com_ptr<IPrincipal> pPrincipal;
        THROW_IF_FAILED_MSG(m_task->get_Principal(pPrincipal.put()), "Cannot get principal pointer");
        //  Set up principal logon type to interactive logon
        THROW_IF_FAILED_MSG(pPrincipal->put_LogonType(logon), "Cannot put principal info");
    }

    void set_settings(bool start_when_available, std::chrono::minutes wait_timeout)
    {
        wil::com_ptr<ITaskSettings> pSettings;
        THROW_IF_FAILED_MSG(m_task->get_Settings(pSettings.put()), "Cannot get settings pointer");

        THROW_IF_FAILED_MSG(pSettings->put_StartWhenAvailable(start_when_available ? VARIANT_TRUE : VARIANT_FALSE), "Cannot put setting information");

        wil::com_ptr<IIdleSettings> pIdleSettings;
        THROW_IF_FAILED_MSG(pSettings->get_IdleSettings(pIdleSettings.put()), "Cannot get idle setting information");
        std::wstring timeout = std::format(L"PT{}M", wait_timeout.count());
        auto value = wil::make_bstr(timeout.c_str());
        THROW_IF_FAILED_MSG(pIdleSettings->put_WaitTimeout(value.get()), "Cannot put idle setting information");
    }

    void add_time_trigger(LPCWSTR id, DateTime start, DateTime end)
    {
        wil::com_ptr<ITriggerCollection> pTriggerCollection;
        THROW_IF_FAILED_MSG(m_task->get_Triggers(pTriggerCollection.put()), "Cannot get trigger collection");

        //  Add the time trigger to the task.
        wil::com_ptr<ITrigger> pTrigger;
        THROW_IF_FAILED_MSG(pTriggerCollection->Create(TASK_TRIGGER_TIME, pTrigger.put()), "Cannot create trigger");

        auto pTimeTrigger = pTrigger.query<ITimeTrigger>();
        auto value = wil::make_bstr(id);
        THROW_IF_FAILED_MSG(pTimeTrigger->put_Id(value.get()), "Cannot put trigger ID");

        auto end_time = std::format(L"{:%Y-%m-%dT%T}", end);
        value = wil::make_bstr(end_time.c_str());
        THROW_IF_FAILED_MSG(pTimeTrigger->put_EndBoundary(value.get()), "Cannot put end boundary on trigger");

        auto start_time = std::format(L"{:%Y-%m-%dT%T}", start);
        value = wil::make_bstr(start_time.c_str());
        THROW_IF_FAILED_MSG(pTimeTrigger->put_StartBoundary(value.get()), "Cannot add start boundary to trigger");
    }

    void add_exec_action(const std::wstring& path)
    {
        wil::com_ptr<IActionCollection> pActionCollection;

        THROW_IF_FAILED_MSG(m_task->get_Actions(pActionCollection.put()), "Cannot get Task collection pointer");

        wil::com_ptr<IAction> pAction;
        THROW_IF_FAILED_MSG(pActionCollection->Create(TASK_ACTION_EXEC, pAction.put()), "Cannot create the action");

        auto pExecAction = pAction.query<IExecAction>();
        auto value = wil::make_bstr(path.c_str());
        THROW_IF_FAILED_MSG(pExecAction->put_Path(value.get()), "Cannot put action path");
    }

private:
    wil::com_ptr<ITaskDefinition> m_task;
};

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
        return pRootFolder;
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
    {
    }

    wil::com_ptr<ITaskService> m_service;
};

void save(ITaskDefinition& pTask, LPCWSTR name, ITaskFolder& pRootFolder)
{
    auto value = wil::make_bstr(name);
    wil::com_ptr<IRegisteredTask> pRegisteredTask;
    THROW_IF_FAILED_MSG(pRootFolder.RegisterTaskDefinition(
        value.get(),
        &pTask,
        TASK_CREATE_OR_UPDATE,
        {},
        {},
        TASK_LOGON_INTERACTIVE_TOKEN,
        {},
        pRegisteredTask.put()),
        "Error saving the Task");
}

void run()
{
    auto cleanup = init_com();
    auto service = TaskService::connect();
    auto pRootFolder = service.get_root_folder();
    auto task = service.create_task();
    task.set_author(L"Author Name");
    task.set_logon_type(TASK_LOGON_INTERACTIVE_TOKEN);
    task.set_settings(true, std::chrono::minutes(5));
    task.add_time_trigger(L"Trigger1", make_date_time(2005y / 1 / 1, 12h + 5min), make_date_time(2015y / 5 / 2, 8h));
    task.add_exec_action(get_executable_path());
    save(task.get(), L"Time Trigger Test Task", *pRootFolder);
}

int main()
try
{
    init_wil();
    run();
    std::cout << "Success! Task successfully registered.\n";
}
CATCH_RETURN()