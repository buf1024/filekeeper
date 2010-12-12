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


void UserObject::Persist()
{

}
void UserObject::Restore()
{

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
	return -1;
}

bool UserObject::DropEncryptPath(Std_String strPath)
{
	return false;
}