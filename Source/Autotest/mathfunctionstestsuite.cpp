#include "mathfunctionstestsuite.h"

#include "gslpp/Common/number.h"
#include "gslpp/Common/math.h"

#include <gsl/gsl_math.h>

////////////////////////////////////////////////////////////

CPPUNIT_TEST_SUITE_REGISTRATION( MathFunctionsTestSuite );

////////////////////////////////////////////////////////////

void MathFunctionsTestSuite::setUp(){}

////////////////////////////////////////////////////////////

void MathFunctionsTestSuite::tearDown(){}

////////////////////////////////////////////////////////////

void MathFunctionsTestSuite::ElementaryFunctions()
{
	// These test check that the gsl++ functions return the same values as their gsl counterparts
	real rTolerance = 1e-12;
	real rValue = 0.001;
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( gsl_log1p(rValue), gsl::log1p(rValue), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( gsl_expm1(rValue), gsl::expm1(rValue), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( gsl_hypot(rValue, rValue), gsl::hypot(rValue, rValue), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( gsl_ldexp(rValue, 5), gsl::ldexp( gsl::floating_point(rValue, 5)), rTolerance );
	
	real f;
	int e;
	f = gsl_frexp( rValue, &e );
	
	gsl::floating_point x = gsl::frexp( rValue );
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( x.f(), f, rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( x.e(), e, rTolerance );
}

////////////////////////////////////////////////////////////

void MathFunctionsTestSuite::SmallIntegerPowers()
{
	real rTolerance = 1e-12;
	real x = 3.1415628;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( x*x, gsl::pow_2(x), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( x*x*x, gsl::pow_3(x), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( x*x*x*x, gsl::pow_4(x), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( x*x*x*x*x, gsl::pow_5(x), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( x*x*x*x*x*x, gsl::pow_6(x), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( x*x*x*x*x*x*x, gsl::pow_7(x), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( x*x*x*x*x*x*x*x, gsl::pow_8(x), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( x*x*x*x*x*x*x*x*x, gsl::pow_9(x), rTolerance );
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( x*x*x*x*x*x*x*x*x*x*x*x, gsl::pow(x, 12), rTolerance );
}

////////////////////////////////////////////////////////////

void MathFunctionsTestSuite::Signs()
{
	real rPos = 1.32;
	real rZero = realZero;
	real rNegZero = -realZero;
	real rNeg = -0.01;
	
	CPPUNIT_ASSERT( gsl::sign( rPos ) == gsl::positive );
	CPPUNIT_ASSERT( gsl::sign( rZero ) == gsl::positive );
	CPPUNIT_ASSERT( gsl::sign( rNegZero ) == gsl::positive );
	CPPUNIT_ASSERT( gsl::sign( rNeg ) == gsl::negative );
}

////////////////////////////////////////////////////////////

void MathFunctionsTestSuite::Approximation()
{
	real x = 1;
	CPPUNIT_ASSERT( gsl::fcmp( x, realOne, 1e-15 ) == gsl::equal_to );
	CPPUNIT_ASSERT( gsl::fcmp( x + 5e-15, realOne, 1e-15 ) == gsl::greater_than );
	CPPUNIT_ASSERT( gsl::fcmp( x + 5e-15, realOne, 1e-14 ) == gsl::equal_to );
	CPPUNIT_ASSERT( gsl::fcmp( x - 5e-15, realOne, 1e-15 ) == gsl::less_than );
}

////////////////////////////////////////////////////////////

void MathFunctionsTestSuite::MinMaxOddEven()
{
	int i1 = 5;
	int i2 = 8;
	
	CPPUNIT_ASSERT( gsl::is_odd( i1 ) );
	CPPUNIT_ASSERT( ! gsl::is_even( i1 ) );
	CPPUNIT_ASSERT( gsl::is_even( i2 ) );
	CPPUNIT_ASSERT( ! gsl::is_odd( i2 ) );
	
	real r1 = 4.3232;
	real r2 = 9.2312;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( r1, gsl::min(r1, r2), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( r2, gsl::max(r1, r2), rTolerance );
}

////////////////////////////////////////////////////////////