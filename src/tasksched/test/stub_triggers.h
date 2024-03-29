#pragma once

#include <windows.h>
#include <taskschd.h>

#include <wil/cppwinrt.h>

namespace wacpp::test
{

class Stub_ITimeTrigger : public winrt::implements<Stub_ITimeTrigger, ITimeTrigger>
{
public:
    // ITimeTrigger

    STDMETHODIMP get_RandomDelay(
        BSTR* pRandomDelay) noexcept override;

    STDMETHODIMP put_RandomDelay(
        BSTR randomDelay) noexcept override;

    // ITrigger

    STDMETHODIMP get_Type(
        TASK_TRIGGER_TYPE2* pType) noexcept override;

    STDMETHODIMP get_Id(
        BSTR* pId) noexcept override;

    STDMETHODIMP put_Id(
        BSTR id) noexcept override;

    STDMETHODIMP get_Repetition(
        IRepetitionPattern** ppRepeat) noexcept override;

    STDMETHODIMP put_Repetition(
        IRepetitionPattern* pRepeat) noexcept override;

    STDMETHODIMP get_ExecutionTimeLimit(
        BSTR* pTimeLimit) noexcept override;

    STDMETHODIMP put_ExecutionTimeLimit(
        BSTR timelimit) noexcept override;

    STDMETHODIMP get_StartBoundary(
        BSTR* pStart) noexcept override;

    STDMETHODIMP put_StartBoundary(
        BSTR start) noexcept override;

    STDMETHODIMP get_EndBoundary(
        BSTR* pEnd) noexcept override;

    STDMETHODIMP put_EndBoundary(
        BSTR end) noexcept override;

    STDMETHODIMP get_Enabled(
        VARIANT_BOOL* pEnabled) noexcept override;

    STDMETHODIMP put_Enabled(
        VARIANT_BOOL enabled) noexcept override;

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