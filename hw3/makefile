home    = /home/courses/cop4530p/LIB
cpp     = $(home)/cpp
tcpp    = $(home)/tcpp
tests   = $(home)/tests
proj    = .
incpath = -I$(proj) -I$(cpp) -I$(tcpp)
CC      = g++47 -std=c++11 -Wall -Wextra

project: ws.x

ws.x:   main.o xstring.o wordsmith.o
	$(CC) -o ws.x main.o xstring.o wordsmith.o

main.o: $(proj)/wordsmith.h $(proj)/main.cpp
	$(CC) $(incpath)  -c $(proj)/main.cpp

wordsmith.o: $(proj)/wordsmith.h $(proj)/wordsmith.cpp
	$(CC) $(incpath)  -c wordsmith.cpp

xstring.o: $(cpp)/xstring.h $(cpp)/xstring.cpp
	$(CC) $(incpath)  -c $(cpp)/xstring.cpp
