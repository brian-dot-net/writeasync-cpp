#include "task.h"

namespace wacpp
{

    Task::Task(wil::com_ptr<ITaskDefinition> task) noexcept
        : m_task(std::move(task))
    {}

    ITaskDefinition& Task::get() noexcept
    {
        return *m_task.get();
    }

    void Task::set_author(LPCWSTR author)
    {
        wil::com_ptr<IRegistrationInfo> pRegInfo;
        THROW_IF_FAILED_MSG(m_task->get_RegistrationInfo(pRegInfo.put()), "Cannot get identification pointer");
        auto value = wil::make_bstr(author);
        THROW_IF_FAILED_MSG(pRegInfo->put_Author(value.get()), "Cannot put identification info");
    }

    void Task::set_logon_type(TASK_LOGON_TYPE logon)
    {
        wil::com_ptr<IPrincipal> pPrincipal;
        THROW_IF_FAILED_MSG(m_task->get_Principal(pPrincipal.put()), "Cannot get principal pointer");
        //  Set up principal logon type to interactive logon
        THROW_IF_FAILED_MSG(pPrincipal->put_LogonType(logon), "Cannot put principal info");
    }

    void Task::set_settings(bool start_when_available, std::chrono::minutes wait_timeout)
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

    void Task::add_time_trigger(LPCWSTR id, DateTime start, DateTime end)
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

    void Task::add_exec_action(const std::wstring& path)
    {
        wil::com_ptr<IActionCollection> pActionCollection;

        THROW_IF_FAILED_MSG(m_task->get_Actions(pActionCollection.put()), "Cannot get Task collection pointer");

        wil::com_ptr<IAction> pAction;
        THROW_IF_FAILED_MSG(pActionCollection->Create(TASK_ACTION_EXEC, pAction.put()), "Cannot create the action");

        auto pExecAction = pAction.query<IExecAction>();
        auto value = wil::make_bstr(path.c_str());
        THROW_IF_FAILED_MSG(pExecAction->put_Path(value.get()), "Cannot put action path");
    }

}