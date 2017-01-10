/*
    mbst.cpp
    02/25/15
    Chris Lacher

    Dynamic Random Test of BST<>

    Driver program testing BST<T> for pointer errors and memory
    leaks by fully exercising all BST<T> and
    BST<T>::Iterator functions randomly in an unending loop.

    For VERBOSE mode, execute with any argument, as in:

    >  mbst.x x

    IMPORTANT INSTRUCTIONS FOR USE: 
    ==============================

    Running this program using a faulty implementation of BST can take over a
    machine and virtually shut it down, preventing all other processes from
    running, including those of other users. It is therefore REQUIRED that this
    program be executed ONLY using the following procedures:

    1. Create a login to one of the programming machines (program or linprog)
    2. Compile using your command line compile script
    3. Limit your memory use by entering
       "limit vmemoryuse 50000"
    4. Check that your limits have been set by entering
       "limit"
    5. Run by entering the executable name
    6. Execution should terminate when memory is used up
    7. After a run, remove your vmememoryuse restriction by entering
       "limit vmemoryuse unlimited"

    With vmemoryuse limited to 4000, you don't have enough space to run emacs
    or a compiler. 

    NOTE: Students not following this procedure and resulting in bogging down a
    machine will be responsible for the consequences, including possible
    suspension of your CS account, which could affect your performance in this
    and other courses. 

    Copyright 2015, R.C. Lacher
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <xstring.h>
#include <xran.h>
#include <xranxstr.h>
#include <cmath>

// choose one from group A 

// =====================
// ===== group A =======
// =====================

/********************************/
/*     select element type      */
/********************************/

// A1: makes BSTs of unsigned int
#include <xran.cpp>  // in lieu of makefile
typedef unsigned int       ElementType;
typedef fsu::Random_int Random_class;
const char* typestring = "unsigned int";
const long unsigned int maxSize        =     3000;
const long unsigned int maxNodes       =     5000;
const      unsigned int ranBound       =     5000; // upper bound on range
const long unsigned int reportInterval =    10000;
const      unsigned int getPercent  =       50;    // to control
const      unsigned int putPercent  =       50;    // growth rate
const      unsigned int assignPercent  =    30; // and volatility
ElementType RandomObject( Random_class& ranobj )
{
  return ranobj(0,ranBound);
}
// end A1 */

/* // A2: makes BSTs of String
#include <xstring.cpp>  // in lieu of makefile
#include <xran.cpp>     // in lieu of makefile
#include <xranxstr.cpp> // in lieu of makefile
typedef fsu::String        ElementType;
typedef fsu::Random_String Random_class;
const char* typestring = "String";
const long unsigned int maxSize        =   4000;
const long unsigned int maxNodes       =   4000;
const      unsigned int ranBound       =      8;  // max length of strings
const long unsigned int reportInterval =  10000;
const      unsigned int getPercent     =      30;    // to control
const      unsigned int putPercent     =      30;    // growth rate
const      unsigned int assignPercent  =      10; // and volatility
ElementType RandomObject( Random_class& ranobj )
{
  return ranobj(ranBound);
}
// end A2 */

/**********************************/
/*     select container type      */
/**********************************/

/*// BST w ADT-based iterators
#include <bst_adt.h>
const char* containerstring = "BST_ADT";
typedef fsu::BST_ADT<ElementType> BST;
bool Check(const BST& x, char command)
{
  bool val(0);
  if (command != '0') val = 1;
  return x.CheckBST(val);
}
// */

/* // BST w thread-based iterators
#include <bst_threaded.h>
const char* containerstring = "BST_threaded";
typedef fsu::BST_Threaded<ElementType> BST;
bool Check(const BST& x, char command)
{
  bool val(0);
  if (command != '0') val = 1;
  return x.CheckBST(val);
}
// */

 // RBLLT w ADT-based iterators
#include <rbllt_adt.h>
const char* containerstring = "RBLLT_ADT";
typedef fsu::RBLLT_ADT<ElementType> BST;
bool Check(const BST& x, char command)
{
  int val;
  switch(command)
  {
    case '0': val = 0; break;
    case '1': val = 1; break;
    default: val = 2; break;
  }  
  return x.CheckRBLLT(val);
}
// */

/* // RBLLT w Navigator-based iterators
#include <rbllt_full.h>
const char* containerstring = "RBLLT_full";
typedef fsu::RBLLT<ElementType> BST;
bool Check(const BST& x, char command)
{
  int val;
  switch(command)
  {
    case '0': val = 0; break;
    case '1': val = 1; break;
    default: val = 2; break;
  }  
  return x.CheckRBLLT(val);
}
// */

typedef BST::Iterator Iterator;
typedef BST::LevelorderIterator LevelorderIterator;

// constants for number of containers and operations
const unsigned int numObj = 3; // containers x0, x1, x2
const unsigned int numOps = 7; // operations 0..6
// 0=Put  1=Get  2=Insert  3=Retrieve  4=Erase 
// 5=Size,Clear  6=assignment 


template < class C >
void WriteReport(const C& x, char n, unsigned long numreports);

template < class C >
bool Traverse(const C& x);

int main(int argc, char* argv[] )
{
  if (argc < 2)
  {
    std::cout << " ** arguments:\n"
              << "    1: number of reports (enter 0 for unlimited) (REQUIRED)\n"
              << "    2: verbose (OPTIONAL)\n"
              << " Try again\n";
    return 0;
  }
  size_t maxrpts = atoi(argv[1]);

  bool VERBOSE = 0;
  if (argc > 2) VERBOSE = 1;

  // objects
  BST x0, x1, x2;
  Iterator i, j;
  Random_class   ranobj;
  ElementType    tval;

  // controls
  fsu::Random_int ranint;
  unsigned long numtrials(0);
  unsigned long numrpts(0); 
  unsigned int option;
  size_t size;

  std::cout << "\nStarting dynamic random test of " << containerstring << " < " << typestring << " >"
            << "\n\n" << std::flush;
  while (1)
  {
    option = ranint(0,numObj);
    switch(option)
    {
      case 0:
      option = ranint(0,numOps);
        switch (option)
        {
          case 0:   // Put (t)
            option = ranint(0,100);
            if (option < putPercent)
            {
              tval = RandomObject(ranobj);
              if (VERBOSE) std::cerr << " x0.Put(" << tval << ")";
              x0.Put(tval);
              if (VERBOSE) std::cerr << ".\n";
            }
            break;
        
          case 1:   // void Get (t)
            option = ranint(0,100);
            if (option < getPercent)
            {
              tval = RandomObject(ranobj);
              if (VERBOSE) std::cerr << " x0.Get(" << tval << ")";
              x0.Get(tval);
              if (VERBOSE) std::cerr << ".\n";
            }
            break;
        
          case 2:   // Insert (t)
            option = ranint(0,100);
            if (option < putPercent)
            {
              tval = RandomObject(ranobj);
              if (VERBOSE) std::cerr << " x0.Insert(" << tval << ")";
              x0.Insert(tval);
              if (VERBOSE) std::cerr << ".\n";
            }
            break;
        
          case 3:   // Retrieve (t)
            tval = RandomObject(ranobj);
            if (VERBOSE) std::cerr << " x0.Retrieve(" << tval << ")";
            x0.Retrieve(tval);
            if (VERBOSE) std::cerr << ".\n";
            break;
        
          case 4:   // Erase (t)
            tval = RandomObject(ranobj);
            if (VERBOSE) std::cerr << " x0.Erase(" << tval << ")";
            x0.Erase(tval);
            if (VERBOSE) std::cerr << ".\n";
            break;
        
          case 5:   // void Size()
            if (VERBOSE) std::cerr << " x0.Size()";
            size = x0.Size();
            if (VERBOSE) std::cerr << ".\n";
            if (size > maxSize)
            {
              x0.Clear();
              std::cout << " ** x0 cleared at size = " << size << std::endl;
            }
            break;

          case 6:  // assignment
            option = ranint(0,100);
            if (option < assignPercent)
            {
              option = ranint(0,numObj);
              switch(option)
              {
              case 0:
                if (VERBOSE) std::cerr << " x0 = x0";
                x0 = x0;
                if (VERBOSE) std::cerr << ".\n";
                break;
              case 1:
                if (VERBOSE) std::cerr << " x0 = x1";
                x0 = x1;
                if (VERBOSE) std::cerr << ".\n";
                break;
              case 2:
                if (VERBOSE) std::cerr << " x0 = x2";
                x0 = x2;
                if (VERBOSE) std::cerr << ".\n";
                break;
              }
              if (VERBOSE) x0.Snapshot("snapshot=.x0");
            }
            break;

          default: std::cout << " ** bad operation number\n";

        }   // end switch() x0 operations

      case 1:
        option = ranint(0,numOps); 
        switch (option)
        {
          case 0:   // Put (t)
            option = ranint(0,100);
            if (option < putPercent)
            {
              tval = RandomObject(ranobj);
              if (VERBOSE) std::cerr << " x1.Put(" << tval << ")";
              x1.Put(tval);
              if (VERBOSE) std::cerr << ".\n";
            }
            break;
        
          case 1:   // void Get (t)
            option = ranint(0,100);
            if (option < getPercent)
            {
              tval = RandomObject(ranobj);
              if (VERBOSE) std::cerr << " x1.Get(" << tval << ")";
              x1.Get(tval);
              if (VERBOSE) std::cerr << ".\n";
            }
            break;
        
          case 2:   // Insert (t)
            option = ranint(0,100);
            if (option < putPercent)
            {
              tval = RandomObject(ranobj);
              if (VERBOSE) std::cerr << " x1.Insert(" << tval << ")";
              x1.Insert(tval);
              if (VERBOSE) std::cerr << ".\n";
            }
            break;
        
          case 3:   // Retrieve (t)
            tval = RandomObject(ranobj);
            if (VERBOSE) std::cerr << " x1.Retrieve(" << tval << ")";
            x1.Retrieve(tval);
            if (VERBOSE) std::cerr << ".\n";
            break;
        
          case 4:   // Erase (t)
            tval = RandomObject(ranobj);
            if (VERBOSE) std::cerr << " x1.Erase(" << tval << ")";
            x1.Erase(tval);
            if (VERBOSE) std::cerr << ".\n";
            break;
        
          case 5:   // void Size()
            if (VERBOSE) std::cerr << " x1.Size()";
            size = x1.Size();
            if (VERBOSE) std::cerr << ".\n";
            if (size > maxSize)
            {
              x1.Clear();
              std::cout << " ** x1 cleared at size = " << size << std::endl;
            }
            break;

          case 6:  // assignment
            option = ranint(0,100);
            if (option < assignPercent)
            {
              option = ranint(0,numObj);
              switch(option)
              {
              case 0:
                if (VERBOSE) std::cerr << " x1 = x0";
                x1 = x0;
                if (VERBOSE) std::cerr << ".\n";
                break;
              case 1:
                if (VERBOSE) std::cerr << " x1 = x1";
                x1 = x1;
                if (VERBOSE) std::cerr << ".\n";
                break;
              case 2:
                if (VERBOSE) std::cerr << " x1 = x2";
                x1 = x2;
                if (VERBOSE) std::cerr << ".\n";
                break;
              }
              if (VERBOSE) x1.Snapshot("snapshot=.x1");
            }
            break;

          default: std::cout << " ** bad operation number\n";

        }   // end switch() x1 operations

      case 2:
        option = ranint(0,numOps); 
        switch (option)
        {
          case 0:   // Put (t)
            option = ranint(0,100);
            if (option < putPercent)
            {
              tval = RandomObject(ranobj);
              if (VERBOSE) std::cerr << " x2.Put(" << tval << ")";
              x2.Put(tval);
              if (VERBOSE) std::cerr << ".\n";
            }
            break;
        
          case 1:   // void Get (t)
            option = ranint(0,100);
            if (option < getPercent)
            {
              tval = RandomObject(ranobj);
              if (VERBOSE) std::cerr << " x2.Get(" << tval << ")";
              x2.Get(tval);
              if (VERBOSE) std::cerr << ".\n";
            }
            break;
        
          case 2:   // Insert (t)
            option = ranint(0,100);
            if (option < putPercent)
            {
              tval = RandomObject(ranobj);
              if (VERBOSE) std::cerr << " x2.Insert(" << tval << ")";
              x2.Insert(tval);
              if (VERBOSE) std::cerr << ".\n";
            }
            break;
        
          case 3:   // Retrieve (t)
            tval = RandomObject(ranobj);
            if (VERBOSE) std::cerr << " x2.Retrieve(" << tval << ")";
            x2.Retrieve(tval);
            if (VERBOSE) std::cerr << ".\n";
            break;
        
          case 4:   // Erase (t)
            tval = RandomObject(ranobj);
            if (VERBOSE) std::cerr << " x2.Erase(" << tval << ")";
            x2.Erase(tval);
            if (VERBOSE) std::cerr << ".\n";
            break;
        
          case 5:   // void Size()
            if (VERBOSE) std::cerr << " x2.Size()";
            size = x2.Size();
            if (VERBOSE) std::cerr << ".\n";
            if (size > maxSize)
            {
              x2.Clear();
              std::cout << " ** x2 cleared at size = " << size << std::endl;
            }
            break;

          case 6:  // assignment
            option = ranint(0,100);
            if (option < assignPercent)
            {
              option = ranint(0,numObj);
              switch(option)
              {
              case 0:
                if (VERBOSE) std::cerr << " x2 = x0";
                x2 = x0;
                if (VERBOSE) std::cerr << ".\n";
                break;
              case 1:
                if (VERBOSE) std::cerr << " x2 = x1";
                x2 = x1;
                if (VERBOSE) std::cerr << ".\n";
                break;
              case 2:
                if (VERBOSE) std::cerr << " x2 = x2";
                x2 = x2;
                if (VERBOSE) std::cerr << ".\n";
                break;
              }
              if (VERBOSE) x2.Snapshot("snapshot=.x2");
            }
            break;

          default: std::cout << " ** bad operation number\n";

        }   // end switch() x2 operations

    } // end switch() case x2

    ++numtrials;
    if (numtrials == reportInterval)
    {
      ++numrpts;
      numtrials = 0;
      option = ranint(0,3);
      switch(option)
      {
      case 0: WriteReport(x0,'0',numrpts); break;
      case 1: WriteReport(x1,'1',numrpts); break;
      case 2: WriteReport(x2,'2',numrpts); break;
      }
      if (numrpts == maxrpts)
      {
        std::cout << "\nTest Complete\n";
        break;
      }
    }

  }  // end while()
  return EXIT_SUCCESS;
}  // end main()

template < class C >
bool Traverse (const C& x)
{
  bool ok = 1;
  typename C::Iterator i, a;
  size_t n;
  for (i = x.Begin(), n = 0; i != x.End(); ++i, ++n)
  {
    a = i;
    ++a;
    if (a != x.End())
    {
      --a;
      if (a != i)
      {
        std::cout << "  ** --(++) reciprocity failure at position: " << n << " , value: " << *i << '\n'; 
        ok = 0;
      }
    }
    a = i;
    --a;
    if (a != x.rEnd())
    {
      ++a;
      if (a != i)
      {
        std::cout << "  ** ++(--) reciprocity failure at position: " << n << " , value: " << *i << '\n'; 
        ok = 0;
      }
    }
  }
  if (n != x.Size())
  {
    std::cout << "  ** S-L Mismatch: Size = " << x.Size() << " , Traversal Length = " << n << '\n'; 
    ok = 0;
  }
  return ok;
}

template < class C >
void WriteReport(const C& x, char n, unsigned long numrpts)
{
  size_t size = x.Size();
  size_t numnodes = x.NumNodes();
  std::cout << std::showpoint << std::fixed << std::setprecision(2);
  std::cout << "\nTesting " << containerstring << " < " << typestring << " >"
            << " at trial " << numrpts << " x " << reportInterval << ":\n"
            << "  x" << n << ".Size()              ==  " << size << '\n' 
            << "  x" << n << ".NumNodes()          ==  " << numnodes << '\n' 
            << "  x" << n << ".Height()            ==  " << x.Height() << '\n'
            << "  optimal ht (size)      ==  " << (size_t)(floor(log2(size))) << '\n'
            << "  optimal ht (numnodes)  ==  " << (size_t)(floor(log2(numnodes))) << std::endl;
  if (Traverse(x))
  {
    std::cout << "  Traverse(x" << n << ") OK\n";
  }
  else
  {
    std::cout << " ** Traverse failure\n";
    x.Snapshot("snapshot.traverse");
    std::cout << "    Tree data stored in \"snapshot.traverse\"\n";
    exit(EXIT_FAILURE);
  }
  if (Check(x,'0'))
  {
    std::cout << "  Check(x" << n << ") OK\n";
  }
  else
  {
    std::cout << " ** Check failure\n";
    x.Snapshot("snapshot.traverse");
    std::cout << "  Tree data stored in \"snapshot.traverse\"\n";
    exit(EXIT_FAILURE);
  }
}
