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
//  FILE:	user_interface.cpp
//
//  DESCRIPTION:
//    Source file of the user interface
************************************************/

#include <iostream>
#include <sstream>
#include <cstring>
#include "llist.h"

void getaddress( char[], int );
int getaccountnum();

using namespace std;

int main(int argc, char *argv[])
{  
    char filename[] = "records.txt";
    llist mylist(filename);
    int exit, ilength, accountnum;
    string input;
    char uaddress[50], uname[30];

    #ifdef DEBUG
        cout << "\n***** PROJECT_DEBUG *****" << endl;
    #endif

    cout << "\nWelcome! You have entered the user interface for managing customer's banking records\n" << endl;

    exit = 0;
    while (exit == 0)
    {
        cout << "\nSelect one of the options below:\n";
        cout << "add: add a new customer record\n";
        cout << "printall: print all existing record(s)\n";
        cout << "find: find record(s) of an existing customer\n";
        cout << "delete: delete record(s) of an existing customer\n";
        cout << "quit: exit the program\n";
        cout << "Awaiting input..." << endl;

        getline ( cin, input );
        ilength = input.length();
        if (ilength == 0)
        {
            cout << "\nINVALID OPTION!" << endl;
        }
        else if (ilength <= 3 && input.compare ( 0, ilength, "add", ilength ) == 0 )
        {
            /* addRecord() */
            cout << "\nAdd a new record:" << endl;

            accountnum = getaccountnum();

            cout << "\nEnter the account name: " << endl;
            getline ( cin, input );
            strcpy(uname, input.c_str());
            
            getaddress ( uaddress, sizeof(uaddress) );

            cout << "\nAdding a new record to database..." << endl;
            mylist.addRecord( accountnum, uname, uaddress );
            cout << "\nRecord with account #" << accountnum << " has been added" << endl;
        }
        else if (ilength <= 8 && input.compare ( 0, ilength, "printall", ilength) == 0)
        {
            /* printallRecord() */
            cout << "\nPrinting all records..." << endl;
            mylist.printAllRecords();
        }
        else if (ilength <= 4 && input.compare ( 0, ilength, "find", ilength) == 0)
        {
            /* findRecord() */
            cout << "\nFind record(s):" << endl;
            accountnum = getaccountnum();
            mylist.findRecord(accountnum);
        }
        else if (ilength <= 6 && input.compare ( 0, ilength, "delete", ilength) == 0)
        {
            /* deleteRecord() */
            cout << "\nDelete record(s):" << endl;
            accountnum = getaccountnum();
            if ( mylist.deleteRecord(accountnum) == 0)
            {
                cout << "\nRecord(s) with account #" << accountnum << " have been deleted" << endl;
            }
            else
            {
                cout << "\nRECORD NOT FOUND!" << endl;
            }
        }
        else if (ilength <= 4 && input.compare ( 0, ilength, "quit" , ilength) == 0)
        {
            cout << "\nQuitting the program..." << endl;
            exit = 1;
        }
        else
        {
            cout << "\nINVALID OPTION!" << endl;
        }
    }
    /* test for extra credit
    llist copy;
    copy = mylist;
    cout << copy;
    llist another = mylist;
    cout << another;
    */
    return 0;
}

/*******************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   inquire the record's address from the user
//
//  Parameters:    address (char[]) : char array to store the address
//                 length (int)     : length of the char array
********************************************************************/

void getaddress ( char address[], int length )
{
    string str;
    
    #ifdef DEBUG
        cout << "\n******************************\n";
        cout << "Function: void getaddress ( char address[], int length )\n";
        cout << "\n******************************\n";
    #endif

    cout << "Enter the account mailing address (type '!' at the end to indicate the end of the address)" << endl;
    getline(cin, str, '!');
    cin.get();
    strcpy(address, str.c_str());
}

/*******************************************************************
//
//  Function name: getaccountnum
//
//  DESCRIPTION:   inquire an account number from the user
//
//  Return value:  (int) : the account number
//
********************************************************************/

int getaccountnum()
{
    int num;
    string str;

    #ifdef DEBUG
        cout << "\n******************************\n";
        cout << "Function: int getaccountnum()\n";
        cout << "\n******************************\n";
    #endif

    num = 0;
    do
    {
        cout << "Enter the account number: " << endl;
        getline(cin, str);
        if ( !(stringstream(str) >> num) || num <= 0)
        {
            cout << "INVALID ACCOUNT NUMBER!" << endl;
        }           
    }
    while (num <= 0);
    return num;
}
