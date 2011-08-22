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
};

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////
