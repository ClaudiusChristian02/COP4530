/*
   sort_spy.cpp
   Chris Lacher
   03/30/14

   (covers fsu::heapsort, alt::heapsort, and cormen::heapsort)

   takes two arguments: input and output file names

   processes as follows: 

     reads data from input file
     for each sort:
       sorts data
       collects comp_count data for comparison sorts
       writes comp_count data to output file (and screen)

   Comp_count data is collected using a "spy" less-than predicate object that
   counts the number of times it is called.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdint>
#include <cmath>
#include <climits>
#include <vector.h>
#include <genalg.h>
#include <gheap.h>
// #include <gheap_basic.h>
// #include <gheap_advanced.h>
// #include <gheap_cormen.h>
#include <gsort.h>
#include <list.h>
#include <insert.h>
#include <compare_spy.h>
#include <compare.h>

const int c1 = 20, c2 = 8, c3 = 15, c4 = 10, c5 = 10, c6 = 12; // column widths

typedef uint32_t ElementType;

template < class I , class P >
size_t CheckOrder (I beg, I end, P& p)
{
  // if range has 0 or 1 element, order is ok
  if (beg == end) return 0;
  I i = beg;
  I j = i++;
  if (i == end) return 0;

  size_t position = 0;
  size_t count = 0;
  while (i != end)
  {
    if (p(*i,*j))
    {
      // std::cerr << " ** order discrepancy at c[" << position << "] = " << *i << '\n';
      ++count;
    }
    ++ position;
    j = i++;
  }
  return count;
}

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cout << " ** required arguments:\n"
	      << "     1: input filename\n"
	      << "     2: output filename\n"
	      << " ** try again\n";
    return 0;
  }

  char* infile      = argv[1];
  char* outfile     = argv[2];
  fsu::LessThanSpy < ElementType > lts;
  fsu::LessThan    < ElementType > lt;
  // fsu::GreaterThanSpy < ElementType > lts;
  // fsu::GreaterThan    < ElementType > lt;
  std::ifstream in1(infile);
  if (in1.fail())
  {
    std::cout << " ** cannot open file " << infile << " for read\n"
	      << " ** try again\n";
    return 0;
  }

  std::ofstream out1(outfile);
  if (out1.fail())
  {
    std::cout << " ** cannot open file " << outfile << " for write\n"
	      << " ** try again\n";
    return 0;
  }

  fsu::Vector < ElementType >   dataStore;
  fsu::List   < ElementType >   dataList;
  fsu::PushBackIterator < fsu::List < ElementType > > listBackPusher(dataList);
  size_t error_count = 0;

  ElementType item;
  while (in1 >> item)
    dataStore.PushBack(item);
  in1.clear();
  in1.close();
  if (dataStore.Size() > UINT_MAX)
  {
    std::cout << " ** WARNING: too many items, keep count <= " << UINT_MAX << '\n';
  }
  size_t size = dataStore.Size();
  size_t sizesize = size * (size + 1) >> 1;
  // double sizelogsize = size * log2(size);
  size_t sizelogsize = size * log2(size);

  // this is where we will run the sorts:
  ElementType * data = new ElementType [size];

  std::cout << "\n -"
	    << infile
	    << "----------------------------------------------\n\n"
	    << " Input file name: " << infile << '\n'
	    << "            size: " << size << '\n'
            << '\n'
            << std::setw(c1) << "algorithm" << std::setw(c2) << "errors" << std::setw(c3) << "comp_count" 
            << std::setw(c4) << "  n" << std::setw(c5) << "n lg n" << std::setw(c6) << "n(n+1)/2"
            << '\n'
            << std::setw(c1) << "---------" << std::setw(c2) << "------" << std::setw(c3) << "----------"
            << std::setw(c4) << "---" << std::setw(c5) << "------" << std::setw(c6) << "--------" 
            << '\n';

  out1      << " \n-"
	    << infile
	    << "----------------------------------------------\n\n"
	    << " Input file name: " << infile << '\n'
	    << "            size: " << size << '\n'
            << '\n'
            << std::setw(c1) << "algorithm" << std::setw(c2) << "errors" << std::setw(c3) << "comp_count" 
            << '\n'
            << std::setw(c1) << "---------" << std::setw(c2) << "------" << std::setw(c3) << "----------"
            << '\n';

  // std::cout << std::fixed << std::setprecision(2) << std::showpoint;

  // selection sort
  fsu::g_copy (dataStore.Begin(), dataStore.End(), data);
  lts.Reset();
  fsu::g_selection_sort(data , data + size, lts);
  error_count = 0;
  error_count = CheckOrder(data,data+size,lt);
  std::cout << std::setw(c1) << "g_selection_sort";
  std::cout << std::setw(c2) << error_count;
  std::cout << std::setw(c3) << lts.Count();
  std::cout << std::setw(c4) << size  << std::setw(c5) << sizelogsize  << std::setw(c6) << sizesize
            << '\n';
  out1 << std::setw(c1) << "g_selection_sort"
       << std::setw(c2) << error_count
       << std::setw(c3) << lts.Count()
       << '\n';
  // */

  // insertion sort on arrays
  fsu::g_copy (dataStore.Begin(), dataStore.End(), data);
  lts.Reset();
  fsu::g_insertion_sort(data , data + size, lts);
  error_count = 0;
  error_count = CheckOrder(data,data+size,lt);
  std::cout << std::setw(c1) << "g_insertion_sort";
  std::cout << std::setw(c2) << error_count;
  std::cout << std::setw(c3) << lts.Count();
  std::cout << std::setw(c4) << size  << std::setw(c5) << sizelogsize  << std::setw(c6) << sizesize
            << '\n';
  out1 << std::setw(c1) << "g_insertion_sort"
       << std::setw(c2) << error_count
       << std::setw(c3) << lts.Count()
       << '\n';
  // */

  // alt::heap sort: n log n + n log n
  fsu::g_copy (dataStore.Begin(), dataStore.End(), data);
  lts.Reset();
  error_count = 0;
  alt::g_heap_sort(data , data + size, lts);
  error_count = 0;
  error_count = CheckOrder(data,data+size,lt);
  std::cout << std::setw(c1) << "alt::g_heap_sort";
  std::cout << std::setw(c2) << error_count;
  std::cout << std::setw(c3) << lts.Count();
  std::cout << std::setw(c4) << size  << std::setw(c5) << sizelogsize  << std::setw(c6) << sizesize
            << '\n';
  out1 << std::setw(c1) << "alt::g_heap_sort"
       << std::setw(c2) << error_count
       << std::setw(c3) << lts.Count()
       << '\n';
  // */

  // fsu::heap sort: n + n log n
  fsu::g_copy (dataStore.Begin(), dataStore.End(), data);
  lts.Reset();
  fsu::g_heap_sort(data , data + size, lts);
  error_count = 0;
  error_count = CheckOrder(data,data+size,lt);
  std::cout << std::setw(c1) << "fsu::g_heap_sort";
  std::cout << std::setw(c2) << error_count;
  std::cout << std::setw(c3) << lts.Count();
  std::cout << std::setw(c4) << size  << std::setw(c5) << sizelogsize  << std::setw(c6) << sizesize
            << '\n';
  out1 << std::setw(c1) << "fsu::g_heap_sort"
       << std::setw(c2) << error_count
       << std::setw(c3) << lts.Count()
       << '\n';
  // */

  /* // cormen::heap sort: recursive
  fsu::g_copy (dataStore.Begin(), dataStore.End(), data);
  lts.Reset();
  cormen::g_heap_sort(data , data + size, lts);
  error_count = 0;
  error_count = CheckOrder(data,data+size,lt);
  std::cout << std::setw(c1) << "cormen::g_heap_sort";
  std::cout << std::setw(c2) << error_count;
  std::cout << std::setw(c3) << lts.Count();
  std::cout << std::setw(c4) << size  << std::setw(c5) << sizelogsize  << std::setw(c6) << sizesize
            << '\n';
  out1 << std::setw(c1) << "cormen::g_heap_sort"
       << std::setw(c2) << error_count
       << std::setw(c3) << lts.Count()
       << '\n';
  // */

  /* // quick sort
  fsu::g_copy (dataStore.Begin(), dataStore.End(), data);
  lts.Reset();
  fsu::g_quick_sort(data , data + size, lts);
  error_count = 0;
  error_count = CheckOrder(data,data+size,lt);
  std::cout << std::setw(c1) << "g_quick_sort";
  std::cout << std::setw(c2) << error_count;
  std::cout << std::setw(c3) << lts.Count();
  std::cout << std::setw(c4) << size  << std::setw(c5) << sizelogsize  << std::setw(c6) << sizesize
            << '\n';
  out1 << std::setw(c1) << "g_quick_sort"
       << std::setw(c2) << error_count
       << std::setw(c3) << lts.Count()
       << '\n';
  // */

  /* // merge sort
  fsu::g_copy (dataStore.Begin(), dataStore.End(), data);
  lts.Reset();
  fsu::g_merge_sort(data , data + size, lts);
  error_count = 0;
  error_count = CheckOrder(data,data+size,lt);
  std::cout << std::setw(c1) << "g_merge_sort";
  std::cout << std::setw(c2) << error_count;
  std::cout << std::setw(c3) << lts.Count();
  std::cout << std::setw(c4) << size  << std::setw(c5) << sizelogsize  << std::setw(c6) << sizesize
            << '\n';
  out1 << std::setw(c1) << "g_merge_sort"
       << std::setw(c2) << error_count
       << std::setw(c3) << lts.Count()
       << '\n';
  // */

  // List::Sort member function
  fsu::g_copy (dataStore.Begin(), dataStore.End(), listBackPusher);
  lts.Reset();
  dataList.Sort(lts);
  error_count = 0;
  error_count = CheckOrder(dataList.Begin(), dataList.End(), lt);
  std::cout << std::setw(c1) << "List::Sort";
  std::cout << std::setw(c2) << error_count;
  std::cout << std::setw(c3) << lts.Count();
  std::cout << std::setw(c4) << size  << std::setw(c5) << sizelogsize  << std::setw(c6) << sizesize
            << '\n';
  out1 << std::setw(c1) << "List::Sort"
       << std::setw(c2) << error_count
       << std::setw(c3) << lts.Count()
       << '\n';
  // */

  delete [] data;
  std::cout << '\n' << " Process complete\n\n";
  return 0;
}
