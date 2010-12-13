//=============================================================================
/**
* @file	    ProgObject.cpp
* @brief	ProgObject implementation
* @author	heidong
* @version	1.0
* @date		2010-12-13 20:54:11
*/
//=============================================================================
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

bool ProgObject::Persist()
{
	return false;
}
bool ProgObject::Refresh()
{
	return false;
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

int ProgObject::GetForbidPath(list<ForbidOpt>& rgpPathOpt)
{
	return -1;
}

int ProgObject::GetPathForbidOpt(Std_String strPath)
{
	return 0xFF;
}

bool ProgObject::AddForbidPath(Std_String strPath, int nOpt)
{
	return false;
}
bool ProgObject::DropForbidPath(Std_String strPath)
{
	return false;

}
bool ProgObject::ChangeForbidPathOpt(Std_String strPath, int nOpt)
{
	return false;
}