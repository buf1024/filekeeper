//=============================================================================
/**
* @file	    ForbidOpt.h
* @brief	Forbiden Option
* @author	heidong
* @version	1.0
* @date		2010-12-13 20:44:04
*/
//=============================================================================
#pragma once

#include <stl.h>

/**Multi usage of Forbid Option*/
struct ForbidOpt
{
	ForbidOpt()
	{

	}
	ForbidOpt(int nOpt, Std_String strPath)
		: m_nOpt(nOpt)
		, m_strPath(strPath)
	{

	}
	int m_nOpt; /**< Use the linux right value, for example, 111 means forbid read, write and execute*/
	Std_String m_strPath; /**<The forbiden path or the program path*/
};