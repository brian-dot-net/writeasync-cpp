#pragma once

#include <windows.h>
#include <taskschd.h>

#include <wil/cppwinrt.h>

namespace wacpp::test
{

class Stub_IRegisteredTask : public winrt::implements<Stub_IRegisteredTask, IRegisteredTask>
{
public:
    // IRegisteredTask

    STDMETHODIMP get_Name(
        BSTR* pName) noexcept override;

    STDMETHODIMP get_Path(
        BSTR* pPath) noexcept override;

    STDMETHODIMP get_State(
        TASK_STATE* pState) noexcept override;

    STDMETHODIMP get_Enabled(
        VARIANT_BOOL* pEnabled) noexcept override;

    STDMETHODIMP put_Enabled(
        VARIANT_BOOL enabled) noexcept override;

    STDMETHODIMP Run(
        VARIANT params,
        IRunningTask** ppRunningTask) noexcept override;

    STDMETHODIMP RunEx(
        VARIANT params,
        LONG flags,
        LONG sessionID,
        BSTR user,
        IRunningTask** ppRunningTask) noexcept override;

    STDMETHODIMP GetInstances(
        LONG flags,
        IRunningTaskCollection** ppRunningTasks) noexcept override;

    STDMETHODIMP get_LastRunTime(
        DATE* pLastRunTime) noexcept override;

    STDMETHODIMP get_LastTaskResult(
        LONG* pLastTaskResult) noexcept override;

    STDMETHODIMP get_NumberOfMissedRuns(
        LONG* pNumberOfMissedRuns) noexcept override;

    STDMETHODIMP get_NextRunTime(
        DATE* pNextRunTime) noexcept override;

    STDMETHODIMP get_Definition(
        ITaskDefinition** ppDefinition) noexcept override;

    STDMETHODIMP get_Xml(
        BSTR* pXml) noexcept override;

    STDMETHODIMP GetSecurityDescriptor(
        LONG securityInformation,
        BSTR* pSddl) noexcept override;

    STDMETHODIMP SetSecurityDescriptor(
        BSTR sddl,
        LONG flags) noexcept override;

    STDMETHODIMP Stop(
        LONG flags) noexcept override;

    STDMETHODIMP GetRunTimes(
        const LPSYSTEMTIME pstStart,
        const LPSYSTEMTIME pstEnd,
        DWORD* pCount,
        LPSYSTEMTIME* pRunTimes) noexcept override;

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