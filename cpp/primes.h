/*
    primes.h
    01/01/09
    Chris Lacher

    03/23/15: added output options and a "verbose" ticker

    prototypes of functions: 
    prime_below(n), prime_above(n), all_primes_below(n, os), and sieve (bv)

    all use BitVectors, and the first three all call sieve(), an
    implementation of the  Sieve of Eratosthenes (fast, memory intensive)

    prime_below() is likely to be faster than prime_above(), because
    the former uses a bitvector of size n, while the latter needs
    a bitvector of size max_primes

    Copyright 2009, R.C. Lacher
*/

#ifndef _PRIMES_H
#define _PRIMES_H

#include <iostream>
#include <bitvect.h>

namespace fsu
{

  size_t PrimeBelow (size_t n, bool ticker = 0);
  // returns largest prime number <= n
  // or zero if input is too large

  size_t PrimeAbove (size_t n, bool ticker = 0);
  // returns smallest prime number >= n
  // or zero if input is too large

  void AllPrimesBelow (size_t n, std::ostream& os = std::cout, bool ticker = 0);
  // prints all primes less than n

  void Sieve (fsu::BitVector& b, bool ticker = 0);
  // The Sieve of Eratosthenes
  // pre:  b is a BitVector
  // post: for n < b.Size(), 
  //       n is prime iff 1 = b.Test(n)

}   // namespace fsu

#endif
