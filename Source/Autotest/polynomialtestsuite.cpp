#include "polynomialtestsuite.h"

#include <iostream>

#include "gslpp/Polynomial/polynomial.h"

CPPUNIT_TEST_SUITE_REGISTRATION( PolynomialTestSuite );

void PolynomialTestSuite::setUp()
{
	M_tolerance = 1e-12;
}

////////////////////////////////////////////////////////////

void PolynomialTestSuite::tearDown(){}

////////////////////////////////////////////////////////////

void PolynomialTestSuite::Instantiation()
{
	gsl::polynomial p1(1.2, 2.5, -15, 6.9);
	gsl::polynomial p2(1,5.6);
	gsl::polynomial p3( 1.5 + 3i, 2.0, 4.2i );
}

////////////////////////////////////////////////////////////

void PolynomialTestSuite::Evaluation()
{
	gsl::polynomial p1( 1, 2.4, 3.2, 0.22, 1.32 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 82, p1.at( 2.5 ).real(), M_tolerance );
	
	gsl::polynomial p2(1, 1i, 1+1i);
	CPPUNIT_ASSERT( p2.at(1+1i) == std::complex< real >( -2, 3) );
}

////////////////////////////////////////////////////////////