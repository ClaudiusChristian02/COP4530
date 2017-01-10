/* file: machine.h

This file contains the declaration of the "machine" classes
soda_machine, change_counter, and can_dispenser, as well as the
"person" class service_person.

A soda_machine object is a manager that contains one change_counter
object and five can_dispenser objects (one for each brand of soda),
along with the price of a can of soda.

A coin_counter object keeps track of money before, during, and after a
customer attempts to buy a can of soda.

A can_dispenser object keeps track of the cans of soda (of one brand)
and dispenses them on command, when it is not sold out.

A service_person object is a friend of all of these classes and
reports private financial and inventory data.

NOTE: The soda machine simulation is based on ideas from "The Object
Concept" by Rick Decker and Stuart Hirshfield, PWS, Boston, 1995.
This is a fun book that we recommend for outside reading to students
after taking a first course in C or C++.

*/

#ifndef _MACHINE_H
#define _MACHINE_H

const int default_soda_price       = 75;   // price of one soda in cents
const int default_machine_bankroll = 100;  // default change amount in cents
const int default_dispenser_size   = 24;   // default dispenser size

class coin_counter
{
friend class service_person;

public:
   coin_counter(int machine_bankroll = default_machine_bankroll);
   // constructor
   // initialize a counter, setting available change
   // default parameters are constants at top of this file

   void accept_coin(int amt);
   // accept a coin input by user

   int current_amount();
   // report amount tendered so far during a transaction

   void take_all();
   // accept all coins in response to a sale

   void dispense_change(int amt);
   // return change, if possible

private:
   int amount_tendered; // the amount tendered during a transaction
   int in_bank;         // the amount available for making change
}  ;

class can_dispenser
{
friend class service_person;

public:
   can_dispenser(int dispenser_size = default_dispenser_size);
   // constructor
   // initialize a dispenser with number of cans = dispenser_size
   // default parameters are constants at top of this file

   int sale_attempt();
   // try to make a sale

private:
   int num_cans;   // the number of cans available
}  ;

class soda_machine
{
friend class service_person;

public:
   soda_machine(int soda_price = default_soda_price);
   // constructor
   // initialize a machine
   // default parameters are constants at top of this file

   void do_command(char cmd);
   // respond to a command from a customer

private:
   // a soda machine consists of:
   // -- one coin counter
   coin_counter counter;

   // -- five can dispensers
   can_dispenser cola, lite, root, orng, free;

   // -- and the price of a can of soda.
   int price;

   // a soda machine must manage
   // -- drink selection 
   void do_selection(char cmd);

   // -- and coin events
   void do_coin(char cmd);
}  ;

class service_person
{
public:
   service_person();
   // constructor 
   // sets cout for display of floats as money

   void inventory(soda_machine);
   // displays current amount of money and drinks in machine

private:
   int money(coin_counter);
   // returns amount of money in coin_counter

   int sodas(can_dispenser);
   // returns number of drinks in can_dispenser
}  ;

#endif
