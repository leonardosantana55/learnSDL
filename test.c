#include <stdio.h>

#include "mylist.h"

int main(){

    LinkedList *mylist = (LinkedList *)malloc(sizeof(LinkedList));
    if(mylist == NULL){
        return -1;
    }

    LinkedList_Init(mylist);

    // insert items in list
    int size = 10;
    float testarray[size];

    for (int i=0; i<size; i++){

        testarray[i] = i*0.2;
        LinkedList_Insert(mylist, NULL, &testarray[i]);

    }

    // inser item in the middle
    Node *middle = NULL;
    for(int i=0; i<3; i++){
        middle = mylist->head->next;
    }

    LinkedList_Insert(mylist, middle, &testarray[9]);

    float *removed = (float *)malloc(sizeof(float));
    LinkedList_Remove(mylist, NULL, (void **)&removed);
    printf("removed: %.2f\n", *removed);

    LinkedList_Remove(mylist, NULL, (void **)&removed);
    printf("removed: %.2f\n", *removed);

    LinkedList_Remove(mylist, NULL, (void **)&removed);
    printf("removed: %.2f\n", *removed);

    LinkedList_Remove(mylist, NULL, (void **)&removed);
    printf("removed: %.2f\n", *removed);


    //print list
    printf("size: %d\n", mylist->size);

    Node *temp = mylist->head;
    while(temp != NULL){

        printf("%.2f\n", *(float *)temp->data);
        temp = temp->next;

    }


    printf("tail: %.2f\n", *(float *)mylist->tail->data);
    printf("head: %.2f\n", *(float *)mylist->head->data);

    return 0;
}


// TODO: test remove function more
