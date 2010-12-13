//=============================================================================
/**
* @file	    HashImpl.h
* @brief	Hash implementation interface
* @author	heidong
* @version	1.0
* @date		2010-11-9 20:09:04
*/
//=============================================================================

#ifndef _HASHIMPL_H_
#define _HASHIMPL_H_

#include <stl.h>

namespace lgc
{
	class HashImpl
	{
	public:
		HashImpl(){}
		virtual ~HashImpl(){}
	public:
		virtual Std_String GetStringHash(std::string strValue) = 0;
		virtual Std_String GetStringHash(std::wstring strValue) = 0;
		virtual Std_String GetFileHash(Std_String strFile) = 0;

	};
}

#endif
