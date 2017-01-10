/*
    ip_ranmap.cpp
    04/04/15
    Chris Lacher

    creates <destination,route> data for testing of iprouter

    Copyright 2015, R.C. Lacher
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdint>
#include <hashtbl.h>
#include <hashclasses.h>

#include <hashfunctions.h>
#include <primes.h>
#include <bitvect.h>
#include <xran.h>
#include <xstring.h>
#include <iputil.h>

/* // in lieu of makefile
#include <hashfunctions.cpp>
#include <primes.cpp>
#include <bitvect.cpp>
#include <xran.cpp>
#include <xstring.cpp>
#include <iputil.cpp>
// */

typedef fsu::HashTable < uint32_t, uint32_t , hashclass::MM < uint32_t> > TableType;

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cout << " ** program requires 2 arguments\n"
              << "    1 = number of generated entries\n"
              << "    2 = output filename\n"
              << " ** try again\n";
    exit(0);
  }

  std::cout << "Program generating file of TAB-seperated <destination,route> entries\n";

  std::ofstream out1;
  out1.open(argv[2]);
  if (out1.fail())
  {
    std::cout << " ** Unable to open file " << argv[2] << '\n'
              << " ** program closing\n";
    exit(0);
  }

  size_t num = atoi(argv[1]);
  TableType ht (num);
  fsu::Random_uint32_t ranipn;
  uint32_t dest, route;
  out1 << std::uppercase << std::hex << std::setfill('0');
  size_t count(0);
  while (count < num)
  {
    do
    {
      dest = ranipn(); 
    }
    while ( ht.Retrieve(dest,route) || 0xE0000000 == (0xE0000000 & dest) );
    do
    {
      route = ranipn(); 
    }
    while ( 0xE0000000 == (0xE0000000 & route) );
    ht[dest] = route;
    out1 << std::setw(8) << dest << '\t' << std::setw(8) << route << '\n';    
    ++count;
  }

  // close outfile
  out1.close();

  // terminate program
  std::cout << "File of <dest,route> constructed:\n"
            << " filename:        " << argv[2] << '\n'
            << " number of pairs: " << ht.Size() << '\n';
  return 0;
}
