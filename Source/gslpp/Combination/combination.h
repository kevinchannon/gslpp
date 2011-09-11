#pragma once

#include <iostream>
#include <stdexcept>
#include <cstddef>

#include "../Common/gslstructbase.h"
#include "../Common/number.h"
#include "../Common/macros.h"
#include "../Common/exceptions.h"

#include <gsl/gsl_combination.h>

BEGIN_GSL_NAMESPACE

class combination_size_mismatch : public std::runtime_error{
	public:
	combination_size_mismatch() : std::runtime_error("Combinations do not have equal size"){}
};

class combination_uninitialised : public std::runtime_error{
	public:
	combination_uninitialised() : std::runtime_error("Combination illegally used uninitialised"){}
};

class combination : public gsl_base_ptr< gsl_combination >
{
public:

	typedef size_t value_type;
	typedef size_t* iterator;
	typedef const size_t* const_iterator;
	typedef size_t& reference;
	typedef const size_t& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;


	enum initial_state{
		uninitialised = 0,
		initialised = 1
	};

	combination() : M_bIsInitialised(false), M_pStart(NULL), M_pFinish(NULL){}
	combination( size_type n, size_type k, initial_state state = initialised ) throw ( std::bad_alloc ) :
		gsl_base_ptr(state == combination::uninitialised ? gsl_combination_alloc(n,k) : gsl_combination_calloc(n,k)),
		M_bIsInitialised( false ), M_pStart(NULL), M_pFinish(NULL)
	{
		if ( ptr() == NULL )    throw std::bad_alloc();
		
		M_bIsInitialised = state == initialised ? true : false;
		M_pStart  = this->ptr()->data;
		M_pFinish = this->ptr()->data + this->ptr()->k;
	}

	combination( const combination& original ) throw( std::bad_alloc );

	~combination();
	
	/// Initialise or re-set the combination to the first in the range
	INLINE void set_first() throw ( combination_uninitialised )
	{
		if ( isNull() )	throw combination_uninitialised();
		
		gsl_combination_init_first( this->ptr() );
	}
	
	/// Initialise or re-set the combination to the first in the range
	INLINE void set_last() throw ( combination_uninitialised )
	{
		if ( isNull() )	throw combination_uninitialised();
		
		gsl_combination_init_last( this->ptr() );
	}

	/// Swap this combination for another one
	///
	/// Will not throw
	void swap( combination& other );

	/// Assignment operator
	combination& operator=( const gsl::combination &right ) throw( std::bad_alloc );

	/// Equality operators
	///
	/// Will not throw
	bool operator==( const gsl::combination& right ) const;
	INLINE bool operator!=( const gsl::combination& right ) const{	return !( *this == right );		}

	/// Access elements of the combination without range-checking
	///
	/// Will not throw, no range checking so may display undefined behaviour if index is out-of-range
	INLINE const_reference operator[](size_type index) const{  return *( this->cbegin() + index );   }

	/// Access elements of the combination without range checking, but with cyclic boundary conditions
	///
	/// will not throw
	INLINE const_reference operator()(int index)
	{	
		int K = static_cast< int >( this->k() );
		return *( this->begin() + ((index % K + K) % K) );
	}

	/// Access elements of the combination with full range checking
	const_reference at( size_type index ) const throw ( std::out_of_range );

	/// Get the number of elements in the complete set of the combination
	///
	/// Will not throw, returns 0 if uninitialised
	INLINE size_type n() const{    return ( hasValue() ? const_ptr()->n : 0 ); }

	/// Get the selection size of the combination
	///
	/// Will not throw, returns 0 if uninitialised
	INLINE size_type k() const{    return ( hasValue() ? const_ptr()->k : 0 ); }

	/// Redefine the set-size and selection-size the combination, initialises the combination to the
	/// lexographically first combination
	void redefine( size_type n, size_type k ) throw ( std::bad_alloc );

	/// Get a pointer to the first element of the data struct
	///
	/// Will return NULL if the combination is uninitialised, will not throw
	INLINE iterator begin(){ return const_cast< iterator >( cbegin() ); }

	/// Get a pointer to one-past-the-end of the data struct
	///
	/// Will return NULL if the combination is uninitialised, will not throw
	INLINE iterator end(){ return const_cast< iterator>( cend() ); }

	/// Get a pointer to the first element of the data struct
	///
	/// Will return NULL if the combination is uninitialised, will not throw
	INLINE const_iterator cbegin() const { return M_pStart; }

	/// Get a pointer to one-past-the-end of the data struct
	///
	/// Will return NULL if the combination is uninitialised, will not throw
	INLINE const_iterator cend() const { return M_pFinish; }

	/// Check that the combination is valid The k elements should lie in the range 0 to n-1,
	/// with each value occurring once at most and in increasing order
	///
	/// Will return false if the combination is uninitialised, will not throw
	bool isValid();

	/// Get the next combination in lexicographic order
	///
	/// Will return true if the combination can be advanced, false otherwise
	bool next() throw ( combination_uninitialised );

	/// Get the previous combination in lexicographic order
	///
	/// Will return true if the combination can be advanced, false otherwise
	bool prev() throw ( combination_uninitialised );
	
	/// Get the total number of combinations that can be generated
	///
	/// Will not throw, returns 0 if uninitialised
	real count() const;

	/// Free the memory associated with the permutaion
	///
	/// Will not throw, does nothing if it's not initialised
	void free();

private:
	
	bool M_bIsInitialised;
	iterator M_pStart;
	iterator M_pFinish;
};

END_GSL_NAMESPACE

std::ostream &operator<<(std::ostream &os, const gsl::combination &right);
