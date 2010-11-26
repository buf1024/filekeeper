#pragma once
#include "unknwn.h"

class FileKeeperFactory :
	public IClassFactory
{
public:
	FileKeeperFactory(void);
	~FileKeeperFactory(void);

	
public:
	//IClassFactory
	virtual /* [local] */ HRESULT STDMETHODCALLTYPE CreateInstance( 
		/* [unique][in] */ IUnknown *pUnkOuter,
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ void **ppvObject);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE LockServer( 
		/* [in] */ BOOL fLock);

	//IUnkown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
		/* [in] */
		REFIID riid,
		/* [iid_is][out] */
		void **ppvObject);

	virtual ULONG STDMETHODCALLTYPE AddRef( void);

	virtual ULONG STDMETHODCALLTYPE Release( void);

private:
	ULONG m_nRef;
};
