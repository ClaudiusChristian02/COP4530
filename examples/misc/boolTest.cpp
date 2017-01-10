/*  booltest.cpp

    Jul 19 2001
    Chris Lacher

    illustrates interpretation of type int as bool

    Copyright 2001 R.C. Lacher
*/

#include <iostream>

int main()
{
  int x;
  std::cout << "Boolean test program\n\n";
  std::cout << "     Enter an integer ('q' to quit): ";
  while (std::cin >> x)
    {
      if (x)
	std::cout << "                     interpreted as  TRUE\n";
      else
	std::cout << "                     interpreted as  FALSE\n";
      std::cout << "Enter another integer ('q' to quit): ";
    }
  std::cout << "\nEnd of boolean test\n";
  return 0;
} // main()
