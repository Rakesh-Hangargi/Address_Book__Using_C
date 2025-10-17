/*
	Name: Rakesh Hangargi
 Roll No: 25021_240
    Date: 10/10/2025


	
					Project Title: ADDRESS BOOK
	This project demonstrates the usage of a general Database Management System which provides certain techniques to modify ,
	edit and obtain details from the database
	This Database Management System is created using Structures, FILE Handling and some Standard Libraries of C

*/


#include "contact.h"

int main() 
{
    int choice;

    struct AddressBook addressBook;
    initialize(&addressBook); 

    do 
    {
	printf("\nAddress Book Menu:\n");
	printf("1. Create contact\n");
	printf("2. Search contact\n");
	printf("3. Edit contact\n");
	printf("4. Delete contact\n");
	printf("5. List all contacts\n");
	printf("6. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice) 
	{
	    case 1:
		createContact(&addressBook);
		break;
	    case 2:
		searchContact(&addressBook);
		break;
	    case 3:
		editContact(&addressBook);
		break;
	    case 4:
		deleteContact(&addressBook);
		break;
	    case 5:
		listContacts(&addressBook);
		break;
	    case 6:
		printf("Saving and Exiting...\n");
		saveContactsToFile(&addressBook);
		break;
	    default:
		printf("Invalid choice. Please try again.\n");
	}
    } while (choice != 6);

    return 0;
}
