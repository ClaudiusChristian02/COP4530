#include "post.h"
#include <fstream>
#include <iostream>
using namespace std;

PostMachine::PostMachine(){
	cout << "** Post machine started. \n";

}

PostMachine::~PostMachine(){

	cout << "** Post machine stopped. \n";

}

bool PostMachine::Load(){
	string Filename,
		   command;

	program_.Clear();

	cout << "Name of instruction file: ";
	getline(cin, Filename);

	ifstream file(Filename);


	if (!file){
		cout << "Cannot open file '" << Filename << "' . Check name and try again. \n";

		return false;
	}

	while (getline(file, command)){

		if (command == "*"){

			break;
		}

		if (command[0] == '*'){

			continue;
		}

		if (command == ""){

			continue;
		}

		program_.PushBack(command);

	} // end of while (file >> command)

	return true;

} // end of PostMachine::Load()

void PostMachine::Run()
{
	char ch;
	bool finished, halt, crash, maxits_reached, match;
	size_t its;
	string userInput,
		command;
	int maxIterations = 10000;

	// loop until '*' is received as (first character of) input
	while (1)
	{
		tape_.clear();

		cout << "Input string (* to end): ";
		getline(cin, userInput);

		if (userInput == "*"){

			return;
		}

		writeToTape(userInput);

		tape_.push('#');

				// run Post machine
		state_ = 'S'; // set state to start
					
				finished = halt = crash = maxits_reached = 0;
		its = 0;
		do
		{
			match = 0;

			for (List<string>::Iterator i = program_.Begin(); i != program_.End(); ++i){

				command = *i;

				if ((command[0] == state_) && (command[1] == tape_.front())){

					tape_.pop();

					state_ = command[2];

					writeToTape(command.substr(3));

					match = 1;

				} // end of if ((command[0] == state) && (command[1] == tape.front()))
			}
			++its;
			halt = (state_ == 'H');
			crash = !match;
			maxits_reached = (its == maxIterations);
			finished = halt || crash || maxits_reached;

		} while (!finished);
			

		// report result of computation
		if (halt)
		{
			cout << "String accepted. \n";
			cout << "Tape contents at halt: ";
			writeTapeContents();
			cout << endl;
		}
		else if (crash)
		{
			cout << "String rejected. \n";
			cout << "Last State: " << state_ << endl;
			cout << "Tape contents at rejection: ";
			writeTapeContents();
			cout << endl;

		}
		else if (maxits_reached)
		{
			cout << "Machine stopped after '" << maxIterations << "' iterations. \n";
			cout << "Tape contents when stopped: ";
			writeTapeContents();
			cout << endl;
			cout << "Last State: " << state_ << endl;
		}
		else // presumed unreachable branch 
		{
			std::cerr << "** PostMachine error: bad processing termination\n";
		}
	} // end while(1)
} // end PostMachine::Run()

void PostMachine::writeToTape(const string& s){
	
	for (int i = 0; i < s.size(); i++){

		tape_.push(s[i]);
	}
}

void PostMachine::writeTapeContents(){

	while (!tape_.empty()){

		cout << tape_.front();
		tape_.pop();
	}
}