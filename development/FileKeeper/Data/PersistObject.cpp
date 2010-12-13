//=============================================================================
/**
* @file	    PersistObject.cpp
* @brief	PersistObject implemetation
* @author	heidong
* @version	1.0
* @date		2010-12-13 20:52:51
*/
//=============================================================================
#include "StdAfx.h"
#include "PersistObject.h"
#include "DataPool.h"

PersistObject::PersistObject(DataPool* pPool)
: m_pDataPool(pPool)
{
}

PersistObject::~PersistObject(void)
{
}

bool PersistObject::Persist()
{
	return true;
}
bool PersistObject::Refresh()
{
	return true;
}