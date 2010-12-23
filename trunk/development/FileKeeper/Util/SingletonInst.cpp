#include "StdAfx.h"
#include <crtdbg.h>
#include "SingletonInst.h"


using namespace lgc;

SingletonInst::SingletonInst(LPCTSTR pszName)
: m_hEvent(INVALID_HANDLE_VALUE)
, m_bInstExist(FALSE)
{
	TCHAR szName[MAX_PATH] = {0};
	if(pszName == NULL || lstrcmp(pszName, _T("")) == 0)
	{
		GetModuleFileName(NULL, szName, MAX_PATH);
		int nLen = lstrlen(szName);
		for (int i=0; i<nLen; i++)
		{
			if (szName[i] == _T('\\') || szName[i] == _T('/')
				|| szName[i] == _T(':') || szName[i] == _T('.'))
			{
				szName[i] = _T('_');
			}
		}
	}
	else
	{
		lstrcpy(szName, pszName);
	}
	
	m_hEvent = CreateEvent(NULL, FALSE, FALSE, szName);
	if (m_hEvent != NULL && m_hEvent != INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			m_bInstExist = TRUE;
		}
	}
	else
	{
		_ASSERT(FALSE);
	}
}

SingletonInst::~SingletonInst(void)
{
	if (m_hEvent != NULL && m_hEvent != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hEvent);
	}
}

BOOL SingletonInst::operator == (BOOL bCmp)
{
	return (bCmp == TRUE) != m_bInstExist;
}
BOOL SingletonInst::operator != (BOOL bCmp)
{
	return (bCmp == TRUE) == m_bInstExist;
}
BOOL SingletonInst::operator ! ()
{
	return m_bInstExist;
}
SingletonInst::operator BOOL ()
{
	return !m_bInstExist;
}