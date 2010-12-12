#include "StdAfx.h"
#include "ProgObject.h"
#include "DataPool.h"

ProgObject::ProgObject(DataPool* pPool)
: PersistObject(pPool)
{
}

ProgObject::~ProgObject(void)
{
}

void ProgObject::SetProgPath(Std_String strProgPath)
{
	m_strPath = strProgPath;
}
Std_String ProgObject::GetProgPath()
{
	return m_strPath;
}
Std_String ProgObject::GetProgName()
{
	return _T("");
}

void ProgObject::SetFootprint(Std_String strFootprint)
{
	m_strFootprint = strFootprint;
}
Std_String ProgObject::GetFootprint()
{
	return m_strFootprint;
}

void ProgObject::SetDescription(Std_String strDesc)
{
	m_strDesc = strDesc;
}
Std_String ProgObject::GetDescription()
{
	return m_strDesc;
}

int ProgObject::GetForbidPath(list<Std_String>& rgpPath)
{
	return -1;
}
bool ProgObject::DropForbidPath(Std_String strPath)
{
	return false;
}