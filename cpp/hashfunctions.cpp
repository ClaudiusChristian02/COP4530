/*
    hashfunctions.cpp
    01/01/15
    Chris Lacher

    11/28/14: added ModP, upgraded signature for C-strings

    Implementations for hash functions prototyped in hashfunctions.h
    See also hashclasses.h where these are realized as function classes for use
    as template arguments.

    The ModP hash function family is important for several reasons:
    (1) they exist and perform well in all size integers, including uint64_t
    (2) a "rolling" calculation can be done to efficiently produce the hash
        value of a substring s[k ... k+m], k > 0: necessary for Rabin-Karp
        substring search algorithm


    The MM and KISS hash functions are all based on work of George Marsaglia:
    the Marsaglia Mixer and KISS random number generators.

    The Simple hash function is also provided for demonstration purposes only.

    The MM is essentially the "multiply with carry" random number
    generator by George Marsaglia, a statistics professor at FSU.  The
    xran::Crank() method is w = (w & 65535) * magic_number + (w >> 16),
    magic_number = 30103 or 18000. These are known to have period close to
    2^16 and to produce values that are extremely difficult to distinguish
    from random.

    The MM was one of the earliest RNGs to exhibit very high pseudo-randomness,
    and we have used it for years as the default hash method. It does suffer
    from its return value being a 16-bit integer embedded in an unsigned
    long. With the new 64-bit architectures it is common to need at least a
    32-bit hash value. Hence we have several upgrades to choose from, based on
    Marsaglia's KISS RNG.

    KISS is used by several game programs to generate random decisions. Check
    out a Marsaglia post at:
    http://groups.google.com/group/comp.soft-sys.math.mathematica/msg/95a94c3b2aa5f077?pli=1

    ModP is the classic modular hashing.

    Copyright 2015, R.C. Lacher
*/

#include <hashfunctions.h>
#include <cstring>

namespace hashfunction
{

  // *****************************
  //      ModP family
  // *****************************

  uint64_t ModP (const char* s, size_t length, uint64_t prime)
  {
    uint64_t hash = 0;
    for (size_t i = 0; i < length; ++i)
    {
      hash = (length * hash + (uint64_t)s[i]) % prime;
    }
    return hash;
  }

  uint64_t ModP (const fsu::String & s, uint64_t prime)
  {
    return ModP(s.Cstr(),s.Size(),prime);
  }

  uint64_t ModP (const uint64_t & i, uint64_t prime)
  {
    return i % prime;
  }

  uint64_t ModP (const std::string & s, uint64_t prime)
  {
    return ModP(s.c_str(),s.size(),prime);
  }

  uint64_t Simple (const uint64_t & i)
  {
    return 0x00001111 & i;
  }

  // *****************************
  //      Simple family
  // *****************************

  uint64_t Simple (const char* S, size_t length)
  {
    uint64_t rval(0);
    for (size_t i = 0; i < length; ++i)
    {
      rval += S[i] - 'a';
    }
    return rval;
  }

  uint64_t Simple (const fsu::String & S)
  {
    uint64_t rval(0);
    size_t len = S.Size();
    for (size_t i = 0; i < len; ++i)
    {
      rval += S[i] - 'a';
    }
    return rval;
  }

  // *****************************
  //      Marsaglia Mixer family
  // *****************************

  uint64_t MM (const uint64_t & i)
  // The MM version of xran::Crank()
  {
    uint64_t bigval = i;
    bigval = ((bigval & 65535) * 18000) + (bigval >> 16);
    bigval = ((bigval & 65535) * 18000) + (bigval >> 16);
    return bigval & 65535;
  }
  
  uint64_t MM (const char* S, size_t length)
  // This hash function accumulates the unsigned value of string characters,
  // shifting the partial sum left before each new addition.
  // Then the Marsaglia mixer is applied to this uint64_t. 
  {
    uint64_t bigval = 0;
    if (S)
    {
      bigval = S[0];
      for (size_t i = 1; i < length; ++i)
	bigval = ((bigval & 65535) * 18000) + (bigval >> 16) + S[i];
      bigval = ((bigval & 65535) * 18000) + (bigval >> 16);
    }
    return bigval & 65535;
  }

  uint64_t MM (const fsu::String& S)
  // the MM version of xran::Crank()
  {
    uint64_t bigval = S.Element(0);
    for (size_t i = 1; i < S.Size(); ++i)
      bigval = ((bigval & 65535) * 18000) + (bigval >> 16) + S[i];
    bigval = ((bigval & 65535) * 18000) + (bigval >> 16);
    return bigval & 65535;
  }

  // *****************************
  //      Marsaglia KISS family
  // *****************************

  /* // Marsaglia KISS 1
  uint64_t Crank(uint64_t x)
  { 
    uint64_t y = x;
    y ^= (y << 13); y ^= (y >> 17); y ^= (y << 5); 
    x = 69069*x + 12345;
    return x + y;
  } 
  // */

  /* // Marsaglia KISS 2
  uint64_t Crank(uint64_t x)
  { 
    uint64_t y = x;
    y ^= (y << 13); y ^= (y >> 17); y ^= (y << 5); 
    x = 69069*y + 12345;
    return x + y;
  } 
  // */

  /* // Marsaglia KISS 3
  uint64_t Crank(uint64_t x)
  { 
    uint64_t y = x;
    y ^= (y << 13); y ^= (y >> 17); y ^= (y << 5); 
    x = 69069*y + 12345;
    return x;
  } 
  // */

  /* // Marsaglia KISS 4
  uint64_t Crank(uint64_t x)
  { 
    uint64_t y = x;
    y ^= (y << 13); y ^= (y >> 17); y ^= (y << 5); 
    return y;
  } 
  // */

  // Marsaglia KISS 5
  unsigned long Crank(unsigned long x)
  { 
    x ^= (x << 13); x ^= (x >> 17); x ^= (x << 5); 
    x = 69069*x + 12345;
    return x;
  } 
  // */

  /*
    // This is Marsaglia's KISS C code
    // the "magic numbers" are important discoveries by Marsaglia
    unsigned long KISS()
    {
      static unsigned long x=123456789,y=362436000,z=521288629,c=7654321; 
      unsigned long long t, a=698769069LL; 
      x=69069*x+12345; 
      y^=(y<<13); y^=(y>>17); y^=(y<<5); 
      t=a*z+c; c=(t>>32); 
      return x+y+(z=t); 
    } 
 */

  uint64_t KISS (const uint64_t& i)
  {
    return Crank(Crank((uint64_t)i));
  }
  
  uint64_t KISS (const char* S, size_t length)
  {
    size_t i;
    uint64_t bigval = 0;
    if (S)
    {
      bigval = S[0];
      for (i = 1; i < length; ++i)
	bigval = Crank(bigval) + S[i];
      bigval = Crank(bigval);
    }
    return bigval;
  }

  uint64_t KISS (const std::string& S)
  {
    return KISS(S.c_str(), S.size());
  }

  uint64_t KISS (const fsu::String& S)
  {
    size_t i;
    uint64_t bigval = S.Element(0);
    for (i = 1; i < S.Size(); ++i)
      bigval = Crank(bigval) + S[i];
    return Crank(bigval);
  }

} // namespace hashfunction
