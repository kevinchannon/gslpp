#include "blocktestsuite.h"

#include "gslpp/Block/block.h"

CPPUNIT_TEST_SUITE_REGISTRATION( BlockTestSuite );

void BlockTestSuite::setUp(){}

////////////////////////////////////////////////////////////

void BlockTestSuite::tearDown(){}

////////////////////////////////////////////////////////////

void BlockTestSuite::Instantiation()
{
	gsl::block< int > b1(20);
	gsl::block<> b2(100);
}

////////////////////////////////////////////////////////////