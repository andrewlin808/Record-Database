project: user_interface.o llist.o
	g++ -o project user_interface.o llist.o

user_interface.o: user_interface.cpp llist.h
	g++ -ansi -pedantic-errors -Wall -c user_interface.cpp

llist.o: llist.cpp llist.h record.h
	g++ -ansi -pedantic-errors -Wall -c llist.cpp
