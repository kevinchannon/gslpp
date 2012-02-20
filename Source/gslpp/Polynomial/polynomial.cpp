#include "polynomial.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include <gsl/gsl_complex.h>

#include "../Matrix/matrix.h"

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

polynomial::polynomial() : gsl_base_ptr(0), M_bRootsKnown(false), M_bOrderKnown(true), M_iOrder(0)
{}

////////////////////////////////////////////////////////////

polynomial::polynomial( size_type N) throw ( std::bad_alloc ) :	M_bRootsKnown(false), M_bOrderKnown(true), M_iOrder(0)
{
	M_vzCoeffs.resize( N > 0 ? N : 0, complexZero );
	M_vzRoots.resize( N > 1 ? N - 1 : 0);
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

gsl::polynomial& polynomial::operator=( const gsl::polynomial& original )
{
	gsl::polynomial temp( original );
	this->swap( temp );
	return *this;
}

/////////////////////////////////////////////////////////////

gsl::polynomial polynomial::operator-() const
{
	gsl::polynomial temp( *this );
	std::transform(temp.coeff_begin(), temp.coeff_end(), temp.coeff_begin(), std::bind1st(std::multiplies< value_type >(), -1 ) );
	return temp;
}

/////////////////////////////////////////////////////////////

gsl::polynomial& polynomial::operator+=( const gsl::polynomial& right )
{
	// If right is filled with zeros, then there's nothing to do, just return immediately
	if ( right.coeff_end() == std::find_if( right.coeff_begin(), right.coeff_end(), std::bind2nd(std::not_equal_to< value_type>(), complexZero ) ) )
		return *this;
		
	// We're going to change the coefficients (so the roots will probably change)
	M_bRootsKnown = false;
	
	// If this is filled with zeros, then we can just set this = right and return
	if ( this->coeff_end() == std::find_if( this->coeff_begin(), this->coeff_end(), std::bind2nd(std::not_equal_to< value_type>(), complexZero ) ) )
		return *this = right;
		
	// Add the first N terms
	size_type N = std::min( this->M_vzCoeffs.size(), right.M_vzCoeffs.size() );
	std::transform(this->coeff_begin(), this->coeff_begin() + N, right.coeff_begin(),
		this->coeff_begin(), std::plus< value_type >());
	
	// If right has more coefficients than this, we need to add the extra terms to this
	if (this->M_vzCoeffs.size() < right.M_vzCoeffs.size() ){
		this->resize( right.order() );
		std::copy(right.coeff_begin() + N, right.coeff_end(), this->coeff_begin() + N);
		
		// We've added new coeffs, so we don't necessarily know the order now
		M_bOrderKnown = false;
	}
		
	return *this;
}

/////////////////////////////////////////////////////////////

gsl::polynomial& polynomial::operator-=( const gsl::polynomial& right )
{
	// If right is filled with zeros, then there's nothing to do, just return immediately
	if ( right.coeff_end() == std::find_if( right.coeff_begin(), right.coeff_end(), std::bind2nd(std::not_equal_to< value_type>(), complexZero ) ) )
		return *this;
		
	// We're going to change the coefficients (so the roots will probably change)
	M_bRootsKnown = false;
	
	// If this is filled with zeros, then we can just set this = -right and return (need to implement unary - op first)
	if ( this->coeff_end() == std::find_if( this->coeff_begin(), this->coeff_end(), std::bind2nd(std::not_equal_to< value_type>(), complexZero ) ) ){
		*this = -right;
		return *this;
	}
		
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

gsl::polynomial& polynomial::operator*=( const gsl::polynomial& right )
{
	typedef gsl::matrix< gsl::polynomial::value_type >::element_type xy;
	
	// Get the coefficients into matrices
	gsl::matrix< gsl::polynomial::value_type > m1( std::min(this->M_vzCoeffs.size(), right.M_vzCoeffs.size() ), 1 );
	gsl::matrix< gsl::polynomial::value_type > m2( 1, std::max(this->M_vzCoeffs.size(), right.M_vzCoeffs.size() ) );
	 
	if ( this->M_vzCoeffs.size() < right.M_vzCoeffs.size() ){
		std::copy( this->coeff_begin(), this->coeff_end(), m1.begin() );
		std::copy( right.coeff_begin(), right.coeff_end(), m2.begin() );
	}
	else
	{
		std::copy( right.coeff_begin(), right.coeff_end(), m1.begin() );
		std::copy( this->coeff_begin(), this->coeff_end(), m2.begin() );
	}
	
	std::cout << "\nm1 = " << m1 << std::endl;
	std::cout << "m2 = " << m2 << std::endl;	
	
	// Form the outer product of the two sets of coefficients
	gsl::matrix< gsl::polynomial::value_type > m3 = m1 * m2;
	
	std::cout << m3 << std::endl;
	
	// The elements of this matrix are combined into the output coefficients in three
	// stages:
	//
	// | 1 1 1 1 1 2 2 2 |
	// | 1 1 1 1 2 2 2 3 |
	// | 1 1 1 2 2 2 3 3 |
	// | 1 1 2 2 2 3 3 3 |
	// | 1 2 2 2 3 3 3 3 |
	//
	// Stages 1 & 3 are the same for any matrix dimensions, but stage 2 is absent for a square matrix.
	
	size_type N = m3.rows();
	gsl::polynomial out( m3.rows() + m3.cols() - 2 );
	
	//
	// Stage 1
	//
	for ( size_type i = 0; i < N; ++i ){
		gsl::polynomial::value_type coeffSum = complexZero;
		for ( size_type j = 0; j <= i; ++j )
			coeffSum += m3[ xy(j, i - j) ];
		
		out[i] = coeffSum;
	}
	
	//
	// Stage 2
	//
	size_type M = m3.cols();
	for ( size_type i = N; i < M; ++i ){
		gsl::polynomial::value_type coeffSum = complexZero;
		for ( size_type j = 1; j <= N; ++j )
			coeffSum += m3[ xy(j + i - N, N - j ) ];
		
		out[i] = coeffSum;
	}
	
	//
	// Stage 3
	//
	for ( size_type i = M; i < N + M; ++i ){
		gsl::polynomial::value_type coeffSum = complexZero;
		size_type j_o = M + N;
		for ( size_type j = i - j_o; j < M; ++j )
			coeffSum += m3[ xy( j, N - i + M - 1 ) ];
		
		out[i] = coeffSum;
	}
	
	// Remove any high-order zero coefficients
	out.resize( out.order() );
	
	*this = out;
	
	return *this;
}

/////////////////////////////////////////////////////////////

// gsl::polynomial& gsl::polynomial::operator/=( const gsl::polynomial& right )
// {
	
// }

/////////////////////////////////////////////////////////////

bool polynomial::operator==( const gsl::polynomial& right ) const
{
	size_type iThisOrder = this->M_order_finder();
	size_type iRightOrder = right.M_order_finder();
	
	if ( iThisOrder != iRightOrder )
		return false;
	
	return std::equal( this->coeff_begin(), this->coeff_begin() + iThisOrder + 1, right.coeff_begin() );
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

polynomial::size_type polynomial::order() const
{
	if ( M_bOrderKnown )
		return M_iOrder;
	
	M_iOrder = this->M_order_finder();
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
	std::cerr << "  Resizing polynomial..." << std::endl;
	std::cerr << "     Current size: coeffs = " << M_vzCoeffs.size() << " roots = " << M_vzRoots.size() << std::endl;
	std::cerr << "     New size: " << iNewOrder + 1 << std::endl;
	
	M_vzCoeffs.resize( iNewOrder > 0 ? iNewOrder + 1 : 0, complexZero );
	M_vzRoots.resize( iNewOrder, complexEmpty );
	
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

const gsl::polynomial operator+( const gsl::polynomial& p1, const gsl::polynomial& p2 )
{
	gsl::polynomial out( p1 );
	out += p2;
	return out;
}

////////////////////////////////////////////////////////////

const gsl::polynomial operator-( const gsl::polynomial& p1, const gsl::polynomial& p2 )
{
	
	gsl::polynomial out( p1 );
	out -= p2;
	return out;
}

////////////////////////////////////////////////////////////

const gsl::polynomial operator*( const gsl::polynomial& p1, const gsl::polynomial& p2 )
{
	
	gsl::polynomial out( p1 );
	out *= p2;
	return out;
}

////////////////////////////////////////////////////////////