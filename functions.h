#ifndef FUNCTIONS_H
#define FUNCTIONS_H
struct entry{
   char name[50];
   char  phone[11];
   char note[125];
   struct entry* next;
};

struct entry* newNode(char *name, char *phone, char *note);
void Insert(struct entry** head_ref, struct entry* new_node);

int printList(struct entry* head);

void deleteEntry(struct entry** head_ref, int id);

void searchEntry(struct entry* head);

void updateName(struct entry* head, struct entry* temp, int id);
void updateEntry(struct entry* head);
int numberOfEntries(struct entry* head);
void writeEntry(char filename[],struct entry* head);
struct entry* readEntry(char filename[],struct entry* head);
#endif // FUNCTIONS_H
