/*
    deque_ca.cpp
    01/01/12
    Chris Lacher

    The classic "circular array" implementation

    beg_ = array index of front element
    end_ = 1 past index of back element (mod contentSize_)

    Copyright 2012, R.C. Lacher
*/

#ifndef _DEQUE_CPP
#define _DEQUE_CPP

//----------------------------------
//     Deque<T>
//----------------------------------

namespace deque
{
  static const size_t defaultContentSize = 10;
}

// operator overloads

template <typename T>
std::ostream& operator << (std::ostream& os, const Deque<T>& Q)
{
  Q.Display(os);
  return os;
}

template <typename T>
bool operator == (const Deque<T>& Q1, const Deque<T>& Q2)
{
  if (Q1.Size() != Q2.Size())
    return 0;
  for (size_t i = 0; i < Q1.Size(); ++i)
    if (Q1[i] != Q2[i])
      return 0;
  return 1;
}

template <typename T>
bool operator != (const Deque<T>& Q1, const Deque<T>& Q2)
{
  return !(Q1 == Q2);
}

// public methods

template <typename T>
Deque<T>::Deque() : content_(0), contentSize_(0), beg_(0), end_(0)
// Construct a deque of zero size and default contentSize_
{
  content_ = new(std::nothrow) T [deque::defaultContentSize];
  if (content_ == 0)
  {
    std::cerr << "** Deque error: unable to allocate memory in default constructor\n";
    exit(EXIT_FAILURE);
  }
  contentSize_ = deque::defaultContentSize;
}

template <typename T>
Deque<T>::~Deque()
{
  delete[] content_;
  content_=0;
}

template <typename T>
Deque<T>::Deque(size_t cap, const T& Tval)
  :  content_(0), contentSize_(0), beg_(0), end_(0)
// Construct a deque of capacity cap and all elements initialized to Tval
{
  content_ = new(std::nothrow) T [cap];
  if (content_ == 0)
  {
    std::cerr << "** Deque error: unable to allocate memory in 2-argument constructor\n";
    exit(EXIT_FAILURE);
  }
  contentSize_ = cap;
  for (size_t i = 0; i < contentSize_; ++i)
    content_[i] = Tval;
}

template <typename T>
Deque<T>::Deque(const Deque<T>& Q) 
  :  content_(0), contentSize_(Q.contentSize_), beg_(Q.beg_), end_(Q.end_)
// copy constructor      
{
  content_ = new(std::nothrow) T [contentSize_];
  if (content_ == 0)
  {
    std::cerr << "** Deque error: unable to allocate memory in copy constructor\n";
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < contentSize_; ++i)
    content_[i] = Q.content_[i];
}

template <typename T>
Deque<T>& Deque<T>::operator = (const Deque<T>& Q) 
// assignment operator
{
  if (this != &Q)
  {
    T* newContent = new(std::nothrow) T [Q.contentSize_];
    if (newContent == 0)
    {
      std::cerr << "** Deque error: unable to allocate memory in assignment operator\n";
      return *this;  // unchanged
    }
    delete [] content_;
    content_ = newContent;
    contentSize_ = Q.contentSize_;
    beg_ = Q.beg_;
    end_ = Q.end_;
    for (size_t i = 0; i < contentSize_; ++i)
      content_[i] = Q.content_[i];
  }
  return *this;
}

template <typename T>
T& Deque<T>::operator [] (size_t i)
{
  if (Size() <= i)
  {
    std::cerr << "** Deque::operator[] error: index out of range\n";
    // exit (EXIT_FAILURE);
  }
  i += beg_;
  if (i >= contentSize_)
    i -= contentSize_;  
  return content_[i];
}

template <typename T>
const T& Deque<T>::operator [] (size_t i) const
{
  if (Size() <= i)
  {
    std::cerr << "** Deque::operator[]const error: index out of range\n";
    // exit (EXIT_FAILURE);
  }
  i += beg_;
  if (i >= contentSize_)
    i -= contentSize_;  
  return content_[i];
}

// Container class protocol implementation

template <typename T>
bool Deque<T>::Empty() const
{
  return beg_ == end_;
}

template <typename T>
size_t Deque<T>::Size() const
{
  if (beg_ <= end_)
    return end_ - beg_;
  return contentSize_ + end_ - beg_;
}

template <typename T>
bool Deque<T>::PushFront(const T& Tval)
{
  if (Size() + 1 >= contentSize_)
  // deque is full -- grow by doubling content size
  {
    size_t newContentSize,i;
    newContentSize = 2 * contentSize_;
    if (contentSize_ == 0) newContentSize = 2;
    T* newContent = new(std::nothrow) T [newContentSize];
    if (newContent == 0)
    {
      std::cerr << "** Deque error: unable to allocate memory for PushFront()\n";
      return 0; // unchanged
    }
    // copy data to new content array
    if (beg_ <= end_)
    {
      for (i = beg_; i < end_; ++i) newContent[i] = content_[i];
    }
    else
    {
      for (i = beg_; i < contentSize_; ++i) newContent[i] = content_[i];
      for (i = 0; i < end_; ++i) newContent[i + contentSize_] = content_[i];
      end_ += contentSize_;
    }
    // switch to new content
    delete [] content_;
    content_ = newContent;
    contentSize_ = newContentSize;

    // insert Tval into unused slots, for display purposes
    // note that beg_ <= end_ in all cases now
    for (i = 0; i < beg_; ++i) content_[i] = Tval;
    for (i = end_; i < contentSize_; ++i) content_[i] = Tval;
  }
  // now there is extra capacity
  if (beg_ == 0)
    beg_ = contentSize_;
  --beg_;
  content_[beg_] = Tval;
  return 1;
}

template <typename T>
bool Deque<T>::PushBack(const T& Tval)
{
  if (Size() + 1 >= contentSize_)
  // deque is full -- grow by doubling content size
  {
    size_t newContentSize,i;
    newContentSize = 2 * contentSize_;
    if (contentSize_ == 0) newContentSize = 2;
    T* newContent = new(std::nothrow) T [newContentSize];
    if (newContent == 0)
    {
      std::cerr << "** Deque error: unable to allocate memory for PushBack()\n";
      return 0; // unchanged
    }
    // copy data to new content array
    if (beg_ <= end_)
    {
      for (i = beg_; i < end_; ++i) newContent[i] = content_[i];
    }
    else
    {
      for (i = beg_; i < contentSize_; ++i) newContent[i] = content_[i];
      for (i = 0; i < end_; ++i) newContent[i + contentSize_] = content_[i];
      end_ += contentSize_;
    }
    // switch to new content
    delete [] content_;
    content_ = newContent;
    contentSize_ = newContentSize;

    // insert Tval into unused slots, for display purposes
    // note that beg_ <= end_ in all cases now
    for (i = 0; i < beg_; ++i) content_[i] = Tval;
    for (i = end_; i < contentSize_; ++i) content_[i] = Tval;
  }
  // now there is extra capacity
  content_[end_] = Tval;
  ++end_;
  if (end_ == contentSize_)
    end_ = 0;
  return 1;
}

template <typename T>
bool Deque<T>::PopFront()
{
  if (beg_ == end_)
    return 0;
  ++beg_;
  if (beg_ == contentSize_)
    beg_ = 0;
  return 1;
}

template <typename T>
bool Deque<T>::PopBack()
{
  if (beg_ == end_)
    return 0;
  if (end_ == 0)
    end_ = contentSize_;
  --end_;
  return 1;
}

template <typename T>
void Deque<T>::Clear()
{
  beg_ = 0;
  end_ = 0;
}

template <typename T>
T&  Deque<T>::Front()
{
  if (beg_ == end_)
  {
    std::cerr << "** Deque error: Front() called on empty deque\n";
    if (contentSize_ == 0)
      exit (EXIT_FAILURE);
  }
  return content_[beg_];
}

template <typename T>
const T&  Deque<T>::Front() const
{
  if (beg_ == end_)
  {
    std::cerr << "** Deque error: Front() called on empty deque\n";
    if (contentSize_ == 0)
      exit (EXIT_FAILURE);
  }
  return content_[beg_];
}

template <typename T>
T&  Deque<T>::Back()
{
  if (beg_ == end_)
  {
    std::cerr << "** Deque error: Back() called on empty deque\n";
    if (contentSize_ == 0)
      exit (EXIT_FAILURE);
  }
  if (end_ == 0)
    return content_[contentSize_ - 1];
  return content_[end_ - 1];
}

template <typename T>
const T&  Deque<T>::Back() const
{
  if (beg_ == end_)
  {
    std::cerr << "** Deque error: Back() called on empty deque\n";
    if (contentSize_ == 0)
      exit (EXIT_FAILURE);
  }
  if (end_ == 0)
    return content_[contentSize_ - 1];
  return content_[end_ - 1];
}

// Iterator support

template <typename T>
typename Deque<T>::Iterator Deque<T>::Begin ()
{
  Iterator I;
  I.dequePtr_ = this;
  I.indexBase_ = 0;
  return I;
}

template <typename T>
typename Deque<T>::Iterator Deque<T>::End()
{
  Iterator I;
  I.dequePtr_ = this;
  I.indexBase_ = this->Size();
  return I;
}

template <typename T>
typename Deque<T>::Iterator Deque<T>::rBegin()
{
  Iterator I;
  I.dequePtr_ = this;
  if (this->Empty())
    I.indexBase_ = 0;
  else
    I.indexBase_ = this->Size() - 1;
  return I;
}

template <typename T>
typename Deque<T>::Iterator Deque<T>::rEnd()
{
  Iterator I;
  I.dequePtr_ = this;
  I.indexBase_ = this->Size(); // same as " -1 "
  return I;
}

// ConstIterator support

template <typename T>
typename Deque<T>::ConstIterator Deque<T>::Begin () const
{
  Iterator I;
  I.dequePtr_ = this;
  I.indexBase_ = 0;
  return I;
}

template <typename T>
typename Deque<T>::ConstIterator Deque<T>::End() const
{
  Iterator I;
  I.dequePtr_ = this;
  I.indexBase_ = this->Size();
  return I;
}

template <typename T>
typename Deque<T>::ConstIterator Deque<T>::rBegin() const
{
  Iterator I;
  I.dequePtr_ = this;
  if (this->Empty())
    I.indexBase_ = 0;
  else
    I.indexBase_ = this->Size() - 1;
  return I;
}

template <typename T>
typename Deque<T>::ConstIterator Deque<T>::rEnd() const
{
  Iterator I;
  I.dequePtr_ = this;
  I.indexBase_ = this->Size(); // same as " -1 "
  return I;
}

// output methods

template <typename T>
void Deque<T>::Display(std::ostream& os, char ofc) const
{
  size_t i;
  if (ofc == '\0')
    for (i = 0; i < this->Size(); ++i)
      os << operator[](i);
  else
    for (i = 0; i < this->Size(); ++i)
      os << operator[](i) << ofc;
}  // end Display()

template <typename T>
void Deque<T>::Dump(std::ostream& os) const
{
  // special "horizontal" Dump for T = char
  if (sizeof(ValueType) == 1)
  {
    os << " content_[i]: ";
      for (size_t i = 0; i < contentSize_; ++i)
	os << ' ' << content_[i];
    os << '\n';
    os << "    i mod 10: ";
      for (size_t i = 0; i < contentSize_; ++i)
	os << ' ' << i % 10;
    os << '\n';

    if (beg_ < end_)
    {
      os << "              ";
      for (size_t i = 0; i < beg_; ++i)
	os << "  ";
      os << " b";
      for (size_t i = beg_+1; i < end_; ++i)
	os << "  ";
      os << " e";
      os << '\n';
    }
    else if (end_ < beg_)
    {
      os << "              ";
      for (size_t i = 0; i < end_; ++i)
	os << "  ";
      os << " e";
      for (size_t i = end_+1; i < beg_; ++i)
	os << "  ";
      os << " b";
      os << '\n';
    }
    else // (end_ == beg_)
    {
      os << "              ";
      for (size_t i = 0; i < beg_; ++i)
	os << "  ";
      os << " ^b=e";
      os << '\n';
    }

    return;
  }

  // "vertical" Dump for all other types:
  for (size_t i = 0; i < contentSize_; ++i)
  {
    if (i < 10)
      os << "    content_[" << i << "] == " << content_[i];
    else if (i < 100)
      os << "   content_[" << i << "] == " << content_[i];
    else if (i < 1000)
      os << "  content_[" << i << "] == " << content_[i];
    else if (i < 10000)
      os << " content_[" << i << "] == " << content_[i];
    else 
      os << "content_[" << i << "] == " << content_[i];
    if (i == beg_) 
      os << " <- beg";
    if (i == end_)
      os << " <- end";
    os << '\n';
  }
}

//----------------------------------
//     DequeIterator<T>
//----------------------------------

template <typename T>
DequeIterator<T>::DequeIterator () : dequePtr_(0), indexBase_(0)
{}

template <typename T>
DequeIterator<T>::DequeIterator (const Deque<T>& Q)
 : dequePtr_(&Q), indexBase_(0)
{}

template <typename T>
DequeIterator<T>::DequeIterator (const DequeIterator<T>& i)
  :  dequePtr_(i.dequePtr_), indexBase_(i.indexBase_)
{}

template <typename T>
bool DequeIterator<T>::Valid () const
{
  if (0 == dequePtr_)
    return 0;
  if (indexBase_ >= dequePtr_->Size())
    return 0;
  return 1;
}

template <typename T>
bool DequeIterator<T>::operator == (const Iterator& i2) const
{
  if (dequePtr_ != i2.dequePtr_)
    return 0;
  if (indexBase_ != i2.indexBase_)
    return 0;
  return 1;
}

template <typename T>
bool DequeIterator<T>::operator != (const Iterator& i2) const
{
  return !(*this == i2);
}

template <typename T>
T&  DequeIterator<T>::operator *  ()
{
  if (0 == dequePtr_)
  {  
    std::cerr << "** DequeIterator error: invalid dereference\n";
    exit (EXIT_FAILURE);
  }
  if (dequePtr_->Size() == 0)
    std::cerr << "** DequeIterator error: invalid dereference\n";
  return const_cast<T&>(dequePtr_->operator[](indexBase_));
}

template <typename T>
const T&  DequeIterator<T>::operator *  () const
{
  if (0 == dequePtr_)
  {  
    std::cerr << "** DequeIterator error: invalid dereference\n";
    exit (EXIT_FAILURE);
  }
  if (dequePtr_->Size() == 0)
    std::cerr << "** DequeIterator error: invalid dereference\n";
  return dequePtr_->operator[](indexBase_);
}

template <typename T>
T&  DequeIterator<T>::operator [] (size_t index)
{
  if (!dequePtr_)
  {
    std::cerr << "** DequeIterator error: invalid dereference\n";
    exit (EXIT_FAILURE);
  }
  return const_cast<T&>(dequePtr_->operator[](indexBase_ + index));
}

template <typename T>
const T&  DequeIterator<T>::operator [] (size_t index) const
{
  if (!dequePtr_)
  {
    std::cerr << "** DequeIterator error: invalid dereference\n";
    exit (EXIT_FAILURE);
  }
  return dequePtr_->operator[](indexBase_ + index);
}

template <typename T>
DequeIterator<T>& DequeIterator<T>::operator = (const Iterator & i)
{
  if (this != &i)
  {
    dequePtr_ = i.dequePtr_;
    indexBase_ = i.indexBase_;
  }
  return *this;
}

template <typename T>
DequeIterator<T>& DequeIterator<T>::operator ++ ()
{
  if (indexBase_ == dequePtr_->Size())
    indexBase_ = 0;
  else 
    ++indexBase_;
  return *this;
}

template <typename T>
DequeIterator<T>  DequeIterator<T>::operator ++ (int)
{
  Iterator i(*this);
  operator ++();
  return i;
}

template <typename T>
DequeIterator<T>& DequeIterator<T>::operator -- ()
{

  if (indexBase_ == 0)
    indexBase_ = dequePtr_->Size();
  else
    --indexBase_;
  return *this;
}

template <typename T>
DequeIterator<T>  DequeIterator<T>::operator -- (int)
{
  Iterator i(*this);
  operator --();
  return i;
}

template <typename T>
long DequeIterator<T>::operator -  (const Iterator & i2) const
{
  return indexBase_ -  i2.indexBase_;
}

// these are the new template pointer arithmetic operator implementations

template <typename T>
template <typename N>
DequeIterator<T>& DequeIterator<T>::operator += (N n)
{
  indexBase_ += n;
  return *this;
}

template <typename T>
template <typename N>
DequeIterator<T>& DequeIterator<T>::operator -= (N n)
{
  indexBase_ -= n;
  return *this;
}

template <typename T>
template <typename N>
DequeIterator<T>  DequeIterator<T>::operator + (N n) const
{
  Iterator i(*this);
  return i += n;
}

template <typename T>
template <typename N>
DequeIterator<T>  DequeIterator<T>::operator - (N n) const
{
  Iterator i(*this);
  return i -= n;
}

//----------------------------------
//     ConstDequeIterator<T>
//----------------------------------

template <typename T>
ConstDequeIterator<T>::ConstDequeIterator () : dequePtr_(0), indexBase_(0)
{}

template <typename T>
ConstDequeIterator<T>::ConstDequeIterator (const Deque<T>& Q)
 : dequePtr_(&Q), indexBase_(0)
{}

template <typename T>
ConstDequeIterator<T>::ConstDequeIterator (const ConstDequeIterator<T>& i)
  :  dequePtr_(i.dequePtr_), indexBase_(i.indexBase_)
{}

template <typename T>
ConstDequeIterator<T>::ConstDequeIterator (const DequeIterator<T>& i)
  :  dequePtr_(i.dequePtr_), indexBase_(i.indexBase_)
{}

template <typename T>
bool ConstDequeIterator<T>::Valid () const
{
  if (0 == dequePtr_)
    return 0;
  if (indexBase_ >= dequePtr_->Size())
    return 0;
  return 1;
}

template <typename T>
bool ConstDequeIterator<T>::operator == (const ConstIterator& i2) const
{
  if (dequePtr_ != i2.dequePtr_)
    return 0;
  if (indexBase_ != i2.indexBase_)
    return 0;
  return 1;
}

template <typename T>
bool ConstDequeIterator<T>::operator != (const ConstIterator& i2) const
{
  return !(*this == i2);
}

template <typename T>
const T&  ConstDequeIterator<T>::operator *  () const
{
  if (0 == dequePtr_)
  {  
    std::cerr << "** ConstDequeIterator error: invalid dereference\n";
    exit (EXIT_FAILURE);
  }
  if (dequePtr_->Size() == 0)
    std::cerr << "** ConstDequeIterator error: invalid dereference\n";
  return dequePtr_->operator[](indexBase_);
}

template <typename T>
const T&  ConstDequeIterator<T>::operator [] (size_t index) const
{
  if (!dequePtr_)
  {
    std::cerr << "** ConstDequeIterator error: invalid dereference\n";
    exit (EXIT_FAILURE);
  }
  return dequePtr_->operator[](indexBase_ + index);
}

template <typename T>
ConstDequeIterator<T>& ConstDequeIterator<T>::operator = (const ConstIterator & i)
{
  if (this != &i)
  {
    dequePtr_ = i.dequePtr_;
    indexBase_ = i.indexBase_;
  }
  return *this;
}

template <typename T>
ConstDequeIterator<T>& ConstDequeIterator<T>::operator ++ ()
{
  if (indexBase_ == dequePtr_->Size())
    indexBase_ = 0;
  else 
    ++indexBase_;
  return *this;
}

template <typename T>
ConstDequeIterator<T>  ConstDequeIterator<T>::operator ++ (int)
{
  ConstIterator i(*this);
  operator ++();
  return i;
}

template <typename T>
ConstDequeIterator<T>& ConstDequeIterator<T>::operator -- ()
{

  if (indexBase_ == 0)
    indexBase_ = dequePtr_->Size();
  else
    --indexBase_;
  return *this;
}

template <typename T>
ConstDequeIterator<T>  ConstDequeIterator<T>::operator -- (int)
{
  ConstIterator i(*this);
  operator --();
  return i;
}

template <typename T>
long ConstDequeIterator<T>::operator -  (const ConstIterator & i2) const
{
  return indexBase_ -  i2.indexBase_;
}

// these are the new template pointer arithmetic operator implementations

template <typename T>
template <typename N>
ConstDequeIterator<T>& ConstDequeIterator<T>::operator += (N n)
{
  indexBase_ += n;
  return *this;
}

template <typename T>
template <typename N>
ConstDequeIterator<T>& ConstDequeIterator<T>::operator -= (N n)
{
  indexBase_ -= n;
  return *this;
}

template <typename T>
template <typename N>
ConstDequeIterator<T>  ConstDequeIterator<T>::operator + (N n) const
{
  ConstIterator i(*this);
  return i += n;
}

template <typename T>
template <typename N>
ConstDequeIterator<T>  ConstDequeIterator<T>::operator - (N n) const
{
  ConstIterator i(*this);
  return i -= n;
}

#endif
