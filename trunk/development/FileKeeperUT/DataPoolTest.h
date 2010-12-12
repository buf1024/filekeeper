#pragma once

#include "cppunit.h"

class DataPoolTest :
	public TestFixture
{
	CPPUNIT_TEST_SUITE(DataPoolTest);
		CPPUNIT_TEST(testGetUser);
		CPPUNIT_TEST(testGetUsers);
		CPPUNIT_TEST(testGetProg);
		CPPUNIT_TEST(testGetProgs);
		CPPUNIT_TEST(testGetForbidPaths);
		CPPUNIT_TEST(testGetSpecProgForbidPath);
		CPPUNIT_TEST(testGetSpecPathForbidProg);
		CPPUNIT_TEST(testGetEncriptPathUser);
	CPPUNIT_TEST_SUITE_END();
public:
	DataPoolTest(void);
	~DataPoolTest(void);

public:
	void setUp();
	void tearDown();

public:
	void testGetUser();
	void testGetUsers();
	void testGetProg();
	void testGetProgs();
	void testGetForbidPaths();
	void testGetSpecProgForbidPath();
	void testGetSpecPathForbidProg();
	void testGetEncriptPathUser();

};
