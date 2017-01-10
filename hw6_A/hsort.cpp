/*
    hsort.cpp
    09/13/13
    Chris Lacher

    sorts from standard input to standard output

    build with one command:
      g++47 -std=c++11 -o hsort.x -I. -I/home/courses/cop4530p/spring14/cpp -I/home/courses/cop4530p/spring14/tcpp hsort.cpp
    use with redirection:
      hsort.x < input_file > output_file

    Copyright 2013, R.C. Lacher
*/

#include <iostream>
#include <vector.h>
#include <gheap.h>

typedef unsigned long ElementType;

int main()
{
  fsu::Vector < ElementType > v;  // a vector
  ElementType e;
  while (std::cin >> e)
  {
    v.PushBack(e);
  }
  fsu::g_heap_sort(v.Begin(),v.End());
  for (fsu::Vector < ElementType > ::Iterator i = v.Begin(); i != v.End(); ++i)
  {
    std::cout << *i << '\n';
  }
  return 0;
}
