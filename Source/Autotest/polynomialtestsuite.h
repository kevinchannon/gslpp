#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "globals.h"

class PolynomialTestSuite : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE ( PolynomialTestSuite );
	
	CPPUNIT_TEST ( Instantiation );
	CPPUNIT_TEST ( Evaluation );

    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
	void Instantiation();
	void Evaluation();
	
private:
	double M_tolerance;
};
