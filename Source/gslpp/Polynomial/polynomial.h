#pragma once

#include <vector>
#include <complex>
#include <numeric>

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
	typedef typename std::vector< std::complex< real > >::reference			reference;
    typedef typename std::vector< std::complex< real > >::const_reference	const_reference;
    typedef typename std::vector< std::complex< real > >::pointer			pointer;
    typedef typename std::vector< std::complex< real > >::const_pointer		const_pointer;
    typedef typename std::vector< std::complex< real > >::value_type		value_type;
    typedef typename std::vector< std::complex< real > >::size_type			size_type;
	
	polynomial() : gsl_base_ptr(0), M_bRootsKnown(false){
		M_vzCoeffs.push_back(realZero);
	}
	
	polynomial( size_type N) throw ( std::bad_alloc ) :
		gsl_base_ptr( N > 0 ? gsl_poly_complex_workspace_alloc(N) : 0 ),
		M_bRootsKnown(false)
	{
		if ( M_pGSLData == NULL && N != 0 )
			throw std::bad_alloc();
	}

#ifndef GSLPP_NO_CPP0X	
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

	~polynomial(){
	}
	
	INLINE size_type order() const {	return M_vzCoeffs.size() - 1;	}	
	
	/// Evaluate the polynomial at the given (complex) point
	/// Uses Horner's method for stability
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