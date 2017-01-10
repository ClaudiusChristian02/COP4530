/*
    timer.cpp
    03/26/13
    Chris Lacher

    Implementing classes Instant and Timer

    Copyright 2001 - 2013, R.C. Lacher
*/

#ifndef _TIMER_CCP
#define _TIMER_CCP


// #include <dos.h>       // DOS
#include <sys/time.h>  // Unix
#include <iomanip>
#include <timer.h>

namespace fsu
{

  unsigned long Instant::Get_useconds () const
  {
    return sec_ * 1000000 + usec_;
  }

  double Instant::Get_mseconds () const
  {
     return (double)sec_ * 1000.0 + ((double)usec_) / 1000.0;
  }

  double Instant::Get_seconds () const
  {
     return (double)sec_ + ((double)usec_) / 1000000.0;
  }

  double Instant::Get_minutes () const
  {
     return ((double)sec_ + ((double)usec_) / 1000000.0 ) / 60.0;
  }

  double Instant::Get_hours () const
  {
     return ((double)sec_ + ((double)usec_) / 1000000.0 ) / 3600.0;
  }

  void Instant::Write_useconds (std::ostream& os) const
  {
    os << sec_ * 1000000 + usec_;
  }

  void Instant::Write_mseconds (std::ostream& os, int p) const
  {
    os << std::fixed << std::showpoint << std::setprecision(p)
       << (double)sec_ * 1000.0 + ((double)usec_) / 1000.0;
  }

  void Instant::Write_seconds (std::ostream& os, int p) const
  {
    os << std::fixed << std::showpoint << std::setprecision(p)
       << (double)sec_ + ((double)usec_) / 1000000.0;
  }

  void Instant::Write_minutes (std::ostream& os, int p) const
  {
    os << std::fixed << std::showpoint << std::setprecision(p)
       << ((double)sec_ + ((double)usec_) / 1000000.0 ) / 60.0;
  }

  void Instant::Write_hours (std::ostream& os, int p) const
  {
    os << std::fixed << std::showpoint << std::setprecision(p)
       << ((double)sec_ + ((double)usec_) / 1000000.0 ) / 3600.0;
  }

  void Instant::Write_time (std::ostream& os, int p)  const
  {
    double time = ((double)sec_) + ((double)usec_) / 1000000.0;
    long h(0),m(0);
    while (time < 0.0)
    {
      --h;
      time += 3600;
    }
    while (time >= 3600.0)
    {
      ++h;
      time -= 3600.0;
    }
    if (time < 0.0) time = 0.0;  // correct roundoff error
    while (time >= 60.0)
    {
      ++m;
      time -= 60;
    }
    if (time < 0.0) time = 0.0;  // correct roundoff error
    os << std::fixed << std::showpoint << std::setprecision(p)
       << h << ':' << m << ':' << time;
  }

  void Instant::Normalize ()
  {
    while (usec_ < 0)
    {
      --sec_;
      usec_ += 1000000;
    }
    while (usec_ >= 1000000)
    {
      ++sec_;
      usec_ -= 1000000;
    }
    if (usec_ < 0)
      std::cerr << "** Instant::Normalize() error: below-range usec_ detected\n"; 
    if (usec_ >= 1000000)
      std::cerr << "** Instant::Normalize() error: above-range usec_ detected\n"; 
  }

  Instant::Instant () : sec_(0), usec_(0)
  {}

  Instant::Instant (long s, long u) : sec_(s), usec_(u)
  {
    Normalize();
  }

  Instant::Instant (const Instant& i) : sec_(i.sec_), usec_(i.usec_)
  {
    Normalize();
  }

  Instant& Instant::operator = (const Instant& i)
  {
    if (this != &i)
    {
      sec_  = i.sec_;
      usec_ = i.usec_;
      Normalize();
    }
    return *this;
  }
  
  Instant& Instant::operator += (const Instant& i)
  {
    sec_  += i.sec_;
    usec_ += i.usec_;
    Normalize();
    return *this;
  }

  Instant& Instant::operator -= (const Instant& i)
  {
    sec_  -= i.sec_;
    usec_ -= i.usec_;
    Normalize();
    return *this;
  }

  Instant operator + (const Instant& i1, const Instant& i2)
  {
    Instant i(i1);
    return i += i2;
  }

  Instant operator - (const Instant& i1, const Instant& i2)
  {
    Instant i(i1);
    return i -= i2;
  }

  bool operator == (const Instant& i1, const Instant& i2)
  {
    Instant j1(i1), j2(i2);
    j1.Normalize();
    j2.Normalize();
    if (j1.sec_ != j2.sec_)
      return 0;
    if (j1.usec_ != j2.usec_)
      return 0;
    return 1;
  }

  bool operator != (const Instant& i1, const Instant& i2)
  {
    return !(i1 == i2);
  }

  bool operator < (const Instant& i1, const Instant& i2)
  {
    Instant j1(i1), j2(i2);
    j1.Normalize();
    j2.Normalize();
    if (j1.sec_ < j2.sec_)
      return 1;
    if (j1.sec_ > j2.sec_)
      return 0;
    return j1.sec_ < j2.sec_;
  }

  bool operator <= (const Instant& i1, const Instant& i2)
  {
    Instant j1(i1), j2(i2);
    j1.Normalize();
    j2.Normalize();
    if (j1.sec_ < j2.sec_)
      return 1;
    if (j1.sec_ > j2.sec_)
      return 0;
    return j1.sec_ <= j2.sec_;
  }

  bool operator > (const Instant& i1, const Instant& i2)
  {
    return i2 < i1;
  }

  bool operator >= (const Instant& i1, const Instant& i2)
  {
    return i2 <= i1;
  }

  std::ostream& operator << (std::ostream& os, const Instant& i)
  {
    i.Write_time(os,2);
    return os;
  }

  std::istream& operator >> (std::istream& is, Instant& i)
  {
    char bitbucket;
    is >> i.sec_ >> bitbucket >> i.usec_;
    return is;
  }

  Timer::Timer() : birthTime_(GetTime()),
		   eventTime_(birthTime_), splitTime_(birthTime_)
  {}

  void Timer::EventReset()
  {
    splitTime_ = eventTime_ = GetTime();
  }

  void Timer::SplitReset()
  {
    splitTime_ = GetTime();
  }

  Instant Timer::AliveTime() const
  {
    GetTime();
    return GetTime() - birthTime_;
  }

  Instant Timer::EventTime() const
  {
    return GetTime() - eventTime_;
  }

  Instant Timer::SplitTime() const
  {
    return GetTime() - splitTime_;
  }

  /*
  Instant Timer::GetTime()
  // DOS version
  {
    // this version starts at the beginning of the current day
    Instant i;
    time    t;
    ::gettime(&t);
    i.sec_  = 3600 * t.ti_hour + 60 * t.ti_min + t.ti_sec;
    i.usec_ = 10000 * t.ti_hund;
    return i;
  }
  */

  /* Defined in dos.h:
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

  Instant Timer::GetTime()
  // Unix version
  {
    // this version starts at the beginning the Unix universe -- 1/1/70
    Instant i;
    timeval t;
    gettimeofday(&t, NULL);
    i.sec_ = t.tv_sec;
    i.usec_ = t.tv_usec;
    return i;
  }

  /*
  //  defined in sys/time.h:
  struct timeval
  {
   long tv_sec,   // time since 1 JAN 1970 in seconds
        tv_usec;  // time since 1 JAN 1970 in microseconds
  };
  void gettimeofday(timeval * tvptr, NULL);
  */

} // namespace fsu
#endif
