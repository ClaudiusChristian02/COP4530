/*
    hashclasses.h
    03/22/2012
    Chris Lacher

    11/28/14: added ModP

    Definitions and implementations for hash function classes

    The fsu:: and alt:: versions are depracated. New clients should write to
    specific hash functions or hash classes defined here or hash.h

    Copyright 2014, R.C. Lacher
*/

#ifndef _HASHCLASSES_H
#define _HASHCLASSES_H

#include <cstdint>
#include <hashfunctions.h>

//-----------------------------
// The following class templates are just wrappers 
// for the hash functions as function classes.
// Note the inline implementations. 
//-----------------------------

/* 
   n        largest prime <= n
   ----     ------------------
   2^32     4294967291
   2^31     2147483647
   2^30     1073741789
   2^29      536870909
   2^28      268435399
*/

namespace hashclass
{
  template <typename T, size_t P = 2147483647>
  // 2147483647 = PrimeBelow (2^31)
  class ModP
  {
  public:
    uint64_t operator() (const T& t) const { return hashfunction::ModP(t,prime_); }

    const char* Name() const {return "ModP";}
    ModP() : prime_(P) {}
    const uint64_t prime_;
  };
} // hashclass */

namespace hashclass
{

  template < typename T >
  class MM
  {
  public:
    unsigned long operator() (const T& t) const { return hashfunction::MM(t); }
    const char* Name() const {return "MM";}
  };

  template < typename T >
  class KISS
  {
  public:
    unsigned long operator() (const T& t) const { return hashfunction::KISS(t); }
    const char* Name() const {return "KISS";}
  };

  template < typename T >
  class Simple
  {
  public:
    unsigned long operator() (const T& t) const { return hashfunction::Simple(t); }
    const char* Name() const {return "Simple";}
  };

} // namespace hashclass

#endif
