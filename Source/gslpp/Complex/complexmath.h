#pragma once

#include "../Common/macros.h"
#include "complex.h"

#include <gsl/gsl_complex_math.h>

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

/// Get the square-root of a complex number, the branch cut is the negative real axis,
/// the result always lies in the right half of the complex plane
gsl::complex sqrt( const gsl::complex& z );

/// Get the complex sqare-root of a real number, x may be negative
gsl::complex sqrt( real x );

/// Get z^a, where both z & a cam be complex.  Computed as exp(log(z)*a)
gsl::complex pow( const gsl::complex& z, const gsl::complex& a );

/// Get z^a, where z is complex and a is real
gsl::complex pow(const gsl::complex& z, real a );

/// Get the complex exponential of the complex number z
gsl::complex exp( const gsl::complex& z );

/// Get the complex natural logarithm of the complex number, z
gsl::complex log( const gsl::complex& z);

/// Wrapper for log( const gsl::complex& )
gsl::complex ln( const gsl::complex& z);

/// Get the complex log_10 of a complex number, z
gsl::complex log10( const gsl::complex& z );

/// Get the complex base-b logarithm of the complex number z
/// Computed as log(z)/log(b)
gsl::complex log_b( const gsl::complex& z, const gsl::complex& b );

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////