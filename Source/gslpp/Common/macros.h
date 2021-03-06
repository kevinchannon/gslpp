#pragma once

#ifdef GSLPP_INLINE
#define INLINE inline
#else
#define INLINE
#endif 

#define BEGIN_GSL_NAMESPACE namespace gsl{
#define END_GSL_NAMESPACE }

#define BEGIN_BLAS_NAMESPACE namespace blas{
#define END_BLAS_NAMESPACE }

#define BEGIN_FFT_NAMESPACE namespace fft{
#define END_FFT_NAMESPACE }

#define continue_if( condition ) if ( (condition) ) continue
#define break_if( condition ) if ( (condition) ) break