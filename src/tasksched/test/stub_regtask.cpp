#include "stub_regtask.h"

namespace wacpp::test
{

STDMETHODIMP Stub_IRegisteredTask::get_Name(
    [[maybe_unused]] BSTR* pName) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::get_Path(
    [[maybe_unused]] BSTR* pPath) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::get_State(
    [[maybe_unused]] TASK_STATE* pState) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::get_Enabled(
    [[maybe_unused]] VARIANT_BOOL* pEnabled) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::put_Enabled(
    [[maybe_unused]] VARIANT_BOOL enabled) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::Run(
    [[maybe_unused]] VARIANT params,
    [[maybe_unused]] IRunningTask** ppRunningTask) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::RunEx(
    [[maybe_unused]] VARIANT params,
    [[maybe_unused]] LONG flags,
    [[maybe_unused]] LONG sessionID,
    [[maybe_unused]] BSTR user,
    [[maybe_unused]] IRunningTask** ppRunningTask) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::GetInstances(
    [[maybe_unused]] LONG flags,
    [[maybe_unused]] IRunningTaskCollection** ppRunningTasks) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::get_LastRunTime(
    [[maybe_unused]] DATE* pLastRunTime) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::get_LastTaskResult(
    [[maybe_unused]] LONG* pLastTaskResult) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::get_NumberOfMissedRuns(
    [[maybe_unused]] LONG* pNumberOfMissedRuns) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::get_NextRunTime(
    [[maybe_unused]] DATE* pNextRunTime) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::get_Definition(
    [[maybe_unused]] ITaskDefinition** ppDefinition) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::get_Xml(
    [[maybe_unused]] BSTR* pXml) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::GetSecurityDescriptor(
    [[maybe_unused]] LONG securityInformation,
    [[maybe_unused]] BSTR* pSddl) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::SetSecurityDescriptor(
    [[maybe_unused]] BSTR sddl,
    [[maybe_unused]] LONG flags) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::Stop(
    [[maybe_unused]] LONG flags) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::GetRunTimes(
    [[maybe_unused]] const LPSYSTEMTIME pstStart,
    [[maybe_unused]] const LPSYSTEMTIME pstEnd,
    [[maybe_unused]] DWORD* pCount,
    [[maybe_unused]] LPSYSTEMTIME* pRunTimes) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::GetTypeInfoCount(
    [[maybe_unused]] UINT* pctinfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::GetTypeInfo(
    [[maybe_unused]] UINT iTInfo,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] ITypeInfo** ppTInfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::GetIDsOfNames(
    [[maybe_unused]] REFIID riid,
    [[maybe_unused]] LPOLESTR* rgszNames,
    [[maybe_unused]] UINT cNames,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] DISPID* rgDispId) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IRegisteredTask::Invoke(
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