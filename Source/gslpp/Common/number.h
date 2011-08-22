#pragma once

#include "macros.h"

#include <gsl/gsl_math.h>

////////////////////////////////////////////////////////////

typedef double real;

const real realZero = 0.0;
const real realOne = 1.0;
const real realEmpty = GSL_NAN;
const real NaN = GSL_NAN;
const real realPlusInf = GSL_POSINF;
const real realMinusInf = GSL_NEGINF;

inline bool IsEmpty( real x ){	return gsl_isnan(x);	}
inline bool IsNaN( real x ){	return gsl_isnan(x);	}
inline bool IsFinite( real x){	return gsl_finite(x);	}

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

/// Base of natural logarithm
const real e = M_E;

/// Base two logarithm of e
const real log2e = M_LOG2E;

/// Base ten logarithm of e
const real log10e = M_LOG10E;

/// Square-root of two
const real sqrt2 = M_SQRT2;

/// Square-root of one-half
const real sqrt_half = M_SQRT1_2;

/// Square-root of three
const real sqrt3 = M_SQRT3;

/// pi
const real pi = M_PI;

/// pi / 2
const real half_pi = M_PI_2;

/// pi / 4
const real quater_pi = M_PI_4;

/// square-root of pi
const real sqrt_pi = M_SQRTPI;

/// two divided by the square-root of pi
const real two_over_sqrt_pi = M_2_SQRTPI;

/// recprocal of pi
const real one_over_pi = M_1_PI;

/// twice the reciprocal of pi
const real two_over_pi = M_2_PI;

/// Natural logarithm of ten
const real ln10 = M_LN10;

/// Natural logarithm of two
const real ln2 = M_LN2;

/// Natural logarithn of pi
const real ln_pi = M_LNPI;

/// Euler's constant
const real euler = M_EULER;

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE