/*
    xran.cpp
    11/11/13
    Chris Lacher

    Member functions for random object classes

    The base class RandomBase contains a basic pseudo-random unsigned int
    generator that implements the multiply-with-carry generator of
    George Marsaglia,  Professor Emeritus of Statistics at FSU.

    The derived classes adapt the base class engine to various types.

    Copyright 1997 - 2013, R.C. Lacher
*/

#ifndef _XRAN_CCP
#define _XRAN_CCP

#include <iostream>      // std::cerr
// #include <dos.h>         // time (dos)
#include <sys/time.h>    // timeval (unix)
#include <xran.h>        // defines classes

namespace fsu
{

  namespace Marsaglia  // used for MM, but not KISS
  {
    static const long int magicNumber = 30103;    // period  near 2^31
    // const long int magicNumber = 18000;    // also good 
  }

  //-------------------------------------
  //   class RandomBase
  //-------------------------------------

  RandomBase::RandomBase() : word_(0)
  // constructor
  // uses clock to seed generator, activates to get random fill
  {
    // seed for unix
    timeval tv;               // struct defined in sys/time.h
    gettimeofday(&tv, NULL);  // (see end of this file)
    word_ = tv.tv_usec;       // word_ initialized as number of microsecs
    // */

    /* // seed for dos:
    struct time current;        // struct defined in dos.h
    gettime(&current);   // (see end of this file)
    word_ = int(current.ti_hour) + int(current.ti_min)
                                 + int(current.ti_sec)
                                 + int(current.ti_hund); 
    // end DOS seed */

    // Crank 7 times to mix up the register
    for (size_t i = 0; i < 7; ++i) 
      Crank();
  }  

  // Marsaglia KISS 5
  void RandomBase::Crank()
  { 
    word_ ^= (word_ << 13); word_ ^= (word_ >> 17); word_ ^= (word_ << 5); 
    word_ = 69069*word_ + 12345;
  } 

  uint64_t RandomBase::Get()
  // returns random unsigned 32-bit integer in a 64-bit register
  {
    Crank();   // KISS
    return (word_ & 0x00000000FFFFFFFF);   // return low32
  }
  // KISS */

  /* // Marsaglia Mixer
  void RandomBase::Crank()
  // This is the "multiply with carry" random generator of George Marsaglia,
  // using 32-bit integers, yields 16-bit pseudo-random integer.
  // word_ = low16 * magicNumber + high16; return low16
  {
    word_ = (word_ & 65535) * Marsaglia::magicNumber + (word_ >> 16); 
  }

  unsigned long RandomBase::Get()
  // returns random unsigned 16-bit integer in a 32-bit register
  {
    Crank();                  // word_ = low16 * magicNumber + high16
    return (word_ & 65535);   // return low16
  }
  // MM */

  //-------------------------------------
  //   class Random_int
  //-------------------------------------

  Random_int::Random_int() : RandomBase()
  {}

  int Random_int::Get(long int LB, long int UB)
  // returns random int in the interval [LB, UB)
  {
    return (((RandomBase::Get()) % (UB - LB)) + LB);
  }

  int Random_int::SafeGet(long int LB, long int UB)
  // returns random int in the interval [LB, UB)
  // NOTE: The preliminary if statement prevents erroneous returns
  // caused by overflow, but at a performance penalty. 
  // The method Random_int::Get() does not check bounds, and is
  // therefore faster.
  {
    // prevent overflow in casting:
    if ((LB >= UB)  ||
	(UB > INT_MAX) || (UB < INT_MIN) || (LB > INT_MAX) || (LB < INT_MIN))
    {
      std::cerr << "*** xran error: incompatible bounds passed to function"
		<< " Random_int::Get(long int LB, long int UB).";
      exit(1);
    }
    return (((RandomBase::Get()) % (UB - LB)) + LB);
  }

  //-------------------------------------
  //   class Random_unsigned_int
  //-------------------------------------

  Random_unsigned_int::Random_unsigned_int() : RandomBase()
  {}

  unsigned int Random_unsigned_int::Get(unsigned long LB, unsigned long UB)
  // returns random int in the interval [LB, UB)
  {
    return (((RandomBase::Get()) % (UB - LB)) + LB);
  }

  unsigned int Random_unsigned_int::SafeGet(unsigned long LB, unsigned long UB)
  // returns random int in the interval [LB, UB)
  // NOTE: The preliminary if statement prevents erroneous returns
  // caused by overflow, but at a performance penalty. 
  // The method Random_unsigned_int::Get() does not check bounds, and is
  // therefore faster.
  {
    // prevent overflow in casting:
    if ((LB >= UB)  || (UB > UINT_MAX))
    {
      std::cerr << "*** xran error error: incompatible bounds passed to function"
		<< " Random_unsigned_int::Get(unsigned long LB, unsigned long UB).";
      exit(1);
    }
    return (((RandomBase::Get()) % (UB - LB)) + LB);
  }

  //-------------------------------------
  //   class Random_float
  //-------------------------------------

  Random_float::Random_float() : RandomBase()
  {}

  float Random_float::Get(float LB, float UB)
  // returns random float in the interval [LB, UB)
  {
    return (float(RandomBase::Get()) * (UB - LB)) / UINT_MAX + LB;
  }

  float Random_float::SafeGet(float LB, float UB)
  // returns random float in the interval [LB, UB)
  {
    if (LB >= UB)
    {
      std::cerr << "*** xran error: incompatible bounds passed to function"
		<< " Random_float::Get(float LB, float UB).";
      exit(1);
    }
    return (float(RandomBase::Get()) * (UB - LB)) / UINT_MAX + LB;
  }

  //-------------------------------------
  //   class Random_cstring
  //-------------------------------------

  Random_cstring::Random_cstring() : Random_unsigned_int()
  {}

  char* Random_cstring::Get(size_t n)
  // returns random (C-style) character string of length n
  {
    char* str;
    str = new (std::nothrow) char [n+1];
    if (str == NULL)
    {
      std::cerr << "*** xran error: unable to create memory for string"
		<< " in function Random_cstring::Get(int length).";
      exit(1);
    }

    for (size_t i = 0; i < n; ++i)
      str[i] = char((unsigned)'a' + Random_unsigned_int::Get(0,26));
    str[n] = '\0';
    return str;
  }

  //-------------------------------------
  //   class Random_letter
  //-------------------------------------

  Random_letter::Random_letter() : Random_unsigned_int()
  {}

  char Random_letter::Get()
  // returns random lower case letter
  {
    return char((unsigned)'a' + Random_unsigned_int::Get(0,26));
  }

  //-------------------------------------------------
  //   documentation on time functions used for seed
  //-------------------------------------------------

  /*
  // defined in sys/time.h (Unix):
  struct timeval
  {
    long tv_sec,   // time since 1 JAN 1970 in seconds
         tv_usec;  // time since 1 JAN 1970 in microseconds
  } ;
  void gettimeofday(timeval * t, NULL);
  */

  /*
  // defined in dos.h (DOS):
  struct time
  {
    unsigned char   ti_min;     // Minutes 
    unsigned char   ti_hour;    // Hours 
    unsigned char   ti_hund;    // Hundredths of seconds 
    unsigned char   ti_sec;     // Seconds
  };

  struct date
  {
    int     da_year;    // Year - 1980
    char    da_day;     // Day of the month 
    char    da_mon;     // Month (1 = Jan) 
  };

  long _RTLENTRY  _EXPFUNC   dostounix(struct date _FAR *__d, struct time _FAR *__t);
  void _RTLENTRYF _EXPFUNC32 getdate(struct date _FAR *__datep);
  void _RTLENTRYF _EXPFUNC32 gettime(struct time _FAR *__timep);
  void _RTLENTRY  _EXPFUNC32 setdate(struct date _FAR *__datep);
  void _RTLENTRY  _EXPFUNC32 settime(struct time _FAR *__timep);
  void _RTLENTRY  _EXPFUNC   unixtodos(long __time, struct date _FAR *__d,
  */

  //-------------------------------------
  //   class Random_uint32_t
  //-------------------------------------

  Random_uint32_t::Random_uint32_t() : RandomBase()
  {}

  uint32_t Random_uint32_t::Get(uint32_t LB, uint32_t UB)
  // returns random int in the interval [LB, UB)
  {
    return (((RandomBase::Get()) % (UB - LB)) + LB);
  }

  uint32_t Random_uint32_t::SafeGet(uint32_t LB, uint32_t UB)
  // returns random int in the interval [LB, UB)
  // NOTE: The preliminary if statement prevents erroneous returns
  // caused by overflow, but at a performance penalty. 
  // The method Random_uint32_t::Get() does not check bounds, and is
  // therefore faster.
  {
    // prevent overflow in casting:
    if ((LB >= UB)  || (UB > UINT_MAX))
    {
      std::cerr << "*** xran error error: incompatible bounds passed to function"
		<< " Random_uint32_t::Get(uint32_t LB, uint32_t UB).";
      exit(1);
    }
    return (((RandomBase::Get()) % (UB - LB)) + LB);
  }

} // namespace fsu

#endif
