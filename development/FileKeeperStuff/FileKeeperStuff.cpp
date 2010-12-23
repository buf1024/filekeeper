// FileKeeperStuff.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "FileKeeperStuff.h"
#include "ModuleContex.h"

#include "Resource.h"

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
		ULONG uRef = pCtx->GetDataObject()->Release(); 
		if (uRef == 0)
		{
			pCtx->SetDataObject(NULL);
		}
	}

	// If a data object pointer was passed in, save it and
	// extract the file name. 
	pCtx->SetDataObject(pdtobj);
	if (pdtobj) 
	{ 
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
	if (!(uFlags & CMF_DEFAULTONLY))
	{
		ModuleContex* pCtx = ModuleContex::GetInstPtr();
		HMODULE hInst = pCtx->GetModuleHandle();

		int nCmdID = idCmdFirst;
		TCHAR szBuf[MAX_PATH] = _T("");
		int nLen = 0;
		int nSubItemIndex = 0;

		HMENU hFKMenu = CreatePopupMenu();

		MENUITEMINFO mii = {sizeof(mii)};	

		nLen = LoadString(hInst, IDS_STRING_ABOUT, szBuf, MAX_PATH) + 1;
		mii.fMask = MIIM_STRING | MIIM_ID; //MIIM_BITMAP
		mii.wID = nCmdID++;
		mii.dwTypeData = szBuf;
		mii.cch = nLen;
		InsertMenuItem(hFKMenu, nSubItemIndex, TRUE, &mii);
		LoadString(hInst, IDS_STRING_ABOUT_HS, szBuf, MAX_PATH);
		pCtx->AddCommandString(nSubItemIndex, szBuf);
		pCtx->AddCommandHandler(nSubItemIndex, &FileKeeperStuff::OnAbout);
		nSubItemIndex++;
		

		memset(&mii, 0, sizeof(mii));
		mii.cbSize = sizeof(mii);
		nLen = LoadString(hInst, IDS_STRING_FILEKEEPER, szBuf, MAX_PATH) + 1;
		mii.fMask = MIIM_SUBMENU | MIIM_STRING | MIIM_ID;
		mii.hSubMenu = hFKMenu;
		mii.wID = nCmdID++;
		mii.dwTypeData = szBuf;
		mii.cch = nLen;
		InsertMenuItem(hmenu, indexMenu, TRUE, &mii);

		return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(nCmdID - idCmdFirst));
	}

	return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(0));


}

HRESULT FileKeeperStuff::InvokeCommand( 
	/* [in] */ 
	CMINVOKECOMMANDINFO *pici)
{
	if (0 != HIWORD( pici->lpVerb))
		return E_INVALIDARG;
	
	ModuleContex* pCtx = ModuleContex::GetInstPtr();
	
	ModuleContex::CommandHandler lpFunc = pCtx->GetCommandHandler(LOWORD(pici->lpVerb));
	if (lpFunc != NULL)
	{
		(this->*lpFunc)();
		return S_OK;
	}
	return E_INVALIDARG;
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
	ModuleContex* pCtx = ModuleContex::GetInstPtr();

	if (idCmd >= pCtx->GetCommandStringSize())
		return E_INVALIDARG;

	if ( uType & GCS_HELPTEXT )
	{
		Std_String strVal = pCtx->GetCommandString(idCmd);
		if (uType & GCS_UNICODE)
		{
#ifdef _UNICODE
			lstrcpynW((LPWSTR)pszName, strVal.c_str(), cchMax);
#else
			wchar_t szBuf[MAX_PATH] = L"";
			mbstowcs(szBuf, strVal.c_str(), strVal.size() + 1);
			lstrcpynW((LPWSTR)pszName, szBuf, cchMax);
#endif
		}
		else
		{
#ifdef _UNICODE
			char szBuf[MAX_PATH] = "";
			wcstombs(szBuf, strVal.c_str(), strVal.size() + 1);
			lstrcpynA(pszName, szBuf, cchMax);
#else
			lstrcpynA(pszName, strVal.c_str(), cchMax);
#endif
			
		}

		return S_OK;
	}

	return E_INVALIDARG;
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







//Menu Handler
void FileKeeperStuff::OnAbout()
{
    ModuleContex* pCtx = ModuleContex::GetInstPtr();
    list<Std_String> rgpFiles;
    int nCount = pCtx->GetSelectedFiles(rgpFiles);
    if (nCount > 0)
    {
        Std_String strDisp = _T("Selected Files:\r\n");
        for(list<Std_String>::iterator iter = rgpFiles.begin(); iter != rgpFiles.end(); ++iter)
        {
            strDisp += *iter;
            strDisp += _T("\r\n");
        }
        MessageBox(NULL, strDisp.c_str(), _T("OnAbout"), MB_OK);
    }
    else
    {
	    MessageBox(NULL, _T("OnAbout"), _T("About"), MB_OK);
    }
}
void FileKeeperStuff::OnSetting()
{
	MessageBox(NULL, _T("OnSetting"), _T("Setting"), MB_OK);
}





