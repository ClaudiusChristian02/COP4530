/*
    primes.cpp
    01/01/09
    Chris Lacher

    03/23/15: added options

    implementations of functions prototyped in primes.h

    Copyright 2009-15, R.C. Lacher
*/

#ifndef _PRIMES_CCP
#define _PRIMES_CCP

#include <primes.h>
#include <iomanip>

namespace fsu
{

  static const size_t maxPrime = 99999989; // largest prime < 100000000
  // maxPrime needs to be a prime number less than max size_t
  // used by PrimeAbove only

  size_t PrimeBelow (size_t n, bool ticker)
  // returns largest prime number <= n
  // This is likely to be more efficient than PrimeAbove(), because
  // it only needs a bitvector of size n+1
  {
    if (n <= 1) return 0;
    if (n == 2) return 2;

    if (n < n + 1) // n is not the largest size_t
      ++n;         // otherwise n is a power of 2 and hence not prime
    fsu::BitVector b(n);
    Sieve(b, ticker);
    --n;
    if ((n & 0x01) == 0) --n; // now n is odd
    while (n > 3)
    {
      if (b.Test(n))
        return n;
      n -= 2;
    }
    return 2;
  }

  size_t PrimeAbove (size_t n, bool ticker)
  // returns smallest prime number >= n
  // or zero if input is too large
  {
    if (n <= 2) return 2;
    size_t m = n << 1; // m = 2n 
    if (n <= m)        // n <= 2n => overflow
    {
      return 0;
    }
    fsu::BitVector b(m);
    Sieve(b, ticker);

    while (n < m)
    {
      if (b.Test(n))
        return n;
      ++n;
    }
    return PrimeAbove(m,ticker);
  }

  void AllPrimesBelow (size_t n, std::ostream& os, bool ticker)
  // writes all primes <= n to os
  {
    if (n < n + 1) // n is not the largest size_t
      ++n;
    fsu::BitVector b(n);
    Sieve(b, ticker);

    for (size_t i = 0; i < n; ++i)
      if (b.Test(i))
	os << ' ' << i;
    os << std::endl;
  }

  void Sieve(BitVector& b, bool ticker)
  // pre:  b is a BitVector
  // post: for all n < b.Size(), 
  //       n is prime iff 1 = b.Test(n)
  {
    const size_t max = b.Size();
    size_t sqrt = 2;
    while (sqrt*sqrt < max)
    {
      ++sqrt;
    }
    // initialize b
    b.Set();
    b.Unset(0);  // 0 is not prime
    b.Unset(1);  // 1 is not prime

    // clear bits at multiples of all primes < sqrt(max)
    for (size_t i = 2; i < sqrt; ++i)
    {
      if (b.Test(i)) // i is prime
      {
        if (ticker) std::cout << '.' << std::flush;
	for (size_t j = i + i; j < max; j+= i)  // clear all multiples of i
        {
	  b.Unset(j);
        }
      }
    }
    if (ticker) std::cout << '\n';
  }  // end sieve()

} // namespace fsu

#endif
