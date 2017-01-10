home    = /home/courses/cop4530p/LIB
cpp     = $(home)/cpp
tcpp    = $(home)/tcpp
tests   = $(home)/tests
proj    = .
incpath = -I$(proj) -I$(cpp) -I$(tcpp)
CC      = g++47 -std=c++11 -Wall -Wextra -g

project: ws2.x foaa.x

foaa.x : $(proj)/foaa.cpp $(proj)/oaa.h
	$(CC) $(incpath) -o foaa.x $(proj)/foaa.cpp

ws2.x:   main2.o xstring.o wordsmith2.o
	$(CC) -o ws2.x main2.o xstring.o wordsmith2.o

main2.o: $(proj)/wordsmith2.h $(proj)/main2.cpp
	$(CC) $(incpath)  -c $(proj)/main2.cpp

wordsmith2.o: $(proj)/wordsmith2.h $(proj)/wordsmith2.cpp
	$(CC) $(incpath)  -c wordsmith2.cpp

xstring.o: $(cpp)/xstring.h $(cpp)/xstring.cpp
	$(CC) $(incpath)  -c $(cpp)/xstring.cpp
