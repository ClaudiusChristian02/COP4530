/*
    deque_ca.h
    01/01/12
    Chris Lacher

    Parametrized double-ended queue class
    (deque, pronounced "deck")

    ASSUMPTIONS ON TYPE T:

    Deque<T> assumes that T has overloads of the following
    operators and functions:

       insertion  (output) operator    <<  
       assignment          operator    =
       constructor                     T()
       destructor                      ~T()

    A copy constructor for T is not used.

    Efficiency Requirements: 

    1. Each of the container class operations

          PushFront(), PopFront(), PushBack(), PopBack(),
          Empty(), Size(), Clear(), Front(), Back(), and
          operator []()

       has amortized runtime O(1) and runspace <= O(size)

    2. Each Iterator operation has runtime O(1) and runspace O(1)

    Copyright 2012, R.C. Lacher
*/

#ifndef _DEQUE_H
#define _DEQUE_H

#include <iostream>
#include <cstdlib> // size_t

namespace fsu
{

  template <typename T>
  class Deque;

  template <typename T>
  class DequeIterator;

  template <typename T>
  class ConstDequeIterator;

  //----------------------------------
  //     Deque<T>
  //----------------------------------

  template <typename T>
  class Deque
  {
  public:
    // scope Deque<T>:: type definitions
    typedef T                               ValueType;
    typedef T*                              PointerType;
    typedef const T*                        ConstPointerType;
    typedef T&                              ReferenceType;
    typedef const T&                        ConstReferenceType;
    typedef Deque < T >                     ContainerType;
    typedef DequeIterator < T >             Iterator;
    typedef ConstDequeIterator < T >        ConstIterator;

    // constructors - specify size and an initial value
    Deque  ();
    Deque  (size_t, const T&); // sets capacity and initializing value for footprint
    Deque  (const Deque<T>&);     

    // destructor
    virtual ~Deque();

    // member operators
    Deque<T>& operator =  (const Deque<T>&);
    T&        operator [] (size_t);
    const T&  operator [] (size_t) const;

    // Container class protocol
    bool      Empty       () const;
    size_t    Size        () const;
    bool      PushFront   (const T&);
    bool      PopFront    ();
    bool      PushBack    (const T&);
    bool      PopBack     ();
    void      Clear       ();
    T&        Front       ();
    T&        Back        ();
    const T&  Front       () const;
    const T&  Back        () const;

    // Iterator support
    Iterator      Begin       () ;
    ConstIterator Begin       () const;
    Iterator      End         () ;
    ConstIterator End         () const;
    Iterator      rBegin      () ;
    ConstIterator rBegin      () const;
    Iterator      rEnd        () ;
    ConstIterator rEnd        () const;

    // Generic display methods 
    void Display    (std::ostream& os, char ofc = '\0') const;
    void Dump       (std::ostream& os) const;

  protected:
    // classic circular array implementation
    T* content_;
    size_t contentSize_, beg_, end_;
  } ;

  // operator overloads (friend status not required)

  template < class T >
  std::ostream& operator << (std::ostream& os, const Deque<T>& a);

  template < class T >
  bool     operator == (const Deque<T>&, const Deque<T>&); 

  template < class T >
  bool     operator != (const Deque<T>&, const Deque<T>&); 

  //----------------------------------
  //     DequeIterator<T>
  //----------------------------------

  template <typename T>
  class DequeIterator
  {
    friend class Deque<T>;
    friend class ConstDequeIterator<T>;

  public:
    // terminology support

    typedef T                               ValueType;
    typedef T*                              PointerType;
    typedef const T*                        ConstPointerType;
    typedef T&                              ReferenceType;
    typedef const T&                        ConstReferenceType;
    typedef Deque < T >                     ContainerType;
    typedef DequeIterator < T >             Iterator;
    typedef ConstDequeIterator < T >        ConstIterator;

    // constructors
    DequeIterator      ();
    explicit DequeIterator      (const Deque<T>& Q); // depracated
    DequeIterator      (const Iterator& I);

    // legal to de-reference?
    bool       Valid           () const; // cursor is valid element

    // various operators
    bool      operator == (const Iterator& I2) const;
    bool      operator != (const Iterator& I2) const;
    T&        operator *  (); // Return reference to current Tval
    const T&  operator *  () const; // const version
    T&        operator [] (size_t i); // Return reference to Tval at index i
    const T&  operator [] (size_t i) const; // const version
    Iterator& operator =  (const Iterator & I);
    Iterator& operator ++ ();    // prefix
    Iterator  operator ++ (int); // postfix
    Iterator& operator -- ();    // prefix
    Iterator  operator -- (int); // postfix

    // "pointer" arithmetic

    // template <typename N>
    long      operator -  (const Iterator & I2) const;

    template <typename N>
    Iterator& operator += (N n);

    template <typename N>
    Iterator& operator -= (N n);

    template <typename N>
    Iterator  operator +  (N n) const;

    template <typename N>
    Iterator  operator -  (N n) const;

  protected:
    const Deque<T>* dequePtr_;
    size_t          indexBase_;
  } ;

  template <typename T>
  class ConstDequeIterator
  {
    friend class Deque<T>;

  public:
    // terminology support

    typedef T                               ValueType;
    typedef T*                              PointerType;
    typedef const T*                        ConstPointerType;
    typedef T&                              ReferenceType;
    typedef const T&                        ConstReferenceType;
    typedef Deque < T >                     ContainerType;
    typedef DequeIterator < T >             Iterator;
    typedef ConstDequeIterator < T >        ConstIterator;

    // constructors
    ConstDequeIterator      ();
    explicit ConstDequeIterator      (const Deque<T>& Q); // depracated
    ConstDequeIterator      (const ConstIterator& I);

    // type converter
    ConstDequeIterator      (const Iterator& I);

    bool       Valid           () const; // cursor is valid element

    // various operators
    bool           operator == (const ConstIterator& I2) const;
    bool           operator != (const ConstIterator& I2) const;
    const T&       operator *  () const; // const version
    const T&       operator [] (size_t i) const; // const version
    ConstIterator& operator =  (const ConstIterator & I);
    ConstIterator& operator ++ ();    // prefix
    ConstIterator  operator ++ (int); // postfix
    ConstIterator& operator -- ();    // prefix
    ConstIterator  operator -- (int); // postfix

    // "pointer" arithmetic

    // template <typename N>
    long      operator -  (const ConstIterator & I2) const;

    template <typename N>
    ConstIterator& operator += (N n);

    template <typename N>
    ConstIterator& operator -= (N n);

    template <typename N>
    ConstIterator  operator +  (N n) const;

    template <typename N>
    ConstIterator  operator -  (N n) const;

  protected:
    const Deque<T>* dequePtr_;
    size_t          indexBase_;
  } ;

  #include <deque.cpp>

} // namespace fsu

#endif
