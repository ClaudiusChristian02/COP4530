/*
    list_merge_sort.cpp
    10/19/2013
    Chris Lacher

    Implementation of List<T>::Sort() using the
    merge sort algorithm

    Copyright 2013, R. C. Lacher
*/

//----------------------------------
//     List<T>::Sort Implementations
//----------------------------------


template < typename T >
template < class P >
void List<T>::Sort (P& comp)
// merge sort: in place, stable, Theta(n log n)
{
  if (head_->next_ == tail_) return;         // empty list
  if (head_->next_ == tail_->prev_) return;  // only one element

  // size >= 2; at least one pass required
  // isolate list without head and tail nodes
  Link * first = head_->next_;
  first ->prev_ = 0;
  tail_->prev_->next_ = 0;

  // management variables
  Link   *p       // beginning of lead seqment in merge loop
    ,    *q       // beginning of follow segment in merge loop
    ,    *e       // contains element to be merged in merge loop
    ,    *last;   // last link in list
  size_t segsize  // theoretical max size of seqments in merge loop
    ,    psize    // calculated actual size of lead segment (q-p)
    ,    qsize    // calculated size of corresponding follow segment
    ,    nmerges; // number of merges in inner loop [number of lead segments]

  // start with segments of one element
  // double the size after each trip through the list
  segsize = 1;
  do  // merge all segment pairs
  {
    p = first;
    first = 0;
    last = 0;
    nmerges = 0;  // count number of segment pair merges we do in this pass 
    while (p)
    // merge one segment pair
    {
      ++nmerges;  // there exists a merge to be done
      //step `segsize' places along from p
      q = p;
      psize = 0;
      for (size_t i = 0; i < segsize; ++i)
      {
	++psize;
	q = q->next_;
	if (!q) break;
      }
      // note that we could have qsize == 0, case is taken care of in code below

      // now we have two lists; merge them
      qsize = segsize;
      while (psize > 0 || (qsize > 0 && q))
      {
	// identify next element to merge and increment pointer
	if (psize == 0)            // p is empty; e must come from q.
	{
	  e = q;
	  q = q->next_;
	  --qsize;
	}
	else if (qsize == 0 || !q) // q is empty; e must come from p. 
	{
	  e = p;
	  p = p->next_;
	  --psize;
	}
	else if (comp(q->Tval_, p->Tval_))  // q < p, e must come from q. 
	{
	  e = q;
	  q = q->next_;
	  --qsize;
	}
	else                                // p <= q, e must come from p. 
	{
	  e = p;
	  p = p->next_;
	  --psize;
	}
	// now add the identified element to the merged list 
	if (last)
	{
	  last->next_ = e;
	}
	else
	{
	  first = e;
	}
	// maintain reverse pointers and increment last
	e->prev_ = last; /* here */
	last = e;
      }
      // now p and q have incremented segsize places along (where possible)
      p = q;
    }
    // terminate the "new" last node; first is taken care of /* here */
    last->next_ = 0;

    if (nmerges <= 1) // the two segments constituted the entire list
    {
      // restore the head and tail structure
      last->next_ = tail_;
      tail_->prev_ = last;
      head_->next_ = first;
      first->prev_ = head_;
      break;
    }
    // Otherwise repeat, merging lists twice the size 
    segsize *= 2;
  } while(1);
}

template < typename T >
void List<T>::Sort ()
{
  if (head_->next_ == tail_) return;         // empty list
  if (head_->next_ == tail_->prev_) return;  // only one element

  // size >= 2; at least one pass required
  // isolate list without head and tail nodes
  Link * first = head_->next_;
  first ->prev_ = 0;
  tail_->prev_->next_ = 0;

  // management variables
  Link   *p       // beginning of lead seqment in merge loop
    ,    *q       // beginning of follow segment in merge loop
    ,    *e       // contains element to be merged in merge loop
    ,    *last;   // last link in list
  size_t segsize  // theoretical max size of seqments in merge loop
    ,    psize    // calculated actual size of lead segment (q-p)
    ,    qsize    // calculated size of corresponding follow segment
    ,    nmerges; // number of merges in inner loop [number of lead segments]

  // start with segments of one element
  // double the size after each trip through the list
  segsize = 1;
  do  // merge all segment pairs
  {
    p = first;
    first = 0;
    last = 0;
    nmerges = 0;  // count number of segment pair merges we do in this pass 
    while (p)     // merge one segment pair
    {
      ++nmerges;  // there exists a merge to be done
      //step `segsize' places along from p
      q = p;
      psize = 0;
      for (size_t i = 0; i < segsize; ++i)
      {
	++psize;
	q = q->next_;
	if (!q) break;
      }
      // note that we could have qsize == 0, case is taken care of in code below

      // now we have two lists; merge them
      qsize = segsize;
      while (psize > 0 || (qsize > 0 && q))
      {
	// identify next element to merge and increment pointer
	if (psize == 0)            // p is empty; e must come from q.
	{
	  e = q;
	  q = q->next_;
	  --qsize;
	}
	else if (qsize == 0 || !q) // q is empty; e must come from p. 
	{
	  e = p;
	  p = p->next_;
	  --psize;
	}
	else if (q->Tval_ < p->Tval_)  // q < p, e must come from q. 
	{
	  e = q;
	  q = q->next_;
	  --qsize;
	}
	else                                // p <= q, e must come from p. 
	{
	  e = p;
	  p = p->next_;
	  --psize;
	}
	// now add the identified element to the merged list 
	if (last)
	{
	  last->next_ = e;
	}
	else
	{
	  first = e;
	}
	// maintain reverse pointers and increment last
	e->prev_ = last; /* here */
	last = e;
      }
      // now p and q have incremented segsize places along (where possible)
      p = q;
    }
    // terminate the "new" last node; first is taken care of /* here */
    last->next_ = 0;

    if (nmerges <= 1) // the two segments constituted the entire list
    {
      // restore the head and tail structure
      last->next_ = tail_;
      tail_->prev_ = last;
      head_->next_ = first;
      first->prev_ = head_;
      break;
    }
    // Otherwise repeat, merging lists twice the size 
    segsize *= 2;
  } while(1);
}
