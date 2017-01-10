/*
    bitvect.cppa8
    11/11/11
    Chris Lacher

    BitVector class implementation - array of unsigned char version

    Copyright 2011, R.C. Lacher
*/

#ifndef _BITVECT_CCP
#define _BITVECT_CCP

#include <iostream>
#include <bitvect.h>

namespace fsu
{

  std::ostream& operator << (std::ostream& os, const BitVector& bv)
  {
    for (size_t i = 0; i < bv.Size(); ++i)
      os << bv.Test(i);
    return os;
  }

  //----------------------------------
  //     BitVector
  //----------------------------------

  // public methods

  void BitVector::Dump  (std::ostream& os) const
  {
    os << '\t';
    for (size_t i = 0; i < Size(); ++i)
      os << Test(i);
    os << "\n\t";
    for (size_t i = 0; i < Size(); ++i)
      os << (i % 10);
    os << '\n';
  }

  BitVector::BitVector (size_t numbits) // constructor
  {
    byteArraySize_ = (numbits + 7)/8;
    if (byteArraySize_ == 0) byteArraySize_ = 1;
    byteArray_ = new unsigned char [byteArraySize_];
    if (byteArray_ == 0)
    {
      std::cerr << "** BitVector error: memory allocation failure -- terminating program.\n";
      exit (EXIT_FAILURE);
    }
    for (size_t i = 0; i < byteArraySize_; ++i)
      byteArray_[i] = 0x00;
  }

  BitVector::BitVector (const BitVector& bv)  // copy constructor      
  {
    byteArraySize_ = bv.byteArraySize_;
    byteArray_ = new unsigned char [byteArraySize_];
    if (byteArray_ == 0)
    {
      std::cerr << "** BitVector error: memory allocation failure -- terminating program.\n";
      exit (EXIT_FAILURE);
    }
    for (size_t i = 0; i < byteArraySize_; ++i)
      byteArray_[i] = bv.byteArray_[i];
  }

  BitVector::~BitVector ()  // destructor
  {
    delete [] byteArray_;
  }

  BitVector& BitVector::operator = (const BitVector& bv)  
  // assignment operator
  {
    if (this != &bv)
    {
      if (byteArraySize_ != bv.byteArraySize_)
      {
	delete [] byteArray_;
	byteArraySize_ = bv.byteArraySize_;
	byteArray_ = new unsigned char [byteArraySize_];
	if (byteArray_ == 0)
	{
	  std::cerr << "** BitVector error: memory allocation failure -- terminating program.\n";
	  exit (EXIT_FAILURE);
	}
      }
      for (size_t i = 0; i < byteArraySize_; ++i)
	byteArray_[i] = bv.byteArray_[i];
    }
    return *this;
  }

  size_t BitVector::Size() const      
  // return size of bitvector
  {
    return 8 * byteArraySize_;
  }

  void BitVector::Set ()  
  // make all bits = 1
  {
    for (size_t i = 0; i < byteArraySize_; ++i)
      byteArray_[i] = 0xFF;
  }

  void BitVector::Set (size_t index)  
  // make bit = 1: OR with mask
  {
    byteArray_[ByteNumber(index)] |= Mask(index);
  }

  void BitVector::Unset ()  
  // make all bits = 0
  {
    for (size_t i = 0; i < byteArraySize_; ++i)
      byteArray_[i] = 0x00;
  }

  void BitVector::Unset (size_t index)  
  // make bit = 0: AND with inverted mask
  {
    byteArray_[ByteNumber(index)] &= ~ Mask(index);
  }

  void BitVector::Flip ()  
  // change all bit values
  {
    for (size_t i = 0; i < byteArraySize_; ++i)
      byteArray_[i] ^= 0xFF;
  }

  void BitVector::Flip (size_t index)  
  // change bit value: XOR with mask
  {
    byteArray_[ByteNumber(index)] ^= Mask(index);
  }

  bool BitVector::Test  (size_t index) const  
  // return bit value
  {
    return 0 != (byteArray_[ByteNumber(index)] & Mask(index));
  }
   
  // private methods

  size_t BitVector::ByteNumber (size_t index) const
  {
    // return index / 8
    // shift right 3 is equivalent to, and faster than, dividing by 8
    index = index >> 3;
    if (index >= byteArraySize_)
    {
      std::cerr << "** BitVector error: index out of range\n";
      exit (EXIT_FAILURE);
    } 
    return index;
  }

  unsigned char BitVector::Mask (size_t index)
  {
    // return mask for index % 8
    // the low order 3 bits is the remainder when dividing by 8
    size_t shiftamount = index & (size_t)0x07;  // low order 3 bits
    return (unsigned char)0x01 << shiftamount;
  }

} // namespace fsu

#endif
