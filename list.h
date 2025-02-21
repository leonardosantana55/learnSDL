#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

// structure for each node or element in the linked list
typedef struct ListElement_ {

    void *data;
    struct ListElement_ *next;

} ListElement;


// structure for the linked list
typedef struct List_ {

    int size;

    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);

    ListElement *head;
    ListElement *tail;

} List;




