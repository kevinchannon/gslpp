#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "globals.h"

class MatrixTestSuite : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE ( MatrixTestSuite );

	CPPUNIT_TEST ( Construction );
	CPPUNIT_TEST ( MatricesAreEqual );
	CPPUNIT_TEST ( ElementAccess );
    CPPUNIT_TEST ( ElementwiseArithmetic );
    CPPUNIT_TEST ( RowsColsAndDiagonals );
	CPPUNIT_TEST ( MatrixMatrixMultiplication );
	CPPUNIT_TEST ( MatrixVectorMultiplication );
	CPPUNIT_TEST ( Transpose );
	CPPUNIT_TEST ( SwapRowsAndCols );
	CPPUNIT_TEST ( MinMax );
	CPPUNIT_TEST ( RealBooleanComparisons );
//    CPPUNIT_TEST ( Swap );

    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
	void Construction();
    void MatricesAreEqual();
	void ElementAccess();
    void ElementwiseArithmetic();
    void RowsColsAndDiagonals();
	void MatrixMatrixMultiplication();
	void MatrixVectorMultiplication();
	void Transpose();
	void SwapRowsAndCols();
	void MinMax();
	void RealBooleanComparisons();
//    void Swap();
};
