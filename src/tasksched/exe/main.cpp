#include <stdio.h>

#include <string>
#include <vector>

#include <windows.h>
#include <comutil.h>
#include <taskschd.h>

#include <wil/com.h>
#include <wil/resource.h>
#include <wil/win32_helpers.h>

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

void run()
{
    auto cleanup = init_com();
    auto pService = connect_task_service();
    auto pRootFolder = get_root_folder(*pService);
    auto pTask = create_task(*pService);

    //  ------------------------------------------------------
    //  Get the registration info for setting the identification.
    wil::com_ptr<IRegistrationInfo> pRegInfo;
    THROW_IF_FAILED_MSG(pTask->get_RegistrationInfo(pRegInfo.put()), "Cannot get identification pointer");
    THROW_IF_FAILED_MSG(pRegInfo->put_Author(_bstr_t(L"Author Name")), "Cannot put identification info");

    //  ------------------------------------------------------
    //  Create the principal for the task - these credentials
    //  are overwritten with the credentials passed to RegisterTaskDefinition
    wil::com_ptr<IPrincipal> pPrincipal;
    THROW_IF_FAILED_MSG(pTask->get_Principal(pPrincipal.put()), "Cannot get principal pointer");

    //  Set up principal logon type to interactive logon
    THROW_IF_FAILED_MSG(pPrincipal->put_LogonType(TASK_LOGON_INTERACTIVE_TOKEN), "Cannot put principal info");

    //  ------------------------------------------------------
    //  Create the settings for the task
    wil::com_ptr<ITaskSettings> pSettings;
    THROW_IF_FAILED_MSG(pTask->get_Settings(pSettings.put()), "Cannot get settings pointer");

    //  Set setting values for the task.
    THROW_IF_FAILED_MSG(pSettings->put_StartWhenAvailable(VARIANT_TRUE), "Cannot put setting information");

    // Set the idle settings for the task.
    wil::com_ptr<IIdleSettings> pIdleSettings;
    THROW_IF_FAILED_MSG(pSettings->get_IdleSettings(pIdleSettings.put()), "Cannot get idle setting information");
    THROW_IF_FAILED_MSG(pIdleSettings->put_WaitTimeout(_bstr_t(L"PT5M")), "Cannot put idle setting information");

    //  ------------------------------------------------------
    //  Get the trigger collection to insert the time trigger.
    wil::com_ptr<ITriggerCollection> pTriggerCollection;
    THROW_IF_FAILED_MSG(pTask->get_Triggers(pTriggerCollection.put()), "Cannot get trigger collection");

    //  Add the time trigger to the task.
    wil::com_ptr<ITrigger> pTrigger;
    THROW_IF_FAILED_MSG(pTriggerCollection->Create(TASK_TRIGGER_TIME, pTrigger.put()), "Cannot create trigger");

    auto pTimeTrigger = pTrigger.query<ITimeTrigger>();
    THROW_IF_FAILED_MSG(pTimeTrigger->put_Id(_bstr_t(L"Trigger1")), "Cannot put trigger ID");
    THROW_IF_FAILED_MSG(pTimeTrigger->put_EndBoundary(_bstr_t(L"2015-05-02T08:00:00")), "Cannot put end boundary on trigger");

    //  Set the task to start at a certain time. The time
    //  format should be YYYY-MM-DDTHH:MM:SS(+-)(timezone).
    //  For example, the start boundary below
    //  is January 1st 2005 at 12:05
    THROW_IF_FAILED_MSG(pTimeTrigger->put_StartBoundary(_bstr_t(L"2005-01-01T12:05:00")), "Cannot add start boundary to trigger");

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