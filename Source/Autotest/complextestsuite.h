#pragma once


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "globals.h"

class ComplexTestSuite : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE ( ComplexTestSuite );

	CPPUNIT_TEST ( Construction );
	CPPUNIT_TEST ( Properties );
	CPPUNIT_TEST ( Equality );
	CPPUNIT_TEST ( Arithmetic );
	CPPUNIT_TEST ( ElementaryFunctions );
	CPPUNIT_TEST ( TrigonometricFunctions );
	CPPUNIT_TEST ( HyperbolicFunctions );
	CPPUNIT_TEST ( IO );

    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
	void Construction();
	void Properties();
	void Equality();
	void Arithmetic();
	void ElementaryFunctions();
	void TrigonometricFunctions();
	void HyperbolicFunctions();
	void IO();
};
