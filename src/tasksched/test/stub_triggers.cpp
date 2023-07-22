#include "stub_triggers.h"

namespace wacpp::test
{

STDMETHODIMP Stub_ITimeTrigger::get_RandomDelay(
    [[maybe_unused]] BSTR* pRandomDelay) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::put_RandomDelay(
    [[maybe_unused]] BSTR randomDelay) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::get_Type(
    [[maybe_unused]] TASK_TRIGGER_TYPE2* pType) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::get_Id(
    [[maybe_unused]] BSTR* pId) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::put_Id(
    [[maybe_unused]] BSTR id) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::get_Repetition(
    [[maybe_unused]] IRepetitionPattern** ppRepeat) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::put_Repetition(
    [[maybe_unused]] IRepetitionPattern* pRepeat) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::get_ExecutionTimeLimit(
    [[maybe_unused]] BSTR* pTimeLimit) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::put_ExecutionTimeLimit(
    [[maybe_unused]] BSTR timelimit) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::get_StartBoundary(
    [[maybe_unused]] BSTR* pStart) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::put_StartBoundary(
    [[maybe_unused]] BSTR start) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::get_EndBoundary(
    [[maybe_unused]] BSTR* pEnd) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::put_EndBoundary(
    [[maybe_unused]] BSTR end) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::get_Enabled(
    [[maybe_unused]] VARIANT_BOOL* pEnabled) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::put_Enabled(
    [[maybe_unused]] VARIANT_BOOL enabled) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::GetTypeInfoCount(
    [[maybe_unused]] UINT* pctinfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::GetTypeInfo(
    [[maybe_unused]] UINT iTInfo,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] ITypeInfo** ppTInfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::GetIDsOfNames(
    [[maybe_unused]] REFIID riid,
    [[maybe_unused]] LPOLESTR* rgszNames,
    [[maybe_unused]] UINT cNames,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] DISPID* rgDispId) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITimeTrigger::Invoke(
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

STDMETHODIMP Stub_ITriggerCollection::get_Count(
    [[maybe_unused]] long* pCount) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITriggerCollection::get_Item(
    [[maybe_unused]] long index,
    [[maybe_unused]] ITrigger** ppTrigger) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITriggerCollection::get__NewEnum(
    [[maybe_unused]] IUnknown** ppEnum) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITriggerCollection::Create(
    [[maybe_unused]] TASK_TRIGGER_TYPE2 type,
    [[maybe_unused]] ITrigger** ppTrigger) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITriggerCollection::Remove(
    [[maybe_unused]] VARIANT index) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITriggerCollection::Clear() noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITriggerCollection::GetTypeInfoCount(
    [[maybe_unused]] UINT* pctinfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITriggerCollection::GetTypeInfo(
    [[maybe_unused]] UINT iTInfo,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] ITypeInfo** ppTInfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITriggerCollection::GetIDsOfNames(
    [[maybe_unused]] REFIID riid,
    [[maybe_unused]] LPOLESTR* rgszNames,
    [[maybe_unused]] UINT cNames,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] DISPID* rgDispId) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITriggerCollection::Invoke(
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