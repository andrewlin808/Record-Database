/********************************************************************
//
//  NAME:		Andrew Lin
//
//  HOMEWORK:		3b
//
//  CLASS:		ICS 212
//
//  INSTRUCTOR:		Ravi Narayan
//
//  DATE:		March 29, 2022
//
//  FILE:		user_interface.c
//
//  DESCRIPTION:
//    The main program as the user interface for interaction with
//    the record database
//
********************************************************************/

#include <stdio.h>
#include <string.h>
#include "record.h"
#include "database.h"

int debugmode;

void getaddress(char [], int);
void getaccountnum(int *, char []);

/********************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   The main program running the UI for interacting with the database.
//                 Calls the corresponding function to access database.
//
//  Parameters:    argc (int) : number of command-line arguments
//
//  		   argv (char * []) : pointer to the first command-line arguments 
//
//  Return values:  1 : program ran in debug mode
//                  0 : program ran normally
//                 -1 : error
//                  
********************************************************************/

int main(int argc, char * argv[])
{
    struct record * start = NULL;
    char buffer[100], input[100], uname[30], uaddress[50];
    const char debug[] = "debug", add[] = "add", printall[] = "printall", find[] = "find", delete[] = "delete", quit[] = "quit";
    int exit = 0, inputlength, uaccountno;
    
    /* check debugmode */
    if (argc == 2 && strlen(argv[1]) == 5 && (int) (strstr(debug, argv[1]) - debug) == 0) /* in debugmode */
    {
        debugmode = 1;
        printf("\n\n***** project1 running under debug mode! *****\n\n");
    }
    else if (argc != 1) /* invalid command-line-argument(s) */
    {
        printf("\nINVALID COMMAND-LINE ARGUMENT(S)! Program exiting...\n");
        debugmode = -1;
        exit = 1;
    }
    else /* normal mode */
    {
        debugmode = 0;
    }
    /* read records from records.txt */
    if (debugmode != -1)
    {
        readfile(&start, "records.txt");
    }

    /* Menu */
    if (debugmode != -1)
    {
        printf("\n\nWelcome! You have entered the user interface for managing customer's banking records\n\n");
    }
    while (exit == 0)
    {
        printf("\nSelect one of the options below:\n");
        printf("add: add a new customer record\n");
        printf("printall: print all existing record(s) of customers\n");
        printf("find: find record(s) of an existing customer\n");
        printf("delete: delete record(s) of an existing customer\n");
        printf("quit: exit the program\n");
        printf("Awaiting input...\n");

        scanf("%s", input);
        fgets(buffer, sizeof(buffer), stdin);
        inputlength = strlen(input);

        if (inputlength <= 3 && (int) (strstr(add, input) - add) == 0) /* add */
        {
            printf("\nAdd a new record:\n");
            
            /* account number */
            getaccountnum(&uaccountno, buffer);

            /* account name */
            printf("\nEnter the account name: \n");

            fgets(uname, sizeof(uname), stdin);

            /* account address */
            getaddress(uaddress, sizeof(uaddress));

            printf("\nAdding new record to database: \n");
            addRecord(&start, uaccountno, uname, uaddress);
        }
        else if (inputlength <= 8 && (int) (strstr(printall, input) - printall) == 0) /* printall */
        {
            printf("\nPrint all records:\n");
            printAllRecords(start);
        }
        else if (inputlength <= 4 && (int) (strstr(find, input) - find) == 0) /* find */
        {
            printf("\nFind record(s):\n");
            getaccountnum(&uaccountno, buffer);
            findRecord(start, uaccountno);
        }
        else if (inputlength <= 6 && (int) (strstr(delete, input) - delete) == 0) /* delete */
        {
            printf("\nDelete record(s):\n");
            getaccountnum(&uaccountno, buffer);
            deleteRecord(&start, uaccountno);
        }
        else if (inputlength <= 4 && (int) (strstr(quit, input) - quit) == 0) /* quit */
        {
            printf("Quitting the program...\n");
            exit = 1;
            writefile(start, "records.txt");
        }
        else
        {
            printf("\nINVALID OPTION!\n");
        }
    }
    if (debugmode != -1)
    {
        cleanup(&start);
    }
    return debugmode;
}

/********************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   a function to get the mailing address of the record
//                 when adding a new record.
//
//  Parameters:    address (char []) : the character array to hold the address
//
//  		   length (int) : the maximum length of the address
//
********************************************************************/

void getaddress(char address[], int length)
{
    char c;
    int i = 0;

    if (debugmode == 1)
    {
        printf("\n\n***** Function: getaddress(char address[], int length) *****\n\n");
        printf("***** value of address: not yet given *****\n");
        printf("***** value of length: %d\n", length);
    }
    printf("Enter the account mailing address: (type '!' at the end to indicate the end of the address)\n");
    do
    {
        c = fgetc(stdin);
        address[i] = c;
        i++;
    }
    while (c != '!' && i < length);
    address[i - 1] = '\0';

    if (debugmode == 1)
    {
        printf("\n***** char address[]: \n%s\n*****\n", address);
        printf("\n***** int length: %d *****\n\n", (int) strlen(address));
    }
}

/********************************************************************
//
//  Function name: getaccountnum
//
//  DESCRIPTION:   a function to get the account number from the user
//
//  Parameters:    uaccountno (int *) : the int pointer to store the account #
//
//  		   buffer (char []) : a pointer to clean the stdin buffer
//
********************************************************************/

void getaccountnum(int *uaccountno, char buffer[])
{
    int returnval;
    if (debugmode == 1)
    {
        printf("\n\n***** Function: getaccountnum(int *accountno, char buffer[]) *****\n\n");
    }
    do
    {        
        printf("\nEnter the account number: \n");

        returnval = scanf("%d", uaccountno);
        fgets(buffer, sizeof(buffer), stdin);

        if (returnval == 0 || *uaccountno <= 0)
        {
            printf("\nINVALID ACCOUNT NUMBER!\n");
        }
    }
    while (returnval == 0 || *uaccountno <= 0);
}
