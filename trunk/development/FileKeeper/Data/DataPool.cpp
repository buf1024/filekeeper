//=============================================================================
/**
* @file	    DataPool.cpp
* @brief	DataPool implementation file
* @author	heidong
* @version	1.0
* @date		2010-12-13 20:51:41
*/
//=============================================================================
#include "StdAfx.h"
#include "DataPool.h"
#include "DatabaseSchema.h"
#include "..\Util\Util.h"

DataPool::DataPool(void)
: m_pDB(NULL)
{
}

DataPool::~DataPool(void)
{
	if (m_pDB)
	{
		sqlite3_close(m_pDB);
		m_pDB = NULL;
	}
}

bool DataPool::Empty()
{
	return false;
}

bool DataPool::Init(Std_String strFile)
{
	//Not allow memory database
	if (!strFile.empty())
	{
		string strAnsiFile = Util::GetStringFromWString(strFile);
		sqlite3_open(strAnsiFile.c_str(), &m_pDB);

		string strSql = "SELECT ProgName FROM SysConfig;";
		const char* szTail = NULL;
		sqlite3_stmt* pStmt = NULL;
		int nRet = -1;

		nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length() + 1, &pStmt, &szTail);

		//Database not exists, Create one.
		if (nRet != SQLITE_OK)
		{
			strSql = gszSql;
			char* szErr = NULL;
			nRet = sqlite3_exec(m_pDB, strSql.c_str(), NULL, NULL, &szErr);
			if (nRet != SQLITE_OK)
			{
				sqlite3_free(szErr);
				return false;
			}
		}
		return true;
	}
	return false;
}
void DataPool::SetDbFile(Std_String strFile)
{
	if (strFile != m_strDbFile && strFile != _T(""))
	{
		if (m_pDB)
		{
			sqlite3_close(m_pDB);
			m_pDB = NULL;
		}
		m_strDbFile = strFile;
		Init(strFile);
	}
	
}
Std_String DataPool::GetDbFile()
{
	return m_strDbFile;
}

UserObject* DataPool::GetUser(Std_String strUserName)
{
	return NULL;
}
int DataPool::GetUser(list<UserObject*>& rgpUsers)
{

	return -1;
}

ProgObject* DataPool::GetProg(Std_String strProg)
{
	return NULL;
}
int DataPool::GetProg(list<ProgObject*>& rgpProgs)
{
	return -1;
}

int DataPool::GetForbidPath(list<Std_String>& rgpPath)
{
	return -1;
}
int DataPool::GetForbidPath(Std_String strProgPath, list<ForbidOpt>& rgpPath)
{
	return -1;
}

bool DataPool::AddForbidPath(Std_String strProgPath, Std_String strPath, int nOpt)
{
	return false;
}

bool DataPool::ChangeForbidPathOpt(Std_String strProgPath, Std_String strPath, int nOpt)
{
	return false;
}

int DataPool::GetPathForbidProg(Std_String strPath, list<ProgObject*>& rgpProg)
{
	return -1;
}

bool DataPool::DropForbidPath(Std_String strProgPath, Std_String strPath)
{
	return false;
}
int DataPool::GetEncryptPath(list<Std_String>& rgpPath)
{
	return -1;
}
int DataPool::GetEncryptPath(Std_String strUser, list<Std_String>& rgpPath)
{
	return -1;
}
bool DataPool::AddEncryptPath(Std_String strUser, Std_String strPath)
{
	return false;
}
bool DataPool::DropEncryptPath(Std_String strUser, Std_String strPath)
{
	return false;
}