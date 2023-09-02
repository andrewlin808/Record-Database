/************************************************
//
//  NAME:	Andrew Lin
//
//  HOMEWORK:	project2
//
//  CLASS:	ICS 212
//
//  INSTRUCTOR:	Ravi Narayan
//
//  DATE:	April 24, 2022
//
//  FILE:	llist.h
//
//  DESCRIPTION:
//   Class definition of 'llist'
************************************************/

#ifndef LLIST_H
#define LLIST_H
#include <ostream>
#include "record.h"

using namespace std;

class llist
{
private:
    record *	start;
    char	filename[20];
    int		readfile();
    int		writefile();
    void	cleanup();

public:
    llist();
    llist(char[]);
    llist(const llist&);
    llist& operator=(const llist&);
    friend ostream& operator<<(ostream&, const llist&);
    ~llist();
    void addRecord(int, char[], char[]);
    int findRecord(int);
    void printAllRecords();
    int deleteRecord(int);
};

#endif
