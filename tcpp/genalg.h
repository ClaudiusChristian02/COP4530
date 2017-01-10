/*
    genalg.h
    01/01/11
    Chris Lacher

    Basic generic algorithms

    I, J  iterator classes (I = input iterator, J = output iterator)
    T     ValueType
    P     predicate class (may be unary or binary, depending on context)
    F     function class  (context determined)

    Copyright 2009 - 2011, R.C. Lacher
*/

#ifndef _GENALG_H
#define _GENALG_H

namespace fsu
{

  template <class I, typename T>
  void g_fill (I beg, I end, const T& t)
  {
    while (beg != end)
      *beg++ = t;
  }

  template <class I, typename T>
  void g_fill_n (I beg, unsigned int n, const T& t)
  {
    while (n-- > 0)
      *beg++ = t;
  }

  template <class I, class J>
  void g_copy (I source_beg, I source_end, J dest_beg)
  {
    while (source_beg != source_end) 
      *dest_beg++ = *source_beg++;
  }

  template <class I, class J>
  void g_copy_backward (I source_beg, I source_end, J dest_beg)
  {
    while (source_beg != source_end) 
      *dest_beg-- = *source_beg++;
  }

  template <class I>
  I g_min_element (I beg, I end)
  {
    if (beg == end)
      return beg;
    I min (beg);  
    while (++beg != end)
      if (*beg < *min)
	min = beg;
    return min;
  }

  template <class I, class P>
  I g_min_element (I beg, I end, const P& p)
  {
    if (beg == end)
      return beg;
    I min = beg;
    while (++beg != end)
      if (p(*beg,*min))
	min = beg;
    return min;
  }

  template <class I>
  I g_max_element (I beg, I end)
  {
    if (beg == end)
      return beg;
    I max (beg);  
    while (++beg != end)
      if (*max < *beg)
	max = beg;
    return max;
  }

  template <class I, class P>
  I g_max_element (I beg, I end, const P& p)
  {
    if (beg == end)
      return beg;
    I max (beg);  
    while (++beg != end)
      if (p(*max,*beg))
	max = beg;
    return max;
  }

  // classic sequential search
  template <class I, typename T>
  I g_find (I beg, I end, const T& t)
  {
    for ( ; beg != end; ++beg)
      if (t == *beg)
	return beg;
    return end;
  }

  template <class I, class P>
  I g_find_if (I beg, I end, const P& p)
  {
    for ( ; beg != end; ++beg)
      if (p(*beg))
	return beg;
    return end;
  }

  template <class I, class F>
  F g_for_each(I beg, I end, F f)
  {
    while (beg != end)
      f(*beg++);
    return f;
  }

  template < typename T >
  void Swap(T& t1, T& t2)
  {
    T temp(t1);
    t1 = t2;
    t2 = temp;
  }

} // namespace fsu

#endif
