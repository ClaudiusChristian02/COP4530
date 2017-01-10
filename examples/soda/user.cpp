/*
   file: user.cpp 

   Implementations of the member functions for the class defined in user.h
*/

#include <iostream>     // for std::cin, std::cout
#include <ctype.h>      // for toupper ()
#include <machine.h>
#include <user.h>

user::user() 
// constructor -- called at time of declaration
// Initialize by displaying the program header and then the menu
{
   std::cout << "\n\n                    SODA MACHINE\n\n"
	     << "Welcome to the Soda Machine simulation.  You will play three\n"
	     << "roles: the Customer, the Service Person, and the Simulation\n"
	     << "Controller.  As the Customer, you will be inserting coins,\n"
	     << "selecting sodas, and getting change.  As the Service Person,\n"
	     << "you will be examining the machine contents (money and\n"
	     << "sodas).  As the Simulation Controller, you will decide when\n"
	     << "the simulation is over. All roles are played using the menu.\n\n"
	     << "Price of one soda: $0." << default_soda_price << ".\n";
   show_menu();
   return;
}  // end user::user()

char user::get_command()
// Get a char from KB and send the char back to main.
// NOTE: if the command was 'M', just show the menu without returning.
{
   char cmd;    // the command character entered by the user
	
   while (1)    // Keep trying until we get a legal command.
   {
      std::cout << "Make a selection (enter 'M' to see menu): ";
      std::cin >> cmd;
      cmd = toupper(cmd);  
      if (is_legal(cmd))  // We got a legal command
      {
         if (cmd == 'M')    // If it's 'M' 
            show_menu();       // show the menu and stay in the loop
         else               // Otherwise just send it back
            return cmd;        // and break out of the loop (only way out)
      }  // end if
      else               // We got an illegal - notify user, stay in the loop
         std::cout << "          *** Unrecognized command.\n";
   }  // end while
}  // end user::get_command()

int user::is_legal(char cmd)
// Return 1 if cmd is one that we can handle, else return 0.
{
   return ((cmd == 'Q') || (cmd == 'D') || (cmd == 'N') || (cmd == 'R') ||
           (cmd == 'C') || (cmd == 'L') || (cmd == 'B') || (cmd == 'O') ||
           (cmd == 'F') || (cmd == 'M') || (cmd == 'S') || (cmd == 'X'));
}  // end user::is_legal()

void user::show_menu()
// display the menu
{
std::cout << '\n'
	  << "Coin Slot             Drink Buttons        Other\n"
	  << "---------             -------------        -----\n"
	  << "Q = insert quarter    C = cola             M = display this menu\n"
	  << "D = insert dime       L = cola lite        S = display machine state\n"
	  << "N = insert nickel     B = root beer        X = exit simulation\n"
	  << "R = coin return       O = orange\n"
	  << "                      F = caffein free\n\n";
   return;
}  // end user::show_menu()

