#ifndef VECTOR_H
#define VECTOR_H
#include <algorithm>



/*
Thee time complexities of these operators should be as good as feasible in a vector. When the array capacity is exhausted, the array size should be increased
by a factor of 4. You may implement additional features, if you wish to. If you do not implement a copy constructor and an assignment operator, then you
should prevent their use by making them private.
*/

// template class parameter type T
template <class T> class Vector{

public:

	Vector();                            // default constructor
	Vector(const Vector <T> &other);      // copy constructor
	~Vector();                           // destructor
	void push_back(const T &e);
	T & operator[] (size_t);             // returns reference inside the internal array t unsigned type
	Vector <T> & operator= (const Vector <T> &X);
	int size() const;
	void pop_back();
	void pop_front(){ ++first; }

private:
	T *arrayStart;         // pointer of type T which can be anything
	size_t capacity;       // how much space has been allocated
	size_t length;         // number of elements in the array
	size_t first;


}; // end of class dictionary


template <class T> Vector <T>::Vector()
{
	length = 0;
	capacity = 2;
	first = 0;

	arrayStart = new T[capacity];  // initialize array of size 2

}

template <class T> Vector <T>::Vector(const Vector <T> &other){

	length = other.length - other.first;
	capacity = other.capacity;
	first = 0;

	arrayStart = new T[capacity];  // initialize array of size capacity

	for (size_t i = 0; i < length; ++i){

		// must increment the index first to get O(1) time complexity
		arrayStart[i] = other.arrayStart[other.first + i];

	}

	//std::copy(other.arrayStart, other.arrayStart + length, arrayStart);
}

// destructor
template <class T> Vector<T>::~Vector(){

	// deallocate the buffer
	delete[] arrayStart;

	// set arrayStart to null just in case
	arrayStart = 0;
}

template <class T> void Vector<T>::push_back(const T &e){

	if (length >= capacity){

		T *temporaryArray = arrayStart;

		capacity = capacity * 4;

		arrayStart = new T[capacity];

		for (size_t i = 0; i < length - first; ++i){

			arrayStart[i] = temporaryArray[first + i];
		}
		// decrease length by the first index
		length -= first;
		first = 0;

		//std::copy(temporaryArray, temporaryArray + length, arrayStart);

		delete[] temporaryArray;
	}

	// checks to see if there is space in the array
	if (length < capacity)
	{
		arrayStart[length] = e; // puts element e inside array
		length++;               // increases length
	}
} // end of template <class T> void Vector::push_back(const T &e)

template <class T> T & Vector <T>::operator[] (size_t i){

	// when elements of vector are accessed we must start at element first not 0
	return arrayStart[first + i];

} // end of template <class T> T & operator[] (size_t i)

template <class T> Vector <T> & Vector <T>:: operator= (const Vector <T> & other){

	if (this != &other){
		length = other.length - other.first;
		capacity = other.capacity;
		first = 0;

		arrayStart = new T[capacity];  // initialize array of size capacity

		for (size_t i = 0; i < length; ++i){

			// must increment the index first to get O(1) time complexity
			arrayStart[i] = other.arrayStart[other.first + i];
		}
	}

	return *this;
} // end of template <class T> Vector <T> & Vector <T>:: operator= (const Vector <T> & other)

template <class T> int Vector <T>::size() const{

	return length - first;
}

template <class T> void Vector <T>::pop_back(){

	--length;
}
#endif