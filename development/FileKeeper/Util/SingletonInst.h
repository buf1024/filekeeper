//============================================================================
// Descripton:
//  Makesure an application can only run one instance.
//
// USsage Example:
//  At begining of main function, add the code similar to the following:
//  lgc::SingletonInst inst;
//  if(!inst) //Not Singleton
//  {
//    ... //Do other things
//  }
//
// Create at 2010-9-26 22:49:51 by heidong
//============================================================================
#pragma once

namespace lgc
{

class SingletonInst
{
public:
	SingletonInst(LPCTSTR pszName = NULL);
	~SingletonInst(void);
	

public:
	BOOL operator == (BOOL bCmp);
	BOOL operator != (BOOL bCmp);
	BOOL operator ! ();
	operator BOOL ();

private:
	HANDLE m_hEvent;
	BOOL m_bInstExist;
};
}
