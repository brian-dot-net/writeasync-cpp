#include <stdio.h>

#include <chrono>
#include <format>
#include <string>
#include <vector>

#include <windows.h>
#include <comutil.h>
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

auto connect_task_service()
{
    auto pService = wil::CoCreateInstance<ITaskService>(CLSID_TaskScheduler, CLSCTX_INPROC_SERVER);
    THROW_IF_FAILED_MSG(pService->Connect({}, {}, {}, {}), "ITaskService::Connect failed");
    return pService;
}

auto get_root_folder(ITaskService& pService)
{
    wil::com_ptr<ITaskFolder> pRootFolder;
    THROW_IF_FAILED_MSG(pService.GetFolder(_bstr_t(L"\\"), pRootFolder.put()), "Cannot get Root folder pointer");
    return pRootFolder;
}

auto create_task(ITaskService& pService)
{
    wil::com_ptr<ITaskDefinition> pTask;
    THROW_IF_FAILED_MSG(pService.NewTask(0, pTask.put()), "Failed to create a new task definition");
    return pTask;
}

void set_author(ITaskDefinition& pTask, LPCWSTR author)
{
    wil::com_ptr<IRegistrationInfo> pRegInfo;
    THROW_IF_FAILED_MSG(pTask.get_RegistrationInfo(pRegInfo.put()), "Cannot get identification pointer");
    THROW_IF_FAILED_MSG(pRegInfo->put_Author(_bstr_t(author)), "Cannot put identification info");
}

void set_logon_type(ITaskDefinition& pTask, TASK_LOGON_TYPE logon)
{
    wil::com_ptr<IPrincipal> pPrincipal;
    THROW_IF_FAILED_MSG(pTask.get_Principal(pPrincipal.put()), "Cannot get principal pointer");
    //  Set up principal logon type to interactive logon
    THROW_IF_FAILED_MSG(pPrincipal->put_LogonType(logon), "Cannot put principal info");
}

void set_settings(ITaskDefinition& pTask, bool start_when_available, std::chrono::minutes wait_timeout)
{
    wil::com_ptr<ITaskSettings> pSettings;
    THROW_IF_FAILED_MSG(pTask.get_Settings(pSettings.put()), "Cannot get settings pointer");

    THROW_IF_FAILED_MSG(pSettings->put_StartWhenAvailable(start_when_available ? VARIANT_TRUE : VARIANT_FALSE), "Cannot put setting information");

    wil::com_ptr<IIdleSettings> pIdleSettings;
    THROW_IF_FAILED_MSG(pSettings->get_IdleSettings(pIdleSettings.put()), "Cannot get idle setting information");
    std::wstring timeout = std::format(L"PT{}M", wait_timeout.count());
    THROW_IF_FAILED_MSG(pIdleSettings->put_WaitTimeout(_bstr_t(timeout.c_str())), "Cannot put idle setting information");
}

void add_time_trigger(ITaskDefinition& pTask, LPCWSTR id, DateTime start, DateTime end)
{
    wil::com_ptr<ITriggerCollection> pTriggerCollection;
    THROW_IF_FAILED_MSG(pTask.get_Triggers(pTriggerCollection.put()), "Cannot get trigger collection");

    //  Add the time trigger to the task.
    wil::com_ptr<ITrigger> pTrigger;
    THROW_IF_FAILED_MSG(pTriggerCollection->Create(TASK_TRIGGER_TIME, pTrigger.put()), "Cannot create trigger");

    auto pTimeTrigger = pTrigger.query<ITimeTrigger>();
    THROW_IF_FAILED_MSG(pTimeTrigger->put_Id(_bstr_t(id)), "Cannot put trigger ID");

    auto end_time = std::format(L"{:%Y-%m-%dT%T}", end);
    THROW_IF_FAILED_MSG(pTimeTrigger->put_EndBoundary(_bstr_t(end_time.c_str())), "Cannot put end boundary on trigger");

    auto start_time = std::format(L"{:%Y-%m-%dT%T}", start);
    THROW_IF_FAILED_MSG(pTimeTrigger->put_StartBoundary(_bstr_t(start_time.c_str())), "Cannot add start boundary to trigger");
}

void run()
{
    auto cleanup = init_com();
    auto pService = connect_task_service();
    auto pRootFolder = get_root_folder(*pService);
    auto pTask = create_task(*pService);
    set_author(*pTask, L"Author Name");
    set_logon_type(*pTask, TASK_LOGON_INTERACTIVE_TOKEN);
    set_settings(*pTask, true, std::chrono::minutes(5));
    add_time_trigger(*pTask, L"Trigger1", make_date_time(2005y/1/1, 12h + 5min), make_date_time(2015y/5/2, 8h));

    //  ------------------------------------------------------
    //  Add an action to the task. This task will execute notepad.exe.
    wil::com_ptr<IActionCollection> pActionCollection;

    //  Get the task action collection pointer.
    THROW_IF_FAILED_MSG(pTask->get_Actions(pActionCollection.put()), "Cannot get Task collection pointer");

    //  Create the action, specifying that it is an executable action.
    wil::com_ptr<IAction> pAction;
    THROW_IF_FAILED_MSG(pActionCollection->Create(TASK_ACTION_EXEC, pAction.put()), "Cannot create the action");

    auto pExecAction = pAction.query<IExecAction>();

    //  Set the path of the executable to notepad.exe.
    auto wstrExecutablePath = get_executable_path();
    THROW_IF_FAILED_MSG(pExecAction->put_Path(_bstr_t(wstrExecutablePath.c_str())), "Cannot put action path");

    //  ------------------------------------------------------
    //  Create a name for the task.
    LPCWSTR wszTaskName = L"Time Trigger Test Task";

    //  ------------------------------------------------------
    //  Save the task in the root folder.
    wil::com_ptr<IRegisteredTask> pRegisteredTask;
    THROW_IF_FAILED_MSG(pRootFolder->RegisterTaskDefinition(
        _bstr_t(wszTaskName),
        pTask.get(),
        TASK_CREATE_OR_UPDATE,
        {},
        {},
        TASK_LOGON_INTERACTIVE_TOKEN,
        _variant_t(L""),
        pRegisteredTask.put()),
        "Error saving the Task");
}

int main()
try
{
    init_wil();
    run();
    printf("\n Success! Task successfully registered. ");
}
CATCH_RETURN()