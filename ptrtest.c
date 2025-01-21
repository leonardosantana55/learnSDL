#include <stdio.h>


void secondTestFunc(int* ptr){
    *ptr = 30;
}

void ptrTestFunc(int* ptr){
    *ptr = 20;
    secondTestFunc(ptr);
}

int main(){
    int test = 10;
    int* ptr = &test;
    ptrTestFunc(ptr);
    printf("%d\n", *ptr);
    return 0;
}
