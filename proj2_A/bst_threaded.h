/*
    bst_threaded.h

*/

#ifndef _BST_THREADED_H
#define _BST_THREADED_H

#include <cstddef>     // size_t
#include <cstdint>     // uint8_t
#include <iostream>
#include <iomanip>
#include <compare.h>   // LessThan
#include <queue.h>     // used in Dump()
#include <bst_base.h>
#include <bt2iter.h>

namespace fsu
{
  template < typename T, class P >
  class BST_Threaded;

  template < class C >
  class ThreadedBTIterator;

  template < class C >
  class InorderBTIterator;

  template < typename T, class P = fsu::LessThan<T> >
  class BST_Threaded : public BST_BASE<T,P>
  {
  public:

    typedef T    ValueType;
    typedef P    PredicateType;
    typedef ThreadedBTIterator< BST_Threaded <T,P> > Iterator;
    typedef LevelorderBTIterator< BST_Threaded <T,P> > LevelorderIterator;
    typedef InorderBTIterator< BST_Threaded <T,P> > InorderIterator;

    LevelorderIterator BeginLevelorder () const;
    LevelorderIterator EndLevelorder   () const;

    Iterator Begin  () const;
    Iterator rBegin () const;
    Iterator End    () const;
    Iterator rEnd   () const;

             BST_Threaded  ();
    explicit BST_Threaded  (P p);
    virtual  ~BST_Threaded ();
             BST_Threaded  ( const BST_Threaded& tree );
    BST_Threaded<T,P>& operator=( const BST_Threaded& that );

    void Put(const T& t) { Get(t) = t; }

    T& Get (const T& t)
    {
      Node * location = RGet(this->root_,t);
      // this->root_->SetBlack();
      return location -> value_;
    }
    bool     Erase      (const T& t);
    void     Insert     (const T& t) { Get(t) = t; }
    void     Insert     (Iterator i, const T& t);
    bool     Retrieve   (T& t)       const;
    Iterator LowerBound (const T& t) const;
    Iterator UpperBound (const T& t) const;
    Iterator Includes   (const T& t) const;

  protected: // definitions and family
    typedef typename fsu::BST_BASE<T,P>::Node Node;
    friend class ThreadedBTIterator < BST_Threaded <T,P> >;
    friend class LevelorderBTIterator < BST_Threaded <T,P> >;
    friend class PreorderBTIterator < BST_Threaded <T,P> >;

  private: // methods
    Node * RGet          (Node*& parent, const T& tval);

  }; // class BST_Threaded<>


  // define equality using class iterator type

  template < typename T , class P > 
  bool operator == (const BST_Threaded<T,P>& b1, const BST_Threaded<T,P>& b2)
  {
    if (&b1 == &b2) return 1;
    typename BST_Threaded<T,P>::Iterator i1 = b1.Begin(), i2 = b2.Begin();
    while (i1!= b1.End() && i2 != b2.End())
      if (*(i1++) != *(i2++))     // trees have different elements
        return 0;
    if (i1.Valid() || i2.Valid()) // trees are not the same size
      return 0;
    return 1;
  }

  template < typename T , class P > 
  bool operator != (const BST_Threaded<T,P>& b1, const BST_Threaded<T,P>& b2)
  {
    return !(b1 == b2);
  }

  // proper type
  
  template < typename T , class P >
  BST_Threaded<T,P>::BST_Threaded  () : BST_BASE<T,P>()
  {}

  template < typename T , class P >
  BST_Threaded<T,P>::BST_Threaded  (P p) : BST_BASE<T,P>(p)
  {}

  template < typename T , class P >
  BST_Threaded<T,P>::~BST_Threaded ()
  {
    this->Clear();
  }

  template < typename T , class P >
  BST_Threaded<T,P>::BST_Threaded( const BST_Threaded<T,P>& tree ) : BST_BASE<T,P>(tree)
  {
    this->SetAllThreads();
  }

  template < typename T , class P >
  BST_Threaded<T,P>& BST_Threaded<T,P>::operator=( const BST_Threaded<T,P>& that )
  {
    if (this != &that)
    {
      BST_BASE<T,P>::operator=(that);
      this->SetAllThreads();
    }
    return *this;
  }

  // protected helper method prototyped in base class
  template < typename T , class P >
  void BST_BASE<T,P>::SetAllThreads ()
  {
    // fsu::Debug("SetAllThreads");
    BST_BASE<T,P>::InorderIterator i = BST_BASE<T,P>::BeginStructuralInorder();
    if (i == BST_BASE<T,P>::EndInorder()) return;
    Node * n1, * n2;
    n1 = i.stk_.Top();
    n1->SetLeftThread(nullptr);
    i.Increment();
    while (i != BST_BASE<T,P>::EndInorder())
    {
      n2 = i.stk_.Top();
      if (!n1->HasRightChild())
      {
        n1->SetRightThread(n2);
      }
      if (!n2->HasLeftChild())
      {
        n2->SetLeftThread(n1);
      }
      n1 = n2;
      i.Increment();
    }
    n1->SetRightThread(nullptr);
  }

  // Iterator support methods

  template < typename T , class P >
  typename BST_Threaded<T,P>::LevelorderIterator BST_Threaded<T,P>::BeginLevelorder() const
  {
    LevelorderIterator i;
    i.Init(this->root_);
    return i;
  }

  template < typename T , class P >
  typename BST_Threaded<T,P>::LevelorderIterator BST_Threaded<T,P>::EndLevelorder() const
  {
    LevelorderIterator i;
    return i;
  }

  template < typename T , class P >
  typename BST_Threaded<T,P>::Iterator BST_Threaded<T,P>::Begin() const
  {
    Iterator i;
    i.Init(this->root_);
    return i;
  }

  template < typename T , class P >
  typename BST_Threaded<T,P>::Iterator BST_Threaded<T,P>::End() const
  {
    Iterator i;
    return i;
  }

  template < typename T , class P >
  typename BST_Threaded<T,P>::Iterator BST_Threaded<T,P>::rBegin() const
  {
    Iterator i;
    i.rInit(this->root_);
    return i;
  }

  template < typename T , class P >
  typename BST_Threaded<T,P>::Iterator BST_Threaded<T,P>::rEnd() const
  {
    Iterator i;
    return i;
  }

  // the Iterator locator methods 
  // efficient implementations using threaded iterators

  template < typename T , class P >
  typename BST_Threaded<T,P>::Iterator BST_Threaded<T,P>::LowerBound ( const T& t ) const
  {
   // std::cout << "Threaded LowerBound requires implementation!\n";
	for (Iterator u = Begin(); u != End(); ++u){

                if (*u >= t){

                        return u;
                }
        }
    return End();
  }

  template < typename T , class P >
  typename BST_Threaded<T,P>::Iterator BST_Threaded<T,P>::UpperBound ( const T& t ) const
  {
    if (this->root_ == nullptr)
      return End();
    Iterator u = End();
    Node * n = this->root_;
    bool finished = 0;
    while (! finished)
    {
      if (this->pred_(t,n->value_)) // t < n
      {
        u.node_ = n;
        if (n->HasLeftChild())
          n = n->lchild_;
        else
          finished = 1;
      }
      else // t >= n
      {
        if (n->HasRightChild())
          n = n->rchild_;
        else
          finished = 1;
      }
    }
    // take care of dead node case
    if (u.Valid() && u.node_->IsDead())
      ++u;
    return u;
  }

  template < typename T , class P >
  typename BST_Threaded<T,P>::Iterator BST_Threaded<T,P>::Includes ( const T& t ) const
  {
    Iterator i = End();
    i.node_ = this->root_;
    while (i.node_ != nullptr)
    {
      if (this->pred_(t,i.node_->value_))
      {
        if (i.node_->HasLeftChild()) // needed for threaded case
          i.node_ = i.node_->lchild_;
        else
          return End();
      }
      else if  (this->pred_(i.node_->value_,t))
      {
        if (i.node_->HasRightChild())  // needed for threaded case
          i.node_ = i.node_->rchild_;
        else
          return End();
      }
      else // node found
      {
        // take care of dead node case
        if (i.node_->IsAlive())
          return i;
        else
          return End();
      }
    }
    return End();
  }

  // Insert with a hint
  template < typename T , class P >
  void BST_Threaded<T,P>::Insert (Iterator i, const T& t)
  {
    if (t == *i)
    {
      i.node_->value_ = t;
      i.node_->SetAlive();
      return;
    }
    BST_Threaded<T,P>::Insert(t);
  }

  // recursive Get
  template <typename T, class P>
  typename BST_Threaded<T,P>::Node *  BST_Threaded<T,P>::RGet(Node*& parent, const T& tval)
  {
    // add new node at bottom of tree
    if (this->root_ == nullptr)
    {
      this->root_ = BST_BASE<T,P>::NewNode(tval, BST_BASE<T,P>::THREADS);
      return this->root_;
    }

    // insert recursively
    if (this->pred_(tval,parent->value_))  // left subtree
    {
      if (parent->IsLeftThreaded())
      {
        Node * n = BST_BASE<T,P>::NewNode(tval, BST_BASE<T,P>::THREADS);
        n->SetLeftThread(parent->lchild_);
        n->SetRightThread(parent);
        parent->SetLeftChild(n);
        parent->SetLeftChild(n);

        /* // node data output
           std::cout << " RInsert left:\n";
           std::cout << "  Parent:\n";
           parent->Dump();
           std::cout << "  Node:\n";
           n->Dump();
           // node data output */

        return n;
      }

      else
      {
        return RGet(parent->lchild_, tval);
      }
    }
    else if (this->pred_(parent->value_,tval))  // right subtree
    {
      if (parent->IsRightThreaded())
      {
        Node * n = BST_BASE<T,P>::NewNode(tval, BST_BASE<T,P>::THREADS);
        n->SetRightThread(parent->rchild_);
        n->SetLeftThread(parent);
        parent->SetRightChild(n);

        /* // node data output
           std::cout << " RInsert right:\n";
           std::cout << "   parent:\n";
           parent->Dump();
           std::cout << "   node:\n";
           n->Dump();
           // node data output */

        return n;
      }
      else
      {
        return RGet(parent->rchild_, tval);
      }
    }
    else // equality: node exists - unimodal insert here
    {
      // parent->value_ = tval;
      parent->SetAlive();
    }
    return parent;
  } // BST_Threaded<T,P> :: RGet()  */

  template < typename T , class P >
  bool BST_Threaded<T,P>::Retrieve ( T& t ) const
  {
    Node * n = this->root_;
    while (n != nullptr)
    {
      if (this->pred_(t,n->value_))
      {
        if (n->HasLeftChild()) // needed for threaded case
          n = n->lchild_;
        else
          return 0;
      }
      else if  (this->pred_(n->value_,t))
      {
        if (n->HasRightChild())  // needed for threaded case
          n = n->rchild_;
        else
          return 0;
      }
      else // found
      {
        t = n->value_;  // retrieve
        return 1;
      }
    }
    return 0;
  }

  template < typename T , class P >
  bool BST_Threaded<T,P>::Erase ( const T& t )
  {
    Node * n = this->root_;
    while (n != nullptr)
    {
      if (this->pred_(t,n->value_))
      {
        if (n->HasLeftChild())  // needed for threaded case
          n = n->lchild_;
        else
          return 0;
      }
      else if  (this->pred_(n->value_,t))
      {
        if (n->HasRightChild())  // needed for threaded case
          n = n->rchild_;
        else
          return 0;
      }
      else // found
      {
        /* can be improved to delete leaf nodes and nodes that have one null
           child; requires knowing parent & left/right at the "found" case,
           which is the grandparent in the other two cases; also may be tedious
           in the cases of RBLLT or threaded iterators */
        n->SetDead();
        return 1;
      }
    }
    return 0;
  }

} // namespace fsu 

#endif

