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

/////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////

gsl::polynomial& gsl::polynomial::operator=( const gsl::polynomial& original )
{
	gsl::polynomial temp( original );
	this->swap( temp );
	return *this;
}

/////////////////////////////////////////////////////////////

gsl::polynomial& gsl::polynomial::operator+=( const gsl::polynomial& right )
{
	// If right is filled with zeros, then there's nothing to do, just return immediately
	if ( right.coeff_end() == std::find_if( right.coeff_begin(), right.coeff_end(), std::bind2nd(std::not_equal_to< value_type>(), complexZero ) ) )
		return *this;
		
	// We're going to change the coefficients (so the roots will probably change)
	M_bRootsKnown = false;
	
	// If this is filled with zeros, then we can just set this = right and return
	if ( this->coeff_end() == std::find_if( this->coeff_begin(), this->coeff_end(), std::bind2nd(std::not_equal_to< value_type>(), complexZero ) ) )
		return *this = -right;
		
	// Add the first N terms
	size_type N = std::min( this->M_vzCoeffs.size(), right.M_vzCoeffs.size() );
	std::transform(this->coeff_begin(), this->coeff_begin() + N, right.coeff_begin(),
		this->coeff_begin(), std::plus< value_type >());
	
	// If right has more coefficients than this, we need subtract the extra terms from this
	if (this->M_vzCoeffs.size() < right.M_vzCoeffs.size() ){
		this->M_vzCoeffs.resize( right.M_vzCoeffs.size(), complexZero );
		std::copy(right.coeff_begin() + N, right.coeff_end(), this->coeff_begin() + N);
		
		// We've added new coeffs, so we don't necessarily know the order now
		M_bOrderKnown = false;
	}
		
	return *this;
}

/////////////////////////////////////////////////////////////

gsl::polynomial& gsl::polynomial::operator-=( const gsl::polynomial& right )
{
	// If right is filled with zeros, then there's nothing to do, just return immediately
	if ( right.coeff_end() == std::find_if( right.coeff_begin(), right.coeff_end(), std::bind2nd(std::not_equal_to< value_type>(), complexZero ) ) )
		return *this;
		
	// We're going to change the coefficients (so the roots will probably change)
	M_bRootsKnown = false;
	
	// If this is filled with zeros, then we can just set this = r-ight and return (need to implement unary - op first)
//	if ( this->coeff_end() == std::find_if( this->coeff_begin(), this->coeff_end(), std::bind2nd(std::not_equal_to< value_type>(), complexZero ) ) )
//		return *this = right;
		
	// Add the first N terms
	size_type N = std::min( this->M_vzCoeffs.size(), right.M_vzCoeffs.size() );
	std::transform(this->coeff_begin(), this->coeff_begin() + N, right.coeff_begin(),
		this->coeff_begin(), std::minus< value_type >());
	
	// If right has more coefficients than this, we need copy the extra terms to this
	if (this->M_vzCoeffs.size() < right.M_vzCoeffs.size() ){
		this->M_vzCoeffs.resize( right.M_vzCoeffs.size(), complexZero );
		std::transform(this->coeff_begin() + N, this->coeff_end(), right.coeff_begin() + N,
			this->coeff_begin() + N, std::minus< value_type >());
		
		// We've added new coeffs, so we don't necessarily know the order now
		M_bOrderKnown = false;
	}
		
	return *this;
}

/////////////////////////////////////////////////////////////

gsl::polynomial& gsl::polynomial::operator*=( const gsl::polynomial& right )
{
	
}

/////////////////////////////////////////////////////////////

gsl::polynomial& gsl::polynomial::operator/=( const gsl::polynomial& right )
{
	
}

/////////////////////////////////////////////////////////////

bool gsl::polynomial::operator==( const gsl::polynomial& right ) const
{
	
}

/////////////////////////////////////////////////////////////

void polynomial::swap( gsl::polynomial &other )
{
	std::swap( this->M_pGSLData, other.M_pGSLData );
	std::swap( this->M_vzCoeffs, other.M_vzCoeffs );
	std::swap( this->M_vzRoots, other.M_vzRoots );
	std::swap( this->M_bRootsKnown, other.M_bRootsKnown );
	std::swap( this->M_bOrderKnown, other.M_bOrderKnown );
	std::swap( this->M_iOrder, other.M_iOrder );
}

////////////////////////////////////////////////////////////

polynomial::~polynomial(){}

polynomial::size_type polynomial::order()
{
	if ( M_bOrderKnown )
		return M_iOrder;
	
	// Find the largest non-zero coefficient
	auto lambda_goodCoeff = []( value_type z ){ return z != complexZero && z != complexEmpty; };
	M_iOrder = std::distance( coeff_begin(), std::find_if( coeff_rbegin(), coeff_rend(), lambda_goodCoeff ).base()) - 1;
	
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
	
	// Find the roots
	! bComplexCoeffs ? M_roots_real_coeffs() : M_roots_complex_coeffs();
		
	M_bRootsKnown = true;
	return roots();	// Recurse to return the roots
}

////////////////////////////////////////////////////////////

void polynomial::M_roots_complex_coeffs()
{
	switch ( this->order() ){
		case 1 :
		{
			M_vzRoots.resize(1);
			M_vzRoots[0] = -this->coeff(0)/this->coeff(1);
			break;
		}
		case polynomial::empty:
		case 0 :
		{
			M_vzRoots.clear();	// No roots to be found in these cases
			break;
		}
		default :
		{
			// Not currently supporting higher order complex coefficients
			M_vzRoots.clear();
		}
	}
}

////////////////////////////////////////////////////////////

void polynomial::M_roots_real_coeffs()
{
	switch ( this->order() ){
		case 1 :
		{
			real a = this->coeff(1).real();	// Guaranteed to be non-zero
			real b = this->coeff(0).real();
			M_vzRoots.resize(1);
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
			
			M_vzRoots.resize(2);
			M_vzRoots[0] = value_type(GSL_REAL(z0), GSL_IMAG(z0));
			if ( this->coeff(0).real() != 0 ){
				M_vzRoots[1] = value_type(GSL_REAL(z1), GSL_IMAG(z1));
			}
			else{
				M_vzRoots[1] = value_type(GSL_REAL(z0), GSL_IMAG(z0));
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
			
			M_vzRoots.resize(3);
			M_vzRoots[0] = value_type(GSL_REAL(z0), GSL_IMAG(z0));
			M_vzRoots[1] = value_type(GSL_REAL(z1), GSL_IMAG(z1));
			M_vzRoots[2] = value_type(GSL_REAL(z2), GSL_IMAG(z2));
			break;
		}
		case polynomial::empty:
		case 0 :
		{
			M_vzRoots.clear();	// No roots to be found in these cases
			break;
		}
		default :
		{
		   size_type N = this->order() + 1;
		 
		   M_pGSLData = gsl_poly_complex_workspace_alloc ( N );
		   
		   real* a = new real[ N ];
		   auto lambda_complexToRealCopier = []( const_reference z ){ return z.real(); };
		   std::transform(this->coeff_begin(), this->coeff_begin() + N, a, lambda_complexToRealCopier );
		   
		   real* z = new real[ 2*(N - 1 )];
		   
		   // Solve!
		   gsl_poly_complex_solve (a, N, M_pGSLData, z);
		   
			M_vzRoots.resize(N - 1);
		   for ( size_t i = 0; i < 2*(N - 1); i+=2 ){
			   M_vzRoots[i/2].real(z[i]);
			   M_vzRoots[i/2].imag(z[i + 1]);
		   }
		 
		   gsl_poly_complex_workspace_free ( M_pGSLData );
		   delete[] a;
		   delete[] z;
		}
	}
}

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////