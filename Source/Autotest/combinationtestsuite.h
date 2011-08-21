#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "globals.h"

class CombinationTestSuite : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE ( CombinationTestSuite );
	
	CPPUNIT_TEST ( InitialisationTest );
	CPPUNIT_TEST ( ElementAccess );
	CPPUNIT_TEST ( Properties );
	CPPUNIT_TEST ( Advance );

    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:

	void InitialisationTest();
	void ElementAccess();
	void Properties();
	void Advance();
};
