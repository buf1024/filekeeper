//=============================================================================
/**
* @file	    ProcessStat.h
* @brief	Process Statistic Information Header
* @author	heidong
* @version	1.0
* @date		2010-10-10 19:08:35
*/
//=============================================================================

#pragma once
#include <Tlhelp32.h>
#include <list>

namespace lgc
{

	/** @class ModuleInfoItem
	* @brief Module information
	*/
	struct ModuleInfoItem
	{
		ModuleInfoItem();
		ModuleInfoItem(const ModuleInfoItem& other);
		~ModuleInfoItem();
		ModuleInfoItem& operator = (const ModuleInfoItem& other);

		DWORD th32ProcessID;	/**< The identifier of the process whose modules are to be examined. */
		BYTE* modBaseAddr;		/**< The base address of the module in the context of the owning process.*/
		DWORD modBaseSize;		/**< The size of the module, in bytes.*/
		HMODULE hModule;		/**< A handle to the module in the context of the owning process.*/
		TCHAR szModule[MAX_MODULE_NAME32 + 1];/**< The module name.*/
		TCHAR szExePath[MAX_PATH];/**< The module path.*/

	};


	/**@class ThreadInfoItem
	* @brief Thread information
	*/
	struct ThreadInfoItem
	{
		ThreadInfoItem();
		~ThreadInfoItem();
		DWORD th32ThreadID;			/**< The thread identifier, compatible with the thread identifier returned by the CreateProcess function.*/
		DWORD th32OwnerProcessID;	/**< The identifier of the process that created the thread.*/
		LONG tpBasePri;				/**< The base priority level assigned to the thread. */
	};


	/**@class ProcessInfoItem
	* @brief Process information
	*/
	struct ProcessInfoItem
	{
		ProcessInfoItem();
		ProcessInfoItem(const ProcessInfoItem& other);
		~ProcessInfoItem();
		ProcessInfoItem& operator = (const ProcessInfoItem& other);

		DWORD th32ProcessID;		/**< The process identifier.*/
		DWORD cntThreads;			/**< The number of execution threads started by the process.*/
		DWORD th32ParentProcessID;	/**< The identifier of the process that created this process (its parent process).*/
		LONG pcPriClassBase;		/**< The base priority of any threads created by this process.*/
		TCHAR szExeFile[MAX_PATH];	/**< The name of the executable file for the process.*/

		std::list<ModuleInfoItem*> rgpModules; /**< Modules information.*/
		std::list<ThreadInfoItem*> rgpThreads; /**< Thread information.*/

	};
	//for interal use
	//provide functor to use stl algorithm
	template <typename TheClass>
	class TransformUtil
	{
	public:
		TheClass* operator()(TheClass* pSrc);
	};

	/** @class ProcessStat
	* @brief Process Statistic.
	*
	* A class that capture all the running applications of the current computer.
	*/
	class ProcessStat
	{
	private:
		std::list<ProcessInfoItem*> m_rgpProcessInfo;

	public:
		/**@name Constructor&Destructor*/
		/**@{*/
		/**Constructor a ProcessStat object.*/
		ProcessStat(void);
		/**Destructor, release resources.*/
		~ProcessStat(void);
		/**@}*/

	public:
		/**@name Pratical operations*/
		/**@{*/
		/**Retry all the proccess information
		* @param rgpProcessInfo all available processes information will store in it if the operation is sucessfull.
		* @return TRUE if the operation is sucessfull, otherwise FALSE.
		*/
		BOOL GetCurrentProcSnashot(std::list<ProcessInfoItem*>& rgpProcessInfo);
		/**Get the specify  proccess information according the ProcessName
		* @param processInfoItem the process information will store in it if the operation is sucessfull.
		* @param szProcName the specify  proccess name
		* @return TRUE if the operation is sucessfull, otherwise FALSE.
		*/
		BOOL GetProcessInfo(PCTSTR szProcName, ProcessInfoItem& processInfoItem);
		/**Get the specify  proccess information according the PID
		* @param processInfoItem the process information will store in it if the operation is sucessfull.
		* @param dwPid the specify  proccess name
		* @return TRUE if the operation is sucessfull, otherwise FALSE.
		*/
		BOOL GetProcessInfo(DWORD dwPid, ProcessInfoItem& processInfoItem);
		/**Refresh the  proccesses informations.
		* @return TRUE if the operation is sucessfull, otherwise FALSE.
		*/
		BOOL Refresh();
		/**@}*/
	private:
		VOID ReleaseRC();
	};

}

