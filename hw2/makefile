# makefile for Post Machine

home = /home/courses/cop4530p/LIB
cpp  = $(home)/cpp
tcpp = $(home)/tcpp
proj = .

incpath = -I$(cpp) -I$(tcpp) -I$(proj)

obj = main.o post.o xstring.o  

CC = g++47 -std=c++11 -Wall -Wextra

main:   $(obj)
	$(CC) -o post.x $(obj)

main.o: main.cpp post.h post.cpp
	$(CC) $(incpath)  -c main.cpp

post.o: post.h post.cpp $(cpp)/xstring.h
	$(CC) $(incpath)  -c post.cpp

xstring.o: $(cpp)/xstring.h $(cpp)/xstring.cpp
	$(CC) $(incpath)  -c $(cpp)/xstring.cpp
