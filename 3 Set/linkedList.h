#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct SetNode
{
    const char *key; //string of the node
    size_t KeyLen; //string length
    struct SetNode *next;//pointer of the next node
};

struct SetTable // contain all the nodes
{
    struct SetNode **nodes; //pointer of nodes
    size_t HashmapSize;
};

//function declaration
struct SetNode* ListAppend(struct SetTable *table, const char* item,size_t KeyLen,size_t index);
int ListRemoveItem(struct SetTable *table, const char* item,size_t index);
void PrintList(struct SetNode *head, int i);
#endif
