/*
    pair.h
    01/01/12
    Chris Lacher

    Defining:

      Pair<K,D> class template

    Pair<K,D> is a more flexible version of Entry. The difference is that the
    Entry holds the key portion constant and has no default constructor,
    whereas either the first or the second data can be overwritten in a Pair object.

    Pair<K,D> supports comparison operators (both equality and order) that defer
    to the first value in the pair.

    Copyright 2012 R.C. Lacher
*/

#ifndef _FSU_PAIR_H
#define _FSU_PAIR_H

#include <iostream>

namespace fsu
{

  ////////////////////////////////////////////////////
  //  class Pair API
  ////////////////////////////////////////////////////

  template <typename K, typename D>
  class Pair
  {
  public:
    typedef K FirstType;
    typedef D SecondType;
            FirstType  first_;
            SecondType second_;

             Pair  ();
    explicit Pair  (K k);
             Pair  (K k, D d);
             Pair  (const Pair& p);
    Pair&  operator =  (const Pair& p);
    bool   operator == (const Pair p2) const;
    bool   operator != (const Pair p2) const;
    bool   operator <= (const Pair p2) const;
    bool   operator >= (const Pair p2) const;
    bool   operator >  (const Pair p2) const;
    bool   operator <  (const Pair p2) const;
  } ;

  // one stand alone operator

  template <typename K, typename D>
  std::ostream& operator << (std::ostream& os, const Pair<K,D>& e)
  {
    os << e.first_ << ':'<< e.second_;
    return os;
  }

  // order predicate classes
  // LessThan < Pair < K , D > > and GreaterThan < Pair < K , D > > also work

  template <typename K, typename D>
  class PairLessThan
  {
  public:
    bool operator () (const Pair<K,D>& e1, const Pair<K,D>& p2) const
    {
      return e1.first_ < p2.first_;
    }
  } ;

  template <typename K, typename D>
  class PairGreaterThan
  {
  public:
    bool operator () (const Pair<K,D>& e1, const Pair<K,D>& p2) const
    {
      return p2.first_ < e1.first_;
    }
  } ;

  ////////////////////////////////////////////////////
  // implementations
  ////////////////////////////////////////////////////

  template <typename K, typename D>
  Pair<K,D>::Pair() : first_(), second_()
  {}

  template <typename K, typename D>
  Pair<K,D>::Pair(K k) : first_(k), second_()
  {}

  template <typename K, typename D>
  Pair<K,D>::Pair(K k, D d) : first_(k), second_(d)
  {}

  template <typename K, typename D>
  Pair<K,D>::Pair(const Pair<K,D>& p) :   first_(p.first_), second_(p.second_)
  {}

  template <typename K, typename D>
  Pair<K,D>& Pair<K,D>::operator = (const Pair<K,D>& p)
  {
    if (this != &p)
    {
      first_ = p.first_;
      second_ = p.second_;
    }
    return *this;
  }

  template <typename K, typename D>
  bool Pair<K,D>::operator == (const Pair<K,D> p2) const
  {
    return (first_ == p2.first_);
  }

  template <typename K, typename D>
  bool Pair<K,D>::operator != (const Pair<K,D> p2) const
  {
    return (first_ != p2.first_);
  }

  template <typename K, typename D>
  bool Pair<K,D>::operator <= (const Pair<K,D> p2) const
  {
    return (first_ <= p2.first_);
  }

  template <typename K, typename D>
  bool Pair<K,D>::operator >= (const Pair<K,D> p2) const
  {
    return (first_ >= p2.first_);
  }

  template <typename K, typename D>
  bool Pair<K,D>::operator > (const Pair<K,D> p2) const
  {
    return (first_ > p2.first_);
  }

  template <typename K, typename D>
  bool Pair<K,D>::operator < (const Pair<K,D> p2) const
  {
    return (first_ < p2.first_);
  }

} // namespace fsu

#endif
