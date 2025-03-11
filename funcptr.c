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

String *initString(char input[]){

    /* gets the input length */
    int i = 0;
    while(input[i] != '\0'){
        i++;
    }
    int n = i;

    String *str = malloc(sizeof(String));
    str->string = malloc(sizeof(char) * n);
    str->length = stringLength;

    strcpy(str->string, input);

    return str;

}


int main(){

    String *mystring = initString("love my family");
    printf("%d\n", mystring->length(mystring));
    printf("%s\n", mystring->string);

    return 0;

}
