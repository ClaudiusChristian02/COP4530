/*
    xranxstr.h
    Sep 1, 1998
    Chris Lacher

    Definition of the class random_String.

    Copyright 1998 - 2007, R.C. Lacher
*/

#ifndef _XRANXSTR_H
#define _XRANXSTR_H

#include <xran.h>
#include <xstring.h>

namespace fsu
{

  class Random_String  :  private Random_cstring
  {
  public:
    Random_String();
    String Get (int n = 10);
    // returns random String object of size n
    String operator () (int n = 10) { return Get(n); }
  }  ;

}   // namespace fsu
#endif
