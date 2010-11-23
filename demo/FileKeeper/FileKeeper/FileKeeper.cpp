// FileKeeper.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "FileKeeper.h"
#include "log4cxx.h"
#include "APIHook.h"

#define WAIT_TIME 1000


typedef HANDLE (WINAPI* TheCreateFileFunc)(LPCTSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES,
										   DWORD, DWORD, HANDLE);

HINSTANCE g_hDllInst = NULL;
HINSTANCE g_hQQInst = NULL;

LoggerPtr gRootLogger(Logger::getLogger(_T("lgc.FileKeeper")));


HANDLE WINAPI MyCreateFile(
						   LPCTSTR lpFileName,
						   DWORD dwDesiredAccess,
						   DWORD dwShareMode,
						   LPSECURITY_ATTRIBUTES lpSecurityAttributes,
						   DWORD dwCreationDisposition,
						   DWORD dwFlagsAndAttributes,
						   HANDLE hTemplateFile
						   );

CAPIHook g_lpfnCreateFile("kernel32.dll", "CreateFileW", 
					   (PROC)MyCreateFile, TRUE);

HANDLE WINAPI MyCreateFile(
						   LPCTSTR lpFileName,
						   DWORD dwDesiredAccess,
						   DWORD dwShareMode,
						   LPSECURITY_ATTRIBUTES lpSecurityAttributes,
						   DWORD dwCreationDisposition,
						   DWORD dwFlagsAndAttributes,
						   HANDLE hTemplateFile
						 )
{
	TCHAR szPath[MAX_PATH] = _T("qq.exe:");
	lstrcat(szPath, lpFileName);
	LOG4CXX_INFO(gRootLogger, szPath);
	
	return ((TheCreateFileFunc)(PROC) g_lpfnCreateFile)(lpFileName, dwDesiredAccess, dwShareMode,
		lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}
//
//BOOL CALLBACK ReplaceModuleFun(HINSTANCE hInst, PSTR szModule, PROC lpfnOr, PROC lpfnNew)
//{
//	ULONG ulSize;
//	PIMAGE_IMPORT_DESCRIPTOR pImportDes = (PIMAGE_IMPORT_DESCRIPTOR)
//		ImageDirectoryEntryToData(hInst,
//		TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &ulSize);
//	if(!pImportDes) return FALSE;
//	for(; pImportDes->Name; pImportDes++){
//		PSTR pszName = (PSTR)((PBYTE)hInst + pImportDes->Name);
//		LOG4CXX_INFO(gRootLogger, pszName);
//		if(lstrcmpiA(szModule, pszName) == 0)
//		{
//			LOG4CXX_INFO(gRootLogger, _T("Module Found!!"));
//			break;
//		}
//	}
//	if(!pImportDes->Name)
//	{
//		return FALSE;
//	}
//
//	LOG4CXX_INFO(gRootLogger, _T("Original: ") << lpfnOr);
//	PIMAGE_THUNK_DATA pThunk = (PIMAGE_THUNK_DATA)((PBYTE)hInst + pImportDes->FirstThunk);
//	for(; pThunk->u1.Function; pThunk++){
//		PROC* ppfn = (PROC*)&pThunk->u1.Function;
//		LOG4CXX_INFO(gRootLogger, *ppfn);
//		if(*ppfn == lpfnOr){
//			LOG4CXX_INFO(gRootLogger, _T("Function Found!!"));
//			WriteProcessMemory(
//				GetCurrentProcess(),
//				ppfn, &lpfnNew, sizeof(lpfnNew), NULL);
//			return TRUE;
//		}
//	}
//	return FALSE;
//}
//
//

BOOL CALLBACK Initialize(HINSTANCE hInst)
{
	Sleep(WAIT_TIME);
	PropertyConfigurator::configure(_T("C:\\FileKeeper.properties"));
	LOG4CXX_INFO(gRootLogger, _T("Initialize..."));

    g_hDllInst = hInst;    
    g_hQQInst = GetModuleHandle(_T("qq.exe"));
    if(!g_hQQInst)
	{
		MessageBox(NULL, _T("Fail to find QQ instance, Start QQ first!"), _T("Error"), MB_ICONWARNING);
		return FALSE;    
	}


	CHAR szModule[] = "Kernel32.dll";
	HMODULE hModule = GetModuleHandle(_T("kernel32.dll"));
	LOG4CXX_INFO(gRootLogger, _T("HModule of Kernel32.dll: ") << (DWORD)hModule);
	////Replace CreateFile
//	g_lpfnCreateFile = (TheCreateFileFunc)GetProcAddress(hModule, "CreateFileW"); 
	//if(!ReplaceModuleFun(g_hQQInst, szModule, (PROC)g_lpfnCreateFile, (PROC)MyCreateFile))
	//{
	//    MessageBox(NULL, _T("Fail To Replace Kernel32.DLL CreateFileW API Function!"), _T("Error!!"), MB_ICONWARNING);
	//    return FALSE;
	//}

    return TRUE;
}


