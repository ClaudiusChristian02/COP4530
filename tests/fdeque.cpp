/*
    fdeque.cpp
    01/01/12

    functionality test of Deque<T>

    Copyright 2012
*/

#include <iostream>
#include <fstream>
#include <cctype>  // tolower()
#include <deque.h>

// choose A1 or A2

// const int BATCH = 1;  // 0 = interactive, 1 = batch

// A1: makes dequeues of char
typedef char ValueType;
const char* vT = "char";
ValueType Tval = '*';
// end A1 */

/* // A2: makes dequeues of String
#include <xstring.cpp>
typedef fsu::String ValueType;
const char* vT = "String";
ValueType Tval = "*";
// end A2 */

void ClearBuffer(std::istream* isp, bool BATCH)
{
  char ch;
  do
  {
    isp->get(ch);
    if (BATCH) std::cout << ch;
  }
  while (ch != '\n');
  std::cout << " ** Unknown command - try again\n";
}

void ReadIndex(std::istream& is, size_t& i, bool BATCH)
{
  is >> i;
  if (BATCH) std::cout << i;
}

void ReadOption(std::istream& is, char& option, bool BATCH)
{
  is >> option;
  if (BATCH) std::cout << option;
}

void GetOption(std::istream& is, char& option, bool BATCH)
{
  option = is.get();
  if (BATCH) std::cout.put(option);
}

template < typename T >
void ReadValue(std::istream& is, T& Tval, bool BATCH)
{
  is >> Tval;
  if (BATCH) std::cout << Tval << '\n';
}

void DisplayMenu();

int main(int argc, char* argv[])
{
  std::ifstream ifs;
  std::istream * inptr = &std::cin;
  bool BATCH = 0;
  if (argc > 1)
  {
    BATCH = 1;
    ifs.open(argv[1]);
    if (ifs.fail()) return 0;
    inptr = &ifs;
  }

  fsu::Deque<ValueType> x1(10,Tval), x2, x3;
  fsu::Deque<ValueType>::Iterator I, I1, I2, I3;
  ValueType  Tval;
  char       option;
  size_t     i;
  if (!BATCH) DisplayMenu();

  do
  {
    std::cout << "Enter [deq][command][argument] ('M' for menu, 'Q' to quit)\n: ";
    ReadOption(*inptr, option, BATCH);
    option = tolower(option);
    switch (option)
    {
      case 'x': case 'X':
	if (BATCH)
	{
	  std::cout << '\n';
	  ifs.close();
	  inptr = &std::cin;
	  std::cout << "  ** switched to keyboard input **\n";
	  BATCH = 0;
	  DisplayMenu();
	}
	else
	{
	  std::cout << "  ** already using keyboard input **\n";
	}
	break;
          
      case 'q': case 'Q':
	if (BATCH)
	{
	  std::cout << '\n';
	  ifs.close();
	}
	option = 'q';
	break;

      case '=':
	if (BATCH) std::cout << '\n';
	x3 = x2 = x1; break;

      case 'm':
	if (BATCH) std::cout << '\n';
        DisplayMenu(); break;

      case '1': 
        ReadOption(*inptr, option, BATCH);
        option = tolower(option);
        switch (option)
        {
          case '1':   // void PushFront (T)
            ReadValue(*inptr, Tval, BATCH);
            x1.PushFront(Tval);
            break;
        
          case '2':   // void PushBack (T)
            ReadValue(*inptr, Tval, BATCH);
            x1.PushBack(Tval);
            break;
        
          case '3':   // void PopFront()
	    if (BATCH) std::cout << '\n';
            x1.PopFront();
            break;
        
          case '4':   // void PopBack()
	    if (BATCH) std::cout << '\n';
            x1.PopBack();
            break;

          case 'a':
	    if (BATCH) std::cout << '\n';
            std::cout << "x1.Front() == " << x1.Front() << '\n';
            break;

          case 's':   // Size() 
	    if (BATCH) std::cout << '\n';
            std::cout << "Size          == " << x1.Size() << '\n';
            break;

          case 'z':
	    if (BATCH) std::cout << '\n';
	    std::cout << "x1.Back() == " << x1.Back() << '\n';
            break;

          case 'c':   // void Clear ()
	    if (BATCH) std::cout << '\n';
            x1.Clear();
            break;

          case '*':   // *I
            GetOption(*inptr, option, BATCH);
            switch(option)
            {
              case '=':
                ReadValue(*inptr, Tval, BATCH);
                if (I1.Valid())
                  *I1 = Tval;
                else
                  std::cout << " I1 is not valid\n";
                break;
              default:
		if (BATCH) std::cout << '\n';
                if (I1.Valid())
                  std::cout << "*I1 == " << *I1 << '\n';
                else
                  std::cout << " I1 == NULL\n";
                break;
            }
            break;
        
          case 'u':   // void Update(T)
            ReadValue(*inptr, Tval, BATCH);
            if (I1.Valid())
            {
              *I1 = Tval;
              std::cout << "Update completed\n";
            }
            else
              std::cout << "Cannot update -- iterator invalid\n";
            break;
        
          case 'b':   // Begin()
	    if (BATCH) std::cout << '\n';
            I1 = x1.Begin();
            break;

          case 'r':   // rBegin()
	    if (BATCH) std::cout << '\n';
            I1 = x1.rBegin();
            break;

          case '[':   // I[i], I[i]=t
            ReadIndex(*inptr, i, BATCH);
            ReadOption(*inptr, option, BATCH);  // assumed to be ']'
            GetOption(*inptr, option, BATCH);
            switch(option)
            {
              case '=':
                ReadValue(*inptr, Tval, BATCH);
                if (I1.Valid())
                  I1[i] = Tval;
                else
                  std::cout << "I1 not valid\n";
                break;
              default:
		if (BATCH) std::cout << '\n';
                if (I1.Valid())
                  std::cout << "I1[" << i << "] == " << I1[i] << '\n';
                else
                  std::cout << "I1 not valid\n";
                break;
            }
            break;

          case 'e':   // int empty()
	    if (BATCH) std::cout << '\n';
            std::cout << "x1 is";
            if (!x1.Empty())
              std::cout << " not";
            std::cout << " empty\n";
            break;

          case 'd':  // test iterator
	    if (BATCH) std::cout << '\n';
            std::cout << "x1.Display(std::cout): ";
            x1.Display(std::cout);
            std::cout << '\n';
            std::cout << "      Iterate x1: ";
            for (I = x1.Begin(); I != x1.End(); ++I)
            {
              std::cout << *I;
            }
            std::cout << '\n';
            std::cout << "     rIterate x1: ";
            for (I = x1.rBegin(); I != x1.rEnd(); --I)
            {
              std::cout << *I;
            }
            std::cout << '\n';
            std::cout << "       x1.Dump(): \n";
            x1.Dump(std::cout);
            break;
          
          case '=':
            ReadOption(*inptr, option, BATCH);
            switch(option)
            {
              case '1': if (BATCH) std::cout << '\n'; x1 = x1; break;
              case '2': if (BATCH) std::cout << '\n'; x1 = x2; break;
              case '3': if (BATCH) std::cout << '\n'; x1 = x3; break;
              case '=':
                ReadOption(*inptr, option, BATCH);
		if (BATCH) std::cout << '\n';
                switch(option)
                {
                  case '1':
                    if (x1 == x1)
                      std::cout << "x1 == x1\n";
                    else
                      std::cout << "x1 != x1\n";
                    break;
                  case '2':
                    if (x1 == x2)
                      std::cout << "x1 == x2\n";
                    else
                      std::cout << "x1 != x2\n";
                    break;
                  case '3':
                    if (x1 == x3)
                      std::cout << "x1 == x3\n";
                    else
                      std::cout << "x1 != x3\n";
                    break;
                }
                break;
            }
            break;

          case '!':
            ReadOption(*inptr, option, BATCH);  // assumed to be '='
            ReadOption(*inptr, option, BATCH);
	    if (BATCH) std::cout << '\n';
            switch(option)
            {
              case '1':
                if (x1 != x1)
                  std::cout << "x1 != x1\n";
                else
                  std::cout << "x1 == x1\n";
                break;
              case '2':
                if (x1 != x2)
                  std::cout << "x1 != x2\n";
                else
                  std::cout << "x1 == x2\n";
                break;
              case '3':
                if (x1 != x3)
                  std::cout << "x1 != x3\n";
                else
                  std::cout << "x1 == x3\n";
                break;
            }
            break;

          case '+':   // ++(), +=()
            ReadOption(*inptr, option, BATCH);
	    if (BATCH) std::cout << '\n';
            switch(option)
            {
              case '+':
                ++I1;
                break;
              case '=':
                /*
                ReadOption(*inptr, option, BATCH);
                switch(option)
                {
                  case '1': x1 += x1; break;
                  case '2': x1 += x2; break;
                  case '3': x1 += x3; break;
                  default: ClearBuffer(inptr, BATCH);
                }
                */
                std::cout << "** operator +=() not implemented\n";
                break;
              default: ClearBuffer(inptr, BATCH);
            }
            break;
        
          case '-':   // --
            ReadOption(*inptr, option, BATCH);  // assumed to be '-'
	    if (BATCH) std::cout << '\n';
            --I1;
            break;
        
          default:
	    ClearBuffer(inptr, BATCH);

        }  // end case '1'
        break;

      case '2': 
        ReadOption(*inptr, option, BATCH);
        option = tolower(option);
        switch (option)
        {
          case '1':   // void PushFront (T)
            ReadValue(*inptr, Tval, BATCH);
            x2.PushFront(Tval);
            break;
        
          case '2':   // void PushBack (T)
            ReadValue(*inptr, Tval, BATCH);
            x2.PushBack(Tval);
            break;
        
          case '3':   // void PopFront()
            x2.PopFront();
            break;
        
          case '4':   // void PopBack()
            x2.PopBack();
            break;

          case 'a':
            std::cout << "x2.Front() == " << x2.Front() << '\n';
            break;

          case 's':   // Size() 
            std::cout << "Size          == " << x2.Size() << '\n';
            break;

          case 'z':
	    std::cout << "x2.Back() == " << x2.Back() << '\n';
            break;

          case 'c':   // void Clear ()
            x2.Clear();
            break;

          case '*':   // *I
            GetOption(*inptr, option, BATCH);
            switch(option)
            {
              case '=':
                ReadValue(*inptr, Tval, BATCH);
                if (I2.Valid())
                  *I2 = Tval;
                else
                  std::cout << " I2 is not valid\n";
                break;
              default:
                if (I2.Valid())
                  std::cout << "*I2 == " << *I2 << '\n';
                else
                  std::cout << " I2 == NULL\n";
                break;
            }
            break;
        
          case 'u':   // void Update(T)
            ReadValue(*inptr, Tval, BATCH);
            if (I2.Valid())
            {
              *I2 = Tval;
              std::cout << "Update completed\n";
            }
            else
              std::cout << "Cannot update -- iterator invalid\n";
            break;
        
          case 'b':   // Begin()
            I2 = x2.Begin();
            break;

          case 'r':   // rBegin()
            I2 = x2.rBegin();
            break;

          case '[':   // I[i], I[i]=t
            ReadIndex(*inptr, i, BATCH);
            ReadOption(*inptr, option, BATCH);  // assumed to be ']'
            GetOption(*inptr, option, BATCH);
            switch(option)
            {
              case '=':
                ReadValue(*inptr, Tval, BATCH);
                if (I2.Valid())
                  I2[i] = Tval;
                else
                  std::cout << "I2 not valid\n";
                break;
              default:
                if (I2.Valid())
                  std::cout << "I2[" << i << "] == " << I2[i] << '\n';
                else
                  std::cout << "I2 not valid\n";
                break;
            }
            break;

          case 'e':   // int empty()
            std::cout << "x2 is";
            if (!x2.Empty())
              std::cout << " not";
            std::cout << " empty\n";
            break;

          case 'd':  // test iterator
	    if (BATCH) std::cout << '\n';
            std::cout << "x2.Display(std::cout): ";
            x2.Display(std::cout);
            std::cout << '\n';
            std::cout << "      Iterate x2: ";
            for (I = x2.Begin(); I != x2.End(); ++I)
            {
              std::cout << *I;
            }
            std::cout << '\n';
            std::cout << "     rIterate x2: ";
            for (I = x2.rBegin(); I != x2.rEnd(); --I)
            {
              std::cout << *I;
            }
            std::cout << '\n';
            std::cout << "       x2.Dump(): \n";
            x2.Dump(std::cout);
            break;
          
          case '=':
            ReadOption(*inptr, option, BATCH);
            switch(option)
            {
              case '1': x2 = x1; break;
              case '2': x2 = x2; break;
              case '3': x2 = x3; break;
              case '=':
                ReadOption(*inptr, option, BATCH);
                switch(option)
                {
                  case '1':
                    if (x2 == x1)
                      std::cout << "x2 == x1\n";
                    else
                      std::cout << "x2 != x1\n";
                    break;
                  case '2':
                    if (x2 == x2)
                      std::cout << "x2 == x2\n";
                    else
                      std::cout << "x2 != x2\n";
                    break;
                  case '3':
                    if (x2 == x3)
                      std::cout << "x2 == x3\n";
                    else
                      std::cout << "x2 != x3\n";
                    break;
                }
                break;
            }
            break;

          case '!':
            ReadOption(*inptr, option, BATCH);  // assumed to be '='
            ReadOption(*inptr, option, BATCH);
            switch(option)
            {
              case '1':
                if (x2!= x1)
                  std::cout << "x2!= x1\n";
                else
                  std::cout << "x2== x1\n";
                break;
              case '2':
                if (x2!= x2)
                  std::cout << "x2!= x2\n";
                else
                  std::cout << "x2== x2\n";
                break;
              case '3':
                if (x2!= x3)
                  std::cout << "x2!= x3\n";
                else
                  std::cout << "x2== x3\n";
                break;
            }
            break;

          case '+':   // ++(), +=()
            ReadOption(*inptr, option, BATCH);
            switch(option)
            {
              case '+':
                ++I2;
                break;
              case '=':
              /*
                ReadOption(*inptr, option, BATCH);
                switch(option)
                {
                  case '1': x2+= x1; I2= x2.Begin(); break;
                  case '2': x2+= x2; I2= x2.Begin(); break;
                  case '3': x2+= x3; I2= x2.Begin(); break;
                  default: std::cout << "** Unknown command -- try again\n";
                }
                */
                std::cout << "** operator +=() no implemented\n";
                break;
              default: std::cout << "** Unknown command -- try again\n";
              break;
            }
            break;
        
          case '-':   // --
            ReadOption(*inptr, option, BATCH);  // assumed to be '-'
            --I2;
            break;
        
          default:
            do std::cin.get(option);
            while (option != '\n');
            std::cout << " ** Unrecognized command -- please try again\n";

        }  // end case '2'
        break;

      case '3': 
        ReadOption(*inptr, option, BATCH);
        option = tolower(option);
        switch (option)
        {
          case '1':   // void PushFront (T)
            ReadValue(*inptr, Tval, BATCH);
            x3.PushFront(Tval);
            break;
        
          case '2':   // void PushBack (T)
            ReadValue(*inptr, Tval, BATCH);
            x3.PushBack(Tval);
            break;
        
          case '3':   // void PopFront()
            x3.PopFront();
            break;
        
          case '4':   // void PopBack()
            x3.PopBack();
            break;

          case 'a':
            std::cout << "x3.Front() == " << x3.Front() << '\n';
            break;

          case 's':   // Size() 
            std::cout << "Size          == " << x3.Size() << '\n';
            break;

          case 'z':
	    std::cout << "x3.Back() == " << x3.Back() << '\n';
            break;

          case 'c':   // void Clear ()
            x3.Clear();
            break;

          case '*':   // *I
            GetOption(*inptr, option, BATCH);
            switch(option)
            {
              case '=':
                ReadValue(*inptr, Tval, BATCH);
                if (I3.Valid())
                  *I3 = Tval;
                else
                  std::cout << " I3 is not valid\n";
                break;
              default:
                if (I3.Valid())
                  std::cout << "*I3 == " << *I3 << '\n';
                else
                  std::cout << " I3 == NULL\n";
                break;
            }
            break;
        
          case 'u':   // void Update(T)
            ReadValue(*inptr, Tval, BATCH);
            if (I3.Valid())
            {
              *I3 = Tval;
              std::cout << "Update completed\n";
            }
            else
              std::cout << "Cannot update -- iterator invalid\n";
            break;
        
          case 'b':   // Begin()
            I3 = x3.Begin();
            break;

          case 'r':   // rBegin()
            I3 = x3.rBegin();
            break;

          case '[':   // I[i], I[i]=t
            ReadIndex(*inptr, i, BATCH);
            ReadOption(*inptr, option, BATCH);  // assumed to be ']'
            GetOption(*inptr, option, BATCH);
            switch(option)
            {
              case '=':
                ReadValue(*inptr, Tval, BATCH);
                if (I3.Valid())
                  I3[i] = Tval;
                else
                  std::cout << "I3 not valid\n";
                break;
              default:
                if (I3.Valid())
                  std::cout << "I3[" << i << "] == " << I3[i] << '\n';
                else
                  std::cout << "I3 not valid\n";
                break;
            }
            break;

          case 'e':   // int empty()
            std::cout << "x3 is";
            if (!x3.Empty())
              std::cout << " not";
            std::cout << " empty\n";
            break;

          case 'd':  // test iterator
	    if (BATCH) std::cout << '\n';
            std::cout << "x3.Display(std::cout): ";
            x3.Display(std::cout);
            std::cout << '\n';
            std::cout << "      Iterate x3: ";
            for (I = x3.Begin(); I != x3.End(); ++I)
            {
              std::cout << *I;
            }
            std::cout << '\n';
            std::cout << "     rIterate x3: ";
            for (I = x3.rBegin(); I != x3.rEnd(); --I)
            {
              std::cout << *I;
            }
            std::cout << '\n';
            std::cout << "       x3.Dump():\n";
            x3.Dump(std::cout);
            break;
          
          case '=':
            ReadOption(*inptr, option, BATCH);
            switch(option)
            {
              case '1': x3 = x1; break;
              case '2': x3 = x2; break;
              case '3': x3 = x3; break;
              case '=':
                ReadOption(*inptr, option, BATCH);
                switch(option)
                {
                  case '1':
                    if (x3 == x1)
                      std::cout << "x3 == x1\n";
                    else
                      std::cout << "x3 != x1\n";
                    break;
                  case '2':
                    if (x3 == x2)
                      std::cout << "x3 == x2\n";
                    else
                      std::cout << "x3 != x2\n";
                    break;
                  case '3':
                    if (x3 == x3)
                      std::cout << "x3 == x3\n";
                    else
                      std::cout << "x3 != x3\n";
                    break;
                }
                break;
            }
            break;

          case '!':
            ReadOption(*inptr, option, BATCH);  // assumed to be '='
            ReadOption(*inptr, option, BATCH);
            switch(option)
            {
              case '1':
                if (x3!= x1)
                  std::cout << "x3!= x1\n";
                else
                  std::cout << "x3== x1\n";
                break;
              case '2':
                if (x3!= x2)
                  std::cout << "x3!= x2\n";
                else
                  std::cout << "x3== x2\n";
                break;
              case '3':
                if (x3!= x3)
                  std::cout << "x3!= x3\n";
                else
                  std::cout << "x3== x3\n";
                break;
            }
            break;

          case '+':   // ++(), +=()
            ReadOption(*inptr, option, BATCH);
            switch(option)
            {
              case '+':
                ++I3;
                break;
              case '=':
              /*
                ReadOption(*inptr, option, BATCH);
                switch(option)
                {
                  case '1': x3 += x1; break;
                  case '2': x3 += x2; break;
                  case '3': x3 += x3; break;
                  default: std::cout << "** Unknown command -- try again\n";
                }
                */
                std::cout << "** operator +=() no implemented\n";
                break;
              default: std::cout << "** Unknown command -- try again\n";
              break;
            }
            break;
        
          case '-':   // --
            ReadOption(*inptr, option, BATCH);  // assumed to be '-'
            --I3;
            break;
        
          default:
            do std::cin.get(option);
            while (option != '\n');
            std::cout << " ** Unrecognized command -- please try again\n";

        }  // end case '3'
        break;

      default:
	ClearBuffer(inptr, BATCH);
    }
  }
  while (option != 'q');
  std::cout << "\nHave a nice day." << '\n';
  return EXIT_SUCCESS;
}

void DisplayMenu()
{
  std::cout 
       << '\n'
       << "      x1, x2, x3 are Deque < " << vT << " > objects\n"
       << "  operators  = , ==, !=,  ................  [vect][op][vect]\n"
       << "  PushFront   (t) .......  1      PopFront    ()  .......  3\n"
       << "  PushBack    (t) .......  2      PopBack     ()  .......  4\n"
       << "  Empty       ()  .......  E      Size        ()  .......  S\n"
       << "  Front       ()  .......  A      Back        ()  .......  Z\n"
       << "  *I = Tval       .......  U      Clear       ()  .......  C\n"
       << "  I = x.Begin ()  .......  B      I = x.rBegin()  .......  R\n"
       << "  Display dequeue .......  D\n"
       << "  ++I  ..................  ++     --I  ..................  --\n"
       << "  *I  ...................  *      *I = t  ...............  *=t\n"
       << "  I[i]  .................  [i]    I[i] = t  .............  [i]=t\n"
       << "  x3 = x2 = x1 ..........  =\n"
       << "  Display this menu  ....  M\n"
       << "  Quit program  .........  Q\n"
       << '\n';
}

