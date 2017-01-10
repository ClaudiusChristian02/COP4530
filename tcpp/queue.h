/*
    queue.h
    Chris Lacher
    01/01/12

    The Queue < T, C > class
    An adaptor class using any container class C<T>

    ASSUMPTION: T and C::ValueType are the same type

    classes defined  in this file
    -----------------------------

    class Queue < T, C >              //  the primary ADT 

    container protocols used
    ------------------------

    constructor         C         ()
    destructor          ~C        ()
    void                PushBack  (const ValueType&)
    void                PopFront  ()
    void                Clear     ()
    ValueType&          Back      ()
    const ValueType&    Back      () const
    bool                Empty     () const
    size_t              Size      () const
    C::ConstIterator    Begin     () const
    C::ConstIterator    End       () const

    plus forward iterator protocol needed for traversal of C objects

    Copyright 2012, R.C. Lacher
*/

#ifndef _QUEUE_H
#define _QUEUE_H

#include <cstdlib>  // size_t
#include <iostream>
#include <deque.h>

namespace fsu
{

  template < typename T , class C >
  class Queue;

  template < typename T , class C = Deque < T > >
  class Queue
  {

  protected:
    C c_;

  public:
    typedef T ValueType;
    typedef C ContainerType;

    Queue()  :  c_()
    {}

    void Push(const ValueType& x)
    {
      c_.PushBack(x);
    }

    void Pop()
    // Pre:  !Empty()
    {
      c_.PopFront();
    }

    ValueType& Front()
    // Pre:   !Empty()
    {
      return c_.Front();
    }

    const ValueType& Front() const
    // Pre:   !Empty()
    // a const version of Front
    {
      return c_.Front();
    }

    void Clear()
    {
      c_.Clear();
    }

    bool Empty()  const
    {
      return c_.Empty();
    }

    size_t Size() const
    {
      return c_.Size();
    }

    friend  bool operator == ( const fsu::Queue < T , C >& q1 ,  const fsu::Queue < T , C >& q2 )
    {
      return q1.c_ == q2.c_;
    }

    void Display(std::ostream& os, char ofc = '\0') const;
    // non-standard method, implemented outside of class definition
  } ;


  template < typename T , class C >
  bool operator== ( const fsu::Queue < T , C >& q1 ,  const fsu::Queue < T , C >& q2 )
  {
    return !(q1 == q2);
  }

  // The Display() method is provided because Queue<> has no iterator type to
  // facilitate output of queue contents.
  template < typename T , class C >
  void Queue <T,C>:: Display(std::ostream& os, char ofc) const
  {
    typename C::ConstIterator I;
    if (ofc == '\0')
      for (I = c_.Begin(); I != c_.End(); ++I)
	os << *I;
    else
      for (I = c_.Begin(); I != c_.End(); ++I)
	os << *I << ofc;
  }

  template < typename T , class C >
  std::ostream& operator << (std::ostream& os, const Queue<T,C>& s)
  {
    s.Display(os);
    return os;
  }

} // namespace fsu
#endif
