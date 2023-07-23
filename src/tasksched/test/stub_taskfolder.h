#pragma once

#include <windows.h>
#include <taskschd.h>

#include <wil/cppwinrt.h>

namespace wacpp::test
{

class Stub_ITaskFolder : public winrt::implements<Stub_ITaskFolder, ITaskFolder>
{
public:
    // ITaskFolder

    STDMETHODIMP get_Name(
        BSTR* pName) noexcept override;

    STDMETHODIMP get_Path(
        BSTR* pPath) noexcept override;

    STDMETHODIMP GetFolder(
        BSTR path,
        ITaskFolder** ppFolder) noexcept override;

    STDMETHODIMP GetFolders(
        LONG flags,
        ITaskFolderCollection** ppFolders) noexcept override;

    STDMETHODIMP CreateFolder(
        BSTR subFolderName,
        VARIANT sddl,
        ITaskFolder** ppFolder) noexcept override;

    STDMETHODIMP DeleteFolder(
        BSTR subFolderName,
        LONG flags) noexcept override;

    STDMETHODIMP GetTask(
        BSTR path,
        IRegisteredTask** ppTask) noexcept override;

    STDMETHODIMP GetTasks(
        LONG flags,
        IRegisteredTaskCollection** ppTasks) noexcept override;

    STDMETHODIMP DeleteTask(
        BSTR name,
        LONG flags) noexcept override;

    STDMETHODIMP RegisterTask(
        BSTR path,
        BSTR xmlText,
        LONG flags,
        VARIANT userId,
        VARIANT password,
        TASK_LOGON_TYPE logonType,
        VARIANT sddl,
        IRegisteredTask** ppTask) noexcept override;

    STDMETHODIMP RegisterTaskDefinition(
        BSTR path,
        ITaskDefinition* pDefinition,
        LONG flags,
        VARIANT userId,
        VARIANT password,
        TASK_LOGON_TYPE logonType,
        VARIANT sddl,
        IRegisteredTask** ppTask) noexcept override;

    STDMETHODIMP GetSecurityDescriptor(
        LONG securityInformation,
        BSTR* pSddl) noexcept override;

    STDMETHODIMP SetSecurityDescriptor(
        BSTR sddl,
        LONG flags) noexcept override;

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