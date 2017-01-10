#ifndef POST_H
#define POST_H
#include <string>
#include "list.h"
#include "queue.h"
using namespace fsu;
using namespace std;



class PostMachine{

public:


	//PostMachine();         // constructor
	//~PostMachine();        // destructor
	bool Load();
	void Run();
	void writeToTape(const string& s);
	void writeTapeContents();



private:
	char state_;
	List <string> instructions;
	queue < char > tape;




	
	

}; // end of class post

#endif