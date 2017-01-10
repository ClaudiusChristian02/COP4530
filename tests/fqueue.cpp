/*
    fqueue.cpp
    01/22/14
    Chris Lacher

    functionality test of various Queue implementations

    Copyright 2012, R.C. Lacher
*/

#include <iostream>

// choose one from group A

//  A1: makes queues of char
typedef char ElementType;
ElementType fill = ' ';
const size_t maxSize = 10;
const char* eT = "char";
const char ofc = '\0';
// end A1 */

/* //  A2: makes queues of String
#include <xstring.cpp>
typedef fsu::String ElementType;
ElementType fill = "*";
const size_t maxSize = 100;
const char* eT = "String";
const char ofc = ' ';
// end A2 */

/* //  A3: makes queues of int
typedef int ElementType;
ElementType fill = 0;
const size_t maxSize = 100;
const char* eT = "int";
const char ofc = ' ';
// end A2 */

// =====================
// ===== group B =======
// =====================

/* //  B1: makes ringbuffer-based queues
#include <ringbuff.h>
#include <queue.h>
typedef fsu::Queue < ElementType , fsu::RingBuffer < ElementType > > QueueType;
// end B1 */

/* //  B2: makes dequeue-based queues
#include <deque.h>
#include <queue.h>
typedef fsu::Queue < ElementType , fsu::Deque < ElementType > > QueueType;
// end B2 */

//  B3: makes list-based queues
#include <list.h>
#include <queue.h>
typedef fsu::Queue < ElementType , fsu::List < ElementType > > QueueType;
// end B3 */

/* // B4: makes link-based queues
#include <queue.t>
typedef fsu::Queue < ElementType > QueueType;
// end B4 */

void DisplayMenu();

template < class Queue >
void CopyTest(Queue s)
{
  std::cout << "CopyTest:\n";
  std::cout << "Copied object       size: " << s.Size() << '\n'
            << "                contents: ";
  s.Display(std::cout, ofc);
  std::cout << '\n';
}

template < class Queue >
void AssignTest(const Queue& s)
{
  Queue s1;
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

template < class Queue >
void ConstTest (const Queue& s)
{
  if (s.Empty())
  {
    std::cout << "ConstTest: inactive on empty queue\n";
    return;
  }
  Queue s1;
  s1.Push(s.Front());      // OK:    s1 is not const
  // s.Push(s1.Front());   // Error: s is const
  s1.Front() = s.Front();    // OK:    non-const = const
  // s.Front() = s1.Front(); // Error: const = non-const
  std::cout << "ConstTest: OK\n"; 
}

int main( int argc , char* argv[])
{
  bool BATCH = 0;
  if (argc > 1)
  {
    if (argv[1][0] != '\0')
      BATCH = 1;
  }

  std::cout << "This is a Queue < " << eT << " > test program\n";
  DisplayMenu();
  QueueType q;
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
          std::cout << "Queue is empty\n";
        }
        break;

      case 'c': case 'C':  // void clear()
        if (BATCH) std::cout << '\n';
        q.Clear();
        break;

      case 'f': case 'F':  // T Front()
        if (BATCH) std::cout << '\n';
        if (!q.Empty())
        {
          Tval = q.Front();
          std::cout << "Front of Queue: " << Tval << '\n';
        }
        else
        {
          std::cout << "Queue is empty\n";
        }
        break;

      case 'e': case 'E':  // int Empty()
        if (BATCH) std::cout << '\n';
        std::cout << "Queue is ";
        if (!q.Empty()) std::cout << "not ";
        std::cout << "empty\n";
        break;

      case 's': case 'S':  // size_t Size()
        if (BATCH) std::cout << '\n';
        std::cout << "Queue size     = "
                  << q.Size()
                  << '\n';
        break;

      case 'd': case 'D':  // display contents of queue
        if (BATCH) std::cout << '\n';
        std::cout << "Queue contents:   ";
        q.Display(std::cout,ofc);
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
            << "Front()  ................  F\n"
            << "Empty()  ................  E\n"
            << "Size()  .................  S\n"
            << "Copies  .................  =\n"
            << "Display entire queue  ...  D\n"
            << "Display this menu  ......  M\n";
}
