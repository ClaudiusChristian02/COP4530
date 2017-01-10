/*
    fvector.cpp 
    02/8/10
    Chris Lacher

    Copyright 2010, R. C. Lacher
*/

#include <iostream>
#include <fstream>
#include <cctype>  // tolower()

// =====================
// ===== group A =======
// =====================

// A1: makes vectors of char
typedef char  ElementType;
const char ofc = '\0';
const ElementType fillValue(' ');
const char* vT = "char";
const char code0 = 'c';
// end A1 */

/* // A2: makes vectors of String
#include <xstring.h>
#include <xstring.cpp> // in lieu of makefile
typedef fsu::String  ElementType;
const char ofc = ' ';
const ElementType fillValue(" ");
const char* vT = "String";
const char code0 = 's';
// end A2 */

#include <vector.h>
typedef fsu::Vector<ElementType> ContainerType;
// */

void Preamble();
void DisplayContainerType(const char code0, const char code1);
void DisplayMenu();
void DisplayPrompt();

template < class C >
void CopyTest( C x )
{
  std::cout << "CopyTest:\n";
  std::cout << "Copied object size: " << x.Size() << '\n'
            << "              dump: ";
  x.Dump(std::cout);
  std::cout << '\n';
}

template < class C >
void AssignTest(const C& x)
{
  C x1;
  x1 = x;
  std::cout << "AssignTest:\n";
  std::cout << "Original object size: " << x.Size() << '\n'
            << "                dump: ";
  x.Dump(std::cout);
  std::cout << "Assignee object size: " << x1.Size() << '\n'
            << "                dump: ";
  x1.Dump(std::cout);
  std::cout << '\n';
}

void SkipDoc (std::istream& is)
{
  char ch = is.peek();
  while (ch == '#')
  {
    do ch = is.get();
    while (ch != '\n');
    ch = is.peek();
  }
}

int main( int argc, char* argv[] )
{
  bool BATCH = 0;
  if (argc > 1) BATCH = 1;
  std::istream* isptr = &std::cin;
  std::ifstream ifs;
  if (BATCH)
  {
    ifs.open(argv[1]);
    if (ifs.fail())
    {
      std::cout << " ** Error: cannot open file " << argv[1] << '\n';
      return 0;
    }
    SkipDoc(ifs);
    isptr = &ifs;
  }
  else
  {
    Preamble();
    DisplayMenu();
  }
  ContainerType x1, x2, x3;
  ContainerType::Iterator i, i1, i2, i3;
  ElementType  Tval;
  char option;
  size_t index;
  do
  {
    std::cout << "Enter [command][arguments] ('M' for menu, 'Q' to quit): ";
    *isptr >> option;
    if (BATCH) std::cout << option;
    // option = tolower(option);
    switch (option)
    {
      case '1': 
        *isptr >> option;
	if (BATCH) std::cout << option;
        // option = tolower(option);
        switch (option)
        {
/*        case '1':   // void PushFront (T)
            *isptr >> Tval;
	    if (BATCH) std::cout << Tval << '\n';
            x1.PushFront(Tval);
            break;
      
          case '2':   // void PushBack (T)
            *isptr >> Tval;
	    if (BATCH) std::cout << Tval << '\n';
            x1.PushBack(Tval);
            break;
        
          case '3':   // void PopFront()
	    if (BATCH) std::cout << '\n';
            x1.PopFront();
            break;
        
          case '4':   // void PopBack()
	    if (BATCH) std::cout << '\n';
            x1.PopBack();
            break;
*/
          case '1':   // void PushBack (T)
            *isptr >> Tval;
	    if (BATCH) std::cout << Tval << '\n';
            x1.PushBack(Tval);
            break;
        
          case '2':   // void PopBack()
	    if (BATCH) std::cout << '\n';
            x1.PopBack();
            break;

          case 'a':
	    if (BATCH) std::cout << '\n';
	    if (x1.Empty())
              std::cout << "x1 is empty\n";
            else
              std::cout << "x1.Front() == " << x1.Front() << '\n';
            break;

          case 'z':
	    if (BATCH) std::cout << '\n';
	    if (x1.Empty())
              std::cout << "x1 is empty\n";
            else
              std::cout << "x1.Back() == " << x1.Back() << '\n';
            break;

          case 'c':   // void Clear ()
	    if (BATCH) std::cout << '\n';
            x1.Clear();
            i1 = x1.Begin();
            break;

          case 'C':   // CopyTest ()
	    if (BATCH) std::cout << '\n';
            CopyTest(x1);
            AssignTest(x1);
            break;

          case '*':   // *i
            option = isptr->get();
	    if (BATCH) std::cout << option;
            switch(option)
            {
              case '=':
                *isptr >> Tval;
		if (BATCH) std::cout << Tval << '\n';
                if (i1 != x1.End())
                  *i1 = Tval;
                else
                  std::cout << " i1 is not valid\n";
                break;
              default:
		if (BATCH) std::cout << '\n';
                if (i1 != x1.End())
                  std::cout << "*i1 == " << *i1 << '\n';
                else
                  std::cout << " i1 == NULL\n";
                break;
            }
            break;
        
          case 'u':   // void Update(T)
            *isptr >> Tval;
	    if (BATCH) std::cout << Tval << '\n';
            if (i1 != x1.End())
            {
              *i1 = Tval;
              std::cout << "Update completed\n";
            }
            else
              std::cout << "Cannot update -- iterator invalid\n";
            break;
        
          case 'b':   // Begin()
	    if (BATCH) std::cout << '\n';
            i1 = x1.Begin();
            break;

          case 'r':   // rBegin()
	    if (BATCH) std::cout << '\n';
            i1 = x1.rBegin();
            break;

          case 's':   // Size() && Capacity() || SetSize() || SetCapacity()
            option = isptr->get();
	    if (BATCH) std::cout.put(option);
            switch(option)
            {
              case 's':
                *isptr >> index;
		if (BATCH) std::cout << index << '\n';
                x1.SetSize(index,fillValue);
                i1 = x1.Begin();
                break;
              case 'c':
                *isptr >> index;
		if (BATCH) std::cout << index << '\n';
                x1.SetCapacity(index);
                i1 = x1.Begin();
                break;
              default:
		if (BATCH) std::cout << '\n';
                std::cout << "Size     == " << x1.Size() << '\n';
                std::cout << "Capacity == " << x1.Capacity() << '\n'; 
                break;
            }
            break;

          case '[':   // i[index], i[index]=t
            *isptr >> index;
            *isptr >> option;  // assumed to be ']'
	    if (BATCH) std::cout << index << option;
            option = isptr->get();
	    if (BATCH) std::cout.put(option);
            switch(option)
            {
              case '=':
                *isptr >> Tval;
		if (BATCH) std::cout << Tval << '\n';
                if (i1 != x1.End())
                  i1[index] = Tval;
                else
                  std::cout << "i1 not valid\n";
                break;
              default:
		if (BATCH) std::cout << '\n';
                if (i1 != x1.End())
                  std::cout << "i1[" << index << "] == " << i1[index] << '\n';
                else
                  std::cout << "i1 not valid\n";
                break;
            }
            break;

          case 'e':   // int empty()
	    if (BATCH) std::cout << '\n';
            std::cout << "x1 is";
            if (!x1.Empty())
              std::cout << " not";
            std::cout << " empty\n";
            break;

          case 'd':  // test iterator
            if (BATCH) std::cout << '\n';
            std::cout << "  x1.Display(std::cout): ";
            x1.Display(std::cout);
            std::cout << '\n';
            std::cout << "            Traverse x1: ";
            for (i = x1.Begin(); i != x1.End(); ++i)
            {
              std::cout << *i;
            }
            std::cout << '\n';
            std::cout << "           rTraverse x1: ";
            for (i = x1.rBegin(); i != x1.rEnd(); --i)
            {
              std::cout << *i;
            }
            std::cout << '\n';
            break;
          
          case '=':
            *isptr >> option;
	    if (BATCH) std::cout << option;
            switch(option)
            {
              case '1': 
		if (BATCH) std::cout << '\n';
		x1 = x1;
		i1 = x1.Begin();
		break;
              case '2':
		if (BATCH) std::cout << '\n';
		x1 = x2;
		i1 = x1.Begin();
		break;
              case '3':
		if (BATCH) std::cout << '\n';
		x1 = x3;
		i1 = x1.Begin();
		break;
              case '=':
                *isptr >> option;
		if (BATCH) std::cout << option << '\n';
                switch(option)
                {
                  case '1':
                    if (x1 == x1)
                      std::cout << "x1 == x1\n";
                    else
                      std::cout << "x1 != x1\n";
                    break;
                  case '2':
                    if (x1 == x2)
                      std::cout << "x1 == x2\n";
                    else
                      std::cout << "x1 != x2\n";
                    break;
                  case '3':
                    if (x1 == x3)
                      std::cout << "x1 == x3\n";
                    else
                      std::cout << "x1 != x3\n";
                    break;
                }
                break;
            }
            break;

          case '!':
            *isptr >> option;  // assumed to be '='
	    if (BATCH) std::cout << option;
            *isptr >> option;
	    if (BATCH) std::cout << option << '\n';
            switch(option)
            {
              case '1':
                if (x1 != x1)
                  std::cout << "x1 != x1\n";
                else
                  std::cout << "x1 == x1\n";
                break;
              case '2':
                if (x1 != x2)
                  std::cout << "x1 != x2\n";
                else
                  std::cout << "x1 == x2\n";
                break;
              case '3':
                if (x1 != x3)
                  std::cout << "x1 != x3\n";
                else
                  std::cout << "x1 == x3\n";
                break;
            }
            break;

          case '+':   // ++(), +=()
            *isptr >> option;
	    if (BATCH) std::cout << option;
            switch(option)
            {
              case '+':
		if (BATCH) std::cout << '\n';
                ++i1;
                break;
              case '=':
                *isptr >> option;
		if (BATCH) std::cout << option << '\n';
                switch(option)
                {
                  case '1': x1 += x1; i1 = x1.Begin(); break;
                  case '2': x1 += x2; i1 = x1.Begin(); break;
                  case '3': x1 += x3; i1 = x1.Begin(); break;
                  default: std::cout << "** Unknown command -- try again\n";
                }
                break;
              default: std::cout << "** Unknown command -- try again\n";
              break;
            }
            break;
        
          case '-':   // --
            *isptr >> option;  // assumed to be '-'
	    if (BATCH) std::cout << option << '\n';
            --i1;
            break;
        
	  case 't':   case 'T': // traversal
	    if (BATCH) std::cout << '\n';
	    std::cout << "  Traversal:  ";
	    for (i = x1.Begin(); i != x1.End(); ++i)
	      std::cout << *i << ofc;
	    std::cout << '\n';
	    std::cout << "  rTraversal: ";
	    for (i = x1.rBegin(); i != x1.rEnd(); --i)
	      std::cout << *i << ofc;
	    std::cout << '\n';
            break;
        
          default:
            do
	    {
	      isptr->get(option);
	      if (BATCH) std::cout.put(option);
	    }
            while (option != '\n');
            std::cout << " ** Unrecognized command -- please try again\n";

        }  // end case '1'
        break;

      case '2': 
        *isptr >> option;
	if (BATCH) std::cout << option;
        // option = tolower(option);
        switch (option)
        {
/*        case '1':   // void PushFront (T)
            *isptr >> Tval;
	    if (BATCH) std::cout << Tval << '\n';
            x2.PushFront(Tval);
            break;
      
          case '2':   // void PushBack (T)
            *isptr >> Tval;
	    if (BATCH) std::cout << Tval << '\n';
            x2.PushBack(Tval);
            break;
        
          case '3':   // void PopFront()
	    if (BATCH) std::cout << '\n';
            x2.PopFront();
            break;
        
          case '4':   // void PopBack()
	    if (BATCH) std::cout << '\n';
            x2.PopBack();
            break;
*/
          case '1':   // void PushBack (T)
            *isptr >> Tval;
	    if (BATCH) std::cout << Tval << '\n';
            x2.PushBack(Tval);
            break;
        
          case '2':   // void PopBack()
	    if (BATCH) std::cout << '\n';
            x2.PopBack();
            break;

          case 'a':
	    if (BATCH) std::cout << '\n';
	    if (x2.Empty())
              std::cout << "x2 is empty\n";
            else
              std::cout << "x2.Front() == " << x2.Front() << '\n';
            break;

          case 'z':
	    if (BATCH) std::cout << '\n';
	    if (x2.Empty())
              std::cout << "x2 is empty\n";
            else
              std::cout << "x2.Back() == " << x2.Back() << '\n';
            break;

          case 'c':   // void Clear ()
	    if (BATCH) std::cout << '\n';
            x2.Clear();
            i2 = x2.Begin();
            break;

          case 'C':   // CopyTest ()
	    if (BATCH) std::cout << '\n';
            CopyTest(x2);
            AssignTest(x2);
            break;

          case '*':   // *i
            option = isptr->get();
	    if (BATCH) std::cout << option;
            switch(option)
            {
              case '=':
                *isptr >> Tval;
		if (BATCH) std::cout << Tval << '\n';
                if (i2 != x2.End())
                  *i2 = Tval;
                else
                  std::cout << " i2 is not valid\n";
                break;
              default:
		if (BATCH) std::cout << '\n';
                if (i2 != x2.End())
                  std::cout << "*i2 == " << *i2 << '\n';
                else
                  std::cout << " i2 == NULL\n";
                break;
            }
            break;
        
          case 'u':   // void Update(T)
            *isptr >> Tval;
	    if (BATCH) std::cout << Tval << '\n';
            if (i2 != x2.End())
            {
              *i2 = Tval;
              std::cout << "Update completed\n";
            }
            else
              std::cout << "Cannot update -- iterator invalid\n";
            break;
        
          case 'b':   // Begin()
	    if (BATCH) std::cout << '\n';
            i2 = x2.Begin();
            break;

          case 'r':   // rBegin()
	    if (BATCH) std::cout << '\n';
            i2 = x2.rBegin();
            break;

          case 's':   // Size() && Capacity() || SetSize() || SetCapacity()
            option = isptr->get();
	    if (BATCH) std::cout.put(option);
            switch(option)
            {
              case 's':
                *isptr >> index;
		if (BATCH) std::cout << index << '\n';
                x2.SetSize(index,fillValue);
                i2 = x2.Begin();
                break;
              case 'c':
                *isptr >> index;
		if (BATCH) std::cout << index << '\n';
                x2.SetCapacity(index);
                i2 = x2.Begin();
                break;
              default:
		if (BATCH) std::cout << '\n';
                std::cout << "Size     == " << x2.Size() << '\n';
                std::cout << "Capacity == " << x2.Capacity() << '\n'; 
                break;
            }
            break;

          case '[':   // i[index], i[index]=t
            *isptr >> index;
            *isptr >> option;  // assumed to be ']'
	    if (BATCH) std::cout << index << option;
            option = isptr->get();
	    if (BATCH) std::cout.put(option);
            switch(option)
            {
              case '=':
                *isptr >> Tval;
		if (BATCH) std::cout << Tval << '\n';
                if (i2 != x2.End())
                  i2[index] = Tval;
                else
                  std::cout << "i2 not valid\n";
                break;
              default:
		if (BATCH) std::cout << '\n';
                if (i2 != x2.End())
                  std::cout << "i2[" << index << "] == " << i2[index] << '\n';
                else
                  std::cout << "i2 not valid\n";
                break;
            }
            break;

          case 'e':   // int empty()
	    if (BATCH) std::cout << '\n';
            std::cout << "x2 is";
            if (!x2.Empty())
              std::cout << " not";
            std::cout << " empty\n";
            break;

          case 'd':  // test iterator
            if (BATCH) std::cout << '\n';
            std::cout << "  x2.Display(std::cout): ";
            x2.Display(std::cout);
            std::cout << '\n';
            std::cout << "            Traverse x2: ";
            for (i = x2.Begin(); i != x2.End(); ++i)
            {
              std::cout << *i;
            }
            std::cout << '\n';
            std::cout << "           rTraverse x2: ";
            for (i = x2.rBegin(); i != x2.rEnd(); --i)
            {
              std::cout << *i;
            }
            std::cout << '\n';
            break;
          
          case '=':
            *isptr >> option;
	    if (BATCH) std::cout << option;
            switch(option)
            {
              case '1': 
		if (BATCH) std::cout << '\n';
		x2 = x1;
		i2 = x2.Begin();
		break;
              case '2':
		if (BATCH) std::cout << '\n';
		x2 = x2;
		i2 = x2.Begin();
		break;
              case '3':
		if (BATCH) std::cout << '\n';
		x2 = x3;
		i2 = x2.Begin();
		break;
              case '=':
                *isptr >> option;
		if (BATCH) std::cout << option << '\n';
                switch(option)
                {
                  case '1':
                    if (x2 == x1)
                      std::cout << "x2 == x1\n";
                    else
                      std::cout << "x2 != x1\n";
                    break;
                  case '2':
                    if (x2 == x2)
                      std::cout << "x2 == x2\n";
                    else
                      std::cout << "x2 != x2\n";
                    break;
                  case '3':
                    if (x2 == x3)
                      std::cout << "x2 == x3\n";
                    else
                      std::cout << "x2 != x3\n";
                    break;
                }
                break;
            }
            break;

          case '!':
            *isptr >> option;  // assumed to be '='
	    if (BATCH) std::cout << option;
            *isptr >> option;
	    if (BATCH) std::cout << option << '\n';
            switch(option)
            {
              case '1':
                if (x2 != x1)
                  std::cout << "x2 != x1\n";
                else
                  std::cout << "x2 == x1\n";
                break;
              case '2':
                if (x2 != x2)
                  std::cout << "x2 != x2\n";
                else
                  std::cout << "x2 == x2\n";
                break;
              case '3':
                if (x2 != x3)
                  std::cout << "x2 != x3\n";
                else
                  std::cout << "x2 == x3\n";
                break;
            }
            break;

          case '+':   // ++(), +=()
            *isptr >> option;
	    if (BATCH) std::cout << option;
            switch(option)
            {
              case '+':
		if (BATCH) std::cout << '\n';
                ++i2;
                break;
              case '=':
                *isptr >> option;
		if (BATCH) std::cout << option << '\n';
                switch(option)
                {
                  case '1': x2 += x1; i2 = x2.Begin(); break;
                  case '2': x2 += x2; i2 = x2.Begin(); break;
                  case '3': x2 += x3; i2 = x2.Begin(); break;
                  default: std::cout << "** Unknown command -- try again\n";
                }
                break;
              default: std::cout << "** Unknown command -- try again\n";
              break;
            }
            break;
        
          case '-':   // --
            *isptr >> option;  // assumed to be '-'
	    if (BATCH) std::cout << option << '\n';
            --i2;
            break;
        
          case 't':   case 'T': // traversal
	    if (BATCH) std::cout << '\n';
	    std::cout << "  Traversal:  ";
	    for (i = x2.Begin(); i != x2.End(); ++i)
	      std::cout << *i << ofc;
	    std::cout << '\n';
	    std::cout << "  rTraversal: ";
	    for (i = x2.rBegin(); i != x2.rEnd(); --i)
	      std::cout << *i << ofc;
	    std::cout << '\n';
            break;
        
          default:
            do
	    {
	      isptr->get(option);
	      if (BATCH) std::cout.put(option);
	    }
            while (option != '\n');
            std::cout << " ** Unrecognized command -- please try again\n";

        }  // end case '2'
        break;

      case '3': 
        *isptr >> option;
	if (BATCH) std::cout << option;
        // option = tolower(option);
        switch (option)
        {
/*        case '1':   // void PushFront (T)
            *isptr >> Tval;
	    if (BATCH) std::cout << Tval << '\n';
            x3.PushFront(Tval);
            break;
      
          case '2':   // void PushBack (T)
            *isptr >> Tval;
	    if (BATCH) std::cout << Tval << '\n';
            x3.PushBack(Tval);
            break;
        
          case '3':   // void PopFront()
	    if (BATCH) std::cout << '\n';
            x3.PopFront();
            break;
        
          case '4':   // void PopBack()
	    if (BATCH) std::cout << '\n';
            x3.PopBack();
            break;
*/
          case '1':   // void PushBack (T)
            *isptr >> Tval;
	    if (BATCH) std::cout << Tval << '\n';
            x3.PushBack(Tval);
            break;
        
          case '2':   // void PopBack()
	    if (BATCH) std::cout << '\n';
            x3.PopBack();
            break;

          case 'a':
	    if (BATCH) std::cout << '\n';
	    if (x3.Empty())
              std::cout << "x3 is empty\n";
            else
              std::cout << "x3.Front() == " << x3.Front() << '\n';
            break;

          case 'z':
	    if (BATCH) std::cout << '\n';
	    if (x3.Empty())
              std::cout << "x3 is empty\n";
            else
              std::cout << "x3.Back() == " << x3.Back() << '\n';
            break;

          case 'c':   // void Clear ()
	    if (BATCH) std::cout << '\n';
            x3.Clear();
            i3 = x3.Begin();
            break;

          case 'C':   // CopyTest ()
	    if (BATCH) std::cout << '\n';
            CopyTest(x3);
            AssignTest(x3);
            break;

          case '*':   // *i
            option = isptr->get();
	    if (BATCH) std::cout << option;
            switch(option)
            {
              case '=':
                *isptr >> Tval;
		if (BATCH) std::cout << Tval << '\n';
                if (i3 != x3.End())
                  *i3 = Tval;
                else
                  std::cout << " i3 is not valid\n";
                break;
              default:
		if (BATCH) std::cout << '\n';
                if (i3 != x3.End())
                  std::cout << "*i3 == " << *i3 << '\n';
                else
                  std::cout << " i3 == NULL\n";
                break;
            }
            break;
        
          case 'u':   // void Update(T)
            *isptr >> Tval;
	    if (BATCH) std::cout << Tval << '\n';
            if (i3 != x3.End())
            {
              *i3 = Tval;
              std::cout << "Update completed\n";
            }
            else
              std::cout << "Cannot update -- iterator invalid\n";
            break;
        
          case 'b':   // Begin()
	    if (BATCH) std::cout << '\n';
            i3 = x3.Begin();
            break;

          case 'r':   // rBegin()
	    if (BATCH) std::cout << '\n';
            i3 = x3.rBegin();
            break;

          case 's':   // Size() && Capacity() || SetSize() || SetCapacity()
            option = isptr->get();
	    if (BATCH) std::cout.put(option);
            switch(option)
            {
              case 's':
                *isptr >> index;
		if (BATCH) std::cout << index << '\n';
                x3.SetSize(index,fillValue);
                i3 = x3.Begin();
                break;
              case 'c':
                *isptr >> index;
		if (BATCH) std::cout << index << '\n';
                x3.SetCapacity(index);
                i3 = x3.Begin();
                break;
              default:
		if (BATCH) std::cout << '\n';
                std::cout << "Size     == " << x3.Size() << '\n';
                std::cout << "Capacity == " << x3.Capacity() << '\n'; 
                break;
            }
            break;

          case '[':   // i[index], i[index]=t
            *isptr >> index;
            *isptr >> option;  // assumed to be ']'
	    if (BATCH) std::cout << index << option;
            option = isptr->get();
	    if (BATCH) std::cout.put(option);
            switch(option)
            {
              case '=':
                *isptr >> Tval;
		if (BATCH) std::cout << Tval << '\n';
                if (i3 != x3.End())
                  i3[index] = Tval;
                else
                  std::cout << "i3 not valid\n";
                break;
              default:
		if (BATCH) std::cout << '\n';
                if (i3 != x3.End())
                  std::cout << "i3[" << index << "] == " << i3[index] << '\n';
                else
                  std::cout << "i3 not valid\n";
                break;
            }
            break;

          case 'e':   // int empty()
	    if (BATCH) std::cout << '\n';
            std::cout << "x3 is";
            if (!x3.Empty())
              std::cout << " not";
            std::cout << " empty\n";
            break;

          case 'd':  // test iterator
            if (BATCH) std::cout << '\n';
            std::cout << "  x3.Display(std::cout): ";
            x3.Display(std::cout);
            std::cout << '\n';
            std::cout << "            Traverse x3: ";
            for (i = x3.Begin(); i != x3.End(); ++i)
            {
              std::cout << *i;
            }
            std::cout << '\n';
            std::cout << "           rTraverse x3: ";
            for (i = x3.rBegin(); i != x3.rEnd(); --i)
            {
              std::cout << *i;
            }
            std::cout << '\n';
            break;
          
          case '=':
            *isptr >> option;
	    if (BATCH) std::cout << option;
            switch(option)
            {
              case '1': 
		if (BATCH) std::cout << '\n';
		x3 = x1;
		i3 = x3.Begin();
		break;
              case '2':
		if (BATCH) std::cout << '\n';
		x3 = x2;
		i3 = x3.Begin();
		break;
              case '3':
		if (BATCH) std::cout << '\n';
		x3 = x3;
		i3 = x3.Begin();
		break;
              case '=':
                *isptr >> option;
		if (BATCH) std::cout << option << '\n';
                switch(option)
                {
                  case '1':
                    if (x3 == x1)
                      std::cout << "x3 == x1\n";
                    else
                      std::cout << "x3 != x1\n";
                    break;
                  case '2':
                    if (x3 == x2)
                      std::cout << "x3 == x2\n";
                    else
                      std::cout << "x3 != x2\n";
                    break;
                  case '3':
                    if (x3 == x3)
                      std::cout << "x3 == x3\n";
                    else
                      std::cout << "x3 != x3\n";
                    break;
                }
                break;
            }
            break;

          case '!':
            *isptr >> option;  // assumed to be '='
	    if (BATCH) std::cout << option;
            *isptr >> option;
	    if (BATCH) std::cout << option << '\n';
            switch(option)
            {
              case '1':
                if (x3 != x1)
                  std::cout << "x3 != x1\n";
                else
                  std::cout << "x3 == x1\n";
                break;
              case '2':
                if (x3 != x2)
                  std::cout << "x3 != x2\n";
                else
                  std::cout << "x3 == x2\n";
                break;
              case '3':
                if (x3 != x3)
                  std::cout << "x3 != x3\n";
                else
                  std::cout << "x3 == x3\n";
                break;
            }
            break;

          case '+':   // ++(), +=()
            *isptr >> option;
	    if (BATCH) std::cout << option;
            switch(option)
            {
              case '+':
		if (BATCH) std::cout << '\n';
                ++i3;
                break;
              case '=':
                *isptr >> option;
		if (BATCH) std::cout << option << '\n';
                switch(option)
                {
                  case '1': x3 += x1; i3 = x3.Begin(); break;
                  case '2': x3 += x2; i3 = x3.Begin(); break;
                  case '3': x3 += x3; i3 = x3.Begin(); break;
                  default: std::cout << "** Unknown command -- try again\n";
                }
                break;
              default: std::cout << "** Unknown command -- try again\n";
              break;
            }
            break;
        
          case '-':   // --
            *isptr >> option;  // assumed to be '-'
	    if (BATCH) std::cout << option << '\n';
            --i3;
            break;
        
	  case 't':   case 'T': // traversal
	    if (BATCH) std::cout << '\n';
	    std::cout << "  Traversal:  ";
	    for (i = x3.Begin(); i != x3.End(); ++i)
	      std::cout << *i << ofc;
	    std::cout << '\n';
	    std::cout << "  rTraversal: ";
	    for (i = x3.rBegin(); i != x3.rEnd(); --i)
	      std::cout << *i << ofc;
	    std::cout << '\n';
            break;
        
          default:
            do
	    {
	      isptr->get(option);
	      if (BATCH) std::cout.put(option);
	    }
            while (option != '\n');
            std::cout << " ** Unrecognized command -- please try again\n";

        }  // end case '3'
        break;

      case '=':
	if (BATCH) std::cout << '\n';
        x3 = x2 = x1;
	break;

      case 'm':
	if (BATCH) std::cout << '\n';
        DisplayMenu(); break;

    case 'x': case 'X':  // switch to interactive mode or quit
	if (BATCH)
	{
	  std::cout << '\n';
	  ifs.close();
	  BATCH = 0;
	  isptr = &std::cin;
	}
	else
	{
	  option = 'q';
	}
	break;

      case 'q': case 'Q':
	if (BATCH) std::cout << '\n';
	option =  'q';
        break;

      default:
	if (BATCH) std::cout << '\n';
	do 
	{
	  isptr->get(option);
	  if (BATCH) std::cout.put(option);
	} 
	while (option != '\n');
        std::cout << "** Unrecognized command -- please try again.\n";
    }
  }
  while (option != 'q');
  if (BATCH) ifs.close();
  std::cout << "\nHave a nice day." << std::endl;
  return EXIT_SUCCESS;
}

void DisplayMenu()
{
  std::cout 
       << '\n'
       << "      x1, x2, x3 are Vector < " << vT << " > objects\n"
       << "  operators  = , +=, ==, !=,  ............  [vect][op][vect]\n"
       // << "  PushFront   (t)  ......  1      PopFront    ()  .......  3\n"
       // << "  PushBack    (t)  ......  2      PopBack     ()  .......  4\n"
       << "  PushBack    (t)  ......  1      PopBack     ()  .......  2\n"
       << "  Clear       ()  .......  c      Empty       ()  .......  e\n"
       << "  Front       ()  .......  a      Back        ()  .......  z\n"
       << "  Size        ()  .......  a      Capacity    ()  .......  s\n"
       << "  SetSize     (i)  ......  aa     SetCapacity (i)  ......  sc\n"
       << "  Display vector  .......  d      Assign vector  ........  =\n"
       << "  i = x.Begin ()  .......  b      i = x.rBegin()  .......  r\n"
       << "  ++i  ..................  ++     --i  ..................  --\n"
       << "  *i  ...................  *      *i = t  ...............  *=t\n"
       << "  i[j]  .................  [j]    i[j] = t  .............  [j]=t\n"
       << "  Traverse  .............  T      Copy Test  ............  C\n"
       << "     x3 = x2 = x1  .................................  =\n"
       << "     Change to interactive mode  ...................  x\n"
       << "     Display this menu  ............................  m\n"
       << "     Quit program  .................................  q\n"
       << std::endl;
}

void Preamble()
{
  std::cout << "\n   This test uses three Vector objects: x1, x2, x3\n" 
	    << "   and three associated Iterator objects: i1, i2, i3\n"
            << "   The test accesses the Vector API through a menu of commands (below).\n" 
            << "   For most, designate the object (1, 2 or 3), followed by the command,\n"
	    << "   followed by the argument if needed.\n"
	    << "   Some example entries and their meaning for the API:\n\n"
	    << "      Entry     API Function\n"
	    << "      -----     ------------\n"
	    << "      11z       x1.PushFront(z)\n"
	    << "      32q       x3.PushBack(q)\n"
	    << "      2a        i2 = x2.Begin()  \n"
	    << "      2++       ++i2\n"
	    << "      1==2      x1 == x2\n"
	    << "      3=2       x3 = x2\n"
	    << "      =         x3 = x2 = x1; init i1, i2, i3; CopyTest(x3); AssignTest(x3);\n\n";
}

