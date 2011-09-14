#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "globals.h"

class BlockTestSuite : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE ( BlockTestSuite );
	
	CPPUNIT_TEST ( Instantiation );
	CPPUNIT_TEST ( GSLCompatibility );

    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
	void Instantiation();
	void GSLCompatibility();
};
