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

std::ostream &operator<<(std::ostream &os, const gsl::complex& z)
{
	if ( z.x() == 0 && z.y() == 0 ) {
		os << 0;
	}
	else {
		real x = z.x();
		real y = z.y();
		if ( x != 0 )
			os << x;
		if ( x != 0 && y != 0 )
			os << ( y > 0 ? " + " : " - " );
		if ( y != 0 ){
			if ( x == 0 )
				os << ( y > 0 ? "" : "-");
			os << (y > 0 ? y : -y ) << IMAG_SYMB;
		}
	}
		
	return os;
}

////////////////////////////////////////////////////////////