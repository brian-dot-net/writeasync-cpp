#include "stub_settings.h"

namespace wacpp::test
{

STDMETHODIMP Stub_IIdleSettings::get_IdleDuration(
    [[maybe_unused]] BSTR* pDelay) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IIdleSettings::put_IdleDuration(
    [[maybe_unused]] BSTR delay) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IIdleSettings::get_WaitTimeout(
    [[maybe_unused]] BSTR* pTimeout) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IIdleSettings::put_WaitTimeout(
    [[maybe_unused]] BSTR timeout) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IIdleSettings::get_StopOnIdleEnd(
    [[maybe_unused]] VARIANT_BOOL* pStop) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IIdleSettings::put_StopOnIdleEnd(
    [[maybe_unused]] VARIANT_BOOL stop) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IIdleSettings::get_RestartOnIdle(
    [[maybe_unused]] VARIANT_BOOL* pRestart) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IIdleSettings::put_RestartOnIdle(
    [[maybe_unused]] VARIANT_BOOL restart) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IIdleSettings::GetTypeInfoCount(
    [[maybe_unused]] UINT* pctinfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IIdleSettings::GetTypeInfo(
    [[maybe_unused]] UINT iTInfo,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] ITypeInfo** ppTInfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IIdleSettings::GetIDsOfNames(
    [[maybe_unused]] REFIID riid,
    [[maybe_unused]] LPOLESTR* rgszNames,
    [[maybe_unused]] UINT cNames,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] DISPID* rgDispId) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_IIdleSettings::Invoke(
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

STDMETHODIMP Stub_ITaskSettings::get_AllowDemandStart(
    [[maybe_unused]] VARIANT_BOOL* pAllowDemandStart) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_AllowDemandStart(
    [[maybe_unused]] VARIANT_BOOL allowDemandStart) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_RestartInterval(
    [[maybe_unused]] BSTR* pRestartInterval) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_RestartInterval(
    [[maybe_unused]] BSTR restartInterval) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_RestartCount(
    [[maybe_unused]] int* pRestartCount) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_RestartCount(
    [[maybe_unused]] int restartCount) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_MultipleInstances(
    [[maybe_unused]] TASK_INSTANCES_POLICY* pPolicy) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_MultipleInstances(
    [[maybe_unused]] TASK_INSTANCES_POLICY policy) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_StopIfGoingOnBatteries(
    [[maybe_unused]] VARIANT_BOOL* pStopIfOnBatteries) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_StopIfGoingOnBatteries(
    [[maybe_unused]] VARIANT_BOOL stopIfOnBatteries) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_DisallowStartIfOnBatteries(
    [[maybe_unused]] VARIANT_BOOL* pDisallowStart) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_DisallowStartIfOnBatteries(
    [[maybe_unused]] VARIANT_BOOL disallowStart) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_AllowHardTerminate(
    [[maybe_unused]] VARIANT_BOOL* pAllowHardTerminate) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_AllowHardTerminate(
    [[maybe_unused]] VARIANT_BOOL allowHardTerminate) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_StartWhenAvailable(
    [[maybe_unused]] VARIANT_BOOL* pStartWhenAvailable) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_StartWhenAvailable(
    [[maybe_unused]] VARIANT_BOOL startWhenAvailable) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_XmlText(
    [[maybe_unused]] BSTR* pText) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_XmlText(
    [[maybe_unused]] BSTR text) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_RunOnlyIfNetworkAvailable(
    [[maybe_unused]] VARIANT_BOOL* pRunOnlyIfNetworkAvailable) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_RunOnlyIfNetworkAvailable(
    [[maybe_unused]] VARIANT_BOOL runOnlyIfNetworkAvailable) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_ExecutionTimeLimit(
    [[maybe_unused]] BSTR* pExecutionTimeLimit) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_ExecutionTimeLimit(
    [[maybe_unused]] BSTR executionTimeLimit) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_Enabled(
    [[maybe_unused]] VARIANT_BOOL* pEnabled) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_Enabled(
    [[maybe_unused]] VARIANT_BOOL enabled) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_DeleteExpiredTaskAfter(
    [[maybe_unused]] BSTR* pExpirationDelay) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_DeleteExpiredTaskAfter(
    [[maybe_unused]] BSTR expirationDelay) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_Priority(
    [[maybe_unused]] int* pPriority) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_Priority(
    [[maybe_unused]] int priority) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_Compatibility(
    [[maybe_unused]] TASK_COMPATIBILITY* pCompatLevel) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_Compatibility(
    [[maybe_unused]] TASK_COMPATIBILITY compatLevel) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_Hidden(
    [[maybe_unused]] VARIANT_BOOL* pHidden) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_Hidden(
    [[maybe_unused]] VARIANT_BOOL hidden) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_IdleSettings(
    [[maybe_unused]] IIdleSettings** ppIdleSettings) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_IdleSettings(
    [[maybe_unused]] IIdleSettings* pIdleSettings) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_RunOnlyIfIdle(
    [[maybe_unused]] VARIANT_BOOL* pRunOnlyIfIdle) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_RunOnlyIfIdle(
    [[maybe_unused]] VARIANT_BOOL runOnlyIfIdle) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_WakeToRun(
    [[maybe_unused]] VARIANT_BOOL* pWake) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_WakeToRun(
    [[maybe_unused]] VARIANT_BOOL wake) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::get_NetworkSettings(
    [[maybe_unused]] INetworkSettings** ppNetworkSettings) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::put_NetworkSettings(
    [[maybe_unused]] INetworkSettings* pNetworkSettings) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::GetTypeInfoCount(
    [[maybe_unused]] UINT* pctinfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::GetTypeInfo(
    [[maybe_unused]] UINT iTInfo,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] ITypeInfo** ppTInfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::GetIDsOfNames(
    [[maybe_unused]] REFIID riid,
    [[maybe_unused]] LPOLESTR* rgszNames,
    [[maybe_unused]] UINT cNames,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] DISPID* rgDispId) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskSettings::Invoke(
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