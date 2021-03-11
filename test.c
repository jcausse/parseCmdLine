/* NOTA IMPORTANTE
Al tratarse de un banco de pruebas para el parser, en lugar de crear estructuras de userData y un Callback complejo, se prefirió utilizar un Callback sencillo en el que
se lograran probar todos los casos posibles de error, y algunos casos en los que debería no haberlos. Esto se hizo así porque la utilidad de este archivo es simplemente
probar el correcto funcionamiento de la librería "cmdparser".
*/

/* NOTA
La propia librería especifica el prototipo necesario para la función Callback, en el archivo "cmdparser.h". Allí se encontrarán los prototipos indicados por la cátedra.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cmdparser.h"

#define VALUE_ERROR "Value_Error_String"
#define KEY_ERROR "-Key_Error_String"
#define NUMBER_OF_TESTS 5
#define MEM_MAX_SIZE 20

int callbackFunction (char * key, char * value, void * userData);

int main (void){
    //TEST DESIGN
    typedef struct{
        char * test1 [4];
        char * test2 [3];
        char * test3 [4];
        char * test4 [4];
        char * test5 [8];
    }args_t;
    args_t args = {
                {NULL,"-","value1","value2"},                                           //Test 1. NULL replaces executable file path
                {NULL,"value1","-key2"},                                                //Test 2
                {NULL,KEY_ERROR,"value 1","value2"},                                    //Test 3
                {NULL,"-key1","value 1",VALUE_ERROR},                                   //Test 4
                {NULL,"-key1","value1","-key2","value2","value3","value4","value5"}     //Test 5
    };
    int returnValues[NUMBER_OF_TESTS];
    int expectedReturnValues[NUMBER_OF_TESTS] = {-1, -2, -3, -3, 5};

    pCallback ptrCB = &callbackFunction;

    //USER DATA MEMORY
    void * test1_memory = malloc (MEM_MAX_SIZE * sizeof(char *));
    void * test2_memory = malloc (MEM_MAX_SIZE * sizeof(char *));
    void * test3_memory = malloc (MEM_MAX_SIZE * sizeof(char *));
    void * test4_memory = malloc (MEM_MAX_SIZE * sizeof(char *));
    void * test5_memory = malloc (MEM_MAX_SIZE * sizeof(char *));

    //TESTS
    returnValues[0] = parseCmdLine (4, args.test1, ptrCB, test1_memory);
    returnValues[1] = parseCmdLine (3, args.test2, ptrCB, test2_memory);
    returnValues[2] = parseCmdLine (4, args.test3, ptrCB, test3_memory);
    returnValues[3] = parseCmdLine (4, args.test4, ptrCB, test4_memory);
    returnValues[4] = parseCmdLine (8, args.test5, ptrCB, test5_memory);

    //OUTPUT
    for (unsigned short i = 0; i < NUMBER_OF_TESTS; i++){
        if (returnValues[i] != expectedReturnValues[i])
            printf ("Test %d FAIL. Expected %d, got %d.\n", i + 1, expectedReturnValues[i], returnValues[i]);
        else
            printf ("Test %d PASS. Expected %d, got %d.\n", i + 1, expectedReturnValues[i], returnValues[i]);
    }

    //EXIT
    free(test1_memory);
    free(test2_memory);
    free(test3_memory);
    free(test4_memory);
    free(test5_memory);
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
    return returnValue;
}