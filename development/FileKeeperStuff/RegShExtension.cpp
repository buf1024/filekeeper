#include "stdafx.h"
#include "RegShExtension.h"
#include "Reg.h"
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
using namespace lgc;

//====================================================================================
//ContexMenu Handler
HRESULT RegShExtension::RegCtxMenuHandler(Std_String strProgName, const CLSID& clsid)
{
	if (strProgName.empty()) return S_FALSE;

	TCHAR* pszBuf = NULL;	
	if (StringFromCLSID(clsid, &pszBuf) != S_OK)
	{
		//CLSID Not Right
		return S_FALSE;
	}
	Std_String strClsID = pszBuf;
	CoTaskMemFree(pszBuf);

	RegFactory *pFactory = RegFactory::GetInstPtr();
	RegNode* pNode = NULL;
	Std_String strKey;

	//HKEY_CLASSES_ROOT\*\shellex\ContextMenuHandlers
	strKey =  _T("*\\shellex\\ContextMenuHandlers\\");
	strKey.append(strProgName);
	pNode = pFactory->CreateRegNode(HKEY_CLASSES_ROOT, strKey, true);
	pNode->AddRegData(REG_SZ, _T(""), strClsID.c_str(), (strClsID.length() + 1)*sizeof(TCHAR));
	delete pNode;

	//HKEY_CLASSES_ROOT\Directory\Background\shellex\ContextMenuHandlers
	strKey =  _T("Directory\\Background\\shellex\\ContextMenuHandlers\\");
	strKey.append(strProgName);
	pNode = pFactory->CreateRegNode(HKEY_CLASSES_ROOT, strKey, true);
	pNode->AddRegData(REG_SZ, _T(""), strClsID.c_str(), (strClsID.length() + 1)*sizeof(TCHAR));
	delete pNode;

	//HKEY_CLASSES_ROOT\Directory\shellex\ContextMenuHandlers
	strKey =  _T("Directory\\shellex\\ContextMenuHandlers\\");
	strKey.append(strProgName);
	pNode = pFactory->CreateRegNode(HKEY_CLASSES_ROOT, strKey, true);
	pNode->AddRegData(REG_SZ, _T(""), strClsID.c_str(), (strClsID.length() + 1)*sizeof(TCHAR));
	delete pNode;

	//HKEY_CLASSES_ROOT\Drive\shellex\ContextMenuHandlers
	strKey =  _T("Drive\\shellex\\ContextMenuHandlers\\");
	strKey.append(strProgName);
	pNode = pFactory->CreateRegNode(HKEY_CLASSES_ROOT, strKey, true);
	pNode->AddRegData(REG_SZ, _T(""), strClsID.c_str(), (strClsID.length() + 1)*sizeof(TCHAR));
	delete pNode;

	//HKEY_CLASSES_ROOT\Folder\shellex\ContextMenuHandlers
	strKey =  _T("Folder\\shellex\\ContextMenuHandlers\\");
	strKey.append(strProgName);
	pNode = pFactory->CreateRegNode(HKEY_CLASSES_ROOT, strKey, true);
	pNode->AddRegData(REG_SZ, _T(""), strClsID.c_str(), (strClsID.length() + 1)*sizeof(TCHAR));
	delete pNode;
	
	//HKEY_CLASSES_ROOT\InternetShortcut\shellex\ContextMenuHandlers
	strKey =  _T("InternetShortcut\\shellex\\ContextMenuHandlers\\");
	strKey.append(strProgName);
	pNode = pFactory->CreateRegNode(HKEY_CLASSES_ROOT, strKey, true);
	pNode->AddRegData(REG_SZ, _T(""), strClsID.c_str(), (strClsID.length() + 1)*sizeof(TCHAR));
	delete pNode;

	//HKEY_CLASSES_ROOT\lnkfile\shellex\ContextMenuHandlers
	strKey =  _T("lnkfile\\shellex\\ContextMenuHandlers\\");
	strKey.append(strProgName);
	pNode = pFactory->CreateRegNode(HKEY_CLASSES_ROOT, strKey, true);
	pNode->AddRegData(REG_SZ, _T(""), strClsID.c_str(), (strClsID.length() + 1)*sizeof(TCHAR));
	delete pNode;

	RegFactory::ReleaseRC();

	return S_OK;
}
HRESULT RegShExtension::UnRegCtxMenuHandler(Std_String strProgName)
{
	if (strProgName.empty()) return S_FALSE;


	RegFactory *pFactory = RegFactory::GetInstPtr();
	RegNode* pNode = NULL;
	Std_String strKey;

	//HKEY_CLASSES_ROOT\*\shellex\ContextMenuHandlers
	strKey =  _T("*\\shellex\\ContextMenuHandlers\\");
	strKey.append(strProgName);
	pNode = pFactory->CreateRegNode(HKEY_CLASSES_ROOT, strKey, true);
	pNode->DeleteNode();
	delete pNode;

	//HKEY_CLASSES_ROOT\Directory\Background\shellex\ContextMenuHandlers
	strKey =  _T("Directory\\Background\\shellex\\ContextMenuHandlers\\");
	strKey.append(strProgName);
	pNode = pFactory->CreateRegNode(HKEY_CLASSES_ROOT, strKey, true);
	pNode->DeleteNode();
	delete pNode;

	//HKEY_CLASSES_ROOT\Directory\shellex\ContextMenuHandlers
	strKey =  _T("Directory\\shellex\\ContextMenuHandlers\\");
	strKey.append(strProgName);
	pNode = pFactory->CreateRegNode(HKEY_CLASSES_ROOT, strKey, true);
	pNode->DeleteNode();
	delete pNode;

	//HKEY_CLASSES_ROOT\Drive\shellex\ContextMenuHandlers
	strKey =  _T("Drive\\shellex\\ContextMenuHandlers\\");
	strKey.append(strProgName);
	pNode = pFactory->CreateRegNode(HKEY_CLASSES_ROOT, strKey, true);
	pNode->DeleteNode();
	delete pNode;

	//HKEY_CLASSES_ROOT\Folder\shellex\ContextMenuHandlers
	strKey =  _T("Folder\\shellex\\ContextMenuHandlers\\");
	strKey.append(strProgName);
	pNode = pFactory->CreateRegNode(HKEY_CLASSES_ROOT, strKey, true);
	pNode->DeleteNode();
	delete pNode;

	//HKEY_CLASSES_ROOT\InternetShortcut\shellex\ContextMenuHandlers
	strKey =  _T("InternetShortcut\\shellex\\ContextMenuHandlers\\");
	strKey.append(strProgName);
	pNode = pFactory->CreateRegNode(HKEY_CLASSES_ROOT, strKey, true);
	pNode->DeleteNode();
	delete pNode;

	//HKEY_CLASSES_ROOT\lnkfile\shellex\ContextMenuHandlers
	strKey =  _T("lnkfile\\shellex\\ContextMenuHandlers\\");
	strKey.append(strProgName);
	pNode = pFactory->CreateRegNode(HKEY_CLASSES_ROOT, strKey, true);
	pNode->DeleteNode();
	delete pNode;

	RegFactory::ReleaseRC();

	return S_OK;
}