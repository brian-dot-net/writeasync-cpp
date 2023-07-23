#include "stub_tasksvc.h"

namespace wacpp::test
{

STDMETHODIMP Stub_ITaskService::GetFolder(
    [[maybe_unused]] BSTR path,
    [[maybe_unused]] ITaskFolder** ppFolder) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskService::GetRunningTasks(
    [[maybe_unused]] LONG flags,
    [[maybe_unused]] IRunningTaskCollection** ppRunningTasks) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskService::NewTask(
    [[maybe_unused]] DWORD flags,
    [[maybe_unused]] ITaskDefinition** ppDefinition) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskService::Connect(
    [[maybe_unused]] VARIANT serverName,
    [[maybe_unused]] VARIANT user,
    [[maybe_unused]] VARIANT domain,
    [[maybe_unused]] VARIANT password) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskService::get_Connected(
    [[maybe_unused]] VARIANT_BOOL* pConnected) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskService::get_TargetServer(
    [[maybe_unused]] BSTR* pServer) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskService::get_ConnectedUser(
    [[maybe_unused]] BSTR* pUser) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskService::get_ConnectedDomain(
    [[maybe_unused]] BSTR* pDomain) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskService::get_HighestVersion(
    [[maybe_unused]] DWORD* pVersion) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskService::GetTypeInfoCount(
    [[maybe_unused]] UINT* pctinfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskService::GetTypeInfo(
    [[maybe_unused]] UINT iTInfo,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] ITypeInfo** ppTInfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskService::GetIDsOfNames(
    [[maybe_unused]] REFIID riid,
    [[maybe_unused]] LPOLESTR* rgszNames,
    [[maybe_unused]] UINT cNames,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] DISPID* rgDispId) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskService::Invoke(
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