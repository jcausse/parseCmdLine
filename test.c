#include <stdio.h>
#include <string.h>
#include "cmdparser.h"

#define VALUE_ERROR "valor_prohibido"
#define KEY_ERROR "-clave_prohibida"

int callbackFunction (char * key, char * value, void * userData);
typedef int callbackPtr (char *, char *, void *);

int main (void){
    struct args{
        char * test1 [3] = {"-", "value1", "value2"};
        char * test2 [2] = {"value1", "-key2"};
        char * test3 [3] = {KEY_ERROR, "value 1", "value2"};
        char * test4 [3] = {"-key1", "value 1", VALUE_ERROR};
        char * test5 [7] = {"-key1", "value1", "-key2", "value2", "value3", "value4", "value5"};
    };
    int returnValues[5];
    int expectedReturnValues[] = {-1, -2, -3, -3, 5};

    callbackPtr ptrCB = &callbackFunction;

    returnValues[0] = parseCmdLine (3, args.test1, ptrCB, NULL);
    returnValues[1] = parseCmdLine (2, args.test2, ptrCB, NULL);
    returnValues[2] = parseCmdLine (3, args.test3, ptrCB, NULL);
    returnValues[3] = parseCmdLine (3, args.test4, ptrCB, NULL);
    returnValues[4] = parseCmdLine (7, args.test5, ptrCB, NULL);

    for (unsigned short i = 0; i < 5; i++){
        if (returnValues[i] != expectedReturnValues[i){
            printf ("Test %d FAIL\n", i);
        }
        else
            printf ("Test %d PASS\n", i)
    }
    return 0;
}

int callbackFunction (char * key, char * value, void * userData){
    int returnValue;
    if (key == NULL){       //Parameter
        if (!strcmp(value, VALUE_ERROR)){
            returnValue = 0;
        }
        else
            returnValue = 1;
    }
    else{                   //Option
        if (!strcmp(key, KEY_ERROR)){
            returnValue = 0;
        }
        else if (!strcmp(value, VALUE_ERROR)){
            returnValue = 0;
        }
        else
            returnValue = 1;
    }
}

