#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct String_{

    char *string;
    int (*length)(struct String_ *self);

} String;


int stringLength(String *self){

    return strlen(self->string);

}

String *initString(int n){

    String *str = malloc(sizeof(String));
    str->string = malloc(sizeof(char) * n);
    str->length = stringLength;

    str->string[0] = '\0';

    return str;

}


int main(){

    String *mystring = initString(50);
    strcpy(mystring->string, "Leonardo, Joao Gabriel, Arthur, Gabriela");
    printf("\n%d", mystring->length(mystring));

    return 0;

}
