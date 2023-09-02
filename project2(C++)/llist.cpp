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
//  FILE:	llist.cpp
//
//  DESCRIPTION:
//    Source file of 'llist' class
************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include "record.h"
#include "llist.h"

using namespace std;

llist::llist()
{
    this->start = NULL;
}

llist::llist(char name[])
{
    this->start = NULL;
    strcpy( filename, name );
    this->readfile();
}

/* destructor */
llist::~llist()
{
    this->writefile();
    this->cleanup();
}

/* copy constructor */
llist::llist(const llist &source)
{
    #ifdef DEBUG
        cout << "Copy operator called" << endl;
    #endif
    this->start = NULL;
    *this = source;
}

/* assignment operator */
llist& llist::operator=(const llist &source)
{
    struct record *current;
    #ifdef DEBUG
        cout << "Assignment operator called" << endl;
    #endif
    strcpy( this->filename, source.filename);
    current = source.start;
    while (current != NULL)
    {
        this->addRecord ( current->accountno, current->name, current->address );
        current = current->next;
    }
    return *this;
}

/* output operator */
ostream& operator<<(ostream& out, const llist& list)
{
    int num;
    struct record *current;
    #ifdef DEBUG
        cout << "Output operator called" << endl;
    #endif
    current = list.start;
    if (current == NULL)
    {
        out << "\nTHERE ARE NO RECORDS TO PRINT!" << endl;
    }
    else
    {
        num = 1;
        do
        {
            out << "\nRecord Entry #" << num;
            out << "\nAccount #" << current->accountno;
            out << "\nName: " << current->name;
            out << "Address:\n" << current->address << endl;
            num++;
            current = current->next;
        }
        while (current != NULL);
        out << "\n---End-of-Records-List---\n" << endl;
    }
    return out;
}

/*******************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   read records from a file and initialize the llist with them
//
//  Return values:  0 : success
//                 -1 : file was not opened
//
********************************************************************/

int llist::readfile()
{
    ifstream ifile;
    int opened, accountno;
    char name[30], address[50];

    #ifdef DEBUG
        cout << "\n******************************\n";
        cout << "Function: int llist::readfile()\n";
        cout << "\n******************************\n" << endl;
    #endif

    ifile.open(this->filename);
    if (ifile)
    {
        while (ifile.good())
        {
            ifile >> accountno;
            if (ifile.good())
            {
                ifile.ignore(1, EOF);
                ifile.getline(name, 30);
                ifile.getline(address, 50, '!');
                ifile.ignore(1, EOF);
                this->addRecord ( accountno, name, address );
            }
        }
        opened = 0;
        ifile.close();
    }
    else
    {
        opened = -1;
    }
    return opened;
}

/*******************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   write the records of the llist to a file
//
//  Return values:  0 : success
//                 -1 : file was not opened
//
********************************************************************/

int llist::writefile()
{
    ofstream ofile;
    int opened;
    struct record *current;

    #ifdef DEBUG
        cout << "\n******************************\n";
        cout << "Function: int llist::writefile()\n";
        cout << "\n******************************\n" << endl;
    #endif

    ofile.open(this->filename);
    if (ofile)
    {
        current = start;
        while (current != NULL)
        {
            ofile << current->accountno << endl;
            ofile << current->name << endl;
            ofile << current->address << '!' << endl;
            current = current->next;
        }
        opened = 0;
        ofile.close();
    }
    else
    {
        opened = -1;
    }
    return opened;
}

/*******************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   deallocate all records of the llist
//
********************************************************************/

void llist::cleanup()
{
    struct record *current;

    #ifdef DEBUG
        cout << "\n******************************\n";
        cout << "Function: void llist::cleanup()\n";
        cout << "\n******************************\n" << endl;
    #endif

    while (start != NULL)
    {
        current = start;
        start = start->next;
        delete current;
    }
}
 
/*******************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   add a record to the llist; smaller account number
//                 is sorted in front of the llist
//
//  Parameters:    uaccountno (int)  : the record's account number
//                 uname (char[])    : the record's associated name
//                 uaddress (char[]) : the record's associated address
//
********************************************************************/

void llist::addRecord ( int uaccountno, char uname[], char uaddress[] )
{
    struct record *prev, *current, *newRecord;

    #ifdef DEBUG
        cout << "\n******************************\n";
        cout << "Function: void llist::addRecord ( int uaccountno, char uname[], char uaddress[] )\n";
        cout << "\nuaccountno: " << uaccountno;
        cout << "\nuname: " << uname;
        cout << "\nuaddress: " << uaddress;
        cout << "\n******************************\n" << endl;
    #endif

    newRecord = new record;
    newRecord->accountno = uaccountno;
    strcpy(newRecord->name, uname);
    strcpy(newRecord->address, uaddress);
    newRecord->next = NULL;

    if (start == NULL)
    {
        start = newRecord;
    }
    else if (uaccountno <= start->accountno)
    {
        newRecord->next = start;
        start = newRecord;
    }
    else
    {
        prev = start;
        current = start->next;

        while (current != NULL && uaccountno > current->accountno)
        {
            prev = current;
            current = current->next;
        }
        prev->next = newRecord;
        newRecord->next = current;
    }
}

/*******************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   find record(s) in the llist
/ /
//  Parameters:    uaccountno (int) : account number of the llist to find
//
//  Return values:  0 : record was found and printed
//                 -1 : record was not found
//
********************************************************************/

int llist::findRecord ( int uaccountno )
{
    int found, num;
    struct record *current;

    #ifdef DEBUG
        cout << "\n******************************\n";
        cout << "Function: int llist::findRecord ( int uaccountno )\n";
        cout << "\nuaccountno: " << uaccountno;
        cout << "\n******************************\n" << endl;
    #endif

    found = 1;
    if (start != NULL)
    {
        current = start;
        while (current != NULL && found == 1)
        {
            if (uaccountno < current->accountno)
            {
                found = -1;
            }
            else if (uaccountno == current->accountno)
            {
                cout << "\nPrinting account(s) with #" << uaccountno << endl;

                num = 1;
                while (current != NULL && uaccountno == current->accountno)
                {
                    cout << "\nRecord Entry #" << num;
                    cout << "\nAccount #" << current->accountno;
                    cout << "\nName: " << current->name << endl;
                    num++;
                    current = current->next;
                }
                found = 0;
            }
            else
            {
                current = current->next;
            }
        }
    }
    if (found != 0)
    {
        found = -1;
        cout << "\nRECORD NOT FOUND!" << endl;
    }
    return found;
}

/*******************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   print all the records in the llist
//
********************************************************************/

void llist::printAllRecords()
{
    int num;
    struct record *current;

    #ifdef DEBUG
        cout << "\n******************************\n";
        cout << "Function: void llist::printAllRecords()\n";
        cout << "\n******************************\n" << endl;
    #endif

    if (start == NULL)
    {
        cout << "\nTHERE ARE NO RECORDS TO PRINT!" << endl;
    }
    else
    {
        num = 1;
        current = start;
        while (current != NULL)
        {
            cout << "\nRecord Entry #" << num;
            cout << "\nAccount #" << current->accountno;
            cout << "\nName: " << current->name;
            cout << "\nAddress:\n" << current->address << endl;
            num++;
            current = current->next;
        }
        cout << "\n---End-of-Records-List---\n" << endl;
    }
}

/*******************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   delete record(s) on the llist
//
//  Parameters:    uaccountno (int) : account number of the llist to delete
//
//  Return values:  0 : record was deleted
//                 -1 : record was not found
//
********************************************************************/

int llist::deleteRecord ( int uaccountno )
{
    int deleted;
    struct record *prev, *current, *temp;

    #ifdef DEBUG
        cout << "\n******************************\n";
        cout << "Function: int llist::deleteRecord ( int uaccountno )\n";
        cout << "\nuaccountno: " << uaccountno;
        cout << "\n******************************\n" << endl;
    #endif

    deleted = 1;
    current = start;
    while (current != NULL && deleted == 1)
    {

        if (uaccountno < current->accountno)
        {
            deleted = -1;
        }
        else if (uaccountno == current->accountno)
        {
            if (uaccountno == start->accountno)
            {
                temp = NULL; 
            }
            else
            {
                temp = prev;
            }
            while (current != NULL && uaccountno == current->accountno)
            {
                prev = current;
                current = current->next;
                delete prev;
            }
            if (temp == NULL)
            {
                start = current;
            }
            else
            {
                temp->next = current;
            }
            deleted = 0;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
    if (deleted != 0)
    {
        deleted = -1;
    }
    return deleted;
}
