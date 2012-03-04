#pragma once

#include "../Common/macros.h"

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

	/// Make sure a number is greater than 0
    INLINE size_t atLeastOne( int n ){  return n > 0 ? n : 1;   }
	
	/// Check if a number is a power of two
	INLINE bool isPowerOfTwo( unsigned n )	{	return ( n ) && ! ( n & ( n - 1 ) );	}
	INLINE bool isPowerOfTwo( int n )		{	return ( n ) && ! ( n & ( n - 1 ) );	}

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////
