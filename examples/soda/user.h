/*
   file: user.h 

   Declaration of the class user for the soda machine simulation.
   User object responsibilities are to get a legal command character
   from the keyboard, to respond to two of these (displaying the menu,
   and exiting the simulation) and return the others to the calling
   process.

   NOTE: The soda machine simulation is based on ideas from "The Object
   Concept" by Rick Decker and Stuart Hirshfield, PWS, Boston, 1995.
*/

#ifndef _USER_H
#define _USER_H

class user
{
public:
   user();  // Constructor -- initialize a user object
            // by displaying a banner and showing the menu
   char get_command();     // Return a legal char 
private:
   void show_menu();       // Show the available choices
   int is_legal(char cmd); // Return 1 if cmd is legal, 0 otherwise
}  ;

#endif
