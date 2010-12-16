//----------------------------------------------------------------------------
/**
* @file    Util.h
* @brief   Provide some convinient utility functions.
* @author  heidong
* @version 1.0
* @date    2010-12-16 (21:57)
*/
//----------------------------------------------------------------------------

#pragma once

#include <Singleton.h>
#include <stl.h>

using namespace lgc;

class Util
	: public Singleton<Util>
{
public:
	Util(void);
	~Util(void);

public:
	static string GetStringFromWString(wstring strValue);
	static wstring GetWStringFromString(string strValue);
};
