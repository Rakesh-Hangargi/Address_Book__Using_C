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
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(struct AddressBook *addressBook) 
{
    int count = addressBook->contactCount;
    if(count == 0)
    {
        printf("List is empty\n");
        return;
    }

    //:::CONTACTS DETAILS:::
    for(int i = 0; i < count; i++)
    {
        // Displaying the contact details in order with serial number
        printf("%d, %s ,%s ,%s\n", i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
}

void initialize(struct AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);   // load default data if any
    loadContactsFromFile(addressBook);  // load saved contacts from file
}

void saveAndExit(struct AddressBook *addressBook) {
    saveContactsToFile(addressBook); // save the data before exiting
    exit(EXIT_SUCCESS);
}


void createContact(struct AddressBook *addressBook)
{
    int count = addressBook->contactCount;
    printf("::ENTER THE CONTACT DETAILS BELOW::\n");

    // taking name input
    printf("Enter name: ");
    char str[50];
    scanf(" %[^\n]", str);
    strcpy(addressBook->contacts[count].name, str);

    // validating number input
    printf("Enter the number: ");
    char numb[20];
    int choice = 1, flag = 0;
    while(choice)
    {
        scanf(" %[^\n]", numb);

        // checking for exact 10 digits
        if(strlen(numb) != 10)
        {
            printf("Contact Number must contain 10 digits!!\nYou have entered %d digits\nTry again\n", strlen(numb));
            continue;
        }

        // checking valid starting digit
        if(numb[0] != '9' && numb[0] != '8' && numb[0] != '7' && numb[0] != '6')
        {
            printf("Invalid number entered\nNumber should start from '9','8','7'or'6'\nEnter new Number : ");
            continue;
        }

        // checking for any non-digit characters
        char* ptr = numb;
        while(*ptr)
        {
            if(!(*ptr >= '0' && *ptr <= '9'))
            {
                flag = 1;
                break;
            }
            ptr++;
        }

        if(flag)
        {
            printf("Alphabets not allowed in phone number\nEnter valid number : ");
            flag = 0;
            continue;
        }

        // checking for duplicates
        for(int i = 0; i < count; i++)
        {
            if(!(strcmp(addressBook->contacts[i].phone, numb)))
            {
                printf("Number is already present\nEnter a unique number: ");
                flag = 1;
                break;
            }
        }

        if(flag)
            continue;

        choice = 0;
    }

    strcpy(addressBook->contacts[count].phone, numb);
    choice = 1;

    // basic domain endings to validate mail
    char temp1[5] = ".com";
    char temp2[5] = ".edu";
    char temp3[5] = ".in";
    char temp4[5] = ".org";
    char temp5[5] = ".ac";

    printf("Enter email: ");
    char mail[50];
    flag = 0;
    while(choice)
    {
        scanf(" %[^\n]", mail);

        // checking if @ exists and has valid extension
        if(strchr(mail, '@'))
        {
            if(!(strstr(mail, temp1) || strstr(mail, temp2) || strstr(mail, temp3) ||
                 strstr(mail, temp4) || strstr(mail, temp5)))
            {
                printf("Invalid mail extension\nEnter mail ID with proper extension: ");
                continue;
            }
        }
        else
        {
            printf("Invalid mail :: Missing @ \nEnter Mail ID : ");
            continue;
        }

        if(strchr(mail,' '!='\0'))
        {
            printf("\nSpaces are not allowed\nEnter valid Email: \n");
            continue;
        }

        //Checking if the mail is starting with lower case
        if(!(mail[0]>='a' && mail[0]<='z'))
        {
            printf("Mail ID must have a lower case starting alphabet\nEnter valid Email: \n");
            continue;
        }

        char* check=NULL;

        //Checking if the mail is ending with proper extension
       if(check=strstr(mail,temp1))
       {
            if(check+4==NULL)
            {
                printf("Mail ID must end with valid extension (for ex: xyz@gmail.com)\nEnter valid Email: \n");
                continue;
            }
       }
       else if(check=strstr(mail,temp2))
       {
            if(check+4==NULL)
            {
                printf("Mail ID must end with valid extension (for ex: xyz@gmail.edu)\nEnter valid Email: \n");
                continue;
            }
       }
       else if(check=strstr(mail,temp3))
       {
            if(check+3==NULL)
            {
                printf("Mail ID must end with valid extension (for ex: xyz@gmail.in)\nEnter valid Email: \n");
                continue;
            }
       }
       else if(check=strstr(mail,temp4))
       {
             if(check+4==NULL)
            {
                printf("Mail ID must end with valid extension (for ex: xyz@gmail.org)\nEnter valid Email: \n");
                continue;
            }
       }
       else if(check=strstr(mail,temp5))
       {
             if(check+3==NULL)
            {
                printf("Mail ID must end with valid extension (for ex: xyz@gmail.ac)\nEnter valid Email: \n");
                continue;
            }
       }



        // checking duplicate mail IDs
        for(int i = 0; i < count; i++)
        {
            if(!(strcmp(addressBook->contacts[i].email, mail)))
            {
                printf("Mail ID already present\nEnter a Unique Mail ID : ");
                flag = 1;
                break;
            }
        }

        if(flag)
            continue;

        flag = 0;
        choice = 0;
    }

    strcpy(addressBook->contacts[count].email, mail);

    // increasing contact count after adding new one
    addressBook->contactCount = addressBook->contactCount + 1;
}



void searchContact(struct AddressBook *addressBook) 
{
    int count = addressBook->contactCount;
    int choice, z = 0, entry = 1;

    printf("\t\t:::SEARCH CONTACT DETAILS:::\n");
    while(entry)
    {
        int flag = 0;
        printf("1.Name\n2.Number\n3.Email\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: {
                char str[50];
                printf("Enter the Name you wanna search: ");
                scanf(" %[^\n]", str);
                int dummy = 0;

                // searching by name
                for(int i = 0; i < count; i++)
                {
                    if(!(strcmp(addressBook->contacts[i].name, str)))
                    {
                        dummy++;
                        printf("================================================\n");
                        printf("Contact %d\n", i);
                        printf("------------------------------------\n");
                        printf("Name: %s\n", addressBook->contacts[i].name);
                        printf("Phone: %s\n", addressBook->contacts[i].phone);
                        printf("Mail ID: %s\n", addressBook->contacts[i].email);
                        printf("------------------------------------\n\n");
                    }
                }

                if(dummy == 0)
                {
                    printf("Entered name doesn't exit\n");
                    int ex;
                    printf("Enter 1 to search again or 0 to exit : ");
                    scanf("%d", &ex);
                    if(ex == 1)
                        continue;
                    else
                        return;
                }

                break;
            }

            case 2: {
                char str[50];
                printf("Enter the Number you wanna search: ");
                scanf(" %[^\n]", str);
                int dummy = 0;

                // searching by number
                for(int i = 0; i < count; i++)
                {
                    if(!(strcmp(addressBook->contacts[i].phone, str)))
                    {
                        dummy++;
                        z = i;
                        break;
                    }
                }

                if(dummy == 0)
                {
                    printf("Entered number doesn't exit\n");
                    flag = 1;
                    break;
                }
                else
                {
                    printf("Details found\n");
                    printf("------------------------------------\n");
                    printf("Name: %s\n", addressBook->contacts[z].name);
                    printf("Phone: %s\n", addressBook->contacts[z].phone);
                    printf("Mail ID: %s\n", addressBook->contacts[z].email);
                    printf("------------------------------------\n\n");
                }
                break;
            }

            case 3: {
                char str[50];
                printf("Enter the Email you wanna search: ");
                scanf(" %[^\n]", str);
                int dummy = 0;

                // searching by email
                for(int i = 0; i < count; i++)
                {
                    if(!(strcmp(addressBook->contacts[i].email, str)))
                    {
                        dummy++;
                        z = i;
                        break;
                    }
                }

                if(dummy == 0)
                {
                    printf("Entered Mail doesn't exit\n");
                    flag = 1;
                    break;
                }
                else
                {
                    printf("Details found\n");
                    printf("------------------------------------\n");
                    printf("Name: %s\n", addressBook->contacts[z].name);
                    printf("Phone: %s\n", addressBook->contacts[z].phone);
                    printf("Mail ID: %s\n", addressBook->contacts[z].email);
                    printf("------------------------------------\n\n");
                }

                break;
            }

            default: {
                printf("Invalid entry\n");
                break;    
            }
        }

        // giving option to continue searching again
        if(flag)
        {
            printf("Press 1 to search again\nPress 0 to exit\n");
            scanf("%d", &entry);
        }
        else
        {
            entry = 0;
        }
    }
}

void editContact(struct AddressBook *addressBook)
{
    int count = addressBook->contactCount;
    printf("\n\t\t:::EDIT CONTACT WINDOW\n\n");
    int choice = 0, entry = 1;

    while(entry)
    {
        printf("1.Name\n2.Phone\n3.Email\n4.Index\nEnter your choice to edit: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: {
                printf("\nEnter the name you wanna change: ");
                char name1[50];
                scanf(" %[^\n]", name1);
                int dummy = 0;

                // checking multiple contacts with same name
                for(int i = 0; i <= count; i++)
                {
                    if(!strcmp(addressBook->contacts[i].name, name1))
                        dummy++;
                }

                if(dummy > 1)
                {
                    printf("Multiple Contacts found with the same name\n");
                    for(int i = 0; i <= count; i++)
                    {
                        if(!strcmp(addressBook->contacts[i].name, name1))
                        {
                            printf("------------------------------------\n");
                            printf("Name: %s\n", addressBook->contacts[i].name);
                            printf("Phone: %s\n", addressBook->contacts[i].phone);
                            printf("Mail ID: %s\n", addressBook->contacts[i].email);
                            printf("------------------------------------\n\n");
                        }   
                    }
                    continue;
                }
                else if(dummy == 1)
                {
                    // single contact found, update directly
                    for(int i = 0; i <= count; i++)
                    {
                        if(!strcmp(addressBook->contacts[i].name, name1))
                        {
                            char temp[50];
                            printf("\nEnter new name: ");
                            scanf(" %[^\n]", temp);

                            strcpy(addressBook->contacts[i].name, temp);
                            printf("\n::Name Updated Successfully::\n");
                            choice = 0;
                        }
                    }
                    break;
                }
                else
                {
                    printf("Name doesn't exist\n\nPress 1 to check again 0 to exit");
                    scanf("%d", &entry);
                    break;
                }
                break;
            }

            // phone editing block
            case 2: {
                printf("\nEnter the phone you wanna change: ");
                char phone1[20];
                scanf(" %[^\n]", phone1);
                int found = 0;

                for (int i = 0; i < count; i++)
                {
                    if (!strcmp(addressBook->contacts[i].phone, phone1))
                    {
                        char temp[20];
                        printf("\nEnter new phone: ");
                        scanf(" %[^\n]", temp);

                        strcpy(addressBook->contacts[i].phone, temp);
                        printf("\n::Phone Updated Successfully::\n");
                        found = 1;
                        break;
                    }
                }

                if (!found)
                {
                    printf("Phone number doesn't exist\n\nPress 1 to check again 0 to exit: ");
                    scanf("%d", &entry);
                }
                break;
            }    

            // email editing block
            case 3: {
                printf("\nEnter the email you wanna change: ");
                char email1[50];
                scanf(" %[^\n]", email1);
                int found = 0;

                for (int i = 0; i < count; i++)
                {
                    if (!strcmp(addressBook->contacts[i].email, email1))
                    {
                        char temp[50];
                        printf("\nEnter new email: ");
                        scanf(" %[^\n]", temp);

                        strcpy(addressBook->contacts[i].email, temp);
                        printf("\n::Email Updated Successfully::\n");
                        found = 1;
                        break;
                    }
                }

                if (!found)
                {
                    printf("Email doesn't exist\n\nPress 1 to check again 0 to exit: ");
                    scanf("%d", &entry);
                }
                break;
            }

            // editing by index
            case 4: {
                printf("\nEnter the index of contact you want to edit (0 to %d): ", count - 1);
                int idx;
                scanf("%d", &idx);
                idx = idx - 1;

                if (idx >= 0 && idx < count)
                {
                    printf("\nContact chosen:\n");
                    printf("------------------------------------\n");
                    printf("Name: %s\n", addressBook->contacts[idx].name);
                    printf("Phone: %s\n", addressBook->contacts[idx].phone);
                    printf("Mail ID: %s\n", addressBook->contacts[idx].email);
                    printf("------------------------------------\n");

                    int subChoice;
                    printf("\nWhat do you want to edit?\n1.Name\n2.Phone\n3.Email\nChoice: ");
                    scanf("%d", &subChoice);

                    if (subChoice == 1)
                    {
                        char temp[50];
                        printf("\nEnter new name: ");
                        scanf(" %[^\n]", temp);
                        strcpy(addressBook->contacts[idx].name, temp);
                        printf("\n::Name Updated Successfully::\n");
                    }
                    else if (subChoice == 2)
                    {
                        char temp[20];
                        printf("\nEnter new phone: ");
                        scanf(" %[^\n]", temp);
                        strcpy(addressBook->contacts[idx].phone, temp);
                        printf("\n::Phone Updated Successfully::\n");
                    }
                    else if (subChoice == 3)
                    {
                        char temp[50];
                        printf("\nEnter new email: ");
                        scanf(" %[^\n]", temp);
                        strcpy(addressBook->contacts[idx].email, temp);
                        printf("\n::Email Updated Successfully::\n");
                    }
                }
                else
                {
                    printf("Invalid index\n\nPress 1 to check again 0 to exit: ");
                    scanf("%d", &entry);
                }
                break;
            }

            default:{
                printf("Invalid choice\n");
                break;
            }
        }
        choice = 0;
    }
}


void deleteContact(struct AddressBook *addressBook)
{
    int count = addressBook->contactCount;
    printf("\n\t\t:::DELETE CONTACT WINDOW:::\n\n");
    int choice, entry = 1;

    while (entry)
    {
        printf("\nDelete by:\n");
        printf("1. Name\n2. Phone\n3. Email\n4. Index\n0. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            // delete using name
            case 1: {
                char name1[50];
                printf("\nEnter the name of the contact to delete: ");
                scanf(" %[^\n]", name1);

                int matches[100];
                int matchCount = 0;

                for (int i = 0; i < count; i++)
                {
                    if (!strcmp(addressBook->contacts[i].name, name1))
                    {
                        matches[matchCount++] = i;
                        printf("------------------------------------\n");
                        printf("Option: %d\n", matchCount);
                        printf("Name: %s\n", addressBook->contacts[i].name);
                        printf("Phone: %s\n", addressBook->contacts[i].phone);
                        printf("Mail ID: %s\n", addressBook->contacts[i].email);
                        printf("------------------------------------\n\n");
                    }
                }

                if (matchCount == 0)
                {
                    printf("No contact found with name '%s'.\n", name1);
                }
                else if (matchCount == 1)
                {
                    // single contact found
                    int idx = matches[0];
                    for (int j = idx; j < count - 1; j++)
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    
                    addressBook->contactCount--;
                    printf("\n::Contact Deleted Successfully::\n");
                }
                else
                {
                    // multiple contacts found, user has to choose
                    int option;
                    printf("\nMultiple contacts found with the same name.\n");
                    printf("Enter your option (1 to %d): ", matchCount);
                    scanf("%d", &option);

                    if (option >= 1 && option <= matchCount)
                    {
                        int idx = matches[option - 1];
                        for (int j = idx; j < count - 1; j++)
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        
                        addressBook->contactCount--;
                        printf("\n::Contact Deleted Successfully::\n");
                    }
                    else
                    {
                        printf("Invalid option chosen.\n");
                    }
                }

                break;
            }

            // delete using phone
            case 2: {
                char phone1[20];
                printf("\nEnter the phone number of the contact to delete: ");
                scanf(" %[^\n]", phone1);

                int found = 0;
                for (int i = 0; i < count; i++)
                {
                    if (!strcmp(addressBook->contacts[i].phone, phone1))
                    {
                        for (int j = i; j < count - 1; j++)
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        
                        addressBook->contactCount--;
                        printf("\n::Contact Deleted Successfully::\n");
                        found = 1;
                        break;
                    }
                }

                if (!found)
                    printf("Contact with phone '%s' not found.\n", phone1);

                break;
            }

            // delete using email
            case 3: {
                char email1[50];
                printf("\nEnter the email of the contact to delete: ");
                scanf(" %[^\n]", email1);

                int found = 0;
                for (int i = 0; i < count; i++)
                {
                    if (!strcmp(addressBook->contacts[i].email, email1))
                    {
                        for (int j = i; j < count - 1; j++)
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        
                        addressBook->contactCount--;
                        printf("\n::Contact Deleted Successfully::\n");
                        found = 1;
                        break;
                    }
                }

                if (!found)
                    printf("Contact with email '%s' not found.\n", email1);

                break;
            }

            // delete by index
            case 4: {
                int idx;
                printf("\nEnter the index of the contact to delete (0 to %d): ", count - 1);
                scanf("%d", &idx);
                idx = idx - 1;

                if (idx >= 0 && idx < count)
                {
                    for (int j = idx; j < count - 1; j++)
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    
                    addressBook->contactCount--;
                    printf("\n::Contact Deleted Successfully::\n");
                }
                else
                {
                    printf("Invalid index\n");
                }
                break;
            }

            case 0:
                entry = 0;
                printf("\nExiting Delete Window...\n");
                break;

            default:{
                printf("Invalid choice\n");
                entry = 0;
                break;
            }
        }
    }
}
