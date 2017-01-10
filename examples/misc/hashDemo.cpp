/*
    hashtest.cpp
    Dec 16 2002
    Chris Lacher

    hash function calculator

    Copyright 2009, R. C. Lacher
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <xstring.cpp>
#include <hash.cpp>

int main()
{
  const fsu::String ALT("alt");
  const fsu::String FSU("fsu");
  fsu::String N, S;
  unsigned int d;
  std::cout << "Enter hash function namespace: ";
  std::cin >> N;
  std::cout << " Enter divisor for hash value: ";
  std::cin >> d;
  std::cout << "Enter string to be hashed ('}' to quit): ";
  std::cin >> S;

  if (N == ALT)
  {
    while (S[0] != '}')
    {
      std::cout << "                           hash value: " 
		<< alt::HashFunction(S) << '\n'
		<< "                     hash value mod D: "
		<< alt::HashFunction(S) % d << '\n'
		<< "Enter string to be hashed ('}' to quit): ";
      std::cin >> S;
    }
  }
  else if (N == FSU)
  {
    while (S[0] != '}')
    {
      std::cout << "                          hash value: "
		<< fsu::HashFunction(S) << '\n'
		<< "                    hash value mod D: "
		<< fsu::HashFunction(S) % d << '\n'
		<< "Enter value to be hashed ('}' to quit): ";
      std::cin >> S;
    }
  }     
  else
  {
    std::cout << "Namespace not recognized\n";
  }
  return 0;
} // main()
