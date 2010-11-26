#include "StdAfx.h"
#include "ModuleContex.h"

ModuleContex::ModuleContex(void)
: m_hModule(NULL)
, m_nLockNum(0L)
, m_nUseNum(0L)
, m_pPidlFolder(NULL)
, m_pDtObj(NULL)
, m_hkeyProgID(NULL)
{
	
}

ModuleContex::~ModuleContex(void)
{
	if (m_pPidlFolder)
	{
		ILFree((LPITEMIDLIST)m_pPidlFolder);
	}
	if (m_pDtObj)
	{
		m_pDtObj->Release();
	}
	if (m_hkeyProgID)
	{
		RegCloseKey(m_hkeyProgID);
	}
			
}

HMODULE ModuleContex::GetModuleHandle()
{
	_ASSERT(m_hModule != NULL);
	return m_hModule;
}
VOID ModuleContex::SetModuleHandle(HMODULE hModule)
{
	m_hModule = hModule;
}
ULONG ModuleContex::GetLockNum()
{
	return m_nLockNum;
}
ULONG ModuleContex::GetUsageNum()
{
	return m_nUseNum;
}

ULONG ModuleContex::AddRefLockNum()
{
	m_nLockNum++;
	return m_nLockNum;
}
ULONG ModuleContex::ReleaseLockNum()
{
	m_nLockNum--;
	return m_nLockNum;
}

ULONG ModuleContex::AddRefUsageNum()
{
	m_nUseNum++;
	return m_nUseNum;
}
ULONG ModuleContex::ReleaseUsageNum()
{
	m_nUseNum--;
	return m_nUseNum;
}

PIDLIST_ABSOLUTE ModuleContex::GetPIDLFolder()
{
	return m_pPidlFolder;
}
void ModuleContex::SetPIDLFolder(PIDLIST_ABSOLUTE pidlFoder)
{
	m_pPidlFolder = pidlFoder;
}

IDataObject* ModuleContex::GetDataObject()
{
	return m_pDtObj;
}
void ModuleContex::SetDataObject(IDataObject* pObj)
{
	m_pDtObj = pObj;
}

HKEY ModuleContex::GetFolderHEY()
{
	return m_hkeyProgID;
}
void ModuleContex::SetFolderHEY(HKEY hKey)
{
	m_hkeyProgID = hKey;
}
