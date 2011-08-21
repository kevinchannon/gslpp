#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "globals.h"

class PermutationTestSuite : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE ( PermutationTestSuite );

    CPPUNIT_TEST ( InitialisationTest );
    CPPUNIT_TEST ( AdvancePermutation );
    CPPUNIT_TEST ( Inverse );
    CPPUNIT_TEST ( Accessors );
    CPPUNIT_TEST ( Vectors );

    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:

    void InitialisationTest();
    void AdvancePermutation();
    void Inverse();
    void Accessors();
    void Vectors();
};
