#include "permute.h"
#include "../Common/exceptions.h"

BEGIN_GSL_NAMESPACE

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
}

END_GSL_NAMESPACE


