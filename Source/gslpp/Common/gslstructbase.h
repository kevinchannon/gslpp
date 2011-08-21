#pragma once

#include <cstddef>

namespace gsl{

template< typename T >
class gsl_base
{
public:

    /// Get a pointer to the underlying GSL struct
    ///
    /// Will not throw, can return NULL
    inline T* ptr(){                    return M_pGSLData;  }

    /// Get a const pointer to the underlying GSL struct
    ///
    /// Will not throw, can return NULL
    inline const T* const_ptr() const{  return M_pGSLData;  }

    /// Check if it's OK to try and manipulate the object
    ///
    /// Will not throw
    inline bool hasValue() const{       return M_pGSLData != 0;  }

    /// Check if it's not OK to try and manipulate the object
    ///
    /// Will not throw
    inline bool isNull() const{         return M_pGSLData == 0; }

protected:

    gsl_base() : M_pGSLData( NULL ){}
    gsl_base( T* original ) : M_pGSLData( original ){}
    ~gsl_base(){}

    /// Set the value of the underlying GSL struct
    ///
    /// Will not throw
    inline void set_ptr( T* p ){        M_pGSLData = p;     }
	
	/// Exchange the underlying GSL struct with another of the same kind
	///
	/// will not throw
	inline void swap_ptr( T*& p){	std::swap( M_pGSLData, p );	}

    T* M_pGSLData;

};

}
