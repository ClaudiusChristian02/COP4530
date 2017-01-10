/*   file: main.cpp

     Driver program -- simulates the life of a soda machine
*/

#include <iostream>      // std::cout
#include <stdlib.h>      // exit()
#include <machine.h>     // part of simulation
#include <user.h>        // part of simulation

int main()
{
   soda_machine   the_machine;        // Initialize a machine
   user           the_user;           // Initialize a user
   service_person the_service_person; // Initialize a service person
   
   char cmd;      // user input
   while(1)       // exit through case 'X'
   {
      cmd = the_user.get_command();
      switch(cmd)
      {
         case 'X':
            std::cout << "\nSimulation over -- have a nice day.\n";
            exit(1);
         case 'S': 
            the_service_person.inventory(the_machine); 
            break;
         default:
            the_machine.do_command(cmd);
      }  // end switch
   }  // end while
   return 0;
}  // end main()
