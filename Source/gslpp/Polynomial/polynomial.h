#pragma once

#include <vector>
#include <complex>
#include <numeric>
#include <stdexcept>

#include "../Common/macros.h"
#include "../Common/number.h"
#include "../Common/gslstructbase.h"

#include <gsl/gsl_poly.h>

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

class polynomial : public gsl_base_ptr< gsl_poly_complex_workspace >
{
public:
	typedef typename std::vector< std::complex< real > >::reverse_iterator			reverse_iterator;
    typedef typename std::vector< std::complex< real > >::const_reverse_iterator	const_reverse_iterator;
	typedef typename std::vector< std::complex< real > >::iterator					iterator;
    typedef typename std::vector< std::complex< real > >::const_iterator			const_iterator;
	typedef typename std::vector< std::complex< real > >::reference					reference;
    typedef typename std::vector< std::complex< real > >::const_reference			const_reference;
    typedef typename std::vector< std::complex< real > >::pointer					pointer;
    typedef typename std::vector< std::complex< real > >::const_pointer				const_pointer;
    typedef typename std::vector< std::complex< real > >::value_type				value_type;
    typedef typename std::vector< std::complex< real > >::size_type					size_type;
	
	/// Default constructor
	polynomial();
	
	/// Construct a polynomial of order N
	polynomial( size_type N) throw ( std::bad_alloc );
	
	/// Copy constructor
	polynomial( const gsl::polynomial& original );

#ifndef GSLPP_NO_CPP0X	
	/// Construct a polynomial with coefficients specified:
	/// p(z) = \Sum_{i}^{N}arg_{i}*z^{i}
	template< typename... Args >
	polynomial( const std::complex< real >& x, Args... args ) throw ( std::bad_alloc ){
		M_add_coefficients( x, args... );
		M_vzRoots.resize( this->order() );
		M_bRootsKnown = false;
		
		// Don't allocate the gsl_poly_complex_workspace here, it is done just before
		// it's needed for finding the roots.
	}
#endif	// GSLPP_NO_CPP0X

	~polynomial();
	
	/// Add a term to the polynomial
	///
	/// Can throw std::bad_alloc
	void add_term( const_reference zNewCoeff );
	
	/// Change the order of the polynomial. If the order is increased, the new terms have coefficients of zero
	///
	/// Can throw std::bad_alloc
	void resize( size_type iNewOrder );
	
	/// Get the value of the ith order component
	///
	/// Will throw if i is out of range
	INLINE const_reference coeff( size_type i) const throw ( std::out_of_range ){
		if ( i >= M_vzCoeffs.size() )
			throw std::out_of_range( "Polynomial coefficient exceeds polynomial order" );
		return M_vzCoeffs[i];
	}
	
	/// Get the value of the ith order component
	///
	/// Will throw if i is out of range
	INLINE reference coeff( size_type i)  throw ( std::out_of_range ){
		if ( i >= M_vzCoeffs.size() )
			throw std::out_of_range( "Polynomial coefficient exceeds polynomial order" );
		M_bRootsKnown = false;
		return M_vzCoeffs[i];
	}
	
	/// Get the value of the ith order component without range checking
	/// Behaviour is undefined if i exceeds the order of the polynomial
	INLINE const_reference operator[]( size_type i) const {	return M_vzCoeffs[i];	}
	
	/// Get the value of the ith order component without range checking
	/// Behaviour is undefined if i exceeds the order of the polynomial
	INLINE reference operator[]( size_type i) {	return M_vzCoeffs[i];	}
	
	/// Get a const_iterator to the first coefficient of the polynomial
	///
	/// Will not throw
	INLINE const_iterator coeff_begin() const {	return M_vzCoeffs.begin();	}
	
	/// Get a iterator to the first coefficient of the polynomial
	///
	/// Will not throw
	INLINE iterator coeff_begin() {	return M_vzCoeffs.begin();	}
	
	/// Get a const_iterator to one-past the last coefficient of the polynomial
	///
	/// Will not throw
	INLINE const_iterator coeff_end() const {	return M_vzCoeffs.end();	}
	
	/// Get a iterator to one-past the last coefficient of the polynomial
	///
	/// Will not throw
	INLINE iterator coeff_end() {	return M_vzCoeffs.end();	}
	
	/// Get a const_iterator to the first coefficient of the polynomial
	///
	/// Will not throw
	INLINE const_reverse_iterator coeff_rbegin() const {	return M_vzCoeffs.rbegin();	}
	
	/// Get a iterator to the first coefficient of the polynomial
	///
	/// Will not throw
	INLINE reverse_iterator coeff_rbegin() {	return M_vzCoeffs.rbegin();	}
	
	/// Get a const_iterator to one-past the last coefficient of the polynomial
	///
	/// Will not throw
	INLINE const_reverse_iterator coeff_rend() const {	return M_vzCoeffs.rend();	}
	
	/// Get a iterator to one-past the last coefficient of the polynomial
	///
	/// Will not throw
	INLINE reverse_iterator coeff_rend() {	return M_vzCoeffs.rend();	}
	
	/// Get the order of the polynomial
	///
	/// Will not throw
	INLINE size_type order() const {	return M_vzCoeffs.size() - 1;	}	
	
	/// Evaluate the polynomial at the given (complex) point
	/// Uses Horner's method for stability
	///
	/// Will not throw
	INLINE value_type at( const_reference z ) const{
		return std::accumulate( M_vzCoeffs.rbegin(), M_vzCoeffs.rend(), static_cast< value_type >(realZero),
			[z]( const_reference tot, const_reference curr ){return curr + tot*z;  } );
	}
	
	/// Find the roots of the polynomial
	std::vector< value_type > roots();

private:

#ifndef GSLPP_NO_CPP0X
	template< typename T, typename... Args >
	void M_add_coefficients( T v, Args... args ){
		M_vzCoeffs.push_back( v );
		M_add_coeff< T >( args... );
	}
	
	template< typename T, typename... Args >
	void M_add_coeff( T v, Args... args ){
		M_vzCoeffs.push_back( v );
		M_add_coeff< T >( args... );
	}
	
	template< typename T >
	void M_add_coeff( T v ){	M_vzCoeffs.push_back(v);	}
#endif	// GSLPP_NO_CPP0X
	
/// Variables
	std::vector< std::complex< real > > M_vzCoeffs;
	std::vector< std::complex< real > > M_vzRoots;
	bool M_bRootsKnown;
};

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////