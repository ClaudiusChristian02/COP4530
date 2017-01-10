/*
    xranxstr.cpp
    Sep 1 1998
    Chris Lacher

    Implementation of the class random_String.

    Copyright 1998 - 2007, R.C. Lacher
*/

#ifndef _XRANXSTR_CCP
#define _XRANXSTR_CCP

#include <xranxstr.h>

namespace fsu
{

  Random_String::Random_String()  :  fsu::Random_cstring()
  {}

  String Random_String::Get(int n)
  // returns random String object of size n (default size in header file)
  {
    String S;
    S.size_ = n;
    S.data_ = Random_cstring::Get(n);
    // char* str = Random_cstring::Get(n);
    // S.Wrap(str);
    // delete [] str;
    return S;
  }

} // namespace fsu
#endif
