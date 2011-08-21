#pragma once

#include "../Common/number.h"
#include "../Common/exceptions.h"
#include "../Vector/vector.h"
#include "permutation.h"

#include <gsl/gsl_permute.h>

namespace gsl{

    namespace permute{

        void array( const size_t *p, real *data, size_t n, size_t stride = 1 ) throw ( null_pointer_dereference );
        void arrayInverse( const size_t *p, real *data, size_t n, size_t stride = 1 ) throw ( null_pointer_dereference );

        void vector( const permutation& p, gsl::realVector& v ) throw (gsl::size_mismatch, gsl::permutation_uninitialised, gsl::vector_uninitialised );
        void vectorInverse( const permutation& p, gsl::realVector& v ) throw (gsl::size_mismatch, gsl::permutation_uninitialised, gsl::vector_uninitialised );
    }
}

const gsl::realVector operator*( const gsl::permutation& p, const gsl::realVector& v)
throw (gsl::size_mismatch, gsl::permutation_uninitialised, gsl::vector_uninitialised );
