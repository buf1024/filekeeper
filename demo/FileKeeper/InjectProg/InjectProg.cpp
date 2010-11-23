// InjectProg.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "InjectProg.h"
#include <shlwapi.h>
#include "ProcessStat.h"

#pragma comment(lib, "shlwapi.lib")

#define WAIT_TIME 100



lgc::ProcessInfoItem g_QQInfo;
TCHAR g_szDllPath[MAX_PATH] = _T("");

HANDLE CALLBACK InjectDll()
{
	HANDLE hProcess = NULL;
	HANDLE hThread = NULL;
	PTSTR szRemote = NULL;

	__try{
		hProcess = OpenProcess(
			PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE,
			FALSE, g_QQInfo.th32ProcessID);
		if(!hProcess) __leave;
		int nSize = sizeof(TCHAR)*(lstrlen(g_szDllPath)+1);
		szRemote = (PTSTR)VirtualAllocEx(hProcess, NULL,
			nSize, MEM_COMMIT, PAGE_READWRITE);
		if(!szRemote) __leave;
		BOOL bRes = WriteProcessMemory(hProcess, szRemote, (LPVOID)g_szDllPath,
			nSize, NULL);
		if(!bRes) __leave;
		PTHREAD_START_ROUTINE pfn = (PTHREAD_START_ROUTINE)GetProcAddress(
			GetModuleHandle(_T("kernel32.dll")), "LoadLibraryW");
		if(!pfn) __leave;
		//确保线程顺利启动
		Sleep(WAIT_TIME);
		hThread = CreateRemoteThread(hProcess, NULL, 0, pfn, szRemote, 0, NULL);
		if(!hThread) __leave;
	}__finally{
		//  if(szRemote) VirtualFreeEx(hProcess, szRemote, 0, MEM_RELEASE);
		if(hProcess)
			CloseHandle(hProcess);
	}

	return hThread;
}


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	TCHAR szTemp[MAX_PATH] = _T("");
	GetCurrentDirectory(MAX_PATH, szTemp);
	lstrcat(szTemp, _T("\\FileKeeper.dll"));

	if (!PathFileExists(szTemp))
	{
		MessageBox(NULL, _T("Dll NotFould"), _T("Error"), MB_ICONWARNING);
		return -1;
	}

	lstrcpy(g_szDllPath, szTemp);

	lgc::ProcessStat stat;			
	BOOL bFound = stat.GetProcessInfo(_T("QQ.exe"), g_QQInfo);
	if (!bFound)
	{
		MessageBox(NULL, _T("QQ.exe not fould"), _T("Error"), MB_ICONWARNING);
		return -1;
	}

	HANDLE hThread = InjectDll();
	if(!hThread){
		MessageBox(NULL, _T("Fail To InjectDll!"), _T("Not OK!!"), MB_ICONWARNING);
	}else{

		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
	}

	return 0;
}

