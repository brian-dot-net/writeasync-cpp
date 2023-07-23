#pragma once

#include <windows.h>
#include <taskschd.h>

#include <wil/com.h>

namespace wacpp
{

class TaskFolder
{
public:
    TaskFolder(wil::com_ptr<ITaskFolder> folder);

    template <typename Task>
    void save(Task& task, LPCWSTR name)
    {
        save_definition(task.get(), name);
    }

private:
    void save_definition(ITaskDefinition& task, LPCWSTR name);

    wil::com_ptr<ITaskFolder> m_folder;
};

}