/*
    compare.h
    01/01/12
    Chris Lacher

    Defining and implementing the predicate classes
    LessThan<T> and GreaterThan<T>

    Copyright 2012, R.C. Lacher
*/

#ifndef _COMPARE_SPY_H
#define _COMPARE_SPY_H

namespace fsu
{

template < typename T >
class LessThanSpy;

template < typename T >
class GreaterThanSpy;

template < typename T >
class LessThanSpy
{
  public:
    LessThanSpy():count(0){}
    bool operator () (const T& t1, const T& t2)
    {
      ++count;
      return (t1 < t2);
    }

    void Reset(){count = 0;}
    size_t Count() const{return count;}

  private:
    int count;
} ;

template < typename T >
class GreaterThanSpy
{
  public:
    bool operator () (const T& t1, const T& t2) const
    {
      return (t2 < t1);
    }
} ;

// technicality needed for generic algorithms: because these predicate objects
// are stateless, they are all equal

template < typename T >
bool operator == ( const LessThanSpy<T>& , const LessThanSpy<T>& )
{ return 1; }

template < typename T >
bool operator != ( const LessThanSpy<T>& , const LessThanSpy<T>& )
{ return 0; }

template < typename T >
bool operator == ( const GreaterThanSpy<T>& , const GreaterThanSpy<T>& )
{ return 1; }

template < typename T >
bool operator != ( const GreaterThanSpy<T>& , const GreaterThanSpy<T>& )
{ return 0; }


} // namespace fsu
#endif
