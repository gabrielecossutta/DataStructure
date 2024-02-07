#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
struct list_item
{
    struct list_item *next; //pointer of the next node
    struct list_item *prev; //pointer of the previous node
    int value;  //value of the pointer
};

struct list_item *list_get_tail( struct list_item **head)//return the last node of the list
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

int list_append(struct  list_item **head,const int item) //allow to append a element at the end of the list
{
    if (!head)
    {
        printf("the list is empty or not initializzated.\n");
        return -1;
    }
    struct list_item *tail = list_get_tail(head);//last element of the list
    if (!tail)//if there is no tail it means that this element is the first of the list
    {
        (*head) = malloc(sizeof(struct list_item));//alloc space for the node
        (*head)->value = item;
        (*head)->next = NULL;
        (*head)->prev=NULL;
    }
    else
    {
        struct list_item *new_item = malloc(sizeof(struct list_item));//alloc space for the node
        new_item->value = item;
        new_item->next = NULL;
        new_item->prev=tail;
        tail->next = new_item;
    }
    printf("Value %d appended\n", item);
    return 0;
};

int list_append_after(struct list_item **head,const int item, const int index) //allow to append a element after another node given a index
{
    if (!head)
    {
        printf("the list is empty or not initializzated.\n");
        return -1;
    }

    int i = 1;
    struct list_item *current = *head;

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

    
    struct list_item *new_item = malloc(sizeof(struct list_item)); //alloc space for the node
    new_item->value = item;
    new_item->prev = current;
    new_item->next = current->next;

    
    if (current->next)
    {
        current->next->prev = new_item;
    }

    current->next = new_item;
    printf("\nValue %d appended after index %d\n", item,index);
    return 0;
}

int list_append_before(struct  list_item **head,const int item,const int index) //allow to append a element before another node given a index
{
    if (!head)
    {
        printf("the list is empty or not initializzated\n");
        return -1;
    }

    int i = 1;
    struct list_item *current = *head;

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
    struct list_item *new_item = malloc(sizeof(struct list_item));
    new_item->value = item;
    new_item->next = current;
    
    if (current->prev)
    {  
        new_item->prev = current->prev;
        current->prev->next = new_item;
        current->prev = new_item;
    }
    else
    {
        new_item->prev=NULL;
        *head = new_item;
    }
    printf("\nValue %d appended before index %d\n", item,index);
    return 0;
};
        

int list_remove_index(struct list_item** head,const int index)
{
    if (!head || index < 1)
    {
        printf("cant remove index below zero\n");
        return -1;
    }

    struct list_item* current = *head;

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

int list_remove_item(struct list_item** head, const int item )
{
    if (!head)
    {
        printf("list not initializated correctly\n");
        return -1;
    }

    struct list_item* current = *head;
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

void print_list(const struct list_item *head)//allow to print the list
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
    struct list_item *head = NULL;
   
    list_append(&head, 100);
    list_append(&head, 200);
    list_append(&head, 300);
    list_append(&head, 400);

    printf("\nList:");
    print_list(head);

    list_remove_index(&head, 2);
    printf("\n\nlist after removal of index 2: ");
    print_list(head);

    list_remove_item(&head, 100);
    printf("\n\nlist after removal of value 100: ");
    print_list(head);

    list_append_after(&head, 450, 2);
    printf("\n\nlist after hanging after index 2: ");
    print_list(head);

    list_append_before(&head, 350, 2);
    printf("\n\nlist before hanging after index 2:");
    print_list(head);

    return 0;
}
//clang.exe -o .\c\doubleLinked.exe  .\c\doubleLinked.c