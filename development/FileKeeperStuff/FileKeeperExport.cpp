#include "stdafx.h"
#include "clsid.h"
#include "ComRegSrv.h"
#include "RegShExtension.h"
#include "ModuleContex.h"
#include "FileKeeperFactory.h"

using namespace lgc;


STDAPI DllGetClassObject(
						 REFCLSID rclsid,
						 REFIID riid,
						 LPVOID * ppv
						 )
{

	if (rclsid == CLSID_FileKeeperStuff)
	{		
		FileKeeperFactory* pFactory = new FileKeeperFactory;
		return pFactory->QueryInterface(riid, ppv);
	}
	return CLASS_E_CLASSNOTAVAILABLE;
	
}

STDAPI DllCanUnloadNow(void)
{
	ModuleContex* pCtx = ModuleContex::GetInstPtr();
	if(pCtx->GetLockNum() == 0 && pCtx->GetUsageNum() == 0) return S_OK;
	return S_FALSE;
}

STDAPI DllRegisterServer(void)
{
	HRESULT hRet = S_FALSE;
	TCHAR szFileName[MAX_PATH] = _T("");
	ModuleContex* pCtx = ModuleContex::GetInstPtr();
	if(GetModuleFileName(pCtx->GetModuleHandle(), szFileName, MAX_PATH))
	{
		ComRegSrv* pCom = ComRegSrv::GetInstPtr();
		RegShExtension* pEx = RegShExtension::GetInstPtr();

		hRet = pCom->RegisterServer(CLSID_FileKeeperStuff, szFileName, _T("Apartment"),
			_T("FileKeeper.ProgID"), _T("FileKeeper Shell Extension"));
		if (hRet == S_OK)
		{
			hRet = pEx->RegCtxMenuHandler(_T("FileKeeper"), CLSID_FileKeeperStuff);
		}

		RegShExtension::ReleaseRC();
		ComRegSrv::ReleaseRC();
	}
	return hRet;
}

STDAPI DllUnregisterServer(void)
{
	HRESULT hRet = S_FALSE;

	ComRegSrv* pCom = ComRegSrv::GetInstPtr();
	RegShExtension* pEx = RegShExtension::GetInstPtr();

	hRet = pCom->UnregisterServer(CLSID_FileKeeperStuff, _T("FileKeeper.ProgID"));
	if (hRet == S_OK)
	{
		hRet = pEx->UnRegCtxMenuHandler(_T("FileKeeper"));
	}

	RegShExtension::ReleaseRC();
	ComRegSrv::ReleaseRC();

	return hRet;
}

