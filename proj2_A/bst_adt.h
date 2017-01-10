/*
    bst_adt.h

*/

#ifndef _BST_ADT_H
#define _BST_ADT_H

#include <bst_base.h>

namespace fsu
{
  template < typename T, class P = LessThan<T> >
  class BST_ADT : public BST_BASE<T,P>
  {
  public:

    typedef T    ValueType;
    typedef P    PredicateType;
    typedef InorderBTIterator     < BST_ADT <T,P> > InorderIterator;
    typedef LevelorderBTIterator  < BST_ADT <T,P> > LevelorderIterator;
    typedef PreorderBTIterator    < BST_ADT <T,P> > PreorderIterator;
    typedef PostorderBTIterator   < BST_ADT <T,P> > PostorderIterator;
    typedef ThreadedBTIterator    < BST_ADT <T,P> > ThreadedIterator;

    typedef InorderBTIterator     < BST_ADT <T,P> > Iterator;

             BST_ADT  ();
    explicit BST_ADT  (P p);
             BST_ADT  (const BST_ADT& b);
    virtual  ~BST_ADT ();
    BST_ADT& operator=(const BST_ADT& b);

    LevelorderIterator BeginLevelorder () const;
    LevelorderIterator EndLevelorder   () const;

    Iterator Begin  () const;
    Iterator End    () const;
    Iterator rBegin () const;
    Iterator rEnd   () const;

    Iterator LowerBound (const T&) const;
    Iterator UpperBound (const T&) const;
    Iterator Includes   (const T&) const;

    void Insert (Iterator i, const T& t);  // insert with a hint
    void Insert (const T& t); // needed to disambiguate "Insert"

  protected: // definitions and family
    friend class InorderBTIterator    < BST_ADT <T,P> >;
    friend class LevelorderBTIterator < BST_ADT <T,P> >;
    friend class PreorderBTIterator   < BST_ADT <T,P> >;
    friend class PostorderBTIterator  < BST_ADT <T,P> >;
    friend class ThreadedBTIterator   < BST_ADT <T,P> >;
    typedef typename BST_BASE<T,P>::Node Node;

  private: // methods
    // no methods introduced

  }; // class BST_ADT<>
  
  // define equality in terms of Iterator type (which may vary)
  template < typename T , class P > 
  bool operator == (const BST_ADT<T,P>& b1, const BST_ADT<T,P>& b2)
  {
    if (&b1 == &b2) return 1;
    typename BST_ADT<T,P>::Iterator i1 = b1.Begin(), i2 = b2.Begin();
    while (i1!= b1.End() && i2 != b2.End())
      if (*(i1++) != *(i2++))             // trees have different elements
        return 0;
    if (i1 != b1.End() || i2 != b2.End()) // trees are not the same size
      return 0;
    return 1;
  }

  template < typename T , class P > 
  bool operator != (const BST_ADT<T,P>& b1, const BST_ADT<T,P>& b2)
  {
    return !(b1 == b2);
  }

  // proper type
  
  template < typename T , class P >
  BST_ADT<T,P>::BST_ADT  () : BST_BASE<T,P>()
  {}

  template < typename T , class P >
  BST_ADT<T,P>::BST_ADT  (P p) : BST_BASE<T,P>(p)
  {}

  template < typename T , class P >
  BST_ADT<T,P>::~BST_ADT ()
  {
    this->Clear();
  }

  // make copies: these require a cloning mechanism - problematic for threaded trees
  template < typename T , class P >
  BST_ADT<T,P>::BST_ADT  ( const BST_ADT& that ) : BST_BASE<T,P>(that)
  {}

  template < typename T , class P >
  BST_ADT<T,P>& BST_ADT<T,P>::operator=( const BST_ADT& that )
  {
    BST_BASE<T,P>::operator=(that);
    return *this;
  }

  // Iterator support methods

  template < typename T , class P >
  typename BST_ADT<T,P>::LevelorderIterator BST_ADT<T,P>::BeginLevelorder() const
  {
    LevelorderIterator i;
    i.Init(this->root_);
    return i;
  }

  template < typename T , class P >
  typename BST_ADT<T,P>::LevelorderIterator BST_ADT<T,P>::EndLevelorder() const
  {
    LevelorderIterator i;
    return i;
  }

  template < typename T , class P >
  typename BST_ADT<T,P>::Iterator BST_ADT<T,P>::Begin() const
  {
    Iterator i;
    i.Init(this->root_);
    return i;
  }

  template < typename T , class P >
  typename BST_ADT<T,P>::Iterator BST_ADT<T,P>::End() const
  {
    Iterator i;
    return i;
  }

  template < typename T , class P >
  typename BST_ADT<T,P>::Iterator BST_ADT<T,P>::rBegin() const
  {
    Iterator i;
    i.rInit(this->root_);
    return i;
  }

  template < typename T , class P >
  typename BST_ADT<T,P>::Iterator BST_ADT<T,P>::rEnd() const
  {
    Iterator i;
    return i;
  }

  // the Iterator locator methods 

  template < typename T , class P >
  typename BST_ADT<T,P>::Iterator BST_ADT<T,P>::LowerBound ( const T& t ) const
  {
    if (this->root_ == nullptr)
      return End();

    Iterator l = End();
    Node * n = this->root_;
    Node * currentLB = nullptr;

    bool finished = 0;
    while (! finished)
    {
      l.stk_.Push(n);
      if (!this->pred_(n->value_,t)) // t <= n
      {
        currentLB = n;
        if (n->HasLeftChild())
          n = n->lchild_;
        else
          finished = 1;
      }
      else // t > n
      {
        if (n->HasRightChild())
          n = n->rchild_;
        else
          finished = 1;
      }
    }
    // retreat to last accepted location
    while (!l.stk_.Empty() && currentLB != l.stk_.Top())
      l.stk_.Pop();

    // take care of dead node case
    if (l.Valid() && l.stk_.Top()->IsDead())
      ++l;
    return l;
  }

  template < typename T , class P >
  typename BST_ADT<T,P>::Iterator BST_ADT<T,P>::UpperBound ( const T& t ) const
  {
    //std::cout << "ADT UpperBound requires implementation!\n";
	for (Iterator u = Begin(); u != End(); ++u){

		if (*u > t){

			return u;
		}
	}
    return End();
  }

  template < typename T , class P >
  typename BST_ADT<T,P>::Iterator BST_ADT<T,P>::Includes ( const T& t ) const
  {
    Iterator i;
    Node* n = this->root_;
    i.stk_.Clear();
    while (n != nullptr)
    {
      i.stk_.Push(n);
      if (this->pred_(t,*i))
      {
        n = n->lchild_;
      }
      else if  (this->pred_(*i,t))
      {
        n = n->rchild_;
      }
      else // found
      {
        if (n->IsAlive())
          return i;
        else
          return End();
      }
    }
    return End();
  }

  template < typename T , class P >
  void BST_ADT<T,P>::Insert (const T& tval)
  {
    BST_BASE<T,P>::Insert(tval);
  }

  // Insert with a hint
  template < typename T , class P >
  void BST_ADT<T,P>::Insert (Iterator i, const T& tval)
  {
    if (i.Valid() && tval == *i)
    {
      i.stk_.Top()->value_ = tval;
      i.stk_.Top()->SetAlive();
      return;
    }
    BST_BASE<T,P>::Insert(tval);
  }

} // namespace fsu 

#endif

