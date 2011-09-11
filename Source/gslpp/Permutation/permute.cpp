#include "permute.h"
#include "../Common/exceptions.h"

BEGIN_GSL_NAMESPACE

namespace permute{

	void array( const size_t *p, real *data, size_t n, size_t stride ) throw ( null_pointer_dereference )
	{
		if ( p == NULL || data == NULL )
			throw null_pointer_dereference();

		gsl_permute( p, data, stride, n );
	}

	void arrayInverse( const size_t *p, real *data, size_t n, size_t stride ) throw ( null_pointer_dereference )
	{
		if ( p == NULL || data == NULL )
			throw null_pointer_dereference();

		gsl_permute_inverse( p, data, stride, n );
	}

	template< typename T >
	void vector( const permutation& p, gsl::vector< T >& v )
	throw (gsl::size_mismatch, gsl::permutation_uninitialised, gsl::vector_uninitialised )
	{
		if ( p.size() != v.size() )
			throw gsl::size_mismatch();

		if ( p.isNull() )
			throw gsl::permutation_uninitialised();

		if ( v.isNull() )
			throw gsl::vector_uninitialised();

		gsl_permute( p.const_ptr()->data, v.data(), 1, v.size() );
	}

	template< typename T >
	void vectorInverse( const permutation& p, gsl::vector< T >& v )
	throw (gsl::size_mismatch, gsl::permutation_uninitialised, gsl::vector_uninitialised )
	{
		if ( p.size() != v.size() )
			throw gsl::size_mismatch();

		if ( p.isNull() )
			throw gsl::permutation_uninitialised();

		if ( v.isNull() )
			throw gsl::vector_uninitialised();

		gsl_permute_inverse( p.const_ptr()->data, v.data(), 1, v.size() );
	}
}

END_GSL_NAMESPACE

template< typename T >
const gsl::vector< T > operator*( const gsl::permutation& p, const gsl::vector< T >& v)
throw (gsl::size_mismatch, gsl::permutation_uninitialised, gsl::vector_uninitialised )
{
    if ( p.size() != v.size() )
        throw gsl::size_mismatch();

    if ( p.isNull() )
        throw gsl::permutation_uninitialised();

    gsl::vector< T > out( v );
    gsl_permute( p.const_ptr()->data, out.data(), out.stride(), out.size() );

    return out;
}
