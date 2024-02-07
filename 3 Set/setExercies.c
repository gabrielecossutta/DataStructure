#include "linkedList.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define HASHMAP_SIZE 5 //number of nodes
#define HASHMAP_SIZE_LIST 2 // size of nodes



size_t djb33x_hash(const char *key, const size_t keylen)//method for hashing
{
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++)
    {
    hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

struct set_table *set_table_new(const size_t hashmap_size) // create a new table
{
    struct set_table *table = malloc(sizeof(struct set_table));// allocate space for the table
    if (!table)
    {
        return NULL;
    }

    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(struct set_node *));//resize the table for the nodes
    if (!table->nodes)
    {
        free(table);
        return NULL;
    }

    return table;
}

struct set_node *set_insert(struct set_table *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    struct set_node *head = table->nodes[index];

    
    struct set_node *current = head;
    while (current)
    {
        if (strcmp(current->key, key) == 0)// check if the key is already in the set
        {
            printf("Key: %s already exists, duplicate keys not allowed\n", key);
            return NULL;
        }
        current = current->next;
    }

    size_t node_count = 0;
    current = head;
    while (current)
    {
        node_count++;
        current = current->next;
    }

    // control of the number of nodes in a node[index] is superior of HASHMAP SIZE LIST
    if (node_count >= HASHMAP_SIZE_LIST)
    {
        printf("Collision impossible to append this key\n");
        return NULL;
    }
    struct set_node *new_item = list_append(table,key,key_len,index);
    return new_item;
    
}

int set_search(struct set_table *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    struct set_node *head = table->nodes[index];
    if (!head)
    {
        printf("node not found");
        return -1;
    }
    struct set_node *current = head;
    struct set_node *previous = NULL;
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

struct set_node *set_remove(struct set_table *table, const char *key, const size_t key_len)//remove a node given the key
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    struct set_node *head = table->nodes[index];
    while(head)
    {
         if (strcmp(head->key, key) == 0)
         {
            list_remove_item(table,key,index);
         }
         head = head->next;
    }
    return NULL;
}

void print_set(const struct set_table *table)
{
    for (int i = 0; i < table->hashmap_size; i++)
    {
        struct set_node *current = table->nodes[i];
        print_list(current,i); // function of linkedlistcopy
        printf("NULL\n");
    }
}

int main()
{
    struct set_table *myset = set_table_new(HASHMAP_SIZE);
    if (!myset)
    {
        fprintf(stderr, "Failed to create set_table\n");
        return 1;
    }

    set_insert(myset, "Hello0", strlen("Hello0"));
    set_insert(myset, "Hello1", strlen("Hello1"));
    set_insert(myset, "Hello2", strlen("Hello2"));
    set_insert(myset, "Hello3", strlen("Hello3"));
    set_insert(myset, "Hello4", strlen("Hello4"));
    set_insert(myset, "Hello5", strlen("Hello5"));
    printf("\n \nNodes:\n");
    print_set(myset);
    printf("\n \nSearch Hello3:\n");
    set_search(myset, "Hello3", strlen("Hello3"));
    printf("\n \nRemove Hello3:\n");
    set_remove(myset, "Hello3", strlen("Hello3"));
    printf("\n");
    print_set(myset);
    printf("\n \nSearch Hello3:\n");
    set_search(myset, "Hello3", strlen("Hello3"));
    printf("\n \nInsert Hello 4:\n");
    set_insert(myset, "Hello4", strlen("Hello4"));
    printf("\n");
    print_set(myset);

    return 0;
}

//clang -o .\c\setExercies.exe .\c\setExercies.c .\c\linkedListCopy.c -I .\c\linkedList.h