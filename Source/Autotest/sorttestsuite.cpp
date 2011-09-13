#include "sorttestsuite.h"

#include "gslpp/Vector/vector.h"
#include "gslpp/Common/exceptions.h"
#include "gslpp/Sort/sort.h"
#include "gslpp/Permutation/permutation.h"

CPPUNIT_TEST_SUITE_REGISTRATION( SortTestSuite );

void SortTestSuite::setUp(){}

void SortTestSuite::tearDown(){}

void SortTestSuite::VectorSortInPlace()
{
    size_t iVectorSize = 10;
    real rMultiplier = 0.938243247;
    gsl::vector< real > vec( iVectorSize );

    for ( int i = 10; i > 0; --i )
        vec[10 - i] = i*rMultiplier;

    gsl::sort( vec );

    for ( size_t i = 0; i < iVectorSize; ++i )
        CPPUNIT_ASSERT_DOUBLES_EQUAL( (i + 1)*rMultiplier, vec[i], rTolerance );
}

void SortTestSuite::VectorSortIndices()
{
    const size_t ciVectorSize = 10;
    real rMultiplier = 0.938243247;
    gsl::vector< real > vec( ciVectorSize );
    gsl::permutation p( vec.size() );

    for ( int i = 10; i > 0; --i )
        vec(10 - i) = i*rMultiplier;

    gsl::sort(p, vec);

    for ( size_t i = 0; i < ciVectorSize; ++i ){
        int expected = ciVectorSize - 1 - i;
        int actual = p[i];
        CPPUNIT_ASSERT_EQUAL( expected, actual );
    }
}

void SortTestSuite::ArraySortInPlace()
{
    size_t iArraySize = 10;
    real rMultiplier = 0.938243247;
    real *data = new real[ iArraySize ];

    for ( int i = 10; i > 0; --i )
        data[10 - i] = i*rMultiplier;

    gsl::sort(data, iArraySize );

    for ( size_t i = 0; i < iArraySize; ++i )
        CPPUNIT_ASSERT_DOUBLES_EQUAL( (i + 1)*rMultiplier, data[i], rTolerance );
}

void SortTestSuite::ArraySortIndices()
{
    const int ciArraySize = 10;
    const real crMultiplier = 0.938243247;
    real *data = new real[ ciArraySize ];
    size_t *perm = new size_t[ ciArraySize ];

    for ( int i = 0; i < ciArraySize; ++i )
        data[ciArraySize - i - 1] = i*crMultiplier;

    gsl::sort(perm, data, ciArraySize );

    for ( int i = 0; i < ciArraySize; ++i ){
        int expected = ciArraySize - 1 - i;
        int actual = perm[i];
        CPPUNIT_ASSERT_EQUAL( expected, actual );
    }
}
