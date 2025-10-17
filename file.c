/*
	Name: Rakesh Hangargi
 Roll No: 25021_240
    Date: 10/10/2025


	
					Project Title: ADDRESS BOOK
	This project demonstrates the usage of a general Database Management System which provides certain techniques to modify ,
	edit and obtain details from the database
	This Database Management System is created using Structures, FILE Handling and some Standard Libraries of C

*/

#include <stdio.h>
#include "file.h"
#include<string.h>

void saveContactsToFile(struct AddressBook *addressBook) {
    FILE *fp = fopen("contacts.csv", "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fp, "%d, %s, %s, %s\n",
                i + 1,
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);
}


void loadContactsFromFile(struct AddressBook *addressBook) 
{
    FILE *fp = fopen("contacts.csv", "r");
    if (fp == NULL) {
        // No file found — just start with empty list
        printf("No existing contacts file found. Starting fresh.\n");
        return;
    }

    int i = 0;
    int temp=i+1;
    while (i < 100 && 
           fscanf(fp, "%d, %[^,], %[^,], %[^\n]\n",
                  &temp,
                  addressBook->contacts[i].name,
                  addressBook->contacts[i].phone,
                  addressBook->contacts[i].email) == 4)
    {
        i++;
        temp=i+1;
    }

    addressBook->contactCount = i;
    fclose(fp);
}

