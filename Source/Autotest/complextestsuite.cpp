#include "complextestsuite.h"

#include <cmath>

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
	real z_x_1 = z_x*c - z_y*d;
	real z_y_1 = z_x*d + z_y*c;
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_x_1, z3.x(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_y_1, z3.y(), 1e-14 );
	
	z3 /= z2;
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_x, z3.x(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_y, z3.y(), 1e-14 );
	
	// complex - real arithmetic
	gsl::complex z4 = z3 + c;
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_x + c, z4.x(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_y, z4.y(), 1e-14 );
	
	z4 = z3 - d;
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_x - d, z4.x(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_y, z4.y(), 1e-14 );
	
	z4 = z3 * b;
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_x * b, z4.x(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_y * b, z4.y(), 1e-14 );
	
	z4 = z3 / a;
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_x / a, z4.x(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_y / a, z4.y(), 1e-14 );
	
	z4 += a;
	z_x += a;
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_x, z4.x(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_y, z4.y(), 1e-14 );
	
	z4 -= d;
	z_x -= d;
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_x, z4.x(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_y, z4.y(), 1e-14 );
	
	z4 *= b;
	z_x *= b;
	z_y *= b;
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_x, z4.x(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_y, z4.y(), 1e-14 );
	
	z4 /= c;
	z_x /= c;
	z_y /= c;
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_x, z4.x(), 1e-14 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( z_y, z4.y(), 1e-14 );
}

////////////////////////////////////////////////////////////

void ComplexTestSuite::ElementaryFunctions()
{
	real rTolerance = 1e-14;
	
	real a = 1;
	real b = 2;
	gsl::complex z1(a,b);
	
	// Power functions
	real r = std::sqrt( a*a + b*b );
	real q = std::atan( b / a );
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL( std::sqrt(r), gsl::sqrt(z1).abs(), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.5*q, gsl::sqrt(z1).arg(), rTolerance );
	
	real c = -4;
	CPPUNIT_ASSERT_DOUBLES_EQUAL( std::sqrt( fabs(c) ), gsl::sqrt( c ).y(), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0, gsl::sqrt( c ).x(), rTolerance );
	
	gsl::complex z2(b,a);
	gsl::complex z3 = gsl::pow( z1, z2 );
	
	real r3 = std::exp( z2.x()*std::log( z1.abs() ) - z1.arg()*z2.y() );
	real q3 = z1.arg()*z2.x() + z2.y()*std::log( z1.abs() );
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL( r3, z3.abs(), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( q3, z3.arg(), rTolerance );
	
	gsl::complex z4 = gsl::pow( z3, c );
	real q4 = z3.arg()*c;
	// unwind the argument, so that it's -pi < x <= pi
	const real pi = 3.14159265358979323846;
	q4 = q4 - pi * static_cast< int >( q4 / (pi) ) + pi; 
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL( std::pow( z3.abs(), c), z4.abs(), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( q4, z4.arg(), rTolerance );
	
	// Exponentials
	gsl::complex z5 = gsl::exp( z4 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.12334173203738, z5.x(), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0710310274678569, z5.y(), rTolerance );
	
	gsl::complex z6 = gsl::log( z1 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.80471895621705, z6.x(), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.10714871779409, z6.y(), rTolerance );
	CPPUNIT_ASSERT( z6 == gsl::ln( z1 ) );
	
	gsl::complex z7 = gsl::log10( z2 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.349485002168009, z7.x(), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.201359598136687, z7.y(), rTolerance );
	
	gsl::complex z8 = gsl::log_b( z4, z5 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( -11.4955609428967, z8.x(), 100*rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 10.2805834567583, z8.y(), rTolerance );
}

////////////////////////////////////////////////////////////

