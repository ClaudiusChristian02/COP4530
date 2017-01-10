/*
    hasheval.cpp
    08/12/2014
    Chris Lacher
    Copyright 2014, R.C. Lacher

    analysis test for hash tables

    HashTable <K,D,H>

       K =      String
       D =      int
       H =      HashClass<K>
*/

#include <fstream>
#include <cctype>

#include <xstring.h>
#include <hashfunctions.h>
#include <hashclasses.h>

#include <primes.h>
#include <bitvect.h>

#include <hashtbl.h>

/* // in lieu of makefile
#include <xstring.cpp>
#include <hashfunctions.cpp>
#include <primes.cpp>
#include <bitvect.cpp>
// */

// ModP hash function
typedef fsu::String                         KeyType;
typedef int                                 DataType;
typedef hashclass::ModP < KeyType >         HashType;
typedef fsu::Entry < KeyType, DataType >    EntryType;
const bool prime = 1;
// */

/* // KISS hash function
typedef fsu::String                         KeyType;
typedef int                                 DataType;
typedef hashclass::KISS < KeyType >         HashType;
typedef fsu::Entry < KeyType, DataType >    EntryType;
const bool prime = 1;
// */

/* // MM hash function
typedef fsu::String                         KeyType;
typedef int                                 DataType;
typedef hashclass::MM < KeyType >           HashType;
typedef fsu::Entry < KeyType, DataType >    EntryType;
const bool prime = 1;
// */

/* // Simple hash function
typedef fsu::String                         KeyType;
typedef int                                 DataType;
typedef hashclass::Simple < KeyType >       HashType;
typedef fsu::Entry < KeyType, DataType >    EntryType;
const bool prime = 0;
// */

int main(int argc, char* argv[])
{
  typedef fsu::HashTable < KeyType, DataType, HashType > HashTableType;
  std::ifstream ifs;
  std::ofstream ofs;
  int writetofile = 0;
  if (argc != 3 && argc != 4)
  {
    std::cout << " ** program requires 2 or 3 arguments\n"
	      << "    1 = approx no of buckets (required)\n"
	      << "    2 = input table filename (required)\n"
	      << "    3 = output analysis filename (optional)\n"
	      << " ** try again\n";
    exit(0);
  }

  ifs.open(argv[2]);
  if (ifs.fail())
  {
    std::cout << " ** Unable to open file " << argv[2] << '\n'
	      << " ** program closing\n";
    exit(0);
  }

  if (argc == 4)
  {
    ofs.open(argv[3]);
    if (ofs.fail())
    {
      std::cout << " ** Unable to open file " << argv[3] << '\n'
		<< " ** program closing\n";
      exit(0);
    }
    writetofile = 1;
  }

  size_t numbuckets = atoi(argv[1]);
  HashType hfo;
  HashTableType * tablePtr = new HashTableType(numbuckets, hfo, prime);

  KeyType k;
  DataType d;
  while (!ifs.eof())
  {
    ifs >> k >> d;
    tablePtr->Insert(k,d);
  }
  ifs.close();
  std::cout << "  load completed\n" << std::flush;

  if (writetofile)
  {
    tablePtr->Analysis(ofs);
    ofs.close();
    std::cout << "  analysis written to " << argv[3] << '\n';
  }
  else
  {
    tablePtr->Analysis(std::cout);
  }
  return 0;
}
