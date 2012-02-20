#include "polynomialtestsuite.h"

#include <iostream>
#include <iterator>
#include <complex>
#include <algorithm>

#include "gslpp/Polynomial/polynomial.h"
#include "gslpp/Vector/vector.h"

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
	gsl::polynomial p1( 1.2, 2.5, -15, 6.9 );
	gsl::polynomial p2( 1,5.6 );
	gsl::polynomial p3( 1.5 + 3i, 2.0, 4.2i );
	
	std::vector< gsl::polynomial::value_type > std_vz( 4, 1 + 3i );
	gsl::polynomial p4( std_vz );
	
	std::vector< real > std_vr( 4, 2 );
	gsl::polynomial p5( std_vr );
	
	std::vector< gsl::polynomial::value_type > gsl_vz( 4, 2 + 2.5i );
	gsl::polynomial p6( gsl_vz );
	
	gsl::vector< real > gsl_vr( 5, 1 );
	gsl::polynomial p7(gsl_vr);
	
	gsl::polynomial::size_type N = 10;
	
	gsl::polynomial::value_type* az = new gsl::polynomial::value_type[ N ];
	std::fill(az, az + N, 3.1 + 2i );
	gsl::polynomial p9( az, N );
	delete[] az;
	
	real* ar = new real[ N ];
	std::fill(ar, ar + N, 4.5 );
	gsl::polynomial p10( ar, N );
	delete[] ar;
}

////////////////////////////////////////////////////////////

void PolynomialTestSuite::Assignment()
{
	gsl::polynomial p1;
	std::vector< real > std_v(4,1);
	p1 = std_v;
	CPPUNIT_ASSERT( p1.size() == 3 );
	CPPUNIT_ASSERT( p1.order() == 3 );
	CPPUNIT_ASSERT( std::equal( std_v.begin(), std_v.end(), p1.coeff_begin() ) );
	
	gsl::polynomial p2 = p1;
	CPPUNIT_ASSERT( p2.size() == 3 );
	CPPUNIT_ASSERT( p2.order() == 3 );
	CPPUNIT_ASSERT( std::equal( p1.coeff_begin(), p1.coeff_end(), p2.coeff_begin() ) );
	
	gsl::vector< real > gsl_v( 5, 2);
	p1 = gsl_v;
	CPPUNIT_ASSERT( p1.size() == 4 );
	CPPUNIT_ASSERT( p1.order() == 4 );
	CPPUNIT_ASSERT( std::equal( gsl_v.begin(), gsl_v.end(), p1.coeff_begin() ) );
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

void PolynomialTestSuite::Order()
{
	gsl::polynomial p1( 1, 3.2, 1.1 );
	CPPUNIT_ASSERT( 2 == p1.order() );
	
	gsl::polynomial p2( 0, 0, 1.2 );
	CPPUNIT_ASSERT( 2 == p2.order() );
	
	gsl::polynomial p3( 2.3, 1.4, 0, 0, 1.2 );
	CPPUNIT_ASSERT( 4 == p3.order() );
	
	gsl::polynomial p4( 4.1, 0, 0, 5.2, 0, 0, 0 );
	CPPUNIT_ASSERT( 3 == p4.order() );
	
	gsl::polynomial p5( 1+2i, 3.2+1i, 1.1 );
	CPPUNIT_ASSERT( 2 == p5.order() );
	
	gsl::polynomial p6( 0, 0+1.4i, 1.2 );
	CPPUNIT_ASSERT( 2 == p6.order() );
	
	gsl::polynomial p7( 2.3+9.8i, 1.4, 0, 0+3.1i, 1.2+2i );
	CPPUNIT_ASSERT( 4 == p7.order() );
	
	gsl::polynomial p8( 4.1, 0+0.1i, 0, 5.2, 0+1i, 0, 0 );
	CPPUNIT_ASSERT( 4 == p8.order() );
}

////////////////////////////////////////////////////////////

void PolynomialTestSuite::Resize()
{
	gsl::polynomial p1;
	CPPUNIT_ASSERT( p1.order() == 0 );
	CPPUNIT_ASSERT( p1.size() == gsl::polynomial::empty );
	
	p1.add_term( 0.1 );
	CPPUNIT_ASSERT( p1.order() == 0 );
	CPPUNIT_ASSERT( p1.size() == 0 );
	
	p1.add_term( 0.3 );
	CPPUNIT_ASSERT( p1.order() == 1 );
	CPPUNIT_ASSERT( p1.size() == 1 );
	
	p1.resize( 5 );
	CPPUNIT_ASSERT( p1.order() == 1 );
	CPPUNIT_ASSERT( p1.size() == 5 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.1, p1.coeff(0).real(), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.3, p1.coeff(1).real(), rTolerance );
	
	p1.coeff(5) = 1+2i;
	CPPUNIT_ASSERT( 5 == p1.order() );
	CPPUNIT_ASSERT( p1.size() == 5 );
	
	p1.resize(1);
	CPPUNIT_ASSERT( p1.order() == 1 );
	CPPUNIT_ASSERT( p1.size() == 1 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.1, p1.coeff(0).real(), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.3, p1.coeff(1).real(), rTolerance );
}

////////////////////////////////////////////////////////////

void PolynomialTestSuite::OperatorOverloads()
{
	gsl::polynomial p1(1,2,3,4,5);
	gsl::polynomial p2 = -p1;
	
	for ( size_t i = 0; i < 5; ++i ){
		CPPUNIT_ASSERT( p1[i] == -p2[i] );
	}
	
	gsl::polynomial p3( -1+2i, 3, 0, 1.2+3.1i );
	gsl::polynomial p4( 2i, 5, 3, 5.2+3.1i, 5 );
	
	p3 += p1;
	CPPUNIT_ASSERT( p3 == p4 );
	
	gsl::polynomial p5( 2i, 5, 3, 5.2+3.1i, 5 );
	gsl::polynomial p6( 0, 0, 0, 0, 0 );
	p4 -= p5;
	CPPUNIT_ASSERT( p4 == p6 );
	
	gsl::polynomial p7( 2, 3i, 1 + 1i );
	gsl::polynomial p8( 1, 4i );
//	p7 *= p8;
	
//	gsl::polynomial p9( 2, 11i, -11 + 1i, -4 + 4i);
//	CPPUNIT_ASSERT( p7 == p9 );
}

////////////////////////////////////////////////////////////

void PolynomialTestSuite::SolveConstant()
{
	gsl::polynomial p1;
	std::vector< gsl::polynomial::value_type > vRoots = p1.roots();
	CPPUNIT_ASSERT( vRoots.empty() );
	
	p1.add_term( 1 );
	vRoots = p1.roots();
	CPPUNIT_ASSERT( vRoots.empty() );
	
	p1.coeff(0) = 1i;
	vRoots = p1.roots();
	CPPUNIT_ASSERT( vRoots.empty() );
	
	p1.coeff(0) = 1+2i;
	vRoots = p1.roots();
	CPPUNIT_ASSERT( vRoots.empty() );
}

////////////////////////////////////////////////////////////

void PolynomialTestSuite::SolveLinear()
{
	gsl::polynomial p1( 1, 1 );
	std::vector< gsl::polynomial::value_type > vRoots = p1.roots();
	CPPUNIT_ASSERT( vRoots.size() == 1 );
	CPPUNIT_ASSERT( vRoots[0] == gsl::polynomial::value_type(-1, 0) );
	
	p1.coeff(0) = 1+2i;
	vRoots = p1.roots();
	CPPUNIT_ASSERT( vRoots.size() == 1 );
	CPPUNIT_ASSERT( vRoots[0] == gsl::polynomial::value_type(-1, -2) );
}

////////////////////////////////////////////////////////////

void PolynomialTestSuite::SolveQuadratic()
{
	gsl::polynomial p1(2,-3,1);
	std::vector< gsl::polynomial::value_type > vRoots = p1.roots();
	CPPUNIT_ASSERT( vRoots.size() == 2 );
	CPPUNIT_ASSERT( vRoots[0] == gsl::polynomial::value_type(1, 0) );
	CPPUNIT_ASSERT( vRoots[1] == gsl::polynomial::value_type(2, 0) );
	
	p1[0] = 0;
	p1[1] = 0;
	vRoots = p1.roots();
	CPPUNIT_ASSERT( vRoots.size() == 2 );
	CPPUNIT_ASSERT( vRoots[0] == gsl::polynomial::value_type(0, 0) );
	CPPUNIT_ASSERT( vRoots[1] == gsl::polynomial::value_type(0, 0) );
	
	p1[0] = 1;
	vRoots = p1.roots();
	CPPUNIT_ASSERT( vRoots.size() == 2 );
	CPPUNIT_ASSERT( vRoots[0] == gsl::polynomial::value_type(0, -1) );
	CPPUNIT_ASSERT( vRoots[1] == gsl::polynomial::value_type(0, 1) );
	
	p1[1] = 1+1i;
	vRoots = p1.roots();
	CPPUNIT_ASSERT( vRoots.size() == 0 );
}

////////////////////////////////////////////////////////////

void PolynomialTestSuite::SolveCubic()
{
	gsl::polynomial p1( -6, 11, -6, 1 );
	std::vector< gsl::polynomial::value_type > vRoots = p1.roots();
	CPPUNIT_ASSERT( vRoots.size() == 3 );
	CPPUNIT_ASSERT( vRoots[0] == gsl::polynomial::value_type(1, 0) );
	CPPUNIT_ASSERT( vRoots[1] == gsl::polynomial::value_type(2, 0) );
	CPPUNIT_ASSERT( vRoots[2] == gsl::polynomial::value_type(3, 0) );
	
	p1[0] =  0;
	p1[1] =  0;
	p1[2] = -1;
	vRoots = p1.roots();
	CPPUNIT_ASSERT( vRoots.size() == 3 );
	CPPUNIT_ASSERT( vRoots[0] == gsl::polynomial::value_type(0, 0) );
	CPPUNIT_ASSERT( vRoots[1] == gsl::polynomial::value_type(0, 0) );
	CPPUNIT_ASSERT( vRoots[2] == gsl::polynomial::value_type(1, 0) );
	
	p1[0] = 1;
	p1[1] = 0;
	p1[2] = 0;
	vRoots = p1.roots();
	CPPUNIT_ASSERT( vRoots.size() == 3 );
	CPPUNIT_ASSERT( vRoots[0] == gsl::polynomial::value_type(-1, 0) );
	CPPUNIT_ASSERT( vRoots[1] == gsl::polynomial::value_type(0.5, -gsl::sqrt3 / 2) );
	CPPUNIT_ASSERT( vRoots[2] == gsl::polynomial::value_type(0.5,  gsl::sqrt3 / 2) );
}

////////////////////////////////////////////////////////////

void PolynomialTestSuite::SolveHighOrder()
{
	gsl::polynomial p1( 1, 0, 0, 0, 1 );
	std::vector< gsl::polynomial::value_type > vRoots = p1.roots();
	CPPUNIT_ASSERT( vRoots.size() == 4);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( -gsl::sqrt_half, vRoots[0].real(), M_tolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(  gsl::sqrt_half, vRoots[0].imag(), M_tolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( -gsl::sqrt_half, vRoots[1].real(), M_tolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( -gsl::sqrt_half, vRoots[1].imag(), M_tolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(  gsl::sqrt_half, vRoots[2].real(), M_tolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(  gsl::sqrt_half, vRoots[2].imag(), M_tolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(  gsl::sqrt_half, vRoots[3].real(), M_tolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( -gsl::sqrt_half, vRoots[3].imag(), M_tolerance);
}

////////////////////////////////////////////////////////////