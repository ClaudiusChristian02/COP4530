/*
    iputil.h
    03/25/15
    Chris Lacher
    Copyright 2015, R C Lacher

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

#ifndef _IPUTIL_H
#define _IPUTIL_H

#include <iostream>
#include <fstream>
#include <cstdint>  // uint32_t

#include <xstring.h>
#include <hashfunctions.h>
#include <hashtbl.h>
#include <list.h>


// terminology
typedef uint32_t      ipNumber;
typedef fsu::String   ipString;

// declarations
class Router;
class ipHash;

// for code readability
enum ipClass 
{
   classA, classB, classC, badClass
} ;

std::ostream& operator << (std::ostream& os, ipClass ipc);
// sends 'A', 'B', 'C', or 'D' to os depending on ipClass value

ipClass  ipInterpret 
  (
    const ipNumber& address, // the only "input"
    ipNumber& netID,         // calculated netID of address
    ipNumber& hostID         // calculated hostID of address
  );
// pre:     none
// post:    netID and hostID for address are set
//          (these are set to 0 in case address is badClass)
// return:  the ipClass of the address

ipNumber ipS2ipN (const ipString& ips);
// converts ipString to ipNumber
// checks for correct "dot" notation syntax and field sizes

ipString ipN2ipS (ipNumber ipn);
// converts ipNumber to ipString

size_t nextstop  (const fsu::String& S, size_t i);
// called by ipS2ipN()

char*    int2str (uint32_t n);
// converts uint32_t to C-string of digits; called by ipN2ipS

#endif
