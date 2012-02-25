#pragma once

#include <vector>
#include <complex>
#include <numeric>
#include <stdexcept>
#include <limits>

#include "../Common/macros.h"
#include "../Common/number.h"
#include "../Common/gslstructbase.h"
#include "../Vector/vector.h"

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
	
	static const size_type empty = std::numeric_limits< size_type >::max();
	
	/// Default constructor
	polynomial();
	
	/// Construct a polynomial of order N
	polynomial( size_type N ) throw ( std::bad_alloc );
	
	/// Copy constructor
	///
	/// Can throw std::bad_alloc
	polynomial( const gsl::polynomial& original );

#ifndef GSLPP_NO_CPP0X	
	/// Construct a polynomial with coefficients specified:
	/// p(z) = \Sum_{i}^{N}arg_{i}*z^{i}
	template< typename... Args >
	polynomial( const std::complex< real >& x, Args... args ) throw ( std::bad_alloc ){
		M_add_coefficients( x, args... );
		M_vzRoots.resize( M_vzCoeffs.size() - 1 );
		M_bRootsKnown = false;
		M_bOrderKnown = false;	// We don't know because we don't know what the values of the coefficients were
		
		// Don't allocate the gsl_poly_complex_workspace here, it is done just before
		// it's needed for finding the roots.
	}
#endif	// GSLPP_NO_CPP0X

	/// Construct from std::vector, replaces any empty values with zeros
	///
	/// Can throw std::bad_alloc
	template < typename T >
	polynomial( const std::vector< T >& v ) : M_bRootsKnown(false), M_bOrderKnown(false)
	{
		M_vzCoeffs.resize(v.size());
		std::replace_copy_if(v.begin(), v.end(), M_vzCoeffs.begin(), std::bind1st(std::equal_to< value_type >(), complexEmpty), complexZero );
	}
	
	/// Construct from gsl::vector, replaces any empty values with zeros
	///
	/// Can throw std::bad_alloc
	template < typename T >
	polynomial( const gsl::vector< T >& v ) : M_bRootsKnown(false), M_bOrderKnown(false)
	{
		M_vzCoeffs.resize(v.size());
		std::replace_copy_if(v.begin(), v.end(), M_vzCoeffs.begin(), std::bind1st(std::equal_to< value_type >(), complexEmpty), complexZero );
	}
	
	/// Construct from an array, replaces any empty values with zeros
	///
	/// Can throw std::bad_alloc
	template < typename T >
	polynomial( const T* a, size_type N ) : M_bRootsKnown(false), M_bOrderKnown(false)
	{
		M_vzCoeffs.resize( N );
		std::replace_copy_if(a, a + N, M_vzCoeffs.begin(), std::bind1st(std::equal_to< value_type >(), complexEmpty), complexZero );
	}

	~polynomial();
	
	/// Copy-assignment operator
	///
	/// Can throw std::bad_alloc
	gsl::polynomial &operator=( const gsl::polynomial &original );
	
	/// Assignment from std::vector
	///
	/// Can throw std::bad_alloc
	template< typename T >
	gsl::polynomial& operator=( const std::vector< T >& original )
	{
		polynomial temp( original );
		this->swap( temp );
		return *this;
	}
	
	/// Assignment from gsl::vector
	///
	/// Can throw std::bad_alloc
	template< typename T >
	gsl::polynomial& operator=( const gsl::vector< T >& original )
	{
		polynomial temp( original );
		this->swap( temp );
		return *this;
	}
	
	/// Unary minus operator: adds the coefficients of right to the corresponding
	/// coefficients of this
	///
	/// will not throw
	gsl::polynomial operator-() const;
	
	/// Unary addition operator: adds the coefficients of right to the corresponding
	/// coefficients of this
	///
	/// will not throw
	gsl::polynomial& operator+=( const gsl::polynomial& right );
	
	/// Unary subtraction operator: subtracts the coefficients of right from the corresponding
	/// coefficients of this
	///
	/// will not throw
	gsl::polynomial& operator-=( const gsl::polynomial& right );
	
	/// Unary multiplication operator: multiplies the coefficients of this by the corresponding
	/// coefficients of right
	///
	/// will not throw
	gsl::polynomial& operator*=( const gsl::polynomial& right );
	
	/// Unary multiplication operator: divides the coefficients of this by the corresponding
	/// coefficients of right
	///
	/// will not throw
//	gsl::polynomial& operator/=( const gsl::polynomial& right );
	
	/// Boolean equals (compares coefficients up to the effective order )
	///
	/// will not throw
	bool operator==( const gsl::polynomial& right ) const;
	
	/// Boolean not equals (compares coefficients up to the effective order
	///
	/// will not throw
	inline bool operator!=( const gsl::polynomial& right ) const {	return !( *this == right );	}
	
	void swap( gsl::polynomial &other );
	
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
		M_bOrderKnown = false;
		return M_vzCoeffs[i];
	}
	
	/// Get the value of the ith order component without range checking
	/// Behaviour is undefined if i exceeds the order of the polynomial
	INLINE const_reference operator[]( size_type i) const {	return M_vzCoeffs[i];	}
	
	/// Get the value of the ith order component without range checking
	/// Behaviour is undefined if i exceeds the order of the polynomial
	INLINE reference operator[]( size_type i)
	{
		M_bRootsKnown = false;
		M_bOrderKnown = false;
		return M_vzCoeffs[i];
	}
	
	/// Get a const_iterator to the first coefficient of the polynomial
	///
	/// Will not throw
	INLINE const_iterator coeff_begin() const {	return M_vzCoeffs.begin();	}
	
	/// Get a iterator to the first coefficient of the polynomial
	///
	/// Will not throw
	INLINE iterator coeff_begin()
	{
		M_bRootsKnown = false;
		M_bOrderKnown = false;
		return M_vzCoeffs.begin();
	}
	
	/// Get a const_iterator to one-past the last coefficient of the polynomial
	///
	/// Will not throw
	INLINE const_iterator coeff_end() const {	return M_vzCoeffs.end();	}
	
	/// Get a iterator to one-past the last coefficient of the polynomial
	///
	/// Will not throw
	INLINE iterator coeff_end()
	{
		M_bRootsKnown = false;
		M_bOrderKnown = false;
		return M_vzCoeffs.end();
	}
	
	/// Get a const_iterator to the first coefficient of the polynomial
	///
	/// Will not throw
	INLINE const_reverse_iterator coeff_rbegin() const {	return M_vzCoeffs.rbegin();	}
	
	/// Get a iterator to the first coefficient of the polynomial
	///
	/// Will not throw
	INLINE reverse_iterator coeff_rbegin()
	{
		M_bRootsKnown = false;
		M_bOrderKnown = false;
		return M_vzCoeffs.rbegin();
	}
	
	/// Get a const_iterator to one-past the last coefficient of the polynomial
	///
	/// Will not throw
	INLINE const_reverse_iterator coeff_rend() const {	return M_vzCoeffs.rend();	}
	
	/// Get a iterator to one-past the last coefficient of the polynomial
	///
	/// Will not throw
	INLINE reverse_iterator coeff_rend()
	{
		M_bRootsKnown = false;
		M_bOrderKnown = false;
		return M_vzCoeffs.rend();
	}
	
	/// Get the effective order of the polynomial, finds the position of the last non-zero
	/// coefficient. If there are no non-zero coefficients, polynomial::empty is returned
	///
	/// Will not throw
	size_type order() const;
	
	/// Get the current capacity of the polynomial (i.e. the highest order component accessible, without
	/// adding new terms, returns polynomial::empty if there are no coefficients
	///
	/// will not throw
	INLINE size_type size() const {	return M_vzCoeffs.size() - 1;	}
	
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
		M_vzCoeffs.push_back( is_empty( v ) ? complexZero : v );
		M_add_coeff< T >( args... );
	}
	
	template< typename T, typename... Args >
	void M_add_coeff( T v, Args... args ){
		M_vzCoeffs.push_back( is_empty( v ) ? complexZero : v );
		M_add_coeff< T >( args... );
	}
	
	template< typename T >
	void M_add_coeff( T v ){	M_vzCoeffs.push_back( is_empty( v ) ? complexZero : v );	}
#endif	// GSLPP_NO_CPP0X

	void M_roots_complex_coeffs();
	void M_roots_real_coeffs();

	INLINE size_type M_order_finder() const{
		// Find the largest non-zero coefficient
		auto lambda_goodCoeff = []( value_type z ){ return z != complexZero && z != complexEmpty; };
		return std::distance( coeff_begin(), std::find_if( coeff_rbegin(), coeff_rend(), lambda_goodCoeff ).base()) - 1;
	}
	
/// Variables
	std::vector< std::complex< real > > M_vzCoeffs;
	std::vector< std::complex< real > > M_vzRoots;
	bool M_bRootsKnown;
	mutable bool M_bOrderKnown;
	mutable size_type M_iOrder;
};

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////

const gsl::polynomial operator+( const gsl::polynomial& p1, const gsl::polynomial& p2 );
const gsl::polynomial operator-( const gsl::polynomial& p1, const gsl::polynomial& p2 );
const gsl::polynomial operator*( const gsl::polynomial& p1, const gsl::polynomial& p2 );

std::ostream& operator<<( std::ostream& out, const gsl::polynomial& p );

////////////////////////////////////////////////////////////