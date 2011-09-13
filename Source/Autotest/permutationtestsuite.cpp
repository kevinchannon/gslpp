#include "permutationtestsuite.h"

#include <iostream>
#include <algorithm>
#include <iterator>

#include "gslpp/Permutation/permutation.h"
#include "gslpp/Permutation/permute.h"
#include "gslpp/Common/exceptions.h"

CPPUNIT_TEST_SUITE_REGISTRATION( PermutationTestSuite );

void PermutationTestSuite::setUp(){}

////////////////////////////////////////////////////////////

void PermutationTestSuite::tearDown(){}

////////////////////////////////////////////////////////////

void PermutationTestSuite::InitialisationTest()
{
    size_t iSize = 10;

    gsl::permutation p1;
    gsl::permutation p2( iSize );
    gsl::permutation p3( iSize, gsl::permutation::initialised );
    gsl::permutation p4( p3 );

    CPPUNIT_ASSERT ( p1.hasValue() == false );
    CPPUNIT_ASSERT ( p2.hasValue() == true );
    CPPUNIT_ASSERT ( p3.hasValue() == true );
    CPPUNIT_ASSERT ( p4.hasValue() == true );

    CPPUNIT_ASSERT ( p3 == p4 );

    for ( size_t i = 0; i < iSize; ++i )
        CPPUNIT_ASSERT ( p3[i] == i );
}

////////////////////////////////////////////////////////////

void PermutationTestSuite::AdvancePermutation()
{
    size_t iSize = 3;

    gsl::permutation p( iSize, gsl::permutation::initialised );
    size_t forwardResults[6][3] = { {0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0} };

    // Advance the permutation forwards
    size_t iPermutationNumber = 0;
    do{
        for ( size_t i = 0; i < iSize; ++i )
            CPPUNIT_ASSERT ( p[i] == forwardResults[ iPermutationNumber ][ i ] );
        ++iPermutationNumber;
    }while( p.next() );

    CPPUNIT_ASSERT ( iPermutationNumber == 6 );

    size_t reverseResults[6][3] = { {2, 1, 0}, {2, 0, 1}, {1, 2, 0}, {1, 0, 2}, {0, 2, 1}, {0, 1, 2} };

    // Advance the permutation in reverse
    iPermutationNumber = 0;
    do{
        for ( size_t i = 0; i < iSize; ++i )
            CPPUNIT_ASSERT ( p[i] == reverseResults[ iPermutationNumber ][ i ] );
        ++iPermutationNumber;
    }while( p.prev() );

    CPPUNIT_ASSERT ( iPermutationNumber == 6 );
}

////////////////////////////////////////////////////////////

void PermutationTestSuite::Inverse()
{
    size_t iSize = 5;
    gsl::permutation p_identity( iSize, gsl::permutation::initialised );
    gsl::permutation p_inverse( p_identity.inverse() );

    // The inverse of the identity permutation should be itself
    CPPUNIT_ASSERT ( p_inverse == p_identity );

    gsl::permutation p1( p_identity );
    // Advance the permutation to produce a non-identity permutation
    for ( size_t i = 0; i < 70; ++i )   p1.next();

    p_identity = p1*p1.inverse();

    // The product of the inverse and the original should be the identity permutation
    CPPUNIT_ASSERT ( p_identity == gsl::permutation( iSize, gsl::permutation::initialised ) );
}

////////////////////////////////////////////////////////////

void PermutationTestSuite::Accessors()
{
    size_t iSize = 5;
    gsl::permutation p( iSize, gsl::permutation::initialised );

    CPPUNIT_ASSERT_THROW ( p.at( 9 ), std::out_of_range );
    CPPUNIT_ASSERT ( p(  6 ) == p[ 1 ] );
    CPPUNIT_ASSERT ( p( -7 ) == p[ 4 ] );
}

////////////////////////////////////////////////////////////

void PermutationTestSuite::Vectors()
{
    size_t iSize = 5;
    gsl::permutation p( iSize, gsl::permutation::initialised );

    gsl::vector< real > v( iSize );

    real i = 0.0;
    for ( gsl::vector< real >::iterator it_v = v.begin(); it_v != v.end(); ++it_v, ++i )
        *it_v = i;

    // Advance the permutation to produce a non-identity permutation
    for ( size_t i = 0; i < 70; ++i )   p.next();

    gsl::vector< real > w = p*v;

    w = p.inverse()*w;

    i = 0.0;
    for ( gsl::vector< real >::iterator it_v = v.begin(); it_v != v.end(); ++it_v, ++i )
        CPPUNIT_ASSERT_EQUAL ( i, *it_v );

    gsl::permute::vector( p, v );
    gsl::permute::vectorInverse( p, v);

    i = 0.0;
    for ( gsl::vector< real >::iterator it_v = v.begin(); it_v != v.end(); ++it_v, ++i )
        CPPUNIT_ASSERT_EQUAL ( i, *it_v );
}

////////////////////////////////////////////////////////////
