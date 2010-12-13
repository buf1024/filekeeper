//=============================================================================
/**
* @file	    HashCRC32Impl.cpp
* @brief	The CRC32 Implemation
* @author	heidong
* @version	1.0
* @date		2010-11-13 15:18:51
*/
//=============================================================================
#include "StdAfx.h"
#include "HashCRC32Impl.h"
using namespace lgc;

HashCRC32Impl::HashCRC32Impl(void)
{
	Init_CRC32_Table();
}

HashCRC32Impl::~HashCRC32Impl(void)
{
}

Std_String HashCRC32Impl::GetStringHash(std::string strValue)
{
	int nLen = strValue.size();
	const unsigned char* pBuf = (const unsigned char*)strValue.data();
	int nRes = Get_CRC(pBuf, nLen);
	TCHAR szBuf[16] = _T("");
	if (nRes < 0)
		_sntprintf_s(szBuf, 16, 16, _T("-%x"), -nRes);
	else
		_sntprintf_s(szBuf, 16, 16, _T("%x"), nRes);
	return szBuf;
}

Std_String HashCRC32Impl::GetStringHash(std::wstring strValue)
{
	int nLen = strValue.size() * sizeof(wchar_t);
	const unsigned char* pBuf = (const unsigned char*)strValue.data();
	int nRes = Get_CRC(pBuf, nLen);	
	TCHAR szBuf[16] = _T("");
	if (nRes < 0)
		_sntprintf_s(szBuf, 16, 16, _T("-%x"), -nRes);
	else
		_sntprintf_s(szBuf, 16, 16, _T("%x"), nRes);
	return szBuf;
}

Std_String HashCRC32Impl::GetFileHash(Std_String strFile)
{
	Std_String strRet;

	HANDLE hFile = CreateFile(strFile.c_str(), GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_WRITECOPY, 0, 0, NULL);
		if (hMapping != INVALID_HANDLE_VALUE)
		{
			PBYTE pByte = (PBYTE)MapViewOfFile(hMapping, FILE_MAP_COPY, 0, 0, 0);
			DWORD dwSize = GetFileSize(hFile, NULL);			
			int nRes = Get_CRC(pByte, dwSize);
			TCHAR szBuf[16] = _T("");
			if (nRes < 0)
				_sntprintf_s(szBuf, 16, 16, _T("-%x"), -nRes);
			else
				_sntprintf_s(szBuf, 16, 16, _T("%x"), nRes);
			strRet = szBuf;
			UnmapViewOfFile(pByte);
			CloseHandle(hMapping);
		}
		else
		{
			CloseHandle(hFile);
		}
	}

	return strRet;
}

// Call this function only once to initialize the CRC table.
void HashCRC32Impl::Init_CRC32_Table()
{
	// This is the official polynomial used by CRC-32 
	// in PKZip, WinZip and Ethernet. 
	ULONG ulPolynomial = 0x04c11db7;

	// 256 values representing ASCII character codes.
	for(int i = 0; i <= 0xFF; i++)
	{
		crc32_table[i]=Reflect(i, 8) << 24;
		for (int j = 0; j < 8; j++)
			crc32_table[i] = (crc32_table[i] << 1) ^ (crc32_table[i] & (1 << 31) ? ulPolynomial : 0);
		crc32_table[i] = Reflect(crc32_table[i], 32);
	}
}

// Reflection is a requirement for the official CRC-32 standard.
ULONG HashCRC32Impl::Reflect(ULONG ref, char ch)
{
	// Used only by Init_CRC32_Table()
	ULONG value(0);

	// Swap bit 0 for bit 7
	// bit 1 for bit 6, etc.
	for(int i = 1; i < (ch + 1); i++)
	{
		if(ref & 1)
			value |= 1 << (ch - i);
		ref >>= 1;
	}
	return value;
}

// Once the lookup table has been filled in by the two functions above,
// this function creates all CRCs using only the lookup table.
int HashCRC32Impl::Get_CRC(const unsigned char* buffer, int nLen)
{
	// Start out with all bits set high.
	ULONG  ulCRC(0xffffffff);
	while(nLen--)
		ulCRC = (ulCRC >> 8) ^ crc32_table[(ulCRC & 0xFF) ^ *buffer++];
	// Exclusive OR the result with the beginning value.
	return ulCRC ^ 0xffffffff;
}