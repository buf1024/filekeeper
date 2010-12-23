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
#include "..\ProductInfo.h"

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
    if (!m_pDB) return false;
	return ExecRawSql(gszCleanSql);
}

bool DataPool::Init(Std_String strFile)
{
	//Not allow memory database
	if (!strFile.empty())
	{
		string strAnsiFile = Util::GetStringFromWString(strFile);
		sqlite3_open(strAnsiFile.c_str(), &m_pDB);

		string strSql = "SELECT ProgName FROM SystemConfig;";
		sqlite3_stmt* pStmt = NULL;
		
		int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);

		//Database not exists, Create one.
		if (nRet != SQLITE_OK)
		{
            m_bInit = InitDBData();
		}
		else
		{
            sqlite3_step(pStmt);
            int nCount = sqlite3_data_count(pStmt);
            sqlite3_finalize(pStmt);
            if (nCount == 0)
            {                
                m_bInit = ExecRawSql(gszDropSql) && InitDBData();
            }
			
		}
		return m_bInit;
	}
	return false;
}
bool DataPool::InitDBData()
{
    bool bRet = false;
    if(ExecRawSql(gszCreateSql))
    {
        string strSql = "INSERT INTO SystemConfig(ProgName, ProgVer) VALUES(:name, :ver);";
        sqlite3_stmt* pStmt = NULL;
        int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);
        string strName = Util::GetStringFromWString(ProductName);
        string strVer = Util::GetStringFromWString(ProductVer);
        nRet = sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":name"), strName.c_str(), strName.length(), NULL);
        nRet = sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":ver"), strVer.c_str(), strVer.length(), NULL);

        nRet = sqlite3_step(pStmt);
        sqlite3_finalize(pStmt);
        bRet = true;
    }
    return bRet;

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
	int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);	
	if (nRet != SQLITE_OK)	return NULL;

	string strValue = Util::GetStringFromWString(strUserName);
	sqlite3_bind_text(pStmt, 1, strValue.c_str(), strValue.length(), NULL);

	nRet = sqlite3_step(pStmt);
	if (nRet == SQLITE_ROW)
	{
        pObj = BuildUserObject(pStmt);
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
	int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);
	if (nRet != SQLITE_OK)	return NULL;

	while ((nRet = sqlite3_step(pStmt)) == SQLITE_ROW)
	{
		pObj = BuildUserObject(pStmt);
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
	
	int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);
	if (nRet == SQLITE_OK)
	{
		string strName = Util::GetStringFromWString(pUser->GetUserName());
		string strPass = Util::GetStringFromWString(pUser->GetPassword());
		string strDesc = Util::GetStringFromWString(pUser->GetDescription());
		sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":name"),
			strName.c_str(), strName.length(), NULL);
		sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":pass"),
			strPass.c_str(), strPass.length(), NULL);
		sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":desc"),
			strDesc.c_str(), strDesc.length(), NULL);

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
	int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);	
	if (nRet != SQLITE_OK)	return NULL;

	string strValue = Util::GetStringFromWString(strProg);
	sqlite3_bind_text(pStmt, 1, strValue.c_str(), strValue.length(), NULL);

	nRet = sqlite3_step(pStmt);
	if (nRet == SQLITE_ROW)
	{
		pObj = BuildProgObject(pStmt);
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
	int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);
	if (nRet != SQLITE_OK)	return NULL;

	while ((nRet = sqlite3_step(pStmt)) == SQLITE_ROW)
	{
		pObj = BuildProgObject(pStmt);
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
        strSql = "UPDATE Prog SET Option = :opt, FootPrint = :footprint, Desc = :desc WHERE Path = :path;";
		delete pTmp;
	}
	else
	{
        strSql = "INSERT INTO Prog(Path, Option, FootPrint, Desc) VALUES(:path, :opt, :footprint, :desc);";
	}

	int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);
	if (nRet == SQLITE_OK)
	{
		string strPath = Util::GetStringFromWString(pProg->GetProgPath());
		string strFootprint = Util::GetStringFromWString(pProg->GetFootprint());
		string strDesc = Util::GetStringFromWString(pProg->GetDescription());
        sqlite3_bind_int(pStmt, sqlite3_bind_parameter_index(pStmt, ":opt"), pProg->GetOption());
		sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":path"),
			strPath.c_str(), strPath.length(), NULL);
		sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":footprint"),
			strFootprint.c_str(), strFootprint.length(), NULL);
		sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":desc"),
			strDesc.c_str(), strDesc.length(), NULL);

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
	int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);
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
	int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);
	if (nRet == SQLITE_OK)
	{
		string strValue = Util::GetStringFromWString(strProgPath);
        sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":progpath"),
			strValue.c_str(), strValue.length(), NULL);

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
    if (!m_bInit) return false;
    if (nOpt != -1 && strProgPath == _T("")) return false;

    string strSql = "SELECT * FROM ForbidList WHERE ProgPath = :progpath AND Path = :path;";
    sqlite3_stmt* pStmt = NULL;
    int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);
    if (nRet == SQLITE_OK)
    {
        string strAProg = Util::GetStringFromWString(strProgPath);
        string strAPath = Util::GetStringFromWString(strPath);

        sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":progpath"), strAProg.c_str(), strAProg.length(), NULL);
        sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":path"), strAPath.c_str(), strAPath.length(), NULL);

        sqlite3_step(pStmt);
        int nNum = sqlite3_data_count(pStmt);
        sqlite3_finalize(pStmt);
        pStmt = NULL;
        if (nNum > 0)
        { 
            return ChangeForbidPathOpt(strProgPath, strPath, nOpt);
        }
        else
        {
            strSql = "INSERT INTO ForbidList(Option, ProgPath, Path) VALUES(:opt, :progpath, :path);";
            nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);
            sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":progpath"), strAProg.c_str(), strAProg.length(), NULL);
            sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":path"), strAPath.c_str(), strAPath.length(), NULL);
            sqlite3_bind_int(pStmt, sqlite3_bind_parameter_index(pStmt, ":opt"), nOpt);
            nRet = sqlite3_step(pStmt);
            sqlite3_finalize(pStmt);
            return true;
        }
    }
	return false;
}

bool DataPool::AddForbidPath(Std_String strPath)
{
	return AddForbidPath(_T(""), strPath, -1);
}

bool DataPool::ChangeForbidPathOpt(Std_String strProgPath, Std_String strPath, int nOpt)
{
    if (!m_bInit || strProgPath.empty()) return false;

    string strSql = "SELECT * FROM ForbidList WHERE ProgPath = :progpath AND Path = :path;";
    sqlite3_stmt* pStmt = NULL;
    int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);
    if (nRet == SQLITE_OK)
    {
        string strAProg = Util::GetStringFromWString(strProgPath);
        string strAPath = Util::GetStringFromWString(strPath);

        sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":progpath"), strAProg.c_str(), strAProg.length(), NULL);
        sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":path"), strAPath.c_str(), strAPath.length(), NULL);

        sqlite3_step(pStmt);
        int nNum = sqlite3_data_count(pStmt);
        sqlite3_finalize(pStmt);
        if (nNum > 0)
        {
            strSql = "UPDATE ForbidList SET Option = :opt WHERE ProgPath = :progpath AND Path = :path;";
            sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);

            sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":progpath"), strAProg.c_str(), strAProg.length(), NULL);
            sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":path"), strAPath.c_str(), strAPath.length(), NULL);
            sqlite3_bind_int(pStmt, sqlite3_bind_parameter_index(pStmt, ":opt"), nOpt);
            sqlite3_step(pStmt);
            sqlite3_finalize(pStmt);
            return true;
        }
        return false;
    }
    return false;
}

int DataPool::GetPathForbidProg(Std_String strPath, list<ProgObject*>& rgpProg)
{
    if (!m_bInit) return false;

    rgpProg.clear();
    string strSql = "SELECT ProgPath FROM ForbidList WHERE Path = :path;";
    sqlite3_stmt* pStmt = NULL;
    int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);
    if (nRet == SQLITE_OK)
    {
        string strAPath = Util::GetStringFromWString(strPath);
        sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":path"), strAPath.c_str(), strAPath.length(), NULL);
        list<Std_String> rgpProgPath;

        while((nRet = sqlite3_step(pStmt)) == SQLITE_ROW)
        {
            Std_String strValue = Util::GetWStringFromString((const char*)sqlite3_column_text(pStmt, 0));
            rgpProgPath.push_back(strValue);
        }
        sqlite3_finalize(pStmt);

        for (list<Std_String>::iterator iter = rgpProgPath.begin();
            iter != rgpProgPath.end(); ++iter)
        {
            ProgObject* pObj = GetProg(*iter);
            if (pObj)
            {
                rgpProg.push_back(pObj);
            }           
        }
        return rgpProg.size();
    }
	
	return -1;
}
bool DataPool::AddPathForbidProg(Std_String strPath, Std_String strProgPath, int nOpt)
{
    list<ProgObject*> rgpProg;
    int nCount = GetPathForbidProg(strPath, rgpProg);
    if (nCount > 0)
    {
        for (list<ProgObject*>::iterator iter = rgpProg.begin();
            iter != rgpProg.end(); ++iter)
        {
            if ((*iter)->GetProgPath() == strProgPath)
            {
                return true;
            }
        }
    }
    
    string strSql = "INSERT INTO ForbidList(ProgPath, Path, Option) VALUES(:progpath, :path, :opt);";
    sqlite3_stmt* pStmt = NULL;
    int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);

    if (nRet == SQLITE_OK)
    {
        string strAProg = Util::GetStringFromWString(strProgPath);
        string strAPath = Util::GetStringFromWString(strPath);

        sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":progpath"), strAProg.c_str(), strAProg.length(), NULL);
        sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":path"), strAPath.c_str(), strAPath.length(), NULL);
        sqlite3_bind_int(pStmt, sqlite3_bind_parameter_index(pStmt, ":opt"), nOpt);

        nRet = sqlite3_step(pStmt);
        sqlite3_finalize(pStmt);

        return true;
    }

	return false;
}

bool DataPool::DropForbidPath(Std_String strProgPath, Std_String strPath)
{
    if (!m_bInit) return false;

    string strSql = "DELETE FROM ForbidList WHERE Path = :path AND ProgPath = :progpath;";
    sqlite3_stmt* pStmt = NULL;
    int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);
    if (nRet == SQLITE_OK)
    {
        string strAProg = Util::GetStringFromWString(strProgPath);
        string strAPath = Util::GetStringFromWString(strPath);

        sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":progpath"), strAProg.c_str(), strAProg.length(), NULL);
        sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":path"), strAPath.c_str(), strAPath.length(), NULL);

        sqlite3_step(pStmt);
        sqlite3_finalize(pStmt);

        return true;
    }
    return false;
}
bool DataPool::DropForbidPath(Std_String strPath)
{
    if (!m_bInit) return false;

    string strSql = "DELETE FROM ForbidList WHERE Path = :path AND Option = -1;";
    sqlite3_stmt* pStmt = NULL;
    int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);
    if (nRet == SQLITE_OK)
    {
        string strAPath = Util::GetStringFromWString(strPath);
        sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":path"), strAPath.c_str(), strAPath.length(), NULL);

        sqlite3_step(pStmt);
        sqlite3_finalize(pStmt);

        return true;
    }
    return false;
}
int DataPool::GetEncryptPath(list<Std_String>& rgpPath)
{
    if (!m_bInit) return false;

	rgpPath.clear();
    string strSql = "SELECT Path FROM EncryptList;";
    sqlite3_stmt* pStmt = NULL;

    int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);
    if(nRet == SQLITE_OK)
    {
        while((nRet = sqlite3_step(pStmt)) == SQLITE_ROW)
        {
            const unsigned char* szPath = sqlite3_column_text(pStmt, 0);
            rgpPath.push_back(Util::GetWStringFromString((const char*)szPath));
        }
        sqlite3_finalize(pStmt);
        return rgpPath.size();
    }
	return -1;
}
int DataPool::GetEncryptPath(Std_String strUser, list<Std_String>& rgpPath)
{
    if (!m_bInit) return false;

    rgpPath.clear();
    string strSql = "SELECT Path FROM EncryptList WHERE UserName = :username;";
    sqlite3_stmt* pStmt = NULL;

    int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);
    if(nRet == SQLITE_OK)
    {
        string strAUser = Util::GetStringFromWString(strUser);
        sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":username"), strAUser.c_str(), strAUser.length(), NULL);

        while((nRet = sqlite3_step(pStmt)) == SQLITE_ROW)
        {
            const unsigned char* szPath = sqlite3_column_text(pStmt, 0);
            rgpPath.push_back(Util::GetWStringFromString((const char*)szPath));
        }
        sqlite3_finalize(pStmt);
        return rgpPath.size();
    }
    return -1;
}
bool DataPool::AddEncryptPath(Std_String strUser, Std_String strPath)
{
    list<Std_String> rgpPath;
    int nRet = GetEncryptPath(strUser, rgpPath);
    if (nRet >= 0)
    {
        if (find(rgpPath.begin(), rgpPath.end(), strPath) != rgpPath.end())
        {
            return true;
        }
        string strSql = "INSERT INTO EncryptList(Path, UserName) VALUES(:path, :username);";
        sqlite3_stmt* pStmt = NULL;
        int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);
        if (nRet == SQLITE_OK)
        {
            string strAUser = Util::GetStringFromWString(strUser);
            string strAPath = Util::GetStringFromWString(strPath);
            sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":username"), strAUser.c_str(), strAUser.length(),NULL);            
            sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":path"), strAPath.c_str(), strAPath.length(), NULL);

            sqlite3_step(pStmt);
            sqlite3_finalize(pStmt);
            return true;
        }

    }

	return false;
}
bool DataPool::DropEncryptPath(Std_String strUser, Std_String strPath)
{
    if (!m_bInit) return false;

    string strSql = "DELETE FROM EncryptList WHERE Path = :path AND UserName = :username;";
    sqlite3_stmt* pStmt = NULL;
    int nRet = sqlite3_prepare(m_pDB, strSql.c_str(), strSql.length(), &pStmt, NULL);
    if (nRet == SQLITE_OK)
    {
        string strAUser = Util::GetStringFromWString(strUser);
        string strAPath = Util::GetStringFromWString(strPath);
        sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":username"), strAUser.c_str(), strAUser.length(),NULL);            
        sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, ":path"), strAPath.c_str(), strAPath.length(), NULL);

        sqlite3_step(pStmt);
        sqlite3_finalize(pStmt);
        return true;
    }
	return false;
}


bool DataPool::ExecRawSql(string strSql)
{
    char* szErr = NULL;
    int nRet = sqlite3_exec(m_pDB, strSql.c_str(), NULL, NULL, &szErr);
    if (nRet != SQLITE_OK)
    {
        sqlite3_free(szErr);
        return false;
    }
    return true;
}


UserObject* DataPool::BuildUserObject(sqlite3_stmt* pStmt)
{
    const unsigned char* szName = sqlite3_column_text(pStmt, 0);
    //Not safe
    const unsigned char* szPass = sqlite3_column_text(pStmt, 1);
    const unsigned char* szDesc = sqlite3_column_text(pStmt, 2);

    Std_String strName = Util::GetWStringFromString((const char*)szName);
    Std_String strPass = Util::GetWStringFromString((const char*)szPass);
    Std_String strDesc = Util::GetWStringFromString((const char*)szDesc);

    UserObject* pObj = new UserObject;
    pObj->SetUserName(strName);
    pObj->SetPassword(strPass);
    pObj->SetDescription(strDesc);

    return pObj;
}

 ProgObject* DataPool::BuildProgObject(sqlite3_stmt* pStmt)
 {
     const unsigned char* szPath = sqlite3_column_text(pStmt, 0);
     int nOpt = sqlite3_column_int(pStmt, 1);
     const unsigned char* szFootprint = sqlite3_column_text(pStmt, 2);
     const unsigned char* szDesc = sqlite3_column_text(pStmt, 3);

     Std_String strPath = Util::GetWStringFromString((const char*)szPath);
     Std_String strFootprint = Util::GetWStringFromString((const char*)szFootprint);
     Std_String strDesc = Util::GetWStringFromString((const char*)szDesc);

     ProgObject* pObj = new ProgObject;
     pObj->SetProgPath(strPath);
     pObj->SetOption(nOpt);
     pObj->SetFootprint(strFootprint);
     pObj->SetDescription(strDesc);
     return pObj;
 }
