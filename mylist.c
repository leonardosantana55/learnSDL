#include <stdlib.h>

#include "mylist.h"


void LinkedList_Init(LinkedList *list){
    list->size = 0;
    list->tail = NULL;
    list->head = NULL;
    return;
}


int LinkedList_Insert(LinkedList *list, Node *node, const void *data){

    Node *new_node;
    new_node = (Node *)malloc(sizeof(Node));
    if(new_node == NULL){
        return -1;
    }

    //assign data to the new node
    new_node->data = (void *)data;

    //insertion at the head
    if (node == NULL){
        if (list->size == 0){
            //handle insert when list is empty
            list->tail = new_node;
        }

        new_node->next = list->head;
        list->head = new_node;
    }
    //insertion when node is not null
    else {
        //when the node thats been passed is in the head
        if(node->next == NULL){
            list->tail = new_node;
        }

        new_node->next = node->next;
        node->next = new_node;
    }

    list->size++;

    return 0;

}
