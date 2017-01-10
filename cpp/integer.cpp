/*
    integer.cpp
    Apr 19 2001
    Chris Lacher

    Implementation of the class Integer, arbitrary precision integers. 

    We use signed-magnitude representation and store the digits in
    reverse order in a Vector<char> "digit_": digit_[0] is the sign, and
    digit_[Size()]..digit_[1] are the digits from highest to lowest
    order.

    For example, the number 123 is represented as ['+', '3', '2', '1']
    and the number -1234 is represented as ['-', '4', '3', '2', '1'].
    Zero is represented as ['+','0']. 

    Every Integer uses at least two elements of digit_,
    one for a sign (digit_[0]) and one for a digit (digit_[1]). Thus
    Integer::Size() returns digit_.Size() - 1 and
    Integer::SetSize(n) calls digit_.SetSize(n + 1). 

    These ideas are based on those of Decker and Hirschfield, 

    Copyright 2001 - 2013, R.C. Lacher
*/

#include <integer.h>
#include <iostream>
// #include <debug.h>

namespace fsu
{

// stand-alone operators

std::istream& operator >> (std::istream& s, Integer& z)
// This behaves similar to the input operator for standard int: 
// it skips leading clear space and reads an Integer; 
// if non-Integer is encountered, returns without extraction.
{
  // debug d("extraction operator");
  // reset z to zero
  z.SetSize(1); // one digit + sign
  z.digit_[0] = '+';
  z.digit_[1] = '0';

  // local vector to remember digits
  fsu::Vector<char> dig;
  char x;

  // skip leading clear space
  do s.get(x); while ((x == ' ') || (x == '\t') || (x == '\n'));

  // Set sign and skip leading zeros;
  if (x == '-') 
  {
    z.digit_[0] = x;
    do s.get(x); while (x == '0');
  }
  else if ((x == '+') || (x == '0'))
  {
    do s.get(x); while (x == '0');
  }

  // now we have moved past the (optional) sign and (optional) leading zeros

  if ((x == ' ') || (x == '\t') || (x == '\n') || (s.eof()))
  // zero case
  {
    z.digit_[0] = '+';  // convert -0 to +0
    return s;
  }
  else if (('1' <= x) && (x <= '9'))
  // non-zero case
  {
    dig.PushBack(x);
    s.get(x);
  }
  else 
  // bad input case
  {
    while((x != '\n') && (!s.eof())) s.get(x);
    std::cerr << "** non-Integer encountered attempting to extract Integer"
	      << " - buffer cleared.\n";
    return s;
  }

  // now read until we run out of digits
  while(('0' <= x) && (x <= '9'))
  {
    dig.PushBack(x);
    s.get(x);
  }

  // now transfer to properly sized Integer, reversing digit order
  z.SetSize(dig.Size());
  for (size_t i = 1; i <= z.Size(); ++i)
    z.digit_[i] = dig[dig.Size() - i];
  return s;
}

std::ostream& operator << (std::ostream& s, const Integer& z)
{
  // debug d ("insertion operator");
  if (z.digit_[0] != '+')
    s << z.digit_[0];
  for (size_t i = z.Size(); i > 0; --i)
    s << z.digit_[i];
  return s;
}

bool operator == (const Integer& x, const Integer& y)
{
  // debug d ("operator == ()");
  if (x.Size() != y.Size())
    return 0;
  for (size_t i = 0; i <= x.Size(); ++i)
  {
    if (x.digit_[i] != y.digit_[i])
      return 0;
  }
  return 1;
}

bool operator != (const Integer& x, const Integer& y)
{
  // debug d ("operator != ()");
  return (!(x == y));
}

bool operator <= (const Integer& x, const Integer& y)
{
  // debug d ("operator <= ()");
  // first take care of the O(1) cases
  if (x.digit_[0] == '+')
  {
    if (y.digit_[0] == '-')
    {
      return 0;
    }
    else // both positive
    {
      if (x.Size() < y.Size())
        return 1;
      if (x.Size() > y.Size())
        return 0;
      // remaing case falls through
    }
  }
  else
  {
    if (y.digit_[0] == '+')
    {
      return 1;
    }
    else // both negative
    {
      if (x.Size() < y.Size())
        return 0;
      if (x.Size() > y.Size())
        return 1;
      // remaing case falls through
    }
  }

  // now the O(n) case: same size, same sign
  size_t i = x.Size();
  while ((i > 0) && (x.digit_[i] == y.digit_[i]))
    --i;
  if (i == 0) // equal
  {
    return 1;
  }
  else if (x.digit_[0] == '+')
  {
    if (Integer::Int(x.digit_[i]) < Integer::Int(y.digit_[i]))
      return 1;
    else 
      return 0;
  }
  else // (x.digit_[i] == '-')
  {
    if (Integer::Int(x.digit_[i]) < Integer::Int(y.digit_[i]))
      return 0;
    else 
      return 1;
  }
}

bool operator < (const Integer& x, const Integer& y)
{
  // debug d ("operator <= ()");
  // first take care of the O(1) cases
  if (x.digit_[0] == '+')
  {
    if (y.digit_[0] == '-')
    {
      return 0;
    }
    else // both positive
    {
      if (x.Size() < y.Size())
        return 1;
      if (x.Size() > y.Size())
        return 0;
      // remaing case falls through
    }
  }
  else
  {
    if (y.digit_[0] == '+')
    {
      return 1;
    }
    else // both negative
    {
      if (x.Size() < y.Size())
        return 0;
      if (x.Size() > y.Size())
        return 1;
      // remaing case falls through
    }
  }

  // now the O(n) case: same size, same sign
  size_t i = x.Size();
  while ((i > 0) && (x.digit_[i] == y.digit_[i]))
    --i;
  if (i == 0) // equal
  {
    return 0;
  }
  else if (x.digit_[0] == '+')
  {
    if (Integer::Int(x.digit_[i]) < Integer::Int(y.digit_[i]))
      return 1;
    else 
      return 0;
  }
  else // (x.digit_[i] == '-')
  {
    if (Integer::Int(x.digit_[i]) < Integer::Int(y.digit_[i]))
      return 0;
    else 
      return 1;
  }
}

bool operator >= (const Integer& x, const Integer& y)
{
  // debug d ("operator >= ()");
  return (y <= x);
}

bool operator > (const Integer& x, const Integer& y)
{
  // debug d ("operator > ()");
  return (y < x);
}

Integer operator + (const Integer& x, const Integer& y)
{
  // debug d ("operator + ()");
  Integer z;
  if (x.digit_[0] == '+')
    if (y.digit_[0] == '+')
      return Integer::AddPos(x, y);      // x > 0, y > 0
    else
      return Integer::SubPos(x, -y);     // x > 0, y < 0
  else
    if (y.digit_[0] == '+')
      return Integer::SubPos(y, -x);     // x < 0, y > 0
    else
      return - Integer::AddPos(-x, -y);    // x < 0, y < 0
}

Integer operator - (const Integer& x, const Integer& y)
{
  // debug d ("operator - ()");
  return x + (-y);
}

Integer operator - (const Integer& x)
{
  // debug d ("unary operator - ()");
  Integer z = x;
  if (z.IsZero() || z.digit_[0] == '-')
    z.digit_[0] = '+';
  else
    z.digit_[0] = '-';
  return z;
}

Integer operator * (const Integer& x, const Integer& y)
{
  // debug d ("operator * ()");
  Integer z;
  if (x.IsZero() || y.IsZero())
    return z;
      
  z.SetSize(x.Size() + y.Size());
  if (x.digit_[0] == y.digit_[0])
    z.digit_[0] = '+';
  else
    z.digit_[0] = '-';
   
  // multiplication algorithm
  size_t i,j;
  int num, carry;
  for (i = 1; i <= x.Size(); ++i)
  {
    // cout << "{\n";
    carry = 0;
    for (j = 1; j <= y.Size(); ++j)
    {
      // cout << "  {\n";
      num = Integer::Int(x.digit_[i]) * Integer::Int(y.digit_[j])
            + Integer::Int(z.digit_[i + j - 1]) + carry;
      // cout << "    num   == " << num << '\n';
      z.digit_[i + j - 1] = Integer::Char(num % 10);
      // cout << "    z[" << i+j-1 << "] == " << z.digit_[i+j-1] << '\n';
      carry = num / 10;
      // cout << "    carry == " << carry << '\n';
      // cout << "  }\n";
    }
    z.digit_[i + j - 1] = Integer::Char(carry);
    // cout << "  z[" << i+j-1 << "] == " << z.digit_[i+j-1] << '\n';
    // cout << "}\n";
  }
  if (carry == 0)
    z.SetSize(z.Size() - 1);
  return z;
}

Integer operator / (const Integer& x, const Integer& y)
{
  // debug d ("operator / ()");
  if (y.IsZero())
  {
    std::cerr << "** Integer::operator / (): zero divisor\n";
    return y;
  }
  Integer q, nextym;
  if (x.digit_[0] == '+')
  {
    if (y.digit_[0] == '+')  // x > 0, y > 0
    {
      nextym = y;
      while (nextym <= x)
      {
        ++q;
        nextym = nextym + y;
      }
    }
    else                    // x > 0, y < 0
    {
      nextym = -y;
      while (nextym <= x)
      {
        --q;
        nextym = nextym + -y;
      }
    }
  }
  else
  {
    if (y.digit_[0] == '+')  // x < 0, y > 0
    {
      nextym = -y;
      while (nextym >= x)
      {
        --q;
        nextym = nextym + -y;
      }
    }
    else                    // x < 0, y < 0
    {
      nextym = y;
      while (nextym >= x)
      {
        ++q;
        nextym = nextym + y;
      }
    }
  }
  return q;
}

Integer operator % (const Integer& x, const Integer& y)
{
  return (x - (x / y) * y);
}

// public methods

Integer::Integer() : digit_(2,'+')
// Initialize an Integer to zero.
{
  // debug d ("Integer()");
  digit_[1] = '0';
}

Integer::Integer(long i) : digit_(20,0)
// Initialize Integer to a given long.
{
  // debug d ("Integer(long)");
  // Set the sign digit.
  if (i < 0)
  {
    digit_[0] = '-';
    i = -i;
  }
  else
    digit_[0] = '+';
      
  // Fill the digit array.
  size_t currSize = 0;
  do
  {
    digit_[++currSize] = Char(i % 10);
    i /= 10;
  }
  while (i > 0);
  SetSize(currSize);
}

Integer::Integer(const Integer& x) : digit_(x.digit_)
// Copy constructor.
{
  // debug d ("Integer(Integer&)");
}

Integer::~Integer()
{
  // debug d ("~Integer()");
}

Integer& Integer::operator = (const Integer& y)
{
  if (this != &y)
    digit_ = y.digit_;
  return *this;
}

Integer& Integer::operator +=  (const Integer& y)
{
  *this = *this + y;
  return *this;
}

Integer& Integer::operator -=  (const Integer& y)
{
  *this = *this - y;
  return *this;
}

Integer& Integer::operator *=  (const Integer& y)
{
  *this = *this * y;
  return *this;
}

Integer& Integer::operator /=  (const Integer& y)
{
  *this = *this / y;
  return *this;
}

Integer& Integer::operator %=  (const Integer& y)
{
  *this = *this % y;
  return *this;
}

Integer& Integer::operator ++ ()
{
  if (digit_[0] == '-')
  {
    digit_[0] = '+';
    operator -- ();
    digit_[0] = '-';
    return *this;
  }
  size_t i(1);
  while (i <= Size() && digit_[i] == '9')
  {
    digit_[i++] = '0';
  }
  if (i > Size())
  {
    SetSize(i);
    digit_[i] = '0';
  }
  digit_[i] = Char(Int(digit_[i]) + 1);
  return *this;
}

Integer  Integer::operator ++ (int)
{
  Integer r = *this;
  operator ++();
  return r;
}

Integer& Integer::operator -- ()
{
  if (IsZero())
  {
    digit_[0] = '-';
    digit_[1] = '1';
    return *this;
  }
  if (digit_[0] == '-')
  {
    digit_[0] = '+';
    operator ++ ();
    digit_[0] = '-';
    return *this;
  }
  size_t i(1);
  while (i <= Size() && digit_[i] == '0')
  {
    digit_[i++] = '9';
  }
  digit_[i] = Char(Int(digit_[i]) - 1);
  return *this;
}

Integer  Integer::operator -- (int)
{
  Integer r = *this;
  operator --();
  return r;
}

// protected methods

size_t Integer::Size() const
{
  return digit_.Size() - 1;
}

void Integer::SetSize(size_t n)
{
  digit_.SetSize(n + 1,'0');
}

bool Integer::IsZero() const
{
  // debug d ("IsZero()");
  return (digit_[Size()] == '0'); 
}

Integer Integer::AddPos(const Integer& x, const Integer& y)
// pre:      x >= 0 and y >= 0
// return:   x + y
{
  // debug d ("AddPos()");
  Integer z;
  size_t largeSize = ((x.Size() > y.Size()) ? x.Size() : y.Size());
  size_t smallSize = ((x.Size() <= y.Size()) ? x.Size() : y.Size());
   
  z.SetSize(largeSize + 1);
  z.digit_[0] = '+';
   
  size_t carry(0), num, currSize;
   
  for (currSize = 1; currSize <= smallSize; ++currSize)
  {
    num = Int(x.digit_[currSize]) + Int(y.digit_[currSize]) + carry;
    carry = num / 10;
    z.digit_[currSize] = Char(num % 10);
  }
  
  for (currSize = smallSize + 1; currSize <= largeSize; ++currSize)
  {
    if (largeSize == x.Size())
      num = Int(x.digit_[currSize]) + carry;
    else
      num = Int(y.digit_[currSize]) + carry;
    carry = num / 10;
    z.digit_[currSize] = Char(num % 10);
  }
   
  if (0 != carry)
    z.digit_[currSize] = Char(carry);
  else
    --currSize;
  z.SetSize(currSize);
  return z;
}

Integer Integer::SubPos(const Integer& x, const Integer& y)
// pre:      x >= 0 and y >= 0
// return:   x - y
{
  // debug d ("SubPos()");
  Integer z;  // initialized to zero
  size_t largeSize, smallSize, i;
  int signDigit;
  if (x.Size() > y.Size())
  {
    largeSize = x.Size();
    smallSize = y.Size();
    signDigit = 1;
  }
  else
  {
    largeSize = y.Size();
    smallSize = x.Size();
    signDigit = -1;  // tentative -- see next statement
  }
  if (largeSize == smallSize)
  {
    i = largeSize;
    while ((i > 0) && (x.digit_[i] == y.digit_[i]))
      --i;
    if (i == 0)  // if (x == y)
      return z;  //   return zero
    if (Int(x.digit_[i]) > Int(y.digit_[i]))
      signDigit = 1;
  }
  
  // compute large - small
  z.SetSize(largeSize);
  int borrow = 0;
  for (i = 1; i <= smallSize; ++i)
  {
    z.digit_[i] = Char((10 + borrow
                 + signDigit * (Int(x.digit_[i]) - Int(y.digit_[i]))) % 10);
    borrow = (((borrow + signDigit * (Int(x.digit_[i]) - Int(y.digit_[i]))) < 0)
                 ? -1 : 0);
  }
  for (i = smallSize + 1; i <= largeSize; i++)
  {
    if (signDigit == 1)
    {
      z.digit_[i] = Char((10 + borrow + Int(x.digit_[i])) % 10);
      borrow = (((borrow + Int(x.digit_[i])) < 0) ? -1 : 0);
    }
    else
    {
      z.digit_[i] = Char((10 + borrow + Int(y.digit_[i])) % 10);
      borrow = (((borrow + Int(y.digit_[i])) < 0) ? -1 : 0);
    }
  }
  z.digit_[0] = Sgn(signDigit);
  
  // shink-wrap
  while (z.digit_[largeSize] == '0')
    --largeSize;
  z.SetSize(largeSize);
  return z;
}

// Public member functions added for the SQUARE1 palindrom problem

Integer Integer::Reverse() const
// return *this with digits reversed
{
  // debug d ("Reverse()");
  Integer r;
  r.SetSize(Size());
  r.digit_[0] = digit_[0];
  for (size_t i = 1; i <= Size(); ++i)
    r.digit_[i] = digit_[Size() - i + 1];
//  while ((r.Size() > 1) && (r.digit_[r.Size()] == 0))
//    r.SetSize(r.Size() - 1);
  return r;
}

bool Integer::Palindrom() const
// return 1 iff *this is a palindrom
{
  // debug d ("Palindrom()");
  Integer r = (*this).Reverse();
  return (r == (*this));
}

int Integer::Int (char c)
{
  switch(c)
  {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
  }
  std::cerr << "** Integer::Int() error: non-digit argument c == " << c << '\n';
  return 10;
}

char Integer::Char (int i)
{
  switch(i)
  {
    case 0: return '0';
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
  }
  std::cerr << "** Integer::Char() error: non-digit argument i == " << i << '\n';
  return 'e';
}

char Integer::Sgn (int i)
{
  if (i > 0)
    return '+';
  if (i < 0)
    return '-';
  std::cerr << "** Integer::Sgn() error: zero argument\n";
  return 0;
}

} // namespace fsu

