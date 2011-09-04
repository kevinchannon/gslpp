#include "matrix.h"

#include <iomanip>
#include <algorithm>

#include <gsl/gsl_blas.h>

////////////////////////////////////////////////////////////

BEGIN_GSL_NAMESPACE

////////////////////////////////////////////////////////////

bool realMatrix::operator==( const realMatrix& right ) const
{
	if ( this->isNull() )
		return right.isNull() ? true : false;
	
	if ( this->rows() != right.rows() )
		return false;
	
	if ( this->cols() != right.cols() )
		return false;
		
	for ( const_iterator it = this->cbegin(), it_r = right.cbegin(); it != this->cend(); ++it, ++it_r )
		if ( *it != *it_r )	return false;
		
	return true;
}

////////////////////////////////////////////////////////////

void realMatrix::swap( realMatrix& m )
{
	std::swap( M_pGSLData, m.M_pGSLData );
	std::swap( M_pStart, m.M_pStart );
	std::swap( M_pFinish, m.M_pFinish );
	std::swap( M_uRows, m.M_uRows );
	std::swap( M_uCols, m.M_uCols );
}

////////////////////////////////////////////////////////////

const realMatrix &realMatrix::operator=(const realMatrix& right) throw ( std::bad_alloc )
{
	if ( this != &right ){
		realMatrix temp( right );
		this->swap( temp );
	}
	
	return *this;
}

////////////////////////////////////////////////////////////

const realMatrix &realMatrix::operator+=(const realMatrix::value_type x)
{
    gsl_matrix_add_constant( this->ptr(), x );
    return *this;
}

////////////////////////////////////////////////////////////

const realMatrix &realMatrix::operator+=(const realMatrix &m ) throw ( matrix_size_mismatch )
{
    if ( M_dimensions_are_equal( m ) == false )
        throw matrix_size_mismatch();

    std::transform( begin(), end(), m.cbegin(), begin(), std::plus< value_type >() );

    return *this;
}

////////////////////////////////////////////////////////////

const realMatrix &realMatrix::operator-=(const realMatrix::value_type x )
{
    gsl_matrix_add_constant( ptr(), -x );
    return *this;
}

////////////////////////////////////////////////////////////

const realMatrix &realMatrix::operator-=(const realMatrix &m) throw ( matrix_size_mismatch )
{
    if ( M_dimensions_are_equal( m ) == false )
        throw matrix_size_mismatch();

    std::transform( begin(), end(), m.cbegin(), begin(), std::minus< value_type >() );

    return *this;
}

////////////////////////////////////////////////////////////

const realMatrix &realMatrix::operator*=(const realMatrix::value_type x)
{
    gsl_matrix_scale( this->ptr(), x );
    return *this;
}

////////////////////////////////////////////////////////////

const realMatrix &realMatrix::operator*=(const realMatrix &m ) throw ( matrix_size_mismatch )
{
    if ( M_dimensions_are_equal( m ) == false )
        throw matrix_size_mismatch();

    std::transform( begin(), end(), m.cbegin(), begin(), std::multiplies< value_type >() );

    return *this;
}

////////////////////////////////////////////////////////////

const realMatrix &realMatrix::operator/=(const realMatrix::value_type x)
{
	gsl_matrix_scale( this->ptr(), 1/x );
	
    return *this;
}

////////////////////////////////////////////////////////////

const realMatrix &realMatrix::operator/=(const realMatrix &m ) throw ( matrix_size_mismatch )
{
    if ( M_dimensions_are_equal( m ) == false )
        throw matrix_size_mismatch();
		
	const_iterator it_m = m.cbegin();
    for ( iterator it = begin(); it != end(); ++it, ++it_m )
		*it /= *it_m;

    return *this;
}

////////////////////////////////////////////////////////////

gsl::realVector realMatrix::row( realMatrix::size_type i ) const
	throw ( matrix_uninitialised, std::out_of_range, std::bad_alloc )
{
    if ( isNull() )
        throw matrix_uninitialised();

    if ( i >= rows() )
        throw std::out_of_range( "matrix element out-of-range" );

    gsl::realVector out( cols() );
    gsl_matrix_get_row(out.ptr(), const_ptr(), i );

	out.setRowVector();
    return out;
}

////////////////////////////////////////////////////////////

gsl::realVector realMatrix::col(realMatrix::size_type i ) const
	throw ( matrix_uninitialised, std::out_of_range, std::bad_alloc )
{
    if ( isNull() )
        throw matrix_uninitialised();

    if ( i >= cols() )
        throw std::out_of_range( "matrix element out-of-range" );

    gsl::realVector out( rows() );
    gsl_matrix_get_col(out.ptr(), const_ptr(), i );

    out.setColVector();
    return out;
}

////////////////////////////////////////////////////////////

gsl::realVector realMatrix::diagonal( int k ) const
	throw ( matrix_uninitialised, std::out_of_range, std::bad_alloc )
{
    if ( isNull() )
        throw matrix_uninitialised();

    if ( k >= static_cast< int >( cols() ) || -k >= static_cast< int >( rows() ) )
        throw std::out_of_range( "matrix element out-of-range" );

    size_type size = k < 0 ? std::min( cols(), rows() + k ) : std::min( rows(), cols() - k );
    gsl::realVector out( size );

    gsl::realVector::iterator it_v = out.begin();
    const_iterator it = cbegin() + ( k < 0 ? -k*cols() : k );
    size_type step = cols() + 1;

    for ( size_type i = 0; i < size; ++i, it += step )  *it_v++ = *it;

    return out;
}

////////////////////////////////////////////////////////////

void realMatrix::setRow( realMatrix::size_type i, const gsl::realVector& v ) throw ( matrix_uninitialised, std::out_of_range)
{
    if ( isNull() )
        throw matrix_uninitialised();

    if ( i >= rows() )
        throw std::out_of_range( "matrix element out-of-range" );

    gsl_matrix_set_row( ptr(), i, v.const_ptr() );
}

////////////////////////////////////////////////////////////

void realMatrix::setCol(realMatrix::size_type i, const gsl::realVector& v ) throw ( matrix_uninitialised, std::out_of_range)
{
    if ( isNull() )
        throw matrix_uninitialised();

    if ( i >= cols() )
        throw std::out_of_range( "matrix element out-of-range" );

    gsl_matrix_set_col( ptr(), i, v.const_ptr() );
}

////////////////////////////////////////////////////////////

gsl::realMatrix realMatrix::transpose() const throw ( matrix_uninitialised )
{
	if ( isNull() )
		throw matrix_uninitialised();
		
	realMatrix out( this->cols(), this->rows() );
	
	if ( out.isSquare() ){
		out = *this;
		gsl_matrix_transpose( out.ptr() );
	}
	else
		gsl_matrix_transpose_memcpy( out.ptr(), this->const_ptr() );
	
	return out;
}

////////////////////////////////////////////////////////////

void realMatrix::swapCols( size_type c1, size_type c2 ) throw (std::out_of_range )
{
	if ( c1 >= this->cols() || c2 >= this->cols() )
		throw std::out_of_range("matrix column out of range");
		
	if ( c1 == c2 )
		return;
		
	gsl_matrix_swap_columns( this->ptr(), c1, c2 );
}

////////////////////////////////////////////////////////////

void realMatrix::swapRows( size_type r1, size_type r2 ) throw (std::out_of_range )
{
	if ( r1 >= this->rows() || r2 >= this->rows() )
		throw std::out_of_range("matrix row out of range");
		
	if ( r1 == r2 )
		return;
		
	gsl_matrix_swap_rows( this->ptr(), r1, r2 );
}

////////////////////////////////////////////////////////////

void realMatrix::swapRowCol( size_type r, size_type c ) throw (std::out_of_range, matrix_uninitialised )
{
	if ( r >= this->rows() || c >= this->cols() )
		throw std::out_of_range("matrix row out of range");
	
	if ( this->isNull() )
		throw matrix_uninitialised();
		
	gsl_matrix_swap_rowcol( this->ptr(), r, c );
}

////////////////////////////////////////////////////////////

realMatrix::value_type realMatrix::min() const throw ( matrix_uninitialised )
{
	if ( isNull() )
		throw matrix_uninitialised();
		
	realMatrix::const_iterator it = this->cbegin();
	
	// Get to the first non-empty value
	real rMin = realEmpty;
	while ( is_empty( rMin ) )	rMin = *it++;
	
	while ( it != this->cend() ){
		real rCurrent = *it++;
		if ( ! is_empty( rCurrent ) )
			rMin = rCurrent < rMin ? rCurrent : rMin;
	}
	
	return rMin;
}

////////////////////////////////////////////////////////////

realMatrix::value_type realMatrix::max() const throw ( matrix_uninitialised )
{
	if ( isNull() )
		throw matrix_uninitialised();
		
	realMatrix::const_iterator it = this->cbegin();
	
	// Get to the first non-empty value
	real rMax = realEmpty;
	while ( is_empty( rMax ) )	rMax = *it++;
	
	while ( it != this->cend() ){
		real rCurrent = *it++;
		if ( ! is_empty( rCurrent ) )
			rMax = rCurrent > rMax ? rCurrent : rMax;
	}
	
	return rMax;
}

////////////////////////////////////////////////////////////

std::pair< realMatrix::value_type, realMatrix::value_type > realMatrix::minMax() const  throw ( matrix_uninitialised )
{
	return std::make_pair( this->min(), this->max() );
}

////////////////////////////////////////////////////////////

realMatrix::element_type realMatrix::min_element() const throw ( matrix_uninitialised )
{
	if ( isNull() )
		throw matrix_uninitialised();
		
	realMatrix::const_iterator it = this->cbegin();
	
	// Get to the first non-empty value
	real rMin = realEmpty;
	size_type i = 0;
	while ( is_empty( rMin ) ){
		rMin = *it++;
		++i;
	}
	
	// Go through the rest of the values to find the min
	size_type iMinIndex = i;
	while ( it != this->cend() ){
		real rCurrent = *it++;
		if ( ! is_empty( rCurrent ) ){
			if ( rCurrent < rMin ){
				rMin = rCurrent;
				iMinIndex = i;
			}
		}
		++i;
	}
	
	return element_type( iMinIndex / this->cols(), iMinIndex % this->cols() );
}

////////////////////////////////////////////////////////////

realMatrix::element_type realMatrix::max_element() const throw ( matrix_uninitialised )
{
	if ( isNull() )
		throw matrix_uninitialised();
		
	realMatrix::const_iterator it = this->cbegin();
	
	// Get to the first non-empty value
	real rMax = realEmpty;
	size_type i = 0;
	while ( is_empty( rMax ) ){
		rMax = *it++;
		++i;
	}
	
	// Go through the rest of the values to find the min
	size_type iMaxIndex = i;
	while ( it != this->cend() ){
		real rCurrent = *it++;
		if ( ! is_empty( rCurrent ) ){
			if ( rCurrent > rMax ){
				rMax = rCurrent;
				iMaxIndex = i;
			}
		}
		++i;
	}
	
	return element_type( iMaxIndex / this->cols(), iMaxIndex % this->cols() );
}

////////////////////////////////////////////////////////////

std::pair< realMatrix::element_type, realMatrix::element_type > realMatrix::minMax_element() const throw ( matrix_uninitialised )
{
	return std::make_pair( this->min_element(), this->max_element() );
}

////////////////////////////////////////////////////////////

realMatrix::const_reference realMatrix::at(const realMatrix::size_type& r, const realMatrix::size_type& c) const
{
	if ( this->isNull() )
		throw matrix_uninitialised();
	
	if ( r >= this->rows() || c >= this->cols() )
		throw std::out_of_range("matrix index out of range");
		
	return this->operator[]( element_type(r,c) );
}

////////////////////////////////////////////////////////////
	
realMatrix::reference realMatrix::at(const realMatrix::size_type& r, const realMatrix::size_type& c)
{
	if ( this->isNull() )
		throw matrix_uninitialised();
	
	if ( r >= this->rows() || c >= this->cols() )
		throw std::out_of_range("matrix index out of range");
		
	return this->operator[]( element_type(r,c) );
}

////////////////////////////////////////////////////////////

END_GSL_NAMESPACE

////////////////////////////////////////////////////////////

bool operator==( const gsl::realMatrix& left, const gsl::realMatrix::value_type& x )
{
	if ( left.isNull() )
		return false;
	
	gsl::realMatrix::const_iterator it = left.cbegin();
	while ( it != left.cend() ){
		real rValue = *it++;
		if ( is_empty( rValue ) || rValue != x )
			return false;
	}
	
	return true;
}

////////////////////////////////////////////////////////////

bool operator==( const gsl::realMatrix::value_type& x, const gsl::realMatrix& right )
{
	return right == x;
}

////////////////////////////////////////////////////////////

bool operator!=( const gsl::realMatrix& left, const gsl::realMatrix::value_type& x )
{
	return !( left == x );
}

////////////////////////////////////////////////////////////

bool operator!=( const gsl::realMatrix::value_type& x, const gsl::realMatrix& right )
{
	return !( right == x );
}

////////////////////////////////////////////////////////////

bool operator<( const gsl::realMatrix& left, const gsl::realMatrix::value_type& x )
{
	
	if ( left.isNull() )
		return false;
	
	gsl::realMatrix::const_iterator it = left.cbegin();
	while ( it != left.cend() ){
		real rValue = *it++;
		if ( is_empty( rValue ) || rValue >= x )
			return false;
	}
	
	return true;
}

////////////////////////////////////////////////////////////

bool operator<( const gsl::realMatrix::value_type& x, const gsl::realMatrix& right )
{
	return right > x;
}

////////////////////////////////////////////////////////////

bool operator>( const gsl::realMatrix& left, const gsl::realMatrix::value_type& x )
{
	if ( left.isNull() )
		return false;
	
	gsl::realMatrix::const_iterator it = left.cbegin();
	while ( it != left.cend() ){
		real rValue = *it++;
		if ( is_empty( rValue ) || rValue <= x )
			return false;
	}
	
	return true;
}

////////////////////////////////////////////////////////////

bool operator>( const gsl::realMatrix::value_type& x, const gsl::realMatrix& right )
{
	return right < x;
}

////////////////////////////////////////////////////////////

bool operator<=( const gsl::realMatrix& left, const gsl::realMatrix::value_type& x )
{
	
	if ( left.isNull() )
		return false;
	
	gsl::realMatrix::const_iterator it = left.cbegin();
	while ( it != left.cend() ){
		real rValue = *it++;
		if ( is_empty( rValue ) || rValue > x )
			return false;
	}
	
	return true;
}

////////////////////////////////////////////////////////////

bool operator<=( const gsl::realMatrix::value_type& x, const gsl::realMatrix& right )
{
	return !( right > x );
}

////////////////////////////////////////////////////////////

bool operator>=( const gsl::realMatrix& left, const gsl::realMatrix::value_type& x )
{
	if ( left.isNull() )
		return false;
	
	gsl::realMatrix::const_iterator it = left.cbegin();
	while ( it != left.cend() ){
		real rValue = *it++;
		if ( is_empty( rValue ) || rValue < x )
			return false;
	}
	
	return true;
}

////////////////////////////////////////////////////////////

bool operator>=( const gsl::realMatrix::value_type& x, const gsl::realMatrix& right )
{
	return !( right < x );
}

////////////////////////////////////////////////////////////

std::ostream &operator<<( std::ostream &os, const gsl::realMatrix &right )
{
	
    os << "(\n";

    for ( gsl::realMatrix::size_type i = 0; i < right.rows(); ++i ){
        for ( gsl::realMatrix::size_type j = 0; j < right.cols(); ++j )
            os << std::setw( 14 ) << std::setprecision(6) << std::scientific << right[ gsl::realMatrix::element_type( i, j ) ] << " ";
        os << "\n";
    }

    os << ")";
    return os;
}

////////////////////////////////////////////////////////////

const gsl::realMatrix operator+(const gsl::realMatrix& left, const gsl::realMatrix &right)
{
    gsl::realMatrix out( left );
    out += right;
    return out;
}

////////////////////////////////////////////////////////////

const gsl::realMatrix operator+(const gsl::realMatrix& left, const gsl::realMatrix::value_type& x)
{
	gsl::realMatrix out( left );
    out += x;
    return out;	
}

////////////////////////////////////////////////////////////

const gsl::realMatrix operator+(const gsl::realMatrix::value_type& x, const gsl::realMatrix& right)
{
	gsl::realMatrix out( right );
    out += x;
    return out;
}

////////////////////////////////////////////////////////////

const gsl::realMatrix operator-(const gsl::realMatrix& left, const gsl::realMatrix &right)
{
    gsl::realMatrix out( left );
    out -= right;
    return out;
}

////////////////////////////////////////////////////////////

const gsl::realMatrix operator-(const gsl::realMatrix& left, const gsl::realMatrix::value_type& x)
{
	gsl::realMatrix out( left );
    out -= x;
    return out;	
}

////////////////////////////////////////////////////////////

const gsl::realMatrix operator-(const gsl::realMatrix::value_type& x, const gsl::realMatrix& right)
{
	gsl::realMatrix out( right );
    gsl::realMatrix::iterator it = out.begin();
	
	while ( it != out.end() )	*it++ = x - *it ;
	
    return out;
}

////////////////////////////////////////////////////////////

// Element-wise multiply
const gsl::realMatrix operator%(const gsl::realMatrix& left, const gsl::realMatrix &right)
{
    gsl::realMatrix out( left );
    out *= right;
    return out;
}

////////////////////////////////////////////////////////////

const gsl::realMatrix operator%(const gsl::realMatrix& left, const gsl::realMatrix::value_type& x)
{
	gsl::realMatrix out( left );
    out *= x;
    return out;	
}

////////////////////////////////////////////////////////////

const gsl::realMatrix operator%(const gsl::realMatrix::value_type& x, const gsl::realMatrix& right)
{
	gsl::realMatrix out( right );
    out *= x;
    return out;
}

////////////////////////////////////////////////////////////

// Element-wise divide
const gsl::realMatrix operator/(const gsl::realMatrix& left, const gsl::realMatrix &right)
{
    gsl::realMatrix out( left );
    out /= right;
    return out;
}

////////////////////////////////////////////////////////////

const gsl::realMatrix operator/(const gsl::realMatrix& left, const gsl::realMatrix::value_type& x)
{
	gsl::realMatrix out( left );
    out /= x;
    return out;	
}

////////////////////////////////////////////////////////////

const gsl::realMatrix operator/(const gsl::realMatrix::value_type& x, const gsl::realMatrix& right)
{
	gsl::realMatrix out( right );
    gsl::realMatrix::iterator it = out.begin();
	gsl::realMatrix::const_iterator it_r = right.cbegin();
	
	while ( it != out.end() ){
		*it = x / *it_r;
		++it; ++it_r;
	}
	
    return out;
}

////////////////////////////////////////////////////////////

const gsl::realMatrix operator*(const gsl::realMatrix& left, const gsl::realMatrix& right ) throw ( gsl::matrix_size_mismatch )
{
	if ( left.isNull() || right.isNull() )
		throw gsl::matrix_uninitialised();
		
	if ( left.cols() != right.rows() )
		throw gsl::matrix_size_mismatch();
		
	gsl::realMatrix out( left.rows(), right.cols() );
	
	gsl_blas_dgemm( CblasNoTrans, CblasNoTrans, 1.0, left.const_ptr(), right.const_ptr(), 0.0, out.ptr() );
					
	return out;
}

////////////////////////////////////////////////////////////

const gsl::realMatrix operator*(const gsl::realMatrix& left, const gsl::realMatrix::value_type& x)
{
	return left % x;
}

////////////////////////////////////////////////////////////

const gsl::realMatrix operator*(const gsl::realMatrix::value_type& x, const gsl::realMatrix& right)
{
	return x % right;
}

////////////////////////////////////////////////////////////

const gsl::realVector operator*(const gsl::realMatrix& left, const gsl::realVector& v ) throw ( gsl::matrix_size_mismatch )
{
	if ( v.isRowVector() || ( v.isColVector() && left.cols() != v.size() ) )
		throw gsl::matrix_size_mismatch();
		
	gsl::realVector out( left.rows() );
	
	// TODO: Stop segfault
	gsl_blas_dgemv( CblasNoTrans, 1.0, left.const_ptr(), v.const_ptr(), 0.0, out.ptr() );
	
	return out;
}

////////////////////////////////////////////////////////////