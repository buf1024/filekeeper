//=============================================================================
/**
* @file	    UserObject.cpp
* @brief	UserObject implementation
* @author	heidong
* @version	1.0
* @date		2010-12-13 20:54:53
*/
//=============================================================================
#include "StdAfx.h"
#include "UserObject.h"
#include "DataPool.h"

UserObject::UserObject(DataPool* pPool)
: PersistObject(pPool)
{
}

UserObject::~UserObject(void)
{
}


bool UserObject::Persist()
{
	DataPool* pPool = GetDataPool();
	return pPool->PersistUser(this);
}
bool UserObject::Refresh()
{
	DataPool* pPool = GetDataPool();
	UserObject* pObj = pPool->GetUser(m_strName);
	if (pObj)
	{
		m_strName = pObj->GetUserName();
		m_strPass = pObj->GetPassword();
		m_strDesc = pObj->GetDescription();

		delete pObj;
		return true;
	}

	return false;
}

void UserObject::SetUserName(Std_String strUserName)
{
	m_strName = strUserName;
}
Std_String UserObject::GetUserName()
{
	return m_strName;
}

void UserObject::SetPassword(Std_String strPass)
{
	m_strPass = strPass;
}
Std_String UserObject::GetPassword()
{
	return m_strPass;
}

void UserObject::SetDescription(Std_String strDesc)
{
	m_strDesc = strDesc;
}
Std_String UserObject::GetDescription()
{
	return m_strDesc;
}

int UserObject::GetEncryptPath(list<Std_String>& rgpPath)
{
	DataPool* pPool = GetDataPool();
	return pPool->GetEncryptPath(m_strName, rgpPath);
}

bool UserObject::AddEncryptPath(Std_String strPath)
{
	DataPool* pPool = GetDataPool();
	return pPool->AddEncryptPath(m_strName, strPath);
}

bool UserObject::DropEncryptPath(Std_String strPath)
{
	DataPool* pPool = GetDataPool();
	return pPool->DropEncryptPath(m_strName, strPath);
}