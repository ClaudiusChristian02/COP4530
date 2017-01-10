/*
    search_spy.cpp
    02/01/15
    Chris Lacher


    Copyright 2015, R.C. Lacher
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

// #include <vector.h>
#include <deque.h>
#include <list.h>
#include <insert.h>
#include <compare.h>
#include <compare_spy.h>
#include <gheap.h> // g_heap_sort
#include <gbsearch.h> // iterative implementations - fsu::
#include <gssearch.h> // iterative implementations - seq::
#include <rbsearch.h> // recursive implementations - alt::
#include <genalg.h>

typedef char ElementType;     const char* e_t = "char";     bool FIXED_WIDTH = 1;
// typedef uint32_t ElementType; const char* e_t = "uint32_t"; bool FIXED_WIDTH = 0;

const int c1 = 20, c2 = 12, c3 = 7, c4 = 10, c5 = 9, c6 = 8; // column widths
int main(int argc, char* argv[])
{
  bool BATCH = 0;
  if (argc > 1) BATCH = 1;

  if (argc > 1 && '?' == argv[1][0])
  {
    std::cout << " ** Possible command line arguments:\n"
              << "      argv[1] = \'?\' (? in single quotes)         : help\n"
              << "      argv[1] = command_file                     : processed in batch mode\n"
              << "      argv[1] = command_file, argv[2] = \"silent\" : processed in batch silent mode\n";
    std::cout << " ** Current ElementType < " << e_t << " >\n"
              << "      re-build to change element types\n";
    return EXIT_SUCCESS;
  }

  std::istream* isptr = &std::cin;
  std::ifstream ifs;
  if (BATCH)
  {
    ifs.open(argv[1]);
    if (ifs.fail())
    {
      std::cout << " ** Error: cannot open file " << argv[1] << '\n';
      return 0;
    }
    isptr = &ifs;
  }

  bool VERBOSE = 1;
  if (argc > 2) VERBOSE = 0;

  typedef fsu::LessThan <ElementType>       PredicateType1;
  typedef fsu::LessThanSpy <ElementType>    PredicateType2;

  PredicateType1              ltNormal;
  PredicateType2              ltfsuLB, ltfsuUB, ltaltLB, ltaltUB, ltseqLB, ltseqUB; // comp spys
  fsu::Deque  < ElementType > deque;  // a deque
  fsu::Deque  < ElementType > ::Iterator dequeItr, dequeLoc;
  fsu::List   < ElementType > list;  // a list
  fsu::List   < ElementType > ::Iterator listItr, listLoc;
  fsu::PushBackIterator < fsu::List < ElementType > > listBackPusher(list);

  ElementType e, s; // entry, sentinel

  std::cout << "\nWelcome search_spy < " << e_t << " >\n"
            << "For help, execute with argument \'?\'\n\n";
    if (VERBOSE && !BATCH)
      std::cout << "  You will enter elements for storage into a Deque D. These will be\n"
		<< "  copied to a List L and sorted. Then the program enters an interactive phase\n"
		<< "  where you will be prompted to enter search values. The sentinel value\n"
		<< "  will be used to terminate your original input and to end the program.\n\n";
    if (VERBOSE) std::cout << "Enter sentinel: ";
  *isptr >> s;
  if (VERBOSE && BATCH) std::cout << s << '\n';
  if (VERBOSE)          std::cout << "Enter elements ('" << s << "' to end): ";
  *isptr >> e;
  while (e != s)
  {
    if (VERBOSE && BATCH) std::cout << e;
    deque.PushBack(e);
    *isptr >> e;
  }
  if (VERBOSE && BATCH) std::cout << e << '\n';

  if (VERBOSE && FIXED_WIDTH) std::cout << "D as entered:                " << deque << '\n';
  fsu::g_copy(deque.Begin(), deque.End(), listBackPusher);
  if (VERBOSE && FIXED_WIDTH) std::cout << "L as entered:                " << list << '\n';

  // sort both containers
  fsu::g_heap_sort(deque.Begin(), deque.End(), ltNormal);
  if (VERBOSE && FIXED_WIDTH) std::cout << "g_heap_sort(<):              " << deque << '\n';
  list.Sort(ltNormal);
  if (VERBOSE && FIXED_WIDTH) std::cout << "List::Sort(<):               " << list << '\n';
  else std::cout << "search space loaded\n";

  if (deque.Size() == 0)
  {
    std::cout << " ** no data entered - exiting search_spy\n";
    return (EXIT_SUCCESS);
  }

  // now do binary and sequential search
  ltfsuLB.Reset();
  ltfsuUB.Reset();
  ltaltLB.Reset();
  ltaltUB.Reset();
  ltseqLB.Reset();
  ltseqUB.Reset();
  size_t searchcount = 0;
  size_t ltfsuLB_max = 0,
         ltfsuUB_max = 0,
         ltaltLB_max = 0,
         ltaltUB_max = 0,
         ltseqLB_max = 0,
         ltseqUB_max = 0;
  size_t ltfsuLB_min = 0xFFFFFFFFFFFFFFFF,
         ltfsuUB_min = 0xFFFFFFFFFFFFFFFF,
         ltaltLB_min = 0xFFFFFFFFFFFFFFFF,
         ltaltUB_min = 0xFFFFFFFFFFFFFFFF,
         ltseqLB_min = 0xFFFFFFFFFFFFFFFF,
         ltseqUB_min = 0xFFFFFFFFFFFFFFFF;
  size_t before, after;

  while(1)
  {
    if (VERBOSE) std::cout << "Enter search value ('" << s << "' to quit): ";
    *isptr >> e;
    if (VERBOSE && BATCH) std::cout << e << '\n';
    if (e == s) break;
    ++searchcount;

    // fsu::g_lower_bound
    if (VERBOSE) std::cout << " fsu::g_lower_bound on Deque";
    before = ltfsuLB.Count();
    dequeLoc = fsu::g_lower_bound(deque.Begin(), deque.End(), e, ltfsuLB);
    after  = ltfsuLB.Count();
    if ((after - before) < ltfsuLB_min) ltfsuLB_min = after - before;
    if ((after - before) > ltfsuLB_max) ltfsuLB_max = after - before;
    if (VERBOSE)
    {
      if (FIXED_WIDTH) // display graphic
      {
        std::cout << '\n';
        std::cout << "  D = " << deque << '\n';
        std::cout << "      ";
        for (dequeItr = deque.Begin(); dequeItr != dequeLoc; ++dequeItr) std::cout << ' ';
        std::cout << "^lb\n";
      }
      else // display value only
      {
        if (dequeLoc != deque.End())
          std::cout << " *dequeLoc = " << *dequeLoc << '\n';
        else
          std::cout << "  dequeLoc = deque.End()\n";
      }
    }


    // fsu::g_upper_bound 
    if (VERBOSE) std::cout << " fsu::g_upper_bound on Deque";
    before = ltfsuUB.Count();
    dequeLoc = fsu::g_upper_bound(deque.Begin(), deque.End(), e, ltfsuUB);
    after  = ltfsuUB.Count();
    if ((after - before) < ltfsuUB_min) ltfsuUB_min = after - before;
    if ((after - before) > ltfsuUB_max) ltfsuUB_max = after - before;
    if (VERBOSE)
    {
      if (FIXED_WIDTH) // display graphic
      {
        std::cout << '\n';
        std::cout << "  D = " << deque << '\n';
        std::cout << "      ";
        for (dequeItr = deque.Begin(); dequeItr != dequeLoc; ++dequeItr) std::cout << ' ';
        std::cout << "^ub\n";
      }
      else // display value only
      {
        if (dequeLoc != deque.End())
          std::cout << " *dequeLoc = " << *dequeLoc << '\n';
        else
          std::cout << "  dequeLoc = deque.End()\n";
      }
    }

    // alt::g_lower_bound
    if (VERBOSE) std::cout << " alt::g_lower_bound on Deque";
    before = ltaltLB.Count();
    dequeLoc = alt::g_lower_bound(deque.Begin(), deque.End(), e, ltaltLB);
    after  = ltaltLB.Count();
    if ((after - before) < ltaltLB_min) ltaltLB_min = after - before;
    if ((after - before) > ltaltLB_max) ltaltLB_max = after - before;
    if (VERBOSE)
    {
      if (FIXED_WIDTH) // display graphic
      {
        std::cout << '\n';
        std::cout << "  D = " << deque << '\n';
        std::cout << "      ";
        for (dequeItr = deque.Begin(); dequeItr != dequeLoc; ++dequeItr) std::cout << ' ';
        std::cout << "^lb\n";
      }
      else // display value only
      {
        if (dequeLoc != deque.End())
          std::cout << " *dequeLoc = " << *dequeLoc << '\n';
        else
          std::cout << "  dequeLoc = deque.End()\n";
      }
    }

    // g_upper_bound 
    if (VERBOSE) std::cout << " alt::g_upper_bound on Deque";
    before = ltaltUB.Count();
    dequeLoc = alt::g_upper_bound(deque.Begin(), deque.End(), e, ltaltUB);
    after  = ltaltUB.Count();
    if ((after - before) < ltaltUB_min) ltaltUB_min = after - before;
    if ((after - before) > ltaltUB_max) ltaltUB_max = after - before;
    if (VERBOSE)
    {
      if (FIXED_WIDTH) // display graphic
      {
        std::cout << '\n';
        std::cout << "  D = " << deque << '\n';
        std::cout << "      ";
        for (dequeItr = deque.Begin(); dequeItr != dequeLoc; ++dequeItr) std::cout << ' ';
        std::cout << "^ub\n";
      }
      else // display value only
      {
        if (dequeLoc != deque.End())
          std::cout << " *dequeLoc = " << *dequeLoc << '\n';
        else
          std::cout << "  dequeLoc = deque.End()\n";
      }
    }

    // seq 
    if (VERBOSE) std::cout << " seq::g_lower_bound on List";
    before = ltseqLB.Count();
    listLoc = seq::g_lower_bound(list.Begin(), list.End(), e, ltseqLB);
    after  = ltseqLB.Count();
    if ((after - before) < ltseqLB_min) ltseqLB_min = after - before;
    if ((after - before) > ltseqLB_max) ltseqLB_max = after - before;
    if (VERBOSE)
    {
      if (FIXED_WIDTH) // display graphic
      {
        std::cout << '\n';
        std::cout << "  L = " << list << '\n';
        std::cout << "      ";
        for (listItr = list.Begin(); listItr != listLoc; ++listItr) std::cout << ' ';
        std::cout << "^lb\n";
      }
      else // display value only
      {
        if (listLoc != list.End())
          std::cout << "  *listLoc  = " << *listLoc << '\n';
        else
          std::cout << "   listLoc  = list.End()\n";
      }
    }

    // seq 
    if (VERBOSE) std::cout << " seq::g_upper_bound on List";
    before = ltseqUB.Count();
    listLoc = seq::g_upper_bound(list.Begin(), list.End(), e, ltseqUB);
    after  = ltseqUB.Count();
    if ((after - before) < ltseqUB_min) ltseqUB_min = after - before;
    if ((after - before) > ltseqUB_max) ltseqUB_max = after - before;
    if (VERBOSE)
    {
      if (FIXED_WIDTH) // display graphic
      {
        std::cout << '\n';
        std::cout << "  L = " << list << '\n';
        std::cout << "      ";
        for (listItr = list.Begin(); listItr != listLoc; ++listItr) std::cout << ' ';
        std::cout << "^ub\n";
      }
      else // display value only
      {
        if (listLoc != list.End())
          std::cout << "  *listLoc  = " << *listLoc << '\n';
        else
          std::cout << "   listLoc  = list.End()\n";
      }
    }

  } // end while

  /* // verify correct calls being made
  ltfsuLB(e,e);
  ltfsuUB(e,e);

  std::cout << "ltfsuLB.Count() = "  << ltfsuLB.Count() << '\n'
            << "ltfsuUB.Count() = "  << ltfsuUB.Count() << '\n'
            << "ltaltLB.Count() = "  << ltaltLB.Count() << '\n'
            << "ltaltUB.Count() = "  << ltaltUB.Count() << '\n'
            << "ltseqLB.Count() = "  << ltseqLB.Count() << '\n'
            << "ltseqUB.Count() = "  << ltseqUB.Count() << '\n' << '\n';
  // */

  std::cout << std::fixed << std::setprecision(2) << std::showpoint;

  std::cout << std::setw(c1) << "algorithm"
            << std::setw(c2) << "min comps"
            << std::setw(c2) << "avg comps"
            << std::setw(c2) << "max comps"
            << std::setw(c3) << "size" 
            << std::setw(c4) << "log size" 
            << std::setw(c5) << "[ceiling]"
            << std::setw(c6) << "trials"
            << '\n'
            << std::setw(c1) << "---------" 
            << std::setw(c2) << "---------"
            << std::setw(c2) << "---------"
            << std::setw(c2) << "---------"
            << std::setw(c3) << "----"
            << std::setw(c4) << "--------"
            << std::setw(c5+c6) << "------"
            << '\n';

  if (searchcount == 0)
  {
    std::cout << " ** no searches performed - exiting search_spy\n";
    return (EXIT_SUCCESS);
  }

  std::cout << std::setw(c1) << "fsu::g_lower_bound" 
            << std::setw(c2) << ltfsuLB_min
            << std::setw(c2) << ((double)ltfsuLB.Count()) / searchcount
            << std::setw(c2) << ltfsuLB_max
            << std::setw(c3) << deque.Size() 
            << std::setw(c4) << (size_t)ceil(log2(deque.Size()))
            << std::setw(c5+c6) << searchcount
            << '\n';

  std::cout << std::setw(c1) << "fsu::g_upper_bound"
            << std::setw(c2) << ltfsuUB_min
            << std::setw(c2) << ((double)ltfsuUB.Count()) / searchcount
            << std::setw(c2) << ltfsuUB_max
            << std::setw(c3) << deque.Size()
            << std::setw(c4) << (size_t)ceil(log2(deque.Size()))
            << std::setw(c5+c6) << searchcount
            << '\n';

  std::cout << std::setw(c1) << "alt::g_lower_bound" 
            << std::setw(c2) << ltaltLB_min
            << std::setw(c2) << ((double)ltaltLB.Count()) / searchcount
            << std::setw(c2) << ltaltLB_max
            << std::setw(c3) << deque.Size()
            << std::setw(c4) << (size_t)ceil(log2(deque.Size()))
            << std::setw(c5+c6) << searchcount
            << '\n';

  std::cout << std::setw(c1) << "alt::g_upper_bound"
            << std::setw(c2) << ltaltUB_min
            << std::setw(c2) << ((double)ltaltUB.Count()) / searchcount
            << std::setw(c2) << ltaltUB_max
            << std::setw(c3) << deque.Size() 
            << std::setw(c4) << (size_t)ceil(log2(deque.Size()))
            << std::setw(c5+c6) << searchcount
            << '\n';

  std::cout << std::setw(c1) << "seq::g_lower_bound"
            << std::setw(c2) << ltseqLB_min
            << std::setw(c2) << ((double)ltseqLB.Count()) / searchcount
            << std::setw(c2) << ltseqLB_max
            << std::setw(c3) << list.Size() << std::setw(c4) << (size_t)ceil(log2(list.Size()))
            << std::setw(c5+c6) << searchcount
            << '\n';

  std::cout << std::setw(c1) << "seq::g_upper_bound"
            << std::setw(c2) << ltseqUB_min
            << std::setw(c2) << ((double)ltseqUB.Count()) / searchcount
            << std::setw(c2) << ltseqUB_max
            << std::setw(c3) << list.Size() << std::setw(c4) << (size_t)ceil(log2(list.Size()))
            << std::setw(c5+c6) << searchcount
            << '\n';

  std::cout << "\nEnd search_spy\n";
  return 0;
}
