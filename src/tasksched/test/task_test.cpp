#include <gtest/gtest.h>

#include <windows.h>

#include <wil/com.h>

#include "stub_reginfo.h"
#include "stub_taskdef.h"
#include "task.h"

namespace
{

struct Stub
{
    struct Data
    {
        HRESULT get_RegistrationInfo_result{};
    };

    class RegistrationInfo : public wacpp::test::Stub_IRegistrationInfo
    {
    public:
        RegistrationInfo(const Data& data)
            : m_data(data)
        {}

    private:
        const Data& m_data;
    };

    class TaskDefinition : public wacpp::test::Stub_ITaskDefinition
    {
    public:
        TaskDefinition(const Data& data)
            : m_data(data)
        {}

        STDMETHODIMP get_XmlText(
            BSTR* pXml) noexcept override
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

        STDMETHODIMP get_RegistrationInfo(
            IRegistrationInfo** ppRegistrationInfo) noexcept override
        try
        {
            const auto hr = m_data.get_RegistrationInfo_result;
            if (SUCCEEDED(hr))
            {
                auto ptr = winrt::make<Stub::RegistrationInfo>(m_data);
                ptr.copy_to(ppRegistrationInfo);
            }

            return hr;
        }
        CATCH_RETURN()

    private:
        const Data& m_data;
    };
};

wil::com_ptr<ITaskDefinition> make_stub_task_definition(const Stub::Data& data)
{
    auto ptr = winrt::make<Stub::TaskDefinition>(data);
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
    Stub::Data data{.get_RegistrationInfo_result = E_FAIL };
    Task task(make_stub_task_definition(data));

    ASSERT_THROW(task.set_author(L"Fail 1"), wil::ResultException);

    assert_xml(task, L"<Task></Task>");

    data.get_RegistrationInfo_result = S_OK;

    ASSERT_THROW(task.set_author(L"Fail 2"), wil::ResultException);

    assert_xml(task, L"<Task></Task>");
}

}