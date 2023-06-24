#include <stdio.h>

#include <string>
#include <vector>

#include <windows.h>
#include <comutil.h>
#include <taskschd.h>

#include <wil/com.h>
#include <wil/resource.h>
#include <wil/win32_helpers.h>

using unique_couninitialize_call = wil::unique_call<decltype(&::CoUninitialize), ::CoUninitialize>;

int main()
{
    //  ------------------------------------------------------
    //  Initialize COM.
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr))
    {
        printf("\nCoInitializeEx failed: %x", hr);
        return 1;
    }

    unique_couninitialize_call cleanup;

    //  Set general COM security levels.
    hr = CoInitializeSecurity(
        nullptr,
        -1,
        nullptr,
        nullptr,
        RPC_C_AUTHN_LEVEL_PKT_PRIVACY,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        nullptr,
        0,
        nullptr);

    if (FAILED(hr))
    {
        printf("\nCoInitializeSecurity failed: %x", hr);
        return 1;
    }

    //  ------------------------------------------------------
    //  Create a name for the task.
    LPCWSTR wszTaskName = L"Time Trigger Test Task";

    //  Get the windows directory and set the path to notepad.exe.
    auto windir = wil::TryGetEnvironmentVariableW(L"WINDIR");
    std::wstring wstrExecutablePath(windir.get());
    if (wstrExecutablePath.empty())
    {
        printf("Failed to get environment variable");
        return 1;
    }

    wstrExecutablePath += L"\\SYSTEM32\\NOTEPAD.EXE";

    //  ------------------------------------------------------
    //  Create an instance of the Task Service.
    auto pService = wil::CoCreateInstanceNoThrow<ITaskService>(CLSID_TaskScheduler, CLSCTX_INPROC_SERVER);
    if (!pService)
    {
        printf("Failed to create an instance of ITaskService");
        return 1;
    }

    //  Connect to the task service.
    hr = pService->Connect({}, {}, {}, {});
    if (FAILED(hr))
    {
        printf("ITaskService::Connect failed: %x", hr);
        return 1;
    }

    //  ------------------------------------------------------
    //  Get the pointer to the root task folder.  This folder will hold the
    //  new task that is registered.
    wil::com_ptr_nothrow<ITaskFolder> pRootFolder;
    hr = pService->GetFolder(_bstr_t(L"\\"), pRootFolder.put());
    if (FAILED(hr))
    {
        printf("Cannot get Root folder pointer: %x", hr);
        return 1;
    }

    //  If the same task exists, remove it.
    pRootFolder->DeleteTask(_bstr_t(wszTaskName), 0);

    //  Create the task definition object to create the task.
    ITaskDefinition* pTask{};
    hr = pService->NewTask(0, &pTask);

    if (FAILED(hr))
    {
        printf("Failed to CoCreate an instance of the TaskService class: %x", hr);
        return 1;
    }

    //  ------------------------------------------------------
    //  Get the registration info for setting the identification.
    IRegistrationInfo* pRegInfo{};
    hr = pTask->get_RegistrationInfo(&pRegInfo);
    if (FAILED(hr))
    {
        printf("\nCannot get identification pointer: %x", hr);
        pTask->Release();
        return 1;
    }

    hr = pRegInfo->put_Author(_bstr_t(L"Author Name"));
    pRegInfo->Release();
    if (FAILED(hr))
    {
        printf("\nCannot put identification info: %x", hr);
        pTask->Release();
        return 1;
    }

    //  ------------------------------------------------------
    //  Create the principal for the task - these credentials
    //  are overwritten with the credentials passed to RegisterTaskDefinition
    IPrincipal* pPrincipal{};
    hr = pTask->get_Principal(&pPrincipal);
    if (FAILED(hr))
    {
        printf("\nCannot get principal pointer: %x", hr);
        pTask->Release();
        return 1;
    }

    //  Set up principal logon type to interactive logon
    hr = pPrincipal->put_LogonType(TASK_LOGON_INTERACTIVE_TOKEN);
    pPrincipal->Release();
    if (FAILED(hr))
    {
        printf("\nCannot put principal info: %x", hr);
        pTask->Release();
        return 1;
    }

    //  ------------------------------------------------------
    //  Create the settings for the task
    ITaskSettings* pSettings{};
    hr = pTask->get_Settings(&pSettings);
    if (FAILED(hr))
    {
        printf("\nCannot get settings pointer: %x", hr);
        pTask->Release();
        return 1;
    }

    //  Set setting values for the task.
    hr = pSettings->put_StartWhenAvailable(VARIANT_TRUE);
    pSettings->Release();
    if (FAILED(hr))
    {
        printf("\nCannot put setting information: %x", hr);
        pTask->Release();
        return 1;
    }

    // Set the idle settings for the task.
    IIdleSettings* pIdleSettings{};
    hr = pSettings->get_IdleSettings(&pIdleSettings);
    if (FAILED(hr))
    {
        printf("\nCannot get idle setting information: %x", hr);
        pTask->Release();
        return 1;
    }

    hr = pIdleSettings->put_WaitTimeout(_bstr_t(L"PT5M"));
    pIdleSettings->Release();
    if (FAILED(hr))
    {
        printf("\nCannot put idle setting information: %x", hr);
        pTask->Release();
        return 1;
    }

    //  ------------------------------------------------------
    //  Get the trigger collection to insert the time trigger.
    ITriggerCollection* pTriggerCollection{};
    hr = pTask->get_Triggers(&pTriggerCollection);
    if (FAILED(hr))
    {
        printf("\nCannot get trigger collection: %x", hr);
        pTask->Release();
        return 1;
    }

    //  Add the time trigger to the task.
    ITrigger* pTrigger{};
    hr = pTriggerCollection->Create(TASK_TRIGGER_TIME, &pTrigger);
    pTriggerCollection->Release();
    if (FAILED(hr))
    {
        printf("\nCannot create trigger: %x", hr);
        pTask->Release();
        return 1;
    }

    ITimeTrigger* pTimeTrigger{};
    hr = pTrigger->QueryInterface(
        IID_ITimeTrigger, (void**)&pTimeTrigger);
    pTrigger->Release();
    if (FAILED(hr))
    {
        printf("\nQueryInterface call failed for ITimeTrigger: %x", hr);
        pTask->Release();
        return 1;
    }

    hr = pTimeTrigger->put_Id(_bstr_t(L"Trigger1"));
    if (FAILED(hr))
    {
        printf("\nCannot put trigger ID: %x", hr);
    }

    hr = pTimeTrigger->put_EndBoundary(_bstr_t(L"2015-05-02T08:00:00"));
    if (FAILED(hr))
    {
        printf("\nCannot put end boundary on trigger: %x", hr);
    }

    //  Set the task to start at a certain time. The time
    //  format should be YYYY-MM-DDTHH:MM:SS(+-)(timezone).
    //  For example, the start boundary below
    //  is January 1st 2005 at 12:05
    hr = pTimeTrigger->put_StartBoundary(_bstr_t(L"2005-01-01T12:05:00"));
    pTimeTrigger->Release();
    if (FAILED(hr))
    {
        printf("\nCannot add start boundary to trigger: %x", hr);
        pTask->Release();
        return 1;
    }

    //  ------------------------------------------------------
    //  Add an action to the task. This task will execute notepad.exe.
    IActionCollection* pActionCollection{};

    //  Get the task action collection pointer.
    hr = pTask->get_Actions(&pActionCollection);
    if (FAILED(hr))
    {
        printf("\nCannot get Task collection pointer: %x", hr);
        pTask->Release();
        return 1;
    }

    //  Create the action, specifying that it is an executable action.
    IAction* pAction{};
    hr = pActionCollection->Create(TASK_ACTION_EXEC, &pAction);
    pActionCollection->Release();
    if (FAILED(hr))
    {
        printf("\nCannot create the action: %x", hr);
        pTask->Release();
        return 1;
    }

    void* pExecActionVoid{};
    //  QI for the executable task pointer.
    hr = pAction->QueryInterface(IID_IExecAction, &pExecActionVoid);
    pAction->Release();
    if (FAILED(hr))
    {
        printf("\nQueryInterface call failed for IExecAction: %x", hr);
        pTask->Release();
        return 1;
    }

    //  Set the path of the executable to notepad.exe.
    IExecAction* pExecAction = static_cast<IExecAction*>(pExecActionVoid);
    hr = pExecAction->put_Path(_bstr_t(wstrExecutablePath.c_str()));
    pExecAction->Release();
    if (FAILED(hr))
    {
        printf("\nCannot put action path: %x", hr);
        pTask->Release();
        return 1;
    }

    //  ------------------------------------------------------
    //  Save the task in the root folder.
    IRegisteredTask* pRegisteredTask{};
    hr = pRootFolder->RegisterTaskDefinition(
        _bstr_t(wszTaskName),
        pTask,
        TASK_CREATE_OR_UPDATE,
        {},
        {},
        TASK_LOGON_INTERACTIVE_TOKEN,
        _variant_t(L""),
        &pRegisteredTask);
    if (FAILED(hr))
    {
        printf("\nError saving the Task : %x", hr);
        pTask->Release();
        return 1;
    }

    printf("\n Success! Task successfully registered. ");

    //  Clean up.
    pTask->Release();
    pRegisteredTask->Release();
    return 0;
}