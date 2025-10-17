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

// Dummy contact data
static struct Contact dummyContacts[] = {
    {"John Doe", "1234567890", "john@example.com"},
    {"Alice Smith", "0987654321", "alice@example.com"},
    {"Bob Johnson", "1112223333", "bob@company.com"},
    {"Carol White", "4445556666", "carol@company.com"},
    {"David Brown", "7778889999", "david@example.com"},
    {"Eve Davis", "6665554444", "eve@example.com"},
    {"Frank Miller", "3334445555", "frank@example.com"},
    {"Grace Wilson", "2223334444", "grace@example.com"},
    {"Hannah Clark", "5556667777", "hannah@example.com"},
    {"Ian Lewis", "8889990000", "ian@example.com"}
};

void populateAddressBook(struct AddressBook* addressBook)
{
    int numDummyContacts = sizeof(dummyContacts) / sizeof(dummyContacts[0]);
    for (int i = 0; i < numDummyContacts; i++) {
        addressBook->contacts[addressBook->contactCount++] = dummyContacts[i];
    }
}
