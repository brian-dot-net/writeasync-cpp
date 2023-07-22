#pragma once

#include <windows.h>
#include <taskschd.h>

#include <wil/cppwinrt.h>

namespace wacpp::test
{

class Stub_ITaskSettings : public winrt::implements<Stub_ITaskSettings, ITaskSettings>
{
public:
    // ITaskSettings

    STDMETHODIMP get_AllowDemandStart(
        VARIANT_BOOL* pAllowDemandStart) noexcept override;

    STDMETHODIMP put_AllowDemandStart(
        VARIANT_BOOL allowDemandStart) noexcept override;

    STDMETHODIMP get_RestartInterval(
        BSTR* pRestartInterval) noexcept override;

    STDMETHODIMP put_RestartInterval(
        BSTR restartInterval) noexcept override;

    STDMETHODIMP get_RestartCount(
        int* pRestartCount) noexcept override;

    STDMETHODIMP put_RestartCount(
        int restartCount) noexcept override;

    STDMETHODIMP get_MultipleInstances(
        TASK_INSTANCES_POLICY* pPolicy) noexcept override;

    STDMETHODIMP put_MultipleInstances(
        TASK_INSTANCES_POLICY policy) noexcept override;

    STDMETHODIMP get_StopIfGoingOnBatteries(
        VARIANT_BOOL* pStopIfOnBatteries) noexcept override;

    STDMETHODIMP put_StopIfGoingOnBatteries(
        VARIANT_BOOL stopIfOnBatteries) noexcept override;

    STDMETHODIMP get_DisallowStartIfOnBatteries(
        VARIANT_BOOL* pDisallowStart) noexcept override;

    STDMETHODIMP put_DisallowStartIfOnBatteries(
        VARIANT_BOOL disallowStart) noexcept override;

    STDMETHODIMP get_AllowHardTerminate(
        VARIANT_BOOL* pAllowHardTerminate) noexcept override;

    STDMETHODIMP put_AllowHardTerminate(
        VARIANT_BOOL allowHardTerminate) noexcept override;

    STDMETHODIMP get_StartWhenAvailable(
        VARIANT_BOOL* pStartWhenAvailable) noexcept override;

    STDMETHODIMP put_StartWhenAvailable(
        VARIANT_BOOL startWhenAvailable) noexcept override;

    STDMETHODIMP get_XmlText(
        BSTR* pText) noexcept override;

    STDMETHODIMP put_XmlText(
        BSTR text) noexcept override;

    STDMETHODIMP get_RunOnlyIfNetworkAvailable(
        VARIANT_BOOL* pRunOnlyIfNetworkAvailable) noexcept override;

    STDMETHODIMP put_RunOnlyIfNetworkAvailable(
        VARIANT_BOOL runOnlyIfNetworkAvailable) noexcept override;

    STDMETHODIMP get_ExecutionTimeLimit(
        BSTR* pExecutionTimeLimit) noexcept override;

    STDMETHODIMP put_ExecutionTimeLimit(
        BSTR executionTimeLimit) noexcept override;

    STDMETHODIMP get_Enabled(
        VARIANT_BOOL* pEnabled) noexcept override;

    STDMETHODIMP put_Enabled(
        VARIANT_BOOL enabled) noexcept override;

    STDMETHODIMP get_DeleteExpiredTaskAfter(
        BSTR* pExpirationDelay) noexcept override;

    STDMETHODIMP put_DeleteExpiredTaskAfter(
        BSTR expirationDelay) noexcept override;

    STDMETHODIMP get_Priority(
        int* pPriority) noexcept override;

    STDMETHODIMP put_Priority(
        int priority) noexcept override;

    STDMETHODIMP get_Compatibility(
        TASK_COMPATIBILITY* pCompatLevel) noexcept override;

    STDMETHODIMP put_Compatibility(
        TASK_COMPATIBILITY compatLevel) noexcept override;

    STDMETHODIMP get_Hidden(
        VARIANT_BOOL* pHidden) noexcept override;

    STDMETHODIMP put_Hidden(
        VARIANT_BOOL hidden) noexcept override;

    STDMETHODIMP get_IdleSettings(
        IIdleSettings** ppIdleSettings) noexcept override;

    STDMETHODIMP put_IdleSettings(
        IIdleSettings* pIdleSettings) noexcept override;

    STDMETHODIMP get_RunOnlyIfIdle(
        VARIANT_BOOL* pRunOnlyIfIdle) noexcept override;

    STDMETHODIMP put_RunOnlyIfIdle(
        VARIANT_BOOL runOnlyIfIdle) noexcept override;

    STDMETHODIMP get_WakeToRun(
        VARIANT_BOOL* pWake) noexcept override;

    STDMETHODIMP put_WakeToRun(
        VARIANT_BOOL wake) noexcept override;

    STDMETHODIMP get_NetworkSettings(
        INetworkSettings** ppNetworkSettings) noexcept override;

    STDMETHODIMP put_NetworkSettings(
        INetworkSettings* pNetworkSettings) noexcept override;

    // IDispatch

    STDMETHODIMP GetTypeInfoCount(
        UINT* pctinfo) noexcept override;

    STDMETHODIMP GetTypeInfo(
        UINT iTInfo,
        LCID lcid,
        ITypeInfo** ppTInfo) noexcept override;

    STDMETHODIMP GetIDsOfNames(
        REFIID riid,
        LPOLESTR* rgszNames,
        UINT cNames,
        LCID lcid,
        DISPID* rgDispId) noexcept override;

    STDMETHODIMP Invoke(
        DISPID dispIdMember,
        REFIID riid,
        LCID lcid,
        WORD wFlags,
        DISPPARAMS* pDispParams,
        VARIANT* pVarResult,
        EXCEPINFO* pExcepInfo,
        UINT* puArgErr) noexcept override;
};

}