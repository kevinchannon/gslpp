#include "combination.h"

namespace gsl{

////////////////////////////////////////////////////////////

combination::combination( const combination& original ) throw( std::bad_alloc ) :
	gsl_base(gsl_combination_alloc( original.n(), original.k() )), M_bIsInitialised( false ), 
	M_pStart(NULL), M_pFinish(NULL)
{
	if ( isNull() )
		throw std::bad_alloc();
	
	gsl_combination_memcpy( this->ptr(), original.const_ptr() );
	M_bIsInitialised = true;
	M_pStart  = this->ptr()->data;
	M_pFinish = this->ptr()->data + this->ptr()->k;
}

////////////////////////////////////////////////////////////

combination::~combination()
{
}

////////////////////////////////////////////////////////////

void combination::swap( combination& other )
{
	if ( isNull() && other.isNull() )
        return;
		
	gsl_combination* temp = other.ptr();
	this->swap_ptr( temp );
	std::swap( this->M_bIsInitialised, other.M_bIsInitialised );
	std::swap( this->M_pStart, other.M_pStart );
	std::swap( this->M_pFinish, other.M_pFinish );
}

////////////////////////////////////////////////////////////

combination& combination::operator=( const gsl::combination &right ) throw( std::bad_alloc )
{
	if ( &right != this ){
		gsl::combination temp( right );
		this->swap( temp );
	}
	
	return *this;
}

////////////////////////////////////////////////////////////

bool combination::operator==( const gsl::combination& right ) const
{
	if ( this->isNull() && right.isNull() )
		return true;
	
	if ( this->isNull() || right.isNull() )
		return false;
		
	if ( this->k() != right.k() || this->n() != right.n() )
		return false;
		
	if ( this->M_bIsInitialised != right.M_bIsInitialised )
		return false;
		
	const_iterator it = this->cbegin();
	const_iterator it_r = right.cbegin();
	
	while ( it != this->cend() )
	{
		if ( *it++ != *it_r++ )
			return false;
	}
	
	return true;
}

////////////////////////////////////////////////////////////

combination::const_reference combination::at( size_type index ) const throw ( std::out_of_range )
{
	if ( index >= this->k() )
		throw std::out_of_range("combination index out of range");
	
	return this->operator[]( index );
}

////////////////////////////////////////////////////////////

void combination::redefine( size_type n, size_type k ) throw ( std::bad_alloc )
{
	combination temp( n, k, initialised );
	this->swap( temp );
}

////////////////////////////////////////////////////////////

bool combination::isValid()
{
	if ( this->isNull() )	return false;
		
	int iResult = gsl_combination_valid( this->ptr() );
	
	return (iResult == GSL_SUCCESS ? true : false);
}

////////////////////////////////////////////////////////////

bool combination::next() throw ( combination_uninitialised )
{
	if ( this->isNull() )
		throw combination_uninitialised();
	
	int iResult = gsl_combination_next (this->ptr());
	
	return ( iResult == GSL_SUCCESS ? true : false );
}

////////////////////////////////////////////////////////////

bool combination::prev() throw ( combination_uninitialised )
{
	if ( this->isNull() )
		throw combination_uninitialised();
	
	int iResult = gsl_combination_prev (this->ptr());
	
	return ( iResult == GSL_SUCCESS ? true : false );
}

////////////////////////////////////////////////////////////

real combination::count() const
{
	if ( this->isNull() || ! M_bIsInitialised || this->n() == 0 || this->k() == 0 )
		return 0;
		
	real result = realOne;
	real N = this->n();
	real K = this->k();
	
	for ( size_t i = 0; i < K; ++i )
		result *= static_cast< real >(N - i)/static_cast< real >(K - i);
		
	return result;
}

////////////////////////////////////////////////////////////

void combination::free()
{
	if ( this->hasValue() )
		gsl_combination_free( this->ptr() );
		
	M_pStart = NULL;
	M_pFinish = NULL;
	M_bIsInitialised = false;
}

////////////////////////////////////////////////////////////

}	// End of gsl namespace

////////////////////////////////////////////////////////////

std::ostream &operator<<( std::ostream &os, const gsl::combination &right )
{
	
    os << "{ ";

    for ( gsl::combination::const_iterator it = right.cbegin(); it != right.cend(); ++it )
		os << *it << " ";

    os << "}";
    return os;
}

////////////////////////////////////////////////////////////