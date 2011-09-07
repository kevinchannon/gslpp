#pragma once

#include <vector>

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
	typedef size_t size_type;
	
	polynomial() : gsl_base_ptr(0), M_bRootsKnown(false){}
	polynomial( size_type N) throw ( std::bad_alloc ) :
		gsl_base_ptr( N > 0 ? gsl_poly_complex_workspace_alloc(N) : 0 ),
//		M_paRoots(0),
		M_bRootsKnown(false)
	{
		if ( M_pGSLData == NULL && N != 0 )
			throw std::bad_alloc();
	}

#ifndef GSLPP_NO_CPP0X	
	template< typename... Args >
	polynomial( real x, Args... args ) throw ( std::bad_alloc ){
		M_add_coefficients( x, args... );
//		M_paRoots = new real[ 2*order() ];
		M_bRootsKnown = false;
		M_pGSLData = gsl_poly_complex_workspace_alloc( order() + 1 );
		if ( M_pGSLData == NULL )
			throw std::bad_alloc();
	}
#endif	// GSLPP_NO_CPP0X

	~polynomial(){
//		if ( M_paRoots != NULL )
//			delete[] M_paRoots;
	}
	
	__INLINE size_type order() const {	return M_vCoeffs.size() - 1;	}	

private:

#ifndef GSLPP_NO_CPP0X
	template< typename T, typename... Args >
	void M_add_coefficients( T v, Args... args ){
		M_vCoeffs.push_back( v );
		M_add_coeff< T >( args... );
	}
	
	template< typename T, typename... Args >
	void M_add_coeff( T v, Args... args ){
		M_vCoeffs.push_back( v );
		M_add_coeff< T >( args... );
	}
	
	template< typename T >
	void M_add_coeff( T v ){	M_vCoeffs.push_back(v);	}
#endif	// GSLPP_NO_CPP0X
	
/// Variables
	std::vector< real > M_vCoeffs;
//	gsl::complex* M_paRoots;
	bool M_bRootsKnown;
};

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////