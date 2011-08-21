#include "combinationtestsuite.h"

#include "gslpp/Combination/combination.h"

CPPUNIT_TEST_SUITE_REGISTRATION( CombinationTestSuite );

void CombinationTestSuite::setUp(){}

////////////////////////////////////////////////////////////

void CombinationTestSuite::tearDown(){}

////////////////////////////////////////////////////////////

void CombinationTestSuite::InitialisationTest()
{
    gsl::combination::value_type n = 10;
	gsl::combination::value_type k = 5;

    gsl::combination c1;
    gsl::combination c2( n, k );
    gsl::combination c3( c2 );

    CPPUNIT_ASSERT ( c1.hasValue() == false );
    CPPUNIT_ASSERT ( c2.hasValue() == true );
    CPPUNIT_ASSERT ( c3.hasValue() == true );

	for ( size_t i = 0; i < k; ++i )
		CPPUNIT_ASSERT ( c2[i] == i );

    CPPUNIT_ASSERT ( c2 == c3 );
	CPPUNIT_ASSERT ( c2 != c1 );
	
	c1.redefine(n, k);
	c1.next();
	c1.set_first();
	CPPUNIT_ASSERT ( c1 == c2 );
	c1.set_last();
	
	for ( size_t i = 0; i < k; ++i )
		CPPUNIT_ASSERT ( c1[i] == i + 5);
}

////////////////////////////////////////////////////////////

void CombinationTestSuite::Advance()
{
	gsl::combination::value_type n = 3;
	gsl::combination::value_type k = 2;

    gsl::combination c1( n, k );
	
	CPPUNIT_ASSERT ( c1[0] == 0 );
	CPPUNIT_ASSERT ( c1[1] == 1 );
	CPPUNIT_ASSERT ( c1.next() );
	
	CPPUNIT_ASSERT ( c1[0] == 0 );
	CPPUNIT_ASSERT ( c1[1] == 2 );
	CPPUNIT_ASSERT ( c1.next() );
	
	CPPUNIT_ASSERT ( c1[0] == 1 );
	CPPUNIT_ASSERT ( c1[1] == 2 );
	CPPUNIT_ASSERT ( !c1.next() );
	
	CPPUNIT_ASSERT ( c1.prev() );
	CPPUNIT_ASSERT ( c1[0] == 0 );
	CPPUNIT_ASSERT ( c1[1] == 2 );
	
	CPPUNIT_ASSERT ( c1.prev() );
	CPPUNIT_ASSERT ( c1[0] == 0 );
	CPPUNIT_ASSERT ( c1[1] == 1 );
}

////////////////////////////////////////////////////////////

void CombinationTestSuite::ElementAccess()
{
	gsl::combination::value_type n = 3;
	gsl::combination::value_type k = 2;

    gsl::combination c( n, k );
	
	CPPUNIT_ASSERT ( c[0] == 0 );
	CPPUNIT_ASSERT ( c[1] == 1 );
	
	CPPUNIT_ASSERT ( c(1) == c[1] );
	CPPUNIT_ASSERT ( c(-1) == c(1) );
	CPPUNIT_ASSERT ( c(2) == c[0] );
	CPPUNIT_ASSERT ( c(3) == c[1] );
	
	CPPUNIT_ASSERT ( c.at(0) == c[0] );
	CPPUNIT_ASSERT_THROW ( c.at(2), std::out_of_range );
}

////////////////////////////////////////////////////////////

void CombinationTestSuite::Properties()
{
	gsl::combination::value_type n = 49;
	gsl::combination::value_type k = 6;

    gsl::combination c( n, k );
	
	CPPUNIT_ASSERT ( c.isValid() );
	
	CPPUNIT_ASSERT ( c.n() == n );
	CPPUNIT_ASSERT ( c.k() == k );
	
	CPPUNIT_ASSERT ( c.count() == 13983816.0 );
}

////////////////////////////////////////////////////////////
