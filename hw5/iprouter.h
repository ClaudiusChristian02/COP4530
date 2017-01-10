/*
    iprouter.h
    03/25/15
    Chris Lacher
    Copyright 2015, R C Lacher

    Defining the Router class for fast lookup of ip route addresses.

    The table stores information as ipNumber (destination, route) pairs.
    These data are stored in files as one pair per line in hex notation.

    The data are entered manually as ipStrings, which are converted to
    ipNumbers before insertion in the table. (Manual entry of
    <destination,route> pairs is sometimes called "programming the router".)

    ipString is the familier "dot" notation N1.N2.N3.N4 where Ni is a
    decimal in the range 0..255, interpreted as a byte.
    ipString is stored as a String object.

    ipNumber is a 32 bit unsigned int, logically divided into 
    four bytes <byte1><byte2><byte3><byte4>. The four decimal fields
    in the ipString notation correspond to the four bytes in the ipNumber.
    The individual bits of the 32 bit word are decoded by ipClass.

    The ipClass of an address is defined as follows numbering the bits
    from left to right, begining with 0:

      classA:    bit[0] = 0
      classB:    bit[0] = 1 && bit[1] = 0 
      classC:    bit[0] = 1 && bit[1] = 1 && bit[2] = 0 
      badClass:  not A, B, or C

    Depending on the ipClass of an address, the netID and hostID words
    are obtained by masking. The folowing table gives the bits defining the
    ipClass, netID, and hostID, and the value output to log files
    indicating ipClass.

              begin      netID bits   hostID bits   ipWrite() output
              -----      ----------   -----------   ----------------
    classA:   0...       1..7         8..31         'A'
    classB:   10...      2..15        16..31        'B'
    classC:   110...     3..23        24..31        'C'
    badClass: all other                             'D'

*/

#ifndef _IPROUTER_H
#define _IPROUTER_H

#include <iostream>
#include <fstream>
#include <cstdint>  // uint32_t
#include <iputil.h>

#include <xstring.h>
#include <hashfunctions.h>
#include <hashtbl.h>
#include <list.h>

// declarations
class Router;
class ipHash;

class Router
{
public:  // member functions:

  void Load      (const char* loadfile);
  void Save      (const char* savefile);
  void Insert    (const ipString& dS, const ipString& rS, bool verify = 0);
  void Remove    (const ipString& dS);
  void Go        (const char* msgfile, const char* logfile = nullptr);
  void Clear     ();
  void Dump      (const char* dumpfile);
  void Analysis  ();
  void Rehash    (size_t numBuckets = 0);
       Router    (size_t sizeEstimate);
       ~Router   ();

private: // terminology

  typedef fsu::Entry     < ipNumber, ipNumber >         EntryType;
  typedef fsu::List      < EntryType >                  BucketType;
  typedef fsu::HashTable < ipNumber, ipNumber, ipHash > TableType;

private: // one variable - this is an adaptor class

  TableType * tablePtr_;

} ; // class Router

class ipHash
{
public:
  size_t operator () (const ipNumber&) const;
} ;

#endif
