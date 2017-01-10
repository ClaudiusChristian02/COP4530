/*
    ipmain.cpp
    03/29/15

    Router controller
*/

#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>

#include <xstring.h>
#include <iprouter.h>

/* // in lieu of makefile
#include <xstring.cpp>
#include <bitvect.cpp>
#include <hashfunctions.cpp>
#include <primes.cpp>
#include <iprouter.cpp>
// */

typedef fsu::String ipString;
const size_t maxFilenameSize = 81;

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

  size_t numBuckets;
  std::cout << "\nRouter control program started\n";
  std::cout << "  Enter approximate number of entries for RouteTable: ";
  *inptr >> numBuckets;
  if (BATCH) std::cout << numBuckets << '\n';
  if (numBuckets == 0)
    return 0;

  Router router (numBuckets);
  char file1 [maxFilenameSize], file2 [maxFilenameSize];
  char selection;

  ipString dS,   // destination (dot notation)
           rS;   // route       (dot notation)


  if (!BATCH) DisplayMenu();
  do
  {
    std::cout << "Enter Router Command ('M' for menu, 'Q' to quit): ";
    *inptr >> selection;
    if (BATCH) std::cout << selection << '\n';
    switch (selection)
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
	selection = 'q';
	break;

      case 'l': case 'L':
        std::cout << "  Enter table file name: ";
        *inptr >> std::setw(maxFilenameSize) >> file1;
	if (BATCH) std::cout << file1 << '\n';
        router.Load(file1);
        break;

      case 's': case 'S':
        std::cout << "  Enter table file name: ";
        *inptr >> std::setw(maxFilenameSize) >> file1;
	if (BATCH) std::cout << file1 << '\n';
        router.Save(file1);
        break;

      case 'i': case 'I':
        std::cout << "  Enter destination and route (dot notation): ";
        *inptr >> dS >> rS;
	if (BATCH) std::cout << dS << ' ' << rS << '\n';
        router.Insert(dS, rS);
        break;

      case 'v': case 'V':
        std::cout << "  Enter destination and route (dot notation): ";
        *inptr >> dS >> rS;
	if (BATCH) std::cout << dS << ' ' << rS << '\n';
        router.Insert(dS, rS, 1);
        break;

      case 'r': case 'R':
        std::cout << "  Enter destination (dot notation): ";
        *inptr >> dS;
	if (BATCH) std::cout << dS << '\n';
        router.Remove(dS);
        break;

      case 'g': case 'G':
        std::cout << "                  Enter msg file name: ";
        *inptr >> std::setw(maxFilenameSize) >> file1;
	if (BATCH) std::cout << file1 << '\n';
        std::cout << "  Enter log file name (0 for default): ";
        *inptr >> std::setw(maxFilenameSize) >> file2;
	if (BATCH) std::cout << file2 << '\n';
        if (file2[0] =='0')
          router.Go(file1, nullptr);
        else
          router.Go(file1, file2);
        break;

      case 'c': case 'C':
        router.Clear();
        break;

      case 'd': case 'D':
        std::cout << "  Enter Dump file name (0 for default): ";
        *inptr >> std::setw(maxFilenameSize) >> file1;
	if (BATCH) std::cout << file1 << '\n';
        if (file1[0] == '0')
          router.Dump(0);
        else
          router.Dump(file1);
        break;

      case 'a': case 'A':
	router.Analysis();
	break;

      case 'h': case 'H':
        std::cout << "  Enter new table size estimate (0 for default): ";
        std::cin >> numBuckets;
	router.Rehash(numBuckets);
	break;

      case 'm': case 'M':
        DisplayMenu();
        break;

      default:
        std::cout << "  Try again\n";
    }
  }
  while (selection != 'q');
  std::cout << "\nRouter control program stopped\n";
  return 1;
} // end main()

void DisplayMenu()
{
   std::cout << '\n'
             << "  method     (arguments)              command\n"
             << "  ------     -----------              -------\n"
             << "  Load       (filename) ..................  L\n"
             << "  Save       (filename) ..................  S\n"
             << "  Insert     (ipS, ipS, verify = 0) ......  I\n"
             << "  Insert     (ipS, ipS, verify = 1) ......  V\n"
             << "  Remove     (ipS) .......................  R\n"
             << "  Go         (msg_file, log_file) ........  G\n"
             << "  Clear      () ..........................  C\n"
	     << "  Analysis   () ..........................  A\n"
	     << "  Rehash     () ..........................  H\n"
             << "  Dump       () ..........................  D\n"
             << "  Display menu ...........................  M\n"
             << "  Switch to interactive mode .............  X\n"
             << "  Quit program ...........................  Q\n"
             << std::endl;
}
