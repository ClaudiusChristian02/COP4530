/*
    xstring.cpp
    01/01/2009
    Chris Lacher

    Implementations of String methods, friends, and other overloads

    In this implementation the cases (data_ == 0) and (size_ == 0) are
    treated as equal (empty) Strings.

    Note that size_, the return value for Size(), is maintained as one less than
    the size of the containing array by these methods.  The Length() method, on
    the other hand, returns the value of strlen() applied to the private
    C-string datum.  Normally, Size() and Length() should return the same value.
    However, this relationship could be corrupted by the client, by for example
    assigning S[i] = '\0'.

    Copyright 1998 - 2009, R.C. Lacher
*/

#ifndef _XSTRING_CCP
#define _XSTRING_CCP

#include <cstdlib>   // EXIT_FAILURE and other definitions
#include <cstring>   // the C string function library

#include <xstring.h>
// #include <debug.h>

namespace fsu
{

  //--------------------
  //    class String
  //--------------------
  
  static const size_t initBuffSize = 250;
  // used as size increment for local buffer during extraction
  // file scope

  // String operator overloads
  // first the String comparison function, used to define the comparison operators:

  int String::StrCmp(const String& S1, const String& S2)
  // returns:   0 if S1 == S2
  //            - if S1 < S2
  //            + if S1 > S2
  // using lexicographic ordering
  {
    // convenience aliases:
    const char* s1(S1.data_);
    const char* s2(S2.data_);

    // pointer null cases:
    if (s1 == 0 || s2 == 0)
    {
      if (s1 != 0)
	return s1[0];
      if (s2!= 0)
	return -s2[0];
      return 0;
    }

    // essentially the code for strcmp(const char* , const char*):
    while
      (
             *s1 == *s2          // elements are the same 
         &&  *s1 != '\0'         // first element not null
         &&  *s2 != '\0'         // second element not null
      )
    { 
      ++s1; ++s2;              // go to next elements
    }

    // return the difference at the first place where strings differ
    // - avoid overflow of type char
    int rval = *s1;
    rval -= *s2;
    return rval;
  } // end StrCmp()

  // second the comparison operators:

  bool operator == (const String& s1, const String& s2)
  {
    return (String::StrCmp(s1, s2) == 0);
  }

  bool operator != (const String& s1, const String& s2)
  {
    return (String::StrCmp(s1, s2) != 0);
  }

  bool operator >  (const String& s1, const String& s2)
  {
    return (String::StrCmp(s1, s2) > 0);
  }

  bool operator >=  (const String& s1, const String& s2)
  {
    return (String::StrCmp(s1, s2) >= 0);
  }

  bool operator <  (const String& s1, const String& s2)
  {
    return (String::StrCmp(s1, s2) < 0);
  }

  bool operator <=  (const String& s1, const String& s2)
  {
    return (String::StrCmp(s1, s2) <= 0);
  }

  // third the I/O operators:

  std::ostream& operator << (std::ostream& os, const String& S)
  {
    if (S.data_ != 0)
      os << S.data_;
    return os;
  }

  std::istream& operator >> (std::istream& is, String& S)
  {
    // Debug d("operator >> ()");
    size_t currSize = 0, buffSize = initBuffSize;

    // skip clearspace
    char x;
    is >> x;
    if (is.fail() || is.eof())
    {
      return is;
    }

    // space for temporary char storage
    char* buffer = String::NewCstr(buffSize);

    // insert x and continue reading contiguous non-clearspace
    buffer[currSize++] = x;
    x = is.peek();
    while ((x != ' ') && (x != '\n') && (x != '\t') && (!is.eof()))
    {
      if (currSize == buffSize)  // need more buffer 
      {
	buffSize *= 2;
	char* newbuffer = String::NewCstr(buffSize);
	for (size_t i = 0; i < currSize; ++i)
	{
	  newbuffer[i] = buffer[i];
	}
	delete [] buffer;
	buffer = newbuffer;
      }
      buffer[currSize++] = x;
      is.get();
      x = is.peek();
    }
    buffer[currSize] = '\0';
    S.Wrap(buffer);
    delete [] buffer;
    return is;
  }

  // fourth the concatenation operator:

  String operator + (const String&s1, const String& s2)
  {
    String S (s1.Size() + s2.Size(), '\0');
    size_t i;
    
    for (i = 0; i < s1.Size(); ++i)
    {
      S[i] = s1.Element(i);
    }
    
    for (i = s1.Size(); i < S.Size(); ++i)
    {
      S[i] = s2.Element(i - s1.Size());
    }

    return S;
  }

  // String member functions
  // constructors

  String::String() : data_(0), size_(0)
  {
    // Debug d("String constructor 1");
  }

  String::String(const char* Cptr)  :  data_(0), size_(0)  
  {
    // Debug d("String constructor 2");
    Wrap(Cptr);
  }

  String::String (size_t size, char fill) : data_(0), size_(0)
  {
    // Debug d("String constructor 3");
    SetSize(size,fill);
  }

  String::~String()
  {
    // Debug d("String destructor");
    if (data_) delete [] data_;
  }

  String::String(const String& S)
  {
    // Debug d("String copy constructor");
    Clone(S);
  }

  // String operators

  String& String::operator = (const String& S)
  {
    // Debug d("assignment");
    if (this != &S)
    {
      if (size_ != S.size_)
      {
	Clear();
	Clone(S);
      }
      else if (size_ != 0)
      {
	StrCpy (data_, S.data_);
      }
    }
    return *this;
  }

  char& String::operator [] (size_t n)
  // overload of the array access operator
  // Note: [] returns a reference to the element, hence can be used on
  // the left (receiving end) of assignment.
  // Distinctions between [] and Element():
  //    Element(n) returns a value, equal to the element data_[n] 
  //      when 0 <= n < size_ and to '\0' otherwise.
  //    Element(n) cannot be used to assign a (new) value to the element.
  //    [n] returns a reference to the element when 0 <= n < size_
  //      and exits otherwise.
  //    [n] can be used to assign a value to any element except the last.
  {
    if ((size_ == 0) || (n >= size_))
    {
      Error("index out of range");
    }
    return *(data_ + n);
  }

  const char& String::operator [] (size_t n) const
  // const version
  {
    if ((size_ == 0) || (n >= size_))
    {
      Error("index out of range");
    }
    return *(data_ + n);
  }

  // String builders

  void String::Wrap(const char* Cptr)
  {
    // Debug d("Wrap()");
    Clear();
    if (Cptr)
    {
      size_ = StrLen(Cptr);
      data_ = NewCstr(size_);
      StrCpy(data_, Cptr);
    }
  }

  void String::PushBack(char c)
  {
    // Debug d("PushBackq()");
    std::cout << "fsu::String::PushBack(" << c << ") not implemented\n";
  }

  void String::GetLine (std::istream& is)
  {
    // Debug d("GetLine()");
    size_t currSize = 0, buffSize = initBuffSize;
    char* buffer;
    buffer = NewCstr(buffSize);
    char x = is.get();
    while ((x != '\n') && (!is.eof()))
    {
      if (currSize == buffSize)  // need more buffer 
      {
	buffSize *= 2;
	char* newbuffer = NewCstr(buffSize);
	for (size_t i = 0; i < currSize; ++i)
	{
	  newbuffer[i] = buffer[i];
	}
	delete [] buffer;
	buffer = newbuffer;
      }
      buffer[currSize++] = x;
      x = is.get();
    }
    buffer[currSize] = '\0';
    Wrap(buffer);
    delete [] buffer;
  }

  void String::GetNext (std::istream& is, char delim)
  {
    // Debug d("GetNext()");
    size_t currSize = 0, buffSize = initBuffSize;
    char* buffer;
    buffer = NewCstr(buffSize);
    char x = is.get();
    while ( (x!= delim) && (x != '\n') && (!is.eof()))
    {
      if (currSize == buffSize)  // need more buffer 
      {
	buffSize *= 2;
	char* newbuffer = NewCstr(buffSize);
	for (size_t i = 0; i < currSize; ++i)
	{
	  newbuffer[i] = buffer[i];
	}
	delete [] buffer;
	buffer = newbuffer;
      }
      buffer[currSize++] = x;
      x = is.get();
    }
    buffer[currSize] = '\0';
    Wrap(buffer);
    delete [] buffer;
  }

  bool String::SetSize (size_t size, char fill)
  {
    if (data_ == 0)
    {
      data_ = NewCstr(size);
      if (data_ == 0) return 0;
      size_ = size;
      for (size_t j = 0; j < size_; ++j)
	data_[j] = fill;
      return 1;
    }

    if (size != Size())
    {
      char* newdata = NewCstr(size);
      if (newdata == 0) return 0;
      size_t i;
      if (size < Size())
      {
	for (i = 0; i < size; ++i)
	  newdata[i] = data_[i];
      }
      else
      {
	for (i = 0; i < Size(); ++i)
	  newdata[i] = data_[i];
	for (i = Size(); i < size; ++i)
	  newdata[i] = fill;
      }
      delete [] data_;
      data_ = newdata;
      size_ = size;
    }
    return 1;
  }

  void String::Clear()
  {
    // Debug d("Clear()");
    if (data_)
    {
      delete [] data_;
      data_ = 0;
      size_ = 0;
    }
  }

  // String data accessors

  /*
    String::operator const char* () const 
    // Overload of the operator "const char*" for String objects;
    // typical use is in automatic type conversion. For example, any
    // function from string.h that takes const char* parameter can now
    // automatically be called on String objects. See Length()
    // implementation below.
    {
    return data_;
    }
  */

  const char* String::Cstr() const
  // returns bare C string for use as const char* function argument
  {
    return data_;
  }

  size_t String::Size() const
  {
    return size_;
  }

  size_t String::Length () const
  {
    if (data_ != 0)
      return strlen (data_);
    return 0;
  }

  char String::Element(size_t n) const
  {
    if ((size_ == 0) || (n >= size_))
      return '\0';
    else
      return data_[n];
  }

  size_t String::Position  (char c, size_t beg)
  {
    // fsu::Debug("String::Position");
    while (beg < size_ && data_[beg] != c)
    {
      ++beg;
    }
    return beg;
  }

  void String::Dump (std::ostream& os) const
  {
    os << "String::Size()         = " << Size() << '\n'
       << "String::Length()       = " << Length() << '\n'
       << "c-string operator <<() : " << data_ << '\n'
       << "String:: operator <<() : " << *this << '\n';
  }

  // private methods

  void String::Clone(const String& S)
    // Dangerous -- take care not to apply to *this !
  {
    // Debug d("Clone()");
    size_ = S.Size();
    if (S.data_)
    {
      data_ = NewCstr(size_);
      StrCpy (data_, S.data_);
    }
    else
    {
      data_ = 0;
    }
  } // end Clone()

  char* String::NewCstr(int n)
  // creates a new C-string of size n (array size = n+1)
  // with memory allocation error message
  {
    // Debug d("NewCstr()");
    char* Cptr;
    if (n >= 0)
    {
      Cptr = new(std::nothrow) char [n + 1];
      if (Cptr == 0)
      {
	Error("memory allocation failure");
      }
      Cptr[n] = '\0';
    }
    else
      Cptr = 0;
    return Cptr;
  } // end NewCstr()

  int String::StrLen(const char* s)
  // a version of strlen()
  {
    // Debug d("StrLen()");
    int len = 0;
    if (s != 0)
    {
      for (len = 0; s[len] != '\0'; ++len){}
    }
    return len;
  } // end StrLen()

  void String::StrCpy(char* s1, const char* s2)
  // a version of strcpy(); DOES NOT CHECK OPERAND ARRAY SIZES
  {
    // Debug d("StrCpy()");
    if (s2 != 0)
    {
      if (s1 != 0)
      {
	int i;
	for (i = 0; s2[i] != '\0'; ++i)
	  s1[i] = s2[i];
	s1[i] = '\0';
      }
      else
      {
	Error("StrCpy() operand 0");
      }
    }
  } // end StrCpy()

  void String::Error(const char* msg)
  {
    std::cerr << "** String error: " << msg << '\n';
    exit (EXIT_FAILURE);
  }

} // namespace fsu
#endif
