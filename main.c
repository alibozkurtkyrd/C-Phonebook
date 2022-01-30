#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    /* Start with the empty list */
    struct entry* head = NULL;
    int select;
    printf("Welcome to myPhoneBook! Please select an option:\n");

    do {

        printf("\n1) New entry\n");
        printf("2) List all entries\n");
        printf("3) Edit\n");
        printf("4) Delete\n");
        printf("5) Search\n");
        printf("6) Save and exit\n");
        printf("7) Load\n");

        scanf("%d",&select);

        if (select == 1)
        {

            char name [50];
            char phone[11];
            char note[125];

            char  chr;
            printf("\nEnter a name:");
            scanf("%s",name);

            printf("Enter a phone:");
            scanf("%s",phone);


            printf("Enter a note:");
            scanf(" %c", &chr);
            fgets(note,125,stdin);
            //(void)fflush(stdout);

            struct entry* new_node = newNode(name,phone,note);
            Insert(&head, new_node);

        }
        else if (select == 2)
        {
            printList(head);

        }

        else if (select == 3)
        {
            updateEntry(head);
        }

        else if (select == 4)
        {
            int deletedNumber;
            printList(head); // I call this function to fill the id part
            printf("\nPlease enter the number(id) of the entry to be deleted:\n");
            scanf("%d:", &deletedNumber);
            deleteEntry(&head, deletedNumber);

        }

        else if (select == 5)
        {
            searchEntry(head);
        }

        else if (select == 6)
        {
            char fileName [50];
            printf("Entities in your list will be saved, please enter filename(without extension):\n");
            scanf("%s",fileName);
            char extension [] = ".txt";
            strcat(fileName,extension); //this function concatanet two string
            writeEntry(fileName,head);
            break;
        }

        else if (select == 7)
        {
            char fileName [50];
            printf("Please enter the filename to upload the entities(without extension):\n");
            scanf("%s",fileName);
            char extension [] = ".txt";
            strcat(fileName,extension); //this function concatanet two string
           head = readEntry(fileName,head);
        }

        }while(select>0 && select <8);


    return 0;
}
