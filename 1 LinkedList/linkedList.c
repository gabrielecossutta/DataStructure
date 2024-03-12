#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define countStart 0 //define

struct ListItem 
{
    struct ListItem *next; //pointer of the next node
    int value; //value of the pointer
};

unsigned int ListLength(const struct ListItem *head) // scrolls through the entire list and return the lenght of the list
{
    int i = countStart;
    while (head)
    {
        i++;
        head = head->next;
    }
    return i;
}

struct ListItem *ListGetTail(  struct ListItem **head) //return the last node of the list
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

int ListAppend(struct ListItem **head, const int item) //allow to append a element at the end of the list
{
    if (!head)
    {
        printf("the list is not initializzated.\n");
        return -1;
    }
    struct ListItem *tail = ListGetTail(head); //last element of the list
    if (!tail)//if there is no tail it means that this element is the first of the list
    {
        (*head) = malloc(sizeof(struct ListItem)); //alloc space for the node
        if (!(*head))
        {
            printf("allocation error.\n");
            return -1;
        }
        (*head)->value = item; 
        (*head)->next = NULL;
    }
    else
    { 
        struct ListItem *NewItem = malloc(sizeof(struct ListItem));//alloc space for the node
        if (!NewItem)
        {
            printf("allocation error.\n");
            return -1;
        }
        NewItem->value = item;
        NewItem->next = NULL;
        tail->next = NewItem;
    }
    printf("\nValue %d appended\n", item);
    return 0;
}

int ListRemoveIndex(struct ListItem **head,const int index) //remove a value from the list given a index of the list
{
    if (!head || index < 1)
    {
        printf("cant remove index below zero.\n");
        return -1;
    }

    struct ListItem *current = *head; //pointer for the current node
    struct ListItem *previous = NULL; //pointer for the preveiouse node of current node
    int i = countStart;

    while (current && i < index) //search the node with the specified index
    {
        i++;
        previous = current;
        current = current->next;
    }

    if (!current)
    {
        printf("index too high.\n");
        return 1;
    }

    if (previous) 
    {
        previous->next = current->next;
    }
    else //if the null it means that the current node is the first node
    {
        *head = current->next;
    }
    printf("\nNode %d removed", index);
    free(current);
    return 0;
}

int ListRemoveItem(struct ListItem **head, const int item) //remove a value from the list given a value of the list
{
    if (!head)
    {
        printf("list not initializated correctly.\n");
        return -1;
    }

    struct ListItem *current = *head;
    struct ListItem *previous = NULL;

    while (current && item != current->value)
    {
        previous = current;
        current = current->next;
    }

    if (!current)
    {
        printf("element not find.\n");
        return 0;
    }

    if (previous)
    {
        previous->next = current->next;
    }
    else
    {
        *head = current->next;
    }

    printf("\nNode with value %d removed", item);
    free(current);
    return 0;
}

int ListReverse(struct ListItem **head)//allow to reverse the list
{
    if (!head || !(*head))
    {
        printf("list empty or not initializated.\n");
        return -1;
    }

    if (ListLength(*head) <= 1)//if the list as only one element you dont need to reverse the list )
    {
        return 0;
    }

    struct ListItem *ReversedList = NULL; // empty list for the reverse
    struct ListItem *current = *head; // copy of the list

    while(current)  
    {
        struct ListItem *next = current->next;
        current->next = ReversedList; 
        ReversedList = current;
        current = next;
    }
    *head = ReversedList;
    return 0;
}

void PrintList(const struct ListItem *head)//allow to print the list
{
    printf("\n");
    int i=countStart;
    while (head)
    {   
        i++;
        printf("-index:%d ",i);
        printf("|%p ", head);
        printf("value: %d| ", head->value);
        head = head->next;
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

    printf("List:");
    PrintList(head);

    ListRemoveIndex(&head, 2);
    printf("\n\nlist after removal of index 2: ");
    PrintList(head);

    ListRemoveItem(&head, 100);
    printf("\n\nlist after removal of value 100: ");
    PrintList(head);

    ListReverse(&head);
    printf("\nlist reversed: ");
    PrintList(head);

    return 0;
}

//clang.exe -o .\c\linkedList.exe  .\c\linkedList.c