/*
    entry.h
    01/01/2012
    Chris Lacher

    Defining:

      Entry<K,D> class template

    Entry<K,D> is specifically intended for use as the basic entry type in
    tables, maps, dictionaries, and associative arrays. The key stored in a
    Entry object is a constant. This implies that key must be given a value at
    the time of creation of the object, and this value cannot be changed during
    the lifetime of the object. Unusual features derived from these facts are:

      (1) There is no default constructor, and 
      (2) Assignment can only operate on the data field. It is an error to
          attempt to assign between Entry objects with unequal keys.

    Entry<K,D> supports comparison operators (both equality and order) that defer
    to the key value.

    It is sometimes convenient to convert a Pair to an Entry: A Pair p can have
    its first_ modified before conversion to Entry.

    Copyright 2012 R.C. Lacher
*/

#ifndef _FSU_ENTRY_H
#define _FSU_ENTRY_H

#include <iostream>
#include <pair.h>

namespace fsu
{

  ////////////////////////////////////////////////////
  //  class Entry API
  ////////////////////////////////////////////////////

  template <typename K, typename D>
  class Entry
  {
  public:
    typedef K KeyType;
    typedef D DataType;
    const   KeyType  key_;   // copy constructor required
            DataType data_;  // default & copy constructor required

             Entry  ();
    explicit Entry  (K k);
             Entry  (const Pair<K,D>& p); // converts Pair to Entry - may be implicit
             Entry  (K k, D d);
             Entry  (const Entry& e);
    Entry&   operator =  (const Entry& e);
    bool     operator == (const Entry e2) const;
    bool     operator != (const Entry e2) const;
    bool     operator <= (const Entry e2) const;
    bool     operator >= (const Entry e2) const;
    bool     operator >  (const Entry e2) const;
    bool     operator <  (const Entry e2) const;
  } ;

  // one stand alone operator

  template <typename K, typename D>
  std::ostream& operator << (std::ostream& os, const Entry<K,D>& e)
  {
    os << e.key_ << ':'<< e.data_;
    return os;
  }

  // order predicate classes
  // LessThan < Entry < K , D > > and GreaterThan < Entry < K , D > > also work

  template <typename K, typename D>
  class EntryLessThan
  {
  public:
    bool operator () (const Entry<K,D>& e1, const Entry<K,D>& e2) const
    {
      return e1.key_ < e2.key_;
    }
  } ;

  template <typename K, typename D>
  class EntryGreaterThan
  {
  public:
    bool operator () (const Entry<K,D>& e1, const Entry<K,D>& e2) const
    {
      return e2.key_ < e1.key_;
    }
  } ;

  ////////////////////////////////////////////////////
  // implementations
  ////////////////////////////////////////////////////

  template <typename K, typename D>
  Entry<K,D>::Entry() : key_(), data_()
  {}

  template <typename K, typename D>
  Entry<K,D>::Entry(K k) : key_(k), data_()
  {}

  template <typename K, typename D>
  Entry<K,D>::Entry(K k, D d) : key_(k), data_(d)
  {}

  template <typename K, typename D>
  Entry<K,D>::Entry(const Pair<K,D>& p) : key_(p.first_), data_(p.second_)
  {}

  template <typename K, typename D>
  Entry<K,D>::Entry(const Entry<K,D>& e) :   key_(e.key_), data_(e.data_)
  {}

  template <typename K, typename D>
  Entry<K,D>& Entry<K,D>::operator = (const Entry<K,D>& e)
  {
    if (key_ != e.key_)
      std::cerr << " ** Entry error: cannot assign entry objects with different keys\n";
    else
      data_ = e.data_;
    return *this;
  }

  template <typename K, typename D>
  bool Entry<K,D>::operator == (const Entry<K,D> e2) const
  {
    return (key_ == e2.key_);
  }

  template <typename K, typename D>
  bool Entry<K,D>::operator != (const Entry<K,D> e2) const
  {
    return (key_ != e2.key_);
  }

  template <typename K, typename D>
  bool Entry<K,D>::operator <= (const Entry<K,D> e2) const
  {
    return (key_ <= e2.key_);
  }

  template <typename K, typename D>
  bool Entry<K,D>::operator >= (const Entry<K,D> e2) const
  {
    return (key_ >= e2.key_);
  }

  template <typename K, typename D>
  bool Entry<K,D>::operator > (const Entry<K,D> e2) const
  {
    return (key_ > e2.key_);
  }

  template <typename K, typename D>
  bool Entry<K,D>::operator < (const Entry<K,D> e2) const
  {
    return (key_ < e2.key_);
  }

} // namespace fsu

#endif
