#include "StdAfx.h"
#include "DataPoolTest.h"

#include "stl.h"
#include "..\FileKeeper\Data\DataPool.h"
#include "..\FileKeeper\Data\UserObject.h"
#include "..\FileKeeper\Data\ProgObject.h"
#include "..\FileKeeper\Data\PersistObject.h"

DataPoolTest::DataPoolTest(void)
{
}

DataPoolTest::~DataPoolTest(void)
{
}

void DataPoolTest::setUp()
{
	//Assume we have 3 users
	//1. heidong 12345678911111 heidong
	//2. kavin 14785214782 kavin
	//3. hello 1478569 hello
	DataPool* pPool = DataPool::GetInstPtr();
	pPool->Empty();

	UserObject* pObj = new UserObject;
	pObj->SetUserName(_T("heidong"));
	pObj->SetPassword(_T("12345678911111"));
	pObj->SetDescription(_T("heidong"));
	pObj->Persist();
	delete pObj;

	pObj = new UserObject;
	pObj->SetUserName(_T("kavin"));
	pObj->SetPassword(_T("14785214782"));
	pObj->SetDescription(_T("kavin"));
	pObj->Persist();
	delete pObj;

	pObj = new UserObject;
	pObj->SetUserName(_T("hello"));
	pObj->SetPassword(_T("1478569"));
	pObj->SetDescription(_T("hello"));
	pObj->Persist();
	delete pObj;

	//Assume we have 5 programs
	//1. C:\a.exe a4777777 14
	//2. C:\b.exe b4777777 14
	//3. C:\c.exe c4777777 14
	//4. C:\d.exe d4777777 14
	//5. C:\e.exe e4777777 14

	ProgObject* pProg = new ProgObject;
	pProg->SetProgPath(_T("C:\\a.exe"));
	pProg->SetFootprint(_T("a4777777"));
	pProg->SetDescription(_T("14"));
	pProg->Persist();
	delete pProg;

	pProg = new ProgObject;
	pProg->SetProgPath(_T("C:\\b.exe"));
	pProg->SetFootprint(_T("b4777777"));
	pProg->SetDescription(_T("14"));
	pProg->Persist();
	delete pProg;

	pProg = new ProgObject;
	pProg->SetProgPath(_T("C:\\c.exe"));
	pProg->SetFootprint(_T("c4777777"));
	pProg->SetDescription(_T("14"));
	pProg->Persist();
	delete pProg;

	pProg = new ProgObject;
	pProg->SetProgPath(_T("C:\\d.exe"));
	pProg->SetFootprint(_T("d4777777"));
	pProg->SetDescription(_T("14"));
	pProg->Persist();
	delete pProg;

	pProg = new ProgObject;
	pProg->SetProgPath(_T("C:\\e.exe"));
	pProg->SetFootprint(_T("e4777777"));
	pProg->SetDescription(_T("14"));
	pProg->Persist();
	delete pProg;

	//Assume C:\WINDOWS\system32 is forbid to access
	//pPool->AddForbidPath(_T("C:\\WINDOWS\\system32"));

}
void DataPoolTest::tearDown()
{
	DataPool::ReleaseRC();
}

void DataPoolTest::testGetUser()
{
	DataPool* pPool = DataPool::GetInstPtr();

	Std_String strUser = _T("heidong"); //Exsiting User, Assume password is '12345678911111'
	UserObject* pUser = pPool->GetUser(strUser);
	CPPUNIT_ASSERT(pUser != NULL);
	CPPUNIT_ASSERT(pUser->GetUserName() == _T("heidong"));
	CPPUNIT_ASSERT(pUser->GetPassword() == _T("12345678911111"));
	delete pUser;

	strUser = _T("nobody"); //No exsiting user
	pUser = pPool->GetUser(strUser);
	CPPUNIT_ASSERT(pUser == NULL);

}
void DataPoolTest::testGetUsers()
{
	DataPool* pPool = DataPool::GetInstPtr();
	list<UserObject*> rgpUsers;
	int nCount = pPool->GetUser(rgpUsers);
	CPPUNIT_ASSERT(nCount == rgpUsers.size());
	CPPUNIT_ASSERT(nCount == 3);
	UserObject* pUser = NULL;
	for(list<UserObject*>::iterator iter = rgpUsers.begin();
		iter != rgpUsers.end(); ++iter)
	{
		if((*iter)->GetUserName() == _T("heidong"))
		{
			pUser = *iter;
			break;
		}
	}
	CPPUNIT_ASSERT(pUser != NULL);
	CPPUNIT_ASSERT(pUser->GetUserName() == _T("heidong"));
	CPPUNIT_ASSERT(pUser->GetPassword() == _T("12345678911111"));
	
	for(list<UserObject*>::iterator iter = rgpUsers.begin();
		iter != rgpUsers.end(); ++iter)
	{
		delete *iter;
	}

	rgpUsers.clear();
}
void DataPoolTest::testGetProg()
{
	DataPool* pPool = DataPool::GetInstPtr();

	Std_String strProg = _T("C:\\c.exe"); //Exsiting program, reference to setup
	ProgObject* pProg = pPool->GetProg(strProg);
	CPPUNIT_ASSERT(pProg != NULL);
	CPPUNIT_ASSERT(pProg->GetProgName() == _T("c.exe"));
	CPPUNIT_ASSERT(pProg->GetProgPath() == _T("C:\\c.exe"));
	CPPUNIT_ASSERT(pProg->GetFootprint() == _T("c4777777"));
	delete pProg;

	strProg = _T("no"); //No exsiting program
	pProg = pPool->GetProg(strProg);
	CPPUNIT_ASSERT(pProg == NULL);
}
void DataPoolTest::testGetProgs()
{
	DataPool* pPool = DataPool::GetInstPtr();

	list<ProgObject*> rgpProgs;
	int nCount = pPool->GetProg(rgpProgs);
	CPPUNIT_ASSERT(nCount == rgpProgs.size());
	CPPUNIT_ASSERT(nCount == 5);

	ProgObject* pProg = NULL;
	for(list<ProgObject*>::iterator iter = rgpProgs.begin();
		iter != rgpProgs.end(); ++iter)
	{
		if ((*iter)->GetProgName() == _T("c.exe"))
		{
			pProg = *iter;
			break;
		}
	}

	CPPUNIT_ASSERT(pProg != NULL);

	CPPUNIT_ASSERT(pProg->GetProgName() == _T("c.exe"));
	CPPUNIT_ASSERT(pProg->GetProgPath() == _T("C:\\c.exe"));
	CPPUNIT_ASSERT(pProg->GetFootprint() == _T("c4777777"));

	for(list<ProgObject*>::iterator iter = rgpProgs.begin();
		iter != rgpProgs.end(); ++iter)
	{
		delete *iter;
	}
	rgpProgs.clear();
}
void DataPoolTest::testGetForbidPaths()
{
	DataPool* pPool = DataPool::GetInstPtr();

	list<Std_String> rgpPath;
	int nCount = pPool->GetForbidPath(rgpPath);

}
void DataPoolTest::testGetSpecProgForbidPath()
{
	DataPool* pPool = DataPool::GetInstPtr();

	Std_String strProgPath = _T("C:\\c.exe");
	list<Std_String> rgpPath;
	int nCount = pPool->GetForbidPath(strProgPath, rgpPath);
}
void DataPoolTest::testGetSpecPathForbidProg()
{
	DataPool* pPool = DataPool::GetInstPtr();

	Std_String strPath = _T("C:\\Windows");
	list<ProgObject*> rgpProg;
	int nCount = pPool->GetPathForbidProg(strPath, rgpProg);
}
void DataPoolTest::testGetEncriptPathUser()
{
	DataPool* pPool = DataPool::GetInstPtr();

	Std_String strUser = _T("heidong");
	list<Std_String> rgpPath;
	int nCount = pPool->GetEncryptPath(strUser, rgpPath);
}

CPPUNIT_TEST_SUITE_REGISTRATION(DataPoolTest);