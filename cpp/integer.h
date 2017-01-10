/*
    integer.h
    01/12/10
    Chris Lacher

    Definition of the class Integer

    Integer is a class of arbitrary precision base 10 integers,
    the number of digits limited only by the maximum size of an array of char.
    The class uses a private fsu::Vector<char> object to store digits.

    Copyright 2001 - 2013, R.C. Lacher
*/

#include <iostream>
#include <vector.h>

#ifndef _INTEGER_H
#define _INTEGER_H

namespace fsu
{

  class Integer
  {
    friend std::istream& operator >> (std::istream& s, Integer& n);
    friend std::ostream& operator << (std::ostream& s, const Integer& n);

    friend Integer operator  +  (const Integer& n, const Integer& m);
    friend Integer operator  -  (const Integer& n, const Integer& m);
    friend Integer operator  -  (const Integer& n);
    friend Integer operator  *  (const Integer& n, const Integer& m);
    friend Integer operator  /  (const Integer& n, const Integer& m);
    friend Integer operator  %  (const Integer& n, const Integer& m);

    friend bool    operator  == (const Integer& n, const Integer& m);
    friend bool    operator  != (const Integer& n, const Integer& m);
    friend bool    operator  <= (const Integer& n, const Integer& m);
    friend bool    operator  <  (const Integer& n, const Integer& m);
    friend bool    operator  >= (const Integer& n, const Integer& m);
    friend bool    operator  >  (const Integer& n, const Integer& m);

  public:
    Integer   ();                  // Initialize an Integer to zero
    Integer   (long n);            // Initialize: typecast long to Integer
    Integer   (const Integer& y);  // copy constructor
    ~Integer  ();                  // destructor
    Integer& operator  =  (const Integer& y);
    Integer& operator +=  (const Integer& y);
    Integer& operator -=  (const Integer& y);
    Integer& operator *=  (const Integer& y);
    Integer& operator /=  (const Integer& y);
    Integer& operator %=  (const Integer& y);
    Integer& operator ++  ();
    Integer  operator ++  (int);
    Integer& operator --  ();
    Integer  operator --  (int);

    // added to test for palindroms
    Integer Reverse   () const;    // return Integer with digits reversed
    bool    Palindrom () const;    // return 1 iff Integer is a palindrom

  protected:
    // variables
    fsu::Vector < char >  digit_; // the digit array

    // methods
    size_t         Size    () const;    // return number of digits
    void           SetSize (size_t n);  // set number of digits
    bool           IsZero  () const;    // Test for zero.
    static Integer AddPos  (const Integer& x, const Integer& y);
    static Integer SubPos  (const Integer& x, const Integer& y);
    static int     Int     (char c); // char digit to int digit
    static char    Char    (int i);  // int digit to char digit
    static char    Sgn     (int i);  // non-zero int to char sign 
  } ;

}   // namespace fsu
#endif
