#include "StdAfx.h"
#include "UtilTest.h"

#include "..\..\FileKeeper\Util\Util.h"

UtilTest::UtilTest(void)
{
}

UtilTest::~UtilTest(void)
{
}

void UtilTest::setUp()
{

}
void UtilTest::tearDown()
{
}

void UtilTest::testMSTOWS()
{
	string strValue;
	CPPUNIT_ASSERT(Util::GetWStringFromString(strValue) == L"");
	strValue = "heidong in CHN";
	CPPUNIT_ASSERT(Util::GetWStringFromString(strValue) == L"heidong in CHN");
}
void UtilTest::testWSTOMS()
{
	wstring strValue;
	CPPUNIT_ASSERT(Util::GetStringFromWString(strValue) == "");
	strValue = L"heidong in CHN";
	CPPUNIT_ASSERT(Util::GetStringFromWString(strValue) == "heidong in CHN");
}

CPPUNIT_TEST_SUITE_REGISTRATION(UtilTest);