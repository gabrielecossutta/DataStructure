#include "linkedList.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define HASHMAP_SIZE 5 //number of nodes
#define HASHMAP_SIZE_LIST 2 // size of nodes



size_t Djb33xHash(const char *key, const size_t keylen)//method for hashing
{
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++)
    {
    hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

struct SetTable *SetTableNew(const size_t HashmapSize) // create a new table
{
    struct SetTable *table = malloc(sizeof(struct SetTable));// allocate space for the table
    if (!table)
    {
        return NULL;
    }

    table->HashmapSize = HashmapSize;
    table->nodes = calloc(table->HashmapSize, sizeof(struct SetNode *));//resize the table for the nodes
    if (!table->nodes)
    {
        free(table);
        return NULL;
    }

    return table;
}

struct SetNode *SetInsert(struct SetTable *table, const char *key, const size_t KeyLen)
{
    size_t hash = Djb33xHash(key, KeyLen);
    size_t index = hash % table->HashmapSize;
    struct SetNode *head = table->nodes[index];

    
    struct SetNode *current = head;
    while (current)
    {
        if (strcmp(current->key, key) == 0)// check if the key is already in the set
        {
            printf("Key: %s already exists, duplicate keys not allowed\n", key);
            return NULL;
        }
        current = current->next;
    }

    size_t NodeCount = 0;
    current = head;
    while (current)
    {
        NodeCount++;
        current = current->next;
    }

    // control of the number of nodes in a node[index] is superior of HASHMAP SIZE LIST
    if (NodeCount >= HASHMAP_SIZE_LIST)
    {
        printf("Collision impossible to append this key\n");
        return NULL;
    }
    struct SetNode *NewItem = ListAppend(table,key,KeyLen,index);
    return NewItem;
    
}

int SetSearch(struct SetTable *table, const char *key, const size_t KeyLen)
{
    size_t hash = Djb33xHash(key, KeyLen);
    size_t index = hash % table->HashmapSize;
    struct SetNode *head = table->nodes[index];
    if (!head)
    {
        printf("node not found");
        return -1;
    }
    struct SetNode *current = head;
    struct SetNode *previous = NULL;
    while (head)
    {  
        previous = current;
        current = current->next; 
        
        if (strcmp(head->key, key) == 0)
        {
            printf("Key: %s found in node: %p\n", key,head);
        }
        head = head->next;
    }
    return 0;
}

struct SetNode *SetRemove(struct SetTable *table, const char *key, const size_t KeyLen)//remove a node given the key
{
    size_t hash = Djb33xHash(key, KeyLen);
    size_t index = hash % table->HashmapSize;
    struct SetNode *head = table->nodes[index];
    while(head)
    {
         if (strcmp(head->key, key) == 0)
         {
            ListRemoveItem(table,key,index);
         }
         head = head->next;
    }
    return NULL;
}

void PrintSet(const struct SetTable *table)
{
    for (int i = 0; i < table->HashmapSize; i++)
    {
        struct SetNode *current = table->nodes[i];
        PrintList(current,i); // function of linkedlistcopy
        printf("NULL\n");
    }
}

int main()
{
    struct SetTable *myset = SetTableNew(HASHMAP_SIZE);
    if (!myset)
    {
        fprintf(stderr, "Failed to create SetTable\n");
        return 1;
    }

    SetInsert(myset, "Hello0", strlen("Hello0"));
    SetInsert(myset, "Hello1", strlen("Hello1"));
    SetInsert(myset, "Hello2", strlen("Hello2"));
    SetInsert(myset, "Hello3", strlen("Hello3"));
    SetInsert(myset, "Hello4", strlen("Hello4"));
    SetInsert(myset, "Hello5", strlen("Hello5"));
    printf("\n \nNodes:\n");
    PrintSet(myset);
    printf("\n \nSearch Hello3:\n");
    SetSearch(myset, "Hello3", strlen("Hello3"));
    printf("\n \nRemove Hello3:\n");
    SetRemove(myset, "Hello3", strlen("Hello3"));
    printf("\n");
    PrintSet(myset);
    printf("\n \nSearch Hello3:\n");
    SetSearch(myset, "Hello3", strlen("Hello3"));
    printf("\n \nInsert Hello 4:\n");
    SetInsert(myset, "Hello4", strlen("Hello4"));
    printf("\n");
    PrintSet(myset);

    return 0;
}

//clang -o .\c\setExercies.exe .\c\setExercies.c .\c\linkedListCopy.c -I .\c\linkedList.h