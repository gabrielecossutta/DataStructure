#include "linkedList.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int list_length(struct set_node *head)
{
    int i = 0;
    while (head)
    {
        i++;
        head = head->next;
    }
    return i;
}

struct set_node* list_append(struct set_table *table, const char* item, size_t key_len,size_t index)
{
    
    struct set_node *head = table->nodes[index];
    struct set_node *new_item = malloc(sizeof(struct set_node));
    if (!new_item)
    {
        return NULL;
    }

    new_item->key = item;
    new_item->key_len = key_len;
    new_item->next = NULL;

    if (!head)
    {
        table->nodes[index] = new_item;
        printf("New key: %s appended\n", item);
        return new_item;
    }

    //append the new key
    struct set_node *tail = head;
    while (tail->next)
    {
        tail = tail->next;
    }

    tail->next = new_item;
    printf("New key: %s appended\n", item);
    return new_item;
}

int list_remove_item(struct set_table *table, const char* item, size_t index)
{
    
    struct set_node *head = table->nodes[index];
    struct set_node *previous = NULL;
    if (previous)//if the node is the first we need to reimpost the previous node
    {
       previous->next = head->next;
    }
    else
    {
       table->nodes[index] = head->next;
    }

    free(head);
    printf("key: %s removed\n",item);
             
    return 0;
}


void print_list(struct set_node *head,int i)
{
    printf("Node %d: ", i);
        while (head)
        {
            printf("(%s) -> ", head->key);
            head = head->next;
        }
}
