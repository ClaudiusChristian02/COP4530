/*
    bt2iter.h

    Implementations required:

    Levelorder:  Init, Increment
    Inorder:     Init, Increment, rInit, Decrement
    Threaded:    Init, Increment, rInit, Decrement

*/

#include <queue.h>     // LevelorderIterator,  Dump()
#include <stack.h>     // InorderIterator deque-based stack
#include <vector.h>    // InorderIterator alternative
#include <list.h>      // InorderIterator alternative
#include <debug.h>     // argh

#ifndef _BT2ITER_H
#define _BT2ITER_H

namespace fsu
{

  template < class C >
  class InorderBTIterator; // patterns: ConstIterator, BidirectionalIterator

  template < class C >
  class LevelorderBTIterator; // patterns: ConstIterator, ForwardIterator

  template < class C >
  class ThreadedBTIterator; // patterns: ConstIterator, BidirectionalIterator

  /******************************************************************/
  /*    LevelorderBTIterator < C >                                  */
  /******************************************************************/

  template < class C >
  class LevelorderBTIterator // patterns: ConstIterator, BidirectionalIterator
  {
  public: // terminology support
    typedef typename C::ValueType    ValueType;
    typedef typename C::Node         Node;
    typedef LevelorderBTIterator<C>  ConstIterator;
    typedef LevelorderBTIterator<C>  Iterator;

  private: // inner sanctum
    friend C;
    fsu::Queue < Node* > que_; // default is deque-based

  public:
    // first class
    LevelorderBTIterator                 () : que_() {}
    virtual  ~LevelorderBTIterator       () { que_.Clear(); }
    LevelorderBTIterator                 (const LevelorderBTIterator& i) : que_(i.que_) {}
    LevelorderBTIterator<C>&  operator=  (const LevelorderBTIterator& i) { que_ = i.que_; return *this; }

    // information/access
    bool  Valid   () const { return !que_.Empty(); } // cursor is valid element

    // various operators
    bool                      operator== (const LevelorderBTIterator& i2) const { return que_ == i2.que_; }
    bool                      operator!= (const LevelorderBTIterator& i2) const { return !(*this == i2); }
    const ValueType&          operator*  () const { return que_.Front()->value_; }
    LevelorderBTIterator<C>&  operator++ ();    // prefix
    LevelorderBTIterator<C>   operator++ (int); // postfix

  private:
    void Init      (Node* n);
    void Increment ();
  };

  template < class C >
  void LevelorderBTIterator<C>::Init(Node* n)
  {
	  que_.Push(n);

  }

  // pull front node from the queue and pushes
  template < class C >
  void LevelorderBTIterator<C>::Increment()
  {
	  Node* n = que_.Front();

	  if (n->HasLeftChild()){

		  que_.Push(n->lchild_);
	  }

	  if (n->HasRightChild()){

		  que_.Push(n->rchild_);
	  }

	  que_.Pop();

  } // end of void LevelorderBTIterator<C>::Increment()

  template < class C >
  LevelorderBTIterator<C>&  LevelorderBTIterator<C>::operator++ ()
  {
    // fsu::Debug("operator++()");
    do Increment();
    while (!que_.Empty() && que_.Front()->IsDead());
    return *this;
  }

  template < class C >
  LevelorderBTIterator<C>   LevelorderBTIterator<C>::operator++ (int)
  {
    LevelorderBTIterator<C> i(*this);
    this->operator++();
    return i;
  }

  /******************************************************************/
  /*    InorderBTIterator < C >                                     */
  /******************************************************************/

  template < class C >
  class InorderBTIterator // patterns: ConstIterator, BidirectionalIterator
  {
  public: // terminology support
    typedef typename C::ValueType    ValueType;
    typedef typename C::Node         Node;
    typedef InorderBTIterator<C>     ConstIterator;
    typedef InorderBTIterator<C>     Iterator;

  private: // inner sanctum
    friend C;
    // fsu::Stack < Node* > stk_; // default is deque-based - better safety & error detection
    fsu::Stack < Node* , fsu::Vector < Node* > > stk_; // faster

  public:
    // first class
    InorderBTIterator                 () : stk_() {}
    virtual  ~InorderBTIterator       () { stk_.Clear(); }
    InorderBTIterator                 (const InorderBTIterator& i) : stk_(i.stk_) {}
    InorderBTIterator<C>&  operator=  (const InorderBTIterator& i) { stk_ = i.stk_; return *this; }

    // information/access
    bool  Valid   () const { return !stk_.Empty(); } // cursor is valid element

    // various operators
    bool                   operator== (const InorderBTIterator& i2) const { return stk_ == i2.stk_; }
    bool                   operator!= (const InorderBTIterator& i2) const { return !(*this == i2); }
    const ValueType&       operator*  () const { return stk_.Top()->value_; }
    InorderBTIterator<C>&  operator++ ();    // prefix
    InorderBTIterator<C>   operator++ (int); // postfix
    InorderBTIterator<C>&  operator-- ();    // prefix
    InorderBTIterator<C>   operator-- (int); // postfix

  private:
    void Init      (Node* n);
    void sInit     (Node* n); // structural version - pair with Increment for structural traversal
    void rInit     (Node* n);
    void Increment ();
    void Decrement ();
  };

  template < class C >
  void InorderBTIterator<C>::sInit(Node* n)
  {
    if (n == nullptr) return;
    stk_.Clear();
    stk_.Push(n);
    while (n != nullptr && n->HasLeftChild())
    {
      n = n->lchild_;
      stk_.Push(n);
    }
    // while (Valid() && stk_.Top()->IsDead())
    //   Increment();
  }

  template < class C >
  void InorderBTIterator<C>::Init(Node* n)
  {
	  sInit(n);

	  while (Valid() && stk_.Top()->IsDead()){

		Increment();
	  }
  }

  template < class C >
  void InorderBTIterator<C>::rInit(Node* n)
  {
	  if (n == nullptr) return;
	  stk_.Clear();
	  stk_.Push(n);
	  while (n != nullptr && n->HasRightChild())
	  {
		  n = n->rchild_;
		  stk_.Push(n);
	  }

	  while (Valid() && stk_.Top()->IsDead()){

		  Increment();
	  }
  } // end of void InorderBTIterator<C>::rInit(Node* n)

  template < class C >
  void InorderBTIterator<C>::Increment()
  {
    if ( stk_.Empty() )
      return;
    Node *n, *p;
    bool topWasRightChild;
    if ( stk_.Top()->HasRightChild() )
    // slide down to the left
    {
      n = stk_.Top()->rchild_;
      stk_.Push(n);
      while ( n != nullptr && n->HasLeftChild() )
      {
        n = n->lchild_;
        stk_.Push(n);
      }
    }
    else
    // retreat to first ancester for which node came from left branch
    {
      do
      {
        n = stk_.Top();
        stk_.Pop();
        p = (stk_.Empty()? nullptr : stk_.Top());
        topWasRightChild = (p != nullptr && p->HasRightChild() && n == p->rchild_);
      }
      while( topWasRightChild );
    }
  }

  template < class C >
  void InorderBTIterator<C>::Decrement()
  {
	  if (stk_.Empty())
		  return;
	  Node *n, *p;
	  bool topWasLeftChild;
	  if (stk_.Top()->HasLeftChild())
		  // slide down to the left
	  {
		  n = stk_.Top()->lchild_;
		  stk_.Push(n);
		  while (n != nullptr && n->HasRightChild())
		  {
			  n = n->rchild_;
			  stk_.Push(n);
		  }
	  }
	  else
		  // retreat to first ancester for which node came from left branch
	  {
		  do
		  {
			  n = stk_.Top();
			  stk_.Pop();
			  p = (stk_.Empty() ? nullptr : stk_.Top());
			  topWasLeftChild = (p != nullptr && p->HasLeftChild() && n == p->lchild_);
		  } while (topWasLeftChild);
	  }
  }

  template < class C >
  InorderBTIterator<C>&  InorderBTIterator<C>::operator++ ()
  {
    // fsu::Debug("operator++()");
    do Increment();
    while (!stk_.Empty() && stk_.Top()->IsDead());
    return *this;
  }

  template < class C >
  InorderBTIterator<C>   InorderBTIterator<C>::operator++ (int)
  {
    InorderBTIterator<C> i(*this);
    this->operator++();
    return i;
  }

  template < class C >
  InorderBTIterator<C>&  InorderBTIterator<C>::operator-- ()
  {
    // fsu::Debug("operator--()");
    do Decrement();
    while (!stk_.Empty() && stk_.Top()->IsDead());
    return *this;
  }

  template < class C >
  InorderBTIterator<C>   InorderBTIterator<C>::operator-- (int)
  {
    InorderBTIterator<C> i(*this);
    this->operator--();
    return i;
  }

  /*****************************************************/
  /*        class ThreadedBTIterator < C >             */
  /*****************************************************/

  template < class C >
  class ThreadedBTIterator // a ConstIterator pattern
  {
  private:
    friend   C;
    typename C::Node* node_;

  public:
    // terminology support
    typedef typename C::ValueType    ValueType;
    typedef typename C::Node         Node;
    typedef ThreadedBTIterator<C>    ConstIterator;
    typedef ThreadedBTIterator<C>    Iterator;

    // constructors
             ThreadedBTIterator  ();
    virtual  ~ThreadedBTIterator ();
             ThreadedBTIterator  (Node* n);    // type converter
             ThreadedBTIterator  (const ThreadedBTIterator& i); // copy ctor

    // information/access
    bool           Valid   () const; // cursor is valid element

    // various operators
    bool                    operator == (const ThreadedBTIterator& i2) const;
    bool                    operator != (const ThreadedBTIterator& i2) const;
    const ValueType&        operator *  () const; // const version
    ThreadedBTIterator<C>&  operator =  (const ThreadedBTIterator& i);
    ThreadedBTIterator<C>&  operator ++ ();    // prefix
    ThreadedBTIterator<C>   operator ++ (int); // postfix
    ThreadedBTIterator<C>&  operator -- ();    // prefix
    ThreadedBTIterator<C>   operator -- (int); // postfix

  private:
    void Init        (Node*);   
    void rInit       (Node*);
    void Increment   ();  // moves to next inorder node
    void Decrement   ();  // moves to previous inorder node

  };

  // protected increment/decrement
  template < class C >
  void ThreadedBTIterator<C>::Init(Node* n)
  {
	  while (n->HasLeftChild()){

		  n = n->lchild_;

	  }

	  node_ = n;
  }

  template < class C >
  void ThreadedBTIterator<C>::rInit(Node* n)
  {
	  while (n->HasRightChild()){

		  n = n->rchild_;

	  }

	  node_ = n;
  }

  template < class C >
  void ThreadedBTIterator<C>::Increment ()
  {
	  if (node_->IsRightThreaded()){

		  node_ = node_->rchild_;
	  }

	  else{
		  node_ = node_->rchild_;

		  while (!node_->IsLeftThreaded()){

			  node_ = node_->lchild_;

		  }
	  }
  }

  template < class C >
  void ThreadedBTIterator<C>::Decrement ()
  {
	  if (node_->IsLeftThreaded()){

		  node_ = node_->lchild_;
	  }

	  else{
		  node_ = node_->lchild_;

		  while (!node_->IsRightThreaded()){

			  node_ = node_->rchild_;

		  }
	  }
  }

  template < class C >
  ThreadedBTIterator<C>::ThreadedBTIterator ()  :  node_()
  {}

  template < class C >
  ThreadedBTIterator<C>::~ThreadedBTIterator () 
  {}

  template < class C >
  ThreadedBTIterator<C>::ThreadedBTIterator (const ThreadedBTIterator<C>& i)
    :  node_(i.node_)
  {}

  template < class C >
  ThreadedBTIterator<C> & ThreadedBTIterator<C>::operator =  (const ThreadedBTIterator<C>& i)
  {
    node_ = i.node_;
    return *this;
  }

  template < class C >
  ThreadedBTIterator<C>::ThreadedBTIterator (Node * n)
    :  node_(n)
  {}

  template < class C >
  bool ThreadedBTIterator<C>::Valid() const
  {
    return node_ != 0;
  }

  template < class C >
  ThreadedBTIterator<C> & ThreadedBTIterator<C>::operator ++()
  {
    do Increment();
    while (node_ != nullptr && node_->IsDead());
    return *this;
  }

  template < class C >
  ThreadedBTIterator<C>   ThreadedBTIterator<C>::operator ++(int)
  {
    ThreadedBTIterator<C> i = *this;
    operator ++();
    return i;
  }

  template < class C >
  ThreadedBTIterator<C> & ThreadedBTIterator<C>::operator --()
  {
    do Decrement();
    while (node_ != nullptr && node_->IsDead());
    return *this;
  }

  template < class C >
  ThreadedBTIterator<C>   ThreadedBTIterator<C>::operator --(int)
  {
    ThreadedBTIterator<C> i = *this;
    operator --();
    return i;
  }

  template < class C >
  const typename C::ValueType& ThreadedBTIterator<C>::operator *() const
  {
    return node_->value_;
  }

  template < class C >
  bool ThreadedBTIterator<C>::operator == (const ThreadedBTIterator<C>& i2) const
  {
    return node_ == i2.node_;
  }

  template < class C >
  bool ThreadedBTIterator<C>::operator != (const ThreadedBTIterator<C>& i2) const
  {
    return !(*this == i2);
  }

} // namespace fsu 

#endif

