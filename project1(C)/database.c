/********************************************************************
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
//    FILE:		database.c
//
//    DESCRIPTION: 
//     Source code for database functions
//
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"
#include "database.h"

extern int debugmode;

void getaddressfromfile(char [], int, FILE*);

/********************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   a function to add a record entry to the database
//                 with the specified account number, name, and address 
//
//  Parameters:    start (struct record **) : pointer to the start of the
//                 linked list of records, or NULL
//  		   
//  		   uaccountno (int) : the account number of the record
//
//  		   uname (char []) : the name associated with the record 
//
//  		   uaddress (char []) : the mailing address of the record
//
********************************************************************/

void addRecord(struct record ** start, int uaccountno, char uname[], char uaddress[])
{
    struct record *prev, *current, *newRecord;
    if (debugmode == 1)
    {
        printf("\n\n***** Function: addRecord(struct record ** start, int uaccountno, char uname[], char uaddress[] *****\n");
        printf("***** int uaccountno: %d *****\n", uaccountno);
        printf("*****\nchar uname[]: %s*****\n", uname);
        printf("*****\nchar uaddress[]:\n%s\n*****\n", uaddress);
    }
    newRecord = (struct record *) malloc(sizeof(struct record));
    newRecord->accountno = uaccountno;
    strcpy(newRecord->name, uname);
    strcpy(newRecord->address, uaddress);
    newRecord->next = NULL;

    if (*start == NULL)
    {
       *start = newRecord;
    }
    else if (uaccountno <= (*start)[0].accountno)
    {
        newRecord->next = *start;
        *start = newRecord;
    }
    else
    {
        prev = *start;
        current = (*start)[0].next;

        while (current != NULL && uaccountno > current->accountno)
        {
            prev = current;
            current = current->next;
        }
        prev->next = newRecord;
        newRecord->next = current;
    }
    printf("\nRecord with account #%d has been added to the database!\n", newRecord->accountno);
}

/********************************************************************
//
//  Function name: printAllRecord
//
//  DESCRIPTION:   a function to print all existing records in the database 
//
//  Parameters:    start (struct record *) : pointer to the first entry in the record
//
*********************************************************************/

void printAllRecords(struct record * start)
{
    int num;
    if (debugmode == 1)
    {
        printf("\n\n***** Function: printAllRecord(struct record * start) *****\n\n");
    }

    if (start == NULL)
    {
        printf("\nTHERE ARE NO RECORDS TO PRINT!\n");
    }
    else
    {
        num = 1;
        while (start != NULL)
        {
            printf("\nRecord Entry #%d\n", num);
            printf("Account #%d\n", start->accountno);
            printf("Name: %s", start->name);
            printf("Address:\n%s\n", start->address);

            num++;
            start = start->next;
        }
        printf("\n---End-of-Records-List---\n\n");
    }
}

/********************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   a function to find and print all record(s) with the given account #
//
//  Parameters:    start (struct record *) : pointer to the first entry in the record
//  		   
//  		   uaccountno (int) : the account number of the record to find and print
//  
//  Return values:  0  : success
//                  -1 : record not found
//
********************************************************************/

int findRecord(struct record * start, int uaccountno)
{
    int record_found, num;
    record_found = 1;

    if (debugmode == 1)
    {
        printf("\n\n***** Function: findRecord(struct record * start, int uaccountno) *****\n");
        printf("***** int uaccountno: %d *****\n\n", uaccountno);
    }

    if (start != NULL)   
    {
        while (start != NULL && record_found == 1)
        {
            if (uaccountno < start->accountno)
            {
                record_found = -1;
            }
            else if (uaccountno == start->accountno)
            {
                printf("\nPrinting account(s) with #%d:\n", uaccountno);
                
                num = 1;
                while (start != NULL && uaccountno == start->accountno)
                {
                    printf("\nRecord Entry #%d\n", num);
                    printf("Account #%d\n", start->accountno);
                    printf("Name: %s", start->name);
                    printf("Address:\n%s\n", start->address);

                    num++;
                    start = start->next;
                }
                record_found = 0;
            }
            else
            {
                start = start->next;
            }
        }
    }
    if (record_found != 0)
    {
        record_found = -1;
        printf("\nRECORD NOT FOUND!\n");
    }
    return record_found;
}
/********************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   a function to delete 1 or more records of the given account number
//
//  Parameters:    start (struct record **) : pointer to the start of the 
//  		   linked list of records, or NULL
//
//  		   uaccountno (int) : the account number(s) of the record to delete
//
//  Return values:  0  : success
//                  -1 : record not found
//
********************************************************************/

int deleteRecord(struct record ** start, int uaccountno)
{
    int record_deleted;
    struct record *prev, *current, *temp;

    if (debugmode == 1)
    {
        printf("\n\n***** Function: deleteRecord(struct record ** start, int uaccountno) *****\n");
        printf("***** int uaccountno: %d *****\n\n", uaccountno);
    }

    record_deleted = 1;
    current = *start;
    while (current != NULL && record_deleted == 1)
    {
        if (uaccountno < current->accountno)
        {
            record_deleted = -1;
        }
        else if (uaccountno == current->accountno)
        {
            
            if (uaccountno == (*start)->accountno)
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
                free(prev);
            }
            if (temp == NULL)
            {
                *start = current;
            }
            else
            {
                temp->next = current;
            }
            record_deleted = 0;
            printf("\nAll records with account #%d have been deleted!\n", uaccountno);
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }

    if (record_deleted != 0)
    {
        record_deleted = -1;
        printf("\nRECORD NOT FOUND!\n");
    }
    return record_deleted;
}

/********************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   a function that writes existing records onto a .txt file
//
//  Parameters:    start (struct record *) : pointer to the start of the records list
//
//  		   filename (char []) : pointer to the name of the file to write on
//
//  Return values:  0  : success
//                  -1 : file could not be opened
//
********************************************************************/

int writefile(struct record * start, char filename[])
{
    FILE *fout;
    int success, i;

    if (debugmode == 1)
    {
        printf("\n\n***** Function: writefile(struct record * start, char filename[]) *****\n");
        printf("***** char filename[]:\n%s\n*****\n", filename);
    }

    fout = fopen(filename, "w");
    if (fout == NULL)
    {
        success = -1;
    }
    else
    {
        i = 0;
        while (start != NULL)
        {
            fprintf(fout, "%d\n", start->accountno);
            fprintf(fout, "%s", start->name);
            fprintf(fout, "%s!\n", start->address);
            start = start->next;
            i++;
        }
        fclose(fout);
        success = 0;
        if (debugmode == 1)
        {
            printf("\n***** %d records were written onto %s *****\n", i, filename);
        }
    }
    return success;
}

/********************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   a function that reads and constructs a records list from a .txt file
//
//  Parameters:    start (struct record **) : pointer to the start of the 
//  		   linked list of records, or NULL
//
//  		   filename (char []) : pointer to the name of the file to read from
//
//  Return values:  0  : success
//                  -1 : file could not be opened
//
********************************************************************/

int readfile(struct record ** start, char filename[])
{
    FILE *fin;
    struct record *prev, *newRecord;
    char buffer[50], faddress[50];
    int success, i, uaccountno;
    
    if (debugmode == 1)
    {
        printf("\n\n***** Function: readfile(struct record ** start, char filename[]) *****\n");
        printf("***** char filename[]:\n%s\n*****\n", filename);
    }

    fin = fopen(filename, "r");
    if (fin == NULL)
    {
        success = -1;
    }
    else
    {
        i = 0;
        while (fscanf(fin, "%d\n", &uaccountno) != EOF)
        {
            newRecord = (struct record *) malloc(sizeof(struct record));

            newRecord->accountno = uaccountno;
            fgets(newRecord->name, sizeof(newRecord->name), fin);
            getaddressfromfile(faddress, sizeof(faddress), fin);
            strcpy(newRecord->address, faddress);
            newRecord->next = NULL;

            fgets(buffer, sizeof(buffer), fin);

            if (i == 0)
            {
                *start = newRecord;
                prev = newRecord;
            }
            else
            {
                prev->next = newRecord;
                prev = prev->next;
            }
            i++;
        }
        fclose(fin);
        success = 0;
        if (debugmode == 1)
        {
            printf("\n***** %d records were written onto %s *****\n", i, filename);
        }
    }
    return success;
}

/********************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   a function to release all the allocated heap memory spaces
//                 and reset the start pointer
//
//  Parameters:    start (struct record **) : pointer to the start of the 
//  		   linked list of records, or NULL
//
********************************************************************/

void cleanup(struct record ** start)
{
    struct record *current;
    if (debugmode == 1)
    {
        printf("\n\n***** Function: cleanup(struct record ** start) *****\n\n");
    }

    while (*start != NULL)
    {
        current = *start;
        *start = (*start)->next;
        free(current);
    }
}

/********************************************************************
//
//  Function name: getaddressfromfile
//
//  DESCRIPTION:   a function to read the address information from a file
//
//  Parameters:    address (char []) : the array to store the read address
//
//                 length (int) : the max length of the array
//
//                 fin (FILE*) : the file to read from
//
********************************************************************/

void getaddressfromfile(char address[], int length, FILE* fin)
{
    char c;
    int i = 0;
   
    if (debugmode == 1)
    {
        printf("\n\n***** Function: getaddressfromfile(char address[], int length, FILE* fin) *****\n");
        printf("***** int length: %d *****\n", length - 1);
    }

    do
    {
        c = fgetc(fin);
        address[i] = c;
        i++;
    }
    while (c != '!');
    address[i - 1] = '\0';
    if (debugmode == 1)
    {
        printf("***** char address[]:\n%s\n*****\n", address);
    }
}
