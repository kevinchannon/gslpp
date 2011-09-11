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
    INLINE T* ptr(){                    return M_pGSLData;  }

    /// Get a const pointer to the underlying GSL struct
    ///
    /// Will not throw, can return NULL
    INLINE const T* const_ptr() const{  return M_pGSLData;  }

    /// Check if it's OK to try and manipulate the object
    ///
    /// Will not throw
    INLINE bool hasValue() const{       return M_pGSLData != 0;  }

    /// Check if it's not OK to try and manipulate the object
    ///
    /// Will not throw
    INLINE bool isNull() const{         return M_pGSLData == 0; }

protected:

    gsl_base_ptr() : M_pGSLData( NULL ){}
    gsl_base_ptr( T* original ) : M_pGSLData( original ){}
    ~gsl_base_ptr(){}

    /// Set the value of the underlying GSL struct
    ///
    /// Will not throw
    INLINE void set_ptr( T* p ){        M_pGSLData = p;     }
	
	/// Exchange the underlying GSL struct with another of the same kind
	///
	/// will not throw
	INLINE void swap_ptr( T*& p){	std::swap( M_pGSLData, p );	}

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
	INLINE T& ref(){	return M_GSLData;	}
	
	/// Get a const reference to the underlying object
	///
	/// Will not throw, will no return NULL
	INLINE const T& const_ref() const {	return M_GSLData;	}
	
	/// Get a pointer to the underlying object
	///
	/// Will not throw, will not return NULL
	INLINE T* ptr(){	return const_cast< T* >( const_ptr() );	}
	
	/// Get a const pointer to the underlying object
	///
	/// Will not throw, will not return NULL
	INLINE const T* const_ptr() const {	return &M_GSLData;	}
	
protected:
	T M_GSLData;
};

////////////////////////////////////////////////////////////

template< typename T >
class from_STL_container{
public:
	typedef typename T::iterator 		iterator;
	typedef typename T::const_iterator	const_iterator;
	typedef typename T::reference		reference;
    typedef typename T::const_reference	const_reference;
    typedef typename T::pointer			pointer;
    typedef typename T::const_pointer	const_pointer;
    typedef typename T::value_type		value_type;
    typedef typename T::size_type		size_type;
    typedef typename T::difference_type	difference_type;
	
	INLINE iterator begin(){				return M_STLData.begin();	}
	INLINE const_iterator cbegin() const{	return M_STLData.cbegin();	}
	INLINE iterator end(){				return M_STLData.end();		}
	INLINE const_iterator cend() const{	return M_STLData.cend();	}
	
	INLINE size_type size() const{		return M_STLData.size();	}
	INLINE bool empty() const{			return M_STLData.empty();	}
	INLINE size_type max_size() const{	return M_STLData.max_size();}
	
	INLINE iterator insert ( iterator position, const value_type& x )
		{	return M_STLData.insert(position, x);	}
		
    INLINE void insert ( iterator position, size_type n, const value_type& x )
		{	return M_STLData.insert( position, n, x );	}
		
	template <class InputIterator>
    INLINE void insert ( iterator position, InputIterator first, InputIterator last )
		{	return M_STLData.insert( position, first, last );	}
	
	INLINE iterator erase ( iterator position ){	return M_STLData.erase( position );	}
	INLINE iterator erase ( iterator first, iterator last ){	return M_STLData.erase(first, last);	}
	
	INLINE void swap( T& other){	M_STLData.swap( other );	}
	INLINE void clear(){			M_STLData.clear();			}
	
protected:
	~from_STL_container(){}
	T M_STLData;
};

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////
