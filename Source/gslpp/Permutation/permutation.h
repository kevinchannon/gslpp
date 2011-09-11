#pragma once

#include <stdexcept>
#include <cstddef>

#include "../Common/gslstructbase.h"
#include "../Common/number.h"
#include "../Common/macros.h"
#include "../Common/exceptions.h"

#include <gsl/gsl_permutation.h>

BEGIN_GSL_NAMESPACE

class permutation_size_mismatch : public std::runtime_error{
	public:
	permutation_size_mismatch() : std::runtime_error("Permutations do not have equal size"){}
};

class permutation_uninitialised : public std::runtime_error{
	public:
	permutation_uninitialised() : std::runtime_error("Permutation illegally used uninitialised"){}
};

class permutation : public gsl_base_ptr< gsl_permutation >
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

	permutation(){}
	permutation( size_type n, permutation::initial_state state = uninitialised ) throw ( std::bad_alloc ) :
		gsl_base_ptr(state == permutation::uninitialised ? gsl_permutation_alloc(n) : gsl_permutation_calloc(n))
	{
		if ( ptr() == NULL )    throw std::bad_alloc();
	}

	permutation( const permutation& original ) throw( std::bad_alloc );

	~permutation();

	/// Assignment operator
	gsl::permutation &operator=( const gsl::permutation &right ) throw( std::bad_alloc );

	/// Equality operators
	///
	/// Will not throw
	bool operator==( const gsl::permutation& right ) const;
	bool operator!=( const gsl::permutation& right ) const;

	/// Access elements of the permutation without range-checking
	///
	/// Will not throw, no range checking so may display undefined behaviour if index is out-of-range
	INLINE reference operator[](size_type index){  return const_cast< reference >( this->ptr()->data[ index ] );   }
	INLINE const_reference operator[](size_type index) const{  return const_ptr()->data[ index ];   }

	/// Access elements of the permutation without range checking, but with cyclic boundary conditions
	///
	/// Will not throw
	INLINE reference operator()(int index)
	{  
		if ( this->isNull() || this->size() == 0 )
			throw permutation_uninitialised();
			
		return const_ptr()->data[ ( index % size() + size()) % size() ];
	}
	INLINE const_reference operator()(int index) const throw ( permutation_uninitialised )
	{  
		if ( this->isNull() || this->size() == 0 )
			throw permutation_uninitialised();
			
		return const_ptr()->data[ ( index % size() + size()) % size() ];
	}

	/// Access elements of the permutation with full range checking
	reference at( size_type index ) throw ( std::out_of_range );
	const_reference at( size_type index ) const throw ( std::out_of_range );

	/// Get the size of the permutation
	///
	/// Will not throw, returns 0 if uninitialised
	INLINE size_type size() const{    return ( hasValue() ? const_ptr()->size : 0 ); }

	/// Resize the permutation
	void resize( size_type n ) throw ( std::bad_alloc );

	/// Get a pointer to the first element of the data struct
	///
	/// Will return NULL if the permutation is uninitialised, will not throw
	INLINE iterator begin(){ return const_cast< iterator >( cbegin() ); }

	/// Get a pointer to one-past-the-end of the data struct
	///
	/// Will return NULL if the permutation is uninitialised, will not throw
	INLINE iterator end(){ return const_cast< iterator>( cend() ); }

	/// Get a pointer to the first element of the data struct
	///
	/// Will return NULL if the permutation is uninitialised, will not throw
	INLINE const_iterator cbegin() const { return ( hasValue() ? const_ptr()->data : NULL ); }

	/// Get a pointer to one-past-the-end of the data struct
	///
	/// Will return NULL if the permutation is uninitialised, will not throw
	INLINE const_iterator cend() const { return ( hasValue() ? const_ptr()->data + size() : NULL ); }

	/// Swap this permutation for another one
	///
	/// Will not throw
	void swap( permutation& other );

	/// Exchange two elements in the permutation
	void swapElements( size_type i, size_type j) throw( std::out_of_range, permutation_uninitialised );

	/// Check that the permutation is valid (has no repeated elements)
	///
	/// Will return false if the permutation is uninitialised, will not throw
	bool isValid() const;

	/// Reverse the elements of the permutation
	///
	/// will not throw
	void reverse();

	/// Compute the inverse permutation
	permutation inverse() const throw ( permutation_uninitialised );

	/// Get the next permutation in lexicographic order
	///
	/// Will return true if the permutation can be advanced, false otherwise
	bool next() throw ( permutation_uninitialised );

	/// Get the previous permutation in lexicographic order
	///
	/// Will return true if the permutation can be advanced, false otherwise
	bool prev() throw ( permutation_uninitialised );

	/// Free the memory associated with the permutaion
	///
	/// Will not throw, does nothing if it's not initialised
	void free();

private:

	void pv_realloc( size_type n, permutation::initial_state state = uninitialised ) throw ( std::bad_alloc );
};

const permutation operator*( const permutation& left, const permutation& right ) throw( permutation_size_mismatch );

END_GSL_NAMESPACE
