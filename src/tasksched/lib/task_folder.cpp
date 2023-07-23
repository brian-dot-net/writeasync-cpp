#include "task_folder.h"

namespace wacpp
{

TaskFolder::TaskFolder(wil::com_ptr<ITaskFolder> folder)
    : m_folder(std::move(folder))
{}

void TaskFolder::save_definition(ITaskDefinition& task, LPCWSTR name)
{
    auto value = wil::make_bstr(name);
    wil::com_ptr<IRegisteredTask> pRegisteredTask;
    THROW_IF_FAILED_MSG(m_folder->RegisterTaskDefinition(
        value.get(),
        &task,
        TASK_CREATE_OR_UPDATE,
        {},
        {},
        TASK_LOGON_INTERACTIVE_TOKEN,
        {},
        pRegisteredTask.put()),
        "Error saving the Task");
}

}