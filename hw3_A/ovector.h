/*
    ovector.h
    02/01/12
    Chris Lacher

    Definition of the class templates MOVector <> and UOVector <>
    the ordered vector classes adapted from Vector<>

    These are associative (value-oriented) data structures.  Duplicate items are
    allowed in MOVector<> and not allowed in UOVector<>. 

    These are 2-parameter classes: MOVector<T,P> and UOVector<T,P> take a
    predicate class P as second parameter.  An object of type P is used
    to define sort order on T. The second parameter has the default value P =
    LessThan<T>, making these behave as clsses with only one template
    parameter with the default ordering. (See compare.h.)
    
    The MOVector<> public interface gives the archetype for ordered
    associative containers.

    Classes defined in this file
    ----------------------------

    MOVector < T , P = LessThan < T > >
    UOVector < T , P = LessThan < T > >
    OVectorIterator < T , P = LessThan < T > >

    Assumptions on type T
    ---------------------

    MOVector and UOVector assume that T has overloads of the following
    operators and functions:

       insertion  (output) operator    <<  
       equality            operator    ==
       assignment          operator    =
       constructor                     T()
       destructor                      ~T()
       order operator                  <   [called by LessThan::operator()]

    Assumptions on type P
    ---------------------

    P is a "predicate class"; that is, P is assumed to have the operator
    "()" overloaded with the prototype:

      bool P::operator () (const T&, const T&) const;

    A function object lessThan of type P used for order comparison, where
    "lessThan(a,b) == true" is taken to mean "a < b". This is a private class
    variable. A const reference to the predicate is returned by GetPredicate(). 

    There is a 1-parameter constructor that allows the client to supply a
    particular predicate object, otherwise the default predicate of type P is
    used. Since it is possible to have elaborate predicate objects that have
    state that must be set, clients may need to create such an object prior to
    instantiating a ordered vector.

    "M" v "U" semantics
    -------------------

    There are generally two ways to define the semantics of Insert operations
    for associative containers, depending on whether or not duplicate elements
    are allowed in the container. 

    Unimodal containers do not allow duplicate elements. The Insert operations
    for unimodal containers typically perform "overwrite or insert" depending on
    whether the item being inserted exists in the container prior to the call of
    the operation. The SET is the archetype for unimodal containers. 

    Multimodal containers allow duplicate elements. the Insert operations for
    multimodal containers typically perform an insertion whether or not the
    element exists in the container prior to the call of the operation. The
    MULTISET is the archetype for multimodal containers.

    MOVector<> is multimodal, UOVector<> is unimodal. 

    Copyright 2012, R.C. Lacher

*/

#ifndef _OVECTOR_H
#define _OVECTOR_H

#include <iostream>
#include <vector.h>
#include <compare.h>
#include <gbsearch.h>

namespace fsu
{

  template <class T, class P>
  class MOVector;

  template <class T, class P>
  class UOVector;

  template <class T, class P>
  class OVectorIterator;

  template<typename T, class P> 
  bool operator == (const MOVector<T,P>& x1, const MOVector<T,P>& x2);

  template<typename T, class P> 
  bool operator != (const MOVector<T,P>& x1, const MOVector<T,P>& x2);

  template <typename T, class P>
  std::ostream& operator << (std::ostream& os, const MOVector<T,P>& x);

  //----------------------------------
  //     MOVector<T,P>
  //----------------------------------

  template < typename T , class P = LessThan < T > >
  class MOVector
  {
  public:
    typedef T                           ValueType; 
    typedef P                           PredicateType;
    typedef T*                          PointerType;
    typedef const T*                    ConstPointerType;
    typedef T&                          ReferenceType;
    typedef const T&                    ConstReferenceType;
    typedef MOVector < T , P>           ContainerType;
    typedef OVectorIterator < T , P >   Iterator;
    typedef OVectorIterator < T , P >   ConstIterator;

    friend bool operator == <> (const MOVector<T,P>& x1, const MOVector<T,P>& x2);

    // mutating the set
    bool     Insert    (const T& t);  // insert at lower bound
    bool     Insert    (Iterator& i, const T& t);  // insert at i if structure OK
    size_t   Remove    (const T& t);  // remove all copies of t
    bool     Remove    (Iterator& i); // remove item at i
    void     Clear     ();            // make vector empty

    // these vector methods are order-safe and convenient to keep:
    bool     PopBack   () { return vect_.PopBack(); }     // "DeleteMax"
    const T& Front     () const { return vect_.Front(); } // "Min"
    const T& Back      () const { return vect_.Back(); }  // "Max"
    
    // locating elements - ordered associative container operations
    Iterator LowerBound (const T& t) const;
    Iterator UpperBound (const T& t) const;
    Iterator Includes   (const T& t) const;
    // Defn: lower bound is the first position p in a traversal with t <= *p
    // Defn: upper bound is the first position p in a traversal with t <  *p
    // Defn: Includes() returns LowerBound() if found, End() otherwise

    Iterator Begin      () const;
    Iterator End        () const;
    Iterator rBegin     () const;
    Iterator rEnd       () const;

    // size operations
    bool    Empty () const;
    size_t  Size  () const;

    // assignment
    MOVector<T,P>& operator  = (const MOVector<T,P>& x);

    // constructors
             MOVector  ();
    explicit MOVector  ( PredicateType );
             MOVector  ( const MOVector& );
    virtual  ~MOVector ();

    // Provide access to predicate - but don't allow modification
    const P& GetPredicate() const;

    // generic output
    void Display (std::ostream& os, char ofc = '\0') const;
    void Dump    (std::ostream& os, char ofc = '\0') const;

    // structural tests
    bool CheckMOVector(bool verboseFlag = 0) const;
    bool CheckUOVector(bool verboseFlag = 0) const;

  protected:
    Vector<T>  vect_;
    P          pred_;

    bool PushFront(const T& t);
    bool PushBack(const T& t);
    bool LeapFrogInsert(Iterator i, const T& t);
    bool LeapFrogRemove(Iterator i);
    bool LeapFrogRemove(Iterator i1, Iterator i2);

  } ; // class MOVector<T,P>

  //----------------------------------
  //     OVectorIterator<T,P>
  //----------------------------------

  /*
    An ordered vector iterator is just a wrapper on a positional vector
    ConstIterator. The types Iterator and ConstIterator are the same, since we
    don't allow OVector iterators to return mutable values.
  */

  template <typename T, class P = LessThan<T> >
  class OVectorIterator
  {
  public:
    typedef T                           ValueType; 
    typedef P                           PredicateType;
    typedef T*                          PointerType;
    typedef const T*                    ConstPointerType;
    typedef T&                          ReferenceType;
    typedef const T&                    ConstReferenceType;
    typedef MOVector < T , P>           ContainerType;
    typedef OVectorIterator < T , P >   Iterator;
    typedef OVectorIterator < T , P >   ConstIterator;

                 OVectorIterator  ();
                 OVectorIterator  (const OVectorIterator&);
                 OVectorIterator  (const T*& iter);
    virtual      ~OVectorIterator ();

    bool              Valid       () const;

    // operators for bidirectional ConstIterator
    bool      operator == (const Iterator& i2) const;
    bool      operator != (const Iterator& i2) const;
    const T&  operator *  () const; // const version
    Iterator& operator =  (const Iterator & that);
    Iterator& operator ++ ();    // prefix
    Iterator  operator ++ (int); // postfix
    Iterator& operator -- ();    // prefix
    Iterator  operator -- (int); // postfix

  private:
    const T* iter_;
    friend class MOVector<T,P>;
    friend class UOVector<T,P>;
  };

  //----------------------------------
  //     UOVector<T,P>
  //----------------------------------

  /*
     The change in semantics from multi- to uni-modal requires only one
     over-ride - to Insert. All other operations are inherited. The Iterator
     class is re-used in its entirety. 

     Of course, constructors, destrutctor, and assignment require their own
     implementations.

     The operations are left in the definition - commented out - to remind the
     user what the interface is.
  */

  template < typename T , class P = LessThan < T > >
  class UOVector : public MOVector < T , P >
  {
  public:
    typedef T                          ValueType; 
    typedef P                          PredicateType;
    typedef T*                         PointerType;
    typedef const T*                   ConstPointerType;
    typedef T&                         ReferenceType;
    typedef const T&                   ConstReferenceType;
    typedef UOVector < T , P>          ContainerType;
    typedef OVectorIterator < T , P >  Iterator;
    typedef OVectorIterator < T , P >  ConstIterator;

    // friend bool operator == <> (const UOVector<T,P>& x1, const UOVector<T,P>& x2);

    bool     Insert    (const T& t);  // insert at lower bound
    bool     Insert    (Iterator& i, const T& t);  // insert at i if *i == t

    // size_t   Remove    (const T& t);  // remove all copies of t
    // bool     Remove    (Iterator& i); // remove item at i
    // void     Clear     ();            // make vector empty

    // Iterator LowerBound (const T& t) const;
    // Iterator UpperBound (const T& t) const;
    // Iterator Includes   (const T& t) const;

    // Iterator Begin      () const;
    // Iterator End        () const;
    // Iterator rBegin     () const;
    // Iterator rEnd       () const;

    // size operations
    // bool    Empty () const;
    // size_t  Size  () const;

    // assignment
    UOVector<T,P>& operator  = (const UOVector<T,P>& x);

    // constructors
             UOVector  ();
    explicit UOVector  ( PredicateType );
             UOVector  ( const UOVector& );
    virtual  ~UOVector ();

    // Provide access to predicate - but don't allow modification
    // const P& GetPredicate() const;

    // generic output
    // void Display (std::ostream& os, char ofc = '\0') const;
    // void Dump    (std::ostream& os, char ofc = '\0') const;

    // structural tests
    // void CheckMOVector(bool verboseFlag = 0) const;
    // void CheckUOVector(bool verboseFlag = 0) const;

  } ; // class UOVector<T,P>

  //-----------------------------------
  //     TXOVector<T,P>:: Implementations
  //-----------------------------------

  // protected methods

  template<typename T, class P> 
  bool MOVector<T,P>::PushFront(const T& t)
  {
    Iterator i = Begin();
    return LeapFrogInsert(i,t);
  }

  template<typename T, class P> 
  bool MOVector<T,P>::PushBack(const T& t)
  {
    return vect_.PushBack(t);
  }

  template<typename T, class P> 
  bool MOVector<T,P>::LeapFrogInsert(Iterator iter, const T& t)
  {
    if (!iter.Valid()) return 0;
    if (iter == End()) // insert at back
      return vect_.PushBack(t);

    size_t location = iter.iter_ - vect_.Begin();
    bool ok = vect_.PushBack(t); // might change footprint - can't use iter any more
    if (!ok) return 0;

    // assert(location < vect_.Size() - 1);
    // now we play leapfrog:
    for (size_t i = vect_.Size() - 1; i > location; --i)
      vect_[i] = vect_[i - 1];
    vect_[location] = t;
    return 1;
  }

  template<typename T, class P> 
  bool MOVector<T,P>::LeapFrogRemove(Iterator iter)
  {
    if (!iter.Valid()) return 0;
    size_t location = iter.iter_ - vect_.Begin();
    if (location == vect_.Size())
      return 0;

    if (location == vect_.Size() - 1)
      return vect_.PopBack();

    // assert (location < vect_.Size() - 1);
    // leapfrog:
    for (size_t i = location; i <  vect_.Size() - 1; ++i)
      vect_[i] = vect_[i+1];
    return vect_.PopBack();
  }

  template<typename T, class P> 
  bool MOVector<T,P>::LeapFrogRemove(Iterator iter1, Iterator iter2)
  {
    if (!iter1.Valid() || !iter2.Valid()) return 0;
    size_t beg = iter1.iter_ - vect_.Begin();
    size_t end = iter2.iter_ - vect_.Begin();
    if (end <= beg) return 0;
    size_t diff = end - beg;
    // assert (diff <= vect_.Size());
    size_t newsize = vect_.Size() - diff;

    // leapfrog, stepsize = diff:
    for (size_t i = beg; i < newsize; ++i)
      vect_[i] = vect_[i+diff];
    return vect_.SetSize(newsize);
  }

  // non-member operators

  template<typename T, class P> 
  bool operator == (const MOVector<T,P>& x1, const MOVector<T,P>& x2)
  {
    return ( ( x1.vect_ == x2.vect_ ) && (x1.pred_ == x2.pred_) );
  }

  /******** derived class overload ********/
  template<typename T, class P> 
  bool operator == (const UOVector<T,P>& x1, const UOVector<T,P>& x2)
  {
    return (MOVector<T,P>)x1 == (MOVector<T,P>)x2;
  }
  /****************************************/

  template<typename T, class P> 
  bool operator != (const MOVector<T,P>& x1, const MOVector<T,P>& x2)
  {
    return !(x1 == x2);
  }

  /******** derived class overload ********/
  template<typename T, class P> 
  bool operator != (const UOVector<T,P>& x1, const UOVector<T,P>& x2)
  {
    return !(x1 == x2);
  }
  /****************************************/

  template <typename T, class P>
  void MOVector<T,P>::Display (std::ostream& os, char ofc) const
  {
    vect_.Display(os,ofc);
  }

  template <typename T, class P>
  void MOVector<T,P>::Dump (std::ostream& os, char ofc) const
  {
    os << "Contents: ";
    Display(os,ofc);
    os << '\n';
  }

  template <typename T, class P>
  std::ostream& operator << (std::ostream& os, const MOVector<T,P>& x)
  {
    x.Display(os);
    return os;
  }

  /******** derived class overload ********/
  template <typename T, class P>
  std::ostream& operator << (std::ostream& os, const UOVector<T,P>& x)
  {
    x.Display(os);
    return os;
  }
  /****************************************/

  // structural tests
  template <typename T, class P>
  bool MOVector<T,P>::CheckMOVector(bool verboseFlag) const
  {
    bool ok = 1;
    if (Empty())
    {
      if (verboseFlag)
	std:: cout << "MOVector is empty\n";
      return ok;
    }
    Iterator i = MOVector<T,P>::Begin();
    Iterator j;
    size_t number = 0;
    for (j = i++; i != MOVector<T,P>::End(); j = i++, ++number)
    {
      if (verboseFlag || pred_(*i,*j))
      {
	std::cout << "element[" << number << "]= " << *j << " , "
		  << "element[" << number+1 << "]= " << *i;
	if (pred_(*i,*j)) 
	{
	  std::cout << " <- structural error";
	  ok = 0;
	}
	std::cout << '\n';
      }
    }
    if (ok && verboseFlag)
      std::cout << " ** CheckMUVector: OK\n";
    return ok;
  }

  template <typename T, class P>
  bool MOVector<T,P>::CheckUOVector(bool verboseFlag) const
  {
    bool ok = 1;
    if (Empty())
    {
      if (verboseFlag)
	std:: cout << "UOVector is empty\n";
      return ok;
    }
    Iterator i = MOVector<T,P>::Begin();
    Iterator j;
    size_t number = 0;
    for (j = i++; i != MOVector<T,P>::End(); j = i++, ++number)
    {
      if (verboseFlag || !pred_(*j,*i))
      {
	std::cout << "element[" << number << "]= " << *j << " , "
		  << "element[" << number+1 << "]= " << *i;
	if (!pred_(*j,*i))
	{
	  std::cout << " <- structural error";
	  ok = 0;
	}
	std::cout << '\n';
      }
    }
    if (ok && verboseFlag)
      std::cout << " ** CheckOUVector: OK\n";
    return ok;
  }

  // constructors & assignment

  template <typename T, class P>
  MOVector<T,P>::MOVector  () : vect_(), pred_()
  {}

  template <typename T, class P>
  UOVector<T,P>::UOVector  () : MOVector<T,P> ()
  {}

  template <typename T, class P>
  MOVector<T,P>::MOVector  (P p) : vect_(), pred_(p)
  {}

  template <typename T, class P>
  UOVector<T,P>::UOVector  (P p) : MOVector<T,P>(p)
  {}

  template <typename T, class P>
  MOVector<T,P>::MOVector  (const MOVector<T,P>& x) : vect_(x.vect_), pred_(x.pred_)
  {}

  template <typename T, class P>
  UOVector<T,P>::UOVector  (const UOVector<T,P>& x) : MOVector<T,P>(x)
  {}

  template <typename T, class P>
  MOVector<T,P>& MOVector<T,P>::operator  = (const MOVector<T,P>& x)
  {
    if (this != &x)
    {
      vect_ = x.vect_;
      pred_ = x.pred_;
    }
    return *this;
  }

  template <typename T, class P>
  UOVector<T,P>& UOVector<T,P>::operator  = (const UOVector<T,P>& x)
  {
    MOVector<T,P>::operator=(x);
    return *this;
  }

  template <typename T, class P>
  MOVector<T,P>::~MOVector ()
  {}

  template <typename T, class P>
  UOVector<T,P>::~UOVector ()
  {}

  // iterator support

  template <typename T, class P>
  OVectorIterator<T,P> MOVector<T,P>::Begin() const
  {
    Iterator i;
    i.iter_ = vect_.Begin(); // const version of Vector::Begin called here
    return i;
  }

  template <typename T, class P>
  OVectorIterator<T,P> MOVector<T,P>::End() const
  {
    Iterator i;
    i.iter_ = vect_.End(); // const version of Vector::End called here
    return i;
  }

  template <typename T, class P>
  OVectorIterator<T,P> MOVector<T,P>::rBegin() const
  {
    Iterator i;
    i.iter_ = vect_.rBegin(); // const version of Vector::Begin called here
    return i;
  }

  template <typename T, class P>
  OVectorIterator<T,P> MOVector<T,P>::rEnd() const
  {
    Iterator i;
    i.iter_ = vect_.rEnd(); // const version of Vector::Begin called here
    return i;
  }

  template <typename T, class P>
  size_t MOVector<T,P>::Size() const
  {
    return vect_.Size();
  }

  template <typename T, class P>
  bool MOVector<T,P>::Empty() const
  {
    return vect_.Empty();
  }

  template <typename T, class P>
  void MOVector<T,P>::Clear()
  {
    return vect_.Clear();
  }

  template <typename T, class P>
  const P& MOVector<T,P>::GetPredicate() const
  {
    return pred_;
  }

  template <typename T, class P>
  bool MOVector<T,P>::Insert (const T& t)
  // multimodal - insert at upper bound
  // uses binary search
  // uses LeapFrogInsert
  {
    Iterator i;
    i.iter_ = g_upper_bound(vect_.Begin(), vect_.End(), t, pred_);
    return this->LeapFrogInsert(i,t);
  }

  /******** derived class overload ********/
  template <typename T, class P>
  bool UOVector<T,P>::Insert (const T& t)
  // unimodal - insert at lower bound
  {
    Iterator i;
    i.iter_ = g_lower_bound(this->vect_.Begin(), this->vect_.End(), t, this->pred_);
    if (i != this->End() && *i == t)
    {
      const_cast<T&>(*i) = t;
      return 1;
    }
    return this->LeapFrogInsert(i,t);
  }
  /****************************************/

  template <typename T, class P>
  bool MOVector<T,P>::Insert (Iterator& i, const T& t)
  // insert at i if order is preserved (multimodal insert)
  {
    if (vect_.Empty())
    {
      return PushFront(t);
    }
    if (!i.Valid() || i == rEnd()) // can't make sense of request
    {
      return 0;
    }
    if (i == Begin() && !pred_(*i,t)) // t <= *i
    {
      return PushFront(t);
    }
    if (i == End() && !pred_(t,vect_.Back())) // Back() <= t
    {
      return PushBack(t);
    }
    // now i is not at front or back
    // check for correct order (<=)
    Iterator before = i;
    --before;
    if(!pred_(t,*before) && !pred_(*i,t)) // (*before <= t && t <= *i)
    {
      return LeapFrogInsert(i,t);
    }
    return 0;
  }

  /******** derived class overload ********/
  template <typename T, class P>
  bool UOVector<T,P>::Insert (Iterator& i, const T& t)
  // insert at i if order is preserved (unimodal insert)
  {
    // first take care of the over-write case:
    if (i.Valid() && i != this->rEnd() && i != this->End() && (*i == t))
    {
      const_cast<T&>(*i) = t;  // break const-ness to assign to read-only location
      return 1;
    }

    // now the algorithm is the same as the multimodal case, except with strict <
    if (this->vect_.Empty())
    {
      return this->PushFront(t);
    }
    if (!i.Valid() || i == this->rEnd()) // can't make sense of request
    {
      return 0;
    }
    if (i == this->Begin())
    {
      if (this->pred_(t,*i)) // t < *i
	return this->PushFront(t);
      else 
	return 0;
    }
    if (i == this->End())
    {
      if (this->pred_(this->vect_.Back(),t)) // Back() < t
	return this->PushBack(t);
      else
	return 0;
    }

    // now i is not at front or back
    // check for correct order (<)
    Iterator before = i;
    --before; 
    if(this->pred_(*before,t) && this->pred_(t,*i)) // (*before < t && t < *i)
    {
      return this->LeapFrogInsert(i,t);
    }
    return 0;
  }
  /****************************************/

  template <typename T, class P>
  size_t MOVector<T,P>::Remove (const T& t)
  // remove all copies of t
  {
    Iterator i1,i2;
    i1 = LowerBound(t);
    i2 = UpperBound(t);
    LeapFrogRemove(i1,i2);
    return i2.iter_ - i1.iter_;
  }

  template <typename T, class P>
  bool MOVector<T,P>::Remove (Iterator& i)
  // remove item at i
  {
    if (i.Valid())
    {
      return LeapFrogRemove(i);
    }
    return 0;
  }

  template <typename T, class P>
  typename MOVector<T,P>::Iterator MOVector<T,P>::LowerBound (const T& t) const
  // return lower bound
  // Defn: lower bound points to the first item on the vector >= t
  {
    Iterator i;
    i.iter_ = g_lower_bound(vect_.Begin(), vect_.End(), t, pred_);
    return i;
  }

  template <typename T, class P>
  typename MOVector<T,P>::Iterator MOVector<T,P>::UpperBound (const T& t) const
  // return upper bound
  // Defn: upper bound points to the first item on the vector > t
  {
    Iterator i;
    i.iter_ = g_upper_bound(vect_.Begin(), vect_.End(), t, pred_);
    return i;
  }

  template <typename T, class P>
  typename MOVector<T,P>::Iterator MOVector<T,P>::Includes (const T& t) const
  // return LowerBound(t) if found, End() otherwise
  {
    Iterator i = LowerBound(t);
    if (i != End() && (*i == t))
      return i;
    return End();
  }

  //-------------------------------------------
  //     OVectorIterator<T,P>:: Implementations
  //-------------------------------------------

  //Constructors, destructor, and assignment operator.

  template <typename T, class P>
  OVectorIterator<T,P>::OVectorIterator() : iter_()
  {}

  template <typename T, class P>
  OVectorIterator<T,P>::OVectorIterator(const OVectorIterator<T,P>& i) : iter_(i.iter_)
  {}

  template <typename T, class P>
  OVectorIterator<T,P>::OVectorIterator(const T*& iter) : iter_(iter)
  {}

  template <typename T, class P>
  OVectorIterator<T,P>::~OVectorIterator()
  {}

  template <typename T, class P>
  OVectorIterator<T,P>& OVectorIterator<T,P>::operator=(const OVectorIterator<T,P>& i)
  {
    iter_ = i.iter_;
    return *this;
  }

  //Returns 1 if the iterator is valid, 0 otherwise.
  template <typename T, class P>
  bool OVectorIterator<T,P>::Valid() const
  {
    return iter_ != 0;
  }

  //Decides if two iterators are equal.
  template <typename T, class P>
  bool OVectorIterator<T,P>::operator==(const OVectorIterator<T,P>& i) const
  {
    return (iter_ == i.iter_);
  }

  //Decides if two iterators are not equal.
  template <typename T, class P>
  bool OVectorIterator<T,P>::operator!=(const OVectorIterator<T,P>& i) const
  {
    return (iter_ != i.iter_);
  }

  //Returns a const reference to a node value.
  template <typename T, class P>
  const T& OVectorIterator<T,P>::operator*() const
  {
    return *iter_;
  }

  //Increments the iterator using in-order rules.
  template <typename T, class P>
  OVectorIterator<T,P>& OVectorIterator<T,P>::operator++()
  {
    ++iter_;
    return *this;
  }

  //Postfix version.
  template <typename T, class P>
  OVectorIterator<T,P> OVectorIterator<T,P>::operator++(int)
  {
    OVectorIterator<T,P> i = *this;
    operator++();
    return i;
  }

  //Decrements the iterator using in-order rules.
  template <typename T, class P>
  OVectorIterator<T,P>& OVectorIterator<T,P>::operator--()
  {
    --iter_;
    return *this;
  }

  //Postfix version.
  template <typename T, class P>
  OVectorIterator<T,P> OVectorIterator<T,P>::operator--(int)
  {
    OVectorIterator<T,P> i = *this;
    operator--();
    return i;
  }

} // namespace fsu
#endif
