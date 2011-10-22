#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "globals.h"

class PolynomialTestSuite : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE ( PolynomialTestSuite );
	
	CPPUNIT_TEST ( Instantiation );
	CPPUNIT_TEST ( Evaluation );
	CPPUNIT_TEST ( Order );
	CPPUNIT_TEST ( Resize );
	CPPUNIT_TEST ( SolveConstant );
	CPPUNIT_TEST ( SolveLinear );
	CPPUNIT_TEST ( SolveQuadratic );
	CPPUNIT_TEST ( SolveCubic );
	CPPUNIT_TEST ( SolveHighOrder );

    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
	void Instantiation();
	void Evaluation();
	void Order();
	void Resize();
	void SolveConstant();
	void SolveLinear();
	void SolveQuadratic();
	void SolveCubic();
	void SolveHighOrder();
	
private:
	double M_tolerance;
};
