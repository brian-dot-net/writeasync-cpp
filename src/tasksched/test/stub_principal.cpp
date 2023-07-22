#include "stub_principal.h"

namespace wacpp::test
{

STDMETHODIMP Stub_IPrincipal::get_Id(
    [[maybe_unused]] BSTR* pId) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IPrincipal::put_Id(
    [[maybe_unused]] BSTR Id) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IPrincipal::get_DisplayName(
    [[maybe_unused]] BSTR* pName) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IPrincipal::put_DisplayName(
    [[maybe_unused]] BSTR name) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IPrincipal::get_UserId(
    [[maybe_unused]] BSTR* pUser) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IPrincipal::put_UserId(
    [[maybe_unused]] BSTR user) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IPrincipal::get_LogonType(
    [[maybe_unused]] TASK_LOGON_TYPE* pLogon) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IPrincipal::put_LogonType(
    [[maybe_unused]] TASK_LOGON_TYPE logon) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IPrincipal::get_GroupId(
    [[maybe_unused]] BSTR* pGroup) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IPrincipal::put_GroupId(
    [[maybe_unused]] BSTR group) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IPrincipal::get_RunLevel(
    [[maybe_unused]] TASK_RUNLEVEL_TYPE* pRunLevel) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IPrincipal::put_RunLevel(
    [[maybe_unused]] TASK_RUNLEVEL_TYPE runLevel) noexcept
{
    return E_NOTIMPL;
}

// IDispatch

STDMETHODIMP Stub_IPrincipal::GetTypeInfoCount(
    [[maybe_unused]] UINT* pctinfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IPrincipal::GetTypeInfo(
    [[maybe_unused]] UINT iTInfo,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] ITypeInfo** ppTInfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IPrincipal::GetIDsOfNames(
    [[maybe_unused]] REFIID riid,
    [[maybe_unused]] LPOLESTR* rgszNames,
    [[maybe_unused]] UINT cNames,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] DISPID* rgDispId) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IPrincipal::Invoke(
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