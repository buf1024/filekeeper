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
, m_nOption(0)
{
}

ProgObject::~ProgObject(void)
{
}

bool ProgObject::Persist()
{
	DataPool* pPool = GetDataPool();
	return pPool->PersistProg(this);
}
bool ProgObject::Refresh()
{
	DataPool* pPool = GetDataPool();
	ProgObject* pObj = pPool->GetProg(m_strPath);
	if (pObj)
	{
		m_strPath = pObj->GetProgPath();
		m_strFootprint = pObj->GetFootprint();
		m_strDesc = pObj->GetDescription();

		delete pObj;
		return true;
	}

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
	Std_String strRet;
	if (!m_strPath.empty())
	{
		size_t nPos = m_strPath.rfind(_T('\\'));
		if (nPos != -1)
		{
			strRet = m_strPath.substr(nPos + 1);
		}
	}
	return strRet;
}

void ProgObject::SetOption(int nOpt)
{

}
int ProgObject::GetOption()
{
    return m_nOption;
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
	DataPool* pPool = GetDataPool();
	return pPool->GetForbidPath(m_strPath, rgpPathOpt);
}

int ProgObject::GetPathForbidOpt(Std_String strPath)
{
	int nRet = 0xFF;
	list<ForbidOpt> rgpPathOpt;
	int nCount = GetForbidPath(rgpPathOpt);
	if (nCount > 0)
	{
		for (list<ForbidOpt>::iterator iter = rgpPathOpt.begin();
			iter != rgpPathOpt.end(); ++iter)
		{
			if (strPath == iter->m_strPath)
			{
				return iter->m_nOpt;
			}
		}
	}
	return nRet;
}

bool ProgObject::AddForbidPath(Std_String strPath, int nOpt)
{
	DataPool* pPool = GetDataPool();
	return pPool->AddForbidPath(m_strPath, strPath, nOpt);
}
bool ProgObject::DropForbidPath(Std_String strPath)
{
	DataPool* pPool = GetDataPool();
	return pPool->DropForbidPath(m_strPath, strPath);

}
bool ProgObject::ChangeForbidPathOpt(Std_String strPath, int nOpt)
{
	DataPool* pPool = GetDataPool();
	return pPool->ChangeForbidPathOpt(m_strPath, strPath, nOpt);
}