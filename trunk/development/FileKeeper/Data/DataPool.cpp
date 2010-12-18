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
#include "UserObject.h"
#include "ProgObject.h"
#include "PersistObject.h"
#include "..\Util\Util.h"

DataPool::DataPool(void)
: m_pDB(NULL)
, m_bInit(false)
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
	if (!m_bInit)	return false;

	char* szErr = NULL;
	string strSql = gszCleanSql;

	int nRet = sqlite3_exec(m_pDB, strSql.c_str(), NULL, NULL, &szErr);

	if (nRet != SQLITE_OK)
	{
		sqlite3_free(szErr);
		return false;
	}
	return true;
}

bool DataPool::Init(Std_String strFile)
{
	//Not allow memory database
	if (!strFile.empty())
	{
		string strAnsiFile = Util::GetStringFromWString(strFile);
		sqlite3_open(strAnsiFile.c_str(), &m_pDB);

		string strSql = "SELECT ProgName FROM SysConfig;";
		sqlite3_stmt* pStmt = NULL;
		int nRet = -1;

		nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length() + 1, &pStmt, NULL);

		//Database not exists, Create one.
		if (nRet != SQLITE_OK)
		{
			strSql = gszCreateSql;
			char* szErr = NULL;
			nRet = sqlite3_exec(m_pDB, strSql.c_str(), NULL, NULL, &szErr);
			if (nRet != SQLITE_OK)
			{
				sqlite3_free(szErr);
				return false;
			}
		}
		else
		{
			sqlite3_finalize(pStmt);
		}
		m_bInit = true;
		return true;
	}
	return false;
}
void DataPool::SetDbFile(Std_String strFile)
{
	if (strFile != m_strDbFile && strFile != _T(""))
	{
		m_bInit = false;
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
	if (!m_bInit) return NULL;

	UserObject* pObj = NULL;

	//Name is unique
	string strSql = "SELECT * FROM User WHERE Name = ?;";
	sqlite3_stmt* pStmt = NULL;
	int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length() + 1, &pStmt, NULL);	
	if (nRet != SQLITE_OK)	return NULL;

	string strValue = Util::GetStringFromWString(strUserName);
	sqlite3_bind_text(pStmt, 1, strValue.c_str(), strValue.length() + 1, NULL);

	nRet = sqlite3_step(pStmt);
	if (nRet == SQLITE_ROW)
	{
		const unsigned char* szName = sqlite3_column_text(pStmt, 0);
		//Not safe
		const unsigned char* szPass = sqlite3_column_text(pStmt, 1);
		const unsigned char* szDesc = sqlite3_column_text(pStmt, 2);

		Std_String strName = Util::GetWStringFromString((const char*)szName);
		Std_String strPass = Util::GetWStringFromString((const char*)szPass);
		Std_String strDesc = Util::GetWStringFromString((const char*)szDesc);

		pObj = new UserObject;
		pObj->SetUserName(strName);
		pObj->SetPassword(strPass);
		pObj->SetDescription(strDesc);
	}
	sqlite3_finalize(pStmt);

	return pObj;
}
int DataPool::GetUser(list<UserObject*>& rgpUsers)
{
	if (!m_bInit) return NULL;

	rgpUsers.clear();

	UserObject* pObj = NULL;

	//Name is unique
	string strSql = "SELECT * FROM User;";
	sqlite3_stmt* pStmt = NULL;
	int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length() + 1, &pStmt, NULL);
	if (nRet != SQLITE_OK)	return NULL;

	while ((nRet = sqlite3_step(pStmt)) == SQLITE_ROW)
	{
		const unsigned char* szName = sqlite3_column_text(pStmt, 0);
		//Not safe
		const unsigned char* szPass = sqlite3_column_text(pStmt, 1);
		const unsigned char* szDesc = sqlite3_column_text(pStmt, 2);

		Std_String strName = Util::GetWStringFromString((const char*)szName);
		Std_String strPass = Util::GetWStringFromString((const char*)szPass);
		Std_String strDesc = Util::GetWStringFromString((const char*)szDesc);

		pObj = new UserObject;
		pObj->SetUserName(strName);
		pObj->SetPassword(strPass);
		pObj->SetDescription(strDesc);

		rgpUsers.push_back(pObj);
	}
	sqlite3_finalize(pStmt);

	return rgpUsers.size();
}

bool DataPool::PersistUser(UserObject* pUser)
{
	if (!m_bInit || !pUser) return false;
	string strSql;
	UserObject* pTmp = GetUser(pUser->GetUserName());
	
	sqlite3_stmt* pStmt = NULL;
	if (pTmp)
	{
		strSql = "UPDATE User SET Password = :pass, Desc = :desc WHERE Name = :name;";
		delete pTmp;
	}
	else
	{
		strSql = "INSERT INTO User(Name, Password, Desc) VALUES(:name, :pass, :desc);";
	}
	
	int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length() + 1, &pStmt, NULL);
	if (nRet == SQLITE_OK)
	{
		string strName = Util::GetStringFromWString(pUser->GetUserName());
		string strPass = Util::GetStringFromWString(pUser->GetPassword());
		string strDesc = Util::GetStringFromWString(pUser->GetDescription());
		sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":name"),
			strName.c_str(), strName.length() + 1, NULL);
		sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":pass"),
			strPass.c_str(), strPass.length() + 1, NULL);
		sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":desc"),
			strDesc.c_str(), strDesc.length() + 1, NULL);

		nRet = sqlite3_step(pStmt);

		sqlite3_finalize(pStmt);

		return true;
	}
	return false;
}

ProgObject* DataPool::GetProg(Std_String strProg)
{
	if (!m_bInit) return NULL;

	ProgObject* pObj = NULL;

	//Name is unique
	string strSql = "SELECT * FROM Prog WHERE Path = ?;";
	sqlite3_stmt* pStmt = NULL;
	int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length() + 1, &pStmt, NULL);	
	if (nRet != SQLITE_OK)	return NULL;

	string strValue = Util::GetStringFromWString(strProg);
	sqlite3_bind_text(pStmt, 1, strValue.c_str(), strValue.length() + 1, NULL);

	nRet = sqlite3_step(pStmt);
	if (nRet == SQLITE_ROW)
	{
		const unsigned char* szPath = sqlite3_column_text(pStmt, 0);
		const unsigned char* szFootprint = sqlite3_column_text(pStmt, 1);
		const unsigned char* szDesc = sqlite3_column_text(pStmt, 2);

		Std_String strPath = Util::GetWStringFromString((const char*)szPath);
		Std_String strFootprint = Util::GetWStringFromString((const char*)szFootprint);
		Std_String strDesc = Util::GetWStringFromString((const char*)szDesc);

		pObj = new ProgObject;
		pObj->SetProgPath(strPath);
		pObj->SetFootprint(strFootprint);
		pObj->SetDescription(strDesc);
	}
	sqlite3_finalize(pStmt);

	return pObj;
}
int DataPool::GetProg(list<ProgObject*>& rgpProgs)
{
	if (!m_bInit) return NULL;

	rgpProgs.clear();
	ProgObject* pObj = NULL;

	//Name is unique
	string strSql = "SELECT * FROM Prog;";
	sqlite3_stmt* pStmt = NULL;
	int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length() + 1, &pStmt, NULL);
	if (nRet != SQLITE_OK)	return NULL;

	while ((nRet = sqlite3_step(pStmt)) == SQLITE_ROW)
	{
		const unsigned char* szPath = sqlite3_column_text(pStmt, 0);
		const unsigned char* szFootprint = sqlite3_column_text(pStmt, 1);
		const unsigned char* szDesc = sqlite3_column_text(pStmt, 2);

		Std_String strPath = Util::GetWStringFromString((const char*)szPath);
		Std_String strFootprint = Util::GetWStringFromString((const char*)szFootprint);
		Std_String strDesc = Util::GetWStringFromString((const char*)szDesc);

		pObj = new ProgObject;
		pObj->SetProgPath(strPath);
		pObj->SetFootprint(strFootprint);
		pObj->SetDescription(strDesc);

		rgpProgs.push_back(pObj);
	}
	sqlite3_finalize(pStmt);

	return rgpProgs.size();
}

bool DataPool::PersistProg(ProgObject* pProg)
{
	if (!m_bInit || !pProg) return false;
	string strSql;
	ProgObject* pTmp = GetProg(pProg->GetProgPath());

	sqlite3_stmt* pStmt = NULL;
	if (pTmp)
	{
		strSql = "UPDATE Prog SET Footprint = :footprint, Desc = :desc WHERE Path = :path;";
		delete pTmp;
	}
	else
	{
		strSql = "INSERT INTO Prog(Path, Footprint, Desc) VALUES(:path, :footprint, :desc);";
	}

	int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length() + 1, &pStmt, NULL);
	if (nRet == SQLITE_OK)
	{
		string strPath = Util::GetStringFromWString(pProg->GetProgPath());
		string strFootprint = Util::GetStringFromWString(pProg->GetFootprint());
		string strDesc = Util::GetStringFromWString(pProg->GetDescription());
		sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":path"),
			strPath.c_str(), strPath.length() + 1, NULL);
		sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":footprint"),
			strFootprint.c_str(), strFootprint.length() + 1, NULL);
		sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":desc"),
			strDesc.c_str(), strDesc.length() + 1, NULL);

		nRet = sqlite3_step(pStmt);

		sqlite3_finalize(pStmt);

		return true;
	}
	return false;
}

int DataPool::GetForbidPath(list<Std_String>& rgpPath)
{
	if (!m_bInit) return false;
	
	rgpPath.clear();
	string strSql = "SELECT Path FROM ForbidList WHERE Option = -1;";
	sqlite3_stmt* pStmt = NULL;
	int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length() + 1, &pStmt, NULL);
	if (nRet == SQLITE_OK)
	{
		while((nRet = sqlite3_step(pStmt)) == SQLITE_ROW)
		{
			const unsigned char* szPath = sqlite3_column_text(pStmt, 0);
			Std_String strPath = Util::GetWStringFromString((const char*)szPath);
			rgpPath.push_back(strPath);
		}
		sqlite3_finalize(pStmt);
		return rgpPath.size();
	}
	return -1;
}
int DataPool::GetForbidPath(Std_String strProgPath, list<ForbidOpt>& rgpPath)
{
	if (!m_bInit || strProgPath.empty()) return false;
	rgpPath.clear();
	string strSql = "SELECT Option, Path FROM ForbidList WHERE ProgPath = :progpath;";
	sqlite3_stmt* pStmt = NULL;
	int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length() + 1, &pStmt, NULL);
	if (nRet == SQLITE_OK)
	{
		string strValue = Util::GetStringFromWString(strProgPath);
		sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, "progpath"),
			strValue.c_str(), strValue.length() + 1, NULL);

		while((nRet = sqlite3_step(pStmt)) == SQLITE_ROW)
		{
			int nOpt = sqlite3_column_int(pStmt, 0);
			const unsigned char* szPath = sqlite3_column_text(pStmt, 1);

			Std_String strPath = Util::GetWStringFromString((const char*)szPath);
			rgpPath.push_back(ForbidOpt(nOpt, strPath));
		}
		sqlite3_finalize(pStmt);
		return rgpPath.size();
	}
	return -1;
}

bool DataPool::AddForbidPath(Std_String strProgPath, Std_String strPath, int nOpt)
{
	return false;
}

bool DataPool::AddForbidPath(Std_String strPath)
{
	return false;
}

bool DataPool::ChangeForbidPathOpt(Std_String strProgPath, Std_String strPath, int nOpt)
{
	return false;
}

int DataPool::GetPathForbidProg(Std_String strPath, list<ProgObject*>& rgpProg)
{
	rgpProg.clear();
	return -1;
}
bool DataPool::AddPathForbidProg(Std_String strPath, Std_String strProgPath)
{
	return false;
}

bool DataPool::DropForbidPath(Std_String strProgPath, Std_String strPath)
{
	return false;
}
bool DataPool::DropForbidPath(Std_String strPath)
{
	return false;
}
int DataPool::GetEncryptPath(list<Std_String>& rgpPath)
{
	rgpPath.clear();
	return -1;
}
int DataPool::GetEncryptPath(Std_String strUser, list<Std_String>& rgpPath)
{
	rgpPath.clear();
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