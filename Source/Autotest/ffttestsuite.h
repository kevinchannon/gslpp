#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "globals.h"

class FFTTestSuite : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE ( FFTTestSuite );

    CPPUNIT_TEST( Radix2 );

    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
	
protected:
    void Radix2();
};
