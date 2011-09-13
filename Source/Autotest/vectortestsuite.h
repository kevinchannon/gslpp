#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "globals.h"

class VectorTestSuite : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE ( VectorTestSuite );

	CPPUNIT_TEST( Initialise );
	CPPUNIT_TEST( AccessGSLVector );
    CPPUNIT_TEST( VectorsAreEqual );
    CPPUNIT_TEST( AddVector );
    CPPUNIT_TEST( SubtractVector );
    CPPUNIT_TEST( AddConstant );
    CPPUNIT_TEST( SubtractConstant );
    CPPUNIT_TEST( MultiplyConstant );
    CPPUNIT_TEST( DivideConstant );
    CPPUNIT_TEST( ElementwiseVectorMultiply );
    CPPUNIT_TEST( ElementwiseVectorDivide );
    CPPUNIT_TEST( MaxAndMin );
    CPPUNIT_TEST( Swap );
    CPPUNIT_TEST( Basis );
    CPPUNIT_TEST( STLCompatibility );
    CPPUNIT_TEST( Squeeze );
    CPPUNIT_TEST( AccessorsAndMutators );
    CPPUNIT_TEST( Performance );

    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
	void Initialise();
	void AccessGSLVector();
    void VectorsAreEqual();
    void AddVector();
    void SubtractVector();
    void AddConstant();
    void SubtractConstant();
    void MultiplyConstant();
    void DivideConstant();
    void ElementwiseVectorMultiply();
    void ElementwiseVectorDivide();
    void MaxAndMin();
    void Swap();
    void Basis();
    void STLCompatibility();
    void Squeeze();
    void AccessorsAndMutators();
    void Performance();
};
