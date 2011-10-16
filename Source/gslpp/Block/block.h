#pragma once

#include <complex>
#include <stdexcept>

#include "../Common/macros.h"
#include "../Common/number.h"

#include <gsl/gsl_block.h>

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

class block_size_mismatch : public std::runtime_error
{
    public:
    block_size_mismatch() : std::runtime_error("block sizes are unequal"){}
};

////////////////////////////////////////////////////////////

/// Main gsl_block type template
template< typename T >
struct gsl_block_type {};

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

template< typename T >
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
//    typedef ptrdiff_t		difference_type;
	
	typedef typename gsl_block_type< T >::type gsl_block_t;
	
	block() : M_pStart(0), M_pFinish(0){}
	block( size_type N ) : M_pStart( new T[ N ] ) {	M_pFinish = M_pStart + N;	}
	block( size_type N, value_type x ) : M_pStart( new T[ N ] )
	{
		M_pFinish = M_pStart + N;
		std::fill( this->begin(), this->end(), x );
	}
	block( const gsl_block_t* b )
	{
		if ( b != NULL ){
			M_pStart = new T[b->size];
			M_pFinish = M_pStart + b->size;
			std::copy( b->data, b->data + b->size, this->begin() );
		}
	}
	block( const gsl::block< T >& original )
	{
		size_type N = original.size();
		if ( N > 0 )
		{
			M_pStart = new T[ N ];
			M_pFinish = M_pStart + N;
			std::copy( original.cbegin(), original.cend(), this->begin() );
		}
	}
	~block()
		{	if ( has_value() )	delete[] M_pStart;	}
		
	INLINE void swap( gsl::block< T >& other )
	{
		std::swap( M_pStart, other.M_pStart );
		std::swap( M_pFinish, other.M_pFinish );
	}
	
	gsl::block< T > operator=( const gsl::block< T >& right )
	{
		gsl::block< T > temp( right );
		this->swap(temp);
		return *this;
	}
	
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
	INLINE const_iterator begin() const
		{	return M_pStart;	}
	INLINE const_iterator cend() const
		{	return M_pFinish;	}
	INLINE iterator end()
		{	return M_pFinish;	}
	INLINE const_iterator end() const
		{	return M_pFinish;	}
	INLINE bool empty() const
		{	return M_pStart == M_pFinish;	}
	
	INLINE reference operator[]( size_type i )
		{	return M_pStart[ i ];	}
	INLINE const_reference operator[]( size_type i ) const
		{	return M_pStart[ i ];	}
		
	gsl_block_t* as_gsl_block()
	{
		gsl_block_t* b = new gsl_block_t;
		b->data = M_pStart;
		b->size = this->size();
		return b;
	}
	
	const gsl_block_t* as_gsl_block() const
	{
		gsl_block_t* b = new gsl_block_t;
		b->data = M_pStart;
		b->size = this->size();
		return b;
	}
	
	gsl_block_t* to_gsl_block() throw ( std::bad_alloc )
	{
		gsl_block_t* b = gsl_block_type< T >::alloc( this->size() );
		if ( b == NULL )
			throw std::bad_alloc();
			
		std::copy( this->cbegin(), this->cend(), b->data );
		return b;
	}
	
	const gsl_block_t* to_gsl_block() const throw ( std::bad_alloc )
	{
		gsl_block_t* b = gsl_block_type< T >::alloc( this->size() );
		if ( b == NULL )
			throw std::bad_alloc();
			
		std::copy( this->cbegin(), this->cend(), b->data );
		return b;
	}
	
private:
	T* M_pStart;
	T* M_pFinish;
};

////////////////////////////////////////////////////////////

template< typename T >
struct gsl_block_type< std::complex< T > >
{
	typedef gsl_block_complex type;
	INLINE static type* alloc( size_t n ){	return gsl_block_complex_alloc(n);	}
};

////////////////////////////////////////////////////////////

/* The complex block type has not been tested properly, and it definitely has some bugs and a lot of
 * quirks in the API */

template< typename T >
class block< std::complex< T > >{
public:
	typedef T*	iterator;
    typedef const iterator		const_iterator;
    typedef T&	reference;
    typedef const reference		const_reference;
    typedef T*	pointer;
    typedef const pointer		const_pointer;
    typedef std::complex< T >	value_type;
    typedef size_t				size_type;
//    typedef ptrdiff_t			difference_type;
	
	typedef typename gsl::gsl_block_type< std::complex< T > >::type gsl_cplx_block_t;
	
	block() : M_pStart(0), M_pFinish(0){}
	block( size_type N ) : M_pStart( new T[ 2*N ] ) {	M_pFinish = M_pStart + 2 * N;	}
	block( size_type N, std::complex< T > x ) : M_pStart( new T[ 2 * N ] )
	{
		M_pFinish = M_pStart + 2 * N;
		for ( size_type i = 0; i < N; ++i ){
			M_pStart[i] = x.real();
			M_pStart[ i + 1] = x.imag();
		}
	}
	block( size_type N, const T& x, const T& y ) : M_pStart( new T[ 2 * N ] )
	{
		M_pFinish = M_pStart + 2 * N;
		for ( size_type i = 0; i < N; ++i ){
			M_pStart[i] = x;
			M_pStart[ i + 1] = y;
		}
	}
	block( const gsl_cplx_block_t* b )
	{
		if ( b != NULL ){
			M_pStart = new T[b->size];
			M_pFinish = M_pStart + b->size;
			std::copy( b->data, b->data + b->size, this->begin() );
		}
	}
	block( const gsl::block< std::complex< T > >& original )
	{
		size_type N = 2 * original.size();
		if ( N > 0 )
		{
			M_pStart = new T[ N ];
			M_pFinish = M_pStart + N;
			std::copy( original.M_pStart, original.M_pFinish, this->M_pStart );
		}
	}
	block( const gsl::block< T >& realBlock, const gsl::block< T >& imagBlock )
	{
		if ( realBlock.size() != imagBlock.size() )
			throw block_size_mismatch();
			
		size_type N = 2 * realBlock.size();
		if ( N > 0 )
		{
			M_pStart = new T[ 2 * N ];
			M_pFinish = M_pStart + 2 * N;
			for ( size_type i = 0; i < N; ++i ){
				M_pStart[ i ]     = realBlock[i];
				M_pStart[ i + 1 ] = imagBlock[i];
			}
		}
		else
		{
			M_pStart = 0;
			M_pFinish = 0;
		}
	}
	~block()
		{	if ( ! this->empty() )	delete[] M_pStart;	}
		
	INLINE void swap( gsl::block< T >& other )
	{
		std::swap( M_pStart, other.M_pStart );
		std::swap( M_pFinish, other.M_pFinish );
	}
	
	gsl::block< std::complex< T > > operator=( const gsl::block< std::complex< T > >& right )
	{
		gsl::block< std::complex< T > > temp( right );
		this->swap(temp);
		return *this;
	}
	
	INLINE bool is_null() const
		{		return M_pStart == NULL;	}
	INLINE bool has_value() const
		{	return ! is_null();			}
	
	INLINE size_type size() const
		{	return static_cast< size_type >(M_pFinish - M_pStart) / 2;	}
	INLINE const_iterator cbegin() const
		{	return M_pStart;	}
	INLINE iterator begin()
		{	return M_pStart;	}
	INLINE const_iterator begin() const
		{	return M_pStart;	}
	INLINE const_iterator cend() const
		{	return M_pFinish;	}
	INLINE iterator end()
		{	return M_pFinish;	}
	INLINE const_iterator end() const
		{	return M_pFinish;	}
	INLINE bool empty() const
		{	return M_pStart == M_pFinish;	}
	
	INLINE reference operator[]( size_type i )
		{	return M_pStart[ i ];	}
	INLINE value_type operator[]( size_type i ) const
		{	return value_type( M_pStart[ i ], M_pStart[i + 1] );	}
		
	gsl_cplx_block_t* as_gsl_block()
	{
		gsl_cplx_block_t* b = new gsl_cplx_block_t;
		b->data = M_pStart;
		b->size = this->size();
		return b;
	}
	
	const gsl_cplx_block_t* as_gsl_block() const
	{
		gsl_cplx_block_t* b = new gsl_cplx_block_t;
		b->data = M_pStart;
		b->size = this->size();
		return b;
	}
	
	gsl_cplx_block_t* to_gsl_block() throw ( std::bad_alloc )
	{
		gsl_cplx_block_t* b = gsl_block_type< std::complex< T > >::alloc( this->size() );
		if ( b == NULL )
			throw std::bad_alloc();
			
		std::copy( this->cbegin(), this->cend(), b->data );
		return b;
	}
	
	const gsl_cplx_block_t* to_gsl_block() const throw ( std::bad_alloc )
	{
		gsl_cplx_block_t* b = gsl_block_type< std::complex< T > >::alloc( this->size() );
		if ( b == NULL )
			throw std::bad_alloc();
			
		std::copy( this->cbegin(), this->cend(), b->data );
		return b;
	}
	
private:
	T* M_pStart;
	T* M_pFinish;
};

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////