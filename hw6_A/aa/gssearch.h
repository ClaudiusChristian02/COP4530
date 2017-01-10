#ifndef GSSEARCH_H
#define GSSEARCH_H

class gssearch{

public:
	int g_lower_bound(beg, end, t, p);   // returns the lower bound of t in the range [beg,end) (using the predicate p to determine order)
	int g_upper_bound(beg, end, t, p);   // returns the upper bound of t in the range [beg,end) (using the predicate p to determine order)


}; // end of class gssearch

#endif