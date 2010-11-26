#ifndef __CPPUNIT_H__
#define __CPPUNIT_H__

//Test case fixture
#include <cppunit/Test.h>
#include <cppunit/TestLeaf.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestComposite.h>
#include <cppunit/TestSuite.h>

//Test runner
//#include <cppunit/TestRunner.h>
//Test result
//#include <cppunit/TestResult.h>
//Test assertion
#include <cppunit/TestAssert.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <cppunit/ui/mfc/TestRunner.h>

#if _DEBUG

#if _UNICODE
#pragma comment(lib, "cppunitud_dll.lib")
#pragma comment(lib, "testrunnerud.lib")
#else
#pragma comment(lib, "cppunitd_dll.lib")
#pragma comment(lib, "testrunnerd.lib")
#endif

#else

#pragma comment(lib, "cppunitu_dll.lib")
#pragma comment(lib, "testrunneru.lib")

#endif

using namespace CppUnit;

#endif //__CPPUNIT_H__

