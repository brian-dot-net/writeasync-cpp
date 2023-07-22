#pragma once

#include <windows.h>
#include <taskschd.h>

#include <wil/cppwinrt.h>

namespace wacpp::test
{

class Stub_IPrincipal : public winrt::implements<Stub_IPrincipal, IPrincipal>
{
public:
    // IPrincipal

    STDMETHODIMP get_Id(
        BSTR* pId) noexcept override;

    STDMETHODIMP put_Id(
        BSTR Id) noexcept override;

    STDMETHODIMP get_DisplayName(
        BSTR* pName) noexcept override;

    STDMETHODIMP put_DisplayName(
        BSTR name) noexcept override;

    STDMETHODIMP get_UserId(
        BSTR* pUser) noexcept override;

    STDMETHODIMP put_UserId(
        BSTR user) noexcept override;

    STDMETHODIMP get_LogonType(
        TASK_LOGON_TYPE* pLogon) noexcept override;

    STDMETHODIMP put_LogonType(
        TASK_LOGON_TYPE logon) noexcept override;

    STDMETHODIMP get_GroupId(
        BSTR* pGroup) noexcept override;

    STDMETHODIMP put_GroupId(
        BSTR group) noexcept override;

    STDMETHODIMP get_RunLevel(
        TASK_RUNLEVEL_TYPE* pRunLevel) noexcept override;

    STDMETHODIMP put_RunLevel(
        TASK_RUNLEVEL_TYPE runLevel) noexcept override;

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