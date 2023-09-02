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
//  FILE:	record.h
//
//  DESCRIPTION:
//   Structure definition of 'record'
************************************************/

#ifndef RECORD_H
#define RECORD_H

struct record
{
    int	                accountno;
    char                name[30];
    char                address[50];
    struct record*      next;
};

#endif
