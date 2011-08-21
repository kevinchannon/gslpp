#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "globals.h"

class SortTestSuite : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE ( SortTestSuite );

    CPPUNIT_TEST( VectorSortInPlace );
    CPPUNIT_TEST( VectorSortIndices );
    CPPUNIT_TEST( ArraySortInPlace );
    CPPUNIT_TEST( ArraySortIndices );

    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void VectorSortInPlace();
    void VectorSortIndices();
    void ArraySortInPlace();
    void ArraySortIndices();
};
