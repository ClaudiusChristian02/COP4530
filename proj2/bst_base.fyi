/*
    bst_base.h
    02/25/15
    03/13/15: DumpBW added

    Base class for 2-way ordered binary trees

*/

#ifndef _BST_BASE_H
#define _BST_BASE_H

#include <cstddef>     // size_t
#include <cstdint>     // uint8_t
#include <ansicodes.h> // color output
#include <iostream>
#include <fstream>
#include <iomanip>
#include <compare.h>   // LessThan
#include <bt2iter.h>   // Iterator classes for 2-way binary trees
#include <debug.h>     // argh

namespace fsu
{
  template < typename T, class P >
  class BST_BASE;

  template < class C >
  class InorderBTIterator;

  template < class C >
  class LevelorderBTIterator;

  template < class C >
  class PreorderBTIterator;

  template < class C >
  class PostorderBTIterator;

  template < class C >
  class ThreadedBTIterator;

  template < typename T, class P = LessThan<T> >
  class BST_BASE
  {
  public:

    typedef T    ValueType;
    typedef P    PredicateType;
    typedef InorderBTIterator     < BST_BASE <T,P> > InorderIterator;
    typedef LevelorderBTIterator  < BST_BASE <T,P> > LevelorderIterator;
    typedef PreorderBTIterator    < BST_BASE <T,P> > PreorderIterator;
    typedef PostorderBTIterator   < BST_BASE <T,P> > PostorderIterator;
    typedef ThreadedBTIterator    < BST_BASE <T,P> > ThreadedIterator;

             BST_BASE  ();
    explicit BST_BASE  (P p);
             BST_BASE  (const BST_BASE& b);
    virtual  ~BST_BASE ();
    BST_BASE& operator=(const BST_BASE& b);

    LevelorderIterator BeginLevelorder () const;
    LevelorderIterator EndLevelorder   () const;

    InorderIterator BeginInorder  () const;
    InorderIterator EndInorder    () const;
    InorderIterator rBeginInorder () const;
    InorderIterator rEndInorder   () const;

    InorderIterator BeginStructuralInorder  () const;
    // Paired with Increment(), traverses tree physical structure 

    void         Insert     (const T& t);
    // void         Remove     (const T& t);
    void         Put        (const T& t) { Get(t) = t; }
    ValueType&   Get        (const T& t);
    bool         Erase      (const T& t);
    void         Clear      ()
    {
      RRelease(root_);
      delete root_;
      root_ = nullptr;
    }

    bool         Retrieve   (T& t) const;

    // InorderIterator     Includes   (const T& t) const;
    // InorderIterator     LowerBound (const T& t) const;
    // InorderIterator     UpperBound (const T& t) const;
    // void                Insert (Iterator i, const T& t);

    bool         Empty    () const { return root_ == nullptr; }
    size_t       Size     () const { return RSize(root_); }
    size_t       NumNodes () const { return RNumNodes(root_); }
    int          Height   () const { return RHeight(root_); }

    template <class F>
    void   Traverse (F f) const { RTraverse(root_,f); }

    void  Display (std::ostream& os, char ofc) const
    {
      PrintNode printval(os,ofc);
      Traverse (printval);
    }

    // the Dump methods display the tree contents in several forms
    void   DumpBW   (std::ostream& os) const;
    void   Dump     (std::ostream& os) const;
    void   Dump     (std::ostream& os, int dw) const;
    void   Dump     (std::ostream& os, int dw, char fill) const;

    // Check methods examine the required structural properties and report problems
    bool CheckBST   (bool verboseFlag)     const;
    bool CheckRBLLT (int  verboseFlag)     const;

    // Snapshot writes tree data to file in level order 
    // with fbst commands for re-initializing the tree exactly
    void Snapshot   (const char* filename) const;
 
    enum Flags { ZERO = 0x00 , DEAD = 0x01, RED = 0x02 , LEFT_THREAD = 0x04 , RIGHT_THREAD = 0x08 ,
                 THREADS = LEFT_THREAD | RIGHT_THREAD };

  protected: // definitions and family

    friend class InorderBTIterator    < BST_BASE <T,P> >;
    friend class LevelorderBTIterator < BST_BASE <T,P> >;
    friend class PreorderBTIterator   < BST_BASE <T,P> >;
    friend class PostorderBTIterator  < BST_BASE <T,P> >;
    friend class ThreadedBTIterator   < BST_BASE <T,P> >;

    struct Node
    {
      T             value_;
      Node *        lchild_,
           *        rchild_;
      uint8_t       flags_;

      Node (const T& tval, uint8_t flags) : value_(tval), lchild_(nullptr), rchild_(nullptr), flags_(flags)
      {}

      static const char* ColorMap (uint8_t flags)
      {
        flags &= 0x03; // last 2 bits only
        switch(flags)
        {
          case 0x00: return ANSI_BOLD_BLUE;        // bits 00 = !RED |  ALIVE 
          case 0x01: return ANSI_BOLD_BLUE_SHADED; // bits 01 = !RED | !ALIVE
          case 0x02: return ANSI_BOLD_RED;         // bits 10 =  RED |  ALIVE
          case 0x03: return ANSI_BOLD_RED_SHADED;  // bits 11 =  RED | !ALIVE
          default: return "unknown color";   // unknown flags
        }
      }

      static char FlagMap (uint8_t flags)
      {
        flags &= 0x03; // last 2 bits only
        switch(flags)
        {
          case 0x00: return 'B'; // bits 00 = !RED |  ALIVE 
          case 0x01: return 'b'; // bits 01 = !RED | !ALIVE
          case 0x02: return 'R'; // bits 10 =  RED |  ALIVE
          case 0x03: return 'r'; // bits 11 =  RED | !ALIVE
          default: return 'X';   // unknown flags
        }
      }
    
      bool IsRed    () const { return 0 != (RED & flags_); }
      bool IsBlack  () const { return !IsRed(); }
      bool IsDead   () const { return 0 != (DEAD & flags_); }
      bool IsAlive  () const { return !IsDead(); }
      void SetRed   ()       { flags_ |= RED; }
      void SetBlack ()       { flags_ &= ~RED; }
      void SetDead  ()       { flags_ |= DEAD; }
      void SetAlive ()       { flags_ &= ~DEAD; }

      bool HasLeftChild       () const { return (lchild_ != nullptr) && !(IsLeftThreaded()); }
      bool HasRightChild      () const { return (rchild_ != nullptr) && !(IsRightThreaded()); }
    
      bool IsLeftThreaded     () const { return 0 != (LEFT_THREAD & flags_); }
      bool IsRightThreaded    () const { return 0 != (RIGHT_THREAD & flags_); }

      void SetLeftThread      (Node* n) { lchild_ = n; flags_ |= LEFT_THREAD; }
      void SetRightThread     (Node* n) { rchild_ = n; flags_ |= RIGHT_THREAD; }
      void SetLeftChild       (Node* n) { lchild_ = n; flags_ &= ~LEFT_THREAD; }
      void SetRightChild      (Node* n) { rchild_ = n; flags_ &= ~RIGHT_THREAD; }

      void Dump (std::ostream& os = std::cout) const
      {
        os << "  Node data:\n"
           << "    value:          " << value_  << '\n'
           << "    color:          " << (size_t)IsRed() << '\n'
           << "    alive:          " << (size_t)IsAlive() << '\n'
           << "    left_threaded:  " << (size_t)IsLeftThreaded() << '\n'
           << "    right_threaded: " << (size_t)IsRightThreaded() << '\n';
        os << "    lchild:         ";
        if (lchild_)
        {
          if (IsLeftThreaded())
            os << lchild_->value_  << " (predecessor)\n";
          else
            os << lchild_->value_  << " (left child)\n";
        }
        else
          os << "NULL\n";
        os << "    rchild:         ";
        if (rchild_)
        {
          if (IsRightThreaded())
            os << rchild_->value_  << " (succecessor)\n";
          else
            os << rchild_->value_  << " (right child)\n";
        }
        else
          os << "NULL\n";
        os << std::flush;
      }
    };  // struct BST_BASE<T,P>::Node

    class PrintNode
    {
    public:
    PrintNode (std::ostream& os, char ofc) : os_(os), ofc_(ofc) {}
      void operator() (const Node* n) const
      {
        if (ofc_ == '\0') os_ << n->value_; 
        else os_ << n->value_ << ofc_;
      }
    private:
      std::ostream& os_;
      char         ofc_;
    };

  protected: // data - may be accessed by derived classes
    Node *         root_;
    PredicateType  pred_;
    static Node * NewNode   (const T& t, uint8_t flags = ZERO);

  protected: // method
    void SetAllThreads();    // used to set threads in copy of threaded tree

  private: // methods - all static recursive
    static void   RRelease  (Node* n);       // deletes all descendants of n
    static Node * RClone    (const Node* n); // returns deep copy of n
    static size_t RSize     (Node * n);      // number of live nodes at n
    static size_t RNumNodes (Node * n);      // number of nodes at n
    static int    RHeight   (Node * n);      // height of tree at n

    template < class F >
    static void RTraverse (Node * n, F f);

  }; // class BST_BASE<>
  
  // define equality using class iterator type

  template < typename T , class P > 
  bool operator == (const BST_BASE<T,P>& b1, const BST_BASE<T,P>& b2)
  {
    if (&b1 == &b2) return 1;
    typename BST_BASE<T,P>::InorderIterator i1 = b1.BeginInorder(), i2 = b2.BeginInorder();
    while (i1!= b1.EndInorder() && i2 != b2.EndInorder())
      if (*(i1++) != *(i2++))             // trees have different elements
        return 0;
    if (i1 != b1.EndInorder() || i2 != b2.EndInorder()) // trees are not the same size
      return 0;
    return 1;
  }

  template < typename T , class P > 
  bool operator != (const BST_BASE<T,P>& b1, const BST_BASE<T,P>& b2)
  {
    return !(b1 == b2);
  }

  // proper type
  
  template < typename T , class P >
  BST_BASE<T,P>::BST_BASE  () : root_(nullptr), pred_()
  {}

  template < typename T , class P >
  BST_BASE<T,P>::BST_BASE  (P p) : root_(nullptr), pred_(p)
  {}

  template < typename T , class P >
  BST_BASE<T,P>::~BST_BASE ()
  {
    Clear();
  }

  template < typename T , class P >
  BST_BASE<T,P>::BST_BASE  ( const BST_BASE& that ) : root_(nullptr), pred_(that.pred_)
  {
    this->root_ = RClone(that.root_);
  }

  template < typename T , class P >
  BST_BASE<T,P>& BST_BASE<T,P>::operator=( const BST_BASE& that )
  {
    // fsu::Debug("operator=");
    if (this != &that)
    {
      Clear();
      this->pred_ = that.pred_;
      this->root_ = RClone(that.root_);
    }
    return *this;
  }

  template < typename T , class P >
  typename BST_BASE<T,P>::LevelorderIterator BST_BASE<T,P>::BeginLevelorder() const
  {
    LevelorderIterator i;
    i.Init(root_);
    return i;
  }

  template < typename T , class P >
  typename BST_BASE<T,P>::LevelorderIterator BST_BASE<T,P>::EndLevelorder() const
  {
    LevelorderIterator i;
    return i;
  }

  template < typename T , class P >
  typename BST_BASE<T,P>::InorderIterator BST_BASE<T,P>::BeginInorder() const
  {
    InorderIterator i;
    i.Init(root_);
    return i;
  }

  template < typename T , class P >
  typename BST_BASE<T,P>::InorderIterator BST_BASE<T,P>::BeginStructuralInorder() const
  {
    InorderIterator i;
    i.sInit(root_);
    return i;
  }

  template < typename T , class P >
  typename BST_BASE<T,P>::InorderIterator BST_BASE<T,P>::EndInorder() const
  {
    InorderIterator i;
    return i;
  }

  template < typename T , class P >
  typename BST_BASE<T,P>::InorderIterator BST_BASE<T,P>::rBeginInorder() const
  {
    InorderIterator i;
    i.rInit(root_);
    return i;
  }

  template < typename T , class P >
  typename BST_BASE<T,P>::InorderIterator BST_BASE<T,P>::rEndInorder() const
  {
    InorderIterator i;
    return i;
  }

  template < typename T , class P >
  void BST_BASE<T,P>::Insert ( const T& t )
  {
    if (root_ == nullptr)
    {
      root_ = NewNode(t);
      return;
    }
    Node * p = nullptr;  // trailing parent
    Node * n = root_;
    bool   left;
    while (n != nullptr)
    {
      p = n;
      if (pred_(t,n->value_))
      {
        n = n->lchild_;
        left = 1;
      }
      else if  (pred_(n->value_,t))
      {
        n = n->rchild_;
        left = 0;
      }
      else // found
      {
        n->value_ = t;  // unimodal insert
        n->SetAlive();
        return;
      }
    }
    n = NewNode(t);
    (left ? p->lchild_ = n : p->rchild_ = n);
  }

  template < typename T , class P >
  bool BST_BASE<T,P>::Retrieve ( T& t ) const
  {
    Node * n = root_;
    while (n != nullptr)
    {
      if (pred_(t,n->value_))
      {
          n = n->lchild_;
      }
      else if  (pred_(n->value_,t))
      {
          n = n->rchild_;
      }
      else // found
      {
        t = n->value_;  // retrieve
        if (n->IsAlive())
          return 1;
        else
          return 0;
      }
    }
    return 0;
  }

  template < typename T , class P >
  T& BST_BASE<T,P>::Get ( const T& t )
  {
    if (root_ == nullptr)
    {
      root_ = NewNode(t);
      return root_->value_;
    }

    Node * p = nullptr;  // trailing parent
    Node * n = root_;
    bool   left;
    while (n != nullptr)
    {
      p = n;
      if (pred_(t,n->value_))
      {
        n = n->lchild_;
        left = 1;
      }
      else if  (pred_(n->value_,t))
      {
        n = n->rchild_;
        left = 0;
      }
      else // found
      {
        n->SetAlive();
        return n->value_;
      }
    }
    n = NewNode(t);
    (left ? p->lchild_ = n : p->rchild_ = n);
    return n->value_;
  }

  template < typename T , class P >
  bool BST_BASE<T,P>::Erase ( const T& t )
  {
    Node * n = root_;
    while (n != nullptr)
    {
      if (pred_(t,n->value_))
      {
        n = n->lchild_;
      }
      else if  (pred_(n->value_,t))
      {
        n = n->rchild_;
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

  // private static recursive methods

  template < typename T , class P >
  typename BST_BASE<T,P>::Node* BST_BASE<T,P>::RClone(const BST_BASE<T,P>::Node* n)
  // returns a pointer to a deep copy of n
  {
    if (n == nullptr)
      return nullptr;
    typename BST_BASE<T,P>::Node* newN = NewNode (n->value_, n->flags_);
    if (n->HasLeftChild())
      newN->lchild_ = BST_BASE<T,P>::RClone(n->lchild_);
    else
      newN->lchild_ = nullptr;
    if (n->HasRightChild())
      newN->rchild_ = BST_BASE<T,P>::RClone(n->rchild_);
    else
      newN->rchild_ = nullptr;
    return newN;
  } // end BST_BASE<T,P>::RClone() */

  template < typename T , class P >
  size_t BST_BASE<T,P>::RSize(Node * n)
  {
    if (n == nullptr) return 0;
    size_t lsize = 0, rsize = 0;
    if (n->HasLeftChild())
      lsize = RSize(n->lchild_);
    if (n->HasRightChild())
      rsize = RSize(n->rchild_);
    return (size_t)(n->IsAlive()) + lsize + rsize;
  }

  template < typename T , class P >
  size_t BST_BASE<T,P>::RNumNodes(Node * n)
  {
    if (n == nullptr) return 0;
    size_t lsize = 0, rsize = 0;
    if (n->HasLeftChild())
      lsize = RNumNodes(n->lchild_);
    if (n->HasRightChild())
      rsize = RNumNodes(n->rchild_);
    return 1 + lsize + rsize;
  }

  template < typename T , class P >
  int BST_BASE<T,P>::RHeight(Node * n)
  {
    if (n == nullptr) return -1;
    int lh = -1, rh = -1;
    if (!(n->IsLeftThreaded()))
        lh = RHeight(n->lchild_);
    if (!(n->IsRightThreaded()))
        rh = RHeight(n->rchild_);
    if (lh < rh) return 1 + rh;
    return 1 + lh;
  }

  template < typename T , class P >
  template < class F >
  void BST_BASE<T,P>::RTraverse (Node * n, F f)
  {
    if (n == nullptr) return;
    if (n->HasLeftChild())
      RTraverse(n->lchild_,f);
    if (n->IsAlive()) f(n);
    if (n->HasRightChild())
      RTraverse(n->rchild_,f);
  }

  template < typename T , class P >
  void BST_BASE<T,P>::RRelease(Node* n)
  // post:  all descendants of n have been deleted
  {
    if (n != nullptr)
    {
      if (n->HasLeftChild())
      {
        BST_BASE<T,P>::RRelease(n->lchild_);
        delete n->lchild_;
        n->lchild_ = nullptr;
      }
      if (n->HasRightChild())
      {
        BST_BASE<T,P>::RRelease(n->rchild_);
        delete n->rchild_;
        n->rchild_ = nullptr;
      }
    }
    // note: threading may not be correct
    // but: safe to use as RRelease(root_)
  } // BST_BASE<T,P>::RRelease()

  // private static method
  template < typename T , class P >
  typename BST_BASE<T,P>::Node * BST_BASE<T,P>::NewNode(const T& t, uint8_t flags) 
  {
    Node * nPtr = new(std::nothrow) Node(t,flags);
    if (nPtr == nullptr)
    {
      std::cerr << "** BST_BASE memory allocation failure\n";
      // handle exception in-class here
    }
    return nPtr;
  }

  // deveopement support
  template < typename T , class P >
  void BST_BASE<T,P>::DumpBW (std::ostream& os) const
  {
    // fsu::debug ("DumpBW(1)");
    // similar to Dump(1) except uses FlagMap to output characters in place of
    // colors - sometimesuseful for file output
    if (root_ == nullptr)
      return;

    // we will use "root" as the placeholder node; test for dummy by address
    Queue < Node * , Deque < Node * > > Que;
    char nullFill = '-';
    Node * fillNode = root_;
    Node * current;
  
    size_t currLayerSize, nextLayerSize, j, k;
    currLayerSize = 1;
    k = 1;  // 2^LayerNumber
    Que.Push(root_);

    // execute body once for "real" root:
    os << ' '; // 1-space left margin for graphic
    nextLayerSize = 0;
    current = Que.Front();
    Que.Pop();
    os << Node::FlagMap(current->flags_);
    if (current->HasLeftChild())
    {
      Que.Push(current->lchild_);
      ++nextLayerSize;
    }
    else
    {
      Que.Push(fillNode);
    }
    if (current->HasRightChild())
    {
      Que.Push(current->rchild_);
      ++nextLayerSize;
    }
    else
    {
      Que.Push(fillNode);
    }
    os << '\n';
    currLayerSize = nextLayerSize;
    k *= 2;

    // now finish off, using address to detect fillNode.
    while (currLayerSize > 0)
    {
      nextLayerSize = 0;
      os << ' '; // 1-space left margin for graphic
      for (j = 0; j < k; ++j)
      {
        current = Que.Front();
        Que.Pop();
        if (current == fillNode) // an empty position in the tree
          os << nullFill;
        else 
          os << Node::FlagMap(current->flags_);
        if (current != fillNode && current->HasLeftChild())
        {
          Que.Push(current->lchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
        if (current != fillNode && current->HasRightChild())
        {
          Que.Push(current->rchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
      } // end for
      os << '\n';
      currLayerSize = nextLayerSize;
      k *= 2;
    } // end while
    Que.Clear();
  } // DumpBW(os)

  template < typename T , class P >
  void BST_BASE<T,P>::Dump (std::ostream& os) const
  {
    // fsu::debug ("Dump(1)");

    // This implementation is very like that for Dump(os, dw, fill), except that
    // there is no supplied fill object or output format character. The trick is
    // to use the root of a non-empty tree as the fill. To make that work, we have
    // to take care of the real root case before entering the main loop. 

    if (root_ == nullptr)
      return;

    // we will use "root" as the placeholder node; test for dummy by address
    Queue < Node * , Deque < Node * > > Que;
    char nullFill = '-';
    char nodeFill = '*';
    Node * fillNode = root_;
    Node * current;
  
    size_t currLayerSize, nextLayerSize, j, k;
    currLayerSize = 1;
    k = 1;  // 2^LayerNumber
    Que.Push(root_);

    // execute body once for "real" root:
    os << ' '; // 1-space left margin for graphic
    nextLayerSize = 0;
    current = Que.Front();
    Que.Pop();
    os << Node::ColorMap(current->flags_) << nodeFill << ANSI_RESET_ALL;
    if (current->HasLeftChild())
    {
      Que.Push(current->lchild_);
      ++nextLayerSize;
    }
    else
    {
      Que.Push(fillNode);
    }
    if (current->HasRightChild())
    {
      Que.Push(current->rchild_);
      ++nextLayerSize;
    }
    else
    {
      Que.Push(fillNode);
    }
    os << '\n';
    currLayerSize = nextLayerSize;
    k *= 2;

    // now finish off, using address to detect fillNode.
    while (currLayerSize > 0)
    {
      nextLayerSize = 0;
      os << ' '; // 1-space left margin for graphic
      for (j = 0; j < k; ++j)
      {
        current = Que.Front();
        Que.Pop();
        if (current == fillNode) // an empty position in the tree
          os << nullFill;
        else 
          os << Node::ColorMap(current->flags_) << nodeFill << ANSI_RESET_ALL;
        if (current != fillNode && current->HasLeftChild())
        {
          Que.Push(current->lchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
        if (current != fillNode && current->HasRightChild())
        {
          Que.Push(current->rchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
      } // end for
      os << '\n';
      currLayerSize = nextLayerSize;
      k *= 2;
    } // end while
    Que.Clear();
  } // Dump(os)

  template < typename T , class P >
  void BST_BASE<T,P>::Dump (std::ostream& os, int dw) const
  {
    // fsu::debug ("Dump(2)");
    if (root_ == nullptr)
      return;
    Queue < Node * , Deque < Node * > > Que;
    Node * current;
    size_t currLayerSize, nextLayerSize, j;
    Que.Push(root_);
    currLayerSize = 1;
    while (!Que.Empty())
    {
      nextLayerSize = 0;
      if (dw == 1) os << ' '; // indent picture 1 space
      for (j = 0; j < currLayerSize; ++j)
      {
        current = Que.Front();
        Que.Pop();
        if (dw > 1) os << ' '; // indent each column 1 space
        os << Node::ColorMap(current->flags_) << std::setw(dw) << current->value_<< ANSI_RESET_ALL;
        if (current->HasLeftChild())
        {
          Que.Push(current->lchild_);
          ++nextLayerSize;
        }
        if (current->HasRightChild())
        {
          Que.Push(current->rchild_);
          ++nextLayerSize;
        }
      }
      os << '\n';
      currLayerSize = nextLayerSize;
    } // end while
    if (currLayerSize > 0)
      std::cerr << "** BST_BASE<T,P>::Dump() inconsistency\n";
  } // Dump(os, dw)

  template < typename T , class P >
  void BST_BASE<T,P>::Dump (std::ostream& os, int dw, char fill) const
  {
    // fsu::debug ("Dump(3)");
    if (root_ == nullptr)
      return;

    Node* fillNode = NewNode(T());
    Queue < Node * , Deque < Node * > > Que;
    Node * current;
    size_t currLayerSize, nextLayerSize, j, k;
    Que.Push(root_);
    currLayerSize = 1;
    k = 1;  // 2^LayerNumber
    while (currLayerSize > 0)
    {
      nextLayerSize = 0;
      if (dw == 1) os << ' '; // indent picture 1 space
      for (j = 0; j < k; ++j)
      {
        current = Que.Front();
        Que.Pop();
        if (dw > 1) os << ' '; // indent each column 1 space
        if (current == fillNode)
        {
          os << std::setw(dw) << fill;
        }
        else
        {
          os << Node::ColorMap(current->flags_) << std::setw(dw) << current->value_<< ANSI_RESET_ALL;
        }

        if (current->HasLeftChild())
        {
          Que.Push(current->lchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
        if (current->HasRightChild())
        {
          Que.Push(current->rchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
      }
      os << '\n';
      currLayerSize = nextLayerSize;
      k *= 2;
    } // end while
    Que.Clear();
    delete fillNode;
  } // Dump(os, dw, fill) */

  // Checks the order conditions for BST.
  // Note this implicitly also checks unimodality - there are no duplicate entries.
  template <typename T, class P>
  bool BST_BASE<T,P>::CheckBST(bool verboseFlag) const
  {
    if (root_ == nullptr) return 1;
    InorderIterator i,j,k;
    bool ok = 1;
    for (j = BeginStructuralInorder(); j != EndInorder(); j.Increment())
    {
      i = k = j;
      --i;
      ++k;
      if (i.Valid())
      {
        if (!pred_(*i,*j))
        {
          ok = 0;
          std::cout << "  ** CheckBST: order discrepancy between nodes at "
                    << "--i = " << *i
                    <<  " and " 
                    << "i = " << *j << '\n';
        }
      }
      if (k.Valid())
      {
        if (!pred_(*j,*k))
        {
          ok = 0;
          std::cout << "  ** CheckBST: order discrepancy between nodes at "
                    << "i = " << *j
                    <<  " and " 
                     << "++i = " << *k << '\n';
        }
      }
    }
    if (ok && verboseFlag) std::cout << "  ** CheckBST: OK\n";
    return ok;
  } // CheckBST() */

  // writes a file of fbst commands to reproduce the tree
  template <typename T, class P>
  void BST_BASE<T,P>::Snapshot(const char* filename) const
  {
    std::ofstream ofs(filename);
    if (ofs.fail())
    {
      std::cerr << "  ** Unable to open Snapshot file " << filename << '\n';
      return;
    }
    Node* n;
    for (LevelorderIterator i = BeginLevelorder(); i != EndLevelorder(); i.Increment())
    {
      n = i.que_.Front();
      if (n->IsAlive())
        ofs << "1 " << n->value_ << '\n';
      else
        ofs << "1 " << n->value_ << " E " << n->value_ << '\n';
    }
    ofs << "x\n";
    ofs.close();
  }
} // namespace fsu 

#endif

