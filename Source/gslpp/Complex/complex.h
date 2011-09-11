#pragma once

#include <iostream>

#include "../Common/macros.h"
#include "../Common/number.h"
#include "../Common/gslstructbase.h"

#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>

#ifdef GSLPP_IMAG_J
	#define IMAG_SYMB "j"
#else
	#define IMAG_SYMB "i"
#endif

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
	INLINE const real& x() const{	return GSL_REAL( this->const_ref() );	}
	
	/// Set the real component by assignment
	INLINE real& x(){	return GSL_REAL( this->ref() );	}
	
	/// Set the real component
	INLINE void x( real X ){ 	this->x() = X;	}
	
	/// Get the imaginary component
	INLINE const real& y() const{	return GSL_IMAG( this->const_ref() );	}
	
	/// Set the imaginary component by assignment
	INLINE real& y(){	return GSL_IMAG( this->ref() );	}
	
	/// Set the imaginary component
	INLINE void y( real Y ){	this->y() = Y;	}
	
	/// Set the magnitude, keeps the argument the same
	void abs( real R );
	
	/// Set the argument, keeps the magnitude the same
	void arg( real Q );
	
	/// Get the magnitude, |z|
	INLINE real abs() const{	return gsl_complex_abs( this->const_ref() );	}
	
	/// Get the argument
	INLINE real arg() const{	return gsl_complex_arg( this->const_ref() );	}
	
	/// Get the square of the magnitude, |z|^2
	INLINE real abs2() const{	return gsl_complex_abs2( this->const_ref() );	}
	
	/// Get the natural log of the magnitude, Allows accurate evaluation of ln|z| when
	/// |z| is close to unity, where a naive evaluation would lead to loss of precision
	INLINE real log_abs() const{	return gsl_complex_logabs( this->const_ref() );	}
	
	/// Get the complex conjugate
	INLINE gsl::complex conj() const{	return gsl_complex_conjugate( this->const_ref() );	}
	
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

INLINE bool operator!=( const gsl::complex& left, const gsl::complex& right )
{
	return !( left == right );
}

////////////////////////////////////////////////////////////

INLINE bool operator<( const gsl::complex& left, const gsl::complex& right )
{
	return left.abs() < right.abs();
}

////////////////////////////////////////////////////////////

INLINE bool operator<=( const gsl::complex& left, const gsl::complex& right )
{
	return left.abs() <= right.abs();
}

////////////////////////////////////////////////////////////

INLINE bool operator>( const gsl::complex& left, const gsl::complex& right )
{
	return left.abs() > right.abs();
}

////////////////////////////////////////////////////////////

INLINE bool operator>=( const gsl::complex& left, const gsl::complex& right )
{
	return left.abs() >= right.abs();
}

////////////////////////////////////////////////////////////

INLINE gsl::complex operator+( const gsl::complex& left, const gsl::complex& right )
{	return gsl_complex_add( left.const_ref(), right.const_ref() );	}

////////////////////////////////////////////////////////////

INLINE gsl::complex operator+( real left, const gsl::complex& right )
{	return gsl_complex_add_real( right.const_ref(), left );			}

////////////////////////////////////////////////////////////

INLINE gsl::complex operator+( const gsl::complex& left, real right )
{	return gsl_complex_add_real( left.const_ref(), right );			}

////////////////////////////////////////////////////////////

INLINE gsl::complex operator-( const gsl::complex& left, const gsl::complex& right )
{	return gsl_complex_sub( left.const_ref(), right.const_ref() );	}

////////////////////////////////////////////////////////////

INLINE gsl::complex operator-( real left, const gsl::complex& right )
{	return gsl_complex_negative( gsl_complex_sub_real( right.const_ref(), left ) );	}

////////////////////////////////////////////////////////////

INLINE gsl::complex operator-( const gsl::complex& left, real right )
{	return gsl_complex_sub_real( left.const_ref(), right );	}

////////////////////////////////////////////////////////////

INLINE gsl::complex operator*( const gsl::complex& left, const gsl::complex& right )
{	return gsl_complex_mul( left.const_ref(), right.const_ref() );	}

////////////////////////////////////////////////////////////

INLINE gsl::complex operator*( real left, const gsl::complex& right )
{	return gsl_complex_mul_real( right.const_ref(), left );	}

////////////////////////////////////////////////////////////

INLINE gsl::complex operator*( const gsl::complex& left, real right )
{	return gsl_complex_mul_real( left.const_ref(), right );			}

////////////////////////////////////////////////////////////

INLINE gsl::complex operator/( const gsl::complex& left, const gsl::complex& right )
{	return gsl_complex_div( left.const_ref(), right.const_ref() );	}

////////////////////////////////////////////////////////////

INLINE gsl::complex operator/( real left, const gsl::complex& right )
{	return gsl_complex_inverse( gsl_complex_div_real( right.const_ref(), left ) );	}

////////////////////////////////////////////////////////////

INLINE gsl::complex operator/( const gsl::complex& left, real right )
{	return gsl_complex_div_real( left.const_ref(), right );			}

////////////////////////////////////////////////////////////
/// Elementary functions
////////////////////////////////////////////////////////////

/// Get the square-root of a complex number, the branch cut is the negative real axis,
/// the result always lies in the right half of the complex plane
INLINE gsl::complex sqrt( const gsl::complex& z )
{	return gsl_complex_sqrt( z.const_ref() );	}

/// Get the complex sqare-root of a real number, x may be negative
INLINE gsl::complex sqrt( real x )
{	return gsl_complex_sqrt_real( x );	}

/// Get z^a, where both z & a cam be complex.  Computed as exp(log(z)*a)
INLINE gsl::complex pow( const gsl::complex& z, const gsl::complex& a )
{	return gsl_complex_pow( z.const_ref(), a.const_ref() );		}

/// Get z^a, where z is complex and a is real
INLINE gsl::complex pow(const gsl::complex& z, real a )
{	return gsl_complex_pow_real( z.const_ref(), a );	}

/// Get the complex exponential of the complex number z
INLINE gsl::complex exp( const gsl::complex& z )
{	return gsl_complex_exp( z.const_ref() );		}

/// Get the complex natural logarithm of the complex number, z
INLINE gsl::complex log( const gsl::complex& z)
{	return gsl_complex_log( z.const_ref() );		}

/// Wrapper for log( const gsl::complex& )
INLINE gsl::complex ln( const gsl::complex& z)
{	return gsl_complex_log( z.const_ref() );		}

/// Get the complex log_10 of a complex number, z
INLINE gsl::complex log10( const gsl::complex& z )
{	return gsl_complex_log10( z.const_ref() );		}

/// Get the complex base-b logarithm of the complex number z
/// Computed as log(z)/log(b)
INLINE gsl::complex log_b( const gsl::complex& z, const gsl::complex& b )
{	return gsl_complex_log_b( z.const_ref(), b.const_ref() );		}

////////////////////////////////////////////////////////////
/// Trigonometric functions
////////////////////////////////////////////////////////////

/// Return the complex sine of the complex number z.
INLINE gsl::complex sin( const gsl::complex& z )
{	return gsl_complex_sin( z.const_ref() );	}

/// Return the complex cosine of the complex number z.
INLINE gsl::complex cos( const gsl::complex& z )
{	return gsl_complex_cos( z.const_ref() );	}

/// Return the complex tangent of the complex number z.
INLINE gsl::complex tan( const gsl::complex& z )
{	return gsl_complex_tan( z.const_ref() );	}

/// Return the complex secant of the complex number z.
INLINE gsl::complex sec( const gsl::complex& z )
{	return gsl_complex_sec( z.const_ref() );	}

/// Return the complex cosecant of the complex number z.
INLINE gsl::complex csc( const gsl::complex& z )
{	return gsl_complex_csc( z.const_ref() );	}

/// Return the complex cotangent of the complex number z.
INLINE gsl::complex cot( const gsl::complex& z )
{	return gsl_complex_cot( z.const_ref() );	}

////////////////////////////////////////////////////////////
/// Inverse Trigonometric functions
////////////////////////////////////////////////////////////

/// Returns the complex arc-sine of the complex number, z. The branch-cuts are on the
/// real axis, less than -1 and greater than 1.
INLINE gsl::complex asin( const gsl::complex& z )
{	return gsl_complex_arcsin( z.const_ref() );		}

/// Returns the complex arc-sine of the real number, x. For -1 <= x <= 1, returns a zero
/// imaginary component and a real component in the range [-pi/2, pi/2]. For x > 1,
/// asin(x) = pi/2 - iy, y is a positive, real number. For x < -1, asin(x) = -pi/2 + iy.
INLINE gsl::complex asin( real x )
{	return gsl_complex_arcsin_real( x );		}

/// Returns the complex arc-cosine of the complex number, z. The branch-cuts are on the
/// real axis, less than -1 and greater than 1.
INLINE gsl::complex acos( const gsl::complex& z )
{	return gsl_complex_arccos( z.const_ref() );		}

/// Returns the complex arc-cosine of the real number, x. For -1 <= x <= 1, returns a zero
/// imaginary component and a real component in the range [0, pi]. For x < -1,
/// acos(x) = pi - iy, y is a positive, real number. For x > 1, acos(x) = iy.
INLINE gsl::complex acos( real x )
{	return gsl_complex_arccos_real( x );		}

/// Returns the complex arc-tangent of the complex number z. Branch cuts are on the
/// imaginary axis, below -i and above i.
INLINE gsl::complex atan( const gsl::complex& z )
{	return gsl_complex_arctan( z.const_ref() );	}

/// Returns the complex arc-secant of the complex number z.
INLINE gsl::complex asec( const gsl::complex& z )
{	return gsl_complex_arcsec( z.const_ref() );	}

/// Return the complex arc-secant of the real number x
INLINE gsl::complex asec( real x )
{	return gsl_complex_arcsec_real( x );	}	

/// Returns the complex arc-cosecant of the complex number z.
INLINE gsl::complex acsc( const gsl::complex& z )
{	return gsl_complex_arccsc( z.const_ref() );	}

/// Return the complex src-cosecant of the real number x
INLINE gsl::complex acsc( real x )
{	return gsl_complex_arccsc_real( x );	}	

/// Returns the complex arc-cotangent of the complex number z.
INLINE gsl::complex acot( const gsl::complex& z )
{	return gsl_complex_arccot( z.const_ref() );	}

////////////////////////////////////////////////////////////
/// Hyperbolic functions
////////////////////////////////////////////////////////////

/// Returns the complex hyperbolic sine of the complex number z
INLINE gsl::complex sinh( const gsl::complex& z )
{	return gsl_complex_sinh( z.const_ref() );	}

/// Returns the complex hyperbolic cosine of the complex number z
INLINE gsl::complex cosh( const gsl::complex& z )
{	return gsl_complex_cosh( z.const_ref() );	}

/// Returns the complex hyperbolic tangent of the complex number z
INLINE gsl::complex tanh( const gsl::complex& z )
{	return gsl_complex_tanh( z.const_ref() );	}

/// Returns the complex hyperbolic secant of the complex number z
INLINE gsl::complex sech( const gsl::complex& z )
{	return gsl_complex_sech( z.const_ref() );	}

/// Returns the complex hyperbolic co-secant of the complex number z
INLINE gsl::complex csch( const gsl::complex& z )
{	return gsl_complex_csch( z.const_ref() );	}

/// Returns the complex hyperbolic co-tangent of the complex number z
INLINE gsl::complex coth( const gsl::complex& z )
{	return gsl_complex_coth( z.const_ref() );	}

////////////////////////////////////////////////////////////
/// Inverse hyperbolic functions
////////////////////////////////////////////////////////////

/// Returns the complex hyperbolic arc-sine of the complex number, z.
/// The branch-cuts are on the imaginary axis, less than -i and greater than i.
INLINE gsl::complex asinh( const gsl::complex& z )
{	return gsl_complex_arcsinh( z.const_ref() );		}

/// Returns the complex hyperbolic arc-cosine of the complex number, z.
/// The branch-cuts are on theh real axis, less than 1. Note that in this case,
/// we use the negative square-root formula in 4.6.21 of Abramowitz & Stegun, giving
/// acosh(z) = log(z - sqrt(z^2 - 1))
INLINE gsl::complex acosh( const gsl::complex& z )
{	return gsl_complex_arccosh( z.const_ref() );		}

/// Returns the complex hyperbolic arc-cosine of the real number, x.
INLINE gsl::complex acosh( real x )
{	return gsl_complex_arccosh_real( x );		}

/// Returns the complex hyperbolic arc-tangent of the complex number z.
/// Branch cuts are on the real axis, less than -1 and greater than 1
INLINE gsl::complex atanh( const gsl::complex& z )
{	return gsl_complex_arctanh( z.const_ref() );	}

/// Returns the complex hyperbolic arc-tangent of the real number x
INLINE gsl::complex atanh( real x )
{	return gsl_complex_arctanh_real( x );	}	

/// Returns the complex hyperbolic arc-secant of the complex number z.
INLINE gsl::complex asech( const gsl::complex& z )
{	return gsl_complex_arcsech( z.const_ref() );	}

/// Returns the complex hyperbolic arc-cosecant of the complex number z.
INLINE gsl::complex acsch( const gsl::complex& z )
{	return gsl_complex_arccsch( z.const_ref() );	}

/// Returns the complex hyperbolic arc-cotangent of the complex number z.
INLINE gsl::complex acoth( const gsl::complex& z )
{	return gsl_complex_arccoth( z.const_ref() );	}

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////

std::ostream &operator<<(std::ostream &os, const gsl::complex& z);

////////////////////////////////////////////////////////////
