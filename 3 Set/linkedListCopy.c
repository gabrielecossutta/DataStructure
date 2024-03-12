#include "linkedList.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int ListLength(struct SetNode *head)
{
    int i = 0;
    while (head)
    {
        i++;
        head = head->next;
    }
    return i;
}

struct SetNode* ListAppend(struct SetTable *table, const char* item, size_t KeyLen,size_t index)
{
    
    struct SetNode *head = table->nodes[index];
    struct SetNode *new_item = malloc(sizeof(struct SetNode));
    if (!new_item)
    {
        return NULL;
    }

    new_item->key = item;
    new_item->KeyLen = KeyLen;
    new_item->next = NULL;

    if (!head)
    {
        table->nodes[index] = new_item;
        printf("New key: %s appended\n", item);
        return new_item;
    }

    //append the new key
    struct SetNode *tail = head;
    while (tail->next)
    {
        tail = tail->next;
    }

    tail->next = new_item;
    printf("New key: %s appended\n", item);
    return new_item;
}

int ListRemoveItem(struct SetTable *table, const char* item, size_t index)
{
    
    struct SetNode *head = table->nodes[index];
    struct SetNode *previous = NULL;
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


void PrintList(struct SetNode *head,int i)
{
    printf("Node %d: ", i);
        while (head)
        {
            printf("(%s) -> ", head->key);
            head = head->next;
        }
}
