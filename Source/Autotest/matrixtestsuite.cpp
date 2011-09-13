#include "matrixtestsuite.h"

#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <numeric>
#include <functional>

#include "gslpp/Common/number.h"
#include "gslpp/Vector/vector.h"
#include "gslpp/Common/exceptions.h"
#include "gslpp/Matrix/matrix.h"

////////////////////////////////////////////////////////////

CPPUNIT_TEST_SUITE_REGISTRATION( MatrixTestSuite );

////////////////////////////////////////////////////////////

void MatrixTestSuite::setUp(){}

////////////////////////////////////////////////////////////

void MatrixTestSuite::tearDown(){}

////////////////////////////////////////////////////////////

void MatrixTestSuite::Construction()
{
	const int iRows = 10;
	const int iCols = 5;

	gsl::realMatrix m_1( iRows, iCols, 1 );
	gsl::realMatrix m_2( m_1 );
	
	CPPUNIT_ASSERT( m_1.rows() == m_2.rows() );
	CPPUNIT_ASSERT( m_1.cols() == m_2.cols() );
	
	for ( gsl::realMatrix::const_iterator it_1 = m_1.cbegin(), it_2 = m_2.cbegin(); it_1 != m_1.cend(); ++it_1, ++it_2 )
		CPPUNIT_ASSERT( *it_1 == *it_2 );
		
	gsl::realMatrix m_3( m_1.const_ptr() );
	
	CPPUNIT_ASSERT( m_1.rows() == m_3.rows() );
	CPPUNIT_ASSERT( m_1.cols() == m_3.cols() );
	
	for ( gsl::realMatrix::const_iterator it_1 = m_1.cbegin(), it_3 = m_3.cbegin(); it_1 != m_1.cend(); ++it_1, ++it_3 )
		CPPUNIT_ASSERT( *it_1 == *it_3 );
}

////////////////////////////////////////////////////////////

void MatrixTestSuite::MatricesAreEqual()
{
	typedef gsl::realMatrix::element_type xy;
    const int iRows = 10;
    const int iCols = 5;

    gsl::realMatrix m_1( iRows, iCols, 1 );
    gsl::realMatrix m_2( iRows, iCols, 1 );
	gsl::realMatrix m_3( iRows, iCols, 2 );
	gsl::realMatrix m_4( iRows - 1, iCols - 1, 1);
	
	for ( size_t i = 0; i < m_1.rows(); ++i ){
        for ( size_t j = 0; j < m_1.cols(); ++j ){
            CPPUNIT_ASSERT ( m_1[ xy( i, j) ] == 1 );
			CPPUNIT_ASSERT ( m_2[ xy( i, j) ] == 1 );
			CPPUNIT_ASSERT ( m_3[ xy( i, j) ] == 2 );
        }
    }
	for ( size_t i = 0; i < m_4.rows(); ++i ){
        for ( size_t j = 0; j < m_4.cols(); ++j ){
            CPPUNIT_ASSERT ( m_4[ xy( i, j) ] == 1 );
        }
    }
	 
	CPPUNIT_ASSERT( m_1 == m_2 );
	CPPUNIT_ASSERT( m_1 != m_3 );
	CPPUNIT_ASSERT( m_2 != m_3 );
	CPPUNIT_ASSERT( m_1 != m_4 );
}

////////////////////////////////////////////////////////////

void MatrixTestSuite::ElementAccess()
{
	typedef gsl::realMatrix::element_type xy;
	gsl::realMatrix A(3,3);
	
	// Put some values into the matrix
	size_t i = 0;
	gsl::realMatrix::iterator it_A = A.begin();
	while ( it_A != A.end() )
		*it_A++ = static_cast< gsl::realMatrix::value_type>( i++ );
		
	CPPUNIT_ASSERT( A[ xy(1,1) ] == 4 );
	
	i = 0;
	for ( size_t r = 0; r < A.rows(); ++r )
		for ( size_t c = 0; c < A.cols(); ++c )
			A[ xy(r,c) ] = i++;	
	
	CPPUNIT_ASSERT( A[ xy(1,1) ] == 4 );
	
	i = 0;
	for ( size_t r = 0; r < A.rows(); ++r )
		for ( size_t c = 0; c < A.cols(); ++c )
			A(r,c) = i++;
	
	CPPUNIT_ASSERT( A(0,1) == 1 );
	CPPUNIT_ASSERT( A(2,2) == 8 );	
	CPPUNIT_ASSERT( A(-1,-1) == A(2,2) );
	CPPUNIT_ASSERT( A(10,20) == A(1,2) );
	
	i = 0;
	for ( size_t r = 0; r < A.rows(); ++r )
		for ( size_t c = 0; c < A.cols(); ++c )
			A.at(r,c) = i++;
			
	CPPUNIT_ASSERT( A.at(0,2) == 2 );
	CPPUNIT_ASSERT_THROW( A.at(3,3), std::out_of_range );
}

////////////////////////////////////////////////////////////

void MatrixTestSuite::ElementwiseArithmetic()
{
    typedef gsl::realMatrix::element_type xy;

    const int iRows = 10;
    const int iCols = 5;

    gsl::realMatrix mat_1( iRows, iCols, 2 );
    gsl::realMatrix mat_2( iRows, iCols, 5 );

    gsl::realMatrix result = mat_1 + mat_2;

    for ( size_t i = 0; i < mat_1.rows(); ++i ){
        for ( size_t j = 0; j < mat_1.cols(); ++j ){
            CPPUNIT_ASSERT ( result[ xy( i, j) ] == 7 );
        }
    }
	
	result = 3 + mat_1 + 2;

    for ( size_t i = 0; i < mat_1.rows(); ++i ){
        for ( size_t j = 0; j < mat_1.cols(); ++j ){
            CPPUNIT_ASSERT ( result[ xy( i, j) ] == 7 );
        }
    }

    // Subtract matrices
    result = mat_1 - mat_2;

    for ( size_t i = 0; i < mat_1.rows(); ++i ){
        for ( size_t j = 0; j < mat_1.cols(); ++j ){
            CPPUNIT_ASSERT ( result[ xy( i, j) ] == -3 );
        }
    }
	
	result = 3 - mat_1 - 2;

    for ( size_t i = 0; i < mat_1.rows(); ++i ){
        for ( size_t j = 0; j < mat_1.cols(); ++j ){
            CPPUNIT_ASSERT ( result[ xy( i, j) ] == -1 );
        }
    }

    // Element-wise multiply
    result = mat_1 % mat_2;

    for ( size_t i = 0; i < mat_1.rows(); ++i ){
        for ( size_t j = 0; j < mat_1.cols(); ++j ){
            CPPUNIT_ASSERT ( result[ xy( i, j) ] == 10 );
        }
    }
	
	result = 3 % mat_1 % 2;

    for ( size_t i = 0; i < mat_1.rows(); ++i ){
        for ( size_t j = 0; j < mat_1.cols(); ++j ){
            CPPUNIT_ASSERT ( result[ xy( i, j) ] == 12 );
        }
    }

    // Element-wise divide
    result = mat_1 / mat_2;

    for ( size_t i = 0; i < mat_1.rows(); ++i ){
        for ( size_t j = 0; j < mat_1.cols(); ++j ){
            CPPUNIT_ASSERT ( result[ xy( i, j) ] == 0.4 );
        }
    }
	
	result = 3 / mat_1 / 2;

    for ( size_t i = 0; i < mat_1.rows(); ++i ){
        for ( size_t j = 0; j < mat_1.cols(); ++j ){
            CPPUNIT_ASSERT ( result[ xy( i, j) ] == 0.75 );
        }
    }
}

////////////////////////////////////////////////////////////

void MatrixTestSuite::RowsColsAndDiagonals()
{
    typedef gsl::realMatrix::element_type xy;

    gsl::realMatrix::size_type iRows = 5;
    gsl::realMatrix::size_type iCols = 7;
    gsl::realMatrix m( iRows, iCols );

    for ( size_t i = 0; i < m.rows(); ++i ){
        for ( size_t j = 0; j < m.cols(); ++j ){
            m[ xy( i, j) ] = i*m.cols() + j;
        }
    }

    // Rows & cols
    gsl::vector< real > v_col = m.col(4);
    CPPUNIT_ASSERT ( v_col.size() == iRows );
    CPPUNIT_ASSERT ( v_col.is_col_vector() );

    gsl::vector< real > v_col_exp( iRows );
    v_col_exp[0] =  4;
    v_col_exp[1] = 11;
    v_col_exp[2] = 18;
    v_col_exp[3] = 25;
    v_col_exp[4] = 32;
    CPPUNIT_ASSERT ( v_col_exp == v_col );

    gsl::vector< real > v_row = m.row(2);
    CPPUNIT_ASSERT ( v_row.size() == iCols );
    CPPUNIT_ASSERT (v_row.is_row_vector() );

    gsl::vector< real > v_row_exp( iCols );
	v_row_exp.set_row_vector();
    v_row_exp[0] = 14;
    v_row_exp[1] = 15;
    v_row_exp[2] = 16;
    v_row_exp[3] = 17;
    v_row_exp[4] = 18;
    v_row_exp[5] = 19;
    v_row_exp[6] = 20;
    CPPUNIT_ASSERT ( v_row_exp == v_row );

    // Diagonals
    gsl::vector< real > v_diag = m.diagonal();
    gsl::vector< real > v_subDiag = m.diagonal(-3);
    gsl::vector< real > v_supDiag = m.diagonal(6);

    gsl::vector< real > v_diag_exp(5);
    v_diag_exp[0] =  0;
    v_diag_exp[1] =  8;
    v_diag_exp[2] = 16;
    v_diag_exp[3] = 24;
    v_diag_exp[4] = 32;
    CPPUNIT_ASSERT ( v_diag_exp == v_diag );

    gsl::vector< real > v_subDiag_exp(2);
    v_subDiag_exp[0] = 21;
    v_subDiag_exp[1] = 29;
    CPPUNIT_ASSERT ( v_subDiag_exp == v_subDiag );

    gsl::vector< real > v_supDiag_exp(1);
    v_supDiag_exp[0] = 6;
    CPPUNIT_ASSERT ( v_supDiag_exp == v_supDiag );

    CPPUNIT_ASSERT_THROW ( m.diagonal( -10 ), std::out_of_range );
    CPPUNIT_ASSERT_THROW ( m.diagonal( 7 ), std::out_of_range );

    gsl::realMatrix x;
    CPPUNIT_ASSERT_THROW ( x.diagonal(), gsl::matrix_uninitialised );
}

////////////////////////////////////////////////////////////

void MatrixTestSuite::MatrixMatrixMultiplication()
{
	typedef gsl::realMatrix::element_type xy;
	gsl::realMatrix A(2,3);
	gsl::realMatrix B(3,2);
	
	A[ xy(0,0) ] = 0.11; A[ xy(0,1) ] = 0.12; A[ xy(0,2) ] = 0.13;
	A[ xy(1,0) ] = 0.21; A[ xy(1,1) ] = 0.22; A[ xy(1,2) ] = 0.23;
	
	B[ xy(0,0) ] = 1011; B[ xy(0,1) ] = 1012;
	B[ xy(1,0) ] = 1021; B[ xy(1,1) ] = 1022;
	B[ xy(2,0) ] = 1031; B[ xy(2,1) ] = 1032;
	
	gsl::realMatrix C = A*B;
	
	CPPUNIT_ASSERT( C.rows() == 2 );
	CPPUNIT_ASSERT( C.cols() == 2 );
	
	real rTolerance = 1e-10;
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 367.76, C[ xy(0,0) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 368.12, C[ xy(0,1) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 674.06, C[ xy(1,0) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 674.72, C[ xy(1,1) ], rTolerance );
}

////////////////////////////////////////////////////////////

void MatrixTestSuite::MatrixVectorMultiplication()
{
	typedef gsl::realMatrix::element_type xy;
	
	gsl::realMatrix::size_type iRows = 8;
	gsl::realMatrix::size_type iCols = 5;
	gsl::realMatrix A(iRows, iCols);
	
	// Put some values into the matrix
	size_t i = 0;
	gsl::realMatrix::iterator it_A = A.begin();
	while ( it_A != A.end() )
		*it_A++ = static_cast< gsl::realMatrix::value_type>( i++ );
	
	gsl::vector< real > x( iCols );		// The size of the vector must be the same as the number of cols in the matrix
	i = 0;
	gsl::vector< real >::iterator it_x = x.begin();
	while ( it_x != x.end() )
		*it_x++ = static_cast< gsl::vector< real >::value_type >( i++ );
		
	gsl::vector< real > y = A*x;
	
	gsl::vector< real > targetResult( iRows );
	targetResult[ 0 ] = 30;
	targetResult[ 1 ] = 80;
	targetResult[ 2 ] = 130;
	targetResult[ 3 ] = 180;
	targetResult[ 4 ] = 230;
	targetResult[ 5 ] = 280;
	targetResult[ 6 ] = 330;
	targetResult[ 7 ] = 380;
	
	CPPUNIT_ASSERT( y == targetResult );
}

////////////////////////////////////////////////////////////

void MatrixTestSuite::Transpose()
{
	typedef gsl::realMatrix::element_type xy;
	
	gsl::realMatrix::size_type iRows = 3;
	gsl::realMatrix::size_type iCols = 2;
	gsl::realMatrix A(iRows, iCols);
	
	// Put some values into the matrix
	size_t i = 0;
	gsl::realMatrix::iterator it_A = A.begin();
	while ( it_A != A.end() )
		*it_A++ = static_cast< gsl::realMatrix::value_type>( i++ );
		
	// Test non-square matrix
	gsl::realMatrix B = A.transpose();
	
	CPPUNIT_ASSERT ( A[ xy(0,0) ] == B[ xy(0,0) ] );
	CPPUNIT_ASSERT ( A[ xy(0,1) ] == B[ xy(1,0) ] );
	CPPUNIT_ASSERT ( A[ xy(1,0) ] == B[ xy(0,1) ] );
	CPPUNIT_ASSERT ( A[ xy(1,1) ] == B[ xy(1,1) ] );
	CPPUNIT_ASSERT ( A[ xy(2,0) ] == B[ xy(0,2) ] );
	CPPUNIT_ASSERT ( A[ xy(2,1) ] == B[ xy(1,2) ] );
	
	// Test square matrix
	gsl::realMatrix C(2,2);
	
	gsl::realMatrix::iterator it_C = C.begin();
	while ( it_C != C.end() )
		*it_C++ = static_cast< gsl::realMatrix::value_type>( i++ );
	
	gsl::realMatrix D = C.transpose();
	
	CPPUNIT_ASSERT ( C[ xy(0,0) ] == D[ xy(0,0) ] );
	CPPUNIT_ASSERT ( C[ xy(0,1) ] == D[ xy(1,0) ] );
	CPPUNIT_ASSERT ( C[ xy(1,0) ] == D[ xy(0,1) ] );
	CPPUNIT_ASSERT ( C[ xy(1,1) ] == D[ xy(1,1) ] );
	
}

////////////////////////////////////////////////////////////

void MatrixTestSuite::SwapRowsAndCols()
{
	typedef gsl::realMatrix::element_type xy;
	
	gsl::realMatrix::size_type iRows = 4;
	gsl::realMatrix::size_type iCols = 3;
	gsl::realMatrix A(iRows, iCols);
	
	// Put some values into the matrix
	size_t i = 0;
	gsl::realMatrix::iterator it_A = A.begin();
	while ( it_A != A.end() )
		*it_A++ = static_cast< gsl::realMatrix::value_type>( i++ );
	
	A.swapRows(1,3);
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 9,  A[ xy(1,0) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 10, A[ xy(1,1) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 11, A[ xy(1,2) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 3,  A[ xy(3,0) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 4,  A[ xy(3,1) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 5,  A[ xy(3,2) ], rTolerance );
	
	A.swapCols(0,2);
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 2,  A[ xy(0,0) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 11, A[ xy(1,0) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 8,  A[ xy(2,0) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 5,  A[ xy(3,0) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 0,  A[ xy(0,2) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 9,  A[ xy(1,2) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 6,  A[ xy(2,2) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 3,  A[ xy(3,2) ], rTolerance );
	
	gsl::realMatrix B(iRows, iRows);
	
	// Put some values into the matrix
	gsl::realMatrix::iterator it_B = B.begin();
	while ( it_B != B.end() )
		*it_B++ = static_cast< gsl::realMatrix::value_type>( i++ );
	
	B.swapRowCol(2,3);
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 15, B[ xy(2,0) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 19, B[ xy(2,1) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 23, B[ xy(2,2) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 27, B[ xy(2,3) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 20, B[ xy(0,3) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 21, B[ xy(1,3) ], rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 22, B[ xy(3,3) ], rTolerance );
}

////////////////////////////////////////////////////////////

void MatrixTestSuite::MinMax()
{
	typedef gsl::realMatrix::element_type xy;
	gsl::realMatrix A( 2, 2 );
	A[ xy( 0, 0 ) ] = 2.1;	A[ xy( 0, 1 ) ] = 2.4;
	A[ xy( 1, 0 ) ] = 2.0;	A[ xy( 1, 1 ) ] = 2.9;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 2.0, A.min(), rTolerance );
	CPPUNIT_ASSERT_DOUBLES_EQUAL ( 2.9, A.max(), rTolerance );
	CPPUNIT_ASSERT ( A.min_element() == xy( 1, 0 ) );
	CPPUNIT_ASSERT ( A.max_element() == xy( 1, 1 ) );
	
	CPPUNIT_ASSERT ( A.minMax() == std::make_pair( 2.0, 2.9 ) );
	CPPUNIT_ASSERT ( A.minMax_element() == std::make_pair( xy(1,0), xy(1,1) ) );
}

////////////////////////////////////////////////////////////

void MatrixTestSuite::RealBooleanComparisons()
{
	typedef gsl::realMatrix::element_type xy;
	gsl::realMatrix A( 2, 2, 1 );
	
	CPPUNIT_ASSERT ( A == 1.0);
	CPPUNIT_ASSERT ( 1.0 == A );
	CPPUNIT_ASSERT ( A != 0.0 );
	CPPUNIT_ASSERT ( 0.0 != A );
	CPPUNIT_ASSERT ( A > 0.9 );
	CPPUNIT_ASSERT ( 0.9 < A );
	CPPUNIT_ASSERT ( ! ( A < 0.9 ) );
	CPPUNIT_ASSERT ( ! ( 0.9 > A ) );
	CPPUNIT_ASSERT ( A >= 1.0 );
	CPPUNIT_ASSERT ( 1.0 <= A );
	CPPUNIT_ASSERT ( A <= 1.0 );
	CPPUNIT_ASSERT ( 1.0 >= A );
}

////////////////////////////////////////////////////////////
/*
void MatrixTestSuite::Swap()
{
    typedef gsl::realMatrix::element_type xy;

    gsl::realMatrix::size_type iSize = 4;
    gsl::realMatrix m( gsl::identity(iSize) );

    // diagonal matrix, so these two operations should give the original matrix
    m.swapRows( 1,2 );
    m.swapCols( 1,2 );

    CPPUNIT_ASSERT ( m == gsl::identity(iSize));

    m.swapElements( xy( 0,0), xy( 0,3) );

    CPPUNIT_ASSERT ( m[ xy( 0,3 )] == 1 );
}
*/
////////////////////////////////////////////////////////////
