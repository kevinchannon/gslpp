#include "sort.h"

#include <algorithm>

#include "../Vector/vector.h"
#include "../Permutation/permutation.h"

#include <gsl/gsl_sort.h>
#include <gsl/gsl_sort_vector.h>
#include <gsl/gsl_permutation.h>

BEGIN_GSL_NAMESPACE

template< typename T >
void sortSmallest(real *dest, size_t numberOfElements, const gsl::vector< T >& src)
{   gsl_sort_vector_smallest( dest, numberOfElements, src.as_gsl_vector() );    }

template< typename T >
void sortSmallest( gsl::permutation& p, size_t numberOfElements, const gsl::vector< T >& src)
{   gsl_sort_vector_smallest_index( p.begin(), numberOfElements, src.as_gsl_vector() );   }

template< typename T >
void sortLargest(real *dest, size_t numberOfElements, const gsl::vector< T >& src)
{   gsl_sort_vector_largest( dest, numberOfElements, src.as_gsl_vector() ); }
template< typename T >    void sortLargest( gsl::permutation& p, size_t numberOfElements, const gsl::vector< T >& src)
{   gsl_sort_vector_largest_index( p.begin(), numberOfElements, src.as_gsl_vector() );    }

void sort( real *data, size_t length, size_t stride )
{   gsl_sort(data, stride, length); }

void sort( size_t *permutation, const real *data, size_t length, size_t stride )
{   gsl_sort_index(permutation, data, stride, length);  }

void sortSmallest(real *dest, size_t destLength, const real *src, size_t srcLength, size_t stride  )
{   gsl_sort_smallest(dest, destLength, src, srcLength, stride );    }

void sortSmallest(size_t *permutation, size_t numberOfElements, const real *src, size_t srcLength, size_t stride )
{   gsl_sort_smallest_index( permutation, numberOfElements, src, srcLength, stride );   }

void sortLargest(real *dest, size_t destLength, const real *src, size_t srcLength, size_t stride )
{   gsl_sort_largest(dest, destLength, src, srcLength, stride ); }

void sortLargest(size_t *permutation, size_t numberOfElements, const real *src, size_t srcLength, size_t stride )
{   gsl_sort_largest_index( permutation, numberOfElements, src, srcLength, stride );    }

END_GSL_NAMESPACE
