#ifndef COMPARE_SPY_H
#define COMPARE_SPY_H

namespace fsu{
template <class T> class LessThanSpy {

public:
	bool operator()(const T& t1, const T& t2);   // returns true if and only if t1 < t2, where T is the template parameter
	void Reset();                                // Sets the internal counter to zero
	size_t Count() const;                        // Returns the number of times operator() is called since the object was created or the last time Reset was called
	LessThanSpy();                               // default constructor. Sets the internal counter to zero

private:

	int counter;

}; // end of Class LessThanSpy < T > 




template <class T> bool LessThanSpy <T>::operator(const T& t1, const T& t2){
	
	++counter;
	return t1 < t2;

} // end of template <classt T> LessThanSpy <T>::operator()(const T& t1, const T& t2)



template <class T> void LessThanSpy <T>::Reset(){

	counter = 0;

} // end of template <classt T> LessThanSpy <T>::operator()(const T& t1, const T& t2)


template <class T> LessThanSpy <T>::LessThanSpy(){

	counter = 0;

} // end of template <class t> LessThanSpy <T>::LessThanSpy()

template <class T> size_t LessThanSpy <T>::Count() const{


	return counter;

}




} // end of namespace fsu
#endif
