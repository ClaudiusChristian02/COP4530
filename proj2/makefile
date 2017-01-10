#
# master makefile builds all tests and tools for BST::Iterator project
#

LIB  = /home/courses/cop4530p/LIB
CPP  = $(LIB)/cpp
TCPP = $(LIB)/tcpp

BST_BASE_H = $(TCPP)/bst_base.h

CC   = g++47 -std=c++11 -Wall -Wextra -I. -I$(CPP) -I$(TCPP)

all:           bst_adt bst_threaded rbllt_adt tools

bst_adt:       fbst_adt_int.x  fbst_adt_String.x  fbst_adt_CHAR.x \
               mbst_adt_int.x  mbst_adt_String.x 

bst_threaded:  fbst_threaded_int.x  fbst_threaded_String.x  fbst_threaded_CHAR.x \
               mbst_threaded_int.x  mbst_threaded_String.x 

rbllt_adt:     frbllt_adt_int.x  frbllt_adt_String.x  frbllt_adt_CHAR.x \
               mrbllt_adt_int.x  mrbllt_adt_String.x

tools:         ranuint.x ranstring.x


fbst_adt_String.x: $(BST_BASE_H) bst_adt.h bt2iter.h fbst_adt_String.cpp
	$(CC) -ofbst_adt_String.x fbst_adt_String.cpp

fbst_adt_int.x: $(BST_BASE_H) bst_adt.h bt2iter.h fbst_adt_int.cpp
	$(CC) -ofbst_adt_int.x fbst_adt_int.cpp

fbst_adt_CHAR.x: $(BST_BASE_H) bst_adt.h bt2iter.h fbst_adt_CHAR.cpp
	$(CC) -ofbst_adt_CHAR.x fbst_adt_CHAR.cpp

mbst_adt_String.x: $(BST_BASE_H) bst_adt.h bt2iter.h mbst_adt_String.cpp
	$(CC) -ombst_adt_String.x mbst_adt_String.cpp

mbst_adt_int.x: $(BST_BASE_H) bst_adt.h bt2iter.h mbst_adt_int.cpp
	$(CC) -ombst_adt_int.x mbst_adt_int.cpp

fbst_threaded_String.x: $(BST_BASE_H) bst_adt.h bst_threaded.h bt2iter.h fbst_threaded_String.cpp
	$(CC) -ofbst_threaded_String.x fbst_threaded_String.cpp
fbst_threaded_int.x: $(BST_BASE_H) bst_adt.h bst_threaded.h bt2iter.h fbst_threaded_int.cpp
	$(CC) -ofbst_threaded_int.x fbst_threaded_int.cpp
fbst_threaded_CHAR.x: $(BST_BASE_H) bst_adt.h bst_threaded.h bt2iter.h fbst_threaded_CHAR.cpp
	$(CC) -ofbst_threaded_CHAR.x fbst_threaded_CHAR.cpp
mbst_threaded_String.x: $(BST_BASE_H) bst_adt.h bst_threaded.h bt2iter.h mbst_threaded_String.cpp
	$(CC) -ombst_threaded_String.x mbst_threaded_String.cpp
mbst_threaded_int.x: $(BST_BASE_H) bst_adt.h bst_threaded.h bt2iter.h mbst_threaded_int.cpp
	$(CC) -ombst_threaded_int.x mbst_threaded_int.cpp

frbllt_adt_String.x: $(BST_BASE_H) bst_adt.h rbllt_adt.h bt2iter.h frbllt_adt_String.cpp
	$(CC) -ofrbllt_adt_String.x frbllt_adt_String.cpp
frbllt_adt_int.x: $(BST_BASE_H) bst_adt.h rbllt_adt.h bt2iter.h frbllt_adt_int.cpp
	$(CC) -ofrbllt_adt_int.x frbllt_adt_int.cpp
frbllt_adt_CHAR.x: $(BST_BASE_H) bst_adt.h rbllt_adt.h bt2iter.h frbllt_adt_CHAR.cpp
	$(CC) -ofrbllt_adt_CHAR.x frbllt_adt_CHAR.cpp
mrbllt_adt_String.x: $(BST_BASE_H) bst_adt.h rbllt_adt.h bt2iter.h mrbllt_adt_String.cpp
	$(CC) -omrbllt_adt_String.x mrbllt_adt_String.cpp
mrbllt_adt_int.x: $(BST_BASE_H) bst_adt.h rbllt_adt.h bt2iter.h mrbllt_adt_int.cpp
	$(CC) -omrbllt_adt_int.x mrbllt_adt_int.cpp

ranuint.x: ranuint.cpp
	$(CC) -oranuint.x ranuint.cpp
ranstring.x: ranstring.cpp
	$(CC) -oranstring.x ranstring.cpp
