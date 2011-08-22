#include "permutation.h"

#include <cassert>

namespace gsl{

////////////////////////////////////////////////////////////

permutation::permutation( const permutation& original ) throw( std::bad_alloc ) :
    gsl_base_ptr( original.isNull() ? NULL : gsl_permutation_alloc( original.size() ))
{
    if ( isNull() && original.hasValue() )
        throw std::bad_alloc();

    else if ( hasValue() )
        gsl_permutation_memcpy( ptr(), original.const_ptr() );
}

////////////////////////////////////////////////////////////

permutation::~permutation()
{
    free();
    set_ptr( NULL );
}

////////////////////////////////////////////////////////////

void permutation::pv_realloc( size_type n, permutation::initial_state state ) throw ( std::bad_alloc )
{
    free();
    set_ptr( state == initialised ? gsl_permutation_calloc( n ) : gsl_permutation_alloc( n ) );

    if ( isNull() )
        throw std::bad_alloc();
}

////////////////////////////////////////////////////////////

permutation &permutation::operator=(const permutation &right) throw( std::bad_alloc )
{
    if ( this != &right ){
        permutation temp( right );
        swap( temp );
    }

    return *this;
}

////////////////////////////////////////////////////////////

bool permutation::operator==( const gsl::permutation& right ) const
{
    return !( *this != right );
}

////////////////////////////////////////////////////////////

bool permutation::operator!=( const gsl::permutation& right ) const
{
    if ( isNull() && right.isNull() )
        return false;

    if ( isNull() || right.isNull() )
        return true;

    if ( size() != right.size() )
        return true;

    for ( size_type i = 0; i < size(); ++i )
        if ( const_ptr()->data[i] != right[i] ) return true;

    return false;
}

////////////////////////////////////////////////////////////

permutation::reference permutation::at( permutation::size_type index ) throw ( std::out_of_range )
{
    if ( index >= size() )
        throw std::out_of_range("gsl::vector index out of range");

    return ptr()->data[ index ];
}

////////////////////////////////////////////////////////////

permutation::const_reference permutation::at( permutation::size_type index ) const throw ( std::out_of_range )
{
    if ( index >= size() )
        throw std::out_of_range("gsl::vector index out of range");

    return const_ptr()->data[ index ];
}

////////////////////////////////////////////////////////////

void permutation::resize( size_type n ) throw ( std::bad_alloc )
{
    if ( hasValue() ){
        permutation temp( n );
        size_type copyEnd = std::min( size(), n );
        for( size_type i = 0; i < copyEnd; ++i )
            temp[ i ] = ptr()->data[ i ];

        swap( temp );
    }
    else{
        pv_realloc( n );
    }
}

////////////////////////////////////////////////////////////

void permutation::swap( permutation& other )
{
    gsl_permutation* temp_ptr = ptr();
    set_ptr( other.ptr() );
    other.set_ptr( temp_ptr );
}

////////////////////////////////////////////////////////////

void permutation::swapElements( size_type i, size_type j ) throw ( std::out_of_range, permutation_uninitialised )
{
    if ( isNull() )      throw permutation_uninitialised();

    int status( gsl_permutation_swap( ptr(), i, j ) );

    if ( status != GSL_SUCCESS )    throw std::out_of_range("permutation out-of-range");

}

////////////////////////////////////////////////////////////

bool permutation::isValid() const
{
    if ( isNull() )    return false;

    return ( gsl_permutation_valid ( const_ptr() ) == GSL_SUCCESS ? true : false );
}

////////////////////////////////////////////////////////////

void permutation::reverse()
{
    if ( isNull() )    return;

    gsl_permutation_reverse( ptr() );
}

////////////////////////////////////////////////////////////

permutation permutation::inverse() const throw( permutation_uninitialised )
{
    if ( isNull() )
        throw permutation_uninitialised();

    permutation output( size() );
    gsl_permutation_inverse( output.ptr(), const_ptr() );
    return output;
}

////////////////////////////////////////////////////////////

bool permutation::next() throw ( permutation_uninitialised )
{
    if ( isNull() )
        throw permutation_uninitialised();

    int status( gsl_permutation_next( ptr() ) );

    return ( status != GSL_FAILURE ? true : false );
}

////////////////////////////////////////////////////////////

bool permutation::prev() throw ( permutation_uninitialised )
{
    if ( isNull() )
        throw permutation_uninitialised();

    int status( gsl_permutation_prev( ptr() ) );

    return ( status != GSL_FAILURE ? true : false );
}

////////////////////////////////////////////////////////////

void permutation::free()
{
    if ( hasValue() )  gsl_permutation_free( ptr() );
}

////////////////////////////////////////////////////////////

const permutation operator*( const permutation& left, const permutation& right ) throw( permutation_size_mismatch )
{
    permutation output( left.size() );

    int status( gsl_permutation_mul( output.ptr(), left.const_ptr(), right.const_ptr() ) );

    if ( status == GSL_EINVAL )
        throw permutation_size_mismatch();

    return output;
}

////////////////////////////////////////////////////////////

}
