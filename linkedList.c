#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define countStart 0 //define

struct list_item 
{
    struct list_item *next; //pointer of the next node
    int value; //value of the pointer
};

unsigned int list_length(const struct list_item *head) // scrolls through the entire list and return the lenght of the list
{
    int i = countStart;
    while (head)
    {
        i++;
        head = head->next;
    }
    return i;
}

struct list_item *list_get_tail(  struct list_item **head) //return the last node of the list
{
    if (!head || !(*head))
    {
        printf("the list is empty or not initializzated.\n");
        return NULL;
    }
    struct list_item *current_item = *head; //copy of the list
    while (current_item->next) //scrolls the list until it find the last element with no next node 
    {
        current_item = current_item->next;
    }
    return current_item;
}

int list_append(struct list_item **head, const int item) //allow to append a element at the end of the list
{
    if (!head)
    {
        printf("the list is not initializzated.\n");
        return -1;
    }
    struct list_item *tail = list_get_tail(head); //last element of the list
    if (!tail)//if there is no tail it means that this element is the first of the list
    {
        (*head) = malloc(sizeof(struct list_item)); //alloc space for the node
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
        struct list_item *new_item = malloc(sizeof(struct list_item));//alloc space for the node
        if (!new_item)
        {
            printf("allocation error.\n");
            return -1;
        }
        new_item->value = item;
        new_item->next = NULL;
        tail->next = new_item;
    }
    printf("\nValue %d appended\n", item);
    return 0;
}

int list_remove_index(struct list_item **head,const int index) //remove a value from the list given a index of the list
{
    if (!head || index < 1)
    {
        printf("cant remove index below zero.\n");
        return -1;
    }

    struct list_item *current = *head; //pointer for the current node
    struct list_item *previous = NULL; //pointer for the preveiouse node of current node
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

int list_remove_item(struct list_item **head, const int item) //remove a value from the list given a value of the list
{
    if (!head)
    {
        printf("list not initializated correctly.\n");
        return -1;
    }

    struct list_item *current = *head;
    struct list_item *previous = NULL;

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

int list_reverse(struct list_item **head)//allow to reverse the list
{
    if (!head || !(*head))
    {
        printf("list empty or not initializated.\n");
        return -1;
    }

    if (list_length(*head) <= 1)//if the list as only one element you dont need to reverse the list )
    {
        return 0;
    }

    struct list_item *reversed_list = NULL; // empty list for the reverse
    struct list_item *current = *head; // copy of the list

    while(current)  
    {
        struct list_item *next = current->next;
        current->next = reversed_list; 
        reversed_list = current;
        current = next;
    }
    *head = reversed_list;
    return 0;
}

void print_list(const struct list_item *head)//allow to print the list
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
    struct list_item *head = NULL;

    list_append(&head, 100);
    list_append(&head, 200);
    list_append(&head, 300);
    list_append(&head, 400);

    printf("List:");
    print_list(head);

    list_remove_index(&head, 2);
    printf("\n\nlist after removal of index 2: ");
    print_list(head);

    list_remove_item(&head, 100);
    printf("\n\nlist after removal of value 100: ");
    print_list(head);

    list_reverse(&head);
    printf("\nlist reversed: ");
    print_list(head);

    return 0;
}

//clang.exe -o .\c\linkedList.exe  .\c\linkedList.c