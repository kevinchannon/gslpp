#include "polynomial.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include <gsl/gsl_complex.h>

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

polynomial::polynomial() : gsl_base_ptr(0), M_bRootsKnown(false), M_bOrderKnown(true), M_iOrder(0)
{}

////////////////////////////////////////////////////////////

polynomial::polynomial( size_type N) throw ( std::bad_alloc ) :	M_bRootsKnown(false), M_bOrderKnown(true), M_iOrder(0)
{
	M_vzCoeffs.resize( N , complexZero );
	M_vzRoots.resize( N > 0 ? N - 1 : 0);
}

//////////////////////////////////// ////////////////////////

polynomial::polynomial( const gsl::polynomial& original )
{
	M_vzCoeffs = original.M_vzCoeffs;
	M_vzRoots = original.M_vzRoots;
	M_bRootsKnown = original.M_bRootsKnown;
	M_bOrderKnown = original.M_bOrderKnown;
	M_iOrder = original.M_iOrder;
	
	// Don't create a new GSL workspace for this polynomial, if it's needed it'll
	// be created at the point of use
}

////////////////////////////////////////////////////////////

polynomial::~polynomial(){}

polynomial::size_type polynomial::order()
{
	if ( M_bOrderKnown )
		return M_iOrder;
	
	if ( coeff_begin() != coeff_end() )
	{
		// Find the largest non-zero coefficient
		auto lambda_goodCoeff = []( value_type z ){ return z != complexZero && z != complexEmpty; };
		M_iOrder = std::distance( coeff_begin(), std::find_if( coeff_rbegin(), coeff_rend(), lambda_goodCoeff ).base()) - 1;
	}
	else
		M_iOrder = 0;
	
	M_bOrderKnown = true;
	return M_iOrder;
}	

////////////////////////////////////////////////////////////

void polynomial::add_term( polynomial::const_reference zNewCoeff )
{
	M_vzCoeffs.push_back( zNewCoeff );
	M_vzRoots.push_back( complexEmpty );
	
	if ( zNewCoeff != complexZero && zNewCoeff != complexEmpty )
	{
		M_bRootsKnown = false;
		M_bOrderKnown = false;
	}
}

////////////////////////////////////////////////////////////

void polynomial::resize( polynomial::size_type iNewOrder )
{
	M_vzCoeffs.resize( iNewOrder + 1, complexZero );
	M_vzRoots.resize( iNewOrder + 1, complexEmpty );
	
	M_bOrderKnown = false;
	M_bRootsKnown = false;
}

////////////////////////////////////////////////////////////

std::vector< polynomial::value_type > polynomial::roots()
{	
	if ( M_bRootsKnown )	// Return only up to the first non-empty value
		return std::vector< value_type >(M_vzRoots.begin(), std::find( M_vzRoots.begin(), M_vzRoots.end(), complexEmpty ));
	
	// Decide if we only have real coefficients
	bool bComplexCoeffs = this->coeff_end() != std::find_if( this->coeff_begin(), this->coeff_end(),
		[]( const_reference z ){ return z.imag() != realZero; } );
	
	if ( bComplexCoeffs ){
		M_roots_complex_coeffs();
		return std::vector< value_type >();
	}
	else
		M_roots_real_coeffs();
		
	M_bRootsKnown = true;
	return roots();	// Recurse to get the roots
}

////////////////////////////////////////////////////////////

void polynomial::M_roots_complex_coeffs()
{
	std::cerr << "Solution of complex polynomials with complex coefficients not currently supported" << std::endl;
}

////////////////////////////////////////////////////////////

void polynomial::M_roots_real_coeffs()
{
	switch ( this->order() ){
		case 0 : break;	// nothing to do (no roots)
		case 1 :
		{
			real a = this->coeff(1).real();	// Guaranteed to be non-zero
			real b = this->coeff(0).real();
			M_vzRoots[0] = value_type( -b/a, realZero );
			break;
		}
		case 2 :
		{
			gsl_complex z0, z1;
			real a = this->coeff(2).real();
			real b = this->coeff(1).real();
			real c = this->coeff(0).real();
			
			gsl_poly_complex_solve_quadratic (a, b, c, &z0, &z1);
			
			M_vzRoots[0] = value_type(GSL_REAL(z0), GSL_IMAG(z0));
			if ( this->coeff(0).real() != 0 ){
				M_vzRoots[1] = value_type(GSL_REAL(z1), GSL_IMAG(z1));
			}
			break;
		}
		case 3 :
		{
			gsl_complex z0, z1, z2;
			real a = this->coeff(2).real() / this->coeff(3).real();
			real b = this->coeff(1).real() / this->coeff(3).real();
			real c = this->coeff(0).real() / this->coeff(3).real();
			
			gsl_poly_complex_solve_cubic (a, b, c, &z0, &z1, &z2);
			
			M_vzRoots[0] = value_type(GSL_REAL(z0), GSL_IMAG(z0));
			M_vzRoots[1] = value_type(GSL_REAL(z1), GSL_IMAG(z1));
			M_vzRoots[2] = value_type(GSL_REAL(z2), GSL_IMAG(z2));
			break;
		}
		default :
		{
		   size_type size = this->order() + 1;
		 
		   gsl_poly_complex_workspace* ws = gsl_poly_complex_workspace_alloc ( size );
		   
		   real* a = new real[ size ];
		   auto lambda_complexToRealCopier = []( const_reference z ){ return z.real(); };
		   std::transform(this->coeff_begin(), this->coeff_begin() + size, a, lambda_complexToRealCopier );
		   
		   real* z = new real[ 2*(size - 1 )];
		   
		   // Solve!
		   gsl_poly_complex_solve (a, size, ws, z);
		   
		   for ( size_t i = 0; i < 2*(size - 1); i+=2 ){
			   M_vzRoots[i/2].real(z[i]);
			   M_vzRoots[i/2].imag(z[i + 1]);
		   }
		 
		   gsl_poly_complex_workspace_free (ws);
		   delete[] a;
		   delete[] z;
		}
	}
}

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////