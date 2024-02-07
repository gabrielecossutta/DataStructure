#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define maxCollision 2

struct dic_node {
    const char *key;  // string of the node
    size_t key_len;    // string length
    void *value;       // generic value associated with the key
};

struct dic_table {
    struct dic_node **nodes;  // pointer of nodes
    size_t hashmap_size;
    size_t num_elements;      // number of elements
};

int collision = 0;

size_t djb33x_hash(const char *key, const size_t keylen) //method for hashing
{
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++) {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

struct dic_table *set_table_new(const size_t initial_size) // create a new table
{
    struct dic_table *table = malloc(sizeof(struct dic_table));
    if (!table) {
        return NULL;
    }
    table->hashmap_size = initial_size;
    table->nodes = calloc(table->hashmap_size, sizeof(struct dic_node *));
    if (!table->nodes) {
        free(table);
        return NULL;
    }
    table->num_elements = 0;
    return table;
}

int resize_and_rehash(struct dic_table *table) //allow the resize and the rehashing of the table
{
    size_t new_size = table->hashmap_size*2;
    struct dic_node **new_nodes = calloc(new_size, sizeof(struct dic_node *));
    if (!new_nodes) 
    {
        printf("impossible resize the map\n");
        return -1;
    }

    for (size_t i = 0; i < table->hashmap_size; i++) 
    {
        struct dic_node *current = table->nodes[i];
        while (current) 
        {
            size_t new_index = djb33x_hash(current->key, current->key_len) % new_size;
            while (new_nodes[new_index] != NULL)
            {
                new_index = (new_index + 1) % new_size;
            }
            new_nodes[new_index] = current;
            current = NULL;
        }
    }

    free(table->nodes);
    table->nodes = new_nodes;
    table->hashmap_size = new_size;
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

int dic_search(struct dic_table *table, const char *key, const size_t key_len) //allow to search a key
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;

    while (table->nodes[index] != NULL) 
    {
        if (table->nodes[index]->key_len == key_len && strncmp(table->nodes[index]->key, key, key_len) == 0) 
        {
            return -1;
        }
        index = (index + 1) % table->hashmap_size;
    }
    return 0;
}

struct dic_node *dic_insert(struct dic_table *table, const char *key, const size_t key_len, const void *value) {
    
    if (dic_search(table, key, key_len)) {
        printf("Key: %s already in the table. Change key.\n",key);
        return NULL;
    }

    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;

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

    table->nodes[index] = malloc(sizeof(struct dic_node));
    if (!table->nodes[index]) {
        return NULL;
    }

    table->nodes[index]->key = _strdup(key);
    if (!table->nodes[index]->key) {
        free(table->nodes[index]);
        return NULL;
    }

    table->nodes[index]->key_len = key_len;
    table->nodes[index]->value = malloc(sizeof(void*));
    if (!table->nodes[index]->value) {
        free((void*)table->nodes[index]->key);
        free(table->nodes[index]);
        return NULL;
    }

    memcpy(table->nodes[index]->value, &value, sizeof(void*));
    table->num_elements++;
    if (collision>=maxCollision||(double)table->num_elements / table->hashmap_size > 0.7) 
    {
        resize_and_rehash(table);
    }
    printf("Key: %s inserted\n",key);
    return table->nodes[index];
}

int dic_remove(struct dic_table *table, const char *key, const size_t key_len) //allow to remove a key from the table
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;

    while (table->nodes[index] != NULL) 
    {
        if (table->nodes[index]->key_len == key_len && strncmp(table->nodes[index]->key, key, key_len) == 0) 
        {
            free((void *)table->nodes[index]->key);
            free(table->nodes[index]);
            table->nodes[index] = NULL;
            printf("Key: %s removed\n",key);
            table->num_elements--;

            return 0;
        }
        index = (index + 1) % table->hashmap_size;
    }
    printf("value not found, cannot be removed\n");
    return 0;
}


void print_dic(struct dic_table *table) //allow to print the dictionary
{
    for (size_t i = 0; i < table->hashmap_size; i++) {
        struct dic_node *current = table->nodes[i];
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
    struct dic_table *myset = set_table_new(HASHMAP_SIZE);

    if (!myset) 
    {
        printf("error in the creation of the table\n");
        return 1;
    }
    const int value1 = 100;
    const double value2 = 3.14;
    const char* value3 = "Hello";

    dic_insert(myset, "Hello1", strlen("Hello1"), &value1);
    dic_insert(myset, "Hello2", strlen("Hello2"), &value2);
    printf("\n");
    print_dic(myset);
    printf("\n");
    dic_insert(myset, "Hello3", strlen("Hello3"), &value3);
    dic_insert(myset, "Hello4", strlen("Hello4"), &value1);
    dic_insert(myset, "Hello5", strlen("Hello5"), &value2);
    dic_insert(myset, "Hello6", strlen("Hello6"), &value3);
    dic_insert(myset, "Hello7", strlen("Hello7"), &value1);
    dic_insert(myset, "Hello8", strlen("Hello8"), &value2);
    dic_insert(myset, "Hello9", strlen("Hello9"), &value3);
    print_dic(myset);
    
    return 0;
}

//clang.exe -o .\c\dictionariesChallenge.exe .\c\dictionariesChallenge.c