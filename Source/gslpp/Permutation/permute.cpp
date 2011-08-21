#include "permute.h"
#include "../Common/exceptions.h"

namespace gsl{
    namespace permute{

        void array( const size_t *p, real *data, size_t n, size_t stride ) throw ( null_pointer_dereference )
        {
            if ( p == NULL || data == NULL )
                throw null_pointer_dereference();

            gsl_permute( p, data, stride, n );
        }

        void arrayInverse( const size_t *p, real *data, size_t n, size_t stride ) throw ( null_pointer_dereference )
        {
            if ( p == NULL || data == NULL )
                throw null_pointer_dereference();

            gsl_permute_inverse( p, data, stride, n );
        }

        void vector( const permutation& p, gsl::realVector& v )
        throw (gsl::size_mismatch, gsl::permutation_uninitialised, gsl::vector_uninitialised )
        {
            if ( p.size() != v.size() )
                throw gsl::size_mismatch();

            if ( p.isNull() )
                throw gsl::permutation_uninitialised();

            if ( v.isNull() )
                throw gsl::vector_uninitialised();

            gsl_permute( p.const_ptr()->data, v.ptr()->data, v.stride(), v.size() );
        }

        void vectorInverse( const permutation& p, gsl::realVector& v )
        throw (gsl::size_mismatch, gsl::permutation_uninitialised, gsl::vector_uninitialised )
        {
            if ( p.size() != v.size() )
                throw gsl::size_mismatch();

            if ( p.isNull() )
                throw gsl::permutation_uninitialised();

            if ( v.isNull() )
                throw gsl::vector_uninitialised();

            gsl_permute_inverse( p.const_ptr()->data, v.ptr()->data, v.stride(), v.size() );
        }
    }
}

const gsl::realVector operator*( const gsl::permutation& p, const gsl::realVector& v)
throw (gsl::size_mismatch, gsl::permutation_uninitialised, gsl::vector_uninitialised )
{
    if ( p.size() != v.size() )
        throw gsl::size_mismatch();

    if ( p.isNull() )
        throw gsl::permutation_uninitialised();

    if ( v.isNull() )
        throw gsl::vector_uninitialised();

    gsl::realVector out( v );
    gsl_permute( p.const_ptr()->data, out.ptr()->data, out.stride(), out.size() );

    return out;
}
