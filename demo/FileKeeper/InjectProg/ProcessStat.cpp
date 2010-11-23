//=============================================================================
/**
* @file	    ProcessStat.cpp
* @brief	Process Statistic Information Implementation
* @author	heidong
* @version	1.0
* @date		2010-10-10 19:09:16
*/
//=============================================================================
#include "StdAfx.h"
#include "ProcessStat.h"
#include <strsafe.h>
#include <exception>
#include <algorithm>

using namespace lgc;

ModuleInfoItem::ModuleInfoItem()
: th32ProcessID(0L)
, modBaseAddr(NULL)
, modBaseSize(0L)
, hModule(NULL)
{
	memset(szModule, 0, (MAX_MODULE_NAME32 + 1)*sizeof(TCHAR));
	memset(szExePath, 0, MAX_PATH*sizeof(TCHAR));

}
ModuleInfoItem::ModuleInfoItem(const ModuleInfoItem& other)
{
	th32ProcessID = other.th32ProcessID;
	modBaseAddr = other.modBaseAddr;
	modBaseSize = other.modBaseSize;
	hModule = other.hModule;

	StringCchCopy(szModule, MAX_MODULE_NAME32 + 1, other.szModule);
	StringCchCopy(szExePath, MAX_PATH, other.szExePath);
}
ModuleInfoItem::~ModuleInfoItem()
{

}
ModuleInfoItem& ModuleInfoItem::operator = (const ModuleInfoItem& other)
{
	th32ProcessID = other.th32ProcessID;
	modBaseAddr = other.modBaseAddr;
	modBaseSize = other.modBaseSize;
	hModule = other.hModule;

	StringCchCopy(szModule, MAX_MODULE_NAME32 + 1, other.szModule);
	StringCchCopy(szExePath, MAX_PATH, other.szExePath);

	return *this;
}

ThreadInfoItem::ThreadInfoItem()
{

}
ThreadInfoItem::~ThreadInfoItem()
{

}

ProcessInfoItem::ProcessInfoItem()
: th32ProcessID(0L)
, cntThreads(0L)
, th32ParentProcessID(0L)
, pcPriClassBase(0L)
{
	memset(szExeFile, 0, MAX_PATH*sizeof(TCHAR));
	rgpModules.clear();
	rgpThreads.clear();
}
ProcessInfoItem::ProcessInfoItem(const ProcessInfoItem& other)
{
	th32ProcessID = other.th32ProcessID;
	cntThreads = other.cntThreads;
	th32ParentProcessID = other.th32ParentProcessID;
	pcPriClassBase = other.pcPriClassBase;
	StringCchCopy(szExeFile, MAX_PATH, other.szExeFile);
	std::transform(other.rgpModules.begin(), other.rgpModules.end(),
		std::back_inserter(rgpModules), TransformUtil<ModuleInfoItem>());
	std::transform(other.rgpThreads.begin(), other.rgpThreads.end(),
		std::back_inserter(rgpThreads), TransformUtil<ThreadInfoItem>());
}
ProcessInfoItem::~ProcessInfoItem()
{
	for(std::list<ModuleInfoItem*>::iterator mIter = rgpModules.begin();
		mIter != rgpModules.end(); ++mIter)
	{
		delete *mIter;
	}
	rgpModules.clear();
	for(std::list<ThreadInfoItem*>::iterator tIter = rgpThreads.begin();
		tIter != rgpThreads.end(); ++tIter)
	{
		delete *tIter;
	}
	rgpThreads.clear();
}
ProcessInfoItem& ProcessInfoItem::operator = (const ProcessInfoItem& other)
{
	th32ProcessID = other.th32ProcessID;
	cntThreads = other.cntThreads;
	th32ParentProcessID = other.th32ParentProcessID;
	pcPriClassBase = other.pcPriClassBase;
	StringCchCopy(szExeFile, MAX_PATH, other.szExeFile);
	std::transform(other.rgpModules.begin(), other.rgpModules.end(),
		std::back_inserter(rgpModules), TransformUtil<ModuleInfoItem>());
	std::transform(other.rgpThreads.begin(), other.rgpThreads.end(),
		std::back_inserter(rgpThreads), TransformUtil<ThreadInfoItem>());

	return *this;
}

template <typename TheClass>
TheClass* TransformUtil<TheClass>::operator()(TheClass* pSrc)
{
	return new TheClass(*pSrc);
}

ProcessStat::ProcessStat()
{
	Refresh();
}
ProcessStat::~ProcessStat()
{
	ReleaseRC();
}

BOOL ProcessStat::GetCurrentProcSnashot(std::list<ProcessInfoItem*>& rgpProcessInfo)
{  
	BOOL bRet = FALSE;
	if (m_rgpProcessInfo.size() > 0)
	{
		std::copy(m_rgpProcessInfo.begin(),
		m_rgpProcessInfo.end(), std::back_inserter(rgpProcessInfo));
		bRet = TRUE;
	}
    return bRet;

}

BOOL ProcessStat::GetProcessInfo(PCTSTR szProcName, ProcessInfoItem& processInfoItem)
{
	BOOL bRet = FALSE;
	for(std::list<ProcessInfoItem*>::iterator iter = m_rgpProcessInfo.begin();
		iter != m_rgpProcessInfo.end(); ++iter)
	{
		if (lstrcmpi((*iter)->szExeFile, szProcName) == 0)
		{
			//processInfoItem.cntThreads = (*iter)->cntThreads;
			//processInfoItem.pcPriClassBase = (*iter)->pcPriClassBase;
			//processInfoItem.th32ParentProcessID = (*iter)->th32ParentProcessID;
			//processInfoItem.th32ProcessID = (*iter)->th32ProcessID;
			//StringCchCopy(processInfoItem.szExeFile, MAX_PATH, (*iter)->szExeFile);
			//std::copy((*iter)->rgpModules.begin(), (*iter)->rgpModules.end(), std::back_inserter(processInfoItem.rgpModules));
			//std::copy((*iter)->rgpThreads.begin(), (*iter)->rgpThreads.end(), std::back_inserter(processInfoItem.rgpThreads));
			processInfoItem = *(*iter);
			bRet = TRUE;
			break;			
		}
		
	}
	return bRet;
}

BOOL ProcessStat::GetProcessInfo(DWORD dwPid, ProcessInfoItem& processInfoItem)
{

	BOOL bRet = FALSE;
	for(std::list<ProcessInfoItem*>::iterator iter = m_rgpProcessInfo.begin();
		iter != m_rgpProcessInfo.end(); ++iter)
	{
		if ((*iter)->th32ProcessID == dwPid)
		{
			//processInfoItem.cntThreads = (*iter)->cntThreads;
			//processInfoItem.pcPriClassBase = (*iter)->pcPriClassBase;
			//processInfoItem.th32ParentProcessID = (*iter)->th32ParentProcessID;
			//processInfoItem.th32ProcessID = (*iter)->th32ProcessID;
			//StringCchCopy(processInfoItem.szExeFile, MAX_PATH, (*iter)->szExeFile);
			//std::copy((*iter)->rgpModules.begin(), (*iter)->rgpModules.end(), std::back_inserter(processInfoItem.rgpModules));
			//std::copy((*iter)->rgpThreads.begin(), (*iter)->rgpThreads.end(), std::back_inserter(processInfoItem.rgpThreads));
			processInfoItem = *(*iter);
			bRet = TRUE;
			break;			
		}

	}
	return bRet;
}



BOOL ProcessStat::Refresh()
{
	HANDLE hSnapshot = INVALID_HANDLE_VALUE;
	BOOL nRet = FALSE;
	BOOL bFunRet = TRUE;
	HANDLE hModule = INVALID_HANDLE_VALUE;

	hSnapshot = CreateToolhelp32Snapshot(
		TH32CS_SNAPPROCESS | TH32CS_SNAPTHREAD, 0);
	ReleaseRC();

	//__try
	try
	{		
		PROCESSENTRY32 pe = {sizeof(pe)};
		nRet = Process32First(hSnapshot, &pe);
		//if(nRet == ERROR_NO_MORE_FILES) __leave;
		if(nRet == ERROR_NO_MORE_FILES) throw std::exception();
		do{
			ProcessInfoItem* pItem = new ProcessInfoItem;
			//Process
			pItem->cntThreads = pe.cntThreads;
			pItem->pcPriClassBase = pe.pcPriClassBase;
			pItem->th32ParentProcessID = pe.th32ParentProcessID;
			pItem->th32ProcessID = pe.th32ProcessID;
			StringCchCopy(pItem->szExeFile, MAX_PATH, pe.szExeFile);
			//Thread
			THREADENTRY32 te = {sizeof(te)};
			nRet = Thread32First(hSnapshot, &te);
			//if(nRet == ERROR_NO_MORE_FILES) __leave;
			if(nRet == ERROR_NO_MORE_FILES) throw std::exception();
			do{
				ThreadInfoItem* pThreadItem = new ThreadInfoItem;
				pThreadItem->th32OwnerProcessID = te.th32OwnerProcessID;
				pThreadItem->th32ThreadID = te.th32ThreadID;
				pThreadItem->tpBasePri = te.tpBasePri;

				pItem->rgpThreads.push_back(pThreadItem);

				nRet = Thread32Next(hSnapshot, &te);
				//if(nRet == ERROR_NO_MORE_FILES) __leave;
				if(nRet == ERROR_NO_MORE_FILES) throw std::exception();
			}while(nRet);

			//Module
			hModule = CreateToolhelp32Snapshot(
				TH32CS_SNAPMODULE, pe.th32ProcessID);
			//if (hModule == INVALID_HANDLE_VALUE)__leave;
			MODULEENTRY32 me = {sizeof(me)};
			nRet = Module32First(hModule, &me);
			//if(nRet == ERROR_NO_MORE_FILES) __leave;
			do{
				ModuleInfoItem* pModuleItem = new ModuleInfoItem;
				pModuleItem->th32ProcessID = me.th32ProcessID;
				pModuleItem->modBaseAddr = me.modBaseAddr;
				pModuleItem->hModule = me.hModule;
				pModuleItem->modBaseSize = me.modBaseSize;
				StringCchCopy(pModuleItem->szModule, MAX_MODULE_NAME32 + 1, me.szModule);
				StringCchCopy(pModuleItem->szExePath, MAX_PATH, me.szExePath);

				pItem->rgpModules.push_back(pModuleItem);

				nRet = Module32Next(hModule, &me);
				//if(nRet == ERROR_NO_MORE_FILES) __leave;
				if(nRet == ERROR_NO_MORE_FILES) throw std::exception();
			}while(nRet);

			m_rgpProcessInfo.push_back(pItem);
			nRet = Process32Next(hSnapshot, &pe);
			//if(nRet == ERROR_NO_MORE_FILES) __leave;
			if(nRet == ERROR_NO_MORE_FILES) throw std::exception();
		}while(nRet);
	}
	//__finally
	catch(...)
	{
	//	if (AbnormalTermination())
	//	{
	//		m_dwError = GetLastError();

	//	}
		//if (hSnapshot != INVALID_HANDLE_VALUE)
		//{
		//	CloseHandle(hSnapshot);

		//}
		//if (hModule != INVALID_HANDLE_VALUE)
		//{
		//	CloseHandle(hModule);
		//}
		bFunRet = FALSE;
	}
	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hSnapshot);

	}
	if (hModule != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hModule);
	}
	return bFunRet;
}

VOID ProcessStat::ReleaseRC()
{
	for(std::list<ProcessInfoItem*>::iterator pIter = m_rgpProcessInfo.begin();
		pIter != m_rgpProcessInfo.end(); ++pIter)
	{
		//for(std::list<ModuleInfoItem*>::iterator mIter = (*pIter)->rgpModules.begin();
		//	mIter != (*pIter)->rgpModules.end(); ++mIter)
		//{
		//	delete *mIter;
		//}
		//(*pIter)->rgpModules.clear();
		//for(std::list<ThreadInfoItem*>::iterator tIter = (*pIter)->rgpThreads.begin();
		//	tIter != (*pIter)->rgpThreads.end(); ++tIter)
		//{
		//	delete *tIter;
		//}
		//(*pIter)->rgpThreads.clear();
		delete *pIter;
	}
	m_rgpProcessInfo.clear();
}