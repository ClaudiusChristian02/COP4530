/*
    moaa.cpp
    03/10/15
    Chris Lacher


    Dynamic Random Test of OAA<String, int>

    Driver program testing OAA<T> for pointer errors and memory
    leaks by fully exercising all OAA<T> functions randomly in an unending loop.

    IMPORTANT INSTRUCTIONS FOR USE: 
    ==============================

    Running this program using a faulty implementation of OAA can take over a
    machine and virtually shut it down, preventing all other processes from
    running, including those of other users. It is therefore REQUIRED that this
    program be executed ONLY using the following procedures:

    1. Create a login to one of the programming machines (program or linprog)
    2. Compile using your command line compile script
    3. Limit your memory use by entering
       "limit vmemoryuse 50000"
    4. Check that your limits have been set by entering
       "limit"
    5. Run by entering the executable name
    6. Execution should terminate when memory is used up
    7. After a run, remove your vmememoryuse restriction by entering
       "limit vmemoryuse unlimited"

    With vmemoryuse limited to 4000, you don't have enough space to run emacs
    or a compiler. 

    NOTE: Students not following this procedure and resulting in bogging down a
    machine will be responsible for the consequences, including possible
    suspension of your CS account, which could affect your performance in this
    and other courses. 

    Copyright 2015, R.C. Lacher
*/

#include <iostream>
#include <iomanip>
#include <oaa.h>
#include <cmath>

// choose one from group A 

// =====================
// ===== group A =======
// =====================

// <String, int>
#include <xran.h>
#include <xranxstr.h>
#include <xstring.cpp>  // in lieu of makefile
#include <xran.cpp>     // in lieu of makefile
#include <xranxstr.cpp> // in lieu of makefile

typedef fsu::String KeyType;
typedef int         DataType;

typedef fsu::Random_String Random_class;
const char* vT = "String , int";
const long unsigned int maxSize        =     4000;
const long unsigned int maxNodes       =     5000;
const      size_t       stringLength   =        5;
const long unsigned int reportInterval =    10000;
const      unsigned int getPercent  =       50;    // to control
const      unsigned int putPercent  =       50;    // growth rate
const      unsigned int assignPercent  =    30;    // and volatility
// */

// constants for number of containers and operations
const unsigned int numObj = 3;  // containers x0, x1, x2
const unsigned int numOps = 4; // operations 0..3

template < typename T , class P >
void WriteReport(fsu::OAA<T,P> x, char n, unsigned long numreports);

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << " ** Argument required:  number of reports (enter 0 for unlimited)\n"
              << "    Try again\n";
    return 0;
  }
  size_t maxrpts = atoi(argv[1]);

  // objects
  fsu::OAA<KeyType,DataType> x0, x1, x2;
  Random_class   ranobj;
  DataType       data;
  KeyType        key;

  // controls
  fsu::Random_int ranint;
  unsigned long numtrials(0);
  unsigned long numrpts(0); 
  unsigned int option;
  size_t size;

  std::cout << "\nStarting dynamic random test of OAA < " << vT << " >"
            << "\n\n" << std::flush;
  while(1)
  {
    option = ranint(0,numObj);
    switch(option)
    {
      case 0:
        option = ranint(0,numOps); 
        switch (option)
        {
          case 0:   // Put (k,d)
            option = ranint(0,100);
            if (option < putPercent)
            {
              data = ranint(1,11);
              key = ranobj(data);
              x0.Put(key,data);
            }
            break;
        
          case 1:   // void Get (k)
            option = ranint(0,100);
            if (option < getPercent)
            {
              data = ranint(1,11);
              key = ranobj(data);
              x0.Get(key);
            }
            break;
        
          case 2:   // void Size()
            size = x0.Size();
            if (size >= maxSize)
            {
              x0.Clear();
              std::cout << " ** x0 cleared at size = " << size << std::endl;
            }
            break;

          case  3:  // assignment
            option = ranint(0,100);
            if (option < assignPercent)
            {
              option = ranint(0,numObj);
              switch(option)
              {
              case 0:
                x0 = x0;
                break;
              case 1:
                x0 = x1;
                break;
              case 2:
                x0 = x2;
                break;
              }
            }
            break;

          default: std::cout << " ** bad operation number\n";


        }   // end switch() x0 operations

      case 1:
        option = ranint(0,numOps); 
        switch (option)
        {
          case 0:   // Put (k,d)
            option = ranint(0,100);
            if (option < putPercent)
            {
              data = ranint(1,11);
              key = ranobj(data);
              x0.Put(key,data);
            }
            break;
        
          case 1:   // void Get (k)
            option = ranint(0,100);
            if (option < getPercent)
            {
              data = ranint(1,11);
              key = ranobj(data);
              x0.Get(key);
            }
            break;
        
          case 2:   // void Size()
            size = x1.Size();
            if (size >= maxSize)
            {
              x1.Clear();
              std::cout << " ** x1 cleared at size = " << size << std::endl;
            }
            break;

          case  3:  // assignment
            option = ranint(0,100);
            if (option < assignPercent)
            {
              option = ranint(0,numObj);
              switch(option)
              {
              case 0:
                x1 = x0;
                break;
              case 1:
                x1 = x1;
                break;
              case 2:
                x1 = x2;
                break;
              }
            }
            break;

          default: std::cout << " ** bad operation number\n";

        }   // end switch() x1 operations

      case 2:
        option = ranint(0,numOps); 
        switch (option)
        {
          case 0:   // Put (k,d)
            option = ranint(0,100);
            if (option < putPercent)
            {
              data = ranint(1,11);
              key = ranobj(data);
              x0.Put(key,data);
            }
            break;
        
          case 1:   // void Get (k)
            option = ranint(0,100);
            if (option < getPercent)
            {
              data = ranint(1,11);
              key = ranobj(data);
              x0.Get(key);
            }
            break;
        
          case 2:   // void Size()
            size = x2.Size();
            if (size >= maxSize)
            {
              x2.Clear();
              std::cout << " ** x2 cleared at size = " << size << std::endl;
            }
            break;

          case  3:  // assignment
            option = ranint(0,100);
            if (option < assignPercent)
            {
              option = ranint(0,numObj);
              switch(option)
              {
              case 0:
                x2 = x0;
                break;
              case 1:
                x2 = x1;
                break;
              case 2:
                x2 = x2;
                break;
              }
            }
            break;

          default: std::cout << " ** bad operation number\n";

        }   // end switch() x2 operations

    } // end switch() case x2

    ++numtrials;
    if (numtrials == reportInterval)
    {
      ++numrpts;
      numtrials = 0;
      option = ranint(0,3);
      switch(option)
      {
      case 0: WriteReport(x0,'0',numrpts); break;
      case 1: WriteReport(x1,'1',numrpts); break;
      case 2: WriteReport(x2,'2',numrpts); break;
      }
      if (numrpts == maxrpts)
      {
        std::cout << "\nTest Complete\n";
        break;
      }
    }
  }  // end while()
  return EXIT_SUCCESS;
}  // end main()

template < typename T , class P >
void WriteReport(fsu::OAA<T,P> x, char n, unsigned long numrpts)
{
  size_t size = x.Size();
  std::cout << std::showpoint << std::fixed << std::setprecision(2);
  std::cout << "\nTesting OAA < " << vT << " >"
            << " at trial " << numrpts << " x " << reportInterval << ":\n"
            << "  x" << n << ".Size()              ==  " << size << '\n' 
            << "  x" << n << ".Height()            ==  " << x.Height() << '\n'
            << "  optimal ht (size)      ==  " << (size_t)(floor(log2(size))) << std::endl;
}
