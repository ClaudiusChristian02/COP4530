/*
    flist.cpp
    02/10/14
    Chris Lacher

    general test harness for fsu::List
    accepts two optional command line arguments:

      1: command file
      2: UI output file

    Any command line argument puts test in BATCH mode, where commands from a
    command file are duplexed to the UI. If there is only one argument, commands
    are duplexed to screen in RED. If there are two, commands are duplexed (to
    the UI output file) without color.

    Copyright 2014, R.C. Lacher
*/

#include <iostream>
#include <fstream>
#include <cctype>  // tolower()
#include <cmath>   // log2() called in some versions of List
#include <list.h>
#include <compare.h>
#include <xstring.h>
#include <xstring.cpp> // avoid separate build
#include <ansicodes.h> // color response in batch mode

// choose one from group A 

// =====================
// ===== group A =======
// =====================

// A1: makes lists of char
typedef char  ElementType;
const char ofc = '\0';
const char* vT = "char";
const char code0 = 'c';
const char code1 = '1';
// end A1 */

/* // A2: makes lists of CHAR
#include <CHAR.h>
typedef CHAR  ElementType;
const char ofc = '\0';
const char* vT = "char";
const char code0 = 'c';
const char code1 = '1';
// end A2 */

/* // A3: makes lists of String
#include <xstring.h>
#include <xstring.cpp> // in lieu of makefile
typedef fsu::String  ElementType;
const char ofc = ' ';
const char* vT = "String";
const char code0 = 's';
const char code1 = '1';
// end A3 */

/* // A4: makes lists of long
typedef long ElementType;
const char ofc = ' ';
const char* vT = "int";
const char code0 = 'i';
const char code1 = '1';
// end A4 */

typedef fsu::List < ElementType >       ContainerType;
typedef fsu::GreaterThan< ElementType > PredicateType;

void Preamble(std::ostream& os = std::cout);
void DisplayContainerType(const char code0, const char code1 = '1', std::ostream& os = std::cout);
void DisplayMenu(std::ostream& os = std::cout);
void DisplayPrompt(std::ostream& os = std::cout);

template < class C >
void CopyTest( C x , std::ostream& os)
{
  os << "CopyTest:\n";
  os << "Copied object size: " << x.Size() << '\n'
            << "              dump: ";
  x.Dump(os, ofc);
  os << '\n';
}

template < class C >
void AssignTest(const C& x , std::ostream& os)
{
  C x1;
  x1 = x;
  os << "AssignTest:\n";
  os << "Original object size: " << x.Size() << '\n'
            << "                dump: ";
  x.Dump(os, ofc);
  os << "Assignee object size: " << x1.Size() << '\n'
            << "                dump: ";
  x1.Dump(os, ofc);
  os << '\n';
}

template < class C >
void StructureTest(const C& x , std::ostream& os)
{
  x.CheckLinks(os);
}

void SkipDoc (std::istream& is)
{
  char ch = is.peek();
  while (ch == '#')
  {
    do ch = is.get();
    while (ch != '\n');
    ch = is.peek();
  }
}

int main( int argc, char* argv[] )
{
  bool BATCH = 0;
  bool COLOR = 1;
  if (argc > 1) BATCH = 1; // duplex commands to screen in color
  if (argc > 2) COLOR = 0; // duplex commands to file not in color

  // used to load data from a file
  fsu::String   datafile; // used to I/O data from a file with a PushBack loop
  std::ifstream dataistream; // read data
  std::ofstream dataostream; // write data

  // set up for command file / batch mode
  std::istream* isptr = &std::cin; // command input
  std::ifstream ifs;
  if (BATCH)
  {
    ifs.open(argv[1]);
    if (ifs.fail())
    {
      std::cerr << " ** Error: cannot open file " << argv[1] << '\n';
      return 0;
    }
    isptr = &ifs;
  }

  // set up for sending ui output to file
  std::ostream* osptr = &std::cout; // ui output
  std::ofstream ofs;  // ui output
  if (!COLOR)
  {
    ofs.open(argv[2]);
    if (ofs.fail())
    {
      std::cerr << " ** Error: cannot open file " << argv[2] << '\n';
      return 0;
    }
    osptr = &ofs;
  }

  if (!BATCH) Preamble(*osptr);
  if (!BATCH) DisplayMenu(*osptr);
  ContainerType x1, x2, x3;
  ContainerType::Iterator i0, i1, i2, i3;
  ContainerType::ConstIterator ci;
  PredicateType pred;
  ElementType  Tval;
  char option;
  if (BATCH) SkipDoc(*isptr);
  do
  {
    DisplayPrompt(*osptr);
    *isptr >> option;
    if (BATCH)
    {
      if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL;
      else *osptr << option;;
    }
    switch (option)
    {
      case '1': 
        *isptr >> option;
        if (BATCH)
        {
          if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL;
          else *osptr << option;;
        }
        switch (option)
        {
          case '$':
            if (BATCH) *osptr << '\n';
            *osptr << "  x1.CheckLinks()\n";
            StructureTest(x1,*osptr);
            break;
          case '1':   // void PushFront (T)
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  x1.PushFront(" 
		      << Tval
		      << ")\n";
	    x1.PushFront(Tval);
            break;
        
          case '2':   // void PushBack (T)
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  x1.PushBack(" 
		      << Tval
		      << ")\n";
	    x1.PushBack(Tval);
            break;
        
          case '3':   // void Insert (t)
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  x1.Insert(" 
		      << Tval
		      << ")\n";
	    i1 = x1.Insert(Tval);
            break;
        
          case 'i':   // Insert (i,t)
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  x1.Insert(i1," 
		      << Tval
		      << ")\n";
	    i1 = x1.Insert(i1,Tval);
            break;

          case '4':   // void PopFront()
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
            if (x1.Empty())
            {  
              *osptr << "unable to pop: x1 is empty\n";
              break;
            }
            Tval = x1.Front();
            x1.PopFront();
            *osptr << Tval << " popped from front of x1\n";
            i1 = x1.Begin();
            break;
        
          case '5':   // void PopBack()
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
            if (x1.Empty())
            {  
              *osptr <<  "unable to pop: x1 is empty\n";
              break;
            }
            Tval = x1.Back();
            x1.PopBack();
            *osptr << Tval << " popped from back of x1\n";
            i1 = x1.rBegin();
            break;
        
          case '6':   // void Remove(t)
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  ";
            *osptr << x1.Remove(Tval) << " copies of " << Tval 
		      << " removed from x1\n";
            break;

          case 'r':   // void Remove(i)
            if (BATCH) *osptr << '\n';
            if (i1.Valid())
            {
	      *osptr << "  " << *i1 << " =  *i1\n";
              *osptr << "  i1 = x1.Remove(i1)\n";
	      i1 = x1.Remove(i1);
	      *osptr << "  " << *i1 << " =  *i1\n";
            }
	    else
	      *osptr << "  Unable to remove: i1 is invalid\n";
            break;

          case 'a':
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
	    if (x1.Empty())
	      *osptr << "x1 is empty: no front element\n";
            else
              *osptr << x1.Front() << " = x1.Front()\n";
            i1 = x1.Begin();
            *osptr << "  i1 = x1.Begin()\n";
            break;

          case 'z':
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
	    if (x1.Empty())
	      *osptr << "x1 is empty: no back element\n";
            else
              *osptr << x1.Back() << " = x1.Back()\n";
            i1 = x1.rBegin();
            *osptr << "  i1 = x1.rBegin()\n";
            break;

          case 'c':   // void Clear ()
            if (BATCH) *osptr << '\n';
            x1.Clear();
            i1 = x1.Begin();
            break;

          case '*': case '?':  // *i, i.Valid
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
            if (i1.Valid())
              *osptr << "*i1 == " << *i1 << '\n';
            else
              *osptr << "i1 == NULL\n";
            break;
        
          case '^':   // *i = t
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  ";
            if (i1.Valid())
            {
              *i1 = Tval;
              *osptr << "Update completed\n";
            }
            else
              *osptr << "Cannot update: iterator invalid\n";
            break;
        
          case 'R':   // void Reverse()
            if (BATCH) *osptr << '\n';
	    x1.Reverse();
            *osptr << "  x1.Reverse();\n";
	    break;

          case 'M': case 'm':  // Merge(list)
            *isptr >> option;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL << '\n';
              else *osptr << option << '\n';;
            }
	    switch(option)
	    {
	      case '1':
		x1.Merge(x1);
		*osptr << "  x1.Merge(x1);\n";
		break;
	      case '2':
		x1.Merge(x2);
		*osptr << "  x1.Merge(x2);\n";
		break;
	      case '3':
		x1.Merge(x3);
		*osptr << "  x1.Merge(x3);\n";
		break;
	    }
	    break;

          case 'e':   // bool Empty()
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
            *osptr << "x1 is";
            if (!x1.Empty())
              *osptr << " NOT";
            *osptr << " empty\n";
            break;

	  case 'd':  case 'D': // Display
            if (BATCH) *osptr << '\n';
            DisplayContainerType(code0,code1,*osptr);
            *osptr << "  x1.Display(*osptr): ";
            x1.Display(*osptr,ofc);
            *osptr << '\n';
            break;
          
	  case 't':  case 'T': // traverse
            if (BATCH) *osptr << '\n';
            if (ofc == '\0')
            {
              *osptr << "   Traverse x1: ";
              for (i0 = x1.Begin(); i0 != x1.End(); ++i0)
              {
                *osptr << *i0;
              }
              *osptr << '\n';
              *osptr << "  rTraverse x1: ";
              for (i0 = x1.rBegin(); i0 != x1.rEnd(); --i0)
              {
                *osptr << *i0;
              }
              *osptr << '\n';
            }
            else
            {
              *osptr << "   Traverse x1: ";
              for (i0 = x1.Begin(); i0 != x1.End(); ++i0)
              {
                *osptr << ofc << *i0;
              }
              *osptr << '\n';
              *osptr << "  rTraverse x1: ";
              for (i0 = x1.rBegin(); i0 != x1.rEnd(); --i0)
              {
                *osptr << ofc << *i0;
              }
              *osptr << '\n';
            }
            break;
          
          case 's': case 'S':  // unsigned int Size()
            if (BATCH) *osptr << '\n';
            *osptr << "  " << x1.Size() << " = x1.Size();\n";
	    break;

          case '<':   // void Sort()
            if (BATCH) *osptr << '\n';
	    x1.Sort();
            *osptr << "  x1.Sort();\n";
	    break;

          case '>':   // void Sort(p)
            if (BATCH) *osptr << '\n';
	    x1.Sort(pred);
            *osptr << "  x1.Sort(>);\n";
	    break;

          case '=':
            *isptr >> option;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL;
              else *osptr << option;;
            }
            switch(option)
            {
              case '1': 
		if (BATCH) *osptr << '\n';
		x1 = x1;
		i1 = x1.Begin();
		*osptr << "x1 = x1; i1 = x1.Begin();\n";
		break;
	      case '2':
		if (BATCH) *osptr << '\n'; 
		x1 = x2;
		i1 = x1.Begin();
		*osptr << "x1 = x2; i1 = x1.Begin();\n";
		break;
	      case '3':
		if (BATCH) *osptr << '\n';
		x1 = x3;
		i1 = x1.Begin();
		*osptr << "x1 = x3; i1 = x1.Begin();\n";
		break;
	      case '=':
	        *isptr >> option;
                if (BATCH)
                {
                  if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL << '\n';
                  else *osptr << option << '\n';;
                }
		*osptr << "  ";
		switch(option)
                {
                  case '1':
                    if (x1 == x1)
                      *osptr << "x1 == x1\n";
                    else
                      *osptr << "x1 != x1\n";
                    break;
                  case '2':
                    if (x1 == x2)
                      *osptr << "x1 == x2\n";
                    else
                      *osptr << "x1 != x2\n";
                    break;
                  case '3':
                    if (x1 == x3)
                      *osptr << "x1 == x3\n";
                    else
                      *osptr << "x1 != x3\n";
                    break;
                }
                break;
            }
            break;

          case '!':
            *isptr >> option;  // assumed to be '='
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL;
              else *osptr << option;;
            }
            *isptr >> option;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL << '\n';
              else *osptr << option << '\n';;
            }
            *osptr << "  ";
            switch(option)
            {
              case '1':
                if (x1 != x1)
                  *osptr << "x1 != x1\n";
                else
                  *osptr << "x1 == x1\n";
                break;
              case '2':
                if (x1 != x2)
                  *osptr << "x1 != x2\n";
                else
                  *osptr << "x1 == x2\n";
                break;
              case '3':
                if (x1 != x3)
                  *osptr << "x1 != x3\n";
                else
                  *osptr << "x1 == x3\n";
                break;
            }
            break;

          case '+':   // ++(), +=()
            *isptr >> option;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL;
              else *osptr << option;;
            }
            switch(option)
            {
              case '+':
		if (BATCH) *osptr << '\n'; 
		++i1;
		*osptr << "  ++i1;";
		if (i1.Valid())
		  *osptr << "  " << *i1 << " = *i1;\n";
		else 
		  *osptr << "  false = i1.Valid();\n";
		break;
              case '=':
		*isptr >> option;
                if (BATCH)
                {
                  if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL << '\n'; 
                  else *osptr << option << '\n';;
                }
                switch(option)
		{
                  case '1':
		    x1 += x1;
                    *osptr << "  x1 += x1;\n";
                  break;
                  case '2':
		    x1 += x2;
                    *osptr << "  x1 += x2;\n";
                  break;
                  case '3':
		    x1 += x3;
                    *osptr << "  x1 += x3;\n";
                  break;
		}
		break;
              default: *osptr << "** Unknown command -- try again\n";
              break;
            }  
            break;
        
          case '-':   // --
            *isptr >> option;  // assumed to be '-'
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL << '\n'; 
              else *osptr << option << '\n';;
            }
            --i1;
	    *osptr << "  --i1;";
	    if (i1.Valid())
	      *osptr << "  " << *i1 << " = *i1;\n";
	    else 
	      *osptr << "  false = i1.Valid();\n";
	    break;

          case 'l': case 'L': // load file
            *isptr >> datafile;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << ' ' << datafile << ANSI_RESET_ALL << '\n'; 
              else *osptr << ' ' << datafile  << '\n';;
            }
            dataistream.open(datafile.Cstr());
            if ( dataistream.fail() )
            {
              *osptr << " ** unable to open file " << datafile << '\n';
              dataistream.clear();
            }
            else
            {
              while (dataistream >> Tval)
                x1.PushBack(Tval);
              dataistream.clear();
              dataistream.close();
              *osptr << " Loaded data from file " << datafile << " at back of x1\n";
            }
            break;

          case 'w': case 'W': // write file
            *isptr >> datafile;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << ' ' << datafile << ANSI_RESET_ALL << '\n'; 
              else *osptr << ' ' << datafile  << '\n';;
            }
            dataostream.open(datafile.Cstr());
            if ( dataostream.fail() )
            {
              *osptr << " ** unable to open file " << datafile << '\n';
              dataostream.clear();
            }
            else
            {
              for (ci = x1.Begin(); ci != x1.End(); ++ci)
                dataostream << *ci << '\n';
              dataostream.close();
              *osptr << " Written x1 data to file " << datafile << '\n';
            }
            break;

          default:
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL; 
              else *osptr << option;;
            }
            do 
	    {
	      isptr->get(option);
	      if (BATCH)
              {
                if (COLOR) *osptr << ANSI_BOLD_RED;
                osptr->put(option);
                if (COLOR) *osptr << ANSI_RESET_ALL;
              }
	    } 
            while (option != '\n');
            *osptr << " ** Unrecognized command -- please try again\n";

        }  // end case '1'
        break;

      case '2': 
        *isptr >> option;
        if (BATCH)
        {
          if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL;
          else *osptr << option;;
        }
        switch (option)
        {
          case '$':
            if (BATCH) *osptr << '\n';
            *osptr << "  x2.CheckLinks()\n";
            StructureTest(x2,*osptr);
            break;
          case '1':   // void PushFront (T)
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  x2.PushFront(" 
		      << Tval
		      << ")\n";
	    x2.PushFront(Tval);
            break;
        
          case '2':   // void PushBack (T)
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  x2.PushBack(" 
		      << Tval
		      << ")\n";
	    x2.PushBack(Tval);
            break;
        
          case '3':   // void Insert (t)
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  x2.Insert(" 
		      << Tval
		      << ")\n";
	    i2 = x2.Insert(Tval);
            break;
        
          case 'i':   // Insert (i,t)
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  x2.Insert(i2," 
		      << Tval
		      << ")\n";
	    i2 = x2.Insert(i2,Tval);
            break;

          case '4':   // void PopFront()
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
            if (x2.Empty())
            {  
              *osptr << "unable to pop: x2 is empty\n";
              break;
            }
            Tval = x2.Front();
            x2.PopFront();
            *osptr << Tval << " popped from front of x2\n";
            i2 = x2.Begin();
            break;
        
          case '5':   // void PopBack()
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
            if (x2.Empty())
            {  
              *osptr <<  "unable to pop: x2 is empty\n";
              break;
            }
            Tval = x2.Back();
            x2.PopBack();
            *osptr << Tval << " popped from back of x2\n";
            i2 = x2.rBegin();
            break;
        
          case '6':   // void Remove(t)
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  ";
            *osptr << x2.Remove(Tval) << " copies of " << Tval 
		      << " removed from x2\n";
            break;

          case 'r':   // void Remove(i)
            if (BATCH) *osptr << '\n';
            if (i2.Valid())
            {
	      *osptr << "  " << *i2 << " =  *i2\n";
              *osptr << "  i2 = x2.Remove(i2)\n";
	      i2 = x2.Remove(i2);
	      *osptr << "  " << *i2 << " =  *i2\n";
            }
	    else
	      *osptr << "  Unable to remove: i2 is invalid\n";
            break;

          case 'a':
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
	    if (x2.Empty())
	      *osptr << "x2 is empty: no front element\n";
            else
              *osptr << x2.Front() << " = x2.Front()\n";
            i2 = x2.Begin();
            *osptr << "  i2 = x2.Begin()\n";
            break;

          case 'z':
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
	    if (x2.Empty())
	      *osptr << "x2 is empty: no back element\n";
            else
              *osptr << x2.Back() << " = x2.Back()\n";
            i2 = x2.rBegin();
            *osptr << "  i2 = x2.rBegin()\n";
            break;

          case 'c':   // void Clear ()
            if (BATCH) *osptr << '\n';
            x2.Clear();
            i2 = x2.Begin();
            break;

          case '*': case '?':  // *i, i.Valid
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
            if (i2.Valid())
              *osptr << "*i2 == " << *i2 << '\n';
            else
              *osptr << "i2 == NULL\n";
            break;
        
          case '^':   // *i = t
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  ";
            if (i2.Valid())
            {
              *i2 = Tval;
              *osptr << "Update completed\n";
            }
            else
              *osptr << "Cannot update: iterator invalid\n";
            break;
        
          case 'R':   // void Reverse()
            if (BATCH) *osptr << '\n';
	    x2.Reverse();
            *osptr << "  x2.Reverse();\n";
	    break;

          case 'M': case 'm':  // Merge(list)
            *isptr >> option;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL << '\n';
              else *osptr << option << '\n';;
            }
	    switch(option)
	    {
	      case '1':
		x2.Merge(x1);
		*osptr << "  x2.Merge(x1);\n";
		break;
	      case '2':
		x2.Merge(x2);
		*osptr << "  x2.Merge(x2);\n";
		break;
	      case '3':
		x2.Merge(x3);
		*osptr << "  x2.Merge(x3);\n";
		break;
	    }
	    break;

          case 'e':   // bool Empty()
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
            *osptr << "x2 is";
            if (!x2.Empty())
              *osptr << " NOT";
            *osptr << " empty\n";
            break;

	  case 'd':  case 'D': // Display
            if (BATCH) *osptr << '\n';
            DisplayContainerType(code0,code1,*osptr);
            *osptr << "  x2.Display(*osptr): ";
            x2.Display(*osptr,ofc);
            *osptr << '\n';
            break;
          
	  case 't':  case 'T': // traverse
            if (BATCH) *osptr << '\n';
            if (ofc == '\0')
            {
              *osptr << "   Traverse x2: ";
              for (i0 = x2.Begin(); i0 != x2.End(); ++i0)
              {
                *osptr << *i0;
              }
              *osptr << '\n';
              *osptr << "  rTraverse x2: ";
              for (i0 = x2.rBegin(); i0 != x2.rEnd(); --i0)
              {
                *osptr << *i0;
              }
              *osptr << '\n';
            }
            else
            {
              *osptr << "   Traverse x2: ";
              for (i0 = x2.Begin(); i0 != x2.End(); ++i0)
              {
                *osptr << ofc << *i0;
              }
              *osptr << '\n';
              *osptr << "  rTraverse x2: ";
              for (i0 = x2.rBegin(); i0 != x2.rEnd(); --i0)
              {
                *osptr << ofc << *i0;
              }
              *osptr << '\n';
            }
            break;
          
          case 's': case 'S':  // unsigned int Size()
            if (BATCH) *osptr << '\n';
            *osptr << "  " << x2.Size() << " = x2.Size();\n";
	    break;

          case '<':   // void Sort()
            if (BATCH) *osptr << '\n';
	    x2.Sort();
            *osptr << "  x2.Sort();\n";
	    break;

          case '>':   // void Sort(p)
            if (BATCH) *osptr << '\n';
	    x2.Sort(pred);
            *osptr << "  x2.Sort(>);\n";
	    break;

          case '=':
            *isptr >> option;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL;
              else *osptr << option;;
            }
            switch(option)
            {
              case '1': 
		if (BATCH) *osptr << '\n';
		x2 = x1;
		i2 = x1.Begin();
		*osptr << "x2 = x1; i2 = x2.Begin();\n";
		break;
	      case '2':
		if (BATCH) *osptr << '\n'; 
		x2 = x2;
		i2 = x2.Begin();
		*osptr << "x2 = x2; i2 = x2.Begin();\n";
		break;
	      case '3':
		if (BATCH) *osptr << '\n';
		x2 = x3;
		i2 = x2.Begin();
		*osptr << "x2 = x3; i2 = x2.Begin();\n";
		break;
	      case '=':
	        *isptr >> option;
                if (BATCH)
                {
                  if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL << '\n';
                  else *osptr << option << '\n';;
                }
		*osptr << "  ";
		switch(option)
                {
                  case '1':
                    if (x2 == x1)
                      *osptr << "x2 == x1\n";
                    else
                      *osptr << "x2 != x1\n";
                    break;
                  case '2':
                    if (x2 == x2)
                      *osptr << "x2 == x2\n";
                    else
                      *osptr << "x2 != x2\n";
                    break;
                  case '3':
                    if (x2 == x3)
                      *osptr << "x2 == x3\n";
                    else
                      *osptr << "x2 != x3\n";
                    break;
                }
                break;
            }
            break;

          case '!':
            *isptr >> option;  // assumed to be '='
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL;
              else *osptr << option;;
            }
            *isptr >> option;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL << '\n';
              else *osptr << option << '\n';;
            }
            *osptr << "  ";
            switch(option)
            {
              case '1':
                if (x2 != x1)
                  *osptr << "x2 != x1\n";
                else
                  *osptr << "x2 == x1\n";
                break;
              case '2':
                if (x2 != x2)
                  *osptr << "x2 != x2\n";
                else
                  *osptr << "x2 == x2\n";
                break;
              case '3':
                if (x2 != x3)
                  *osptr << "x2 != x3\n";
                else
                  *osptr << "x2 == x3\n";
                break;
            }
            break;

          case '+':   // ++(), +=()
            *isptr >> option;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL;
              else *osptr << option;;
            }
            switch(option)
            {
              case '+':
		if (BATCH) *osptr << '\n'; 
		++i2;
		*osptr << "  ++i2;";
		if (i2.Valid())
		  *osptr << "  " << *i2 << " = *i2;\n";
		else 
		  *osptr << "  false = i2.Valid();\n";
		break;
              case '=':
		*isptr >> option;
                if (BATCH)
                {
                  if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL << '\n'; 
                  else *osptr << option << '\n';;
                }
                switch(option)
		{
                  case '1':
		    x2 += x1;
                    *osptr << "  x2 += x1;\n";
                  break;
                  case '2':
		    x2 += x2;
                    *osptr << "  x2 += x2;\n";
                  break;
                  case '3':
		    x2 += x3;
                    *osptr << "  x2 += x3;\n";
                  break;
		}
		break;
              default: *osptr << "** Unknown command -- try again\n";
              break;
            }  
            break;
        
          case '-':   // --
            *isptr >> option;  // assumed to be '-'
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL << '\n'; 
              else *osptr << option << '\n';;
            }
            --i2;
	    *osptr << "  --i2;";
	    if (i2.Valid())
	      *osptr << "  " << *i2 << " = *i2;\n";
	    else 
	      *osptr << "  false = i2.Valid();\n";
	    break;

          case 'l': case 'L': // load file
            *isptr >> datafile;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << ' ' << datafile << ANSI_RESET_ALL << '\n'; 
              else *osptr << ' ' << datafile << '\n';;
            }
            dataistream.open(datafile.Cstr());
            if ( dataistream.fail() )
            {
              *osptr << " ** unable to open file " << datafile << '\n';
              dataistream.clear();
            }
            else
            {
              while (dataistream >> Tval)
                x2.PushBack(Tval);
              dataistream.clear();
              dataistream.close();
              *osptr << " Loaded data from file " << datafile << " at back of x2\n";
            }
            break;

          case 'w': case 'W': // write file
            *isptr >> datafile;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << ' ' << datafile << ANSI_RESET_ALL << '\n'; 
              else *osptr << ' ' << datafile << '\n';;
            }
            dataostream.open(datafile.Cstr());
            if ( dataostream.fail() )
            {
              *osptr << " ** unable to open file " << datafile << '\n';
              dataostream.clear();
            }
            else
            {
              for (ci = x2.Begin(); ci != x2.End(); ++ci)
                dataostream << *ci << '\n';
              dataostream.close();
              *osptr << " Written x2 data to file " << datafile << '\n';
            }
            break;

          default:
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL; 
              else *osptr << option;;
            }
            do 
	    {
	      isptr->get(option);
	      if (BATCH)
              {
                if (COLOR) *osptr << ANSI_BOLD_RED;
                osptr->put(option);
                if (COLOR) *osptr << ANSI_RESET_ALL;
              }
	    } 
            while (option != '\n');
            *osptr << " ** Unrecognized command -- please try again\n";

        }  // end case '2'
        break;

      case '3': 
        *isptr >> option;
        if (BATCH)
        {
          if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL;
          else *osptr << option;;
        }
        switch (option)
        {
          case '$':
            if (BATCH) *osptr << '\n';
            *osptr << "  x3.CheckLinks()\n";
            StructureTest(x3,*osptr);
            break;
          case '1':   // void PushFront (T)
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  x3.PushFront(" 
		      << Tval
		      << ")\n";
	    x3.PushFront(Tval);
            break;
        
          case '2':   // void PushBack (T)
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  x3.PushBack(" 
		      << Tval
		      << ")\n";
	    x3.PushBack(Tval);
            break;
        
          case '3':   // void Insert (t)
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  x3.Insert(" 
		      << Tval
		      << ")\n";
	    i3 = x3.Insert(Tval);
            break;
        
          case 'i':   // Insert (i,t)
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  x3.Insert(i3," 
		      << Tval
		      << ")\n";
	    i3 = x3.Insert(i3,Tval);
            break;

          case '4':   // void PopFront()
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
            if (x3.Empty())
            {  
              *osptr << "unable to pop: x3 is empty\n";
              break;
            }
            Tval = x3.Front();
            x3.PopFront();
            *osptr << Tval << " popped from front of x3\n";
            i3 = x3.Begin();
            break;
        
          case '5':   // void PopBack()
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
            if (x3.Empty())
            {  
              *osptr <<  "unable to pop: x3 is empty\n";
              break;
            }
            Tval = x3.Back();
            x3.PopBack();
            *osptr << Tval << " popped from back of x3\n";
            i3 = x3.rBegin();
            break;
        
          case '6':   // void Remove(t)
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  ";
            *osptr << x3.Remove(Tval) << " copies of " << Tval 
		      << " removed from x3\n";
            break;

          case 'r':   // void Remove(i)
            if (BATCH) *osptr << '\n';
            if (i3.Valid())
            {
	      *osptr << "  " << *i3 << " =  *i3\n";
              *osptr << "  i3 = x3.Remove(i3)\n";
	      i3 = x3.Remove(i3);
	      *osptr << "  " << *i3 << " =  *i3\n";
            }
	    else
	      *osptr << "  Unable to remove: i3 is invalid\n";
            break;

          case 'a':
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
	    if (x3.Empty())
	      *osptr << "x3 is empty: no front element\n";
            else
              *osptr << x3.Front() << " = x3.Front()\n";
            i3 = x3.Begin();
            *osptr << "  i3 = x3.Begin()\n";
            break;

          case 'z':
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
	    if (x3.Empty())
	      *osptr << "x3 is empty: no back element\n";
            else
              *osptr << x3.Back() << " = x3.Back()\n";
            i3 = x3.rBegin();
            *osptr << "  i3 = x3.rBegin()\n";
            break;

          case 'c':   // void Clear ()
            if (BATCH) *osptr << '\n';
            x3.Clear();
            i3 = x3.Begin();
            break;

          case '*': case '?':  // *i, i.Valid
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
            if (i3.Valid())
              *osptr << "*i3 == " << *i3 << '\n';
            else
              *osptr << "i3 == NULL\n";
            break;
        
          case '^':   // *i = t
            *isptr >> Tval;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << Tval << ANSI_RESET_ALL << '\n';
              else *osptr << Tval << '\n';;
            }
            *osptr << "  ";
            if (i3.Valid())
            {
              *i3 = Tval;
              *osptr << "Update completed\n";
            }
            else
              *osptr << "Cannot update: iterator invalid\n";
            break;
        
          case 'R':   // void Reverse()
            if (BATCH) *osptr << '\n';
	    x3.Reverse();
            *osptr << "  x3.Reverse();\n";
	    break;

          case 'M': case 'm':  // Merge(list)
            *isptr >> option;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL << '\n';
              else *osptr << option << '\n';;
            }
	    switch(option)
	    {
	      case '1':
		x3.Merge(x1);
		*osptr << "  x3.Merge(x1);\n";
		break;
	      case '2':
		x3.Merge(x2);
		*osptr << "  x3.Merge(x2);\n";
		break;
	      case '3':
		x3.Merge(x3);
		*osptr << "  x3.Merge(x3);\n";
		break;
	    }
	    break;

          case 'e':   // bool Empty()
            if (BATCH) *osptr << '\n';
            *osptr << "  ";
            *osptr << "x3 is";
            if (!x3.Empty())
              *osptr << " NOT";
            *osptr << " empty\n";
            break;

	  case 'd':  case 'D': // Display
            if (BATCH) *osptr << '\n';
            DisplayContainerType(code0,code1,*osptr);
            *osptr << "  x3.Display(*osptr): ";
            x3.Display(*osptr,ofc);
            *osptr << '\n';
            break;
          
	  case 't':  case 'T': // traverse
            if (BATCH) *osptr << '\n';
            if (ofc == '\0')
            {
              *osptr << "   Traverse x3: ";
              for (i0 = x3.Begin(); i0 != x3.End(); ++i0)
              {
                *osptr << *i0;
              }
              *osptr << '\n';
              *osptr << "  rTraverse x3: ";
              for (i0 = x3.rBegin(); i0 != x3.rEnd(); --i0)
              {
                *osptr << *i0;
              }
              *osptr << '\n';
            }
            else
            {
              *osptr << "   Traverse x3: ";
              for (i0 = x3.Begin(); i0 != x3.End(); ++i0)
              {
                *osptr << ofc << *i0;
              }
              *osptr << '\n';
              *osptr << "  rTraverse x3: ";
              for (i0 = x3.rBegin(); i0 != x3.rEnd(); --i0)
              {
                *osptr << ofc << *i0;
              }
              *osptr << '\n';
            }
            break;
          
          case 's': case 'S':  // unsigned int Size()
            if (BATCH) *osptr << '\n';
            *osptr << "  " << x3.Size() << " = x3.Size();\n";
	    break;

          case '<':   // void Sort()
            if (BATCH) *osptr << '\n';
	    x3.Sort();
            *osptr << "  x3.Sort();\n";
	    break;

          case '>':   // void Sort(p)
            if (BATCH) *osptr << '\n';
	    x3.Sort(pred);
            *osptr << "  x3.Sort(>);\n";
	    break;

          case '=':
            *isptr >> option;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL;
              else *osptr << option;;
            }
            switch(option)
            {
              case '1': 
		if (BATCH) *osptr << '\n';
		x3 = x1;
		i3 = x3.Begin();
		*osptr << "x3 = x1; i3 = x3.Begin();\n";
		break;
	      case '2':
		if (BATCH) *osptr << '\n'; 
		x3 = x2;
		i3 = x3.Begin();
		*osptr << "x3 = x2; i3 = x3.Begin();\n";
		break;
	      case '3':
		if (BATCH) *osptr << '\n';
		x3 = x3;
		i3 = x3.Begin();
		*osptr << "x3 = x3; i3 = x3.Begin();\n";
		break;
	      case '=':
	        *isptr >> option;
                if (BATCH)
                {
                  if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL << '\n';
                  else *osptr << option << '\n';;
                }
		*osptr << "  ";
		switch(option)
                {
                  case '1':
                    if (x3 == x1)
                      *osptr << "x3 == x1\n";
                    else
                      *osptr << "x3 != x1\n";
                    break;
                  case '2':
                    if (x3 == x2)
                      *osptr << "x3 == x2\n";
                    else
                      *osptr << "x3 != x2\n";
                    break;
                  case '3':
                    if (x3 == x3)
                      *osptr << "x3 == x3\n";
                    else
                      *osptr << "x3 != x3\n";
                    break;
                }
                break;
            }
            break;

          case '!':
            *isptr >> option;  // assumed to be '='
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL;
              else *osptr << option;;
            }
            *isptr >> option;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL << '\n';
              else *osptr << option << '\n';;
            }
            *osptr << "  ";
            switch(option)
            {
              case '1':
                if (x3 != x1)
                  *osptr << "x3 != x1\n";
                else
                  *osptr << "x3 == x1\n";
                break;
              case '2':
                if (x3 != x2)
                  *osptr << "x3 != x2\n";
                else
                  *osptr << "x3 == x2\n";
                break;
              case '3':
                if (x3 != x3)
                  *osptr << "x3 != x3\n";
                else
                  *osptr << "x3 == x3\n";
                break;
            }
            break;

          case '+':   // ++(), +=()
            *isptr >> option;
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL;
              else *osptr << option;;
            }
            switch(option)
            {
              case '+':
		if (BATCH) *osptr << '\n'; 
		++i3;
		*osptr << "  ++i3;";
		if (i3.Valid())
		  *osptr << "  " << *i3 << " = *i3;\n";
		else 
		  *osptr << "  false = i3.Valid();\n";
		break;
              case '=':
		*isptr >> option;
                if (BATCH)
                {
                  if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL << '\n'; 
                  else *osptr << option << '\n';;
                }
                switch(option)
		{
                  case '1':
		    x3 += x1;
                    *osptr << "  x3 += x1;\n";
                  break;
                  case '2':
		    x3 += x2;
                    *osptr << "  x3 += x2;\n";
                  break;
                  case '3':
		    x3 += x3;
                    *osptr << "  x3 += x3;\n";
                  break;
		}
		break;
              default: *osptr << "** Unknown command -- try again\n";
              break;
            }  
            break;
        
          case '-':   // --
            *isptr >> option;  // assumed to be '-'
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL << '\n'; 
              else *osptr << option << '\n';;
            }
            --i3;
	    *osptr << "  --i3;";
	    if (i3.Valid())
	      *osptr << "  " << *i3 << " = *i3;\n";
	    else 
	      *osptr << "  false = i3.Valid();\n";
	    break;

          case 'l': case 'L': // load file
            *isptr >> datafile;
            if (BATCH)
            {
              if (COLOR)  *osptr << ANSI_BOLD_RED << ' ' << datafile << ANSI_RESET_ALL << '\n'; 
              else *osptr << ' ' << datafile << '\n';;
            }
            dataistream.open(datafile.Cstr());
            if ( dataistream.fail() )
            {
              *osptr << " ** unable to open file " << datafile << '\n';
              dataistream.clear();
            }
            else
            {
              while (dataistream >> Tval)
                x3.PushBack(Tval);
              dataistream.clear();
              dataistream.close();
              *osptr << " Loaded data from file " << datafile << " at back of x3\n";
            }
            break;

          case 'w': case 'W': // write file
            *isptr >> datafile;
            if (BATCH)
            {
              if (COLOR)  *osptr << ANSI_BOLD_RED << ' ' << datafile << ANSI_RESET_ALL << '\n'; 
              else *osptr << ' ' << datafile << '\n';;
            }
            dataostream.open(datafile.Cstr());
            if ( dataostream.fail() )
            {
              *osptr << " ** unable to open file " << datafile << '\n';
              dataostream.clear();
            }
            else
            {
              for (ci = x3.Begin(); ci != x3.End(); ++ci)
                dataostream << *ci << '\n';
              dataostream.close();
              *osptr << " Written x3 data to file " << datafile << '\n';
            }
            break;

          default:
            if (BATCH)
            {
              if (COLOR) *osptr << ANSI_BOLD_RED << option << ANSI_RESET_ALL; 
              else *osptr << option;;
            }
            do 
	    {
	      isptr->get(option);
	      if (BATCH)
              {
                if (COLOR) *osptr << ANSI_BOLD_RED;
                osptr->put(option);
                if (COLOR) *osptr << ANSI_RESET_ALL;
              }
	    } 
            while (option != '\n');
            *osptr << " ** Unrecognized command -- please try again\n";

        }  // end case '3'
        break;

      case '=':
	if (BATCH) *osptr << '\n'; 
        x3 = x2 = x1;
	i1 = x1.Begin();
	i2 = x2.Begin();
	i3 = x3.Begin();
	CopyTest(x3,*osptr);
	AssignTest(x3,*osptr);
        StructureTest(x3,*osptr);
	break;

      case 'm': case 'M':
	if (BATCH) *osptr << '\n'; 
        DisplayMenu(*osptr);
	break;

      case 'x': case 'X':  // switch to interactive mode or quit
	if (BATCH)
	{
	  *osptr << '\n';
	  ifs.close();
	  BATCH = 0;
	  isptr = &std::cin;
	}
	else
	{
          *osptr << " ** already in interactive mode\n";
	}
	break;

      case 'q': case 'Q':
	if (BATCH) *osptr << '\n'; 
	option = 'q';
        break;
          
      default:
        do 
        {
          isptr->get(option);
          if (BATCH)
          {
            if (COLOR) *osptr << ANSI_BOLD_RED;
            osptr->put(option);
            if (COLOR) *osptr << ANSI_RESET_ALL;
          }
        } 
	while (option != '\n');
        *osptr << "** Unrecognized command -- please try again.\n";
    }
  }
  while (option != 'q');
  if (BATCH) ifs.close();
  *osptr << "\nHave a nice day." << std::endl;
  return EXIT_SUCCESS;
}

void DisplayPrompt(std::ostream& os)
{
  os << "Enter [command][arguments] ('m' for menu, 'q' to quit): ";
}

void DisplayMenu(std::ostream& os)
{
  os 
       << '\n'
       << "  PushFront  (Tval)  .....  1      PopFront   ()  .........  4\n"
       << "  PushBack   (Tval)  .....  2      PopBack    ()  .........  5\n"
       << "  Insert     (Tval)  .....  3      Remove     (Tval)  .....  6\n"
       << "  Insert     (I,Tval)  ...  i      Remove     (I)  ........  r\n"
       << "  Front      ()  .........  a      Back       ()  .........  z\n"
       << "  Empty      ()  .........  e      Size       ()  .........  s\n"
       << "  I.Valid    ()  .........  ?      Clear      ()  .........  c\n"
       << "  *I         .............  *      *I = Tval  .............  ^\n"
       << "  I = X.Begin()  .........  a      I = X.rBegin()  ........  z\n"
       << "  ++I  ...................  ++     --I  ...................  --\n"
       << "  Sort  ..................  <      Sort(>)  ...............  >\n"
       << "  Reverse  ...............  R      Merge (list)  ..........  M\n"
       << "  Display  ...............  D      Traverse  ..............  T\n"
       << "  Load data from file  ...  L      Write list to file  ....  W\n"
       << "  Structure Test .........  $\n"
       << "  ------------------------------------------------------------\n"
       << "   Switch to interactive mode  ......  X\n"
       << "   operators  = , += , ==, !=  ......  [list][op][list]\n\n"
       << "   Enter '=' alone  .................  x3 = x2 = x1;\n"
       << "                     ................  CopyTest(x3);\n"
       << "                      ...............  AssignTest(x3);\n"
       << "                       ..............  StructureTest(x3);\n"
       << "                        .............  i1 = x1.Begin();\n"
       << "                         ............  i2 = x2.Begin();\n"
       << "                          ...........  i3 = x3.Begin();\n"
       << std::endl;
}

void Preamble(std::ostream& os)
{
  os << "\n   This test uses three Container objects: x1, x2, x3\n" 
     << "   and three associated Iterator objects: i1, i2, i3\n"
     << "   The test accesses the list API through a menu of commands (below).\n" 
     << "   For most, designate the list (1, 2 or 3), followed by the command,\n"
     << "   followed by the argument if needed.\n"
     << "   Some example entries and their meaning for the API:\n\n"
     << "      Entry     Action\n"
     << "      -----     ------\n"
     << "      11z       x1.PushFront(z)\n"
     << "      32q       x3.PushBack(q)\n"
     << "      2a        i2 = x2.Begin()  \n"
     << "      2++       ++i2\n"
     << "      2ig       x2.Insert(i2,g)\n"
     << "      1<        x1.Sort()\n"
     << "      1>        x1.Sort(pred)\n"
     << "      3=2       x3 = x2\n"
     << "      =         x3 = x2 = x1; init i1, i2, i3; CopyTest(x3); AssignTest(x3);\n\n";
}

void DisplayContainerType(const char code0, const char code1, std::ostream& os)
{
  switch(code0)
  {
    case 'c':
      switch(code1)
      {
        case '1':
          os << "List < char >";
          break;
        default:
          std::cerr << " [bad code1 passed to DisplayPrompt()]";
      }
      break;
    case 's':
      switch(code1)
      {
        case '1':
          os << "List < String >";
          break;
        default:
          std::cerr << " [bad code1 passed to DisplayPrompt()]";
      }
      break;
    case 'i':
      switch(code1)
      {
        case '1':
          os << "List < int >";
          break;
        default:
          std::cerr << " [bad code1 passed to DisplayPrompt()]";
      }
      break;
    default:
      std::cerr << " [bad code[0] passed to DisplayPrompt()]";
  }
}

