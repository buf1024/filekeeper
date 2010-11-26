//=============================================================================
/**
* @file	    stl.h
* @brief	common header providing basic stl services
* @author	heidong
* @version	1.0
* @date		2010-11-9 20:12:50
*/
//=============================================================================
#ifndef _STL_H_
#define _STL_H_

#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <iterator>
#include <string>

#ifdef _UNICODE
#define Std_String std::wstring
#else
#define Std_String std::string
#endif

using namespace std;

#endif
