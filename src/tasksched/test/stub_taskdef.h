#pragma once

#include <windows.h>
#include <taskschd.h>

#include <wil/cppwinrt.h>

namespace wacpp::test
{

class Stub_ITaskDefinition : public winrt::implements<Stub_ITaskDefinition, ITaskDefinition>
{
public:
    // ITaskDefinition

    STDMETHODIMP get_RegistrationInfo(
        IRegistrationInfo** ppRegistrationInfo) noexcept override;

    STDMETHODIMP put_RegistrationInfo(
        IRegistrationInfo* pRegistrationInfo) noexcept override;

    STDMETHODIMP get_Triggers(
        ITriggerCollection** ppTriggers) noexcept override;

    STDMETHODIMP put_Triggers(
        ITriggerCollection* pTriggers) noexcept override;

    STDMETHODIMP get_Settings(
        ITaskSettings** ppSettings) noexcept override;

    STDMETHODIMP put_Settings(
        ITaskSettings* pSettings) noexcept override;

    STDMETHODIMP get_Data(
        BSTR* pData) noexcept override;

    STDMETHODIMP put_Data(
        BSTR data) noexcept override;

    STDMETHODIMP get_Principal(
        IPrincipal** ppPrincipal) noexcept override;

    STDMETHODIMP put_Principal(
        IPrincipal* pPrincipal) noexcept override;

    STDMETHODIMP get_Actions(
        IActionCollection** ppActions) noexcept override;

    STDMETHODIMP put_Actions(
        IActionCollection* pActions) noexcept override;

    STDMETHODIMP get_XmlText(
        BSTR* pXml) noexcept override;

    STDMETHODIMP put_XmlText(
        BSTR xml) noexcept override;

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