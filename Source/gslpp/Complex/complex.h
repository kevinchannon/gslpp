#pragma once

#include <iostream>

#include "../Common/macros.h"
#include "../Common/number.h"
#include "../Common/gslstructbase.h"

#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

class complex : public gsl_base< gsl_complex >
{
public:

	/// Default constructor
	complex(){}
	
	/// Construct from real and complex components
	complex( real X ){
		this->x() = X;
		this->y() = realZero;
	}
	
	/// Construct from real and complex components
	complex( real X, real Y ){
		this->x() = X;
		this->y() = Y;
	}
	
	/// Copy constructor
	complex( const gsl::complex& z ){
		M_GSLData.dat[0] = z.x();
		M_GSLData.dat[1] = z.y();
	}
	
	/// Copy from a gsl_complex struct
	complex( const gsl_complex& z ){
		this->ref().dat[0] = z.dat[0];
		this->ref().dat[1] = z.dat[1];
	}
	
	/// type-cast to real
	operator real(){	return this->abs();	}
	
	/// Swap, wraps std:swap
	void swap( gsl::complex& other ){
		std::swap( *this, other );
	}
	
	/// Assignment operator, complex
	gsl::complex& operator=( const gsl::complex& right ){
		if ( this != &right )	M_GSLData = right.const_ref();
		return *this;
	}
	
	/// Assignment from a real
	gsl::complex& operator=( const real& right ){
		this->x() = right;
		this->y() = realZero;
		
		return *this;
	}
	
	/// Get the real component
	inline const real& x() const{	return GSL_REAL( this->const_ref() );	}
	
	/// Set the real component by assignment
	inline real& x(){	return GSL_REAL( this->ref() );	}
	
	/// Set the real component
	inline void x( real X ){ 	this->x() = X;	}
	
	/// Get the imaginary component
	inline const real& y() const{	return GSL_IMAG( this->const_ref() );	}
	
	/// Set the imaginary component by assignment
	inline real& y(){	return GSL_IMAG( this->ref() );	}
	
	/// Set the imaginary component
	inline void y( real Y ){	this->y() = Y;	}
	
	/// Set the magnitude, keeps the argument the same
	void abs( real R );
	
	/// Set the argument, keeps the magnitude the same
	void arg( real Q );
	
	/// Get the magnitude, |z|
	inline real abs() const{	return gsl_complex_abs( this->const_ref() );	}
	
	/// Get the argument
	inline real arg() const{	return gsl_complex_arg( this->const_ref() );	}
	
	/// Get the square of the magnitude, |z|^2
	inline real abs2() const{	return gsl_complex_abs2( this->const_ref() );	}
	
	/// Get the natural log of the magnitude, Allows accurate evaluation of ln|z| when
	/// |z| is close to unity, where a naive evaluation would lead to loss of precision
	inline real log_abs() const{	return gsl_complex_logabs( this->const_ref() );	}
	
	/// Get the complex conjugate
	inline gsl::complex conj() const{	return gsl_complex_conjugate( this->const_ref() );	}
	
	/// Overloaded unitary operators
	gsl::complex& operator+=( const gsl::complex& right ){
		this->x() += right.x();
		this->y() += right.y();
		
		return *this;
	}
	gsl::complex& operator+=( real X ){
		this->x() += X;
		return *this;
	}
	
	gsl::complex& operator-=( const gsl::complex& right ){
		this->x() -= right.x();
		this->y() -= right.y();
		
		return *this;
	}
	gsl::complex& operator-=( real X ){
		this->x() -= X;
		return *this;
	}
	
	gsl::complex& operator*=( const gsl::complex& right ){
		gsl::complex temp( gsl_complex_mul(this->const_ref(), right.const_ref()) );
		*this = temp;
		
		return *this;
	}
	gsl::complex& operator*=( real X ){
		this->x() *= X;
		this->y() *= X;
		return *this;
	}
	
	gsl::complex& operator/=( const gsl::complex& right ){
		gsl::complex temp( gsl_complex_div(this->const_ref(), right.const_ref()) );
		*this = temp;
		
		return *this;
	}
	gsl::complex& operator/=( real X ){
		this->x() /= X;
		this->y() /= X;
		return *this;
	}
};

////////////////////////////////////////////////////////////

bool operator==( const gsl::complex& left, const gsl::complex& right )
{
	if ( left.x() != right.x() )
		return false;
	if ( left.y() != right.y() )
		return false;
		
	return true;
}

////////////////////////////////////////////////////////////

inline bool operator!=( const gsl::complex& left, const gsl::complex& right )
{
	return !( left == right );
}

////////////////////////////////////////////////////////////

inline bool operator<( const gsl::complex& left, const gsl::complex& right )
{
	return left.abs() < right.abs();
}

////////////////////////////////////////////////////////////

inline bool operator<=( const gsl::complex& left, const gsl::complex& right )
{
	return left.abs() <= right.abs();
}

////////////////////////////////////////////////////////////

inline bool operator>( const gsl::complex& left, const gsl::complex& right )
{
	return left.abs() > right.abs();
}

////////////////////////////////////////////////////////////

inline bool operator>=( const gsl::complex& left, const gsl::complex& right )
{
	return left.abs() >= right.abs();
}

////////////////////////////////////////////////////////////

inline gsl::complex operator+( const gsl::complex& left, const gsl::complex& right )
{	return gsl_complex_add( left.const_ref(), right.const_ref() );	}

////////////////////////////////////////////////////////////

inline gsl::complex operator+( real left, const gsl::complex& right )
{	return gsl_complex_add_real( right.const_ref(), left );			}

////////////////////////////////////////////////////////////

inline gsl::complex operator+( const gsl::complex& left, real right )
{	return gsl_complex_add_real( left.const_ref(), right );			}

////////////////////////////////////////////////////////////

inline gsl::complex operator-( const gsl::complex& left, const gsl::complex& right )
{	return gsl_complex_sub( left.const_ref(), right.const_ref() );	}

////////////////////////////////////////////////////////////

inline gsl::complex operator-( real left, const gsl::complex& right )
{	return gsl_complex_negative( gsl_complex_sub_real( right.const_ref(), left ) );	}

////////////////////////////////////////////////////////////

inline gsl::complex operator-( const gsl::complex& left, real right )
{	return gsl_complex_sub_real( left.const_ref(), right );	}

////////////////////////////////////////////////////////////

inline gsl::complex operator*( const gsl::complex& left, const gsl::complex& right )
{	return gsl_complex_mul( left.const_ref(), right.const_ref() );	}

////////////////////////////////////////////////////////////

inline gsl::complex operator*( real left, const gsl::complex& right )
{	return gsl_complex_mul_real( right.const_ref(), left );	}

////////////////////////////////////////////////////////////

inline gsl::complex operator*( const gsl::complex& left, real right )
{	return gsl_complex_mul_real( left.const_ref(), right );			}

////////////////////////////////////////////////////////////

inline gsl::complex operator/( const gsl::complex& left, const gsl::complex& right )
{	return gsl_complex_div( left.const_ref(), right.const_ref() );	}

////////////////////////////////////////////////////////////

inline gsl::complex operator/( real left, const gsl::complex& right )
{	return gsl_complex_inverse( gsl_complex_div_real( right.const_ref(), left ) );	}

////////////////////////////////////////////////////////////

inline gsl::complex operator/( const gsl::complex& left, real right )
{	return gsl_complex_div_real( left.const_ref(), right );			}

////////////////////////////////////////////////////////////

/// Get the square-root of a complex number, the branch cut is the negative real axis,
/// the result always lies in the right half of the complex plane
inline gsl::complex sqrt( const gsl::complex& z )
{	return gsl_complex_sqrt( z.const_ref() );	}

/// Get the complex sqare-root of a real number, x may be negative
inline gsl::complex sqrt( real x )
{	return gsl_complex_sqrt_real( x );	}

/// Get z^a, where both z & a cam be complex.  Computed as exp(log(z)*a)
inline gsl::complex pow( const gsl::complex& z, const gsl::complex& a )
{	return gsl_complex_pow( z.const_ref(), a.const_ref() );		}

/// Get z^a, where z is complex and a is real
inline gsl::complex pow(const gsl::complex& z, real a )
{	return gsl_complex_pow_real( z.const_ref(), a );	}

/// Get the complex exponential of the complex number z
inline gsl::complex exp( const gsl::complex& z )
{	return gsl_complex_exp( z.const_ref() );		}

/// Get the complex natural logarithm of the complex number, z
inline gsl::complex log( const gsl::complex& z)
{	return gsl_complex_log( z.const_ref() );		}

/// Wrapper for log( const gsl::complex& )
inline gsl::complex ln( const gsl::complex& z)
{	return gsl_complex_log( z.const_ref() );		}

/// Get the complex log_10 of a complex number, z
inline gsl::complex log10( const gsl::complex& z )
{	return gsl_complex_log10( z.const_ref() );		}

/// Get the complex base-b logarithm of the complex number z
/// Computed as log(z)/log(b)
inline gsl::complex log_b( const gsl::complex& z, const gsl::complex& b )
{	return gsl_complex_log_b( z.const_ref(), b.const_ref() );		}

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////
