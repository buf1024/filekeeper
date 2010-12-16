#pragma once

#include "cppunit.h"

class UtilTest :
	public TestFixture
{
	CPPUNIT_TEST_SUITE(UtilTest);
		CPPUNIT_TEST(testMSTOWS);
		CPPUNIT_TEST(testWSTOMS);
	CPPUNIT_TEST_SUITE_END();
public:
	UtilTest(void);
	~UtilTest(void);

public:
	void setUp();
	void tearDown();

public:
	void testMSTOWS();
	void testWSTOMS();
};
