#pragma once

#ifdef GSLPP_INLINE
#define __INLINE inline
#else
#define __INLINE
#endif 

#define BEGIN_GSL_NAMESPACE namespace gsl{
#define END_GSL_NAMESPACE }

#define BEGIN_BLAS_NAMESPACE namespace blas{
#define END_BLAS_NAMESPACE }