/* file: machine.cpp

This file contains implementations of member functions for the classes
coin_counter, can_dispenser, soda_machine, and service_person.

NOTE: The soda machine simulation is based on ideas from "The Object
Concept" by Rick Decker and Stuart Hirshfield, PWS, Boston, 1995.
This is a fun book that we recommend for outside reading to students
after taking COP 2000.  (This is the text for our class "Object
Oriented Programming in C++" for non-majors.  CS majors cannot receive
credit for this class.)  The book is available in the FSU book store.

*/

#include <iostream>
#include <machine.h>

/*-----------------------------------------------------------------*/
/* implementations of coin_counter member functions                */
/*-----------------------------------------------------------------*/

coin_counter::coin_counter(int machine_bankroll)
// initialize a counter, setting available change
{
   amount_tendered = 0;
   in_bank = machine_bankroll;
   return;
}  // end coin_counter::coin_counter()

int coin_counter::current_amount()
// report amount tendered so far
{
   return amount_tendered;
}  // end coin_counter::current_amount()

void coin_counter::accept_coin(int amt)
// handle coin insertion
{
   amount_tendered += amt;
   return;
}  // end coin_counter::accept_coin()

void coin_counter::take_all()
// respond to a sale by taking in all coins so far tendered
{
   in_bank += amount_tendered;
   amount_tendered = 0;
   return;
}  // end coin_counter::take_all()

void coin_counter::dispense_change(int amt)
// return change, if possible
{
   if (in_bank >= amt)
   {
      std::cout << "*** CHANGE RETURNED: " << amt << " cents\n";
      in_bank -= amt;
   }  // end if
   else
      std::cout << "*** EXACT CHANGE ONLY from now on\n";
   return;
}  // end coin_counter::dispense_change()

/*-----------------------------------------------------------------*/
/* implementations of can_dispenser member functions               */
/*-----------------------------------------------------------------*/

can_dispenser::can_dispenser(int dispenser_size)
// initialize a dispenser
{
   num_cans = dispenser_size;
   return;
}  // can_dispenser::can_dispenser()

int can_dispenser::sale_attempt()
// respond to a button push
// return 0 if no cans left, return 1 if successful sale
{
   if (num_cans == 0)    // no cans left
   {
      std::cout << "*** SELECTION EMPTY -- please make another selection\n";
      return 0;
   }  // end if
   else                  // success, make sale and decrement num_cans
   {
      num_cans--;
      std::cout << "*** SALE COMPLETE\n";
      return 1;
   }  // end else
}  // end can_dispenser::sale_attempt()

/*-----------------------------------------------------------------*/
/* implementations of soda_machine member functions                */
/*-----------------------------------------------------------------*/

soda_machine::soda_machine(int soda_price)
// Initialize a soda_machine object and set the price of sodas.  
// Note that this automatically initializes a coin counter and the 
// can dispensers (implicitly, through their constructors).
{
   price = soda_price;
   return;
}  // end soda_machine::soda_machine()

void soda_machine::do_command(char cmd)
// get a legal character (Q, D, N, R, C, L, B, O, F) and send
// the appropriate message to either the coin counter or a dispenser.
{
   if ((cmd == 'Q') || (cmd == 'D') || (cmd == 'N') || (cmd == 'R'))
      do_coin(cmd);
   else
      do_selection(cmd);
   return;
}  // end soda_machine::do_command()

void soda_machine::do_coin(char cmd)
// respond to a coin insertion or a request to return all coins tendered
{
   int tendered;
   switch(cmd)
   {
      case 'R' : // Return amount tendered
               tendered = counter.current_amount();
               counter.take_all();
               counter.dispense_change(tendered);
               break;
      case 'Q' : counter.accept_coin(25);   break;
      case 'D' : counter.accept_coin(10);   break;
      case 'N' : counter.accept_coin(5);    break;
   }  // end switch
   return;
}  // end soda_machine::do_coin()

void soda_machine::do_selection(char cmd)
// Respond to a dispenser button push by determining if there is 
// enough money inserted to make a sale.  If so, send a request
// to make a sale, else do nothing.
{
   int success;  // 1, if a successful sale, 0 otherwise
   int tendered; // amount inserted so far by customer

   tendered = counter.current_amount();
   if (tendered < price)
      std::cout << "*** INSUFFICIENT FUNDS -- Please insert more money\n";
   else
   {
      switch(cmd)               // send sale message to a dispenser
      {
         case 'C' : success = cola.sale_attempt();  break;
         case 'L' : success = lite.sale_attempt();  break;
         case 'B' : success = root.sale_attempt();  break;
         case 'O' : success = orng.sale_attempt();  break;
         case 'F' : success = free.sale_attempt();  break;
      }  // end switch
   
      if (success)      // dispenser signalled a successful sale
      {
         counter.take_all();         // take the money
         if (tendered > price)       // and make change if needed
            counter.dispense_change(tendered - price);
      }  // end if
   }  // end else
   return;
}  // end soda_machine::do_selection()

/*-----------------------------------------------------------------*/
/* implementations of service_person member functions              */
/*-----------------------------------------------------------------*/

service_person::service_person()
// constructor
// sets std::cout for display of floats as money
{
   std::cout.setf(std::ios::fixed);
   std::cout.setf(std::ios::showpoint);
   std::cout.precision(2);
   return;
}  // end service_person::service_person()

void service_person::inventory(soda_machine machine)
// displays current amount of money and drinks in machine
{
   std::cout << '\n'
	     << "Money on hold:   $"
	     << (float(machine.counter.current_amount()) / 100.0)
	     << '\n'
	     << "Money in bank:   $"
	     << (float(money(machine.counter)) / 100.0)
	     << '\n'
	     << "Drink inventory  C: " << sodas(machine.cola) << '\n'
	     << "                 L: " << sodas(machine.lite) << '\n'
	     << "                 B: " << sodas(machine.root) << '\n'
	     << "                 O: " << sodas(machine.orng) << '\n'
	     << "                 F: " << sodas(machine.free) << "\n\n";
   return;
}  // end service_person::inventory()

int service_person::money(coin_counter counter)
// return amount of money available (in dollars)
{
   return(counter.in_bank);
}  // end service_person::money()

int service_person::sodas(can_dispenser dispenser)
// return supply of each drinks
{
   return(dispenser.num_cans);
}  // end service_person::sodas()

