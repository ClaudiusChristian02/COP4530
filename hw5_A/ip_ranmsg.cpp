/*
    ip_ranmsg.cpp
    04/04/15
    Chris Lacher

    creates simulated ip traffic packets
    associates with a given iptable

    Copyright 2015, R.C. Lacher
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdint>

#include <xstring.h>
#include <iputil.h>
#include <xran.h>

/* // in lieu of makefile
#include <xstring.cpp>
#include <iputil.cpp>
#include <xran.cpp>
// */

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cout << " ** program requires 3 arguments\n"
	      << "    1 = number of generated entries\n"
	      << "    2 = ipmap file\n"
	      << "    3 = output filename\n"
	      << " ** try again\n";
    exit(0);
  }

  std::cout << "Program generating simulated internet traffic\n";

  std::ifstream in1;
  std::ofstream out1;

  in1.open(argv[2]);
  if (in1.fail())
  {
    std::cout << " ** Unable to open file " << argv[2] << '\n'
	      << " ** program closing\n";
    exit(0);
  }

  out1.open(argv[3]);
  if (out1.fail())
  {
    std::cout << " ** Unable to open file " << argv[3] << '\n'
	      << " ** program closing\n";
    exit(0);
  }

  ipNumber ipn, netid, hostid;
  ipString ips;
  ipClass ipc;

  fsu::Vector<ipNumber> dest (0);
  in1 >> std::hex;
  while (in1 >> ipn >> netid) dest.PushBack(ipn);
  in1.clear();
  in1.close();
  // dest.SetCapacity(dest.Size());
  fsu::Random_uint32_t ranint;
  size_t num = atoi(argv[1]);
  size_t Acount(0), Bcount(0), Ccount(0), Dcount(0);

  std::cerr << std::uppercase << std::hex << std::setfill('0');
  // dest.Dump(std::cerr);
  for (size_t i = 0; i < num; ++i)
  {
    if (ranint(0,100) < 90) // use map entry
    {
      size_t index = ranint(0,dest.Size());
      ipn = dest[index];
      ipc = ipInterpret(ipn, netid, hostid);
      // std::cerr << "index = " << index << ", ipn = " << ipn << ", class = " << ipc << '\n';
      switch(ipc)
      {
        case classA: ++ Acount; break;
        case classB: ++ Bcount; break;
        case classC: ++ Ccount; break;
        case badClass: ++Dcount;
          std::cerr << " ** bad ipnumber " << ipn << " found in " << argv[2] << '\n';
          break;
      }
    }
    else
    {
      ipn = ranint();
      ipc = ipInterpret(ipn, netid, hostid);
      switch(ipc)
      {
        case classA: ++ Acount; break;
        case classB: ++ Bcount; break;
        case classC: ++ Ccount; break;
        case badClass: ++ Dcount; break;
      }
    }
    out1 << ipN2ipS(ipn) << '\t' << "packet_" << ipc << '_';
    switch(ipc)
      {
        case classA:   out1 << Acount; break;
        case classB:   out1 << Bcount; break;
        case classC:   out1 << Ccount; break;
        case badClass: out1 << Dcount; break;
      }
    out1 << '\n';
  }

  // close outfile
  out1.close();

  // terminate program
  std::cout << "File of ip messages:\n"
	    << " filename: " << argv[3] << '\n'
	    << "    count: " << num << '\n';
  return 0;
}
