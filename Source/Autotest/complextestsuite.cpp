#include "complextestsuite.h"

#include "gslpp/Common/number.h"
#include "gslpp/Complex/complex.h"

////////////////////////////////////////////////////////////

CPPUNIT_TEST_SUITE_REGISTRATION( ComplexTestSuite );

////////////////////////////////////////////////////////////

void ComplexTestSuite::setUp(){}

////////////////////////////////////////////////////////////

void ComplexTestSuite::tearDown(){}

////////////////////////////////////////////////////////////

void ComplexTestSuite::Construction()
{
	gsl::complex z1;
	gsl::complex z2( 1.3, 2.1 );
	
	CPPUNIT_ASSERT ( z2.x() == 1.3 );
	CPPUNIT_ASSERT ( z2.y() == 2.1 );
	
	z1 = z2;
	
	CPPUNIT_ASSERT ( z1.x() == 1.3 );
	CPPUNIT_ASSERT ( z1.y() == 2.1 );
	
	gsl::complex z3( 4.5 );
	
	CPPUNIT_ASSERT ( z3.x() == 4.5 );
	CPPUNIT_ASSERT ( z3.y() == realZero );
	
	real r = z2;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( sqrt(1.3*1.3 + 2.1*2.1), r, 1e-15 );
}

////////////////////////////////////////////////////////////

void ComplexTestSuite::Properties()
{
	gsl::complex z( 1.3, 2.1 );
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( sqrt(1.3*1.3 + 2.1*2.1), z.abs(), 1e-15 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( (1.3*1.3 + 2.1*2.1), z.abs2(), 1e-15 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0.904144385589633, z.log_abs(), 1e-15 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 1.01648883059335, z.arg(), 1e-14 );
	
	z.abs( 2 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 2.0, z.abs(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 1.01648883059335, z.arg(), 1e-14 );
	
	z.arg( 1.8 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 2.0, z.abs(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 1.8, z.arg(), 1e-14 );
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( -0.454404189386174, z.x(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 1.94769526175639, z.y(), 1e-14 );
}

////////////////////////////////////////////////////////////

void ComplexTestSuite::Equality()
{
	gsl::complex z1(1.2, 3.2);
	gsl::complex z2(1.2, 3.2);
	gsl::complex z3(3.4, 6.3);
	gsl::complex z4( z3 );
	
	CPPUNIT_ASSERT ( z1 == z2 );
	CPPUNIT_ASSERT ( z1 != z3 );
	CPPUNIT_ASSERT ( z4 == z3 );
	
	CPPUNIT_ASSERT ( z3 > z1 );
	CPPUNIT_ASSERT ( z3 <= z4 );
	CPPUNIT_ASSERT ( z2 <= z3 );
	CPPUNIT_ASSERT ( z2 < z4 );
	CPPUNIT_ASSERT ( z3 >= z1 );
	CPPUNIT_ASSERT ( z3 >= z2 );
}

////////////////////////////////////////////////////////////

void ComplexTestSuite::Arithmetic()
{
	real a = 1;
	real b = 2;
	real c = 2;
	real d = 3;
	gsl::complex z1( a, b );
	gsl::complex z2( c, d );
	
	// complex - complex arithmetic
	gsl::complex z3 = z1 + z2;
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( a + c, z3.x(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( b + d, z3.y(), 1e-14 );
	
	z3 = z1 - z2;
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( a - c, z3.x(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( b - d, z3.y(), 1e-14 );
	
	z3 = z1*z2;
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( a*c - b*d, z3.x(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( c*b + a*d, z3.y(), 1e-14 );
	
	z3 = z1/z2;
	real z_x = (c*a + b*d)/(c*c + d*d);
	real z_y = (b*c - a*d)/(c*c + d*d);
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_x, z3.x(), 1e-15 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_y, z3.y(), 1e-15 );
	
	z3 += z2;
	z_x += c;
	z_y += d;
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_x, z3.x(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_y, z3.y(), 1e-14 );
	
	z3 -= z1;
	z_x -= a;
	z_y -= b;
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_x, z3.x(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_y, z3.y(), 1e-14 );
	
	z3 *= z2;
	z_x = z_x*c - z_y*d;
	z_y = z_x*d + z_y*c;
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_x, z3.x(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_y, z3.y(), 1e-14 );
	
	// complex - real arithmetic
}

////////////////////////////////////////////////////////////

