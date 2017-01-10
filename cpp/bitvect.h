/*
    bitvect.ha8
    11/11/11
    Chris Lacher

    BitVector class - based on array of 8-bit words

    Copyright 2011, R.C. Lacher
*/

#ifndef _BITVECT_H
#define _BITVECT_H

#include <cstdlib>
#include <iostream>

namespace fsu
{

  //----------------------------------
  //     BitVector
  //----------------------------------

  class BitVector;

  std::ostream& operator << (std::ostream&, const BitVector&);

  class BitVector
  {
  public:
    explicit BitVector  (size_t size);       // construct a BitVector with specified size
             BitVector  (const BitVector&);  // copy constructor      
             ~BitVector ();                  // destructor

    BitVector& operator = (const BitVector& a);  // assignment operator

    size_t Size () const;              // return size of bitvector

    void Set   ();                     // make all bits = 1
    void Set   (size_t index);         // make bit = 1
    void Unset ();                     // make all bits = 0
    void Unset (size_t index);         // make bit = 0
    void Flip  ();                     // change all bits 
    void Flip  (size_t index);         // change bit 
    bool Test  (size_t index) const;   // return bit value

    void Dump  (std::ostream& os) const;
   
  private:
    // data
    unsigned char *      byteArray_;
    size_t               byteArraySize_;

    // methods
    size_t               ByteNumber (size_t index) const;
    static unsigned char Mask       (size_t index);

  } ; // class BitVector

}   // namespace fsu
#endif
