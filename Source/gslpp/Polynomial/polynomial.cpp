#include "polynomial.h"

#include <algorithm>

#include <gsl/gsl_complex.h>

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

polynomial::polynomial() : gsl_base_ptr(0), M_bRootsKnown(false)
{	M_vzCoeffs.push_back(realZero);	}

////////////////////////////////////////////////////////////

polynomial::polynomial( size_type N) throw ( std::bad_alloc ) :	M_bRootsKnown(false)
{
	M_vzCoeffs.resize( N, realZero );
}

////////////////////////////////////////////////////////////

polynomial::polynomial( const gsl::polynomial& original )
{
	M_vzCoeffs = original.M_vzCoeffs;
	M_vzRoots = original.M_vzRoots;
	M_bRootsKnown = original.M_bRootsKnown;
	
	// Don't create a new GSL workspace for this polynomial, if it's needed it'll
	// be created at the point of use
}

////////////////////////////////////////////////////////////

polynomial::~polynomial(){}

////////////////////////////////////////////////////////////

void polynomial::add_term( polynomial::const_reference zNewCoeff )
{
	M_vzCoeffs.push_back(zNewCoeff);
	M_vzRoots.resize( M_vzRoots.size() + 1 );
	
	M_bRootsKnown = false;	// The roots will change if new terms are added
}

////////////////////////////////////////////////////////////

void polynomial::resize( polynomial::size_type iNewOrder )
{
	M_vzCoeffs.resize( iNewOrder + 1, static_cast< value_type >(realZero) );
	M_vzRoots.resize( iNewOrder + 1 );
	
	M_bRootsKnown = false;
}

////////////////////////////////////////////////////////////

std::vector< polynomial::value_type > polynomial::roots()
{
	std::vector< value_type > out( this->order() > 0 ? this->order() : 1, realEmpty );
	size_type iEffectiveOrder = std::distance( this->coeff_begin(),
		std::find_if( this->coeff_rbegin(), this->coeff_rend(), std::bind1st(std::not_equal_to<value_type>(), 0) ).base());
	switch ( iEffectiveOrder ){
		case 0 : break;	// nothing to do (no roots)
		case 1 :
		{
			out[0] = -( this->coeff(0)/this->coeff(1) );
			break;
		}
		case 2 :
		{
			gsl_complex z0, z1;
			gsl_poly_complex_solve_quadratic (this->coeff(0).real(), this->coeff(1).real(), this->coeff(2).real(), &z0, &z1);
			
			out[0] = value_type(GSL_REAL(z0), GSL_IMAG(z0));
			if ( this->coeff(0).real() != 0 ){
				out[1] = value_type(GSL_REAL(z1), GSL_IMAG(z1));
			}
		}
	}
		
		
}

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////