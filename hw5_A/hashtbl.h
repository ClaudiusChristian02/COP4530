/*
    hashtbl.h
    <your name>
    <date>

    <file documentation>

    NOTE: search for "TBS" to find missing code that is required

*/

#ifndef _HASHTBL_H
#define _HASHTBL_H

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>    // used by Analysis in hashtbl.cpp

#include <entry.h>
#include <vector.h>
#include <list.h>
#include <primes.h>
#include <genalg.h> // Swap()

namespace fsu
{

  template <typename K, typename D, class H>
  class HashTable;

  template <typename K, typename D, class H>
  class HashTableIterator;

  //--------------------------------------------
  //     HashTable <K,D,H>
  //--------------------------------------------

  template <typename K, typename D, class H>
  class HashTable
  {
    friend class HashTableIterator <K,D,H>;
  public:
    typedef K                                KeyType;
    typedef D                                DataType;
    typedef fsu::Entry<K,D>                  EntryType;
    typedef fsu::List<EntryType>             BucketType;
    typedef H                                HashType;
    typedef typename BucketType::ValueType   ValueType;
    typedef HashTableIterator<K,D,H>         Iterator;
    typedef HashTableIterator<K,D,H>    ConstIterator;

    // ADT Table
    Iterator       Insert        (const K& k, const D& d);
    bool           Remove        (const K& k);
    bool           Retrieve      (const K& k, D& d) const;
    Iterator       Includes      (const K& k) const;

    // ADT Associative Array
    D&             Get           (const K& key);
    void           Put           (const K& key, const D& data);
    D&             operator[]    (const K& key);

    // const versions of Get & []
    const D&       Get           (const K& key) const;
    const D&       operator[]    (const K& key) const;

    void           Clear         ();
    void           Rehash        (size_t numBuckets = 0);
    size_t         Size          () const;
    bool           Empty         () const;

    // Iterator       Begin         ();
    // Iterator       End           ();

    ConstIterator  Begin         () const;
    ConstIterator  End           () const;

    // first ctor uses default hash object, second uses supplied hash object
    explicit       HashTable     (size_t numBuckets = 100, bool prime = 1);
    HashTable                    (size_t numBuckets, HashType hashObject, bool prime = 1);
                   ~HashTable    ();
    HashTable                    (const HashTable<K,D,H>&);
    HashTable& operator =        (const HashTable&);

    // these are for debugging and analysis
    void           Dump          (std::ostream& os, int c1 = 0, int c2 = 0) const;
    size_t         MaxBucketSize () const;
    void           Analysis      (std::ostream& os) const;

  private:
    // data
    size_t                 numBuckets_; // number of entries in the vector
    Vector < BucketType >  bucketVector_;
    HashType               hashObject_;
    bool                   prime_;     // flag for prime number of buckets

    // private method calculates bucket index
    size_t  Index          (const KeyType& k) const;
  } ;

  //--------------------------------------------
  //     HashTableIterator <K,D,H>
  //--------------------------------------------

  // Note: This is a ConstIterator - cannot be used to modify table 

  template <typename K, typename D, class H>
  class HashTableIterator
  {
    friend class HashTable <K,D,H>;
  public:
    typedef K                                KeyType;
    typedef D                                DataType;
    typedef fsu::Entry<K,D>                  EntryType;
    typedef fsu::List<EntryType>             BucketType;
    typedef H                                HashType;
    typedef typename BucketType::ValueType   ValueType;
    typedef HashTableIterator<K,D,H>         Iterator;
    typedef HashTableIterator<K,D,H>         ConstIterator;

    HashTableIterator   ();
    HashTableIterator   (const Iterator& i);
    bool Valid          () const;
    HashTableIterator <K,D,H>& operator =  (const Iterator& i);
    HashTableIterator <K,D,H>& operator ++ ();
    HashTableIterator <K,D,H>  operator ++ (int);
    // Entry <K,D>&               operator * ();
    const Entry <K,D>&         operator *  () const;
    bool                       operator == (const Iterator& i2) const;
    bool                       operator != (const Iterator& i2) const;

  protected:
    const HashTable <K,D,H> *           tablePtr_;
    size_t                              bucketNum_;
    typename BucketType::ConstIterator  bucketItr_;
    // typename BucketType::Iterator  bucketItr_;
  } ;

  //--------------------------------------------
  //     HashTable <K,D,H>
  //--------------------------------------------

  // ADT Table

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H> HashTable<K,D,H>::Insert (const K& k, const D& d)
  {
    EntryType e(k,d);
    Iterator i;
    // TBS

	// with this we address the list in the vector
	size_t key2int = hashObject_(k) % numBuckets_;
	 
	// inserts key value pair
	i.bucketItr_ = bucketVector_[key2int].Insert(e);

	i.tablePtr_ = this;
	i.bucketNum_ = key2int;
    return i;
  }

  template <typename K, typename D, class H>
  bool HashTable<K,D,H>::Remove (const K& k)
  {
    // TBS
	  // iterator that points to the list
	  Iterator list = Includes(k);

	  if (list == End()){

		  return false;
	  }

	  else{

		  bucketVector_[list.bucketNum_].Remove(list.bucketItr_);

		  return true;
	  }
	  
	return false;
    //return 0;
  }

  template <typename K, typename D, class H>
  bool HashTable<K,D,H>::Retrieve (const K& k, D& d) const
  {
    // TBS

	  // iterator that points to the list
	  Iterator list = Includes(k);
	
	  if (list == End()){

		  return false;
	  }

	  else{

		  d = (*list.bucketItr_).data_;

		  return true;
	  }


    return 0;
  }

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H> HashTable<K,D,H>::Includes (const K& k) const
  {
    // TBS

	  // with this we address the list in the vector
	  size_t key2int = hashObject_(k) % numBuckets_;

	  for (auto i = bucketVector_[key2int].Begin(); i != bucketVector_[key2int].End(); ++i){

		  // if a similar key value is found it removes the value from the list
		  if ((*i).key_ == k){

			  HashTableIterator<K, D, H> iterator;

			  // tablePtr_ is a pointer to associated hash table
			  // iterator points to a value in a container 
			  iterator.tablePtr_ = this;

			  iterator.bucketNum_ = key2int;

			  iterator.bucketItr_ = i;

			  return iterator;
		  }

	  }

    return End();
  }

  // ADT Associative Array

  template <typename K, typename D, class H>
  D& HashTable<K,D,H>::Get (const K& key)
  {
    EntryType e(key);
    size_t bn = Index(key);
    typename BucketType::Iterator i = bucketVector_[bn].Includes(e); 
    if (i == bucketVector_[bn].End())
      i = bucketVector_[bn].Insert(e);
    return (*i).data_;
  }

  template <typename K, typename D, class H>
  const D& HashTable<K,D,H>::Get (const K& key) const
  {
    Iterator i = Includes(key);
    if (i == End())
    {
      std::cerr << "** Error: const bracket operator called on non-existence key\n";
      exit (EXIT_FAILURE);
    }
    return (*i).data_;
  }

  template <typename K, typename D, class H>
  void HashTable<K,D,H>::Put (const K& key, const D& data)
  {
    // any of these works:
    Insert(key,data);
    // Get(key) = data;
    // (*this)[key] = data;
  }

  template <typename K, typename D, class H>
  D& HashTable<K,D,H>::operator[] (const K& key)
  {
    return Get(key);
  }

  template <typename K, typename D, class H>
  const D& HashTable<K,D,H>::operator[] (const K& key) const
  {
    return Get(key);
  }

  // constructors

  template <typename K, typename D, class H>
  HashTable <K,D,H>::HashTable (size_t n, bool prime)
    :  numBuckets_(n), bucketVector_(0), hashObject_(), prime_(prime)
  {
    // ensure at least 2 buckets
    if (numBuckets_ < 3)
      numBuckets_ = 2;
    // optionally convert to prime number of buckets
    if (prime_)
      numBuckets_ = fsu::PrimeBelow(numBuckets_);
    // create buckets
    bucketVector_.SetSize(numBuckets_);
  }

  template <typename K, typename D, class H>
  HashTable <K,D,H>::HashTable (size_t n, H hashObject, bool prime)
    :  numBuckets_(n), bucketVector_(0), hashObject_(hashObject), prime_(prime)
  {
    // ensure at least 2 buckets
    if (numBuckets_ < 3)
      numBuckets_ = 2;
    // optionally convert to prime number of buckets
    if (prime_)
      numBuckets_ = fsu::PrimeBelow(numBuckets_);
    // create buckets
    bucketVector_.SetSize(numBuckets_);
  }

  // copies

  template <typename K, typename D, class H>
  HashTable <K,D,H>::HashTable (const HashTable& ht)
    :  numBuckets_(ht.numBuckets_), bucketVector_(ht.bucketVector_), hashObject_(ht.hashObject_)
  {}

  template <typename K, typename D, class H>
  HashTable<K,D,H>& HashTable <K,D,H>::operator =  (const HashTable& ht)
  {
    if (this != &ht)
    {
      numBuckets_ = ht.numBuckets_;
      bucketVector_ = ht.bucketVector_;
      hashObject_ = ht.hashObject_;
    }
    return *this;
  }

  // other public methods

  template <typename K, typename D, class H>
  HashTable <K,D,H>::~HashTable ()
  {
    Clear();
  }

  template <typename K, typename D, class H>
  void HashTable<K,D,H>::Rehash (size_t nb)
  {
    if (nb == 0) nb = Size();
    HashTable<K,D,H> newTable(nb,hashObject_,prime_);
    for (size_t i = 0; i < numBuckets_; ++i)
    {
      while (!bucketVector_[i].Empty()) // pop as we go saves local space bloat
      {
        newTable.Insert(bucketVector_[i].Back().key_,bucketVector_[i].Back().data_);
        bucketVector_[i].PopBack();
      }
    }
    fsu::Swap(numBuckets_,newTable.numBuckets_);
    bucketVector_.Swap(newTable.bucketVector_);
  }

  template <typename K, typename D, class H>
  void HashTable<K,D,H>::Clear ()
  {
    for (size_t i = 0; i < numBuckets_; ++i)
      bucketVector_[i].Clear();
  }

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H> HashTable<K,D,H>::Begin () const
  {
    // fsu::debug("Begin()");
    HashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = 0;
    while (i.bucketNum_ < numBuckets_ && bucketVector_[i.bucketNum_].Empty())
      ++i.bucketNum_;
    // now we either have the first non-empty bucket or we've exhausted the bucket numbers
    if (i.bucketNum_ < numBuckets_)
      i.bucketItr_ = bucketVector_[i.bucketNum_].Begin();
    else
    {
      i.bucketNum_ = 0;
      i.bucketItr_ = bucketVector_[i.bucketNum_].End();
    }
    return i;
  }

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H> HashTable<K,D,H>::End () const
  {
    // fsu::debug("End()");
    HashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = numBuckets_ - 1;
    i.bucketItr_ = bucketVector_[i.bucketNum_].End();
    return i;
  }

  template <typename K, typename D, class H>
  size_t HashTable<K,D,H>::Size () const
  {
    size_t size(0);
    for (size_t i = 0; i < numBuckets_; ++i)
      size += bucketVector_[i].Size();
    return size;
  }

  template <typename K, typename D, class H>
  bool HashTable<K,D,H>::Empty () const
  {
    for (size_t i = 0; i < numBuckets_; ++i)
      if (!bucketVector_[i].Empty())
        return 0;
    return 1;
  }

  template <typename K, typename D, class H>
  void HashTable<K,D,H>::Dump (std::ostream& os, int c1, int c2) const
  {
    typename BucketType::ConstIterator i;
    for (size_t b = 0; b < numBuckets_; ++b)
    {
      os << "b[" << b << "]:";
      for (i = bucketVector_[b].Begin(); i != bucketVector_[b].End(); ++i)
        os << '\t' << std::setw(c1) << (*i).key_ << ':' << std::setw(c2) << (*i).data_;
      os << '\n';
    }
  }

  // private helper

  template <typename K, typename D, class H>
  size_t HashTable <K,D,H>::Index (const K& k) const
  {
    return hashObject_ (k) % numBuckets_;
  }

  //--------------------------------------------
  //     HashTableIterator <K,D,H>
  //--------------------------------------------

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H>::HashTableIterator () 
    :  tablePtr_(0), bucketNum_(0), bucketItr_()
  {}

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H>::HashTableIterator (const Iterator& i)
    :  tablePtr_(i.tablePtr_), bucketNum_(i.bucketNum_), bucketItr_(i.bucketItr_)
  {}

  template <typename K, typename D, class H>
  HashTableIterator <K,D,H>& HashTableIterator<K,D,H>::operator = (const Iterator& i)
  {
    if (this != &i)
    {
      tablePtr_  = i.tablePtr_;
      bucketNum_ = i.bucketNum_;
      bucketItr_ = i.bucketItr_;
    }
    return *this;
  }

  template <typename K, typename D, class H>
  HashTableIterator <K,D,H>& HashTableIterator<K,D,H>::operator ++ ()
  {
    // TBS

	  // first must check for table pointer because default constructor assigns NULL
	  if (tablePtr_ != NULL){

		  // if the iterator is not at the end increment the iterator
		  if (bucketItr_ != tablePtr_->bucketVector_[bucketNum_].End()){

			  ++bucketItr_;

		  }

		  // it is at the end of hashtable or end of the entry
		  else if(bucketNum_ < tablePtr_->numBuckets_ - 1 ){


			  ++bucketNum_;

			  // if at the end increcment the bucket number and set the
			  // iterator to the beginning of the next list
			  bucketItr_ = tablePtr_->bucketVector_[bucketNum_].Begin();

		  }


	  }

    return *this;
  }

  template <typename K, typename D, class H>
  HashTableIterator <K,D,H> HashTableIterator<K,D,H>::operator ++ (int)
  {
    HashTableIterator <K,D,H> i = *this;
    operator ++();
    return i;
  }

  /* Note: the following would be in Iterator, which would differ from ConstIterator by
     (1) the underlying bucketItr_ would not be const
     (2) adding Begin() and End() support
     (3) adding this non-const dereference

  template <typename K, typename D, class H>
  Entry<K,D>& HashTableIterator<K,D,H>::operator * () 
  {
    if (!Valid())
    {
      std::cerr << "** HashTableIterator error: invalid dereference\n";
      exit (EXIT_FAILURE);
    }
    return *bucketItr_;
  }
  */

  template <typename K, typename D, class H>
  const Entry<K,D>& HashTableIterator<K,D,H>::operator * () const
  {
    if (!Valid())
    {
      std::cerr << "** HashTableIterator error: invalid dereference\n";
      exit (EXIT_FAILURE);
    }
    return *bucketItr_;
  }

  template <typename K, typename D, class H>
  bool HashTableIterator<K,D,H>::operator == (const Iterator& i2) const
  {
    if (!Valid() && !i2.Valid())
      return 1;
    if (Valid() && !i2.Valid())
      return 0;
    if (!Valid() && i2.Valid())
      return 0;

    // now both are valid
    if (tablePtr_ != i2.tablePtr_)
      return 0;
    if (bucketNum_ != i2.bucketNum_)
      return 0;
    if (bucketItr_ != i2.bucketItr_)
      return 0;
    return 1;
  }

  template <typename K, typename D, class H>
  bool HashTableIterator<K,D,H>::operator != (const Iterator& i2) const
  {
    return !(*this == i2);
  }

  template <typename K, typename D, class H>
  bool HashTableIterator<K,D,H>::Valid () const
  {
    if (tablePtr_ == 0)
      return 0;
    if (bucketNum_ >= tablePtr_->numBuckets_)
      return 0;
    return bucketItr_ != tablePtr_->bucketVector_[bucketNum_].End();
  }

  // The stub implementations below should remain as-is.
  // They will be implemented as a project in COP4531.

  template <typename K, typename D, class H>
  size_t HashTable<K,D,H>::MaxBucketSize () const
  {   
    std::cout << " ** MaxBucketSize not implemented\n";
    return 0;
  }

  template <typename K, typename D, class H>
  void HashTable<K,D,H>::Analysis (std::ostream& os) const
  {
    os << " ** Analysis not implemented\n";
  } // Analysis

} // namespace fsu

#endif
