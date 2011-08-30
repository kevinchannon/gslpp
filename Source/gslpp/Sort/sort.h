#pragma once

#include <cstddef>

#include "../Common/number.h"
#include "../Common/macros.h"

BEGIN_GSL_NAMESPACE

class realVector;
class permutation;

void sort( gsl::realVector& v );
void sort( gsl::permutation& p, const gsl::realVector& v );
void sortSmallest( real *dest, size_t numberOfElements, const gsl::realVector& src);
void sortSmallest( gsl::permutation& p, size_t numberOfElements, const gsl::realVector& src);
void sortLargest( real *dest, size_t numberOfElements, const gsl::realVector& src);
void sortLargest( gsl::permutation& p, size_t numberOfElements, const gsl::realVector& src);

void sort( real *data, size_t length, size_t stride = 1 );
void sort( size_t *permutation, const real *data, size_t length, size_t stride = 1 );
void sortSmallest(real *dest, size_t destLength, const real *src, size_t srcLength, size_t stride = 1 );
void sortSmallest(size_t *permutation, size_t numberOfElements, const real *src, size_t srcLength, size_t stride = 1 );
void sortLargest(real *dest, size_t destLength, const real *src, size_t srcLength, size_t stride = 1 );
void sortLargest(size_t *permutation, size_t numberOfElements, const real *src, size_t srcLength, size_t stride = 1 );

END_GSL_NAMESPACE
