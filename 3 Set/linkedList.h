#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct set_node
{
    const char *key; //string of the node
    size_t key_len; //string length
    struct set_node *next;//pointer of the next node
};

struct set_table // contain all the nodes
{
    struct set_node **nodes; //pointer of nodes
    size_t hashmap_size;
};

//function declaration
struct set_node* list_append(struct set_table *table, const char* item,size_t key_len,size_t index);
int list_remove_item(struct set_table *table, const char* item,size_t index);
void print_list(struct set_node *head, int i);
#endif
