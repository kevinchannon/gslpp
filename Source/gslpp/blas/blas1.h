#pragma once

#include <gsl/gsl_blas.h>

#include "../Common/macros.h"
#include "..Vector/vector.h"

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

BEGIN_BLAS_NAMESPACE

////////////////////////////////////////////////////////////

/// Computes the sum: a + x^{T}y
::gsl::realVector dot( real a, const ::gsl::realVector& x, const ::gsl::realVector& y )
	throw ( std::bad_alloc, ::gsl::vector_size_mismatch );

/// Computes the scalar product: x^{T}y
::gsl::realVector dot( const ::gsl::realVector& x, const ::gsl::realVector& y )
	throw ( std::bad_alloc, ::gsl::vector_size_mismatch );

/// Computes the Euclidean norm: ||x||_{2} = \sqrt{ \sum{ x_{i}^{2} } }
///
/// Will not throw
real nrm2( const ::gsl::realVector& x );

/// Computes the absolute sum: \sum{ |x_{i}| }
///
/// Will not throw
real asum( const ::gsl::realVector& x );

/// Return the index of the element with the largest absolute magnitude in the vector x
/// If the largest vaule occurs several times, the first instance found is returned
::gsl::realVector::size_type imax( const ::gsl::realVector& x );

/// Exchange the elements of x and y
void swap( ::gsl::realVector& x, ::gsl::realVector& y ) throw (::gsl::vector_size_mismatch );

/// Copy the elements of x into y
void copy( const ::gsl::realVector& x, ::gsl::realVector& y ) throw (::gsl::vector_size_mismatch );

/// Compute the sum: y = ax + y for the vectors x and y
void axpy( real a, const ::gsl::realVector& x, ::gsl::realVector& y ) throw (::gsl::vector_size_mismatch );

/// Scale the vector x by the factor a
::gsl::realVector scal( real a, const ::gsl::realVector& x);

/// Compute a Givens rotation (c,s) which zeros the vector (a,b)
/// a & b are over-written by the routine
void rotg( ::gsl::realVector& a, ::gsl::realVector& b, ::gsl::realVector& c, ::gsl::realVector& s );


////////////////////////////////////////////////////////////

END_BLAS_NAMESPACE

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////