/*
   CHAR.h

   defines type CHAR
   case-insensitive char 

   Useful in illustrating such things as unimodal insert, where equality is not
   the same is being identical

   All comparison operators are defined by the usual meaning, but on the upper
   case version. This divides the alpha char into equivalence classes
   {a,A},{b,B}, ... , {z,Z}.

*/

#ifndef _CHAR_H
#define _CHAR_H

#include <cctype>
#include <iostream>

struct CHAR
// illustrates unimodal insert, since lower and upper case are considered equal
{
  char val_;
  CHAR( ) : val_('\0') {}
  CHAR( const CHAR& c ) : val_(c.val_) {}
  CHAR& operator= (const CHAR& c) {val_ = c.val_; return *this;}
  explicit CHAR( char ch ) : val_(ch) {}
};
bool operator == (const CHAR & c1 , const CHAR & c2)
{
  return (toupper(c1.val_) == toupper(c2.val_));
}
bool operator < (const CHAR & c1 , const CHAR & c2)
{
  return (toupper(c1.val_) < toupper(c2.val_));
}

// these are all defined in terms of == and <
bool operator != (const CHAR & c1 , const CHAR & c2)
{
  return !(c1 == c2);
}
bool operator > (const CHAR & c1 , const CHAR & c2)
{
  return (c2 < c1);
}
bool operator <= (const CHAR & c1 , const CHAR & c2)
{
  return !(c2 < c1);
}
bool operator >= (const CHAR & c1 , const CHAR & c2)
{
  return !(c1 < c2);
}

std::ostream& operator << (std::ostream& os, const CHAR& c)
{
  os << c.val_;
  return os;
}
std::istream& operator >> (std::istream& os, CHAR& c)
{
  os >> c.val_;
  return os;
}

#endif
