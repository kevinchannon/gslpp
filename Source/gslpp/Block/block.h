#pragma once

#include "../Common/macros.h"
#include "../Common/number.h"

#include <gsl/gsl_block.h>

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

/// Main gsl_block type template
template< typename T >
struct gsl_block_type
{};

/// Template specialisations for actual gsl_block types
template<>
struct gsl_block_type< real >
{
	typedef gsl_block type;
	INLINE static type* alloc( size_t n ){	return gsl_block_alloc(n);	}
};

template<>
struct gsl_block_type< char >
{
	typedef gsl_block_char type;
	INLINE static type* alloc( size_t n ){	return gsl_block_char_alloc(n);	}
};

template<>
struct gsl_block_type< float >
{
	typedef gsl_block_float type;
	INLINE static type* alloc( size_t n ){	return gsl_block_float_alloc(n);	}
};

template<>
struct gsl_block_type< int >
{
	typedef gsl_block_int type;
	INLINE static type* alloc( size_t n ){	return gsl_block_int_alloc(n);	}
};

template<>
struct gsl_block_type< long >
{
	typedef gsl_block_long type;
	INLINE static type* alloc( size_t n ){	return gsl_block_long_alloc(n);	}
};

template<>
struct gsl_block_type< long double >
{
	typedef gsl_block_long_double type;
	INLINE static type* alloc( size_t n ){	return gsl_block_long_double_alloc(n);	}
};

template<>
struct gsl_block_type< short >
{
	typedef gsl_block_short type;
	INLINE static type* alloc( size_t n ){	return gsl_block_short_alloc(n);	}
};

template<>
struct gsl_block_type< unsigned char >
{
	typedef gsl_block_uchar type;
	INLINE static type* alloc( size_t n ){	return gsl_block_uchar_alloc(n);	}
};

template<>
struct gsl_block_type< unsigned short >
{
	typedef gsl_block_ushort type;
	INLINE static type* alloc( size_t n ){	return gsl_block_ushort_alloc(n);	}
};

template<>
struct gsl_block_type< unsigned int >
{
	typedef gsl_block_uint type;
	INLINE static type* alloc( size_t n ){	return gsl_block_uint_alloc(n);	}
};

template<>
struct gsl_block_type< unsigned long >
{
	typedef gsl_block_ulong type;
	INLINE static type* alloc( size_t n ){	return gsl_block_ulong_alloc(n);	}
};

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
	
	INLINE bool is_null() const
		{		return M_pStart == NULL;	}
	INLINE bool has_value() const
		{	return ! is_null();			}
	
	INLINE size_type size() const
		{	return static_cast< size_type >(M_pFinish - M_pStart);	}
	INLINE const_iterator cbegin() const
		{	return M_pStart;	}
	INLINE iterator begin()
		{	return M_pStart;	}
	INLINE const_iterator cend() const
		{	return M_pFinish;	}
	INLINE iterator end()
		{	return M_pFinish;	}
	INLINE bool empty() const
		{	return M_pStart == M_pFinish;	}
	
	INLINE reference operator[]( size_type i )
		{	return M_pStart[ i ];	}
	INLINE const_reference operator[]( size_type i ) const
		{	return M_pStart[ i ];	}
	
private:
	T* M_pStart;
	T* M_pFinish;
};

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////