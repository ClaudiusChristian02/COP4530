/*
    olist.h
    02/01/12
    Chris Lacher

    Definition of the class templates MOList <> and UOList <>
    the ordered list classes adapted from List<>

    These are associative (value-oriented) data structures.  Duplicate items are
    allowed in MOList<> and not allowed in UOList<>. 

    These are 2-parameter classes: MOList<T,P> and UOList<T,P> take a
    predicate class P as second parameter.  An object of type P is used
    to define sort order on T. The second parameter has the default value P =
    LessThan<T>, making these behave as clsses with only one template
    parameter with the default ordering. (See compare.h.)
    
    The MOList<> public interface gives the archetype for ordered
    associative containers.

    Classes defined in this file
    ----------------------------

    MOList < T , P = LessThan < T > >
    UOList < T , P = LessThan < T > >
    OListIterator < T , P = LessThan < T > >

    Assumptions on type T
    ---------------------

    MOList and UOList assume that T has overloads of the following
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
    instantiating a ordered list.

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

    MOList<> is multimodal, UOList<> is unimodal. 

    Copyright 2012, R.C. Lacher

*/

#ifndef _OLIST_H
#define _OLIST_H

#include <iostream>
#include <list.h>
#include <compare.h>

namespace fsu
{

  template <class T, class P>
  class MOList;

  template <class T, class P>
  class UOList;

  template <class T, class P>
  class OListIterator;

  template<typename T, class P> 
  bool operator == (const MOList<T,P>& x1, const MOList<T,P>& x2);

  template<typename T, class P> 
  bool operator != (const MOList<T,P>& x1, const MOList<T,P>& x2);

  template <typename T, class P>
  std::ostream& operator << (std::ostream& os, const MOList<T,P>& x);

  //----------------------------------
  //     MOList<T,P>
  //----------------------------------

  template < typename T , class P = LessThan < T > >
  class MOList
  {
  public:
    typedef T                         ValueType; 
    typedef P                         PredicateType;
    typedef T*                        PointerType;
    typedef const T*                  ConstPointerType;
    typedef T&                        ReferenceType;
    typedef const T&                  ConstReferenceType;
    typedef MOList < T , P>           ContainerType;
    typedef OListIterator < T , P >   Iterator;
    typedef OListIterator < T , P >   ConstIterator;

    friend bool operator == <> (const MOList<T,P>& x1, const MOList<T,P>& x2);

    // mutating the set
    bool     Insert    (const T& t);  // insert at lower bound
    bool     Insert    (Iterator& i, const T& t);  // insert at i if structure OK
    size_t   Remove    (const T& t);  // remove all copies of t
    bool     Remove    (Iterator& i); // remove item at i
    void     Clear     ();            // make list empty

    // these list methods are order-safe and convenient to keep:
    bool     PopFront  () { return list_.PopFront(); }    // "DeleteMin"
    bool     PopBack   () { return list_.PopBack(); }     // "DeleteMax"
    const T& Front     () const { return list_.Front(); } // "Min"
    const T& Back      () const { return list_.Back(); }  // "Max"
    
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
    MOList<T,P>& operator  = (const MOList<T,P>& x);

    // constructors
             MOList  ();
    explicit MOList  ( PredicateType );
             MOList  ( const MOList& );
    virtual  ~MOList ();

    // Provide access to predicate - but don't allow modification
    const P& GetPredicate() const;

    // generic output
    void Display (std::ostream& os, char ofc = '\0') const;
    void Dump    (std::ostream& os, char ofc = '\0') const;

    // structural tests
    bool CheckMOList(bool verboseFlag = 0) const;
    bool CheckUOList(bool verboseFlag = 0) const;

  protected:
    List<T>  list_;
    P        pred_;

  } ; // class MOList<T,P>

  //----------------------------------
  //     OListIterator<T,P>
  //----------------------------------

  /*
    An ordered list iterator is just a wrapper on a positional list
    ConstIterator. The types Iterator and ConstIterator are the same, since we
    don't allow OList iteratrors to return mutable values.
  */

  template <typename T, class P = LessThan<T> >
  class OListIterator
  {
  public:
    typedef T                         ValueType; 
    typedef P                         PredicateType;
    typedef T*                        PointerType;
    typedef const T*                  ConstPointerType;
    typedef T&                        ReferenceType;
    typedef const T&                  ConstReferenceType;
    typedef MOList < T , P>           ContainerType;
    typedef OListIterator < T , P >   Iterator;
    typedef OListIterator < T , P >   ConstIterator;

                 OListIterator   ();
                 OListIterator   (const OListIterator&);
                 OListIterator   (const ListIterator<T>&iter);
    virtual      ~OListIterator  ();

    OListIterator&  operator=    (const OListIterator&);

    bool              Valid      () const;

    bool              operator== (const OListIterator&) const;
    bool              operator!= (const OListIterator&) const;

    const T&          operator*  () const;

    OListIterator&  operator++   ();
    OListIterator   operator++   (int);
    OListIterator&  operator--   ();
    OListIterator   operator--   (int);

  private:
    typename List<T>::ConstIterator  iter_;
    friend class MOList<T,P>;
    friend class UOList<T,P>;
  };

  //----------------------------------
  //     UOList<T,P>
  //----------------------------------

  /*
     The change in semantics from multi- to uni-modal requires only one
     over-ride - to Insert. All other operations are inherited. The Iterator
     class is re-used in its entirety. 

     Of course, constructors, destrtctor, and assignment require their own
     implementations.

     The operations are left in the definition - commented out - to remind the
     user what the interface is.
  */

  template < typename T , class P = LessThan < T > >
  class UOList : public MOList < T , P >
  {
  public:
    typedef T                        ValueType; 
    typedef P                        PredicateType;
    typedef T*                       PointerType;
    typedef const T*                 ConstPointerType;
    typedef T&                       ReferenceType;
    typedef const T&                 ConstReferenceType;
    typedef UOList < T , P>          ContainerType;
    typedef OListIterator < T , P >  Iterator;
    typedef OListIterator < T , P >  ConstIterator;
    // typedef typename OListIterator <T,P>::ReverseIterator      ReverseIterator;
    // typedef typename OListIterator <T,P>::ConstReverseIterator ConstReverseIterator;

    // friend bool operator == <> (const UOList<T,P>& x1, const UOList<T,P>& x2);

    bool     Insert    (const T& t);  // insert at lower bound
    bool     Insert    (Iterator& i, const T& t);  // insert at i if *i == t

    // size_t   Remove    (const T& t);  // remove all copies of t
    // bool     Remove    (Iterator& i); // remove item at i
    // void     Clear     ();            // make list empty

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
    UOList<T,P>& operator  = (const UOList<T,P>& x);

    // constructors
             UOList  ();
    explicit UOList  ( PredicateType );
             UOList  ( const UOList& );
    virtual  ~UOList ();

    // Provide access to predicate - but don't allow modification
    // const P& GetPredicate() const;

    // generic output
    // void Display (std::ostream& os, char ofc = '\0') const;
    // void Dump    (std::ostream& os, char ofc = '\0') const;

    // structural tests
    // void CheckMOList(bool verboseFlag = 0) const;
    // void CheckUOList(bool verboseFlag = 0) const;

  } ; // class UOList<T,P>

  //-----------------------------------
  //     TXOList<T,P>:: Implementations
  //-----------------------------------

  // non-member operators

  template<typename T, class P> 
  bool operator == (const MOList<T,P>& x1, const MOList<T,P>& x2)
  {
    return ( ( x1.list_ == x2.list_ ) && (x1.pred_ == x2.pred_) );
  }

  /******** derived class overload ********/
  template<typename T, class P> 
  bool operator == (const UOList<T,P>& x1, const UOList<T,P>& x2)
  {
    return (MOList<T,P>)x1 == (MOList<T,P>)x2;
  }
  /****************************************/

  template<typename T, class P> 
  bool operator != (const MOList<T,P>& x1, const MOList<T,P>& x2)
  {
    return !(x1 == x2);
  }

  /******** derived class overload ********/
  template<typename T, class P> 
  bool operator != (const UOList<T,P>& x1, const UOList<T,P>& x2)
  {
    return !(x1 == x2);
  }
  /****************************************/

  template <typename T, class P>
  void MOList<T,P>::Display (std::ostream& os, char ofc) const
  {
    list_.Display(os,ofc);
  }

  template <typename T, class P>
  void MOList<T,P>::Dump (std::ostream& os, char ofc) const
  {
    os << "Contents: ";
    Display(os,ofc);
    os << '\n';
  }

  template <typename T, class P>
  std::ostream& operator << (std::ostream& os, const MOList<T,P>& x)
  {
    x.Display(os);
    return os;
  }

  /******** derived class overload ********/
  template <typename T, class P>
  std::ostream& operator << (std::ostream& os, const UOList<T,P>& x)
  {
    x.Display(os);
    return os;
  }
  /****************************************/

  // structural tests
  template <typename T, class P>
  bool MOList<T,P>::CheckMOList(bool verboseFlag) const
  {
    if (Empty())
    {
      if (verboseFlag)
	std:: cout << "MOList is empty\n";
      return 1;
    }
    bool ok = 1;
    Iterator i = MOList<T,P>::Begin();
    Iterator j;
    size_t number = 0;
    for (j = i++; i != MOList<T,P>::End(); j = i++, ++number)
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
      std::cout << " ** CheckMUList: OK\n";
    return ok;
  }

  template <typename T, class P>
  bool MOList<T,P>::CheckUOList(bool verboseFlag) const
  {
    if (Empty())
    {
      if (verboseFlag)
	std:: cout << "UOList is empty\n";
      return 1;
    }
    bool ok = 1;
    Iterator i = MOList<T,P>::Begin();
    Iterator j;
    size_t number = 0;
    for (j = i++; i != MOList<T,P>::End(); j = i++, ++number)
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
      std::cout << " ** CheckOUList: OK\n";
    return ok;
  }

  // constructors & assignment

  template <typename T, class P>
  MOList<T,P>::MOList  () : list_(), pred_()
  {}

  template <typename T, class P>
  UOList<T,P>::UOList  () : MOList<T,P> ()
  {}

  template <typename T, class P>
  MOList<T,P>::MOList  (P p) : list_(), pred_(p)
  {}

  template <typename T, class P>
  UOList<T,P>::UOList  (P p) : MOList<T,P>(p)
  {}

  template <typename T, class P>
  MOList<T,P>::MOList  (const MOList<T,P>& x) : list_(x.list_), pred_(x.pred_)
  {}

  template <typename T, class P>
  UOList<T,P>::UOList  (const UOList<T,P>& x) : MOList<T,P>(x)
  {}

  template <typename T, class P>
  MOList<T,P>& MOList<T,P>::operator  = (const MOList<T,P>& x)
  {
    if (this != &x)
    {
      list_ = x.list_;
      pred_ = x.pred_;
    }
    return *this;
  }

  template <typename T, class P>
  UOList<T,P>& UOList<T,P>::operator  = (const UOList<T,P>& x)
  {
    MOList<T,P>::operator=(x);
    return *this;
  }

  template <typename T, class P>
  MOList<T,P>::~MOList ()
  {}

  template <typename T, class P>
  UOList<T,P>::~UOList ()
  {}

  // iterator support

  template <typename T, class P>
  OListIterator<T,P> MOList<T,P>::Begin() const
  {
    Iterator i;
    i.iter_ = list_.Begin(); // const version of List::Begin called here
    return i;
  }

  template <typename T, class P>
  OListIterator<T,P> MOList<T,P>::End() const
  {
    Iterator i;
    i.iter_ = list_.End(); // const version of List::End called here
    return i;
  }

  template <typename T, class P>
  OListIterator<T,P> MOList<T,P>::rBegin() const
  {
    Iterator i;
    i.iter_ = list_.rBegin(); // const version of List::Begin called here
    return i;
  }

  template <typename T, class P>
  OListIterator<T,P> MOList<T,P>::rEnd() const
  {
    Iterator i;
    i.iter_ = list_.rEnd(); // const version of List::Begin called here
    return i;
  }

  template <typename T, class P>
  size_t MOList<T,P>::Size() const
  {
    return list_.Size();
  }

  template <typename T, class P>
  bool MOList<T,P>::Empty() const
  {
    return list_.Empty();
  }

  template <typename T, class P>
  void MOList<T,P>::Clear()
  {
    return list_.Clear();
  }

  template <typename T, class P>
  const P& MOList<T,P>::GetPredicate() const
  {
    return pred_;
  }

  template <typename T, class P>
  bool MOList<T,P>::Insert (const T& t)
  // multimodal - insert at upper bound
  // uses sequential search
  {
    typename List<T>::Iterator iter = list_.Begin();
    while (iter != list_.End() && !pred_(t,*iter)) // (*i <= t))
      ++iter;
    iter = list_.Insert(iter,t);
    return (iter != list_.End());
  }

  /******** derived class overload ********/
  template <typename T, class P>
  bool UOList<T,P>::Insert (const T& t)
  // unimodal - insert at lower bound
  // uses sequential search
  {
    typename List<T>::Iterator iter = MOList<T,P>::list_.Begin();
    while (iter != MOList<T,P>::list_.End() && this->pred_(*iter,t)) 
      ++iter;
    if (iter.Valid() && iter!= this->list_.End() && iter != this->list_.rEnd() && *iter == t)
    {
      *iter = t;
      return 1;
    }
    iter = this->list_.Insert(iter,t);
    return (iter != this->list_.End());
  }
  /****************************************/

  template <typename T, class P>
  bool MOList<T,P>::Insert (Iterator& i, const T& t)
  // insert at i if order is preserved (multimodal insert)
  {
    if (list_.Empty())
    {
      return list_.PushFront(t);
    }
    if (!i.Valid() || i == rEnd()) // can't make sense of request
    {
      return 0;
    }
    if (i == Begin() && !pred_(*i,t)) // t <= *i
    {
      return list_.PushFront(t);
    }
    if (i == End() && !pred_(t,list_.Back())) // Back() <= t
    {
      return list_.PushBack(t);
    }
    // now i is not at front or back
    // check for correct order (<=)
    Iterator before = i;
    --before;
    if(!pred_(t,*before) && !pred_(*i,t)) // (*before <= t && t <= *i)
    {
      i.iter_ = list_.Insert (i.iter_,t);
      return i.Valid() && i != End();
    }
    return 0;
  }

  /******** derived class overload ********/
  template <typename T, class P>
  bool UOList<T,P>::Insert (Iterator& i, const T& t)
  // insert at i if order is preserved (unimodal insert)
  {
    // first take care of the over-write case:
    if (i.Valid() && i != this->rEnd() && i != this->End() && (*i == t))
    {
      const_cast<T&>(*i) = t;  // break const-ness to assign to read-only location
      return 1;
    }

    // now the algorithm is the same as the multimodal case, except with strict <
    if (this->list_.Empty())
    {
      return this->list_.PushFront(t);
    }
    if (!i.Valid() || i == this->rEnd()) // can't make sense of request
    {
      return 0;
    }
    if (i == this->Begin())
    {
      if (this->pred_(t,*i)) // t < *i
	return this->list_.PushFront(t);
      else 
	return 0;
    }
    if (i == this->End())
    {
      if (this->pred_(this->list_.Back(),t)) // Back() < t
	return this->list_.PushBack(t);
      else
	return 0;
    }

    // now i is not at front or back
    // check for correct order (<)
    Iterator before = i;
    --before; 
    if(this->pred_(*before,t) && this->pred_(t,*i)) // (*before < t && t < *i)
    {
      i.iter_ = this->list_.Insert (i.iter_,t);
      return (i.Valid() && i != this->End());
    }
    return 0;
  }
  /****************************************/

  template <typename T, class P>
  size_t MOList<T,P>::Remove (const T& t)
  // remove all copies of t
  // uses sequential search
  {
    typename List<T>::Iterator iter = list_.Begin();
    while (iter != list_.End() && pred_(*iter,t)) // find lower bound
      ++iter;
    size_t count = 0;
    while (iter!= list_.End() && *iter == t) // remove contiguous elements
    {
      list_.Remove(iter);
      ++count;
    }
    return count;
  }

  template <typename T, class P>
  bool MOList<T,P>::Remove (Iterator& i)
  // remove item at i
  {
    if (i.Valid())
    {
      list_.Remove(i.iter_);
      return 1;
    }
    return 0;
  }

  template <typename T, class P>
  typename MOList<T,P>::Iterator MOList<T,P>::LowerBound (const T& t) const
  // return lower bound
  // Defn: lower bound points to the first item on the list >= t
  // uses sequential search
  {
    Iterator i = Begin();
    while (i != End() && pred_(*i,t)) // (*i < t))
      ++i;
    return i;
  }

  template <typename T, class P>
  typename MOList<T,P>::Iterator MOList<T,P>::UpperBound (const T& t) const
  // return upper bound
  // Defn: upper bound points to the first item on the list > t
  // uses sequential search
  {
    Iterator i = Begin();
    while (i != End() && !pred_(t,*i)) // (*i <= t))
      ++i;
    return i;
  }

  template <typename T, class P>
  typename MOList<T,P>::Iterator MOList<T,P>::Includes (const T& t) const
  // return LowerBound(t) if found, End() otherwise
  // uses sequential search (indirectly)
  {
    Iterator i = LowerBound(t);
    if (i != End() && (*i == t))
      return i;
    return End();
  }

  //-------------------------------------------
  //     OListIterator<T,P>:: Implementations
  //-------------------------------------------

  //Constructors, destructor, and assignment operator.

  template <typename T, class P>
  OListIterator<T,P>::OListIterator() : iter_()
  {}

  template <typename T, class P>
  OListIterator<T,P>::OListIterator(const OListIterator<T,P>& i) : iter_(i.iter_)
  {}

  template <typename T, class P>
  OListIterator<T,P>::OListIterator(const ListIterator<T>&iter) : iter_(iter)
  {}

  template <typename T, class P>
  OListIterator<T,P>::~OListIterator()
  {}

  template <typename T, class P>
  OListIterator<T,P>& OListIterator<T,P>::operator=(const OListIterator<T,P>& i)
  {
    iter_ = i.iter_;
    return *this;
  }

  //Returns 1 if the iterator is valid, 0 otherwise.
  template <typename T, class P>
  bool OListIterator<T,P>::Valid() const
  {
    return iter_.Valid();
  }

  //Decides if two iterators are equal.
  template <typename T, class P>
  bool OListIterator<T,P>::operator==(const OListIterator<T,P>& i) const
  {
    return (iter_ == i.iter_);
  }

  //Decides if two iterators are not equal.
  template <typename T, class P>
  bool OListIterator<T,P>::operator!=(const OListIterator<T,P>& i) const
  {
    return (iter_ != i.iter_);
  }

  //Returns a const reference to a node value.
  template <typename T, class P>
  const T& OListIterator<T,P>::operator*() const
  {
    return *iter_;
  }

  //Increments the iterator using in-order rules.
  template <typename T, class P>
  OListIterator<T,P>& OListIterator<T,P>::operator++()
  {
    ++iter_;
    return *this;
  }

  //Postfix version.
  template <typename T, class P>
  OListIterator<T,P> OListIterator<T,P>::operator++(int)
  {
    OListIterator<T,P> i = *this;
    operator++();
    return i;
  }

  //Decrements the iterator using in-order rules.
  template <typename T, class P>
  OListIterator<T,P>& OListIterator<T,P>::operator--()
  {
    --iter_;
    return *this;
  }

  //Postfix version.
  template <typename T, class P>
  OListIterator<T,P> OListIterator<T,P>::operator--(int)
  {
    OListIterator<T,P> i = *this;
    operator--();
    return i;
  }

} // namespace fsu
#endif
