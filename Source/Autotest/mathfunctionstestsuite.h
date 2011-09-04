#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "globals.h"

class MathFunctionsTestSuite : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE ( MathFunctionsTestSuite );

	CPPUNIT_TEST ( ElementaryFunctions );
	CPPUNIT_TEST ( SmallIntegerPowers );
	CPPUNIT_TEST ( Signs );
	CPPUNIT_TEST ( Approximation );
	CPPUNIT_TEST ( MinMaxOddEven );

    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
	void ElementaryFunctions();
	void SmallIntegerPowers();
	void Signs();
	void Approximation();
	void MinMaxOddEven();
};
