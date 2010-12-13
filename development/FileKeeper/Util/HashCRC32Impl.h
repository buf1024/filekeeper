//=============================================================================
/**
* @file	    HashCRC32Impl.h
* @brief	The CRC32 Implemetaion
* @author	heidong
* @version	1.0
* @date		2010-11-13 15:19:12
*/
//=============================================================================

#ifndef _HASHCRC32IMPL_H_
#define _HASHCRC32IMPL_H_

#include "HashImpl.h"

namespace lgc
{

	class HashCRC32Impl :
		public HashImpl
	{
	public:
		HashCRC32Impl(void);
		~HashCRC32Impl(void);
	public:
		virtual Std_String GetStringHash(std::string strValue);
		virtual Std_String GetStringHash(std::wstring strValue);
		virtual Std_String GetFileHash(Std_String strFile);

	private:
		void Init_CRC32_Table(); // Builds Lookup table array
		ULONG Reflect(ULONG ref, char ch); // Reflects CRC bits in the lookup table
		int Get_CRC(const unsigned char* buffer, int nLen); // Creates a CRC from a string buffer		
	private:
		ULONG crc32_table[256]; // Lookup table array
	};

}
#endif