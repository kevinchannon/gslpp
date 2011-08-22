#include "complex.h"

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

void complex::abs( real rR )
{
	// Keep the effective arg the same, but scale abs
	real rArg = this->arg();
	this->ref() = gsl_complex_polar( rR, rArg );
}

////////////////////////////////////////////////////////////

void complex::arg( real rQ )
{
	// Keep the effective abs the same, but change the argument
	real rAbs = this->abs();
	this->ref() = gsl_complex_polar( rAbs, rQ );
}

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////