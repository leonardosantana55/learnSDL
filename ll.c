#include <stdio.h>

typedef struct Node_{
    void *value;
    struct Node_ *next;
}Node;

typedef struct LinkedList{
    Node* head;
    Node* tail;
    
}LinkedList;

int main(){
    printf("Hello world");
    return 0;
}
