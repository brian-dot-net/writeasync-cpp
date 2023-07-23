#pragma once

#include <windows.h>
#include <taskschd.h>

#include <wil/cppwinrt.h>

namespace wacpp::test
{

class Stub_ITaskService : public winrt::implements<Stub_ITaskService, ITaskService>
{
public:
    // ITaskService

    STDMETHODIMP GetFolder(
        BSTR path,
        ITaskFolder** ppFolder) noexcept override;

    STDMETHODIMP GetRunningTasks(
        LONG flags,
        IRunningTaskCollection** ppRunningTasks) noexcept override;

    STDMETHODIMP NewTask(
        DWORD flags,
        ITaskDefinition** ppDefinition) noexcept override;

    STDMETHODIMP Connect(
        VARIANT serverName,
        VARIANT user,
        VARIANT domain,
        VARIANT password) noexcept override;

    STDMETHODIMP get_Connected(
        VARIANT_BOOL* pConnected) noexcept override;

    STDMETHODIMP get_TargetServer(
        BSTR* pServer) noexcept override;

    STDMETHODIMP get_ConnectedUser(
        BSTR* pUser) noexcept override;

    STDMETHODIMP get_ConnectedDomain(
        BSTR* pDomain) noexcept override;

    STDMETHODIMP get_HighestVersion(
        DWORD* pVersion) noexcept override;

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