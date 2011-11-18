#pragma once

#include <stdexcept>
#include <cassert>
#include <iostream>
#include <iomanip>

#include "../Common/exceptions.h"
#include "../Common/number.h"
#include "../Common/macros.h"
#include "../Common/gslstructbase.h"
#include "../Vector/vector.h"
#include "../Block/block.h"

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_complex.h>

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

template<>
struct gsl_matrix_type< std::complex< real > >
{
	typedef gsl_matrix_complex type;
	INLINE static type* alloc( size_t r, size_t c ){	return gsl_matrix_complex_alloc(r,c);	}
};

////////////////////////////////////////////////////////////

template< typename T >
class matrix : public from_STL_container< std::vector< T > >
{
public:
	typedef typename gsl_matrix_type< T >::type gsl_mat_t;
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
		this->M_STLData.assign( r*c, x );
	}
	
	/// Construct from a pointer to a gsl_matrix
	matrix( const gsl_mat_t* pcGSL_matrix ) : M_rows(pcGSL_matrix->size1), M_cols( pcGSL_matrix->size2)
	{
		size_type iDataLength = M_rows * M_cols;
		this->M_STLData.resize( iDataLength );
		std::copy( pcGSL_matrix->data, pcGSL_matrix->data + iDataLength, this->M_STLData.begin() );
	}
	
	/// Copy constructor
	matrix( const matrix< T >& m ) : M_rows(m.rows()), M_cols(m.cols())
	{
		this->M_STLData.resize( M_rows * M_cols );
		std::copy( m.cbegin(), m.cend(), this->begin() );
	}
	
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
	
	/// Get a const_iterator to the first element in the matrix
	///
	/// Will not throw, can return NULL
	INLINE const_iterator cbegin() const {		return this->M_STLData.begin();	}
	
	/// Get a const_iterator to the first element in the matrix
	///
	/// Will not throw, can return NULL
	INLINE const_iterator begin() const {		return this->M_STLData.begin();	}
	
	/// Get a const_iterator to one past the last element in the matrix
	///
	/// Will not throw, can return NULL
	INLINE const_iterator cend() const {		return this->M_STLData.end();	}
	
	/// Get a const_iterator to one past the last element in the matrix
	///
	/// Will not throw, can return NULL
	INLINE const_iterator end() const {		return this->M_STLData.end();	}
	
	/// Get an iterator to the first element in the matrix
	///
	/// Will not throw, can return NULL
	INLINE iterator begin() {	return this->M_STLData.begin();		}
	
	/// Get an iterator to one past the last element in the matrix
	///
	/// Will not throw, can return NULL
	INLINE iterator end() {		return this->M_STLData.end();		}
	
	/// Get the number of rows in the matrix
	/// 
	/// Will not throw
	INLINE size_type rows() const {	return M_rows;	}
	
	/// Get the number of columns in the matrix
	/// 
	/// Will not throw
	INLINE size_type cols() const {	return M_cols;	}
	
	/// Unary arithmetic operators (scalars)
	/// 
	/// Will not throw
	INLINE const matrix< T > &operator+=(const value_type& x){
		std::transform( this->begin(), this->end(), this->begin(), std::bind2nd(std::plus< T >(), x ) );
		return *this;
	}
	const matrix< T >& operator-=(const value_type& x){
		std::transform( this->begin(), this->end(), this->begin(), std::bind2nd(std::minus< T >(), x ) );
		return *this;
	}
	const matrix< T >& operator*=(const value_type& x){
		std::transform( this->begin(), this->end(), this->begin(), std::bind2nd(std::multiplies< T >(), x ) );
		return *this;
	}
	const matrix< T >& operator/=(const value_type& x){
		std::transform( this->begin(), this->end(), this->begin(), std::bind2nd(std::divides< T >(), x ) );
		return *this;
	}
	
	
	/// Unary arithetic operators (matrices)
	const matrix< T >& operator+=(const matrix< T >& right) throw ( matrix_size_mismatch ){
		if ( this->size() != right.size() )
			throw matrix_size_mismatch();
		std::transform( this->begin(), this->end(), right.begin(), this->begin(), std::plus< T >() );
		return *this;
	}
	const matrix< T >& operator-=(const matrix< T >& right) throw ( matrix_size_mismatch ){
		if ( this->size() != right.size() )
			throw matrix_size_mismatch();
		std::transform( this->begin(), this->end(), right.begin(), this->begin(), std::minus< T >() );
		return *this;
	}
	const matrix< T >& operator*=(const matrix< T >& right) throw ( matrix_size_mismatch ){
		if ( this->size() != right.size() )
			throw matrix_size_mismatch();
		std::transform( this->begin(), this->end(), right.begin(), this->begin(), std::multiplies< T >() );
		return *this;
	}
	const matrix< T >& operator/=(const matrix< T >& right) throw ( matrix_size_mismatch ){
		if ( this->size() != right.size() )
			throw matrix_size_mismatch();
		std::transform( this->begin(), this->end(), right.begin(), this->begin(), std::divides< T >() );
		return *this;
	}
	
	/// Logical equality
	///
	/// Will not throw
	INLINE bool operator==( const matrix< T >& right ) const
	{	return this->M_rows == right.M_rows && this->M_cols == right.M_cols && this->M_STLData == right.M_STLData;	}
	
	/// Logical inequality
	///
	/// Will not throw
	INLINE bool operator!=( const matrix< T >& right ) const{		return !(*this == right );		}
	
	/// Get an rvalue for an element directly, without range checking
	///
	/// Will not throw
	INLINE const_reference operator[]( const matrix< T >::element_type& x ) const {
		return *( cbegin() + ( x.row * cols() ) + x.col );
	}
	
	/// Get an lvalue for an element directly, without range checking
	///
	/// Will not throw
	INLINE reference operator[]( const matrix< T >::element_type& x ){
		return *( begin() + ( x.row * cols() ) + x.col );
	}
	
	/// Get an rvalue for a row directly, without range checking
	///
	/// Will not throw
	INLINE gsl::vector< T > operator[]( const matrix< T >::size_type r ) const {
		return gsl::vector< T >( this->begin() + r * this->cols(), this->begin() + (r + 1) * this->cols(), false );
	}
	
	/// Get an rvalue for an element directly, with cyclic boundary conditions
	///
	/// Will not throw, but behaviour will be undefined if the matrix is uninitialised, or has zero size
	INLINE const_reference operator()( int r, int c ) const {
		int R = static_cast< int >( rows() ), C = static_cast< int >( cols() );
		return *( cbegin() + ((r % R + R) % R) * C + ( (c % C + C) % C ) );
	}
	
	/// Get an lvalue for an element directly, with cyclic boundary conditions
	///
	/// Will not throw, but behaviour will be undefined if the matrix is uninitialised, or has zero size
	INLINE reference operator()( int r, int c ){
		int R = static_cast< int >( rows() ), C = static_cast< int >( cols() );
		return *( begin() + ((r % R + R) % R) * C + ( (c % C + C) % C ) );
	}
	
	/// Get an rvalue for an element directly, with cyclic boundary conditions
	///
	/// Will not throw, but behaviour will be undefined if the matrix is uninitialised, or has zero size
	INLINE const_reference operator()( const element_type& x ) const {
		return this->operator()( x.row, x.col );
	}
	
	/// Get an lvalue for an element directly, with cyclic boundary conditions
	///
	/// Will not throw, but behaviour will be undefined if the matrix is uninitialised, or has zero size
	INLINE reference operator()( const element_type& x ) {
		return this->operator()( x.row, x.col );
	}
	
	/// Get an rvalue for an element directly, with validity- and range-checking
	const_reference at(const size_type& r, const size_type& c) const throw( std::out_of_range ){
		if ( r >= this->rows() || c >= this->cols() )
			throw std::out_of_range("matrix index out of range");
		
		return this->operator[]( element_type(r,c) );
	}
	
	/// Get an rvalue for an element directly, with validity- and range-checking
	reference at(const size_type& r, const size_type& c) throw( std::out_of_range ){
		if ( r >= this->rows() || c >= this->cols() )
			throw std::out_of_range("matrix index out of range");
		
		return this->operator[]( element_type(r,c) );
	}
	
	/// Get a row from the matrix as a vector
	gsl::vector< T > row( size_type r ) const throw ( std::out_of_range )
	{
		if ( r >= this->rows() )
			throw std::out_of_range("Matrix element out-of-range");
			
		return gsl::vector< T >( this->begin() + r * this->cols(), this->begin() + (r + 1) * this->cols(), false );
	}
	
	/// Get a column from the matrix as a vector
	gsl::vector< T > col( size_type c ) const throw ( std::out_of_range )
	{
		if ( c >= this->cols() )
			throw std::out_of_range("Matrix element out-of-range");
			
		gsl::vector< T > out( this->rows() );
		out.set_col_vector();
		
		typename gsl::vector< T >::iterator it_out = out.begin();
		const typename gsl::vector< T >::const_iterator it_outEnd = out.end();
		const_iterator it_matrix = this->begin() + c;
		difference_type step = this->cols();
		
		while( it_out != it_outEnd ){
			*it_out = *it_matrix;
			++it_out;
			std::advance( it_matrix, step );
		}
		
		return out;
	}
	
	/// Get the k-th diagonal of the matrix as a vector.
	gsl::vector< T > diagonal( int k = 0 ) const throw ( std::out_of_range )
	{
		if ( k >= static_cast< int >( this->cols() ) || -k >= static_cast< int >( this->rows() ) )
			throw std::out_of_range( "matrix element out-of-range" );
			
		size_type size = k < 0 ? std::min( this->cols(), this->rows() + k ) : std::min( this->rows(), this->cols() - k );
		gsl::vector< T > out( size );

		typename gsl::vector< T >::iterator it_out = out.begin();
		const typename gsl::vector< T >::const_iterator it_end = out.end();
		const_iterator it_matrix = this->begin() + ( k < 0 ? -k * this->cols() : k );
		difference_type step = this->cols() + 1;
		
		while( it_out != it_end ){
			*it_out = *it_matrix;
			++it_out;
			std::advance( it_matrix, step );
		}

		return out;
	}
	
	/// Misc convenience functions
    pointer to_array() const
	{
		pointer out = new T[ this->size() ];
		std::copy(this->begin(), this->end(), out);
		return out;
	}
	
	INLINE const_pointer as_array() const {	return ( ! this->M_STLData.empty() ? this->M_STLData.data() : NULL );	}
	INLINE pointer as_array() {	return ( ! this->M_STLData.empty() ? this->M_STLData.data() : NULL );	}
	
	INLINE gsl_mat_t* as_gsl_matrix()
	{
		gsl_block_t* b = (gsl_block_t*) malloc( sizeof( gsl_block_t ) );
		b->data = this->M_STLData.data();		
		b->size = this->size();
		
		gsl_mat_t* m = (gsl_mat_t*) malloc( sizeof( gsl_mat_t ) );
		m->owner = 0;	// The gsl_matrix doesn't own the underlying memory
		m->block = b;
		m->data = b->data;
		m->size1 = this->rows();
		m->size2 = this->cols();
		m->tda = this->cols(); 
		
		return m;
	}
	
	INLINE const gsl_mat_t* as_gsl_matrix() const
	{
		gsl_block_t* b = (gsl_block_t*) malloc( sizeof( gsl_block_t ) );
		b->data = const_cast< pointer >( this->M_STLData.data() );		
		b->size = this->size();
		
		gsl_mat_t* m = (gsl_mat_t*) malloc( sizeof( gsl_mat_t ) );
		m->owner = 0;	// The gsl_matrix doesn't own the underlying memory
		m->block = b;
		m->data = b->data;
		m->size1 = this->rows();
		m->size2 = this->cols();
		m->tda = this->cols(); 
		
		return m;
	}
	
	gsl_mat_t* to_gsl_matrix() const
	{
		gsl_mat_t* out = gsl_matrix_type< T >::alloc( this->rows(), this->cols() );
		if ( out == NULL )
			throw std::bad_alloc();
		
		std::copy( this->begin(), this->end(), out->data );
		return out;
	}
	
	/// Set the values of a given matrix row
	void set_row( size_type r, const gsl::vector< T >& v ) throw ( std::out_of_range){
		if ( r >= this->rows() )
			throw std::out_of_range("Martix row out-of-range");
			
		if ( v.size() > this->cols() )
			throw std::out_of_range("Matrix column out-of-range");
		
		iterator it_copyStart = this->begin();
		std::advance( it_copyStart, r * this->cols() );
		std::copy( v.begin(), v.end(), it_copyStart );
	}
	
	/// Set the values of a given matrix column
	void set_col( size_type c, const gsl::vector< T >& v ) throw ( std::out_of_range){
		if ( c >= this->cols() )
			throw std::out_of_range("Martix column out-of-range");
			
		if ( v.size() > this->rows() )
			throw std::out_of_range("Matrix row out-of-range");
			
		iterator it_copyStart = this->begin();
		std::advance( it_copyStart, c );
		typename gsl::vector< T >::const_iterator it_v = v.begin();
		const typename gsl::vector< T >::const_iterator it_end = v.end();
		while( it_v != it_end ){
			*it_copyStart = *it_v++;
			std::advance( it_copyStart, this->cols() );
		}
	}
	
	/// Get the matrix transpose (returns a new matrix)
	gsl::matrix< T > transpose() const
	{
		size_type iRows = this->rows();
		size_type iCols = this->cols();
		gsl::matrix< T > out( iCols, iRows );
		
		typename gsl::matrix< T >::const_iterator it_this = this->begin();
		for ( size_type i = 0; i < iRows; ++i ){
			typename gsl::matrix< T >::iterator it_out = out.begin() + i;
			for ( size_type j = 0; j < iCols; ++j ){
				*it_out = *it_this++;
				std::advance( it_out, iRows );
			}
		}
		
		return out;
	}
	
	/// Determine if the matrix is square or not
	INLINE bool is_square() const {	return this->rows() == this->cols();	}
	
	/// Exchange two columns
	void swap_cols( size_type c1, size_type c2 ) throw (std::out_of_range ){
		size_type iRows = this->rows();
		size_type iCols = this->cols();
		
		if ( c1 >= iCols || c2 >= iCols )
			throw std::out_of_range( "Matrix column out-of-range" );
			
		typename gsl::matrix< T >::iterator it_1 = this->begin() + c1;
		typename gsl::matrix< T >::iterator it_2 = this->begin() + c2;
		for ( size_type i = 0; i < iRows; ++i ){
			T temp = *it_1;
			*it_1 = *it_2;
			*it_2 = temp;
			std::advance( it_1, iCols);
			std::advance( it_2, iCols);
		}
	}
	
	/// Exchange two rows
	void swap_rows( size_type r1, size_type r2 ) throw (std::out_of_range ){
		size_type iRows = this->rows();
		size_type iCols = this->cols();
		if ( r1 >= iRows || r2 >= iRows )
			throw std::out_of_range( "Matrix row out-of-range" );
			
		typename gsl::matrix< T >::iterator it_1 = this->begin() + r1 * iCols;
		typename gsl::matrix< T >::iterator it_2 = this->begin() + r2 * iCols;
		for ( size_type i = 0; i < iCols; ++i ){
			T temp = *it_1;
			*it_1 = *it_2;
			*it_2 = temp;
			++it_1;	++it_2;
		}
	}
	
	/// Exchange row r with column c (matrix must be square)
	void swap_row_col(size_type r, size_type c ) throw (std::out_of_range ){
		size_type iRows = this->rows();
		size_type iCols = this->cols();
		
		if ( r >= iRows || c >= iCols)
			throw std::out_of_range( "Matrix row out-of-range" );
			
		if ( iRows != iCols )
			throw gsl::matrix_size_mismatch();
			
		typename gsl::matrix< T >::iterator it_1 = this->begin() + r * iCols;
		typename gsl::matrix< T >::iterator it_2 = this->begin() + c;
		for ( size_type i = 0; i < iCols; ++i ){
			T temp = *it_1;
			*it_1 = *it_2;
			*it_2 = temp;
			++it_1;
			std::advance( it_2, iCols );
		}
	}
	
	/// Get the a const_iterator to the minimum (non-empty) value in the matrix
	/// Returns realEmpty if all the values in the matrix are empty
	INLINE const_iterator min() const
	{	return std::min_element(this->begin(), this->end() );	}
	
	/// Get the a const_iterator to the maximum (non-empty) value in the matrix
	/// Returns realEmpty if all the values in the matrix are empty
	INLINE const_iterator max() const
	{	return std::max_element(this->begin(), this->end() );	}
	
	/// Get const_iterators to the min and max (non-empty) values in the matrix
	/// Returns realEmpty if all the values in the matrix are empty
	INLINE std::pair< const_iterator, const_iterator > min_max() const
	{	return std::make_pair( this->min(), this->max() );		}
	
	/// Get the an iterator to the minimum (non-empty) value in the matrix
	/// Returns realEmpty if all the values in the matrix are empty
	INLINE iterator min()
	{	return std::min_element(this->begin(), this->end() );	}
	
	/// Get the an iterator to the maximum (non-empty) value in the matrix
	/// Returns realEmpty if all the values in the matrix are empty
	INLINE iterator max()
	{	return std::max_element(this->begin(), this->end() );	}
	
	/// Get iterators to the min and max (non-empty) values in the matrix
	/// Returns realEmpty if all the values in the matrix are empty
	INLINE std::pair< iterator, iterator > min_max()
	{	return std::make_pair( this->min(), this->max() );		}
	
	/// Get the minimum (non-empty) value in the matrix
	/// Returns realEmpty if all the values in the matrix are empty
	INLINE value_type min_value() const
	{	return *std::min_element(this->begin(), this->end() );	}
	
	/// Get the maximum (non-empty) value in the matrix
	/// Returns realEmpty if all the values in the matrix are empty
	INLINE value_type max_value() const
	{	return *std::max_element(this->begin(), this->end() );	}
	
	/// Get both the minimun and maximum (non-empty) values in the matrix
	/// Returns realEmpty if all the values in the matrix are empty
	INLINE std::pair< value_type, value_type > min_max_value() const
	{	return std::make_pair( *this->min(), *this->max() );	}
	
	/// Get the minimum element in the matrix
	/// Returns the final element if all values are empty
	element_type min_element() const{
		size_type iMinIndex = std::distance( this->begin(), this->min() );
		return element_type( M_row_index(iMinIndex), M_col_index( iMinIndex ) );
	}
	
	/// Get the maximum element in the matrix
	/// Returns the final element if all values are empty
	element_type max_element() const{
		size_type iMaxIndex = std::distance( this->begin(), this->max() );
		return element_type( M_row_index(iMaxIndex), M_col_index( iMaxIndex ) );
	}
	
	/// Get both the minimun and maximum (non-empty) elements in the matrix
	/// Returns the final element if all values are empty
	INLINE std::pair< element_type, element_type > min_max_element() const
	{	return std::make_pair( this->min_element(), this->max_element() );	}
	
private:
	
	size_type M_rows;
	size_type M_cols;
	
	INLINE size_type M_row_index( size_type x ) const {	return x / M_cols;	}
	INLINE size_type M_col_index( size_type x )const {	return x % M_cols;	}
};

END_GSL_NAMESPACE

// Addition and subtraction
template< typename T >
const gsl::matrix< T > operator+(const gsl::matrix< T >& left, const gsl::matrix< T >& right){
	gsl::matrix< T > out( left );
	return out += right;	// this will throw if sizes are mis-matched
}

template< typename T >
const gsl::matrix< T > operator+(const gsl::matrix< T >& left, const typename gsl::matrix< T >::value_type& x){
	gsl::matrix< T > out( left );
	return out += x;
}

template< typename T >
const gsl::matrix< T > operator+(const typename gsl::matrix< T >::value_type& x, const gsl::matrix< T >& right){
	gsl::matrix< T > out( right.rows(), right.cols() );
	std::transform( right.begin(), right.end(), out.begin(), std::bind1st( std::plus< T >(), x ) );
	return out;
}

template< typename T >
const gsl::matrix< T > operator-(const gsl::matrix< T >& left, const gsl::matrix< T >& right){
	gsl::matrix< T > out( left );
	return out -= right;	// this will throw if sizes are mis-matched
}

template< typename T >
const gsl::matrix< T > operator-(const gsl::matrix< T >& left, const typename gsl::matrix< T >::value_type& x){
	gsl::matrix< T > out( left );
	return out -= x;
}

template< typename T >
const gsl::matrix< T > operator-(const typename gsl::matrix< T >::value_type& x, const gsl::matrix< T >& right){
	gsl::matrix< T > out( right.rows(), right.cols() );
	std::transform( right.begin(), right.end(), out.begin(), std::bind1st( std::minus< T >(), x ) );
	return out;
}

// Element-wise divide
template< typename T >
const gsl::matrix< T > operator/(const gsl::matrix< T >& left, const gsl::matrix< T >& right){
	gsl::matrix< T > out( left );
	return out /= right;	// this will throw if sizes are mis-matched
}

template< typename T >
const gsl::matrix< T > operator/(const gsl::matrix< T >& left, const typename gsl::matrix< T >::value_type& x){
	gsl::matrix< T > out( left );
	return out /= x;
}

template< typename T >
const gsl::matrix< T > operator/(const typename gsl::matrix< T >::value_type& x, const gsl::matrix< T >& right){
	gsl::matrix< T > out( right.rows(), right.cols() );
	std::transform( right.begin(), right.end(), out.begin(), std::bind1st( std::divides< T >(), x ) );
	return out;
}

// Element-wise multiply
template< typename T >
const gsl::matrix< T > operator%(const gsl::matrix< T >& left, const gsl::matrix< T >& right){
	gsl::matrix< T > out( left );
	return out *= right;	// this will throw if sizes are mis-matched
}

template< typename T >
const gsl::matrix< T > operator%(const gsl::matrix< T >& left, const typename gsl::matrix< T >::value_type& x){
	gsl::matrix< T > out( left );
	return out *= x;
}

template< typename T >
const gsl::matrix< T > operator%(const typename gsl::matrix< T >::value_type& x, const gsl::matrix< T >& right){
	gsl::matrix< T > out( right.rows(), right.cols() );
	std::transform( right.begin(), right.end(), out.begin(), std::bind1st( std::multiplies< T >(), x ) );
	return out;
}

// Matrix product
template< typename T >
const gsl::matrix< T > operator*(const gsl::matrix< T >& left, const gsl::matrix< T >& right ) throw ( gsl::matrix_size_mismatch ){
	if ( left.cols() != right.rows() )
		throw gsl::matrix_size_mismatch();
		
	gsl::matrix< T > out( left.rows(), right.cols() );
	
	gsl_blas_dgemm( CblasNoTrans, CblasNoTrans, 1.0, left.as_gsl_matrix(), right.as_gsl_matrix(), 0.0, out.as_gsl_matrix() );
					
	return out;
}

template<>
const gsl::matrix< std::complex< real > > operator*(const gsl::matrix< std::complex<real> >& left, const gsl::matrix< std::complex<real> >& right ) throw ( gsl::matrix_size_mismatch ){
	if ( left.cols() != right.rows() )
		throw gsl::matrix_size_mismatch();
		
	gsl_matrix_complex* gsl_left = gsl_matrix_complex_alloc( left.rows(), left.cols());
	if ( gsl_left == NULL )
		throw std::bad_alloc();
		
	gsl_matrix_complex* gsl_right = gsl_matrix_complex_alloc( right.rows(), right.cols());
	if ( gsl_right == NULL )
		throw std::bad_alloc();
		
	gsl_matrix_complex* gsl_out = gsl_matrix_complex_alloc( left.rows(), right.cols());
	if ( gsl_out == NULL )
		throw std::bad_alloc();
	
	typedef gsl::matrix< std::complex< real > >::element_type xy;
	typedef gsl::matrix< std::complex< real > >::size_type size_type;
	
	size_type iLeftElementCount = left.rows() * left.cols();
	for ( size_type i = 0; i < iLeftElementCount; ++i ){
		gsl_left->data[ 2*i ] = left.as_array()[ i ].real();
		gsl_left->data[ 2*i + 1 ] = left.as_array()[ i ].imag();
	}
	
	gsl_complex z0, z1;
	GSL_SET_COMPLEX(&z0, 1.0, 0.0);
	GSL_SET_COMPLEX(&z1, 0.0, 0.0);
	
	gsl_blas_zgemm( CblasNoTrans, CblasNoTrans, z0, gsl_left, gsl_right, z1, gsl_out );
					
	gsl::matrix< std::complex<real> > out( left.rows(), right.cols() );
	gsl::matrix< std::complex<real> >::iterator it = out.begin();
	for ( size_type i = 0; i < iLeftElementCount; ++i, ++it ){
		*it = std::complex< real >( gsl_out->data[ 2*i ], gsl_out->data[ 2*i + 1 ] );
	}
	
	return out;
}

template< typename T >
const gsl::matrix< T > operator*(const gsl::matrix< T >& left, const typename gsl::matrix< T >::value_type& x){
	return left % x;
}

template< typename T >
const gsl::matrix< T >  operator*(const typename gsl::matrix< T >::value_type& x, const gsl::matrix< T >& right){
	return x % right;
}

template< typename T >
const gsl::vector< T > operator*(const gsl::matrix< T >& left, const gsl::vector< T >& v) throw ( gsl::matrix_size_mismatch ){
	if ( v.is_row_vector() || ( v.is_col_vector() && left.cols() != v.size() ) )
		throw gsl::matrix_size_mismatch();
		
	gsl::vector< T > out( left.rows() );
	
	gsl_blas_dgemv( CblasNoTrans, 1.0, left.as_gsl_matrix(), v.as_gsl_vector(), 0.0, out.as_gsl_vector() );
	
	return out;
}

template< typename T >
INLINE bool operator==( const gsl::matrix< T >& left, const typename gsl::matrix< T >::value_type& x )
{	return std::find_if( left.begin(), left.end(), std::bind2nd( std::not_equal_to< T >(), x ) ) == left.end();	}

template< typename T >
INLINE bool operator==( const typename gsl::matrix< T >::value_type& x, const gsl::matrix< T >& right )
{	return std::find_if( right.begin(), right.end(), std::bind1st( std::not_equal_to< T >(), x ) ) == right.end();	}

template< typename T >
INLINE bool operator!=( const gsl::matrix< T >& left, const typename gsl::matrix< T >::value_type& x )
{	return ! ( left == x );	}

template< typename T >
INLINE bool operator!=( const typename gsl::matrix< T >::value_type& x, const gsl::matrix< T >& right )
{	return ! ( x == right );	}

template< typename T >
INLINE bool operator<( const gsl::matrix< T >& left, const typename gsl::matrix< T >::value_type& x )
{	return std::find_if( left.begin(), left.end(), std::bind2nd(std::greater_equal< T >(), x ) ) == left.end();		}

template< typename T >
INLINE bool operator<( const typename gsl::matrix< T >::value_type& x, const gsl::matrix< T >& right )
{	return std::find_if( right.begin(), right.end(), std::bind1st(std::greater_equal< T >(), x ) ) == right.end();	}

template< typename T >
INLINE bool operator>( const gsl::matrix< T >& left, const typename gsl::matrix< T >::value_type& x )
{	return std::find_if( left.begin(), left.end(), std::bind2nd(std::less_equal< T >(), x ) ) == left.end();		}

template< typename T >
INLINE bool operator>( const typename gsl::matrix< T >::value_type& x, const gsl::matrix< T >& right )
{	return std::find_if( right.begin(), right.end(), std::bind1st(std::less_equal< T >(), x ) ) == right.end();		}
	
template< typename T >
INLINE bool operator<=( const gsl::matrix< T >& left, const typename gsl::matrix< T >::value_type& x )
{	return std::find_if( left.begin(), left.end(), std::bind2nd(std::greater< T >(), x ) ) == left.end();		}

template< typename T >
INLINE bool operator<=( const typename gsl::matrix< T >::value_type& x, const gsl::matrix< T >& right )
{	return std::find_if( right.begin(), right.end(), std::bind1st(std::greater< T >(), x ) ) == right.end();		}

template< typename T >
INLINE bool operator>=( const gsl::matrix< T >& left, const typename gsl::matrix< T >::value_type& x )
{	return std::find_if( left.begin(), left.end(), std::bind2nd(std::less< T >(), x ) ) == left.end();		}

template< typename T >
INLINE bool operator>=( const typename gsl::matrix< T >::value_type& x, const gsl::matrix< T >& right )
{	return std::find_if( right.begin(), right.end(), std::bind1st(std::less< T >(), x ) ) == right.end();		}

template< typename T >
std::ostream &operator<<(std::ostream& os, const gsl::matrix< T >& right){
	os << "(\n";

    for ( typename gsl::matrix< T >::size_type i = 0; i < right.rows(); ++i ){
        for ( typename gsl::matrix< T >::size_type j = 0; j < right.cols(); ++j )
            os << std::setw( 14 ) << std::setprecision(6) << std::scientific << 
				right[ typename gsl::matrix< T >::element_type( i, j ) ] << " ";
		
        os << "\n";
    }

    os << ")";
    return os;
}