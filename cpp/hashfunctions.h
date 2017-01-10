/*
    hashfunctions.h
    01/01/15
    Chris Lacher

    Prototypes for pure hash functions. Hash classes are defined in hashclasses.h.

    11/28/14: added mod prime hashing

    The fsu:: and alt:: versions are no longer supported. New clients should write to
    specific hash functions or hash classes. Older clients will need to have
    fsu::HashFunction replaced with hashfunction::MM and alt::HashFunction
    replaced with hashfunction::Simple.

    Copyright 2015, R.C. Lacher
*/

#ifndef _HASHFUNCTIONS_H
#define _HASHFUNCTIONS_H

#include <cstdint>
#include <string>
#include <xstring.h>

//-----------------------------
//     hash function prototypes
//-----------------------------

namespace hashfunction
{

  // const uint64_t PRIME = 268435399; // = fsu::PrimeBelow(0x0FFFFFFF);

  uint64_t ModP (const uint64_t & i,    uint64_t prime);
  uint64_t ModP (const fsu::String & s, uint64_t prime);
  uint64_t ModP (const std::string & s, uint64_t prime);
  uint64_t ModP (const char* s, size_t length, uint64_t prime);

  uint64_t MM (const uint64_t & i);
  uint64_t MM (const char* s);
  uint64_t MM (const fsu::String & s);

  uint64_t KISS (const uint64_t & i);
  uint64_t KISS (const char* s, size_t length);
  uint64_t KISS (const fsu::String & s);
  uint64_t KISS (const std::string & s);

  uint64_t Simple (const uint64_t & i);
  uint64_t Simple (const char* s, size_t length);
  uint64_t Simple (const fsu::String & s);

} // hashfunction

#endif
