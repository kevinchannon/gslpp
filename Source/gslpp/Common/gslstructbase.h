#pragma once

#include "macros.h"

#include <cstddef>

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

template< typename T >
class gsl_base_ptr
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

    gsl_base_ptr() : M_pGSLData( NULL ){}
    gsl_base_ptr( T* original ) : M_pGSLData( original ){}
    ~gsl_base_ptr(){}

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

////////////////////////////////////////////////////////////

template< typename T >
class gsl_base
{
public:
	
	/// Get a reference to the underlying object
	///
	/// Will not throw, will no return NULL
	inline T& ref(){	return M_GSLData;	}
	
	/// Get a const reference to the underlying object
	///
	/// Will not throw, will no return NULL
	inline const T& const_ref() const {	return M_GSLData;	}
	
	/// Get a pointer to the underlying object
	///
	/// Will not throw, will not return NULL
	inline T* ptr(){	return const_cast< T* >( const_ptr() );	}
	
	/// Get a const pointer to the underlying object
	///
	/// Will not throw, will not return NULL
	inline const T* const_ptr() const {	return &M_GSLData;	}
	
protected:
	T M_GSLData;
};

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////
