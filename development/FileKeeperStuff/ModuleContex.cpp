#include "StdAfx.h"
#include "ModuleContex.h"
#include <shellapi.h>

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
	if (m_nLockNum ==0)
	{
		return m_nLockNum;
	}
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
	if (m_nUseNum == 0)
	{
		return m_nUseNum;
	}
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

bool ModuleContex::AddCommandHandler(UINT nCmdID, CommandHandler pfnHandler)
{
	bool bRet = false;
	_ASSERT(nCmdID >= 0 && pfnHandler != NULL);
	CmdHandlerIterator iter = m_mapCommands.find(nCmdID);
	if (iter == m_mapCommands.end())
	{
		m_mapCommands.insert(make_pair(nCmdID, pfnHandler));
		bRet = true;
	}
	return bRet;
}
bool ModuleContex::RemoveCommandHandler(UINT nCmdID)
{
	CmdHandlerIterator iter = m_mapCommands.find(nCmdID);
	if (iter != m_mapCommands.end())
	{
		m_mapCommands.erase(iter);
	}
	return true;
}
ModuleContex::CommandHandler ModuleContex::GetCommandHandler(UINT nCmdID)
{
	CommandHandler pfnHandler = NULL;
	CmdHandlerIterator iter = m_mapCommands.find(nCmdID);
	if (iter != m_mapCommands.end())
	{
		pfnHandler = m_mapCommands[nCmdID];
	}
	return pfnHandler;
}

UINT ModuleContex::GetCommandHandlerSize() const
{
	return m_mapCommands.size();
}

bool ModuleContex::AddCommandString(UINT nCmdID, Std_String strVal)
{
	bool bRet = false;
	_ASSERT(nCmdID >= 0 && strVal != _T(""));
	CmdIDStringIterator iter = m_mapCmdString.find(nCmdID);
	if (iter == m_mapCmdString.end())
	{
		m_mapCmdString.insert(make_pair(nCmdID, strVal));
		bRet = true;
	}
	return bRet;
}
bool ModuleContex::RemoveCommandString(UINT nCmdID)
{
	CmdIDStringIterator iter = m_mapCmdString.find(nCmdID);
	if (iter != m_mapCmdString.end())
	{
		m_mapCmdString.erase(iter);
	}
	return true;
}
Std_String ModuleContex::GetCommandString(UINT nCmdID)
{
	Std_String strRet;
	CmdIDStringIterator iter = m_mapCmdString.find(nCmdID);
	if (iter != m_mapCmdString.end())
	{
		strRet = m_mapCmdString[nCmdID];
	}
	return strRet;
}

UINT ModuleContex::GetCommandStringSize() const
{
	return m_mapCmdString.size();
}

int ModuleContex::GetSelectedFiles(list<Std_String>& rgpFiles)
{
    rgpFiles.clear();

    if(!m_pDtObj) return -1;

    STGMEDIUM medium;
    FORMATETC fmte = {CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
    HRESULT hres = m_pDtObj->GetData(&fmte, &medium);
    if(FAILED(hres))
        return -1;
    
    int numFiles = DragQueryFile((HDROP)medium.hGlobal, (UINT)-1, NULL, 0);
    TCHAR szPath[MAX_PATH] = _T("");
    for(int i = 0; i < numFiles; i++)
    {
        DragQueryFile((HDROP)medium.hGlobal, i, szPath, sizeof(szPath));
        rgpFiles.push_back(szPath);
    }
    ::ReleaseStgMedium(&medium);

    return rgpFiles.size();
}