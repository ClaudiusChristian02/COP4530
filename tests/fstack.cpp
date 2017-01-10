/*
    fstack.cpp
    10-21-12
    Chris Lacher

    functionality test of various Stack implementations

    Copyright 2012, R.C. Lacher
*/

#include <iostream>

// choose one from group A

//  A1: makes stacks of char
typedef char ElementType;
ElementType fill = '*';
const size_t maxSize = 10;
const char* eT = "char";
const char ofc = '\0';
// end A1 */

/* //  A2: makes stacks of String
#include <xstring.cpp>
typedef fsu::String ElementType;
ElementType fill = "*";
const size_t maxSize = 100;
const char* eT = "String";
const char ofc = ' ';
// end A2 */

/* //  A3: makes stacks of int
typedef int ElementType;
ElementType fill = 0;
const size_t maxSize = 100;
const char* eT = "int";
const char ofc = ' ';
// end A2 */

// =====================
// ===== group B =======
// =====================

/* //  B1: makes vector-based stacks
#include <vector.h>
#include <stack.h>
typedef fsu::Stack < ElementType , fsu::Vector < ElementType > > StackType;
// end B1 */

/* //  B2: makes dequeue-based stacks
#include <deque.h>
#include <stack.h>
typedef fsu::Stack < ElementType , fsu::Deque < ElementType > > StackType;
// end B2 */

/* //  B3: makes list-based stacks
#include <list.h>
#include <stack.h>
typedef fsu::Stack < ElementType , fsu::List < ElementType > > StackType;
// end B3 */

// B4: makes array-based stacks
#include <stack.t>
typedef fsu::Stack < ElementType , maxSize > StackType;
// end B4 */

void DisplayMenu();

template < class Stack >
void CopyTest(Stack s)
{
  std::cout << "CopyTest:\n";
  std::cout << "Copied object       size: " << s.Size() << '\n'
            << "                contents: ";
  s.Display(std::cout, ofc);
  std::cout << '\n';
}

template < class Stack >
void AssignTest(const Stack& s)
{
  Stack s1;
  s1 = s;
  std::cout << "AssignTest:\n";
  std::cout << "Original object     size: " << s.Size() << '\n'
            << "                contents: ";
  s.Display(std::cout, ofc);
  std::cout << '\n';
  std::cout << "Assignee object     size: " << s1.Size() << '\n'
            << "                contents: ";
  s1.Display(std::cout, ofc);
  std::cout << '\n';
}

template < class Stack >
void ConstTest (const Stack& s)
{
  if (s.Empty())
  {
    std::cout << "ConstTest: inactive on empty stack\n";
    return;
  }
  Stack s1;
  s1.Push(s.Top());      // OK:    s1 is not const
  // s.Push(s1.Top());   // Error: s is const
  s1.Top() = s.Top();    // OK:    non-const = const
  // s.Top() = s1.Top(); // Error: const = non-const
  std::cout << "ConstTest: OK\n"; 
}

int main( int argc, char* argv[] )
{
  bool BATCH = 0;
  if (argc > 1)
  {
    if (argv[1][0] != '\0')
      BATCH = 1;
  }

  std::cout << "This is a Stack < " << eT << " > test program\n";
  DisplayMenu();
  StackType q(fill);
  ElementType Tval;
  char option;
  do
  {
    std::cout << "Enter [command][argument] ('M' for menu, 'Q' to quit): ";
    std::cin >> option;
    if (BATCH) std::cout << option;
    switch (option)
    {
      case '=':   // CC and =
        if (BATCH) std::cout << '\n';
        CopyTest(q);
        AssignTest(q);
        ConstTest(q);
        break;

      case '+': case '1':   // void Push(T)
        std::cin >> Tval;
        if (BATCH) std::cout << Tval << '\n';
        q.Push(Tval);
        break;

      case '-': case '2':  // void Pop()
        if (BATCH) std::cout << '\n';
        if (!q.Empty())
        {
          q.Pop();
        }
        else
        {
          std::cout << "Stack is empty\n";
        }
        break;

      case 'c': case 'C':  // void clear()
        if (BATCH) std::cout << '\n';
        q.Clear();
        break;

      case 't': case 'T':  // T Top()
        if (BATCH) std::cout << '\n';
        if (!q.Empty())
        {
          Tval = q.Top();
          std::cout << "Top of Stack: " << Tval << '\n';
        }
        else
        {
          std::cout << "Stack is empty\n";
        }
        break;

      case 'e': case 'E':  // int Empty()
        if (BATCH) std::cout << '\n';
        std::cout << "Stack is ";
        if (!q.Empty()) std::cout << "not ";
        std::cout << "empty\n";
        break;

      case 's': case 'S':  // size_t Size()
        if (BATCH) std::cout << '\n';
        std::cout << "Stack size     = "
                  << q.Size()
                  << '\n';
        break;

      case 'd': case 'D':  // display contents of stack
        if (BATCH) std::cout << '\n';
        std::cout << "Stack contents:   ";
        q.Display(std::cout,ofc);
        std::cout << '\n';
        break;

      case 'u': case 'U':  // display contents of stack
        if (BATCH) std::cout << '\n';
        std::cout << "Stack Dump():\n";
        q.Dump(std::cout);
        std::cout << '\n';
        break;

      case 'm': case 'M': // display menu
        if (BATCH) std::cout << '\n';
        DisplayMenu(); break;

      case 'q': case 'Q': case 'x': case 'X':
        if (BATCH) std::cout << '\n';
        option = 'q';
        break;
            
      default:
        if (BATCH) std::cout << '\n';
        std::cout << "** Unrecognized command -- please try again.\n";
    }
  }
  while (option != 'q');
  std::cout << "\nHave a nice day." << std::endl;
  return EXIT_FAILURE;
}

void DisplayMenu()
{
  std::cout << "Push(Tval)  .............  + or 1\n"
            << "Pop()  ..................  - or 2\n"
            << "Clear()  ................  C\n"
            << "Top()  ..................  T\n"
            << "Empty()  ................  E\n"
            << "Size()  .................  S\n"
            << "Copies  .................  =\n"
            << "Display stack ...........  D\n"
            << "Dump() ..................  U\n"
            << "Display this menu  ......  M\n";
}
