#pragma once

#include <iostream>
#include <stdexcept>
#include <iterator>
#include <vector>

#include <gsl/gsl_vector.h>

#include "../Common/macros.h"
#include "../Common/gslstructbase.h"
#include "../Common/number.h"
#include "../Common/exceptions.h"

BEGIN_GSL_NAMESPACE

class vector_uninitialised : public std::runtime_error
{
    public:
    vector_uninitialised() : std::runtime_error("vector used before initialisation"){}
};

class vector_size_mismatch : public std::runtime_error
{
    public:
    vector_size_mismatch() : std::runtime_error("vector sizes are unequal"){}
};

class realVector : public gsl_base_ptr< gsl_vector >
{
public :

// TODO: understand this and make it work
//    struct _vector_iterator : public std::iterator_traits< real* >{};

    typedef real*                       iterator;
    typedef const real*                 const_iterator;
    typedef real&                       reference;
    typedef const real&                 const_reference;
    typedef real*                       pointer;
    typedef const real*                 const_pointer;
    typedef real                        value_type;
    typedef size_t                      size_type;
    typedef ptrdiff_t                   difference_type;

    realVector();
    realVector( size_type length, bool isColVector = true ) throw ( std::bad_alloc );
    realVector( size_type length, real defaultElementValue, bool isColVector = true ) throw ( std::bad_alloc );
    realVector( size_type length, real* array, bool isColVector = true  ) throw ( std::bad_alloc );
    realVector( const gsl::realVector& original ) throw ( std::bad_alloc );
    realVector( gsl_vector* original, bool isColVector = true ) throw ( std::bad_alloc );
    realVector( const std::vector< real >& original, bool isColVector = true ) throw ( std::bad_alloc );
    ~realVector();

    /// Over-loaded operators
    gsl::realVector &operator=(const gsl::realVector &right);
    gsl::realVector &operator=( const value_type right);
    gsl::realVector &operator+=(const gsl::realVector &right) throw ( vector_uninitialised, vector_size_mismatch );
    gsl::realVector &operator+=( const value_type right) throw ( vector_uninitialised );
    gsl::realVector &operator-=(const gsl::realVector &right) throw ( vector_uninitialised, vector_size_mismatch );
    gsl::realVector &operator-=( const value_type right) throw ( vector_uninitialised );
    gsl::realVector &operator*=(const gsl::realVector &right) throw ( vector_uninitialised, vector_size_mismatch );
    gsl::realVector &operator*=( const value_type right) throw ( vector_uninitialised );
    gsl::realVector &operator/=(const gsl::realVector &right) throw ( vector_uninitialised, vector_size_mismatch );
    gsl::realVector &operator/=( const value_type right) throw ( vector_uninitialised );

    /// Accessor with cyclic boundary
    reference operator()(int index) throw ( std::bad_alloc );
    const_reference operator()(int index) const;

    /// GSL-style Functions
    __INLINE value_type max() const{ return gsl_vector_max( this->const_ptr() );    }
    __INLINE value_type min() const{ return gsl_vector_min( this->const_ptr() );    }
    std::pair< real, real > minmax() const;
    __INLINE size_type max_element() const{ return gsl_vector_max_index( this->const_ptr() );  }
    __INLINE size_type min_element() const{ return gsl_vector_min_index( this->const_ptr() );  }
    std::pair< size_type, size_type > minmax_element() const;

    void swapElements( size_type index1, size_type index2);

    __INLINE difference_type stride() const { return static_cast< difference_type >( this->const_ptr()->stride );   }
//    void set_stride( difference_type s );

    void zero();
    void basis(unsigned index);
    void free();

    /// STL-style functions

    // Iterators
    __INLINE iterator begin(){  return const_cast< iterator >( cbegin() );  }
    __INLINE iterator end(){ return const_cast< iterator >( cend() ); }
    __INLINE iterator rbegin(){  return const_cast< iterator >( crbegin() );  }
    __INLINE iterator rend(){ return const_cast< iterator >( crend() ); }
    __INLINE const_iterator cbegin() const {  return static_cast< const_iterator >( M_pStart );  }
    __INLINE const_iterator cend() const {  return static_cast< const_iterator >( M_pFinish );  }
    __INLINE const_iterator crbegin() const {  return static_cast< const_iterator >( M_pFinish - 1 );  }
    __INLINE const_iterator crend() const { return static_cast< const_iterator >( M_pStart - 1 );  }

    // Capacity
    __INLINE size_type size() const { return M_pFinish - M_pStart; }
    void resize(const size_type length);
    void resize(const size_type length, const real value);
    __INLINE bool empty() const{ return M_pFinish == M_pStart; }
    __INLINE size_type capacity() const{    return M_pEnd_of_storage - M_pStart;  }
    void reserve( size_type ) throw (std::bad_alloc );

    // Element access
    __INLINE reference operator[](size_type index){  return *( M_pStart + index );   }
    __INLINE const_reference operator[](size_type index) const{  return *( M_pStart + index );  }
    const_reference at( size_type index) const throw ( std::out_of_range, vector_uninitialised );
    reference at( size_type index) throw ( std::out_of_range, vector_uninitialised );
    __INLINE reference front(){   return *begin();  }
    __INLINE reference back(){    return *( end() - 1);    }
    __INLINE const_reference front() const {   return *cbegin();  }
    __INLINE const_reference back() const {    return *( cend() - 1);    }

    // Modifiers
    void assign( size_type n, const_reference value );
    void assign( const_iterator start, const_iterator finish );
    void swap(gsl::realVector& otherVector);
    __INLINE void clear(){    M_pFinish = M_pStart;    }
    void push_back( value_type value );
    value_type pop_back();
    void erase( size_type n );
    iterator insert ( iterator position, value_type x );
    void insert ( iterator position, size_type n, value_type x );
    void insert ( iterator position, iterator first, iterator last );

    /// Misc convenience functions
    __INLINE bool isRowVector() const{   return M_bIsRowVector;  }
    __INLINE void setRowVector(bool bIsRowVec = true ){         M_bIsRowVector = bIsRowVec; }
    __INLINE bool isColVector() const{   return !M_bIsRowVector; }
    __INLINE void setColVector(bool bIsColVec = true ){         M_bIsRowVector = !bIsColVec; }

    iterator toArray() const throw ( std::bad_alloc );

    void squeeze();
    void reset();

private :
    pointer M_pStart;
    pointer M_pFinish;
    pointer M_pEnd_of_storage;

    bool M_bIsRowVector;

    void M_guaranteed_reserve( size_type n );
    void M_realloc( size_type length ) throw ( std::bad_alloc) ;
    __INLINE void M_range_check( size_type n ) const throw ( std::out_of_range )
    {
        if ( n >= size() )
            throw std::out_of_range( "vector index out-of-range" );
    }
};

 __INLINE void swap( gsl::realVector& a, gsl::realVector& b)
 {
	  a.swap( b );
 }

END_GSL_NAMESPACE

std::ostream &operator<<(std::ostream &os, const gsl::realVector &right);

bool operator==(const gsl::realVector& left, const gsl::realVector &right);
__INLINE bool operator!=(const gsl::realVector& left, const gsl::realVector &right){    return !(left == right);   }

const gsl::realVector operator+(const gsl::realVector& left, const gsl::realVector &right);
const gsl::realVector operator-(const gsl::realVector& left, const gsl::realVector &right);

// Element-wise multiply
const gsl::realVector operator%(const gsl::realVector& left, const gsl::realVector &right);

// Scalar product
real operator*(const gsl::realVector& left, const gsl::realVector &right);

// Vector product
//const gsl::matrix operator^(const gsl::vector& left, const gsl::vector &right) const;
