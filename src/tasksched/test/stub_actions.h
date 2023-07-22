#pragma once

#include <windows.h>
#include <taskschd.h>

#include <wil/cppwinrt.h>

namespace wacpp::test
{

class Stub_IExecAction : public winrt::implements<Stub_IExecAction, IExecAction>
{
    // IExecAction

    STDMETHODIMP get_Path(
        BSTR* pPath) noexcept override;

    STDMETHODIMP put_Path(
        BSTR path) noexcept override;

    STDMETHODIMP get_Arguments(
        BSTR* pArgument) noexcept override;

    STDMETHODIMP put_Arguments(
        BSTR argument) noexcept override;

    STDMETHODIMP get_WorkingDirectory(
        BSTR* pWorkingDirectory) noexcept override;

    STDMETHODIMP put_WorkingDirectory(
        BSTR workingDirectory) noexcept override;

    // IAction

    STDMETHODIMP get_Id(
        BSTR* pId) noexcept override;

    STDMETHODIMP put_Id(
        BSTR Id) noexcept override;

    STDMETHODIMP get_Type(
        TASK_ACTION_TYPE* pType) noexcept override;

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

class Stub_IActionCollection : public winrt::implements<Stub_IActionCollection, IActionCollection>
{
public:
    // IActionCollection

    STDMETHODIMP get_Count(
        long* pCount) noexcept override;

    STDMETHODIMP get_Item(
        long index,
        IAction** ppAction) noexcept override;

    STDMETHODIMP get__NewEnum(
        IUnknown** ppEnum) noexcept override;

    STDMETHODIMP get_XmlText(
        BSTR* pText) noexcept override;

    STDMETHODIMP put_XmlText(
        BSTR text) noexcept override;

    STDMETHODIMP Create(
        TASK_ACTION_TYPE type,
        IAction** ppAction) noexcept override;

    STDMETHODIMP Remove(
        VARIANT index) noexcept override;

    STDMETHODIMP Clear() noexcept override;

    STDMETHODIMP get_Context(
        BSTR* pContext) noexcept override;

    STDMETHODIMP put_Context(
        BSTR context) noexcept override;

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