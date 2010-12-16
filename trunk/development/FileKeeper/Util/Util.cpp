//----------------------------------------------------------------------------
/**
* @file    Util.cpp
* @brief   Util Implementation File
* @author  heidong
* @version 1.0
* @date    2010-12-16 (21:58)
*/
//----------------------------------------------------------------------------

#include "StdAfx.h"
#include "Util.h"

Util::Util(void)
{
}

Util::~Util(void)
{
}

string Util::GetStringFromWString(wstring strValue)
{
	if (strValue.empty())
	{
		return "";
	}
	char szBuf[1024] = "";
	//We don't use C Runtime convert function here
	WideCharToMultiByte(CP_ACP, 0L, 
		strValue.c_str(), -1, 
		szBuf, 1024,
		NULL, NULL);
	return szBuf;
}
wstring Util::GetWStringFromString(string strValue)
{
	if (strValue.empty())
	{
		return L"";
	}
	wchar_t szBuf[1024] = L"";
	//We don't use C Runtime convert function here
	MultiByteToWideChar(CP_ACP, 0L,
		strValue.c_str(), -1,       
		szBuf, 1024);
	return szBuf;
}
