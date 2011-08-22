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

