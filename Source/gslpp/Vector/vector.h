#pragma once

#include <iostream>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>
#include <limits>
#include <numeric>

#include <gsl/gsl_vector.h>

#include "../Block/block.h"
#include "../Common/macros.h"
#include "../Common/gslstructbase.h"
#include "../Common/number.h"
#include "../Common/exceptions.h"

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

class vector_uninitialised : public std::runtime_error
{
    public:
    vector_uninitialised() : std::runtime_error("vector used before initialisation"){}
};

////////////////////////////////////////////////////////////

class vector_size_mismatch : public std::runtime_error
{
    public:
    vector_size_mismatch() : std::runtime_error("vector sizes are unequal"){}
};

////////////////////////////////////////////////////////////

/// Main gsl_vector type template
template< typename T >
struct gsl_vector_type
{};

/// Template specialisations for actual gsl_vector types
template<>
struct gsl_vector_type< real >
{
	typedef gsl_vector type;
	INLINE static type* alloc( size_t n ){	return gsl_vector_alloc(n);	}
};

template<>
struct gsl_vector_type< char >
{
	typedef gsl_vector_char type;
	INLINE static type* alloc( size_t n ){	return gsl_vector_char_alloc(n);	}
};

template<>
struct gsl_vector_type< float >
{
	typedef gsl_vector_float type;
	INLINE static type* alloc( size_t n ){	return gsl_vector_float_alloc(n);	}
};

template<>
struct gsl_vector_type< int >
{
	typedef gsl_vector_int type;
	INLINE static type* alloc( size_t n ){	return gsl_vector_int_alloc(n);	}
};

template<>
struct gsl_vector_type< long >
{
	typedef gsl_vector_long type;
	INLINE static type* alloc( size_t n ){	return gsl_vector_long_alloc(n);	}
};

template<>
struct gsl_vector_type< long double >
{
	typedef gsl_vector_long_double type;
	INLINE static type* alloc( size_t n ){	return gsl_vector_long_double_alloc(n);	}
};

template<>
struct gsl_vector_type< short >
{
	typedef gsl_vector_short type;
	INLINE static type* alloc( size_t n ){	return gsl_vector_short_alloc(n);	}
};

template<>
struct gsl_vector_type< unsigned char >
{
	typedef gsl_vector_uchar type;
	INLINE static type* alloc( size_t n ){	return gsl_vector_uchar_alloc(n);	}
};

template<>
struct gsl_vector_type< unsigned short >
{
	typedef gsl_vector_ushort type;
	INLINE static type* alloc( size_t n ){	return gsl_vector_ushort_alloc(n);	}
};

template<>
struct gsl_vector_type< unsigned int >
{
	typedef gsl_vector_uint type;
	INLINE static type* alloc( size_t n ){	return gsl_vector_uint_alloc(n);	}
};

template<>
struct gsl_vector_type< unsigned long >
{
	typedef gsl_vector_ulong type;
	INLINE static type* alloc( size_t n ){	return gsl_vector_ulong_alloc(n);	}
};

////////////////////////////////////////////////////////////

template< typename T >
class vector : public from_STL_container< std::vector< T > >
{
public:
	typedef typename gsl_vector_type< T >::type gsl_vec_t;
	typedef typename gsl_block_type< T >::type gsl_block_t;
	
	typedef typename from_STL_container< std::vector< T > >::iterator 			iterator;
	typedef typename from_STL_container< std::vector< T > >::const_iterator		const_iterator;
	typedef typename from_STL_container< std::vector< T > >::reference			reference;
    typedef typename from_STL_container< std::vector< T > >::const_reference	const_reference;
    typedef typename from_STL_container< std::vector< T > >::pointer			pointer;
    typedef typename from_STL_container< std::vector< T > >::const_pointer		const_pointer;
    typedef typename from_STL_container< std::vector< T > >::value_type			value_type;
    typedef typename from_STL_container< std::vector< T > >::size_type			size_type;
    typedef typename from_STL_container< std::vector< T > >::difference_type	difference_type;
	
	/// Default constructor
	vector() :	M_bIsColVector(true) {}
	
	/// Construct with a given length
    vector( size_type length, bool isColVector = true ) throw ( std::bad_alloc ) :	M_bIsColVector( isColVector )
	{
		this->M_STLData.resize( length );
	}
	
	/// Construct with a given length and fill with a given value
    vector( size_type length, T defaultElementValue, bool isColVector = true ) throw ( std::bad_alloc ) :
	M_bIsColVector( isColVector )
	{
		this->M_STLData.resize( length );
		std::fill( this->M_STLData.begin(), this->M_STLData.end(), defaultElementValue );
	}
	
	/// Construct from a C-style array with a given length
    vector( size_type length, T* array, bool isColVector = true  ) throw ( std::bad_alloc ) :
	M_bIsColVector( isColVector )
	{
		this->M_STLData.resize( length );
		std::copy( array, array + length, this->M_STLData.begin() );
	}
	
	/// Copy constructor
    vector( const gsl::vector< T >& original ) throw ( std::bad_alloc ) :
	M_bIsColVector( original.is_col_vector() )
	{
		this->M_STLData.resize( original.size() );
		std::copy( original.cbegin(), original.cend(), this->M_STLData.begin() );
	}
	
	/// Construct from a gsl_vector (or any of the gsl_vector_xxx family, e.g. gsl_vector_char )
    vector( gsl_vec_t* original, bool isColVector = true ) throw ( std::bad_alloc ) :
	M_bIsColVector( isColVector )
	{
		if ( original == NULL )
			throw gsl::vector_uninitialised();
			
		this->M_STLData.resize( original->size );
		std::copy( original->data, original->data + original->size, this->M_STLData.begin() );
	}
	
	/// Construct from an std::vector
    vector( const std::vector< T >& original, bool isColVector = true ) throw ( std::bad_alloc ) :
	M_bIsColVector( isColVector )
	{	this->M_STLData = original;	}
	
    ~vector(){}
	
	/// Check if the vector is a column vector
	INLINE bool  is_col_vector() const {	return   M_bIsColVector;	}
	
	/// Check if the vector is a row vector
	INLINE bool  is_row_vector() const {	return ! M_bIsColVector;	}
	
	/// Set the vector to column vector
	INLINE void set_col_vector(){	M_bIsColVector = true;	}
	
	/// Set the vector to row vector
	INLINE void set_row_vector(){	M_bIsColVector = false;	}
	
	/// Copy assignment operator
    INLINE gsl::vector< T >& operator=(const gsl::vector< T > &right)
	{
		this->M_STLData = right.M_STLData;
		this->M_bIsColVector = right.M_bIsColVector;
		return *this;
	}
	
	/// Value assignment operator
    INLINE gsl::vector< T >& operator=( const value_type x )
	{
		std::fill( this->M_STLData.begin(), this->M_STLData.end(), x );
		return *this;
	}
	
	/// std::vector assignment operator
	INLINE gsl::vector< T >& operator=( const std::vector< T >& right )
	{
		this->M_STLData = right;
		return *this;
	}
	
	/// Over-loaded unitary arithmetic operators
	gsl::vector< T >& operator+=(const gsl::vector< T >& right) throw ( vector_size_mismatch );
    gsl::vector< T >& operator+=( const value_type right);
    gsl::vector< T >& operator-=(const gsl::vector< T >& right) throw ( vector_size_mismatch );
    gsl::vector< T >& operator-=( const value_type right);
    gsl::vector< T >& operator*=(const gsl::vector< T >& right) throw ( vector_size_mismatch );
    gsl::vector< T >& operator*=( const value_type right);
    gsl::vector< T >& operator/=(const gsl::vector< T >& right) throw ( vector_size_mismatch );
    gsl::vector< T >& operator/=( const value_type right);

	/// Boolean equal
	INLINE bool operator==( const gsl::vector< T >& right )
	{	return this->M_STLData == right.M_STLData && this->M_bIsColVector == right.M_bIsColVector;	} 

	/// Boolean not equal
	INLINE bool operator!=( const gsl::vector< T >& right )
	{    return !( *this == right ); 	}
	
	/// GSL-style Functions
	
	/// Get the maximum value in the vector
    INLINE value_type max() const
	{	return *std::max_element( this->begin(), this->end() );	}
	
	/// Get the minimum value in the vector
    INLINE value_type min() const
	{	return *std::min_element( this->begin(), this->end() );	}
	
	/// Get both the min and max values in the vector
    INLINE std::pair< real, real > minmax() const
	{	return std::make_pair(this->min(), this->max() );	}
	
	/// Get the position of the maximum element
    INLINE size_type max_index() const
	{	return std::distance(this->begin(), std::max_element( this->begin(), this->end() ) );  }
	
	/// Get the position of the minimum element
    INLINE size_type min_index() const
	{	return std::distance(this->begin(), std::min_element( this->begin(), this->end() ) );  }
	
	/// Get the indices of the minimum and maximum elements
    INLINE std::pair< size_type, size_type > minmax_index() const
	{ 	return std::make_pair(this->min_index(), this->max_index() );  }
	
	/// Get a const iterator to the maximum element
	INLINE const_iterator max_element() const
	{	return std::max( this->begin(), this->end() );	}
	
	/// Get an iterator to the maximum element
	INLINE iterator max_element()
	{	return std::max( this->begin(), this->end() );	}
	
	/// Get a const iterator to the minimum element
	INLINE const_iterator min_element() const
	{	return std::min( this->begin(), this->end() );	}
	
	/// Get an iterator to the minimum element
	INLINE iterator min_element()
	{	return std::min( this->begin(), this->end() );	}
	
	/// Swap the two specified elements
	INLINE void swap_elements( size_type index1, size_type index2)
	{	std::swap( (*this)[index1], (*this)[index2] );	}
	
	/// Set all the values in the vector to zero
	INLINE void zero()
	{	std::fill( this->begin(), this->end(), static_cast< T >(0) );	}
	
    INLINE void basis(unsigned index)
	{
		this->zero();
		this->at( index ) = static_cast< T >(1);
	}
	
	/// STL-style functions
	
    /// Capacity
    INLINE void resize(const size_type length){	this->M_STLData.resize( length );	}
    INLINE void resize(const size_type length, const real value){	this->M_STLData.resize(length, value);	}
    INLINE size_type capacity() const{    return this->M_STLData.capacity();  }
    INLINE void reserve( size_type n ){		this->M_STLData.reserve(n);	}
	
    /// Element access
	
	/// Unchecked accessor
	INLINE reference operator[]( size_type i )
	{	return this->M_STLData[i];	}
	INLINE const_reference operator[]( size_type i ) const
	{	return this->M_STLData[i];	}
	
	/// Accessor with cyclic boundary condition
	/// behaviour is undefined if the vector has zero size
	/// Will throw if the vector has a size greater than the int max size
	INLINE reference operator()( int i )
	{
		if ( this->size() > static_cast< size_type >(std::numeric_limits< int >::max()) )
			throw std::out_of_range("Vector is too large for valid use of operator()");
			
		int N = static_cast< int >( this->size() );
		return this->M_STLData[ ((i % N) + N) % N ];
	}
	INLINE const_reference operator()( size_type i ) const
	{	
		if ( this->size() > static_cast< size_type >(std::numeric_limits< int >::max()) )
			throw std::out_of_range("Vector is too large for valid use of operator()");
			
		int N = static_cast< int >( this->size() );
		return this->M_STLData[ ((i % N) + N) % N ];
	}
	
	/// Safe accessor
	const_reference at( size_type i ) const
	{
		M_throw_if_out_of_range( i );
		return this->M_STLData[i];
	}
	reference at( size_type i )
	{
		M_throw_if_out_of_range( i );
		return this->M_STLData[i];
	}
	
	/// Iterators
    INLINE iterator begin(){  				return this->M_STLData.begin();		}
    INLINE iterator end(){ 					return this->M_STLData.end();		}
    INLINE iterator rbegin(){  				return this->M_STLData.rbegin();	}
    INLINE iterator rend(){ 					return this->M_STLData.rend();		}
    INLINE const_iterator begin() const {  	return this->M_STLData.begin();		}
    INLINE const_iterator end() const{ 		return this->M_STLData.end();		}
    INLINE const_iterator rbegin() const{  	return this->M_STLData.rbegin();	}
    INLINE const_iterator rend() const{ 		return this->M_STLData.rend();		}
    INLINE const_iterator cbegin() const {  	return this->M_STLData.begin();		}
    INLINE const_iterator cend() const {  	return this->M_STLData.end();		}
    INLINE const_iterator crbegin() const {	return this->M_STLData.rbegin();	}
    INLINE const_iterator crend() const {		return this->M_STLData.rend();  	}
	
    INLINE reference front(){					return this->M_STLData.front();	}
    INLINE reference back(){					return this->M_STLData.back();	}
    INLINE const_reference front() const {	return this->M_STLData.front();	}
    INLINE const_reference back() const {		return this->M_STLData.back();	}

    /// Modifiers
    INLINE void assign( size_type n, const_reference value ){	this->M_STLData.assign(n, value);	}
    void assign( const_iterator start, const_iterator finish ){	this->M_STLData.assign(start, finish);	}
	
	/// Swap this vector with another
	INLINE void swap( gsl::vector< T >& other )
	{
		std::swap( this->M_STLData, other.M_STLData );
		std::swap( this->M_bIsColVector, other.M_bIsColVector);
	}
	
    INLINE void clear(){	this->M_STLData.clear();	}
    INLINE void push_back( value_type value ){	this->M_STLData.push_back( value );	}
    INLINE value_type pop_back()
	{
		value_type out = this->back();
		this->M_STLData.pop_back();
		return out;
	}
    INLINE void erase( iterator pos){	this->M_STLData.erase( pos );	}
    INLINE void erase( size_type pos){	this->M_STLData.erase( this->begin() + pos );	}
    INLINE iterator insert( iterator pos, value_type x ){	return this->M_STLData.insert(pos,x);	}
    INLINE void insert ( iterator pos, size_type n, value_type x ){	return this->M_STLData.insert(pos,n,x);	}
    INLINE void insert ( iterator pos, iterator first, iterator last ){	return this->M_STLData.insert(pos,first,last);	}

    /// Misc convenience functions
    pointer to_array() const
	{
		pointer out = new T[ this->size() ];
		std::copy(this->begin(), this->end(), out);
		return out;
	}

	INLINE pointer as_array(){	return this->M_STLData.data();	}
	INLINE const_pointer as_array() const {	return this->M_STLData.data();	}
	
	INLINE gsl_vec_t* as_gsl_vector()
	{
		gsl_block_t* b = (gsl_block_t*) malloc( sizeof( gsl_block_t ) );
		b->data = this->M_STLData.data();		
		b->size = this->size();
		
		gsl_vec_t* v = (gsl_vec_t*) malloc( sizeof( gsl_vec_t ) );
		v->owner = 0;	// The gsl_vector doesn't own the underlying memory
		v->block = b;
		v->data = b->data;
		v->size = b->size;
		v->stride = 1;
		
		return v;
	}
	
	INLINE const gsl_vec_t* as_gsl_vector() const
	{
		gsl_block_t* b = (gsl_block_t*) malloc( sizeof( gsl_block_t ) );
		b->data = const_cast< pointer >(this->M_STLData.data());		
		b->size = this->size();
		
		gsl_vec_t* v = (gsl_vec_t*) malloc( sizeof( gsl_vec_t ) );
		v->owner = 0;	// The gsl_vector doesn't own the underlying memory
		v->block = b;
		v->data = b->data;
		v->size = b->size;
		v->stride = 1;
		
		return v;
	}
	
	gsl_vec_t* to_gsl_vector()
	{
		gsl_vec_t* out = gsl_vector_type< T >::alloc( this->size() );
		if ( out == NULL )
			throw std::bad_alloc();
		
		std::copy( this->begin(), this->end(), out->data );
		return out;
	}

    void squeeze()
	{
		if ( this->capacity() == this->size() )
			return;
			
		vector< T > temp(*this);
		this->swap(temp);
	}
	
	INLINE void reset()
	{
		this->clear();
		this->resize(0);
	}
	
	std::ostream &operator<<(std::ostream &os)
	{
		char sep( this->is_col_vector() ?  '\n' : ' ' );

		os << "(" << sep;
		std::copy( this->cbegin(), this->cend(), std::ostream_iterator< T >( os, &sep ));
		os << ")";

		return os;
	}
	
private:

	void M_throw_if_out_of_range( size_type i )
	{
		if ( i >= this->size() ){
			std::stringstream ss;
			ss << "Index, " << i << ", is out of range. Max = " << this->size() - 1;
			throw std::out_of_range(ss.str());
		} 
	}
	
	bool M_bIsColVector;
};

////////////////////////////////////////////////////////////

template< typename T >
gsl::vector< T >& gsl::vector< T >::operator+=(const gsl::vector< T >& right) throw ( vector_size_mismatch )
{
    if( this->size() != right.size() )
        throw vector_size_mismatch();
	
	std::transform(this->begin(), this->end(), right.begin(), this->begin(), std::plus< T >() );
	return *this;
}

////////////////////////////////////////////////////////////

template< typename T >
INLINE gsl::vector< T >& gsl::vector< T >::operator+=( const value_type right)
{
	std::transform(this->begin(), this->end(), this->begin(), std::bind2nd(std::plus< T >(), right) );
	return *this;
}

////////////////////////////////////////////////////////////

template< typename T >
gsl::vector< T >& gsl::vector< T>::operator-=(const gsl::vector< T >& right) throw ( vector_size_mismatch )
{
    if( this->size() != right.size() )
        throw vector_size_mismatch();
	
	std::transform(this->begin(), this->end(), right.begin(), this->begin(), std::minus< T >() );
	return *this;
}

////////////////////////////////////////////////////////////

template< typename T >
INLINE gsl::vector< T >& gsl::vector< T>::operator-=( const value_type right)
{
	std::transform(this->begin(), this->end(), this->begin(), std::bind2nd(std::minus< T >(), right) );
	return *this;
}

////////////////////////////////////////////////////////////

template< typename T >
gsl::vector< T >& gsl::vector< T>::operator*=(const gsl::vector< T >& right) throw ( vector_size_mismatch )
{
	if( this->size() != right.size() )
        throw vector_size_mismatch();
	
	std::transform(this->begin(), this->end(), right.begin(), this->begin(), std::multiplies< T >() );
	return *this;
}

////////////////////////////////////////////////////////////

template< typename T >
INLINE gsl::vector< T >& gsl::vector< T>::operator*=( const value_type right)
{
	std::transform(this->begin(), this->end(), this->begin(), std::bind2nd(std::multiplies< T >(), right) );
	return *this;
}

////////////////////////////////////////////////////////////

template< typename T >
gsl::vector< T >& gsl::vector< T>::operator/=(const gsl::vector< T >& right) throw ( vector_size_mismatch )
{
	if( this->size() != right.size() )
        throw vector_size_mismatch();
	
	std::transform(this->begin(), this->end(), right.begin(), this->begin(), std::divides< T >() );
	return *this;
}

////////////////////////////////////////////////////////////

template< typename T >
INLINE gsl::vector< T >& gsl::vector< T>::operator/=( const value_type right)
{
	std::transform(this->begin(), this->end(), this->begin(), std::bind2nd(std::divides< T >(), right) );
	return *this;
}

////////////////////////////////////////////////////////////

template< typename T >
INLINE void swap( gsl::vector< T >& a, gsl::vector< T >& b)
{
	a.swap( b );
}

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////

/// Element-wise add
/// Returns a new vector whose ith element is the sum of left[i] and right[i]
/// The vectors must have the same size, but the orientation is ignored.
template< typename T , typename U >
const gsl::vector< T > operator+(const gsl::vector< T >& left, const gsl::vector< U >& right)
{
	if ( left.size() != right.size() )
		throw gsl::vector_size_mismatch();
		
	gsl::vector< T > out( left.size() );
	std::transform(left.cbegin(), left.cend(), right.cbegin(), out.begin(), std::plus< T >() );
	return out;
}

/// Element-wise subtract
/// Returns a new vector whose ith element is the difference of left[i] and right[i]
/// The vectors must have the same size, but the orientation is ignored.
template< typename T , typename U >
const gsl::vector< T > operator-(const gsl::vector< T >& left, const gsl::vector< U >& right)
{
	if ( left.size() != right.size() )
		throw gsl::vector_size_mismatch();
		
	gsl::vector< T > out( left.size() );
	std::transform(left.cbegin(), left.cend(), right.cbegin(), out.begin(), std::minus< T >() );
	return out;
}

////////////////////////////////////////////////////////////

/// Element-wise multiply
/// Returns a new vector whose ith element is the product of left[i] and right[i]
/// The vectors must have the same size, but the orientation is ignored.
template< typename T, typename U >
const gsl::vector< T > operator%(const gsl::vector< T >& left, const gsl::vector< U >& right)
{
	if ( left.size() != right.size() )
		throw gsl::vector_size_mismatch();
		
	gsl::vector< T > out( left.size() );
	std::transform(left.cbegin(), left.cend(), right.cbegin(), out.begin(), std::multiplies< T >() );
	return out;
}

////////////////////////////////////////////////////////////

// Element-wise divide
/// Returns a new vector whose ith element is the quotient of left[i] and right[i]
/// The vectors must have the same size, but the orientation is ignored.
template< typename T, typename U >
const gsl::vector< T > operator/(const gsl::vector< T >& left, const gsl::vector< U >& right)
{
	if ( left.size() != right.size() )
		throw gsl::vector_size_mismatch();
		
	gsl::vector< T > out( left.size() );
	std::transform(left.cbegin(), left.cend(), right.cbegin(), out.begin(), std::divides< T >() );
	return out;
}

// Scalar product
template< typename T, typename U >
T operator*(const gsl::vector< T >& left, const gsl::vector< U >& right)
{
	if ( left.size() != right.size() )
		throw gsl::vector_size_mismatch();
		
	gsl::vector< T > temp( left.size() );
	std::transform(left.cbegin(), left.cend(), right.cbegin(), temp.begin(), std::multiplies< T >() );
	return std::accumulate(temp->cbegin(), temp->cend(), realZero, std::plus< T >() );
}

// Vector product
//const gsl::matrix operator^(const gsl::vector& left, const gsl::vector &right) const;

////////////////////////////////////////////////////////////
