// FileKeeperStuff.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "FileKeeperStuff.h"
#include "ModuleContex.h"

FileKeeperStuff::FileKeeperStuff(void)
: m_nRef(0L)
{
	ModuleContex* pCtx = ModuleContex::GetInstPtr();
	pCtx->AddRefUsageNum();
}

FileKeeperStuff::~FileKeeperStuff(void)
{
}


//IShellExtInit
HRESULT FileKeeperStuff::Initialize( 
	/* [unique][in] */ 
	PCIDLIST_ABSOLUTE pidlFolder,
	/* [unique][in] */ 
	IDataObject *pdtobj,
	/* [unique][in] */ 
	HKEY hkeyProgID)
{
	ModuleContex* pCtx = ModuleContex::GetInstPtr();

	// If Initialize has already been called, release the old PIDL
	if (pCtx->GetPIDLFolder())
	{
		ILFree(pCtx->GetPIDLFolder());
		pCtx->SetPIDLFolder(NULL);
	}

	//Store the new PIDL.
	if(pidlFolder)
	{
		pCtx->SetPIDLFolder(ILClone(pidlFolder));
	}

	// If Initialize has already been called, release the old
	// IDataObject pointer.
	if (pCtx->GetDataObject())
	{ 
		pCtx->GetDataObject()->Release(); 
	}

	// If a data object pointer was passed in, save it and
	// extract the file name. 
	if (pdtobj) 
	{ 
		pCtx->SetDataObject(pdtobj);
		pdtobj->AddRef(); 
	}

	// Duplicate the registry handle. 
	if (hkeyProgID) 
	{
		HKEY hRegDup = NULL;
		RegOpenKeyEx(hkeyProgID, NULL, 0L, MAXIMUM_ALLOWED, &hRegDup); 
		pCtx->SetFolderHEY(hRegDup);
	}

	return S_OK;
}

//IContextMenu
HRESULT FileKeeperStuff::QueryContextMenu( 
	/* [in] */ 
	HMENU hmenu,
	/* [in] */ 
	UINT indexMenu,
	/* [in] */ 
	UINT idCmdFirst,
	/* [in] */ 
	UINT idCmdLast,
	/* [in] */ 
	UINT uFlags)
{
		MessageBox(NULL, _T("QueryContextMenu"), _T("Demo"), MB_OK);
	return S_OK;
}

HRESULT FileKeeperStuff::InvokeCommand( 
	/* [in] */ 
	CMINVOKECOMMANDINFO *pici)
{
		MessageBox(NULL, _T("InvokeCommand"), _T("Demo"), MB_OK);
	return S_OK;
}

HRESULT FileKeeperStuff::GetCommandString( 
	/* [in] */ 
	UINT_PTR idCmd,
	/* [in] */ 
	UINT uType,
	/* [in] */ 
	UINT *pReserved,
	/* [out] */ 
	LPSTR pszName,
	/* [in] */ 
	UINT cchMax)
{
		MessageBox(NULL, _T("GetCommandString"), _T("Demo"), MB_OK);
	return S_OK;
}

//IUnkown
HRESULT FileKeeperStuff::QueryInterface( 
	/* [in] */
	REFIID riid,
	/* [iid_is][out] */
	void **ppvObject)
{
	if (riid == IID_IUnknown)
	{
		*ppvObject = (IContextMenu*)this;
		((IContextMenu*)*ppvObject)->AddRef();
	}
	else if (riid == IID_IContextMenu)
	{
		*ppvObject = (IContextMenu*)this;
		((IContextMenu*)*ppvObject)->AddRef();
	}
	else if(riid == IID_IShellExtInit)
	{
		*ppvObject = (IShellExtInit*)this;
		((IShellExtInit*)*ppvObject)->AddRef();
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}


	return S_OK;
}

ULONG FileKeeperStuff::AddRef( void)
{
	m_nRef++;
	return m_nRef;
}

ULONG FileKeeperStuff::Release( void)
{
	m_nRef--;
	if (m_nRef == 0L)
	{
		//Suicide
		delete this;
		ModuleContex* pCtx = ModuleContex::GetInstPtr();
		pCtx->ReleaseLockNum();

	}
	return m_nRef;
}