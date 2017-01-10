#ifndef QUEUE_H
#define QUEUE_H
#include "Vector.h"




template <class T> class queue{

public:
	void push(const T &e){ q.push_back(e); }
	void pop(){ q.pop_front(); }
	T &front(){ return q[0]; }
	bool empty(){ return q.size() == 0; }
	void clear(){ while (q.size() > 0) pop(); };

private:
	Vector < T > q;

};
#endif