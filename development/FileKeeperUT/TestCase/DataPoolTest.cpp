#include "StdAfx.h"
#include "DataPoolTest.h"

#include "stl.h"
#include "..\..\FileKeeper\Data\DataPool.h"
#include "..\..\FileKeeper\Data\UserObject.h"
#include "..\..\FileKeeper\Data\ProgObject.h"
#include "..\..\FileKeeper\Data\PersistObject.h"
#include "..\..\FileKeeper\Data\ForbidOpt.h"

bool gbInt = false;

DataPoolTest::DataPoolTest(void)
{
}

DataPoolTest::~DataPoolTest(void)
{
}

void DataPoolTest::setUp()
{
    
	
    if (gbInt) return;
	
	gbInt = true;
	//Assume we have 3 users
	//1. heidong 12345678911111 heidong
	//2. kavin 14785214782 kavin
	//3. hello 1478569 hello
    DataPool* pPool = DataPool::GetInstPtr();
    pPool->Init(_T("FileKeeper.db"));
	pPool->Empty();

	UserObject* pObj = new UserObject;
	pObj->SetUserName(_T("heidong"));
	pObj->SetPassword(_T("12345678911111"));
	pObj->SetDescription(_T("heidong"));
	pObj->Persist();
	//assume user heidong encrypt E:\\DDD H:\\AAA
	pObj->AddEncryptPath(_T("E:\\DDD"));
	pObj->AddEncryptPath(_T("H:\\AAA"));
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
	//Assume Prog C:\\e.exe Forbid to access C:\\AAA B:\\BBB
	pProg->AddForbidPath(_T("C:\\AAA"));
	pProg->AddForbidPath(_T("B:\\BBB"));
	delete pProg;

	//Assume C:\WINDOWS\system32 D:\Program Files are forbid to access
	pPool->AddForbidPath(_T("C:\\WINDOWS\\system32"));
	pPool->AddForbidPath(_T("D:\\Program Files"));

	//Assum path A:\\AAA forbid program C:\\a.exe C:\\d.exe to access
	pPool->AddPathForbidProg(_T("A:\\AAA"), _T("C:\\a.exe"));
	pPool->AddPathForbidProg(_T("A:\\AAA"), _T("C:\\d.exe"));

}
void DataPoolTest::tearDown()
{
	//DataPool::ReleaseRC();
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
	CPPUNIT_ASSERT(nCount == 2);
	CPPUNIT_ASSERT(nCount == rgpPath.size());

	
	for(list<Std_String>::iterator iter = rgpPath.begin();
		iter != rgpPath.end(); ++iter)
	{
		CPPUNIT_ASSERT(*iter == _T("C:\\WINDOWS\\system32") || *iter == _T("D:\\Program Files"));
	}

}
void DataPoolTest::testGetSpecProgForbidPath()
{
	DataPool* pPool = DataPool::GetInstPtr();

	Std_String strProgPath = _T("C:\\e.exe");
	list<ForbidOpt> rgpPath;
	int nCount = pPool->GetForbidPath(strProgPath, rgpPath);

	CPPUNIT_ASSERT(nCount == 2);
	CPPUNIT_ASSERT(nCount == rgpPath.size());

	for(list<ForbidOpt>::iterator iter = rgpPath.begin();
		iter != rgpPath.end(); ++iter)
	{
		CPPUNIT_ASSERT(iter->m_strPath == _T("C:\\AAA") || iter->m_strPath == _T("B:\\BBB"));
		CPPUNIT_ASSERT(iter->m_nOpt == 0x07);
	}
}
void DataPoolTest::testGetSpecPathForbidProg()
{
	DataPool* pPool = DataPool::GetInstPtr();

	Std_String strPath = _T("A:\\AAA");
	list<ProgObject*> rgpProg;
	int nCount = pPool->GetPathForbidProg(strPath, rgpProg);

	CPPUNIT_ASSERT(nCount == 2);
	CPPUNIT_ASSERT(nCount == rgpProg.size());

	for(list<ProgObject*>::iterator iter = rgpProg.begin();
		iter != rgpProg.end(); ++iter)
	{
		CPPUNIT_ASSERT((*iter)->GetProgPath() == _T("C:\\a.exe") || (*iter)->GetProgPath() == _T("C:\\d.exe"));
		CPPUNIT_ASSERT((*iter)->GetFootprint() == _T("a4777777") || (*iter)->GetFootprint() == _T("d4777777"));
	}

	for(list<ProgObject*>::iterator iter = rgpProg.begin();
		iter != rgpProg.end(); ++iter)
	{
		delete *iter;
	}
	rgpProg.clear();
}
void DataPoolTest::testGetEncriptPathUser()
{
	DataPool* pPool = DataPool::GetInstPtr();

	Std_String strUser = _T("heidong");
	list<Std_String> rgpPath;
	int nCount = pPool->GetEncryptPath(strUser, rgpPath);

	CPPUNIT_ASSERT(nCount == 2);
	CPPUNIT_ASSERT(nCount == rgpPath.size());

	for(list<Std_String>::iterator iter = rgpPath.begin();
		iter != rgpPath.end(); ++iter)
	{
		CPPUNIT_ASSERT(*iter == _T("E:\\DDD") || *iter == _T("H:\\AAA"));
	}
}

void DataPoolTest::testAddDropPath()
{
	DataPool* pPool = DataPool::GetInstPtr();

	pPool->DropForbidPath(_T("D:\\Program Files"));
	list<Std_String> rgpPath;
	int nCount = pPool->GetForbidPath(rgpPath);
	CPPUNIT_ASSERT(nCount == 1);
	CPPUNIT_ASSERT(nCount == rgpPath.size());
	ASSERT(rgpPath.front() == _T("C:\\WINDOWS\\system32"));
    pPool->AddForbidPath(_T("D:\\Program Files"));

	Std_String strProgPath = _T("C:\\e.exe");
	pPool->DropForbidPath(strProgPath, _T("C:\\AAA"));	
	list<ForbidOpt> rgpPathOpt;
	nCount = pPool->GetForbidPath(strProgPath, rgpPathOpt);
	CPPUNIT_ASSERT(nCount == 1);
	CPPUNIT_ASSERT(nCount == rgpPathOpt.size());
	ASSERT(rgpPathOpt.front().m_strPath == _T("B:\\BBB"));
    pPool->AddForbidPath(strProgPath, _T("C:\\AAA"));	

	Std_String strUser = _T("heidong");
	pPool->DropEncryptPath(strUser, _T("E:\\DDD"));
	list<Std_String> rgpPathEn;
	nCount = pPool->GetEncryptPath(strUser, rgpPathEn);	
	CPPUNIT_ASSERT(nCount == 1);
	CPPUNIT_ASSERT(nCount == rgpPathEn.size());
	ASSERT(rgpPathEn.front() == _T("H:\\AAA"));
    pPool->AddEncryptPath(strUser, _T("E:\\DDD"));

    strProgPath = _T("C:\\e.exe");
    pPool->ChangeForbidPathOpt(strProgPath, _T("B:\\BBB"), 0x01);
    pPool->DropForbidPath(strProgPath, _T("C:\\AAA"));	
    nCount = pPool->GetForbidPath(strProgPath, rgpPathOpt);
    CPPUNIT_ASSERT(nCount == 1);
    CPPUNIT_ASSERT(nCount == rgpPathOpt.size());
    ForbidOpt opt = rgpPathOpt.front();
    CPPUNIT_ASSERT(opt.m_nOpt == 0X01);
    pPool->ChangeForbidPathOpt(strProgPath, _T("B:\\BBB"), 0x07);
    pPool->AddForbidPath(strProgPath, _T("C:\\AAA"));	

}


CPPUNIT_TEST_SUITE_REGISTRATION(DataPoolTest);