#pragma once

#include <stdexcept>
#include <cassert>
#include <iostream>

#include "../Common/exceptions.h"
#include "../Common/number.h"
#include "../Common/macros.h"
#include "../Common/gslstructbase.h"
#include "../Vector/vector.h"

#include <gsl/gsl_matrix.h>

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

class matrix_uninitialised : public std::runtime_error
{
    public:
    matrix_uninitialised() : std::runtime_error("matirx used before initialisation"){}
};

class matrix_size_mismatch : public std::runtime_error
{
	public:
	matrix_size_mismatch() : std::runtime_error("matrix sizes are mismatched"){}
};

////////////////////////////////////////////////////////////

/// Main gsl_vector type template
template< typename T >
struct gsl_matrix_type
{};

/// Template specialisations for actual gsl_matrix types
template<>
struct gsl_matrix_type< real >
{
	typedef gsl_matrix type;
	INLINE static type* alloc( size_t r, size_t c ){	return gsl_matrix_alloc(r,c);	}
};

template<>
struct gsl_matrix_type< char >
{
	typedef gsl_matrix_char type;
	INLINE static type* alloc( size_t r, size_t c ){	return gsl_matrix_char_alloc(r,c);	}
};

template<>
struct gsl_matrix_type< float >
{
	typedef gsl_matrix_float type;
	INLINE static type* alloc( size_t r, size_t c ){	return gsl_matrix_float_alloc(r,c);	}
};

template<>
struct gsl_matrix_type< int >
{
	typedef gsl_matrix_int type;
	INLINE static type* alloc( size_t r, size_t c ){	return gsl_matrix_int_alloc(r,c);	}
};

template<>
struct gsl_matrix_type< long >
{
	typedef gsl_matrix_long type;
	INLINE static type* alloc( size_t r, size_t c ){	return gsl_matrix_long_alloc(r,c);	}
};

template<>
struct gsl_matrix_type< long double >
{
	typedef gsl_matrix_long_double type;
	INLINE static type* alloc( size_t r, size_t c ){	return gsl_matrix_long_double_alloc(r,c);	}
};

template<>
struct gsl_matrix_type< short >
{
	typedef gsl_matrix_short type;
	INLINE static type* alloc( size_t r, size_t c ){	return gsl_matrix_short_alloc(r,c);	}
};

template<>
struct gsl_matrix_type< unsigned char >
{
	typedef gsl_matrix_uchar type;
	INLINE static type* alloc( size_t r, size_t c ){	return gsl_matrix_uchar_alloc(r,c);	}
};

template<>
struct gsl_matrix_type< unsigned short >
{
	typedef gsl_matrix_ushort type;
	INLINE static type* alloc( size_t r, size_t c ){	return gsl_matrix_ushort_alloc(r,c);	}
};

template<>
struct gsl_matrix_type< unsigned int >
{
	typedef gsl_matrix_uint type;
	INLINE static type* alloc( size_t r, size_t c ){	return gsl_matrix_uint_alloc(r,c);	}
};

template<>
struct gsl_matrix_type< unsigned long >
{
	typedef gsl_matrix_ulong type;
	INLINE static type* alloc( size_t r, size_t c ){	return gsl_matrix_ulong_alloc(r,c);	}
};

////////////////////////////////////////////////////////////

template< typename T >
class matrix : public from_STL_container< std::vector< T > >
{
public:
	typedef typename gsl_matrix_type< T >::type gsl_mat_t;
	
	typedef typename from_STL_container< std::vector< T > >::iterator 			iterator;
	typedef typename from_STL_container< std::vector< T > >::const_iterator		const_iterator;
	typedef typename from_STL_container< std::vector< T > >::reference			reference;
    typedef typename from_STL_container< std::vector< T > >::const_reference	const_reference;
    typedef typename from_STL_container< std::vector< T > >::pointer			pointer;
    typedef typename from_STL_container< std::vector< T > >::const_pointer		const_pointer;
    typedef typename from_STL_container< std::vector< T > >::value_type			value_type;
    typedef typename from_STL_container< std::vector< T > >::size_type			size_type;
    typedef typename from_STL_container< std::vector< T > >::difference_type	difference_type;
	
	struct M_matrix_element_type{
		size_type row;
		size_type col;
		
		M_matrix_element_type( size_type r, size_type c ) :
		row( r ), col( c ) {}
		
		INLINE bool operator==( const M_matrix_element_type& right ) const{	return (right.row == row) && (right.col == col);	}
	};

	typedef M_matrix_element_type element_type;
	
	/// Default constructor
	matrix() : M_rows(0), M_cols(0) {}
	
	/// Construct an empty matrix of a given size
	matrix( size_type r, size_type c ) : M_rows(r), M_cols(c)
	{
		this->M_STLData.resize( r*c );
	}
	
	/// Construct a matrix of a given size with each element set to the given value
	matrix( size_type r, size_type c, const value_type& x ) : M_rows(r), M_cols(c)
	{
		this->M_STLData.resize( r*c, x );
	}
	
	/// Copy constructor
	matrix( const matrix< T >& m ) : M_rows(m.rows()), M_cols(m.cols())
	{
		this->M_STLData.resize( M_rows, M_cols );
		std::copy( m.cbegin(), m.cend(), this->begin() );
	}
	
	/// Construct from a gsl_matrix
	matrix( const gsl_mat_t* m ) : M_rows(m->size1), M_cols(m->size2)
	{
		this->M_STLData.resize( M_rows, M_cols );
		std::copy( m->data, m->data + m->block->size, this->begin() );
	}
	
	/// Destructor
	~matrix(){}
	
	/// Swap the contents of this matrix with another
	///
	/// Will not throw
	void swap( matrix< T >& other )
	{
		std::swap( this->M_STLData, other.M_STLData );
		std::swap( this->M_rows, other.M_rows );
		std::swap( this->M_cols, other.M_cols );
	}
	
	/// Assignment operator
	const matrix< T >& operator=(const matrix< T >& right)
	{
		matrix< T > temp( right );
		this->swap( temp );
		return *this;
	}
	
	/// Get the number of rows in the matrix
	/// 
	/// Will not throw
	INLINE size_type rows() const {	return M_rows;	}
	
	/// Get the number of columns in the matrix
	/// 
	/// Will not throw
	INLINE size_type cols() const {	return M_cols;	}
	
private:
	size_type M_rows;
	size_type M_cols;
};




class realMatrix : public gsl::gsl_base_ptr< gsl_matrix > {
	
	public:
	
	typedef real				value_type;
	typedef size_t				size_type;
	typedef real* 				iterator;
	typedef const real*			const_iterator;
	typedef real&				reference;
	typedef const real&			const_reference;
	typedef real*				pointer;
	typedef const real*			const_pointer;
	typedef ptrdiff_t			difference_type;
	
	struct M_matrix_element_type{
		realMatrix::size_type row;
		realMatrix::size_type col;
		
		M_matrix_element_type( realMatrix::size_type r, realMatrix::size_type c ) :
		row( r ), col( c ) {}
		
		INLINE bool operator==( const M_matrix_element_type& right ) const{	return (right.row == row) && (right.col == col);	}
	};
	
	typedef M_matrix_element_type element_type;

	/// Default constructor
	realMatrix() : gsl_base_ptr(NULL), M_pStart(NULL), M_pFinish(NULL), M_uRows(0), M_uCols(0) {}
	
	/// Construct an empty matrix of a given size
	realMatrix( size_type r, size_type c ) throw ( std::bad_alloc ) :
		gsl_base_ptr( gsl_matrix_alloc( (r < 1 ? 1 : r ), (c < 1 ? 1 : c) ) )
	{
		if ( isNull() )
			throw std::bad_alloc();
			
		M_set_all_fields( this->const_ptr() );
	}
	
	/// Construct a matrix of a given size with each element set to the given value
	realMatrix( size_type r, size_type c, const value_type& x ) throw ( std::bad_alloc ) :
	gsl_base_ptr( gsl_matrix_alloc( (r < 1 ? 1 : r ), (c < 1 ? 1 : c) ) )
	{
		if ( isNull() )
			throw std::bad_alloc();
			
		M_set_all_fields( this->const_ptr() );
		std::fill( this->begin(), this->end(), x );
	}
	
	/// Copy constructor
	realMatrix( const realMatrix& m ) throw ( std::bad_alloc )
	{
		realMatrix temp( m.rows(), m.cols() );
		std::copy( m.cbegin(), m.cend(), temp.begin() );
		
		this->swap( temp );
	}
	
	/// Construct from a gsl_matrix
	realMatrix( const gsl_matrix* m ) throw ( std::bad_alloc )
	{
		realMatrix temp( m->size1, m->size2 );
		std::copy( m->data, m->data + m->size1 * m->size2, temp.begin() );
		
		this->swap( temp );
	}
	
	/// Destructor
	~realMatrix()
	{
		if ( hasValue() )
			gsl_matrix_free( M_pGSLData );
	}
	
	/// Swap the contents of this matrix with another
	///
	/// Will not throw
	void swap( realMatrix& m );
	
	/// Assignment operator
	const realMatrix &operator=(const realMatrix& right) throw (std::bad_alloc);
	
	/// Unary arithmetic operators (scalars)
	/// 
	/// Will not throw
	const realMatrix &operator+=(const value_type x);
	const realMatrix &operator-=(const value_type x);
	const realMatrix &operator*=(const value_type x);
	
	/// Unary divide operator (scalar).  Will set elements to +/- inf if the value is zero
	/// Will set value to NaN if the element and x are both zero
	const realMatrix &operator/=(const value_type x);
	
	/// Unary arithetic operators (matrices)
	const realMatrix &operator+=(const realMatrix& right) throw ( matrix_size_mismatch );
	const realMatrix &operator-=(const realMatrix& right) throw ( matrix_size_mismatch );
	const realMatrix &operator*=(const realMatrix& right) throw ( matrix_size_mismatch );
	
	/// Unary divide operator (matrix).  Will set elements to +/- inf if the value is zero
	/// Will set value to NaN if the element and right.element are both zero
	const realMatrix &operator/=(const realMatrix& right) throw ( matrix_size_mismatch );
	
	/// Logical equality
	///
	/// Will not throw
	bool operator==( const realMatrix& right ) const;
	
	/// Logical inequality
	///
	/// Will not throw
	INLINE bool operator!=( const realMatrix& right ) const{		return !(*this == right );		}
	
	/// Get an rvalue for an element directly, without range checking
	///
	/// Will not throw
	INLINE const_reference operator[]( const realMatrix::element_type& x ) const {
		return *( cbegin() + ( x.row * cols() ) + x.col );
	}
	
	/// Get an lvalue for an element directly, without range checking
	///
	/// Will not throw
	INLINE reference operator[]( const realMatrix::element_type& x ){
		return *( begin() + ( x.row * cols() ) + x.col );
	}
	
	/// Get an rvalue for an element directly, with cyclic boundary conditions
	///
	/// Will not throw, but behaviour will be undefined if the matrix is uninitialised, or has zero size
	INLINE const_reference operator()( int r, int c ) const {
		int R = static_cast< int >( rows() );
		int C = static_cast< int >( cols() );
		return *( cbegin() + ((r % R + R) % R) * C + ( (c % C + C) % C ) );
	}
	
	/// Get an lvalue for an element directly, with cyclic boundary conditions
	///
	/// Will not throw, but behaviour will be undefined if the matrix is uninitialised, or has zero size
	INLINE reference operator()( int r, int c ){
		int R = static_cast< int >( rows() );
		int C = static_cast< int >( cols() );
		return *( begin() + ((r % R + R) % R) * C + ( (c % C + C) % C ) );
	}
	
	/// Get an rvalue for an element directly, with cyclic boundary conditions
	///
	/// Will not throw, but behaviour will be undefined if the matrix is uninitialised, or has zero size
	INLINE const_reference operator()( const realMatrix::element_type& x ) const {
		return this->operator()( x.row, x.col );
	}
	
	/// Get an lvalue for an element directly, with cyclic boundary conditions
	///
	/// Will not throw, but behaviour will be undefined if the matrix is uninitialised, or has zero size
	INLINE reference operator()( const realMatrix::element_type& x ) {
		return this->operator()( x.row, x.col );
	}
	
	/// Get an rvalue for an element directly, with validity- and range-checking
	const_reference at(const realMatrix::size_type& r, const realMatrix::size_type& c) const;
	
	/// Get an rvalue for an element directly, with validity- and range-checking
	reference at(const realMatrix::size_type& r, const realMatrix::size_type& c);
	
	/// Get the number of rows in the matrix
	/// 
	/// Will not throw
	INLINE size_type rows() const {	return M_uRows;	}
	
	/// Get the number of columns in the matrix
	/// 
	/// Will not throw
	INLINE size_type cols() const {	return M_uCols;	}
	
	/// Get a const_iterator to the first element in the matrix
	///
	/// Will not throw, can return NULL
	INLINE const_iterator cbegin() const {		return M_pStart;	}
	
	/// Get a const_iterator to one past the last element in the matrix
	///
	/// Will not throw, can return NULL
	INLINE const_iterator cend() const {		return M_pFinish;	}
	
	/// Get an iterator to the first element in the matrix
	///
	/// Will not throw, can return NULL
	INLINE iterator begin() {	return M_pStart;		}
	
	/// Get an iterator to one past the last element in the matrix
	///
	/// Will not throw, can return NULL
	INLINE iterator end() {		return M_pFinish;		}
	
	/// Get a row from the matrix as a vector
	gsl::vector< real > row( size_type r ) const throw ( matrix_uninitialised, std::out_of_range, std::bad_alloc );
	
	/// Get a column from the matrix as a vector
	gsl::vector< real > col( size_type c ) const throw ( matrix_uninitialised, std::out_of_range, std::bad_alloc );
	
	/// Get the k-th diagonal of the matrix as a vector.
	gsl::vector< real > diagonal( int k = 0 ) const throw ( matrix_uninitialised, std::out_of_range, std::bad_alloc );
	
	/// Set the values of a given matrix row
	void setRow( size_type r, const gsl::vector< real >& v ) throw ( matrix_uninitialised, std::out_of_range);
	
	/// Set the values of a given matrix column
	void setCol( size_type c, const gsl::vector< real >& v ) throw ( matrix_uninitialised, std::out_of_range);
	
	/// Get the matrix transpose (returns a new matrix)
	gsl::realMatrix transpose() const throw ( matrix_uninitialised );
	
	/// Determine if the matrix is square or not
	INLINE bool isSquare() const {	return this->rows() == this->cols();	}
	
	/// Exchange two columns
	void swapCols( size_type c1, size_type c2 ) throw (std::out_of_range );
	
	/// Exchange two rows
	void swapRows( size_type r1, size_type r2 ) throw (std::out_of_range );
	
	/// Exchange row r with column c (matrix must be square)
	void swapRowCol(size_type r, size_type c ) throw (std::out_of_range, matrix_uninitialised );
	
	/// Get the minimum (non-empty) value in the matrix
	/// Returns realEmpty if all the values in the matrix are empty
	value_type min() const throw ( matrix_uninitialised );
	
	/// Get the maximum (non-empty) value in the matrix
	/// Returns realEmpty if all the values in the matrix are empty
	value_type max() const throw ( matrix_uninitialised );
	
	/// Get both the minimun and maximum (non-empty) values in the matrix
	/// Returns realEmpty if all the values in the matrix are empty
	std::pair< value_type, value_type > minMax() const  throw ( matrix_uninitialised );
	
	/// Get the minimum element in the matrix
	/// Returns the final element if all values are empty
	element_type min_element() const throw ( matrix_uninitialised );
	
	/// Get the maximum element in the matrix
	/// Returns the final element if all values are empty
	element_type max_element() const throw ( matrix_uninitialised );
	
	/// Get both the minimun and maximum (non-empty) values in the matrix
	/// Returns the final element if all values are empty
	std::pair< element_type, element_type > minMax_element() const throw ( matrix_uninitialised );

	private:
	
	pointer M_pStart;
	pointer M_pFinish;
	size_type M_uRows;
	size_type M_uCols;
	
	/// Set all private fields to NULL
	///
	/// Will not throw
	INLINE void M_zero_all_fields()
	{
		M_pStart = NULL;
		M_pFinish = NULL;
		M_uRows = 0;
		M_uCols = 0;
	}
	
	/// Set all private fields to correspond to a gsl_matrix structs values
	/// m must not be NULL
	///
	/// Will not throw
	INLINE void M_set_all_fields( const gsl_matrix* m )
	{
		assert( m != 0 );
		M_pStart = m->block->data;
		M_pFinish = M_pStart + m->size1 * m->size2;
		M_uRows = m->size1;
		M_uCols = m->size2;
	}
	
	/// Check that the row and column sizes for this matrix are equal to the
	/// given matrix
	///
	/// Will not throw
	INLINE bool M_dimensions_are_equal( const realMatrix& m ) const
	{
		return ( this->rows() == m.rows() ) && ( this->cols() == m.cols() );
	}
};

	INLINE void swap( realMatrix& a, realMatrix& b ){	a.swap( b );	}

END_GSL_NAMESPACE

bool operator==( const gsl::realMatrix& left, const gsl::realMatrix::value_type& x );
bool operator==( const gsl::realMatrix::value_type& x, const gsl::realMatrix& right );
bool operator!=( const gsl::realMatrix& left, const gsl::realMatrix::value_type& x );
bool operator!=( const gsl::realMatrix::value_type& x, const gsl::realMatrix& right );
bool operator<( const gsl::realMatrix& left, const gsl::realMatrix::value_type& x );
bool operator<( const gsl::realMatrix::value_type& x, const gsl::realMatrix& right );
bool operator>( const gsl::realMatrix& left, const gsl::realMatrix::value_type& x );
bool operator>( const gsl::realMatrix::value_type& x, const gsl::realMatrix& right );
bool operator<=( const gsl::realMatrix& left, const gsl::realMatrix::value_type& x );
bool operator<=( const gsl::realMatrix::value_type& x, const gsl::realMatrix& right );
bool operator>=( const gsl::realMatrix& left, const gsl::realMatrix::value_type& x );
bool operator>=( const gsl::realMatrix::value_type& x, const gsl::realMatrix& right );

std::ostream &operator<<(std::ostream &os, const gsl::realMatrix &right);

// Addition and subtraction
const gsl::realMatrix operator+(const gsl::realMatrix& left, const gsl::realMatrix& right);
const gsl::realMatrix operator+(const gsl::realMatrix& left, const gsl::realMatrix::value_type& x);
const gsl::realMatrix operator+(const gsl::realMatrix::value_type& x, const gsl::realMatrix& right);
const gsl::realMatrix operator-(const gsl::realMatrix& left, const gsl::realMatrix& right);
const gsl::realMatrix operator-(const gsl::realMatrix& left, const gsl::realMatrix::value_type& x);
const gsl::realMatrix operator-(const gsl::realMatrix::value_type& x, const gsl::realMatrix& right);


// Element-wise divide
const gsl::realMatrix operator/(const gsl::realMatrix& left, const gsl::realMatrix& right);
const gsl::realMatrix operator/(const gsl::realMatrix& left, const gsl::realMatrix::value_type& x);
const gsl::realMatrix operator/(const gsl::realMatrix::value_type& x, const gsl::realMatrix& right);

// Element-wise multiply
const gsl::realMatrix operator%(const gsl::realMatrix& left, const gsl::realMatrix& right);
const gsl::realMatrix operator%(const gsl::realMatrix& left, const gsl::realMatrix::value_type& x);
const gsl::realMatrix operator%(const gsl::realMatrix::value_type& x, const gsl::realMatrix& right);

// Matrix product
const gsl::realMatrix operator*(const gsl::realMatrix& left, const gsl::realMatrix& right ) throw ( gsl::matrix_size_mismatch );
const gsl::realMatrix operator*(const gsl::realMatrix& left, const gsl::realMatrix::value_type& x);
const gsl::realMatrix operator*(const gsl::realMatrix::value_type& x, const gsl::realMatrix& right);
const gsl::vector< real > operator*(const gsl::realMatrix& left, const gsl::vector< real >& v) throw ( gsl::matrix_size_mismatch );