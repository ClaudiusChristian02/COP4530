/*  commandlinearguments.cpp
    Jul 19 2001
    Chris Lacher

    demonstrates use of command line arguments
    as parameters for function main()

    Copyright 2001, R.C. Lacher
*/

#include <iostream>

int main (int argc, char* argv[])
{
  std::cout << argc << " command line arguments were entered.\n"
	    << "The data passed to function main were:\n";
  std::cout << argc << " = argc\n";
  for (int i = 0; i < argc; ++i)
    {
      std::cout << "argv[" << i << "] = " << argv[i];
      std::cout << '\n';
    }

  return 0;
} // main()
