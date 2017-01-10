#ifndef GSSEARCH_H
#define GSSEARCH_H

namespace seq{
/*
	template <class I> I calc_middle(I low, I hih){

		int count = 0;

		// calculate the number of elements in the rage
		// uses iterator because it will be used later
		for (I it = low; it != hih; ++it){

			++count;

		} // for (I it = low; it != hih; ++it )

		// finds the middle
		count /= 2;

		// first counted the number of elements (for loop) then
		// increment to find the middle of the range
		while (count-- > 0){

			++low;

		}

		return low;

	} //  end of template <class I> I calc_middle(I low, I hih)
*/

	template <class I, typename T, class P>
	I g_lower_bound(I low, I hih, const T& val, P& cmp)
		// pre:    I is a random access iterator (operator [] and "pointer" arithmetic)
		//         I has ValueType T
		//         low + n = hih for some n >= 0
		//         low[0] ... low[n-1] are in non-decreasing order using cmp
		// post:   no state is changed
		// return: itr = lower bound location in range, that is:
		//         itr = low + i, where low[i-1] < val <= low[i] or
		//         itr = hih if no such i exists
	{
		I mid;
		while (low != hih)
		{
			if (cmp(*low, val))                // *low < val
				++low;
			else                                // val <= *mid
				break;
		}
		return low;
	}

template <class I, typename T, class P>
I g_upper_bound(I low, I hih, const T& val, P& cmp)
// pre:    I is a random access iterator (operator [] and "pointer" arithmetic)
//         I has ValueType T
//         low + n = hih for some n >= 0
//         low[0] ... low[n-1] are in non-decreasing order using cmp
// post:   no state is changed
// return: itr =  low + i, where low[i-1] <= val < low[i]; or
//         itr = hih if no such i exists
{
	I mid;
	while (low != hih)
	{       
                // start at the beginning and then break when larger value is found
		if (cmp(val, *low))                 // val < low[low]
			break;
		else                                // low[mid] <= val
			++low;                       
	}
	return low;
} // end of I g_upper_bound(I low, I hih, const T& val, P& cmp)

} // end of namespace seq



/*
class gssearch{

public:
	int g_lower_bound(beg, end, t, p);   // returns the lower bound of t in the range [beg,end) (using the predicate p to determine order)
	int g_upper_bound(beg, end, t, p);   // returns the upper bound of t in the range [beg,end) (using the predicate p to determine order)


}; // end of class gssearch



int gssearch::g_lower_bound(beg, end, t, p){




} // end of int gssearch::g_lower_bound(beg, end, t, p)


int gssearch::g_upper_bound(beg, end, t, p){



} // end of int gssearch::g_lower_bound(beg, end, t, p)

*/

#endif
