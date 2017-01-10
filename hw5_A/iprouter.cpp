/*
    iprouter.cpp
    <date>
    <Claudius christian>

    <file doc> 

*/

#include <fstream>
#include <iomanip>
#include <cstring>
#include <iprouter.h>


void Router::Insert(const ipString& dS, const ipString& rS, bool verify)
{
  // TBS
  ipNumber dN = ipS2ipN(dS);
  ipNumber rN = ipS2ipN(rS);

  // checks with ip iterpret to see if A,B,C network. if it is a bad netowrk
  // do not insert
  if (verify){

	  ipNumber netID, hostID;

	  if (ipInterpret(dN, netID, hostID) == badClass){

		  return;
	  }

	  if (ipInterpret(rN, netID, hostID) == badClass){

		  return;
	  }
  }

  tablePtr_->Insert(dN, rN);


}

void Router::Remove (const ipString& dS)
{
  // TBS
  ipNumber dN = ipS2ipN(dS);

  tablePtr_->Remove(dN);
}

void Router::Go (const char* msgfile, const char* logfile)
{
  std::cout << "  Router simulation started\n";
  std::ifstream fin;

  fin.open(msgfile);
  if (fin.fail())
  {
    std::cerr << "** Router: unable to open msg file " << msgfile << '\n'
              << "   Go() aborted\n";
    return;
  }
  fin >> std::hex;

  std::ofstream fout;
  std::ostream * optr = &std::cout;

  if (logfile != nullptr)
  {
    fout.open(logfile);
    if (fout.fail())
    {
      std::cerr << "** Router: unable to open log file " << logfile << '\n'
                << "   Go() aborted\n";
      return;
    }
    optr = &fout;
  }

  ipClass ipC;
  ipString dS;
  ipNumber dN, rN, netID, hostID;
  fsu::String msgID;
  size_t packets(0);
  (*optr) << std::hex << std::uppercase;
  fin >> dS >> msgID;
  while (!fin.fail())
  {
    ++packets;

    // TBS
	dN = ipS2ipN(dS);

	// assigns ip class to ipc
	ipC = ipInterpret(dN, netID, hostID);

	// 
	if (ipC != badClass){

		// looks into the hashtable and determines if there
		// is a destination value
		if (tablePtr_->Retrieve(dN, rN)){

			ipC = ipInterpret(rN, netID, hostID);

			(*optr) << "msgID: " << std::setfill(' ') << std::setw(5) << msgID << " dest: " << std::setfill('0') << std::setw(8) << dN << " route class: " << ipC << " netID: " << std::setfill('0') << std::setw(8) << netID << " hostID: " << std::setfill('0') << std::setw(8) << hostID << std::endl;
		}
		else{

			(*optr) << "msgID: " << std::setfill(' ')  << std::setw(5) << msgID << " dest: " << std::setfill('0') << std::setw(8) << dN << " NOT ROUTED -- NO TABLE ENTRY\n";

		}
	}

	else{

		(*optr) << "msgID: " << std::setfill(' ')  << std::setw(5) << msgID << " dest: " << std::setfill('0') << std::setw(8) << dN << " NOT ROUTED -- BAD IP CLASS\n";
	}

    fin >> dS >> msgID;
  } // end while()
  fin.close();
  if (logfile == nullptr)
  {
    // set cout back to normal
    std::cout << std::dec << std::setfill(' ');
  }
  else
  {
    // close the log file
    fout.clear();
    fout.close();
  }
  std::cout << "    " << packets << " packets processed\n";
  std::cout << "  Router simulation stopped\n";
  return;
} // end Router::Go()

void Router::Clear(){

	tablePtr_->Clear();

}

// ***********************************************
// below this sign should not require modification
// ***********************************************

Router::Router  (size_t sizeEstimate) : tablePtr_(0)
{
  ipHash iph;
  tablePtr_ = new TableType  (sizeEstimate, iph);
}

Router::~Router ()
{
  delete tablePtr_;
}

void Router::Load (const char* loadfile)
{
  std::ifstream in1;
  in1.open (loadfile);
  if (in1.fail())
  {
    std::cerr << "** Router: unable to open file " << loadfile << '\n'
              << "   Load() aborted\n";
    return;
  }
  in1 >> std::hex;
  EntryType::KeyType key;
  EntryType::DataType data;
  while (in1 >> key)
  {
    in1 >> data;
    tablePtr_->Insert(key, data);
  }
  in1.close();
  std::cout << "  Load() completed\n";
} // end Router::Load()

void Router::Save (const char* savefile)
{
  std::ofstream out1;
  out1.open (savefile);
  if (out1.fail())
  {
    std::cerr << "** Router: unable to open file " << savefile << '\n'
              << "   Save() aborted\n";
    return;
  }

  TableType::Iterator i;
  out1 << std::uppercase << std::hex << std::setfill('0');
  for (i = tablePtr_->Begin(); i != tablePtr_->End(); ++i)
  {
    out1 << std::setw(8) << (*i).key_ << ' ' << std::setw(8) << (*i).data_ << '\n';
  }
  out1.close();
  std::cout << "  Save() completed\n";
} // end Router::Save()

void Router::Dump(const char* dumpfile)
{
  if (dumpfile == 0)
  {
    std::cout.setf(std::ios::uppercase);
    std::cout << "\nSize(): " << std::dec << tablePtr_->Size() << std::hex
              << "\nDump():\n";
    std::cout.fill('0');
    tablePtr_->Dump(std::cout,8,8);
    std::cout.fill(' ');
    std::cout.setf(std::ios::dec, std::ios::basefield);
  }

  else
  {
    std::ofstream out1;
    out1.open(dumpfile);
    if (out1.fail())
    {
      std::cerr << "** Router: failure to open dump file " << dumpfile << '\n'
                << "   Dump() aborted\n";
      return;
    }
    out1.setf(std::ios::uppercase);
    out1 << "\nSize(): " << std::dec << tablePtr_->Size() << std::hex
         << "\nDump():\n";

    out1.fill('0');
    tablePtr_->Dump(out1,8,8);
    out1.close();
  }
} // end Router::Dump()

void Router::Analysis()
{
  tablePtr_->Analysis(std::cout);
}

void Router::Rehash(size_t numBuckets)
{
  tablePtr_->Rehash(numBuckets);
}

size_t ipHash::operator () (const ipNumber& ipn) const
{
  return hashfunction::KISS (ipn);
}

