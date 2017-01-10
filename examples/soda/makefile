# makefile for Soda Machine simulation

# This simulation is adapted from one of our favorite examples of object based
# programming, found in the excellent introductory text by 
# Rick Decker and Stuart Hirshfeld: "The Object Concept", Prindle Weber & Schmidt, publisher.

proj    = .
incpath =  -I$(proj)
obj     = main.o user.o machine.o
CC      = g++

soda_machine:   main.o user.o machine.o
	$(CC) $(incpath) -o soda_machine main.o user.o machine.o

main.o: $(proj)/user.h $(proj)/machine.h $(proj)/main.cpp
	$(CC) $(incpath) -c $(proj)/main.cpp

user.o: $(proj)/user.h $(proj)/user.cpp
	$(CC) $(incpath) -c $(proj)/user.cpp

machine.o: $(proj)/machine.h $(proj)/machine.cpp
	$(CC) $(incpath) -c $(proj)/machine.cpp
