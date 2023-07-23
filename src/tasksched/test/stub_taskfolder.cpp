#include "stub_taskfolder.h"

namespace wacpp::test
{

STDMETHODIMP Stub_ITaskFolder::get_Name(
    [[maybe_unused]] BSTR* pName) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskFolder::get_Path(
    [[maybe_unused]] BSTR* pPath) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskFolder::GetFolder(
    [[maybe_unused]] BSTR path,
    [[maybe_unused]] ITaskFolder** ppFolder) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskFolder::GetFolders(
    [[maybe_unused]] LONG flags,
    [[maybe_unused]] ITaskFolderCollection** ppFolders) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskFolder::CreateFolder(
    [[maybe_unused]] BSTR subFolderName,
    [[maybe_unused]] VARIANT sddl,
    [[maybe_unused]] ITaskFolder** ppFolder) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskFolder::DeleteFolder(
    [[maybe_unused]] BSTR subFolderName,
    [[maybe_unused]] LONG flags) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskFolder::GetTask(
    [[maybe_unused]] BSTR path,
    [[maybe_unused]] IRegisteredTask** ppTask) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskFolder::GetTasks(
    [[maybe_unused]] LONG flags,
    [[maybe_unused]] IRegisteredTaskCollection** ppTasks) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskFolder::DeleteTask(
    [[maybe_unused]] BSTR name,
    [[maybe_unused]] LONG flags) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskFolder::RegisterTask(
    [[maybe_unused]] BSTR path,
    [[maybe_unused]] BSTR xmlText,
    [[maybe_unused]] LONG flags,
    [[maybe_unused]] VARIANT userId,
    [[maybe_unused]] VARIANT password,
    [[maybe_unused]] TASK_LOGON_TYPE logonType,
    [[maybe_unused]] VARIANT sddl,
    [[maybe_unused]] IRegisteredTask** ppTask) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskFolder::RegisterTaskDefinition(
    [[maybe_unused]] BSTR path,
    [[maybe_unused]] ITaskDefinition* pDefinition,
    [[maybe_unused]] LONG flags,
    [[maybe_unused]] VARIANT userId,
    [[maybe_unused]] VARIANT password,
    [[maybe_unused]] TASK_LOGON_TYPE logonType,
    [[maybe_unused]] VARIANT sddl,
    [[maybe_unused]] IRegisteredTask** ppTask) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskFolder::GetSecurityDescriptor(
    [[maybe_unused]] LONG securityInformation,
    [[maybe_unused]] BSTR* pSddl) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskFolder::SetSecurityDescriptor(
    [[maybe_unused]] BSTR sddl,
    [[maybe_unused]] LONG flags) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskFolder::GetTypeInfoCount(
    [[maybe_unused]] UINT* pctinfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskFolder::GetTypeInfo(
    [[maybe_unused]] UINT iTInfo,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] ITypeInfo** ppTInfo) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskFolder::GetIDsOfNames(
    [[maybe_unused]] REFIID riid,
    [[maybe_unused]] LPOLESTR* rgszNames,
    [[maybe_unused]] UINT cNames,
    [[maybe_unused]] LCID lcid,
    [[maybe_unused]] DISPID* rgDispId) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP Stub_ITaskFolder::Invoke(
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