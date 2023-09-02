/**********************************************************
//
//    NAME:		Andrew Lin
//
//    HOMEWORK:		project1
//
//    CLASS:		ICS 212
//
//    INSTRUCTOR:	Ravi Narayan
//
//    DATE:		March 29, 2022
//
//    FILE:		database.h
//
//    DESCRIPTION: header file with functions to access the database
//
**********************************************************/

#ifndef DATABASE_H
#define DATABASE_H
#include "record.h"

extern int debugmode;

void addRecord (struct record **, int, char [], char []);
void printAllRecords (struct record *);
int findRecord (struct record *, int);
int deleteRecord (struct record **, int);
int writefile (struct record *, char []);
int readfile (struct record **, char []);
void cleanup (struct record **);

#endif
