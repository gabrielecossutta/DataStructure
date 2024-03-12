#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
struct ListItem
{
    struct ListItem *next; //pointer of the next node
    struct ListItem *prev; //pointer of the previous node
    int value;  //value of the pointer
};

struct ListItem *ListGetTail( struct ListItem **head)//return the last node of the list
{
    if (!head || !(*head))
    {
        printf("the list is empty or not initializzated.\n");
        return NULL;
    }
    struct ListItem *CurrentItem = *head; //copy of the list
    while (CurrentItem->next) //scrolls the list until it find the last element with no next node 
    {
        CurrentItem = CurrentItem->next;
    }
    return CurrentItem;
}

int ListAppend(struct  ListItem **head,const int item) //allow to append a element at the end of the list
{
    if (!head)
    {
        printf("the list is empty or not initializzated.\n");
        return -1;
    }
    struct ListItem *tail = ListGetTail(head);//last element of the list
    if (!tail)//if there is no tail it means that this element is the first of the list
    {
        (*head) = malloc(sizeof(struct ListItem));//alloc space for the node
        (*head)->value = item;
        (*head)->next = NULL;
        (*head)->prev=NULL;
    }
    else
    {
        struct ListItem *NewItem = malloc(sizeof(struct ListItem));//alloc space for the node
        NewItem->value = item;
        NewItem->next = NULL;
        NewItem->prev=tail;
        tail->next = NewItem;
    }
    printf("Value %d appended\n", item);
    return 0;
};

int ListAppendAfter(struct ListItem **head,const int item, const int index) //allow to append a element after another node given a index
{
    if (!head)
    {
        printf("the list is empty or not initializzated.\n");
        return -1;
    }

    int i = 1;
    struct ListItem *current = *head;

    while (current && i < index)//search the note by the index
    {
        i++;
        current = current->next;
    }

    if (!current)//control if the node is valid
    {
        printf("invalid index\n");
        return -1;
    }

    
    struct ListItem *NewItem = malloc(sizeof(struct ListItem)); //alloc space for the node
    NewItem->value = item;
    NewItem->prev = current;
    NewItem->next = current->next;

    
    if (current->next)
    {
        current->next->prev = NewItem;
    }

    current->next = NewItem;
    printf("\nValue %d appended after index %d\n", item,index);
    return 0;
}

int ListAppendBefore(struct  ListItem **head,const int item,const int index) //allow to append a element before another node given a index
{
    if (!head)
    {
        printf("the list is empty or not initializzated\n");
        return -1;
    }

    int i = 1;
    struct ListItem *current = *head;

    //serach  node by index
    while (current && i < index)
    {
        i++;
        current = current->next;
    }
    
    //control if the node is valid
    if (!current)
    {
        printf("invalid index\n");
        return -1;
    }

    // Create new node
    struct ListItem *NewItem = malloc(sizeof(struct ListItem));
    NewItem->value = item;
    NewItem->next = current;
    
    if (current->prev)
    {  
        NewItem->prev = current->prev;
        current->prev->next = NewItem;
        current->prev = NewItem;
    }
    else
    {
        NewItem->prev=NULL;
        *head = NewItem;
    }
    printf("\nValue %d appended before index %d\n", item,index);
    return 0;
};
        

int ListRemoveIndex(struct ListItem** head,const int index)
{
    if (!head || index < 1)
    {
        printf("cant remove index below zero\n");
        return -1;
    }

    struct ListItem* current = *head;

    int i = 1;
    while (current && i < index) //search the node with the specified index
    {
        current = current->next;
        i++;
    }

    if (!current)
    {
        printf("element not found\n");
        return 1;
    }

    if (current->prev)
    {
        current->prev->next = current->next;
    }
    else
    {
        *head = current->next;
    }

    if (current->next)
    {
        current->next->prev = current->prev;
    }

    printf("\nNode %d removed", index);
    free(current);
    return 0;
}

int ListRemoveItem(struct ListItem** head, const int item )
{
    if (!head)
    {
        printf("list not initializated correctly\n");
        return -1;
    }

    struct ListItem* current = *head;
    while (current && current->value != item) //search the node with the specified value
    {
        current = current->next;
    }

    if (!current)
    {
        printf("invalid node\n");
        return 1;
    }

    if (current->prev)
    {
        current->prev->next = current->next;
    }
    else
    {
        *head = current->next;
    }

    if (current->next)
    {
        current->next->prev = current->prev;
    }

    printf("\nNode with value %d removed", item);
    free(current);
    return 0;
}

void PrintList(const struct ListItem *head)//allow to print the list
{
    printf("\n");
    int i=1;
    while (head)
    {   printf("-index:%d ",i);
        printf("|%p ", head);
        printf("value: %d| ", head->value);
        head = head->next;
        i++;
    }
    printf("\n");
}

int main()
{
    struct ListItem *head = NULL;
   
    ListAppend(&head, 100);
    ListAppend(&head, 200);
    ListAppend(&head, 300);
    ListAppend(&head, 400);

    printf("\nList:");
    PrintList(head);

    ListRemoveIndex(&head, 2);
    printf("\n\nlist after removal of index 2: ");
    PrintList(head);

    ListRemoveItem(&head, 100);
    printf("\n\nlist after removal of value 100: ");
    PrintList(head);

    ListAppendAfter(&head, 450, 2);
    printf("\n\nlist after hanging after index 2: ");
    PrintList(head);

    ListAppendBefore(&head, 350, 2);
    printf("\n\nlist before hanging after index 2:");
    PrintList(head);

    return 0;
}
//clang.exe -o .\c\doubleLinked.exe  .\c\doubleLinked.c