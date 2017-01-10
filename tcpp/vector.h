/*
    vector.h
    01/01/12
    Chris Lacher

    fsu::Vector

    Copyright 2012
*/

#ifndef _VECTOR_H
#define _VECTOR_H

#include <iostream>
#include <cstdlib>    // EXIT_FAILURE, size_t
#include <genalg.h>   // fsu::Swap(x,y)

namespace fsu
{

  // declare classes
  template <typename T>
  class Vector;

  // operator overloads (friend status not required)

  template < class T >
  std::ostream& operator << (std::ostream& os, const Vector<T>& a);

  template < class T >
  bool     operator == (const Vector<T>&, const Vector<T>&); 

  template < class T >
  bool     operator != (const Vector<T>&, const Vector<T>&); 

  //----------------------------------
  //     Vector<T>
  //----------------------------------

  template <typename T>
  class Vector
  {
  public:
    // scope Vector<T>:: type definitions
    typedef T                  ValueType;
    typedef T&                 ReferenceType;
    typedef const T&           ConstReferenceType;
    typedef T*                 Iterator;
    typedef const T*           ConstIterator;


    // constructors - specify size and an initial value
    Vector  ();                      // vector of size = 0 and capacity = defaultCapacity
    explicit Vector (size_t sz);     // vector of size = capacity = sz ...
    Vector  (size_t sz, const T& t); // ... and all elements = t
    Vector  (const Vector<T>&);      // copy constructor
    virtual ~Vector ();              // destructor

    // member operators
    Vector<T>&          operator =  (const Vector<T>&); // assignment operator
    Vector<T>&          operator += (const Vector<T>&); // expand to append argument
    ReferenceType       operator [] (size_t);            // bracket operator
    ConstReferenceType  operator [] (size_t) const;      // const version

    // other methods
    bool     SetSize     (size_t);    // set size as specified, change capacity iff needed
    bool     SetSize     (size_t, const T&); // ... and initialize new elements
    bool     SetCapacity (size_t);    // force capacity change (up or down)
    size_t   Size        () const;    // return size
    size_t   Capacity    () const;    // return capacity

    // Container class protocol
    bool     Empty       () const;    // 1 iff empty
    bool     PushBack    (const T&);  // expand by 1 new element appended at back
    bool     PopBack     ();          // contract by 1 from back
    void     Clear       ();          // make size = 0
    T&       Front       ();          // return front element (index 0)
    const T& Front       () const;    // cont version
    T&       Back        ();          // return back element (index Size() - 1)
    const T& Back        () const;    // const version

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

    enum { defaultCapacity = 10 };

    // swap data with annother vector
    void Swap (Vector<T>& v);

  protected:
    // variables
    size_t size_,        // current size of vector, 
           capacity_;    // size of data_ array
    T*     data_;        // pointer to the primative array elements

    // method
    static T*  NewArray (size_t);  // safe space allocator
  } ;

#include <vector.cpp> // "slave" file, included inside multiple read protection and namespace

}   // namespace fsu

#endif
