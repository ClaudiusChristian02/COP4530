/*
    vector.cpp
    01/01/12
    Chris Lacher

    fsu::Vector<T> // lite version 

    Copyright 2012, R.C. Lacher
*/

//----------------------------------
//     Vector<T>:: Implementations
//----------------------------------

// operator overloads

template <typename T>
std::ostream& operator << (std::ostream& os, const Vector<T>& v)
{
  v.Display(os);
  return os;
}  // end <<

template <typename T>
bool operator == (const Vector<T>& v1, const Vector<T>& v2)
{
   if (v1.Size() != v2.Size())
      return 0;
   for (size_t i = 0; i < v1.Size(); ++i)
      if (v1[i] != v2[i])
         return 0;
   return 1;
}

template <typename T>
bool operator != (const Vector<T>& v1, const Vector<T>& v2)
{
   return !(v1 == v2);
}

// public methods

template <typename T>
Vector<T>::Vector() : size_(0), capacity_(Vector::defaultCapacity), data_(0)
// Construct a vector of zero size and default capacity
{
  data_ = NewArray(capacity_);
}

template <typename T>
Vector<T>::Vector(size_t sz) : size_(sz), capacity_(sz), data_(0)
// Construct a vector of size and capacity sz
{
  data_ = NewArray(capacity_);
}

template <typename T>
Vector<T>::Vector(size_t sz, const T& t) : size_(sz), capacity_(sz), data_(0)
// Construct a vector with all elements initialized to the same value
{
  data_ = NewArray(capacity_);
  for (size_t i = 0; i < size_; ++i)
  {
    data_[i] = t;
  }
}

template <typename T>
Vector<T>::Vector(const Vector<T>& source) : size_(source.size_), capacity_(source.capacity_)
// copy constructor      
{
  data_ = NewArray(capacity_);
  for (size_t i = 0; i < size_; ++i)
  {
    data_[i] = source.data_[i];
  }
}

template <typename T>
Vector<T>::~Vector()         
// destructor
{
  delete [] data_;
  data_ = 0;
  size_ = capacity_ = 0;
}

template <typename T>
Vector<T>& Vector<T>::operator = (const Vector<T>& source) 
// assignment operator
{
  if (this != &source)
  {
    // the NULL case
    if (source.capacity_ == 0)
    {
      if (capacity_ > 0)
	delete [] data_;
      size_ = capacity_ = 0;
      data_ = 0;
      return *this;
    }

    // set capacity 
    if (capacity_ != source.capacity_)
    {
      if (capacity_ > 0)
	delete [] data_;
      capacity_ = source.capacity_;
      data_ = NewArray(capacity_);
    }

    // set size_
    size_ = source.size_;

    // copy content
    for (size_t i = 0; i < size_; ++i)
    {
      data_[i] = source.data_[i];
    }
  }  // end if
  return *this;
}  // end assignment operator =

template <typename T>
Vector<T>& Vector<T>::operator += (const Vector<T>& v) 
{
  if (v.Empty())
    return *this;
  size_t i, s(Size());
  if (!SetSize(s + v.Size()))
  {
    std::cerr << "** Vector error: cannot expand vector in operator +=()\n";
    return *this;
  }
  for (i = 0; i < v.Size(); ++i)
    data_[i + s] = v[i];
  return *this;
}

template <typename T>
T& Vector<T>::operator [] (size_t i)
// element operator
{
  if (i >= size_)
  {
    if (i >= capacity_)
    {
      std::cerr << "** Vector<T>::operator[] error: vector index beyond memory allocation!\n";
      if (capacity_ > 0)
      {
	std::cerr << "   Returning last available location\n";
	return data_[capacity_ - 1];
      }
      std::cerr << "   Unable to recover, no memory allocated\n"
		<< "   Terminating program\n";
      exit(EXIT_FAILURE);
    }
    std::cerr << "** Vector<T>::operator[] error: vector index out of range!\n";
  }
  return data_[i];
}

template <typename T>
const T& Vector<T>::operator [] (size_t i) const                 
{
  if (i >= size_)
  {
    if (i >= capacity_)
    {
      std::cerr << "** Vector<T>::operator[] error: vector index beyond memory allocation!\n";
      if (capacity_ > 0)
      {
	std::cerr << "   Returning last available location\n";
	return data_[capacity_ - 1];
      }
      std::cerr << "   Unable to recover, no memory allocated\n"
		<< "   Terminating program\n";
      exit(EXIT_FAILURE);
    }
    std::cerr << "** Vector<T>::operator[] error: vector index out of range!\n";
  }
  return data_[i];
}

template <typename T>
bool Vector<T>::SetCapacity(size_t newcapacity)
// Reserve more (or less) space for vector growth;
// this is where memory is allocated. Note that this is 
// an expensive operation and should be used judiciuosly. 
// SetCapacity() is called by SetSize() only when increased capacity
// is required. If the client needs to reduce capacity, a call must be
// made specifically to SetCapacity.
{
  if (newcapacity == 0)
  {
    delete [] data_;
    data_ = 0;
    size_ = capacity_ = 0;
    return 1;
  }
  if (newcapacity != capacity_)
  {
    T* newcontent = NewArray(newcapacity);
    if (newcontent == 0)
      return 0;
    if (size_ > newcapacity)
      size_ = newcapacity;
    for (size_t i = 0; i < size_; ++i)
    {
      newcontent[i] = data_[i];
    }
    capacity_ = newcapacity;
    delete [] data_;
    data_ = newcontent;
  }
  return 1;
} // end SetCapacity()

template <typename T>
bool Vector<T>::SetSize(size_t newsize)
{
  if (newsize > capacity_)
  {
    if (!SetCapacity(newsize))
    {
      return 0;
    }
  }
  size_ = newsize;
  return 1;
}

template <typename T>
bool Vector<T>::SetSize(size_t newsize, const T& t)      
// (re)set size_ with extra elements initialized to the same value
{
  size_t i, oldsize = size_;
  if (!SetSize(newsize))
    return 0;
  for (i = oldsize; i < newsize; ++i)
  {
    data_[i] = t;
  }
  return 1;
}

template <typename T>
size_t Vector<T>::Capacity() const 
// return capacity of vector (current memory reserved)
{
  return capacity_;
}

// Container class protocol implementation

template <typename T>
bool Vector<T>::Empty() const
{
  return size_ == 0;
}

template <typename T>
size_t Vector<T>::Size() const
{
  return size_;
}

template <typename T>
bool Vector<T>::PushBack(const T& t)
// grow by doubling capacity
{
  if (size_ >= capacity_) 
  {
    if (capacity_ == 0)
    {
      if (!SetCapacity(1))
        return 0;
    }
    else if (!SetCapacity(2 * capacity_))
    {
      return 0;
    }
  }
  data_[size_] = t;
  ++size_;
  return 1;
}

template <typename T>
bool Vector<T>::PopBack()
{
  if (size_ == 0)
    return 0;
  --size_;
  return 1;
}

template <typename T>
void Vector<T>::Clear()
{
  SetSize(0);
}

template <typename T>
T&  Vector<T>::Front()
{
  if (size_ == 0)
  {
    std::cerr << "** Vector error: invalid Front() called on empty vector\n";
    if (capacity_ == 0)
      {
	std::cerr << "   Unable to recover, no memory allocated\n"
		  << "   Terminating program\n";
	exit(EXIT_FAILURE);
      }
    std::cerr << "   Returning first allocated location\n";
  }
  return data_[0];
}

template <typename T>
const T&  Vector<T>::Front() const
{
  if (size_ == 0)
  {
    std::cerr << "** Vector error: invalid Front() called on empty vector\n";
    if (capacity_ == 0)
      {
	std::cerr << "   Unable to recover, no memory allocated\n"
		  << "   Terminating program\n";
	exit(EXIT_FAILURE);
      }
    std::cerr << "   Returning first allocated location\n";
  }
  return data_[0];
}

template <typename T>
T&  Vector<T>::Back()
{
  if (size_ == 0)
  {
    std::cerr << "** Vector error: invalid Back() called on empty vector\n";
    if (capacity_ == 0)
      {
	std::cerr << "   Unable to recover, no memory allocated\n"
		  << "   Terminating program\n";
	exit(EXIT_FAILURE);
      }
    std::cerr << "   Returning last allocated location\n";
    return data_[capacity_ - 1];
  }
  return data_[size_ - 1];
}

template <typename T>
const T&  Vector<T>::Back() const
{
  if (size_ == 0)
  {
    std::cerr << "** Vector error: invalid Back() called on empty vector\n";
    if (capacity_ == 0)
      {
	std::cerr << "   Unable to recover, no memory allocated\n"
		  << "   Terminating program\n";
	exit(EXIT_FAILURE);
      }
    std::cerr << "   Returning last allocated location\n";
    return data_[capacity_ - 1];
  }
  return data_[size_ - 1];
}

template <typename T>
void Vector<T>::Swap (Vector<T>& v)
{
  // Lock lock();
  fsu::Swap(size_,v.size_);
  fsu::Swap(capacity_,v.capacity_);
  fsu::Swap(data_,v.data_);
}

// output

template <typename T>
void Vector<T>::Display(std::ostream& os, char ofc) const
// note: this tests ConstIterator
{
  ConstIterator i;
  if (ofc == '\0')
    for (i = Begin(); i != End(); ++i)
      os << *i;
  else
    for (i = Begin(); i != End(); ++i)
      os << *i << ofc;
} // end Display()


template <typename T>
void Vector<T>::Dump(std::ostream& os) const
// note: this tests const version of []
{
  size_t i;
  for (i = 0; i < capacity_; ++i)
  {
    if (i < 10)
      os << "    data_[" << i << "] == " << data_[i];
    else if (i < 100)
      os << "   data_[" << i << "] == " << data_[i];
    else if (i < 1000)
      os << "  data_[" << i << "] == " << data_[i];
    else if (i < 10000)
      os << " data_[" << i << "] == " << data_[i];
    else 
      os << "data_[" << i << "] == " << data_[i];
    if (i == 0) 
      os << " <- begin";
    if (i == size_) 
      os << " <- end";
    os << '\n';
  }
  i = capacity_;
  if (i < 10)
    os << "    data_[" << i << "] == <undefined>";
  else if (i < 100)
    os << "   data_[" << i << "] == <undefined>";
  else if (i < 1000)
    os << "  data_[" << i << "] == <undefined>";
  else if (i < 10000)
    os << " data_[" << i << "] == <undefined>";
  else 
    os << "data_[" << i << "] == <undefined>";
  if (i == size_) 
    os << " <- end";
  os << '\n';
} // end Dump()

// protected

template <typename T>
T* Vector<T>::NewArray(size_t newcapacity)
// safe memory allocator
{
  T* tptr;
  if (newcapacity > 0)
  {
    tptr = new T [newcapacity];
    if (tptr == 0)
    {
      std::cerr << "** Vector error: unable to allocate memory for array!\n";
      exit (EXIT_FAILURE);
    }
  }
  else
  {
    tptr = 0;
  }
  return tptr;
}



// Iterator support - pointer version

template <typename T>
typename Vector<T>::Iterator Vector<T>::Begin ()
{
  return data_;
}

template <typename T>
typename Vector<T>::ConstIterator Vector<T>::Begin () const
{
  return data_;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::End()
{
  return data_ + size_;
}

template <typename T>
typename Vector<T>::ConstIterator Vector<T>::End() const
{
  return data_ + size_;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::rBegin ()
{
  Iterator i = End();
  return --i;
}

template <typename T>
typename Vector<T>::ConstIterator Vector<T>::rBegin () const
{
  ConstIterator i = End();
  return --i;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::rEnd()
{
  Iterator i = Begin();
  return --i;
}

template <typename T>
typename Vector<T>::ConstIterator Vector<T>::rEnd() const
{
  ConstIterator i = Begin();
  return --i;
}

