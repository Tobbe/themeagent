#include "URLDownloadCallback.h"

URLDownloadCallback::URLDownloadCallback()
{
}

HRESULT URLDownloadCallback::GetBindInfo(DWORD *grfBINDF, BINDINFO *pbindinfo)
{
	return E_NOTIMPL;
}

HRESULT URLDownloadCallback::GetPriority(LONG *pnPriority)
{
	return E_NOTIMPL;
}

HRESULT URLDownloadCallback::OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC *pformatetc, STGMEDIUM *pstgmed)
{
	return E_NOTIMPL;
}

HRESULT URLDownloadCallback::OnLowResource(DWORD dwReserved)
{
	return E_NOTIMPL;
}

HRESULT URLDownloadCallback::OnObjectAvailable(REFIID riid, IUnknown *punk)
{
	return E_NOTIMPL;
}

HRESULT URLDownloadCallback::OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)
{
	return S_OK;
}

HRESULT URLDownloadCallback::OnStartBinding(DWORD dwReserved, IBinding *pib)
{
	return E_NOTIMPL;
}

HRESULT URLDownloadCallback::OnStopBinding(HRESULT hresult, LPCWSTR szError)
{
	return E_NOTIMPL;
}

HRESULT URLDownloadCallback::QueryInterface(const IID &, void **)
{
	return E_NOTIMPL;
}

ULONG URLDownloadCallback::AddRef()
{
	return 0;
}

ULONG URLDownloadCallback::Release()
{
	return 0;
}
