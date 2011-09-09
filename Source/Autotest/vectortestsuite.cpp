#include "vectortestsuite.h"

#include <vector>
#include <ctime>

#include "gslpp/Common/number.h"
#include "gslpp/Vector/vector.h"
#include "gslpp/Common/exceptions.h"

////////////////////////////////////////////////////////////

CPPUNIT_TEST_SUITE_REGISTRATION( VectorTestSuite );

////////////////////////////////////////////////////////////

void VectorTestSuite::setUp(){}

////////////////////////////////////////////////////////////

void VectorTestSuite::tearDown(){}

////////////////////////////////////////////////////////////

void VectorTestSuite::VectorsAreEqual()
{
	gsl::vector< real > v(5);
	
    const int iVectorSize = 10;

    gsl::realVector vec_1( iVectorSize );
    gsl::realVector vec_2( iVectorSize );

    for ( size_t i = 0; i < vec_1.size(); ++i ){
        vec_1[i] = i;
        vec_2[i] = i;
    }

    CPPUNIT_ASSERT( vec_1 == vec_2 );

    vec_2 *= vec_1;

    CPPUNIT_ASSERT( vec_1 != vec_2 );
}

////////////////////////////////////////////////////////////

void VectorTestSuite::AddVector()
{
    const int iVectorSize = 10;
    const int iOffset = 5;

    gsl::realVector vec_1( iVectorSize );
    gsl::realVector vec_2( iVectorSize );

    for ( size_t i = 0; i < vec_1.size(); ++i ){
        vec_1[i] = i;
        vec_2[i] = i + iOffset;
    }

    gsl::realVector vec_3 = vec_1 + vec_2;

    for ( size_t i = 0; i < vec_1.size(); ++i ){
        double expected = i + i + iOffset;
        CPPUNIT_ASSERT( expected == vec_3[i]);
    }
}

////////////////////////////////////////////////////////////

void VectorTestSuite::SubtractVector()
{
    const int iVectorSize = 10;
    const int iOffset = 5;

    gsl::realVector vec_1( iVectorSize );
    gsl::realVector vec_2( iVectorSize );

    for ( int i = 0; i < vec_1.size(); ++i ){
        vec_1[i] = i;
        vec_2[i] = iVectorSize - i - iOffset;
    }

    gsl::realVector vec_3 = vec_1 - vec_2;

    for ( int i = 0; i < vec_1.size(); ++i ){
        double expected = i - (iVectorSize - i - iOffset);
        CPPUNIT_ASSERT( expected == vec_3[i] );
    }
}

////////////////////////////////////////////////////////////

void VectorTestSuite::AddConstant()
{
    const int iVectorSize = 10;
    const double value = 1.22313;

    gsl::realVector vec( iVectorSize );

    for ( int i = 0; i < iVectorSize; ++i ) vec[i] = i;

    vec += value;

    for( int i = 0; i < iVectorSize; ++i ){
        double expected = i + value;
        double actual = vec[i];
        CPPUNIT_ASSERT_DOUBLES_EQUAL( actual, expected, rTolerance );
    }
}

////////////////////////////////////////////////////////////

void VectorTestSuite::SubtractConstant()
{
    const int iVectorSize = 10;
    const double value = 1.22313;

    gsl::realVector vec( iVectorSize );

    for ( int i = 0; i < iVectorSize; ++i ) vec[i] = i;

    vec -= value;

    for( int i = 0; i < iVectorSize; ++i ){
        double expected = i - value;
        double actual = vec[i];
        CPPUNIT_ASSERT_DOUBLES_EQUAL( actual, expected, rTolerance );
    }
}

////////////////////////////////////////////////////////////

void VectorTestSuite::MultiplyConstant()
{
    const int iVectorSize = 10;
    const double value = 1.22313;

    gsl::realVector vec( iVectorSize );

    for ( int i = 0; i < iVectorSize; ++i ) vec[i] = i;

    vec *= value;

    for( int i = 0; i < iVectorSize; ++i ){
        double expected = i * value;
        double actual = vec[i];
        CPPUNIT_ASSERT_DOUBLES_EQUAL( actual, expected, rTolerance );
    }
}

////////////////////////////////////////////////////////////

void VectorTestSuite::DivideConstant()
{
    const int iVectorSize = 10;
    const double value = 1.22313;

    gsl::realVector vec( iVectorSize );

    for ( int i = 0; i < iVectorSize; ++i )
        vec[i] = i;

    vec /= value;

    for( int i = 0; i < iVectorSize; ++i ){
        double expected = i / value;
        double actual = vec[i];
        CPPUNIT_ASSERT_DOUBLES_EQUAL( actual, expected, rTolerance );
    }
}

////////////////////////////////////////////////////////////

void VectorTestSuite::ElementwiseVectorMultiply()
{
    const int iVectorSize = 10;
    const real rMultiplier = 323.3242349;

    gsl::realVector vec_1( iVectorSize );
    gsl::realVector vec_2( iVectorSize );

    for ( int i = 0; i < vec_1.size(); ++i ){
        vec_1[i] = i + 1;
        vec_2[i] = rMultiplier/(i + 1);
    }

    vec_2 *= vec_1;

    for ( int i = 0; i < vec_1.size(); ++i )
        CPPUNIT_ASSERT_DOUBLES_EQUAL( rMultiplier, vec_2[i], rTolerance );
}

////////////////////////////////////////////////////////////

void VectorTestSuite::ElementwiseVectorDivide()
{
    const int iVectorSize = 10;
    const real rMultiplier = 323.3242349;

    gsl::realVector vec_1( iVectorSize );
    gsl::realVector vec_2( iVectorSize );

    for ( int i = 0; i < vec_1.size(); ++i ){
        vec_1[i] = i + 1;
        vec_2[i] = (i + 1)*rMultiplier;
    }

    vec_2 /= vec_1;

    for ( int i = 0; i < vec_1.size(); ++i )
        CPPUNIT_ASSERT_DOUBLES_EQUAL( rMultiplier, vec_2[i], rTolerance );

    vec_1.zero();
    vec_2 /= vec_1;

    CPPUNIT_ASSERT ( vec_2 == gsl::realVector( iVectorSize, realPlusInf ) );
}

////////////////////////////////////////////////////////////

void VectorTestSuite::MaxAndMin()
{
    const int iVectorSize = 10;
    const real rMultiplier = 323.3242349;

    gsl::realVector vec( iVectorSize );

    for ( int i = 0; i < vec.size(); ++i )
        vec[i] = i*rMultiplier - 3*rMultiplier;

    CPPUNIT_ASSERT_DOUBLES_EQUAL(-3*rMultiplier, vec.min(), rTolerance );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( (iVectorSize - 3 - 1)*rMultiplier, vec.max(), rTolerance );
    CPPUNIT_ASSERT( 0 == vec.min_element() );
    CPPUNIT_ASSERT( iVectorSize - 1 == vec.max_element() );

    std::pair< real, real > pair_minMax = vec.minmax();
    CPPUNIT_ASSERT_DOUBLES_EQUAL( -3*rMultiplier, pair_minMax.first, rTolerance );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( (iVectorSize - 3 - 1)*rMultiplier, pair_minMax.second, rTolerance );

    std::pair< size_t, size_t > pair_minMax_element = vec.minmax_element();
    CPPUNIT_ASSERT( 0 == pair_minMax_element.first );
    CPPUNIT_ASSERT( iVectorSize-1 == pair_minMax_element.second );
}

////////////////////////////////////////////////////////////

void VectorTestSuite::Swap()
{
    gsl::realVector vec_1(4);
    vec_1[0] = 1;
    vec_1[1] = 2;
    vec_1[2] = 3;
    vec_1[3] = 4;

    vec_1.swapElements(0,3);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 4.0, vec_1[0], rTolerance );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0, vec_1[3], rTolerance );

    gsl::realVector vec_2(4);
    vec_1.swap( vec_2 );

    CPPUNIT_ASSERT_DOUBLES_EQUAL( 4.0, vec_2[0], rTolerance );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 2.0, vec_2[1], rTolerance );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 3.0, vec_2[2], rTolerance );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0, vec_2[3], rTolerance );
}

////////////////////////////////////////////////////////////

void VectorTestSuite::Basis()
{
    gsl::realVector vec(4);
    vec.basis(2);

    for ( size_t i = 0; i < 4; ++i )
        CPPUNIT_ASSERT_DOUBLES_EQUAL( (i == 2 ? 1 : 0), vec[i], rTolerance );
}

////////////////////////////////////////////////////////////

void VectorTestSuite::IsNull()
{
    gsl::realVector vec;

    CPPUNIT_ASSERT( vec.isNull() );
}

////////////////////////////////////////////////////////////

void VectorTestSuite::STLCompatibility()
{
    const size_t ciVecSize = 10;
    gsl::realVector vec( ciVecSize );

    for ( size_t i = 0; i < ciVecSize; ++i )
        vec[ i ] = static_cast< double >( i );

    // Iterators
    CPPUNIT_ASSERT ( vec.ptr()->data == vec.begin() );
    CPPUNIT_ASSERT ( vec.ptr()->data + vec.size() == vec.end() );
    CPPUNIT_ASSERT ( vec.ptr()->data + (vec.size() - 1) == vec.rbegin() );
    CPPUNIT_ASSERT ( vec.ptr()->data - 1 == vec.rend() );

    // Capacity
    CPPUNIT_ASSERT ( vec.size() == ciVecSize );

    const size_t ciCap = 20;
    vec.reserve( ciCap );
    CPPUNIT_ASSERT ( vec.size() == ciVecSize );
    CPPUNIT_ASSERT ( vec.capacity() == ciCap );

    // Not an STL function, but useful here
    vec.reset();
    CPPUNIT_ASSERT ( vec.empty() );

    // Element access & Modifiers
    //
    // push_back
    for ( size_t i = 0; i < ciVecSize; ++i )
        vec.push_back( static_cast< double >( i ) );

    // front & back
    CPPUNIT_ASSERT ( vec.size() == ciVecSize );
    CPPUNIT_ASSERT ( vec.front() == 0 );
    CPPUNIT_ASSERT ( vec.back() == 9 );

    // assign
    vec.assign( 25, 1 );
    vec.assign( 6, 2 );

    CPPUNIT_ASSERT ( vec.size() == 25 );
    for ( size_t i = 0; i < 6; ++i )
        CPPUNIT_ASSERT ( vec[i] == 2 );
    for ( size_t i = 6; i < 25; ++i )
        CPPUNIT_ASSERT ( vec[i] == 1 );

    // insert
    vec.insert( vec.begin() + 6, 7 );
    CPPUNIT_ASSERT ( vec[6] == 7 );

    // pop_back
    CPPUNIT_ASSERT ( vec.pop_back() == 1 );

    // erase
    vec.erase(6);
    CPPUNIT_ASSERT ( vec.size() == 24 );
    for ( size_t i = 0; i < 6; ++i )
        CPPUNIT_ASSERT ( vec[i] == 2 );
    for ( size_t i = 6; i < 24; ++i )
        CPPUNIT_ASSERT ( vec[i] == 1 );

    // clear
    vec.clear();
    CPPUNIT_ASSERT ( vec.empty() );
    CPPUNIT_ASSERT ( vec.size() == 0);
    CPPUNIT_ASSERT ( vec.capacity() == 26 );
}

////////////////////////////////////////////////////////////

void VectorTestSuite::Squeeze()
{
    const size_t ciVecSize = 10;
    const size_t ciCap = 1000;
    gsl::realVector vec( ciVecSize, 2.0 );

    CPPUNIT_ASSERT ( vec.size() == ciVecSize );
    CPPUNIT_ASSERT ( vec.capacity() == ciVecSize );

    vec.reserve( ciCap );
    CPPUNIT_ASSERT ( vec.size() == ciVecSize );
    CPPUNIT_ASSERT ( vec.capacity() == ciCap );

    vec.push_back( 3 );
    CPPUNIT_ASSERT ( vec.size() == ciVecSize + 1 );
    CPPUNIT_ASSERT ( vec.capacity() == ciCap );

    vec.squeeze();
    CPPUNIT_ASSERT ( vec.size() == ciVecSize + 1 );
    CPPUNIT_ASSERT ( vec.capacity() == ciVecSize + 1 );
}

////////////////////////////////////////////////////////////

void VectorTestSuite::AccessorsAndMutators()
{
    const size_t ciVecSize = 10;
    gsl::realVector vec( ciVecSize );

    for ( size_t i = 0; i < ciVecSize; ++i )
        vec[ i ] = static_cast< double >( i );

    CPPUNIT_ASSERT_THROW ( vec.at( 10 ), std::out_of_range );
    CPPUNIT_ASSERT_THROW ( vec.at( -4 ), std::out_of_range );

    CPPUNIT_ASSERT_EQUAL ( vec.back(), vec( -1 ) );
    CPPUNIT_ASSERT_EQUAL ( vec[ 5 ], vec( 35 ) );
    CPPUNIT_ASSERT_EQUAL ( vec[ 5 ], vec( -35 ) );

    real rTolerance = 1e-15;
    vec( -3 ) = 372.23;
    CPPUNIT_ASSERT_DOUBLES_EQUAL ( vec[7], 372.23, rTolerance );

    vec.at( 2 ) = 123.43;
    CPPUNIT_ASSERT_DOUBLES_EQUAL ( vec[2], 123.43, rTolerance );
}

////////////////////////////////////////////////////////////

void VectorTestSuite::Performance()
{
    clock_t start = clock();

    std::vector< double > stdVec;
    for ( size_t j = 0; j < 100; ++j ){
        for ( size_t i = 0; i < 100000; ++i )
            stdVec.push_back( 3.1415269 );
        stdVec.clear();
    }

    size_t finish = clock();
    double stdRuntime = static_cast< double >(finish - start)/CLOCKS_PER_SEC;

    start = clock();

    gsl::realVector gslVec;
    for ( size_t j = 0; j < 100; ++j ){
        for ( size_t i = 0; i < 100000; ++i )
            gslVec.push_back( 3.1415269 );
        gslVec.clear();
    }

    finish = clock();
    double gslRuntime = static_cast< double >(finish - start)/CLOCKS_PER_SEC;
    CPPUNIT_ASSERT( gslRuntime < 5*stdRuntime );
}

////////////////////////////////////////////////////////////
