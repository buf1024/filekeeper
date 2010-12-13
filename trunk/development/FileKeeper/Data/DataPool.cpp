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

DataPool::DataPool(void)
{
}

DataPool::~DataPool(void)
{
}

bool DataPool::Empty()
{
	return false;
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