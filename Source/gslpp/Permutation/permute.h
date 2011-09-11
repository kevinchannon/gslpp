#pragma once

#include "../Common/number.h"
#include "../Common/exceptions.h"
#include "../Vector/vector.h"
#include "permutation.h"

#include <gsl/gsl_permute.h>

BEGIN_GSL_NAMESPACE

namespace permute{

	void array( const size_t *p, real *data, size_t n, size_t stride = 1 ) throw ( null_pointer_dereference );
	void arrayInverse( const size_t *p, real *data, size_t n, size_t stride = 1 ) throw ( null_pointer_dereference );

	template< typename T >
	void vector( const permutation& p, gsl::vector< T >& v ) throw (gsl::size_mismatch, gsl::permutation_uninitialised, gsl::vector_uninitialised );
	template< typename T >
	void vectorInverse( const permutation& p, gsl::vector< T >& v ) throw (gsl::size_mismatch, gsl::permutation_uninitialised, gsl::vector_uninitialised );
}

END_GSL_NAMESPACE

template< typename T >
const gsl::vector< T > operator*( const gsl::permutation& p, const gsl::vector< T >& v)
throw (gsl::size_mismatch, gsl::permutation_uninitialised, gsl::vector_uninitialised );
