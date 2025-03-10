#ifndef MY_LIST
#define MYLIST

#include <stdlib.h>

typedef struct Node_{
    void *data;
    struct Node_ *next;
} Node;

typedef struct LinkedList_{
    int size;
    Node *tail;
    Node *head;
} LinkedList;

void LinkedList_Init(LinkedList *list);

int LinkedList_Insert(LinkedList *list, Node *node, const void *data);

//int LinkedList_Append(LinkedList *list, const void *data);
//
//int LinkedList_Prepend(LinkedList *list, const void *data);
//
//int LinkedList_Remove(LinkedList *list, const void *data);



#endif
