/*
    binarySearchTrace.cpp
    01/01/12
    Chris Lacher

    shows trace of lower_bound and upper_bound on fsu::Vector<char>

    Copyright 2012, R.C. Lacher
*/

#include <cstdlib>
#include <iostream>
#include <fstream>

#include <vector.h>
#include <compare.h>
#include <gsort.h>

const char* INDENT ("     ");

template <typename T, class P>
void lower_bound_trace (fsu::Vector<T> V, const T& val, const P& cmp)
{
  std::cout << "  =================\n";
  std::cout << "  lower_bound trace\n";
  std::cout << "  =================\n";
  size_t low = 0, hih = V.Size(), mid;
  while (low != hih)
  {
    mid =  (low + hih) >> 1;
    std::cout << INDENT << V << '\n';
    std::cout << INDENT;
    for (size_t i = 0;   i < low; ++i) std::cout << ' ';
    for (size_t i = low; i < hih; ++i) std::cout << '-';
    std::cout << '\n';
    std::cout << INDENT;
    for (size_t i = 0;   i < mid; ++i) std::cout << ' ';
    std::cout << "m\n";
    //    std::cout << "low=" << low << " mid=" << mid << " hih=" << hih << '\n';

    if (cmp(V[mid] , val))
      low = ++mid;     
    else               
      hih = mid;       
  }
  std::cout << INDENT << V << '\n';
  std::cout << INDENT;
  for (size_t i = 0;   i < low; ++i) std::cout << ' ';
  std::cout << "^lb\n";
}

template <typename T, class P>
void upper_bound_trace (fsu::Vector<T> V, const T& val, const P& cmp)
{
  std::cout << "  =================\n";
  std::cout << "  upper_bound trace\n";
  std::cout << "  =================\n";
  size_t low = 0, hih = V.Size(), mid;
  while (low != hih)
  {
    mid =  (low + hih) >> 1;

    std::cout << INDENT << V << '\n';
    std::cout << INDENT;
    for (size_t i = 0;   i < low; ++i) std::cout << ' ';
    for (size_t i = low; i < hih; ++i) std::cout << '-';
    std::cout << '\n';
    std::cout << INDENT;
    for (size_t i = 0;   i < mid; ++i) std::cout << ' ';
    std::cout << "m\n";

    if (cmp(val, V[mid]))
      hih = mid;       
    else               
      low = ++mid;     
  }
  std::cout << INDENT << V << '\n';
  std::cout << INDENT;
  for (size_t i = 0;   i < low; ++i) std::cout << ' ';
  std::cout << "^ub\n";
}

int main()
{
  typedef char element_type; const char* e_t = "char";
  // typedef int element_type; const char* e_t = "int";

  typedef fsu::LessThan <element_type> PredicateType1;
  // typedef fsu::GreaterThan <element_type> PredicateType2;

  fsu::Vector < element_type > V;  // a vector
  PredicateType1               LT; // predicate object

  element_type e, s; // entry, sentinal

  std::cout << "Begin trace of binary search < " << e_t << " >\n\n"
	    << "  You will enter characters for storage into a vector V, which is then sorted\n"
	    << "  Then the program enters an interactive phase where you will be prompted to enter search values.\n"
	    << "  The sentinal value will be used to terminate your original input and to end the program.\n\n"
	    << "Enter sentinal: ";
  std::cin >> s;
  std::cout << "Enter elements ('"
       << s
       << "' to end): ";
  std::cin >> e;
  while (e != s)
  {
    V.PushBack(e);
    std::cin >> e;
  }

  std::cout << "V as entered:                " << V << '\n';
  fsu::g_insertion_sort(V.Begin(), V.End(), LT);
  std::cout << "V after sort:                " << V << '\n';

  // now do binary search
  while(1)
  {
    std::cout << "Enter search value ('"
	 << s
	 << "' to quit): ";
    std::cin >> e;
    if (e == s) break;
    lower_bound_trace(V, e, LT);
    upper_bound_trace(V, e, LT);
  }
  std::cout << "End trace of binary search\n";
  return 0;
}
