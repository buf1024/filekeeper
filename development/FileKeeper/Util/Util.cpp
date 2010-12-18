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

	int nLen = (strValue.length() + 1)*2;
	char* pszBuf = new char[nLen];
	//We don't use C Runtime convert function here
	WideCharToMultiByte(CP_ACP, 0L, 
		strValue.c_str(), -1, 
		pszBuf, nLen,
		NULL, NULL);
	string strRet = pszBuf;
	delete[] pszBuf;

	return strRet;
}
wstring Util::GetWStringFromString(string strValue)
{
	if (strValue.empty())
	{
		return L"";
	}

	int nLen = strValue.length() + 1;
	wchar_t* pszBuf = new wchar_t[nLen];
	//We don't use C Runtime convert function here
	MultiByteToWideChar(CP_ACP, 0L,
		strValue.c_str(), -1,       
		pszBuf, nLen);
	wstring strRet = pszBuf;
	delete[] pszBuf;

	return strRet;
}
