/*
    insert.h
    01/01/12
    Chris Lacher

    Insert iterator adaptors

    These are strange (but useful) beasts. They create an iterator satisfying the
    forward iterator pattern (hence usable in lots of generic algorithms) but
    with insert semantics for operator =(). They are narrow in purpose: to
    receive data and insert it into a container. 

    Note that a template function is provided for each type to facilitate
    creation of the type. For example, suppose we have these declarations:

      fsu::Deque < int >                      d;

    and want a PushBackIterator p to iterate d.
    We can use the class to declare as follows:

      fsu::PushBackIterator < fsu::Deque < int > > p(d);

    Then for any subsequent uses of p, for d or any other of the same type, we can
    use the helper function template as follows:

      p = fsu::BackPusher(d);

    Copyright 2012, R.C. Lacher
*/

#ifndef _FSU_INSERT_H
#define _FSU_INSERT_H

namespace fsu
{

  template <class C>
  class PushBackIterator
  {
  public:
    explicit PushBackIterator (C& x) : Cptr(&x) {}
    PushBackIterator (const PushBackIterator& I) :  Cptr(I.Cptr){}
    PushBackIterator <C>& operator = (const typename C::ValueType& t)
    {
      Cptr -> PushBack(t);
      return *this;
    }
    PushBackIterator<C>& operator *  ()    {return *this;}
    PushBackIterator<C>& operator ++ ()    {return *this;}
    PushBackIterator<C>& operator ++ (int) {return *this;}

  protected:
    C* Cptr;
  };

  // This stand-alone function is useful, returning a PushBackIterator of the
  // correct type without having to specify a template parameter.
  // Note, the PushBackIterator variable must have been declared prior to call
  // of this function.

  template <class C>
  PushBackIterator<C> BackPusher (C& x)
  {
    return PushBackIterator <C> (x);
  }

  template <class C>
  class PushFrontIterator
  {
  public:
    explicit PushFrontIterator (C& x) : Cptr(&x) {}
    PushFrontIterator (const PushFrontIterator& I) :  Cptr(I.Cptr){}
    PushFrontIterator <C>& operator = (const typename C::ValueType& t)
    {
      Cptr -> PushFront(t);
      return *this;
    }
    PushFrontIterator<C>& operator *  ()    {return *this;}
    PushFrontIterator<C>& operator ++ ()    {return *this;}
    PushFrontIterator<C>& operator ++ (int) {return *this;}

  protected:
    C* Cptr;
  };

  // This stand-alone function is useful, returning a PushFrontIterator of the
  // correct type without having to specify a template parameter.
  // Note, the PushFrontIterator variable must have been declared prior to call
  // of this function.

  template <class C>
  PushFrontIterator<C> FrontPusher (C& x)
  {
    return PushFrontIterator <C> (x);
  }

  template <class C>
  class InsertIterator
  {
  public:
    explicit InsertIterator (C& x) : Cptr(&x) {}
    InsertIterator (const InsertIterator& I) :  Cptr(I.Cptr){}
    InsertIterator <C>& operator = (const typename C::ValueType& t)
    {
      Cptr -> Insert(t);
      return *this;
    }
    InsertIterator<C>& operator *  ()    {return *this;}
    InsertIterator<C>& operator ++ ()    {return *this;}
    InsertIterator<C>& operator ++ (int) {return *this;}

  protected:
    C* Cptr;
  };

  // This stand-alone function is useful, returning an InsertIterator of the
  // correct type without having to specify a template parameter.
  // Note, the InsertIterator variable must have been declared prior to call
  // of this function.

  template <class C>
  InsertIterator<C> Inserter (C& x)
  {
    return InsertIterator <C> (x);
  }

} // namespace fsu

#endif
