/*
    xran.h
    11/11/13
    Chris Lacher

    Definition of classes:
    Random_int, Random_float, Random_char, Random_cstring

    class Random_String is treated in seperate files

    Notation: the phrase to right of underscore is a type

    History:

    01/01/97: initial development
    12/09/00: operator () () introduced
    04/13/01: namespace rcl introduced
    04/13/01: namespace fsu introduced
    01/15/07: style upgrade
    04/01/09: minor revisions
    09/05/11: converted engine to KISS [32-bit]
    03/26/12: move to fixed width types defined in stdint.h
    11/11/13: go to C++ style C libraries
    04/04/15: added Random_uint32_t

    about operator () ()
    --------------------

    The xran family of random object generators is now a family of function
    classes whose objects are function objects.  This introduces the following
    syntactical mechanism for producing random objects (shown for random
    integers):

    Random_int ranint;
    y = ranint(100); // y is a random integer in the range [0, 100)

    Copyright 1997 - 2015, R.C. Lacher
*/

#ifndef _XRAN_H
#define _XRAN_H

#include <cstdlib>
#include <climits>
#include <cstdint>

namespace fsu
{

  //-------------------------
  //    class RandomBase
  //-------------------------

  class RandomBase
  {
  public:
    RandomBase();
    uint64_t Get();  // returns random unsigned 32-bit integer in a 64 bit register
    uint64_t operator () () { return Get(); }

  private:
    void Crank();
    uint64_t word_;
  }  ;

  //-------------------------
  //    class Random_int
  //-------------------------

  class Random_int : private RandomBase
  {
  public:
    Random_int();
    int Get(long int LB = INT_MIN, long int UB = INT_MAX);
    // returns random int in the interval [LB, UB)
    // NOTE: unpredictable result returned if
    //       UB is not in the unsigned int range [0,UINT_MAX]

    int SafeGet(long int LB = INT_MIN, long int UB = INT_MAX);
    // same as Get(), but with bounds checking

    int operator () (long int LB = INT_MIN, long int UB = INT_MAX) { return Get (LB,UB); }
  }  ;

  //-----------------------------
  //    class Random_unsigned_int
  //-----------------------------

  class Random_unsigned_int : private RandomBase
  {
  public:
    Random_unsigned_int();
    unsigned int Get(unsigned long LB = 0, unsigned long UB = UINT_MAX);
    // returns random unsigned int in the interval [LB, UB)
    // NOTE: unpredictable result returned if
    //       LB >= UB, or
    //       LB and UB are not in the range [0..uint_max)

    unsigned int SafeGet(unsigned long LB = 0, unsigned long UB = UINT_MAX);
    // same as Get(), but with bounds checking

    unsigned int operator () (unsigned long LB = 0, unsigned long UB = UINT_MAX) { return Get (LB,UB); }
  }  ;

  //-----------------------------
  //    class Random_uint32_t
  //-----------------------------

  class Random_uint32_t : private RandomBase
  {
  public:
    Random_uint32_t();
    uint32_t Get(uint32_t LB = 0, uint32_t UB = UINT32_MAX);
    // returns random uint32_t in the interval [LB, UB)
    // NOTE: unpredictable result returned if
    //       LB >= UB, or
    //       LB and UB are not in the range [0..uint_max)

    uint32_t SafeGet(uint32_t LB = 0, uint32_t UB = UINT32_MAX);
    // same as Get(), but with bounds checking

    uint32_t operator () (uint32_t LB = 0, uint32_t UB = UINT32_MAX) { return Get (LB,UB); }
  }  ;

  //-------------------------
  //    class Random_float
  //-------------------------

  class Random_float : private RandomBase
  {
  public:
    Random_float();
    float Get (float LB = 0.0, float UB = 1.0);
    // returns random float in the interval [LB, UB)
    // NOTE: results are sparse when bounds exceed +/- INT_MAX)
    float SafeGet (float LB = 0.0, float UB = 1.0);
    float operator () (float LB = 0.0, float UB = 1.0) { return Get(LB,UB); }
  }  ;

  //-------------------------
  //    class Random_letter
  //-------------------------

  class Random_letter : private Random_unsigned_int
  {
  public:
    Random_letter();
    char Get();
    // returns random lower case letter
    char operator () () { return Get (); }
  }  ;

  //-------------------------
  //    class Random_cstring
  //-------------------------

  class Random_cstring : private Random_unsigned_int
  {
  public:
    Random_cstring();
    char* Get(size_t n = 10);
    // returns random (C-style) character string of length n
    char* operator () (size_t n = 10) { return Get(n); }
  }  ;

}   // namespace fsu
#endif
