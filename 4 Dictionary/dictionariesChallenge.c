#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define maxCollision 2

struct DicNode {
    const char *key;  // string of the node
    size_t KeyLen;    // string length
    void *value;       // generic value associated with the key
};

struct DicTable {
    struct DicNode **nodes;  // pointer of nodes
    size_t HashmapSize;
    size_t NumElements;      // number of elements
};

int collision = 0;

size_t Djb33xHash(const char *key, const size_t keylen) //method for hashing
{
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++) {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

struct DicTable *SetTableNew(const size_t InitialSize) // create a new table
{
    struct DicTable *table = malloc(sizeof(struct DicTable));
    if (!table) {
        return NULL;
    }
    table->HashmapSize = InitialSize;
    table->nodes = calloc(table->HashmapSize, sizeof(struct DicNode *));
    if (!table->nodes) {
        free(table);
        return NULL;
    }
    table->NumElements = 0;
    return table;
}

int resize_and_rehash(struct DicTable *table) //allow the resize and the rehashing of the table
{
    size_t NewSize = table->HashmapSize*2;
    struct DicNode **new_nodes = calloc(NewSize, sizeof(struct DicNode *));
    if (!new_nodes) 
    {
        printf("impossible resize the map\n");
        return -1;
    }

    for (size_t i = 0; i < table->HashmapSize; i++) 
    {
        struct DicNode *current = table->nodes[i];
        while (current) 
        {
            size_t new_index = Djb33xHash(current->key, current->KeyLen) % NewSize;
            while (new_nodes[new_index] != NULL)
            {
                new_index = (new_index + 1) % NewSize;
            }
            new_nodes[new_index] = current;
            current = NULL;
        }
    }

    free(table->nodes);
    table->nodes = new_nodes;
    table->HashmapSize = NewSize;
    if (collision<2)
    {
        printf("\nRehashing, table too small\n\n");
    }
    else
    {
        printf("\nRehashing, too many collisione\n\n");
    }
    
    
    collision=0;
    return 0;
}

int DicSearch(struct DicTable *table, const char *key, const size_t KeyLen) //allow to search a key
{
    size_t hash = Djb33xHash(key, KeyLen);
    size_t index = hash % table->HashmapSize;

    while (table->nodes[index] != NULL) 
    {
        if (table->nodes[index]->KeyLen == KeyLen && strncmp(table->nodes[index]->key, key, KeyLen) == 0) 
        {
            return -1;
        }
        index = (index + 1) % table->HashmapSize;
    }
    return 0;
}

struct DicNode *DicInsert(struct DicTable *table, const char *key, const size_t KeyLen, const void *value) {
    
    if (DicSearch(table, key, KeyLen)) {
        printf("Key: %s already in the table. Change key.\n",key);
        return NULL;
    }

    size_t hash = Djb33xHash(key, KeyLen);
    size_t index = hash % table->HashmapSize;

    if (table->nodes[index] != NULL) 
    {
            collision++;
            printf("Key: %s caused a collision\n",key);
            if (collision>=maxCollision) 
            {
                resize_and_rehash(table);
            }
            
            return NULL;
    }

    table->nodes[index] = malloc(sizeof(struct DicNode));
    if (!table->nodes[index]) {
        return NULL;
    }

    table->nodes[index]->key = _strdup(key);
    if (!table->nodes[index]->key) {
        free(table->nodes[index]);
        return NULL;
    }

    table->nodes[index]->KeyLen = KeyLen;
    table->nodes[index]->value = malloc(sizeof(void*));
    if (!table->nodes[index]->value) {
        free((void*)table->nodes[index]->key);
        free(table->nodes[index]);
        return NULL;
    }

    memcpy(table->nodes[index]->value, &value, sizeof(void*));
    table->NumElements++;
    if (collision>=maxCollision||(double)table->NumElements / table->HashmapSize > 0.7) 
    {
        resize_and_rehash(table);
    }
    printf("Key: %s inserted\n",key);
    return table->nodes[index];
}

int DicRemove(struct DicTable *table, const char *key, const size_t KeyLen) //allow to remove a key from the table
{
    size_t hash = Djb33xHash(key, KeyLen);
    size_t index = hash % table->HashmapSize;

    while (table->nodes[index] != NULL) 
    {
        if (table->nodes[index]->KeyLen == KeyLen && strncmp(table->nodes[index]->key, key, KeyLen) == 0) 
        {
            free((void *)table->nodes[index]->key);
            free(table->nodes[index]);
            table->nodes[index] = NULL;
            printf("Key: %s removed\n",key);
            table->NumElements--;

            return 0;
        }
        index = (index + 1) % table->HashmapSize;
    }
    printf("value not found, cannot be removed\n");
    return 0;
}


void PrintDic(struct DicTable *table) //allow to print the dictionary
{
    for (size_t i = 0; i < table->HashmapSize; i++) {
        struct DicNode *current = table->nodes[i];
        printf("Node %zu: ", i+1);

        if (current != NULL) {
            printf("Key: %s, Value: %p\n", current->key, current->value);
        } else {
            printf("NULL\n");
        }
    }
}

int main() 
{
    int HASHMAP_SIZE = 3;
    struct DicTable *myset = SetTableNew(HASHMAP_SIZE);

    if (!myset) 
    {
        printf("error in the creation of the table\n");
        return 1;
    }
    const int value1 = 100;
    const double value2 = 3.14;
    const char* value3 = "Hello";

    DicInsert(myset, "Hello1", strlen("Hello1"), &value1);
    DicInsert(myset, "Hello2", strlen("Hello2"), &value2);
    printf("\n");
    PrintDic(myset);
    printf("\n");
    DicInsert(myset, "Hello3", strlen("Hello3"), &value3);
    DicInsert(myset, "Hello4", strlen("Hello4"), &value1);
    DicInsert(myset, "Hello5", strlen("Hello5"), &value2);
    DicInsert(myset, "Hello6", strlen("Hello6"), &value3);
    DicInsert(myset, "Hello7", strlen("Hello7"), &value1);
    DicInsert(myset, "Hello8", strlen("Hello8"), &value2);
    DicInsert(myset, "Hello9", strlen("Hello9"), &value3);
    PrintDic(myset);
    
    return 0;
}

//clang.exe -o .\c\dictionariesChallenge.exe .\c\dictionariesChallenge.c