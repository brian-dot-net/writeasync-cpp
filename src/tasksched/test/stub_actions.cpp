#include "stub_actions.h"

namespace wacpp::test
{

STDMETHODIMP Stub_IActionCollection::get_Count(
    [[maybe_unused]] long* pCount) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IActionCollection::get_Item(
    [[maybe_unused]] long index,
    [[maybe_unused]] IAction** ppAction) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IActionCollection::get__NewEnum(
    [[maybe_unused]] IUnknown** ppEnum) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IActionCollection::get_XmlText(
    [[maybe_unused]] BSTR* pText) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IActionCollection::put_XmlText(
    [[maybe_unused]] BSTR text) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IActionCollection::Create(
    [[maybe_unused]] TASK_ACTION_TYPE type,
    [[maybe_unused]] IAction** ppAction) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IActionCollection::Remove(
    [[maybe_unused]] VARIANT index) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IActionCollection::Clear() noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IActionCollection::get_Context(
    [[maybe_unused]] BSTR* pContext) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IActionCollection::put_Context(
    [[maybe_unused]] BSTR context) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IActionCollection::GetTypeInfoCount(
    [[maybe_unused]] UINT* pctinfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IActionCollection::GetTypeInfo(
    [[maybe_unused]] UINT iTInfo,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] ITypeInfo** ppTInfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IActionCollection::GetIDsOfNames(
    [[maybe_unused]] REFIID riid,
    [[maybe_unused]] LPOLESTR* rgszNames,
    [[maybe_unused]] UINT cNames,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] DISPID* rgDispId) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IActionCollection::Invoke(
    [[maybe_unused]] DISPID dispIdMember,
    [[maybe_unused]] REFIID riid,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] WORD wFlags,
    [[maybe_unused]] DISPPARAMS* pDispParams,
    [[maybe_unused]] VARIANT* pVarResult,
    [[maybe_unused]] EXCEPINFO* pExcepInfo,
    [[maybe_unused]] UINT* puArgErr) noexcept
{
    return E_NOTIMPL;
}

}