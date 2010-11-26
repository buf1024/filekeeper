#pragma once

#include "Singleton.h"
#include <ShTypes.h>
#include <ObjIdl.h>
#include <ShlObj.h>
#include <stl.h>

#include "FileKeeperStuff.h"

using namespace lgc;

class ModuleContex : public Singleton<ModuleContex>
{
public:
	typedef void (FileKeeperStuff::* CommandHandler)();
	typedef map<UINT, Std_String>::iterator CmdIDStringIterator;	
	typedef map<UINT, CommandHandler>::iterator CmdHandlerIterator;

public:
	ModuleContex(void);
	~ModuleContex(void);

public:
	HMODULE STDMETHODCALLTYPE GetModuleHandle();
	VOID STDMETHODCALLTYPE SetModuleHandle(HMODULE hModule);
	ULONG STDMETHODCALLTYPE GetLockNum();
	ULONG STDMETHODCALLTYPE GetUsageNum();

	ULONG STDMETHODCALLTYPE AddRefLockNum();
	ULONG STDMETHODCALLTYPE ReleaseLockNum();

	ULONG STDMETHODCALLTYPE AddRefUsageNum();
	ULONG STDMETHODCALLTYPE ReleaseUsageNum();


	PIDLIST_ABSOLUTE GetPIDLFolder();
	void SetPIDLFolder(PIDLIST_ABSOLUTE pidlFoder);

	IDataObject* GetDataObject();
	void SetDataObject(IDataObject* pObj);

	HKEY GetFolderHEY();
	void SetFolderHEY(HKEY hKey);

	bool AddCommandHandler(UINT nCmdID, CommandHandler pfnHandler);
	bool RemoveCommandHandler(UINT nCmdID);
	ModuleContex::CommandHandler GetCommandHandler(UINT nCmdID);
	UINT GetCommandHandlerSize() const;

	bool AddCommandString(UINT nCmdID, Std_String strVal);
	bool RemoveCommandString(UINT nCmdID);
	Std_String GetCommandString(UINT nCmdID);
	UINT GetCommandStringSize() const;

private:
	HMODULE m_hModule;
	ULONG m_nLockNum;
	ULONG m_nUseNum;

	//Context Initialize Data
	PIDLIST_ABSOLUTE m_pPidlFolder;
	IDataObject *m_pDtObj;
	HKEY m_hkeyProgID;

	//Menu Context
	map<UINT, Std_String> m_mapCmdString;
	map<UINT, CommandHandler> m_mapCommands;
};
