#include <gtest/gtest.h>

#include <windows.h>

#include <wil/com.h>

#include "stub_taskfolder.h"
#include "task_folder.h"

namespace
{

struct Stub
{
    struct TaskFolderData
    {
    };

    class TaskFolder : public wacpp::test::Stub_ITaskFolder
    {
    public:
        using Data = TaskFolderData;

        TaskFolder(const Data& data)
            : m_data(data)
        {}

    private:
        const Data& m_data;
    };

    class TaskWrapper
    {
    public:
        TaskWrapper()
            : m_ptr(this)
        {
        }

        ITaskDefinition& get()
        {
            // This is normally very unsafe. However, the user will never
            // call anything on this reference; it is essentially a token.
            return *reinterpret_cast<ITaskDefinition*>(m_ptr);
        }

    private:
        void* m_ptr;
    };
};

wil::com_ptr<ITaskFolder> make_stub_task_folder(const Stub::TaskFolderData& data)
{
    auto ptr = winrt::make<Stub::TaskFolder>(data);
    return wil::make_com_ptr(ptr.detach());
}

wil::com_ptr<IRegisteredTask> try_get_task(wacpp::TaskFolder& folder, LPCWSTR name)
{
    auto nameb = wil::make_bstr(name);
    wil::com_ptr<IRegisteredTask> task;
    if (FAILED(folder.get().GetTask(nameb.get(), task.put())))
    {
        task.reset();
    }

    return task;
}

}

namespace wacpp::test
{

TEST(task_folder_test, save)
{
    Stub::TaskFolderData data{};
    TaskFolder folder(make_stub_task_folder(data));
    Stub::TaskWrapper wrapper{};

    ASSERT_THROW(folder.save(wrapper, L"Fail1"), wil::ResultException);

    auto task = try_get_task(folder, L"Fail1");
    ASSERT_EQ(nullptr, task);
}

}