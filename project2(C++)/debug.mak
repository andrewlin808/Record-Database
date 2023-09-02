project_debug: user_interface.o llist.o
	g++ -o project_debug user_interface.o llist.o

user_interface.o: user_interface.cpp llist.h
	g++ -ansi -pedantic-errors -Wall -DDEBUG -c user_interface.cpp

llist.o: llist.cpp llist.h record.h
	g++ -ansi -pedantic-errors -Wall -DDEBUG -c llist.cpp
