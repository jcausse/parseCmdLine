#include <stdio.h>
#include "tp1_takehome_g2.h"

//Custom data type
#define BOOLEAN unsigned short
#define TRUE 1
#define FALSE 0

//Error code
#define ERROR_OPTION_NO_KEY -1
#define ERROR_LAST_OPTION_NO_VALUE -2
#define ERROR_ARG_IS_NOT_VALID -3

int main (int argc, char *argv[]){
    parseCmdLine (argc, argv, NULL, NULL);
    return 0;
}

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData){
    unsigned short index = 1, readArgs = 0;
    short error = 0;
    BOOLEAN exit = ((argc > 1) ? FALSE : TRUE), enoughArgsForOption = TRUE, inputIsValid;
    char *arg1, *arg2;

    #ifdef DEBUG
        printf ("\nDEBUG MSG: Started cmdline argument print\n");
        for (index = 0; index < argc; index++){
            printf ("%s ", argv[index]);
        }
        printf ("\nDEBUG MSG: Finished cmdline argument print\n");
    #endif

    while (!exit){
        //Check for non-read args
        if (readArgs == argc - 1){
            exit = TRUE;
            continue;
        }
        if (readArgs == argc - 2){
            enoughArgsForOption = FALSE;
        }
        //Get args if available
        arg1 = argv[index++];
        readArgs++;
        if ((*arg1) == '-'){        //Options (key starting in '-' + value)
            if (!enoughArgsForOption){
                error = ERROR_LAST_OPTION_NO_VALUE;
                continue;
            }
            if (*(arg1+1) == '\0'){
                error = ERROR_OPTION_NO_KEY;
                continue;
            }
            arg2 = argv[index++];
            readArgs++;
            inputIsValid = (BOOLEAN) p(arg1, arg2, userData);   //userData is unmodified
        }
        else{                       //Parameters (not starting in '-')
            inputIsValid = (BOOLEAN) p(NULL, arg1,userData);    //userData is unmodified
        }
        if (!inputIsValid){
                error = ERROR_ARG_IS_NOT_VALID;
                continue;
            }
    }

    return ((error == 0) ? readArgs : error);
}