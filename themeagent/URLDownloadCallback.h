#ifndef URL_DOWNLOAD_CALLBACK_H_
#define URL_DOWNLOAD_CALLBACK_H_

#include <windows.h>

class URLDownloadCallback : public IBindStatusCallback
{
private:
	int timeout;
public:
	URLDownloadCallback();
	STDMETHOD(GetBindInfo)(DWORD *grfBINDF, BINDINFO *pbindinfo);
	STDMETHOD(GetPriority)(LONG *pnPriority);
	STDMETHOD(OnDataAvailable)(DWORD grfBSCF, DWORD dwSize, FORMATETC *pformatetc, STGMEDIUM *pstgmed);
	STDMETHOD(OnLowResource)(DWORD dwReserved);
	STDMETHOD(OnObjectAvailable)(REFIID riid, IUnknown *punk);
	STDMETHOD(OnProgress)(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText);
	STDMETHOD(OnStartBinding)(DWORD dwReserved, IBinding *pib);
	STDMETHOD(OnStopBinding)(HRESULT hresult, LPCWSTR szError);
	STDMETHOD(QueryInterface)(const IID &, void **);
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();
};

#endif