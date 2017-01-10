/*
    timer.h
    03/26/13
    Chris Lacher

    Defining classes Instant and Timer.

    These support the timing of processes using the unix clock. The metaphor is
    that of a stopwatch in a sports context: events start and stop, and split
    times can be gathered between intermediate points between start and stop. 

    Note: This uses underscore notation for method names

    Copyright 2001 - 2013, R.C. Lacher
*/

#ifndef _TIMER_H
#define _TIMER_H

#include <iostream>

namespace fsu
{

  // Instant is a gussied up version of Unix/C struct timeval; see timer.cpp

  class Instant
  {
  public:
    Instant& operator += (const Instant& i2);
    Instant& operator -= (const Instant& i2);
    Instant& operator =  (const Instant& i2);

    Instant ();
    Instant (long s, long u);
    Instant (const Instant& i);

    void Write_useconds (std::ostream& os) const;            // usec as unsigned long
    void Write_mseconds (std::ostream& os, int precision = 0) const; // msec as float
    void Write_seconds  (std::ostream& os, int precision = 0) const; // sec as float
    void Write_minutes  (std::ostream& os, int precision = 0) const; // min as float
    void Write_hours    (std::ostream& os, int precision = 0) const; // hrs as float
    void Write_time     (std::ostream& os, int precision = 0) const; // hrs:mins:secs

    unsigned long Get_useconds () const;
    double        Get_mseconds () const;
    double        Get_seconds  () const;
    double        Get_minutes  () const;
    double        Get_hours    () const;

    void Normalize ();

    long sec_,     // seconds
         usec_;    // microseconds == sec/1000000
  } ;

  Instant       operator +  (const Instant& i1, const Instant& i2);
  Instant       operator -  (const Instant& i1, const Instant& i2);
  bool          operator == (const Instant& i1, const Instant& i2);
  bool          operator != (const Instant& i1, const Instant& i2);
  bool          operator <  (const Instant& i1, const Instant& i2);
  bool          operator <= (const Instant& i1, const Instant& i2);
  bool          operator >  (const Instant& i1, const Instant& i2);
  bool          operator >= (const Instant& i1, const Instant& i2);
  std::ostream& operator << (std::ostream& os, const Instant& i);
  std::istream& operator >> (std::istream& is, Instant& i);

  class Timer
  {
  public:
    Timer();
    // the default copy constructor, assignment and destructor will work fine

    Instant AliveTime() const; // time since object was created
    Instant EventTime() const; // time since last EventReset
    Instant SplitTime() const; // time since last SplitReset

    void EventReset(); // sets event time and split time to current time
    void SplitReset(); // sets event split time to current time

  private:
    // variables
    const Instant birthTime_;
    Instant       eventTime_, splitTime_;

    // get current time
    static Instant GetTime();
  } ;

}   // namespace fsu
#endif
