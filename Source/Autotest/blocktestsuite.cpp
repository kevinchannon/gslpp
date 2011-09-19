#include "blocktestsuite.h"

#include "gslpp/Block/block.h"
#include "gslpp/Complex/complex.h"

#include <gsl/gsl_block.h>

CPPUNIT_TEST_SUITE_REGISTRATION( BlockTestSuite );

void BlockTestSuite::setUp(){}

////////////////////////////////////////////////////////////

void BlockTestSuite::tearDown(){}

////////////////////////////////////////////////////////////

void BlockTestSuite::Instantiation()
{
	gsl::block< int > b1(20);
	CPPUNIT_ASSERT( b1.size() == 20 );
	gsl::block<> b2(100);
	CPPUNIT_ASSERT( b2.size() == 100 );
	
	gsl_block* gsl_b = gsl_block_alloc( 10 );
	for ( size_t i = 0; i < 10; ++i )
		gsl_b->data[i] = 9.9 + i;
	
	gsl::block<> b3( gsl_b );
	CPPUNIT_ASSERT( b3.size() == gsl_b->size );
	for ( size_t i = 0; i < 10; ++i )
		CPPUNIT_ASSERT_DOUBLES_EQUAL( gsl_b->data[i], b3[i], 1e-15 );
		
	gsl::block<> b4( b3 );
	CPPUNIT_ASSERT( b4.size() == b3.size() );
	for ( size_t i = 0; i < 10; ++i )
		CPPUNIT_ASSERT_DOUBLES_EQUAL( b4[i], b3[i], 1e-15 );
		
	gsl::block< char > b5;
	CPPUNIT_ASSERT( b5.size() == 0 );
	
	gsl::block<unsigned long> b6( 10, 1 );
	CPPUNIT_ASSERT( b6.size() == 10 );
	for ( size_t i = 0; i < 10; ++i )
		CPPUNIT_ASSERT( 1 == b6[i] );
		
	gsl::block< gsl::complex > b7(20);
}

////////////////////////////////////////////////////////////

void BlockTestSuite::GSLCompatibility()
{
	gsl::block<> b(100);
	gsl_block* gsl_b1 = b.as_gsl_block();
	for ( size_t i = 0; i < 100; ++i )	gsl_b1->data[i] = 10;
	for ( size_t i = 0; i < 100; ++i )	CPPUNIT_ASSERT_DOUBLES_EQUAL( 10.0, b[i], 1e-15);
	
	gsl_block* gsl_b2 = b.to_gsl_block();
	for ( size_t i = 0; i < 100; ++i )	gsl_b2->data[i] = 20;
	for ( size_t i = 0; i < 100; ++i )	CPPUNIT_ASSERT_DOUBLES_EQUAL( 10.0, b[i], 1e-15);
}

////////////////////////////////////////////////////////////