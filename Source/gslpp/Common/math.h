#pragma once

#include "macros.h"
#include "number.h"

#include <gsl/gsl_math.h>

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

/// Computes the value of $log(1 + x)$ in a way that is accurate for
/// small values of $x$
INLINE real log1p( real x )
{	return gsl_log1p( x );	}

/// Compute the value of $exp(x) - 1$ in a way that is accurate for
// small values of $x$
INLINE real expm1( real x )
{	return gsl_expm1( x );	}

/// Compute the value of $\sqrt{x^2 + y^2}$ in a way that avoids overflow
INLINE real hypot( real x, real y )
{	return gsl_hypot(x,y);	}

/// Compute the value of $f\cdot 2^e$
INLINE real ldexp( const gsl::floating_point& x )
{	return gsl_ldexp(x.f(),x.e());	}

/// Split the number $x$ into its normalised fraction $f$ and exponent $e$,
/// such that $x = f\cdot 2^e$ and $0.5 \leq f < 0.5$. If $x = 0$, both $f$ \&
/// $e$ are set to zero.
INLINE gsl::floating_point frexp( real x )
{	
	return gsl::floating_point(x);
}

/// Computes the power $x^n$ for integer $n$. The power is computed efficiently\mdash
/// for example, $x^8$ is computed as $((x^2)^2)^2$, requiring only three multiplications
INLINE real pow( real x, int n )
{	return gsl_pow_int(x,n);	}

/// These functions efficiently compute small integer powers
INLINE real pow_2( real x ){	return gsl_pow_2( x );	}
INLINE real pow_3( real x ){	return gsl_pow_3( x );	}
INLINE real pow_4( real x ){	return gsl_pow_4( x );	}
INLINE real pow_5( real x ){	return gsl_pow_5( x );	}
INLINE real pow_6( real x ){	return gsl_pow_6( x );	}
INLINE real pow_7( real x ){	return gsl_pow_7( x );	}
INLINE real pow_8( real x ){	return gsl_pow_8( x );	}
INLINE real pow_9( real x ){	return gsl_pow_9( x );	}

/// Determine the sign of x
INLINE gsl::sign_type sign( real x )
{	return x >= 0 ? gsl::positive : gsl::negative;	}

/// Test x to see if it's odd
INLINE bool is_odd( int x ){	return static_cast< bool >( x % 2 );	}

/// Test x to see if it's even
INLINE bool is_even( int x ){	return ! is_odd(x);		}

/// return the min of two numbers, just wraps std::min
template< typename T > INLINE T min( T x1, T x2 ){	return std::min( x1, x2 );	}

/// return the max of two numbers, just wraps std::max
template< typename T > INLINE T max( T x1, T x2 ){	return std::max( x1, x2 );	}

/// Determine whether x & y are approximately equal to a relative accuracy $\varepsilon$
/// The relative accuracy is measured using an interval size $2\delta$, where $\delta = 2^k\varepsilon$
/// and $k$ is the maximum base-2 exponent of x \& y, as computed by the function frexp.
/// Returns 0 if x & y are determined equal, -1 if x < y and +1 if x > y
enum equality_type{
	less_than = -1,
	equal_to = 0,
	greater_than = 1
};
INLINE gsl::equality_type fcmp( real x, real y, real epsilon)
{	return static_cast< equality_type >( gsl_fcmp(x,y,epsilon) );	}

END_GSL_NAMESPACE