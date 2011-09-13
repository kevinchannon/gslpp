#pragma once

#include <cstddef>
#include <algorithm>

#include "../Common/number.h"
#include "../Common/macros.h"
#include "../Vector/vector.h"
#include "../Permutation/permutation.h"

#include <gsl/gsl_sort.h>
#include <gsl/gsl_sort_vector.h>
#include <gsl/gsl_permutation.h>

BEGIN_GSL_NAMESPACE

template< typename T >	class vector;
class permutation;

template< typename T >
void sort( gsl::vector< T >& v )
{   std::sort( v.begin(), v.end()); }

template< typename T >
void sort( gsl::permutation& p, const gsl::vector< T >& v)
{   gsl_sort_vector_index (p.ptr(), v.as_gsl_vector() );  }
	
template< typename T >
void sortSmallest( real *dest, size_t numberOfElements, const gsl::vector< T >& src);
template< typename T >
void sortSmallest( gsl::permutation& p, size_t numberOfElements, const gsl::vector< T >& src);
template< typename T >
void sortLargest( real *dest, size_t numberOfElements, const gsl::vector< T >& src);
template< typename T >
void sortLargest( gsl::permutation& p, size_t numberOfElements, const gsl::vector< real >& src);

void sort( real *data, size_t length, size_t stride = 1 );
void sort( size_t *permutation, const real *data, size_t length, size_t stride = 1 );
void sortSmallest(real *dest, size_t destLength, const real *src, size_t srcLength, size_t stride = 1 );
void sortSmallest(size_t *permutation, size_t numberOfElements, const real *src, size_t srcLength, size_t stride = 1 );
void sortLargest(real *dest, size_t destLength, const real *src, size_t srcLength, size_t stride = 1 );
void sortLargest(size_t *permutation, size_t numberOfElements, const real *src, size_t srcLength, size_t stride = 1 );

END_GSL_NAMESPACE
