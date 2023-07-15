#pragma once

#include <windows.h>
#include <taskschd.h>

#include <wil/cppwinrt.h>

namespace wacpp::test
{

class Stub_IRegistrationInfo : public winrt::implements<Stub_IRegistrationInfo, IRegistrationInfo>
{
public:
    // IRegistrationInfo

    STDMETHODIMP get_Description(
        BSTR* pDescription) noexcept override;

    STDMETHODIMP put_Description(
        BSTR description) noexcept override;

    STDMETHODIMP get_Author(
        BSTR* pAuthor) noexcept override;

    STDMETHODIMP put_Author(
        BSTR author) noexcept override;

    STDMETHODIMP get_Version(
        BSTR* pVersion) noexcept override;

    STDMETHODIMP put_Version(
        BSTR version) noexcept override;

    STDMETHODIMP get_Date(
        BSTR* pDate) noexcept override;

    STDMETHODIMP put_Date(
        BSTR date) noexcept override;

    STDMETHODIMP get_Documentation(
        BSTR* pDocumentation) noexcept override;

    STDMETHODIMP put_Documentation(
        BSTR documentation) noexcept override;

    STDMETHODIMP get_XmlText(
        BSTR* pText) noexcept override;

    STDMETHODIMP put_XmlText(
        BSTR text) noexcept override;

    STDMETHODIMP get_URI(
        BSTR* pUri) noexcept override;

    STDMETHODIMP put_URI(
        BSTR uri) noexcept override;

    STDMETHODIMP get_SecurityDescriptor(
        VARIANT* pSddl) noexcept override;

    STDMETHODIMP put_SecurityDescriptor(
        VARIANT sddl) noexcept override;

    STDMETHODIMP get_Source(
        BSTR* pSource) noexcept override;

    STDMETHODIMP put_Source(
        BSTR source) noexcept override;

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