//=============================================================================
/**
* @file	    HashMD5Impl.h
* @brief	The MD5 implementaion
* @author	heidong
* @version	1.0
* @date		2010-11-13 15:19:54
*/
//=============================================================================
#ifndef _HASHMD5IMPL_H_
#define _HASHMD5IMPL_H_

#include "HashImpl.h"

namespace lgc
{
	class HashMD5Impl :
		public HashImpl
	{
	public:
		HashMD5Impl(void);
		~HashMD5Impl(void);
	public:
		virtual Std_String GetStringHash(std::string strValue);
		virtual Std_String GetStringHash(std::wstring strValue);
		virtual Std_String GetFileHash(Std_String strFile);

	private:
		Std_String ComputeHash(const unsigned char* pBuf, unsigned long lLen);
	};
}
#endif