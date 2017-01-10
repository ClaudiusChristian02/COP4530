#ifndef COMPARE_SPY.H
#define COMPARE_SPY.H

template <class T> class LessThanSpy < T > {

public:
	bool operator()(const T& t1, const T& t2);   // returns true if and only if t1 < t2, where T is the template parameter
	void Reset();                                // Sets the internal counter to zero
	size_t Count() const;                        // Returns the number of times operator() is called since the object was created or the last time Reset was called
	LessThanSpy();                               // default constructor. Sets the internal counter to zero

private:

	int counter;

}; // end of Class LessThanSpy < T > 

#endif



template <classt T> bool LessThanSpy <T>::operator()(const T& t1, const T& t2){

	if (t1 < t2){

		return true;
	}
} // end of template <classt T> LessThanSpy <T>::operator()(const T& t1, const T& t2)



template <class T> void Reset LessThanSpy <T>::Reset(){

	int counter = 0;

} // end of template <classt T> LessThanSpy <T>::operator()(const T& t1, const T& t2)


template <class T> void Reset LessThanSpy <T>::Reset(){ } //ize_t count



template <class t> LessThanSpy <T>::LessThanSpy(){

	int counter = 0;

	return counter;


} // end of template <class t> LessThanSpy <T>::LessThanSpy()