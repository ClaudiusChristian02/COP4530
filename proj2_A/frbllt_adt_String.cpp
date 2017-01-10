/*
    fbst.cpp
    Chris Lacher
    03/13/15

    functionalty test harness for various 2-way binary search trees

    runs in BATCH mode with command file
    'x' switches to interactive after comands are executed

    For the RBLLT case, uncover the Rehash option.

*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <xstring.h>
#include <xstring.cpp>

/********************************/
/*     select element type      */
/********************************/

/*// type int
typedef int ElementType;
int dw = 1;
int digits = 1;
const char fill = '-';
const char ofc = ' ';
const char* typestring = "int";
int CorrectDataWidth(const ElementType& t, int dw)
{
  int digits = 1+(size_t)log10(t);
  if (dw < digits)
    dw = digits;
  // std::cout << "dw = " << dw << '\n';
  return dw;
}
// */

/* // type char
typedef char ElementType;
int dw = 1;
const char fill = '-';
const char ofc = '\0';
const char* typestring = "char";
int CorrectDataWidth(const ElementType& , int )
{
  return 1;
}
// */

/* // type CHAR
#include <CHAR.h>
typedef CHAR ElementType;
int dw = 1;
const char fill = '-';
const char ofc = '\0';
const char* typestring = "CHAR";
int CorrectDataWidth(const ElementType& , int )
{
  return 1;
}
// */

 // type String
typedef fsu::String ElementType;
int dw = 1;
const char fill = '-';
const char ofc = '\t';
const char* typestring = "fsu::String";
int CorrectDataWidth(const ElementType& t, int dw)
{
  int digits = t.Length();
  if (dw < digits)
    dw = digits;
  return dw;
}
// */

/**********************************/
/*     select container type      */
/**********************************/

/* // BST w ADT-based iterators
#include <bst_adt.h>
const char* containerstring = "BST_ADT";
typedef fsu::BST_ADT<ElementType> BST;
typedef fsu::BST_ADT<ElementType>::Iterator Iterator;
typedef fsu::BST_ADT<ElementType>::LevelorderIterator LevelorderIterator;
void Check(const BST& x, char command)
{
  bool val(0);
  if (command != '0') val = 1;
  x.CheckBST(val);
}
// */

/* // BST w thread-based iterators
#include <bst_threaded.h>
const char* containerstring = "BST_threaded";
typedef fsu::BST_Threaded<ElementType> BST;
typedef fsu::BST_Threaded<ElementType>::Iterator Iterator;
typedef fsu::BST_Threaded<ElementType>::LevelorderIterator LevelorderIterator;
void Check(const BST& x, char command)
{
  bool val(0);
  if (command != '0') val = 1;
  x.CheckBST(val);
}
// */

 // RBLLT w ADT-based iterators
#include <rbllt_adt.h>
const char* containerstring = "RBLLT_ADT";
typedef fsu::RBLLT_ADT<ElementType> BST;
typedef fsu::RBLLT_ADT<ElementType>::Iterator Iterator;
typedef fsu::RBLLT_ADT<ElementType>::LevelorderIterator LevelorderIterator;
void Check(const BST& x, char command)
{
  int val;
  switch(command)
  {
    case '0': val = 0; break;
    case '1': val = 1; break;
    default:  val = 2; break;
  }  
  x.CheckRBLLT(val);
}
// */

/* // RBLLT w Thread-based iterators
#include <rbllt_threaded.h>
const char* containerstring = "RBLLT_Threaded";
typedef fsu::RBLLT_Threaded<ElementType> BST;
typedef fsu::RBLLT_Threaded<ElementType>::Iterator Iterator;
typedef fsu::RBLLT_Threaded<ElementType>::LevelorderIterator LevelorderIterator;
void Check(const BST& x, char command)
{
  int val;
  switch(command)
  {
    case '0': val = 0; break;
    case '1': val = 1; break;
    default:  val = 2; break;
  }  
  x.CheckRBLLT(val);
}
// */

/* // RBLLT 3-way nodes with 4 iterator types
#include <rbllt_full.h>
const char* containerstring = "RBLLT_full";
typedef fsu::RBLLT<ElementType> BST;
typedef fsu::RBLLT<ElementType>::Iterator Iterator;
typedef fsu::RBLLT<ElementType>::LevelorderIterator LevelorderIterator;
void Check(const BST& x, char command)
{
  int val;
  switch(command)
  {
    case '0': val = 0; break;
    case '1': val = 1; break;
    default: val = 2; break;
  }  
  x.CheckRBLLT(val);
}
// */

void DisplayMenu(std::ostream& os = std::cout);

// copy test
template < class C >
void CopyTest ( const C& x1,  C x2 );

// assign test
template < class C >
void AssignTest ( const C& x1 );

int main(int argc, char* argv[])
{
  BST x1;
  Iterator i, a, l, u;
  bool ok = 1;
  size_t n;
  ElementType element;
  char        command;
  size_t      size, numnodes;
  std::ifstream com; // command file reader
  std::ifstream ifs; // data file reader
  fsu::String   filename; // data file name
  std::istream * inptr = &std::cin;
  bool BATCH = 0;
  if (argc > 1)
  {
    BATCH = 1;
    com.open(argv[1]);
    if (com.fail())
    {
      std::cout << " ** unable to open file " << argv[1] << '\n'
                << "    try again\n";
      return EXIT_FAILURE;
    }
    inptr = &com;
  }
  if (!BATCH) DisplayMenu();
  do
  {
    std::cout << "command ('M' for menu, 'Q' to quit): ";
    *inptr >> command;
    if (BATCH) std::cout << command;
    switch(command)
    {
    case '1': // Insert
      *inptr >> element;
      if (inptr->fail())
      {
	std::cout << " ** bad element encountered - re-enter command\n";
	inptr->clear();
	while (command != '\n') command = inptr->get();
	inptr->clear();
	break;
      }
      if (BATCH) std::cout << ' ' << element << '\n';
      dw = CorrectDataWidth(element,dw);
      std::cout << "  x1.Insert(" << element << ")\n";
      x1.Insert(element);
      break;
    case 'r': case 'R':
      *inptr >> element;
      if (inptr->fail())
      {
	std::cout << " ** bad element encountered - re-enter command\n";
	inptr->clear();
	while (command != '\n') command = inptr->get();
	inptr->clear();
	break;
      }
      if (BATCH) std::cout << ' ' << element << '\n';
      if (x1.Retrieve(element))
        std::cout << "  \"" << element << "\" Retrieved\n";
      else
        std::cout << "  \"" << element << "\" NOT Retrieved\n";
      break;
    case 'p': case 'P':
      *inptr >> element;
      if (inptr->fail())
      {
	std::cout << " ** bad element encountered - re-enter command\n";
	inptr->clear();
	while (command != '\n') command = inptr->get();
	inptr->clear();
	break;
      }
      if (BATCH) std::cout << ' ' << element << '\n';
      dw = CorrectDataWidth(element,dw);
      std::cout << "  x1.Put(" << element << ")\n";
      x1.Put(element);
      break;
    case 'g': case 'G':
      *inptr >> element;
      if (inptr->fail())
      {
	std::cout << " ** bad element encountered - re-enter command\n";
	inptr->clear();
	while (command != '\n') command = inptr->get();
	inptr->clear();
	break;
      }
      if (BATCH) std::cout << ' ' << element << '\n';
      dw = CorrectDataWidth(element,dw);
      std::cout << "  " << x1.Get(element) << " = x1.Get(" << element << ")\n";
      break;
    case 'e': case 'E':
      *inptr >> element;
      if (inptr->fail())
      {
	std::cout << " ** bad element encountered - re-enter command\n";
	inptr->clear();
	while (command != '\n') command = inptr->get();
	inptr->clear();
	break;
      }
      if (BATCH) std::cout << ' ' << element << '\n';
      std::cout << "  " << x1.Erase(element)
                << " = x1.Erase(" << element << ")\n";
      break;
    case 'l': case 'L':
      *inptr >> filename;
      if (BATCH) std::cout << ' ' << filename << '\n';
      ifs.open(filename.Cstr());
      if (ifs.fail())
      {
	std::cout << "  ** Unable to open file " << filename << '\n';
        ifs.clear();
        break;
      }
      while (ifs >> element)
      {
        dw = CorrectDataWidth(element,dw);
        x1.Insert(element);
      }
      ifs.clear();
      ifs.close();
      std::cout << "  ** set data read and stored\n";
      break;
    case '=':
      if (BATCH) std::cout << '\n';
      CopyTest(x1, x1);
      AssignTest(x1);
      break;
    case 'd': case 'D':
      *inptr >> command;
      if (BATCH) std::cout << command << '\n';
      switch (command)
      {
        case '0': x1.DumpBW(std::cout); break;
        case '1': x1.Dump(std::cout); break;
        case '2': x1.Dump(std::cout,dw); break;
        case '3': x1.Dump(std::cout,dw,fill); break;
        default: std::cout << " ** undefined command \"" << command << "\" (level 2)\n";
          while (command != '\n')
            command = inptr->get(); 
      }
      break;
    case 's': case 'S':
      *inptr >> command;
      if (BATCH) std::cout << command << '\n';
      size = x1.Size();
      numnodes = x1.NumNodes();
      std::cout << "  x1.Size()           = " << size << '\n'
                << "  x1.NumNodes()       = " << numnodes << '\n'
                << "  x1.Height()         = " << x1.Height() << '\n';
      if (size > 0)
        std::cout << "  optimal ht (size)   = " << (size_t)(floor(log2(size))) << '\n';
      if (numnodes > 0)
        std::cout << "  optimal ht (nodes)  = " << (size_t)(floor(log2(numnodes))) << '\n';
      // check iterator reciprocity
      ok = 1;
      for (i = x1.Begin(), n = 0; i != x1.End(); ++i, ++n)
      {
        a = i;
        ++a;
        if (a != x1.End())
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
        if (a != x1.rEnd())
        {
          ++a;
          if (a != i)
          {
            std::cout << "  ** ++(--) reciprocity failure at position: " << n << " , value: " << *i << '\n'; 
            ok = 0;
          }
        }
      }
      if (n != x1.Size())
      {
        std::cout << "  ** S-L Mismatch: Size = " << x1.Size() << " , Traversal Length = " << n << '\n'; 
        ok = 0;
      }
      if (ok) std::cout << "  ** Iterator reciprocity check: OK\n";
      Check(x1,command);
      break;
    case 'c': case 'C':
      if (BATCH) std::cout << '\n';
      x1.Clear();
      break;
    case 't':  case 'T':
      if (BATCH) std::cout << '\n';
      std::cout << "  Traversal (recursive): ";
      x1.Display(std::cout,ofc);
      std::cout << '\n';
      std::cout << "  Traversal  (Iterator): ";
      if (ofc == '\0')
        for (Iterator i = x1.Begin(); i != x1.End(); ++i)
        {
          std::cout << *i;
        }
      else
        for (Iterator i = x1.Begin(); i != x1.End(); ++i)
        {
          std::cout << *i << ofc;
        }
      std::cout << '\n';
      std::cout << "  rTraversal (Iterator): ";
      if (ofc == '\0')
        for (Iterator i = x1.rBegin(); i != x1.rEnd(); --i)
        {
          std::cout << *i;
        }
      else
        for (Iterator i = x1.rBegin(); i != x1.rEnd(); --i)
        {
          std::cout << *i << ofc;
        }
      std::cout << '\n';
      std::cout << "  Levelorder (Iterator): ";
      if (ofc == '\0')
        for (LevelorderIterator i = x1.BeginLevelorder(); i != x1.EndLevelorder(); ++i)
        {
          std::cout << *i;
        }
      else
        for (LevelorderIterator i = x1.BeginLevelorder(); i != x1.EndLevelorder(); ++i)
        {
          std::cout << *i << ofc;
        }
      std::cout << '\n';
      break;
    case 'x': case 'X':
      if (BATCH)
      {
	std::cout << '\n';
	com.close();
	inptr = &std::cin;
	std::cout << "   [ switched to keyboard input ]\n";
	BATCH = 0;
	DisplayMenu();
      }
      else
      {
	std::cout << " ** already using keyboard input\n";
      }
      break;
    case 'm': case 'M':
      if (BATCH) std::cout << '\n';
      DisplayMenu();
      break;
    case 'q': case 'Q':
      if (BATCH)
      {
	std::cout << '\n';
	com.close();
      }
      command = 'q';
      break;
    case 'f': case 'F': // Includes, LowerBound, UpperBound
      *inptr >> element;
      if (inptr->fail())
      {
	std::cout << " ** bad element encountered - re-enter command\n";
	inptr->clear();
	while (command != '\n') command = inptr->get();
	inptr->clear();
	break;
      }
      if (BATCH) std::cout << ' ' << element << '\n';
      l = x1.LowerBound(element);
      if (l == x1.End())
        std::cout << "  " << "End() = x1.LowerBound ( " << element << " )\n";
      else
        std::cout << "  " << *l << " = *(x1.LowerBound ( " << element << " ))\n";
      u = x1.UpperBound(element);
      if (u == x1.End())
        std::cout << "  " << "End() = x1.UpperBound ( " << element << " )\n";
      else
        std::cout << "  " << *u << " = *(x1.UpperBound ( " << element << " ))\n";
      i = x1.Includes(element);
      if (i == x1.End())
        std::cout << "  " << "End() = x1.Includes ( " << element << " )\n";
      else
        std::cout << "  " << *i << " = *(x1.Includes ( " << element << " ))\n";
      // check consistency among L,U,I
      if (l == u) // L == U implies not found
      {
        if (i != x1.End()) 
          std::cout << " ** LUI inconsistency: L == U and I != End\n";
      }
      else // L != U implies found at L
      {
        if (l != i)
        {
          std::cout << " ** LUI inconsistency: L != U and I != L\n";
        }
        a = l;
        ++a;
        if (a != u)
        {
          std::cout << " ** LUI inconsistency: L != U and ++L != U\n";
          if (a.Valid())
          {
            std::cout << "    *++L = " << *a << '\n';
          }
          else
          {
            std::cout << "    ++L not valid\n";
          }
        }
        if (u != x1.End())
        {
          a = u;
          --a;
          if (a != l)
          {
            std::cout << " ** LUI inconsistency: L != U and L != --U\n";
            if (a.Valid())
            {
              std::cout << "    *--U = " << *a << '\n';
            }
            else
            {
              std::cout << "    --U not valid\n";
            }
          }
        }
      }
      break; // Find = LB, UB, Includes

   /* case 'h': case 'H':
      if (BATCH) std::cout << '\n';
      x1.Rehash();
      break; // */

    default:
      if (BATCH) std::cout << '\n';
      std::cout << " ** undefined command << \"" << command << "\" (level 1)\n";
      while (command != '\n')
        command = inptr->get(); 
    }
  }
  while (command != 'q');
}

void DisplayMenu(std::ostream& os)
{
  os << "   fsu::" << containerstring << " < " << typestring << " > x;\n"
     << "   OPERATION                ENTRY\n"
     << "   ---------                -----\n"
     << "   Load (Insert) from file ....... L filename\n"
     << "   x.Insert(val) ................. 1 val\n"
     << "   x.Retrieve(val) ............... R val\n"
     << "   x.Put(val) .................... P val\n"
     << "   x.Get(val) .................... G val\n"
     << "   x.Erase(val) .................. E val\n"
//     << "   x.Rehash() .................... H\n"
     << "   x.Clear() ..................... C\n"
     << "   x.DumpBW(cout) ................ D0\n"
     << "   x.Dump(cout) .................. D1\n"
     << "   x.Dump(cout,ofc) .............. D2\n"
     << "   x.Dump(cout,ofc,fill) ......... D3\n"
     << "   x.CheckBST(?) [levels 0,1,2] .. S?\n"
     << "   Find (Includes, LB, UB) ....... F val\n"
     << "   traversals .................... T\n"
     << "   copy and assign tests ......... =\n"
     << "   switch from batch mode ........ X\n"
     << "   quit program .................. Q\n";
}

// copy test
template < class C >
void CopyTest ( const C& x1,  C x2 )
{
  size_t size1, size2,
         height1, height2,
         nodes1, nodes2;
  bool ok = 1;
  if (x1 != x2)
  {
    std::cout << " ** CopyTest: original and copy not equal\n";
    ok = 0;
  }
  if (!x2.CheckBST(0))
  {
    std::cout << " ** CopyTest: copy.CheckBST() failed\n";
    ok = 0;
  }
  nodes1  = x1.NumNodes();
  size1   = x1.Size();
  height1 = x1.Height();
  nodes2  = x2.NumNodes();
  size2   = x2.Size();
  height2 = x2.Height();
  if (size1  != size2)
  {
    std::cout << " ** CopyTest: original and copy have different size\n";
    ok = 0;
  }
  if (height1 != height2)
  {
    std::cout << " ** CopyTest: original and copy have different height\n";
    ok = 0;
  }
  if (nodes1 != nodes2)
  {
    std::cout << " ** CopyTest: original and copy have different node counts\n";
    ok = 0;
  }
  // iterator test
  typename C::Iterator i1, i2;
  size_t p = 0;
  for (i1 = x1.Begin(), i2 = x2.Begin(); i1!= x1.End() && i2 != x2.End(); ++i1, ++i2, ++p)
  {
    if (*i1 != *i2)
    {
      std::cout << " ** CopyTest traversal failure at position " << p << ":\n"
                << "   " << *i1 << " = *i1\n"
                << "   " << *i2 << " = *i2\n";
      ok = 0;
    }
  }
  if (i2 != x2.End())
  {
    std::cout << " ** CopyTest traversal failure at position " << p << ":\n"
              << "    End() == i1\n"
              << "   " << *i1 << " = *i2\n";
    ok = 0;
  }
  if (i1!= x1.End())
  {
    std::cout << " ** CopyTest traversal failure at position " << p << ":\n"
              << "   " << *i1 << " = *i1\n"
              << "    End() == i2\n";
    ok = 0;
  }
  if (ok) std::cout << " CopyTest OK\n";
}

// assign test
template < class C >
void AssignTest ( const C& x1 )
{
  // fsu::BST<T,P> x2;
  C x2;
  size_t size1, size2,
         height1, height2,
         nodes1, nodes2;
  bool ok = 1;
  size2 = x2.Size();
  x2 = x1;
  if (x1 != x2)
  {
    std::cout << " ** AssignTest: original and copy not equal\n";
    ok = 0;
  }
  if (!x2.CheckBST(0))
  {
    std::cout << " ** AssignTest: assignee.CheckBST() failed\n";
    ok = 0;
  }
  nodes1  = x1.NumNodes();
  size1   = x1.Size();
  height1 = x1.Height();
  nodes2  = x2.NumNodes();
  size2   = x2.Size();
  height2 = x2.Height();
  if (size1  != size2)
  {
    std::cout << " ** AssignTest: original and copy have different size\n";
    ok = 0;
  }
  if (height1  != height2)
  {
    std::cout << " ** AssignTest: original and copy have different height\n";
    ok = 0;
  }
  if (nodes1 != nodes2)
  {
    std::cout << " ** AssignTest: original and copy have different node counts\n";
    ok = 0;
  }
  // iterator test
  typename C::Iterator i1, i2;
  size_t p = 0;
  for (i1 = x1.Begin(), i2 = x2.Begin(); i1!= x1.End() && i2 != x2.End(); ++i1, ++i2)
  {
    if (*i1 != *i2)
    {
      std::cout << " ** AssignTest traversal failure at position " << p << ":\n"
                << "   " << *i1 << " = *i1\n"
                << "   " << *i2 << " = *i2\n";
      ok = 0;
    }
  }
  if (i2 != x2.End())
  {
    std::cout << " ** AssignTest traversal failure at position " << p << ":\n"
              << "    End() == i1\n"
              << "   " << *i1 << " = *i2\n";
    ok = 0;
  }
  if (i1!= x1.End())
  {
    std::cout << " ** AssignTest traversal failure at position " << p << ":\n"
              << "   " << *i1 << " = *i1\n"
              << "    End() == i2\n";
    ok = 0;
  }
  if (ok) std::cout << " AssignTest OK\n";
  // */
}
