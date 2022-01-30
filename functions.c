
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
struct entry{
   int id ; // this stores the index of entity. After delete or insert or update operation it can be changed.
   char name[50];
   char  phone[11];
   char note[125];
   struct entry* next;
};



struct entry* newNode(char *name, char *phone, char *note)
{
    struct entry* new_node= (struct entry*)malloc(
	sizeof(struct entry));


    strcpy(new_node->name, name);
    strcpy(new_node->phone, phone);
    strcpy(new_node->note, note);
    new_node->next = NULL;

    return new_node;
}

void Insert(struct entry** head_ref, struct entry* new_node)
{
   struct entry* current;
   if (*head_ref == NULL
      || strcmp((*head_ref)->name,new_node->name)> 0) {

      new_node->next = *head_ref;
       *head_ref = new_node;
    }
    else {
        current = *head_ref;
        while (current->next != NULL
               && strcmp(current->next->name,new_node->name)< 0) {  //If the first parameters are greater than the second, it returns less than 0.
     	   current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

int printList(struct entry* head)
{
    int counter=1;
    struct entry* temp = head;
    while (temp != NULL) {
        temp->id = counter; // whenever printList method called possibly id can be changed
        printf("\n%d) %s\t%s\t%s\n",temp->id, temp->name, temp->phone, temp->note);
        temp = temp->next;
        counter++;
    }
    printf("\n");

    if (head == NULL)
        printf("List is EMPTY\n");

    return counter-1; //it returns to last entity'id
}

int numberOfEntries(struct entry* head)
{//this function returns the length of linkedlist
    int counter=1;
    struct entry* temp = head;
    while (temp != NULL) {
        temp->id = counter; // whenever printList method called possibly id can be changed
        temp = temp->next;
        counter++;
    }
    printf("\n");



    return counter-1; //it returns to last entity'id
}

void deleteEntry(struct entry** head_ref, int id)
{
    struct entry * temp = *head_ref, *prev;
    char sure;



    if (temp != NULL && temp->id == id)
    {
        printf("Entry '%s' will be deleted Are your sure?",temp->name);
        scanf(" %c",&sure);

        if(sure == 'n')
            return;

        else if (sure == 'y')
        {
            *head_ref = temp->next; // head become next new_node
            printf("Entry is successfully deleted. Total number of entries: %d\n",numberOfEntries(*head_ref));
            free(temp);
            return;
        }

    }

    //find the previous node
    while (temp != NULL && temp->id != id){
        prev = temp;
        temp = temp->next;
    }

     printf("Entry '%s' will be deleted Are your sure?",temp->name);
    scanf(" %c",&sure);

    if (temp == NULL) // we reach the end of the node
        return;

    if(sure == 'n')
        return;

    else if (sure == 'y')
    {
        prev->next = temp->next; // cut the delted node from chain
        printf("Entry is successfully deleted. Total number of entries: %d\n",numberOfEntries(*head_ref));
        free(temp); // we nned to unallocate memory
        return;
    }

}

void searchEntry(struct entry* head)
{
    bool flag = false;
    if (head == NULL)
    {
        printf("\nList is empty\n");
    }

    else {

     char name[50];
     char note[125];

     int select;

     printf("1-Search by using Name\n");
     printf("2-Search by using Note\n");
     printf("3-Terminate Search Step\n");
     scanf("%d",&select);

     if (select == 1)
     {
        printf("enter the name you want to search :");
        scanf("%s", name);

        struct entry *temp = head;
        while (temp != NULL)
        {
            if (strcasecmp(temp->name, name) == 0) //  compares string1 and string2 without sensitivity to case
            {
                    flag = true;
                    printf("name %s :\n", temp->name);
                    printf("phone: %s \n", temp->phone);
                    printf("note: %s \n",  temp->note);
            }
            temp = temp->next;
        }
     }

     else if (select ==2)
     {
        printf("Enter the Note you want to search :");
        scanf("%s", note);

        struct entry *temp = head;
        while (temp != NULL)
        {
            if (strcasecmp(temp->note, note) == 0) //  compares string1 and string2 without sensitivity to case
            {
                    flag = true;
                    printf("name %s :\n", temp->name);
                    printf("phone: %s \n", temp->phone);
                    printf("note: %s \n",  temp->note);
            }
            temp = temp->next;
        }
     }


     if (flag == false && (select==1 || select ==2))
         printf("sorry we cannot find the entity your search!\n");
    }

}

//this function helps to updateNme class
void updateHelper(struct entry** head_ref, int id)
{
    struct entry * temp = *head_ref, *prev;

    if (temp != NULL && temp->id == id)
    {

        *head_ref = temp->next; // head become next new_node
        printf("Entry is successfully updated.\n");
        free(temp);
        return;

    }

    //find the previous node
    while (temp != NULL && temp->id != id){
        prev = temp;
        temp = temp->next;
    }

       if (temp == NULL) // we reach the end of the node
        return;

     prev->next = temp->next; // cut the delted node from chain
     printf("Entry is successfully updated.\n");
     free(temp); // we nned to unallocate memory
     return;
}


// this function is helper of updateEntry function
void updateName(struct entry* head, struct entry* temp, int id)
{
    char newName[50];
    char tempPhone[11];
    char tempNote [125];
    printf("Enter the new name:\n");
    scanf("%s",newName);


    strcpy(tempPhone, temp->phone);
    strcpy(tempNote, temp->note);


    updateHelper(&head,id); // I made delete and insert operation rather than sort linkedlist. Becasue, delete and insert operation gives
    //better result than sort in terms of time complexty

    struct entry* new_node = newNode(newName, tempPhone, tempNote);
    Insert(&head, new_node);
    printf("\nName is succesfully changed\n\n");
    printList(head);

}
// this function is helper of updateEntry function
void updatePhone(struct entry* head, struct entry* temp)
{// we do not need to sort linkedlist for updataing phonenumber because list is sorted according to name
    char tempPhone[11];
    printf("Enter the new phone number for '%s':\n", temp->name);
    scanf("%s",tempPhone);
    strcpy(temp->phone, tempPhone);
    printf("\nPhone number succesfully updated\n");
    printList(head);
}

void updateNote(struct entry * head, struct entry * temp)
{//we do not need to sort linkedlist for updataing phonenumber because list is sorted according to name
    char tempNote[125];
    printf("Enter the new note for '%s':\n", temp->name);
    scanf("%s",tempNote);
    strcpy(temp->note, tempNote);
    printf("\nNote is succesfully updated\n");
    printList(head);
}

void updateEntry(struct entry* head)
{
    if (head == NULL)
    {
        printf("List is EMPTY\n");
        return;
    }

    int personId;
    int lastEntityId;//the id of the person at the end of the list
    int select, i;
    struct entry * temp = head;

    lastEntityId = printList(head);
    //printf("latenttiyıd: %d\n", lastEntityId);
    printf("Enter the entity you want to update:\n");
    scanf("%d",&personId);

    if (personId<1 || personId > lastEntityId)
    {
        printf("\nInvalid entity position");
        system("PAUSE");
        return;
    }

    else
    {
        if (personId == 1)
        {
            temp = head;
        }

        else{
            for(i=1; i < personId; i++)
            {
                temp = temp->next;
                //printf("temp test phone: %s\n", temp->phone);
            }
        }


        do {
        printf("\n1-Update Name\n");
        printf("\n2-Update Phone\n");
        printf("\n3-Update Note\n");
        printf("\n4-Terminate the Update step\n");

        scanf("%d",&select);

        if (select == 1) //In this condition, we must pay attention to the order of the list.
        {
            updateName(head,temp,personId);
            break;
        }
        else if (select == 2)
        {
            updatePhone(head,temp);
            break;
        }

        else if (select == 3)
        {
            updateNote(head,temp);
        }

        }while(select !=4);
    }


}

void writeEntry(char filename[],struct entry* head)
{
    struct entry* temp = head;

    FILE* file;
    file = fopen(filename, "w");

    if (file == NULL)
    {
        fprintf(stderr, "\nCould not Open File\n");
        exit(1);
    }

    while (temp!=NULL)
    {


        fputs(temp->name, file) ;
        fputs("--", file) ;

        fputs(temp->phone, file) ;
        fputs("--", file) ;

        fputs(temp->note, file) ;
        //fputs("--", file) ;

        fputs("\n", file) ;

        temp= temp->next;
    }

    fclose(file) ;

    printf("Data successfully written \n");

}
struct entry* readEntry(char filename[],struct entry* head)
{

    char tempString[250];
    char * token;

    int i = 0;
    char * tempArray[3];
    tempArray[0] = (char*)malloc(50*
	sizeof(char)); //name
    tempArray[1] = (char*)malloc(11*
	sizeof(char)); //phone
    tempArray[2] = (char*)malloc(125*
	sizeof(char)); //note

    FILE *fptr;
    fptr = fopen(filename,"r");
    if (fptr == NULL)
    {
        printf("Error while opening file");
        exit(1);
    }

    while(fgets(tempString, sizeof(tempString),fptr) !=NULL)
    {


        token = strtok(tempString, "--");
        while(token != NULL)
        {

            tempArray[i] = token;
            token = strtok(NULL,"--");
            i++;
        }
        i = 0;


        struct entry* new_node = newNode(tempArray[0],tempArray[1],tempArray[2]);
        Insert(&head, new_node);


    }
    printList(head);

    return head;

}



