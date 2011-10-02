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

class complex;

////////////////////////////////////////////////////////////

class polynomial : public gsl_base_ptr< gsl_poly_complex_workspace >
{
public:
	typedef typename std::vector< std::complex< real > >::reverse_iterator			reverse_iterator;
    typedef typename std::vector< std::complex< real > >::const_reverse_iterator	const_reverse_iterator;
	typedef typename std::vector< std::complex< real > >::iterator			iterator;
    typedef typename std::vector< std::complex< real > >::const_iterator	const_iterator;
	typedef typename std::vector< std::complex< real > >::reference			reference;
    typedef typename std::vector< std::complex< real > >::const_reference	const_reference;
    typedef typename std::vector< std::complex< real > >::pointer			pointer;
    typedef typename std::vector< std::complex< real > >::const_pointer		const_pointer;
    typedef typename std::vector< std::complex< real > >::value_type		value_type;
    typedef typename std::vector< std::complex< real > >::size_type			size_type;
	
	/// Default constructor
	polynomial() : gsl_base_ptr(0), M_bRootsKnown(false){
		M_vzCoeffs.push_back(realZero);
	}
	
	/// Construct a polynomial of order N
	polynomial( size_type N) throw ( std::bad_alloc ) :
		gsl_base_ptr( gsl_poly_complex_workspace_alloc(N + 1) ),
		M_bRootsKnown(false)
	{
		if ( M_pGSLData == NULL )
			throw std::bad_alloc();
	}
	
	/// Copy constructor
	polynomial( const gsl::polynomial& original ){
		M_vzCoeffs = original.M_vzCoeffs;
		M_vzRoots = original.M_vzRoots;
		M_bRootsKnown = original.M_bRootsKnown;
		
		// Create a new GSL workspace for this polynomial
		M_pGSLData = gsl_poly_complex_workspace_alloc( this->order() + 1 );
		if ( M_pGSLData == NULL )
			throw std::bad_alloc();
		
		// Fill in the workspace with details from the original
		M_pGSLData->nc = original.M_pGSLData->nc;
		size_t nc2 = M_pGSLData->nc * M_pGSLData->nc;
		std::copy( original.M_pGSLData->matrix, original.M_pGSLData->matrix + nc2, M_pGSLData->matrix );
	}

#ifndef GSLPP_NO_CPP0X	
	/// Construct a polynomial with coefficients specified:
	/// p(z) = \Sum_{i}^{N}arg_{i}*z^{i}
	template< typename... Args >
	polynomial( const std::complex< real >& x, Args... args ) throw ( std::bad_alloc ){
		M_add_coefficients( x, args... );
		M_vzRoots.resize( this->order() );
		M_bRootsKnown = false;
		M_pGSLData = gsl_poly_complex_workspace_alloc( order() + 1 );
		if ( M_pGSLData == NULL )
			throw std::bad_alloc();
	}
#endif	// GSLPP_NO_CPP0X

	~polynomial(){}
	
	/// Add a term to the polynomial
	///
	/// Can throw std::bad_alloc
	void add_term( const std::complex< real >& zNewCoeff );
	
	/// Add a term with the specified order
	///
	/// Can throw std::bad_alloc
	void add_term( const std::complex< real >& zNewCoeff, size_type iOrder );
	
	/// Change the order of the polynomial
	///
	/// Can throw std::bad_alloc
	void resize( size_type iNewOrder );
	
	/// Get the value of the ith order component
	///
	/// Will throw if i is out of range
	INLINE const_reference coeff( size_type i) const throw ( std::out_of_range ){
		if ( i >= M_vzCoeffs.size() )
			throw std::out_of_range( "Polynomial coefficient out exceeds polynomial order" );
		return M_vzCoeffs[i];
	}
	
	/// Get the value of the ith order component
	///
	/// Will throw if i is out of range
	INLINE reference coeff( size_type i)  throw ( std::out_of_range ){
		if ( i >= M_vzCoeffs.size() )
			throw std::out_of_range( "Polynomial coefficient out exceeds polynomial order" );
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
	INLINE std::complex< real > at( const std::complex< real >& z ) const{
		return std::accumulate( M_vzCoeffs.rbegin(), M_vzCoeffs.rend(), std::complex< real >(0.0),
			[z]( const std::complex< real >& tot, const std::complex< real >& curr ){return curr + tot*z;  } );
	}

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