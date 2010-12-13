//=============================================================================
/**
* @file	    HashSHA1Impl.h
* @brief	The SHA1 Implementaion
* @author	heidong
* @version	1.0
* @date		2010-11-13 15:20:36
*/
//=============================================================================
#ifndef _HASHSHA1IMPL_H_
#define _HASHSHA1IMPL_H_

// Test Vectors (from FIPS PUB 180-1)
//
//  SHA1("abc") =
//      A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D
//
//  SHA1("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq") =
//      84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1
//
//  SHA1(A million repetitions of "a") =
//      34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F
//

#include "HashImpl.h"
#include "sha1.h"

namespace lgc
{
	class HashSHA1Impl :
		public HashImpl, private SHA1
	{
	public:
		HashSHA1Impl(void);
		~HashSHA1Impl(void);
	public:
		virtual Std_String GetStringHash(std::string strValue);
		virtual Std_String GetStringHash(std::wstring strValue);
		virtual Std_String GetFileHash(Std_String strFile);
	};

}

#endif
