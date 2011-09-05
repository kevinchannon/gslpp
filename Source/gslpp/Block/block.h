#pragma once

#include "../Common/macros.h"
#include "../Common/number.h"

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

template< typename T = real >
class block{
public:
	typedef T*				iterator;
    typedef const iterator	const_iterator;
    typedef T&				reference;
    typedef const reference	const_reference;
    typedef T*				pointer;
    typedef const pointer	const_pointer;
    typedef T				value_type;
    typedef size_t			size_type;
    typedef ptrdiff_t		difference_type;
	
	block() : M_pStart(0), M_pFinish(0){}
	block( size_type N ) : M_pStart( new T[ N ] )
		{	M_pFinish = M_pStart + N;	}
	~block()
		{	if ( has_value() )	delete[] M_pStart;	}
	
	__INLINE bool is_null() const
		{		return M_pStart == NULL;	}
	__INLINE bool has_value() const
		{	return ! is_null();			}
	
	__INLINE size_type size() const
		{	return static_cast< size_type >(M_pFinish - M_pStart);	}
	__INLINE const_iterator cbegin() const
		{	return M_pStart;	}
	__INLINE iterator begin()
		{	return M_pStart;	}
	__INLINE const_iterator cend() const
		{	return M_pFinish;	}
	__INLINE iterator end()
		{	return M_pFinish;	}
	__INLINE bool empty() const
		{	return M_pStart == M_pFinish;	}
	
	__INLINE reference operator[]( size_type i )
		{	return M_pStart[ i ];	}
	__INLINE const_reference operator[]( size_type i ) const
		{	return M_pStart[ i ];	}
	
private:
	T* M_pStart;
	T* M_pFinish;
};

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////