/*
    gheap_basic.h
    01/01/14
    Chris Lacher

    generic heap algorithms

    basic set includes push_heap, pop_heap, and the vanilla version of heap_sort
    both predicate and default order versions are included

    These algorithms use three types
    but only two template parameters <I,P>

      I: a random access iterator class
      P: a predicate class for T
      I::ValueType for underlying container on which I iterates

    A random access iterator I is one for which the bracket operator 
      T& operator [] (size_t );
    is defined and for which "pointer" arithmetic is defined. 
    Examples include: ordinary arrays of T; TVector<T>; and TDeque<T>

    A predicate class is one for which the function evaluation operator 
      bool operator () (const T&, const T&);
    is defined. An object pred of class P is used to determine order
    in T: "a < b" iff "true = pred (a,b)"

    ValueType is not explicitly mentioned in the template (or parameter)
    list for g_heap_sort, but it is needed for the call to g_XC.

*/

#ifndef _GHEAP_H
#define _GHEAP_H

#include <cstdlib>   // size_t

namespace fsu
{
  template <class I, class P>
  void g_heap_sort (I beg, I end, P& pred);

  template <class I>
  void g_heap_sort (I beg, I end);  // the default order version

  template <class I, class P>
  void g_push_heap (I beg, I end, P& pred);

  template <class I>
  void g_push_heap (I beg, I end);  // the default order version

  template <class I, class P>
  void g_pop_heap (I beg, I end, P& pred);

  template <class I>
  void g_pop_heap (I beg, I end);  // the default order version

  template <typename T>
  void g_XC (T& t1, T& t2);
}

namespace fsu
{
  template <class I, class P>
  void g_heap_sort (I beg, I end, P& pred)
  // Implements heapsort for the iterators
  // Heapsort has the following attributes:
  //   * fast:     runtime O(size*log(size))
  //   * in-place: the sort happens in the space implied by the iterators
  //   * NOT stable -- the original order of objects a, b may change when
  //                   a == b
  // pre:  I is a random access iterator class (operator [] and "pointer" arithmetic)
  //       T is the ValueType of I
  //       P is a predicate class for type T
  // post: the range of values specified by the iterators is ordered by pred,
  //       i.e., true = pred(a,b)  <==>  a comes before b in the container
  {
    if (end - beg <= 1)
      return;
    size_t size = end - beg;
    size_t i; 
    // push elements onto heap one at a time
    for (i = 1; i < size; ++i)
    {
      fsu::g_push_heap(beg, beg + (i + 1), pred);
    }
    
    // keep popping largest remaining element to end of remaining array
    for (i = size; i > 1; --i)
    {
      fsu::g_pop_heap(beg, beg + i, pred);
    }
  } // end g_heap_sort()

  template <class I>
  void g_heap_sort (I beg, I end)
  // the default order version
  {
    if (end - beg <= 1)
      return;
    size_t size = end - beg;
    size_t i; 
    for (i = 1; i < size; ++i)
    {
      fsu::g_push_heap(beg, beg + (i + 1));
    }
    for (i = size; i > 1; --i)
    {
      fsu::g_pop_heap(beg, beg + i);
    }
  } // end g_heap_sort()

  template <class I, class P>
  void g_push_heap (I beg, I end, P& pred)
  // Defn: a < b means true = pred(a,b)
  // Defn: POT means parent >= children
  // Pre:  the range [beg,end)   is valid
  //       if the range [beg,end-1) is valid (i.e., [beg,end) is non-void)
  //         then the range [beg,end-1) is a POT
  // Post: the range [beg,end)   has been permuted
  //       the range [beg,end)   is a POT
  {
    size_t n = end - beg;
    size_t i = n - 1, p;
    bool finished = 0;
    do
    {
      if (i > 0)
      {
        p = (i - 1) / 2;  // parent node
        if (pred(beg[p],beg[i]))
        {
          g_XC(beg[i], beg[p]);
          i = p;
        }
        else
        {
          finished = 1;
        }
      }
      else
      {
        finished = 1;
      }
    }
    while (!finished);
  } // end g_push_heap()

  template <class I>
  void g_push_heap (I beg, I end)
  // the default order version
  {
    size_t n = end - beg;
    size_t i = n - 1, p;
    bool finished = 0;
    do
    {
      if (i > 0)
      {
        p = (i - 1) / 2;  // parent node
        if (beg[p] < beg[i])
        {
          g_XC(beg[i], beg[p]);
          i = p;
        }
        else
        {
          finished = 1;
        }
      }
      else
      {
        finished = 1;
      }
    }
    while (!finished);
  } // end g_push_heap()

  template <class I, class P>
  void g_pop_heap (I beg, I end, P& pred)
  // Defn: a < b means true = pred(a,b)
  // Defn: POT means parent >= children
  // Pre:  the range [beg,end)   is valid
  //       the range [beg,end-1) is valid (i.e., [beg,end) is non-void)
  //       the range [beg,end)   is a POT 
  // Post: the largest element beg[0] is removed from the range [beg,end-1)
  //       the input range [beg+1,end) has been permuted to the output range [beg,end-1)
  //       the range [beg,end-1) is a POT
  //       the old largest element (i.e., beg[0]) is copied to 
  //         the end of the old range (i.e., to beg[end - beg - 1])
  {
    if (end - beg < 2)
      return;
    g_XC(*beg,*(end - 1));
    size_t n = end - beg - 1;
    size_t i = 0, l, r;
    bool finished = 0;
    do
    {
      l = 2*i + 1; r = l + 1;  // left and right child nodes
      if (r < n)               // both child nodes exist
      {
        if (pred(beg[l],beg[r]))
        // ==> follow right subtree
        {
          if (pred(beg[i],beg[r]))
          {
            g_XC(beg[r], beg[i]);
            i = r;
          }
          else
          {
            finished = 1;
          }
        } // end if
        else // (!pred(beg[l],beg[r]))
        // ==> follow left subtree
        {
          if (pred(beg[i],beg[l]))
          {
            g_XC(beg[l], beg[i]);
            i = l;
          }
          else
          {
            finished = 1;
          }
        }  // end else
      } // end if
      else if (l < n)
      // only the left child node exists
      {
        if (pred(beg[i],beg[l]))
        {
          g_XC(beg[l], beg[i]);
        }
        finished = 1;          // no grandchild nodes exist
      } // end else if
      else                     // no child nodes exist
      {
        finished = 1;
      } // end else
    }
    while (!finished);
    // */
  } // end g_pop_heap()

  template <class I>
  void g_pop_heap (I beg, I end)
  // the default order version
  {
    if (end - beg < 2)
      return;
    size_t n = end - beg - 1;
    size_t i = 0, l, r;
    bool finished = 0;
    g_XC(beg[0],beg[n]);
    do
    {
      l = 2*i + 1; r = l + 1;  // left and right child nodes
      if (r < n)               // both child nodes exist
      {
        if (beg[l] < beg[r])
        // ==> follow right subtree
        {
          if (beg[i] < beg[r])
          {
            g_XC(beg[r], beg[i]);
            i = r;
          }
          else
            {
              finished = 1;
            }
        } // end if
        else // !(beg[l] < beg[r])
        // ==> follow left subtree
        {
          if (beg[i] < beg[l])
          {
            g_XC(beg[l], beg[i]);
            i = l;
          }
          else
          {
            finished = 1;
          }
        }  // end else
      } // end if
      else if (l < n)
      // only the left child node exists
      {
        if (beg[i] < beg[l])
        {
          g_XC(beg[l], beg[i]);
        }
        finished = 1;          // no grandchild nodes exist
      } // end else if
      else                     // no child nodes exist
      {
        finished = 1;
      } // end else
    }
    while (!finished);
  } // end g_pop_heap()

  template <typename T>
  void g_XC (T& t1, T& t2)
  {
    T temp(t1);
    t1 = t2;
    t2 = temp;
  }
  
} // namespace fsu

#endif
