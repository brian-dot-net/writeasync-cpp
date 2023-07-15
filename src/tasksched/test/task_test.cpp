#include <gtest/gtest.h>

#include <windows.h>

#include <wil/com.h>

#include "stub_taskdef.h"
#include "task.h"

namespace
{
class StubTaskDefinition : public wacpp::test::Stub_ITaskDefinition
{
public:
    STDMETHODIMP get_XmlText(BSTR* pXml) noexcept override
        try
    {
        std::wstring xml{};
        xml += L"<Task>";
        xml += L"</Task>";

        auto outer_xml = wil::make_bstr(xml.c_str());
        *pXml = outer_xml.release();

        return S_OK;
    }
    CATCH_RETURN()
};

wil::com_ptr<ITaskDefinition> make_stub_task_definition()
{
    auto ptr = winrt::make<StubTaskDefinition>();
    return wil::make_com_ptr(ptr.detach());
}

void assert_xml(wacpp::Task& task, const std::wstring& expected)
{
    wil::unique_bstr str{};
    THROW_IF_FAILED(task.get().get_XmlText(str.put()));
    std::wstring actual = str.get();

    ASSERT_EQ(expected, actual);
}

}

namespace wacpp::test
{

TEST(task_test, set_author)
{
    Task task(make_stub_task_definition());

    ASSERT_THROW(task.set_author(L"Fail 1"), wil::ResultException);

    assert_xml(task, L"<Task></Task>");
}

}