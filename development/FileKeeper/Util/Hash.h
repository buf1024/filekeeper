//=============================================================================
/**
* @file	    Hash.h
* @brief	For computing kinds of hash value(CRC32, MD5, SHA1...)
* @author	heidong
* @version	1.0
* @date		2010-11-9 20:08:32
*/
//=============================================================================

#ifndef _HASH_H_
#define _HASH_H_

#include <stl.h>

namespace lgc
{
	class HashImpl;
	/**@class Hash
	*@brief The interface of some hash algorithm
	*/
	class Hash
	{
	public:
		/**Constructor, provide some kind of implementation
		*@param pImpl The specific implemetation
		*/
		Hash(HashImpl* pImpl);
		~Hash();
	public:
		/**Compute the ASCII form of string hash code
		*@param strValue The string need to compute
		*@return the correspond hash value
		*/
		Std_String GetStringHash(std::string strValue);
		/**Compute the UNICODE form of string hash code
		*@param strValue The string need to compute
		*@return the correspond hash value
		*/
		Std_String GetStringHash(std::wstring strValue);
		/**Compute the specific file hash code
		*@param strFile The file need to compute
		*@return the correspond hash value, if the file does not exist or errors occur return empty string
		*/
		Std_String GetFileHash(Std_String strFile);
	private:
		HashImpl* m_pImpl;

	};
}

#endif
