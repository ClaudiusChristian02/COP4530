/*
    stack.h
    Chris Lacher
    01/01/12

    The Stack < T, C > class
    An adaptor class using any container class C<T>

    ASSUMPTION: T and C::ValueType are the same type

    classes defined  in this file
    -----------------------------

    class Stack < T, C >              //  the primary ADT 

    container protocols used
    ------------------------

    constructor         C         ()
    destructor          ~C        ()
    void                PushBack  (const ValueType&)
    void                PopBack   ()
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

#ifndef _STACK_H
#define _STACK_H

#include <cstdlib>  // size_t
#include <iostream>
#include <deque.h>

namespace fsu
{

  template < typename T , class C >
  class Stack;

  template < typename T , class C = Deque < T > >
  class Stack
  {

  protected:
    C c_;

  public:
    typedef T ValueType;
    typedef C ContainerType;

    Stack()  :  c_()
    {}

    void Push(const ValueType& x)
    {
      c_.PushBack(x);
    }

    void Pop()
    // Pre:  !Empty()
    {
      c_.PopBack();
    }

    ValueType& Top()
    // Pre:   !Empty()
    {
      return c_.Back();
    }

    const ValueType& Top() const
    // Pre:   !Empty()
    // a const version of Top(0
    {
      return c_.Back();
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

    friend  bool operator == ( const fsu::Stack < T , C >& s1 ,  const fsu::Stack < T , C >& s2 )
    {
      return s1.c_ == s2.c_;
    }

    void Display(std::ostream& os, char ofc = '\0') const;
    // non-standard method, implemented outside of class definition

  } ;

  template < typename T , class C >
  bool operator != ( const fsu::Stack < T , C >& s1 ,  const fsu::Stack < T , C >& s2 )
  {
    return s1 != s2;
  }

  // The Display() method is provided because Stack<> has no iterator type to
  // facilitate output of stack contents.
  template < typename T , class C >
  void Stack <T,C>:: Display(std::ostream& os, char ofc) const
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
  std::ostream& operator << (std::ostream& os, const Stack<T,C>& s)
  {
    s.Display(os);
    return os;
  }

} // namespace fsu
#endif
