#include "vector.h"
#include "../Utils/mathutils.h"

#include <exception>
#include <algorithm>
#include <iterator>
#include <numeric>

namespace gsl{

////////////////////////////////////////////////////////////

void realVector::M_realloc( size_type n) throw ( std::bad_alloc )
{
    free();
    set_ptr( gsl_vector_alloc( atLeastOne( n ) ) );

    if ( isNull() )
        throw std::bad_alloc();

    M_pStart = ptr()->data;
    M_pFinish = M_pStart + n;
    M_pEnd_of_storage = M_pStart + atLeastOne( n );
}

////////////////////////////////////////////////////////////

void realVector::M_guaranteed_reserve( size_type n )
{
    // Remember the original size ( not capacity )
    size_type iOriginalSize = size();

    // Make a new gsl_vector with the new capacity
    gsl_vector* temp = gsl_vector_alloc( atLeastOne( n ) );

    if ( temp == NULL ) throw std::bad_alloc();

    // Copy the existing values into the new vector
    std::copy( begin(), end(), temp->data );

    // Exchange the old gsl_vector for the new one
    std::swap( temp, M_pGSLData );

    // Free the memory for the temorary gsl_vector
    gsl_vector_free( temp );

    // Set the new markers for this vector
    M_pStart = M_pGSLData->data;
    M_pFinish = M_pStart + iOriginalSize;
    M_pEnd_of_storage = M_pStart + n;
}

////////////////////////////////////////////////////////////

realVector::realVector() :
	gsl_base( NULL ), M_pStart(0), M_pFinish(0), M_pEnd_of_storage(0), M_bIsRowVector(false)
{}

////////////////////////////////////////////////////////////

realVector::realVector( size_type n, bool isColVector ) throw ( std::bad_alloc ) :
    gsl_base( gsl_vector_alloc( atLeastOne( n ) ) ), M_bIsRowVector(!isColVector)
{
    if ( isNull() ) throw std::bad_alloc();

    M_pStart = ptr()->data;
    M_pFinish = M_pStart + n;
    M_pEnd_of_storage = M_pFinish;
}

////////////////////////////////////////////////////////////

realVector::realVector( size_type n, real value, bool isColVector ) throw ( std::bad_alloc ) :
    gsl_base( gsl_vector_alloc( atLeastOne( n ) ) ), M_bIsRowVector(!isColVector)
{
    if ( isNull() ) throw std::bad_alloc();

    M_pStart = ptr()->data;
    M_pFinish = M_pStart + n;
    M_pEnd_of_storage = M_pFinish;

    std::fill( M_pStart, M_pFinish, value );
}

////////////////////////////////////////////////////////////

realVector::realVector( size_type n, real* array, bool isColVector ) throw ( std::bad_alloc ) :
    gsl_base( gsl_vector_alloc( atLeastOne( n ) ) ), M_bIsRowVector(!isColVector)
{
    if ( isNull() ) throw std::bad_alloc();

    M_pStart = ptr()->data;
    M_pFinish = M_pStart + n;
    M_pEnd_of_storage = M_pFinish;

    std::copy( array, array + n, M_pStart );
}

////////////////////////////////////////////////////////////

realVector::realVector( const realVector &right ) throw ( std::bad_alloc ) :
    gsl_base( gsl_vector_alloc( atLeastOne( right.capacity() ) ) ), M_bIsRowVector( right.M_bIsRowVector )
{
    if ( isNull() )    throw std::bad_alloc();

    M_pStart = ptr()->data;
    M_pFinish = M_pStart + right.size();
    M_pEnd_of_storage = M_pFinish;

    std::copy( right.cbegin(), right.cend(), M_pStart );
}

////////////////////////////////////////////////////////////

realVector::realVector( gsl_vector* pGSLVec, bool isColVector ) throw ( std::bad_alloc ) :
	M_bIsRowVector(!isColVector)
{
    if ( pGSLVec != NULL ){
        M_pGSLData = gsl_vector_alloc( pGSLVec->size );
        if ( isNull() )
            throw std::bad_alloc();

        M_pStart = ptr()->data;
        M_pFinish = M_pStart + pGSLVec->size;
        M_pEnd_of_storage = M_pFinish;

        std::copy( pGSLVec->data, pGSLVec->data + pGSLVec->size, begin() );
    }
}

////////////////////////////////////////////////////////////

realVector::realVector( const std::vector< real >& original, bool isColVector ) throw ( std::bad_alloc )  :
    gsl_base( gsl_vector_alloc( atLeastOne( original.capacity() ) ) ), M_bIsRowVector(!isColVector)
{
    if ( isNull() )    throw std::bad_alloc();

    M_pStart = ptr()->data;
    M_pFinish = M_pStart + original.size();
    M_pEnd_of_storage = M_pFinish;

    std::copy( original.begin(), original.end(), M_pStart );
}

////////////////////////////////////////////////////////////

realVector::~realVector()
{
//    free();
}

////////////////////////////////////////////////////////////

gsl::realVector &realVector::operator=( const realVector::value_type right )
{
    if( isNull() )
        M_realloc(1);

    std::fill( begin(), end(), right );

    return *this;
}

////////////////////////////////////////////////////////////

gsl::realVector &realVector::operator=(const gsl::realVector &right)
{
    gsl::realVector out( right );
    swap( out );

    return *this;
}

////////////////////////////////////////////////////////////

gsl::realVector &realVector::operator+=(const realVector &right) throw ( vector_uninitialised, vector_size_mismatch )
{
    if ( isNull() )
        throw vector_uninitialised();

    if( size() != right.size() )
        throw vector_size_mismatch();

    const_iterator it_r = right.cbegin();
    for ( iterator it_l = begin(); it_l != end(); ++it_l, ++it_r )
        *it_l += *it_r;

    return *this;
}

////////////////////////////////////////////////////////////

gsl::realVector &realVector::operator+=( const value_type right) throw ( vector_uninitialised )
{
    if( isNull() )
        throw vector_uninitialised();

    for ( iterator it = begin(); it != end(); ++it )
        *it += right;

    return *this;
}

////////////////////////////////////////////////////////////

gsl::realVector &realVector::operator-=(const realVector &right) throw ( vector_uninitialised, vector_size_mismatch )
{
    if ( isNull() )
        throw vector_uninitialised();

    if( size() != right.size() )
        throw vector_size_mismatch();

    const_iterator it_r = right.cbegin();
    for ( iterator it_l = begin(); it_l != end(); ++it_l, ++it_r )
        *it_l -= *it_r;

    return *this;
}

////////////////////////////////////////////////////////////

gsl::realVector &realVector::operator-=( const value_type right) throw ( vector_uninitialised )
{
    if( isNull() )
        throw vector_uninitialised();

    for ( iterator it = begin(); it != end(); ++it )
        *it -= right;

    return *this;
}

////////////////////////////////////////////////////////////

gsl::realVector &realVector::operator*=(const realVector &right) throw ( vector_uninitialised, vector_size_mismatch )
{
    if ( isNull() )
        throw vector_uninitialised();

    if( size() != right.size() )
        throw vector_size_mismatch();

    const_iterator it_r = right.cbegin();
    for ( iterator it_l = begin(); it_l != end(); ++it_l, ++it_r )
        *it_l *= *it_r;

    return *this;
}

////////////////////////////////////////////////////////////

gsl::realVector &realVector::operator*=( const value_type right) throw ( vector_uninitialised )
{
    if( isNull() )
        throw vector_uninitialised();

    for ( iterator it = begin(); it != end(); ++it)
        *it *= right;

    return *this;
}

////////////////////////////////////////////////////////////

gsl::realVector &realVector::operator/=(const realVector &right) throw ( vector_uninitialised, vector_size_mismatch )
{
    if ( isNull() )
        throw vector_uninitialised();

    if( size() != right.size() )
        throw vector_size_mismatch();

    const_iterator it_r = right.cbegin();
    for ( iterator it_l = begin(); it_l != end(); ++it_l, ++it_r ){
        if ( *it_r == 0 ){
            if ( *it_l != 0 )
                *it_l = *it_l > 0 ? realPlusInf : realMinusInf;
            else
                *it_l = NaN;
        }
        else
            *it_l /= *it_r;
    }

    return *this;
}

////////////////////////////////////////////////////////////

gsl::realVector &realVector::operator/=(const value_type right) throw ( vector_uninitialised )
{
    if ( isNull() )
        throw vector_uninitialised();

    if ( right == 0 ){
        for ( iterator it_l = begin(); it_l != end(); ++it_l ){
            if ( *it_l != 0 )
                *it_l = *it_l > 0 ? realPlusInf : realMinusInf;
            else
                *it_l = NaN;
        }
    }

    for ( iterator it_l = begin(); it_l != end(); ++it_l )
        *it_l /= right;

    return *this;
}

////////////////////////////////////////////////////////////

real *realVector::toArray() const throw ( std::bad_alloc )
{
    iterator out = static_cast< iterator >( malloc( (size()/stride()) * sizeof( size_type ) ) );

    if ( out == NULL )
        throw std::bad_alloc();

    std::copy( cbegin(), cend(), out );

    return out;
}

////////////////////////////////////////////////////////////

realVector::const_reference realVector::at( realVector::size_type i) const throw ( std::out_of_range, vector_uninitialised )
{
    M_range_check( i );

    return *( M_pStart + i );
}

////////////////////////////////////////////////////////////

realVector::reference realVector::at(size_type i)throw ( std::out_of_range, vector_uninitialised )
{
    M_range_check( i );

    return *( M_pStart + i );
}

////////////////////////////////////////////////////////////

realVector::reference realVector::operator()( int i ) throw ( std::bad_alloc )
{
    if ( isNull() )
    {
        set_ptr( gsl_vector_alloc( 1 ) );

        if ( isNull() )
            throw std::bad_alloc();

        M_pStart = ptr()->data;
        M_pFinish = M_pStart + 1;
        M_pEnd_of_storage = M_pFinish;

        return *M_pStart;
    }
    else
        return *( M_pStart + ( i  % static_cast< int >( size() ) + size() ) % size() );
}

////////////////////////////////////////////////////////////

realVector::const_reference realVector::operator()( int i ) const
{
    if ( isNull() )
    {
        return realEmpty;
    }
    else
        return *( M_pStart + ( i  % static_cast< int >( size() ) + size() ) % size() );
}

////////////////////////////////////////////////////////////

std::pair< realVector::value_type, realVector::value_type > realVector::minmax() const
{
    value_type minVal, maxVal;
    gsl_vector_minmax( const_ptr(), &minVal, &maxVal );
    return std::pair< value_type, value_type >( minVal, maxVal );
}

////////////////////////////////////////////////////////////

std::pair< realVector::size_type, realVector::size_type > realVector::minmax_element() const
{
    size_type minVal, maxVal;
    gsl_vector_minmax_index( const_ptr(), &minVal, &maxVal );
    return std::pair< size_type, size_type >(minVal,maxVal);
}

////////////////////////////////////////////////////////////

void realVector::swapElements(realVector::size_type i1, realVector::size_type i2)
{
    M_range_check( i1 );
    M_range_check( i2 );

    gsl_vector_swap_elements( ptr(), i1, i2);
}

////////////////////////////////////////////////////////////

void realVector::swap(gsl::realVector& other)
{
    if ( isNull() && other.isNull() )
        return;

    std::swap( M_pGSLData, other.M_pGSLData );
    std::swap( M_bIsRowVector, other.M_bIsRowVector );
    std::swap( M_pStart, other.M_pStart );
    std::swap( M_pFinish, other.M_pFinish );
    std::swap( M_pEnd_of_storage, other.M_pEnd_of_storage );

}

////////////////////////////////////////////////////////////

void realVector::resize(const realVector::size_type n)
{
    reserve( n );
    M_pFinish = M_pStart + n;
}

////////////////////////////////////////////////////////////

void realVector::resize(const realVector::size_type n, const realVector::value_type value)
{
    reserve( n );
    pointer pOriginalEnd = M_pFinish;
    M_pFinish = M_pStart + n;

    std::fill( pOriginalEnd, M_pFinish, value );
}

////////////////////////////////////////////////////////////

void realVector::reserve( size_type n ) throw (std::bad_alloc )
{
    if ( hasValue() ){
        if ( M_pStart + n > M_pEnd_of_storage ){
            M_guaranteed_reserve( n );
        }
    }
    else{
        M_realloc( n );
    }
}

////////////////////////////////////////////////////////////

/*    void vector::set_stride( vector::difference_type s )
{
    gsl_vector* pVec = ptr();
    pVec->stride = s;
}*/

////////////////////////////////////////////////////////////

void realVector::zero()
{
    if ( hasValue() )
        gsl_vector_set_zero( ptr() );
}

////////////////////////////////////////////////////////////

void realVector::basis(size_type i)
{
    M_range_check( i );

    gsl_vector_set_basis( ptr(),i);
}

////////////////////////////////////////////////////////////

void realVector::free()
{
    if( isNull() )  return;

    gsl_vector_free( ptr() );
    M_bIsRowVector = true;
    M_pStart = 0;
    M_pFinish = 0;
    M_pEnd_of_storage = 0;
}

////////////////////////////////////////////////////////////

void realVector::squeeze()
{
    if ( hasValue() ){
        if ( M_pFinish != M_pEnd_of_storage ){
            realVector temp( *this );
            swap( temp );
        }
    }
}

void realVector::assign( size_type n, const_reference value )
{
    if ( n > size() )   resize( n );

    std::fill( begin(), begin() + n, value );
}

////////////////////////////////////////////////////////////

void realVector::assign( const_iterator start, const_iterator finish )
{
    if ( static_cast< size_type >(finish - start) > size() )
        resize( static_cast< size_type >(finish - start) );

    std::copy( start, finish, M_pStart );
}

////////////////////////////////////////////////////////////

void realVector::reset()
{
    M_realloc( 0 );
}

////////////////////////////////////////////////////////////

void realVector::push_back( value_type value )
{
    if ( M_pFinish == M_pEnd_of_storage )
        M_guaranteed_reserve( M_pEnd_of_storage != M_pStart ? 2 * ( M_pEnd_of_storage - M_pStart ) : 1 );

    *M_pFinish = value;
    ++M_pFinish;
}

////////////////////////////////////////////////////////////

realVector::value_type realVector::pop_back()
{
    value_type temp = 0.0;

    if ( M_pStart != M_pFinish ){
         temp = back();
        --M_pFinish;
    }

    return temp;
}

////////////////////////////////////////////////////////////

void realVector::erase( size_type n )
{
    M_range_check( n );

    std::copy( begin() + n + 1, end(), begin() + n);
    --M_pFinish;
}

/* need to add void vector::erase( iterator n ) */

////////////////////////////////////////////////////////////

realVector::iterator realVector::insert( realVector::iterator position, value_type x )
{
    size_type pos = static_cast< size_type >( position - M_pStart );
    M_range_check( pos );

    resize( size() + 1 );

    for ( size_type i = size() - 1; i > pos; --i ){
        ptr()->data[i] = ptr()->data[i - 1];
    }
    ptr()->data[ pos ] = x;

    return M_pStart + pos;
}

////////////////////////////////////////////////////////////

void realVector::insert( realVector::iterator position, size_type n, value_type x )
{
    M_range_check( position - M_pStart );

    // Move the old elements out of the way
    iterator it = end();
    iterator shuffleStop = position + n;
    while ( --it != shuffleStop )
        *it = *(it - n);

    // Copy in the new values
    for ( iterator it = position; it != shuffleStop; ++it)
        *it = x;
}

////////////////////////////////////////////////////////////

void realVector::insert( realVector::iterator position, realVector::iterator first, realVector::iterator last )
{
    M_range_check( position - M_pStart );

    // Move the old elements out of the way
    difference_type n = last - first;
    iterator it = end();
    iterator shuffleStop = position + n;
    while ( --it != shuffleStop )
        *it = *(it - n);

    // Copy in the new values
    for ( iterator it = position; it != shuffleStop; ++it)
        *it = *first++;
}

////////////////////////////////////////////////////////////

}   // end namespace gsl

////////////////////////////////////////////////////////////

std::ostream &operator<<( std::ostream &os, const gsl::realVector &right )
{
    char sep( right.isRowVector() ?  ' ' : '\n' );

    os << "(" << sep;
    std::copy( right.cbegin(), right.cend(), std::ostream_iterator< real >( os, &sep ));
    os << ")";

    return os;
}

////////////////////////////////////////////////////////////

bool operator==(const gsl::realVector &left, const gsl::realVector &right)
{
    if ( left.isNull() && right.isNull() )
        return true;

    if ( left.isNull() || right.isNull() )
        return false;

    if ( left.size() != right.size())
        return false;

    if ( left.isRowVector() != right.isRowVector() )
        return false;

    for ( gsl::realVector::const_iterator it_l = left.cbegin(), it_r = right.cbegin(); it_l != left.cend(); ++it_l, ++it_r )
        if ( *it_l != *it_r )   return false;

    return true;
}

////////////////////////////////////////////////////////////

const gsl::realVector operator+( const gsl::realVector& left, const gsl::realVector& right )
{
    if ( left.size() != right.size() )
        throw gsl::vector_size_mismatch();

    gsl::realVector out( left.size() );
    std::transform(left.cbegin(), left.cend(), right.cbegin(), out.begin(), std::plus< real >() );

    return out;
}

////////////////////////////////////////////////////////////

const gsl::realVector operator-( const gsl::realVector& left, const gsl::realVector& right )
{
    if ( left.size() != right.size() )
        throw gsl::vector_size_mismatch();

    gsl::realVector out( left.size() );
    std::transform(left.cbegin(), left.cend(), right.cbegin(), out.begin(), std::minus< real >() );

    return out;
}

////////////////////////////////////////////////////////////

const gsl::realVector operator%( const gsl::realVector& left, const gsl::realVector& right )
{
    if ( left.size() != right.size() )
        throw gsl::vector_size_mismatch();

    gsl::realVector out( left.size() );
    std::transform(left.cbegin(), left.cend(), right.cbegin(), out.begin(), std::multiplies< real >() );

    return out;
}

////////////////////////////////////////////////////////////

real operator*( const gsl::realVector& left, const gsl::realVector& right )
{
    if ( left.size() != right.size() )
        throw gsl::vector_size_mismatch();

    gsl::realVector temp( left.size() );
    std::transform( left.cbegin(), left.cend(), right.cbegin(), temp.begin(), std::multiplies< real >() );
    std::partial_sum( temp.begin(), temp.end(), temp.begin() );

    return temp.back();
}

////////////////////////////////////////////////////////////
