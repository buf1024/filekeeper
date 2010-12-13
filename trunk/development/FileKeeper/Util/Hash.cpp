//=============================================================================
/**
* @file	    Hash.cpp
* @brief	
* @author	heidong
* @version	1.0
* @date		2010-11-9 20:09:19
*/
//=============================================================================
#include "stdafx.h"
#include "Hash.h"
#include "HashImpl.h"

using namespace lgc;

Hash::Hash(HashImpl* pImpl)
: m_pImpl(pImpl)
{
	_ASSERT(pImpl != NULL);
}
Hash::~Hash()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = NULL;
	}
}
Std_String Hash::GetStringHash(std::string strValue)
{
	return m_pImpl->GetStringHash(strValue);
}
Std_String Hash::GetStringHash(std::wstring strValue)
{
	return m_pImpl->GetStringHash(strValue);
}
Std_String Hash::GetFileHash(Std_String strFile)
{
	return m_pImpl->GetFileHash(strFile);
}