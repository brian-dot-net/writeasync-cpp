#pragma once

#include <windows.h>
#include <taskschd.h>

#include <wil/cppwinrt.h>

namespace wacpp::test
{

class Stub_ITriggerCollection : public winrt::implements<Stub_ITriggerCollection, ITriggerCollection>
{
public:
    // ITriggerCollection

    STDMETHODIMP get_Count(
        long* pCount) noexcept override;

    STDMETHODIMP get_Item(
        long index,
        ITrigger** ppTrigger) noexcept override;

    STDMETHODIMP get__NewEnum(
        IUnknown** ppEnum) noexcept override;

    STDMETHODIMP Create(
        TASK_TRIGGER_TYPE2 type,
        ITrigger** ppTrigger) noexcept override;

    STDMETHODIMP Remove(
        VARIANT index) noexcept override;

    STDMETHODIMP Clear() noexcept override;

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