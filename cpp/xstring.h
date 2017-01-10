/*
    xstring.h
    01/01/2009
    Chris Lacher

    Definition of the String class 
    The 'x' is so compiler won't confuse file names. 

    See also xranxstr.h, xstrcomp.h

    History:

    08/31/98
    08/06/00: upgraded treatment of boolean operators and StrCmp()
    10/18/00: added constructor String (size_t sz, char fill)
    12/07/02: removed outdated method Cstr(), made Clear() a public method
    12/28/04: removed broken operator const char*
              resurrected less elegant method Cstr()
    11/01/05: upgraded implementation of StrCmp()
    01/13/07: style upgrade
    09/23/07: new(std::nothrow)
    01/01/09: style upgrade

    Copyright 2009, R.C. Lacher
*/

#ifndef _XSTRING_H
#define _XSTRING_H

#include <iostream>
#include <cstdlib> // size_t

namespace fsu
{

  //--------------------
  //    class String
  //--------------------

  class String
  {
    // extraction and insertion operators
    friend std::ostream& operator << (std::ostream& os, const String& S);
    friend std::istream& operator >> (std::istream& is, String& S);
    friend class Random_String; // ref xranxstr.h

  public:
    // constructors
    String           ();                           // construct a null String 
    String           (size_t sz, char fill);       // size sz and all characters = fill
    String           (const char* cptr);           // construct a String around cptr
    ~String          ();                           // destructor
    String           (const String& s);            // copy constructor
 
    // operators
    String&      operator =   (const String& s);  // assignment operator
    char&        operator []  (size_t n) ;        // returns character n by ref
    const char&  operator []  (size_t n) const;   // const version

    // builders
    void  Wrap    (const char* cptr);        // wrap cptr up in a String
    void  GetLine (std::istream& in1);       // read/wrap entire line
    void  GetNext (std::istream& in1, char delim); // read/wrap string from here to delim
    bool  SetSize (size_t size, char fill = '\0');  // keep old data, fill extra spaces with fill character
    void  Clear   ();                        // make String empty (zero size)
    void  PushBack (char c);                 // add c to (right-hand) end of string

    // data accessors (const)
    size_t Size      ()         const;
    size_t Length    ()         const; // calls strlen(const char*)
    char   Element   (size_t n) const; // returns character n by value
                                       // (returns '\0' if n is out of range)
    size_t Position  (char c, size_t beg); // index of first occurrence of c in [beg,size)
    const char* Cstr () const; // returns C-string for use as const char* function argument

    // String comparison function
    static int StrCmp (const String&, const String&);
    // modelled on the classic strcmp() in string.h
    // called by the boolean equality and order operators

    void Dump (std::ostream& os) const;
    // displays structural output for development and testing

  private:
    // variables
    char *   data_;
    size_t   size_;

    // methods
    void          Clone   (const String& s);
    static void   Error   (const char*);
    static int    StrLen  (const char*);
    static void   StrCpy  (char*, const char*);
    static char*  NewCstr (int n);
  }  ;

  // equality and order comparison operators
  bool operator == (const String& s1, const String& s2);
  bool operator != (const String& s1, const String& s2);
  bool operator <  (const String& s1, const String& s2);
  bool operator <= (const String& s1, const String& s2);
  bool operator >= (const String& s1, const String& s2);
  bool operator >  (const String& s1, const String& s2);

  // sum (concatenation) operator
  String operator + (const String&, const String&);

}   // namespace fsu

#endif
