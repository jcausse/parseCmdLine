#include "cmdparser.h"

//Custom data type
typedef unsigned short boolean;
#define TRUE 1
#define FALSE 0

//Error codes
#define ERROR_OPTION_NO_KEY -1
#define ERROR_LAST_OPTION_NO_VALUE -2
#define ERROR_ARG_IS_NOT_VALID -3

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData){
    unsigned short index = 1, readArgs = 0;
    short error = 0;
    boolean exit = ((argc > 1) ? FALSE : TRUE), enoughArgsForOption = TRUE, inputIsValid;
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
        if (readArgs == argc - 1){          //None left
            exit = TRUE;
            continue;
        }
        else if (readArgs == argc - 2){          //1 arg left
            enoughArgsForOption = FALSE;
        }
        //Get args if available
        arg1 = argv[index++];
        readArgs++;
        if ((*arg1) == '-'){                    //Options (key starting in '-' + value)
            if (*(arg1+1) == '\0'){             //All argv arguments are null terminated
                error = ERROR_OPTION_NO_KEY;
                exit = TRUE;
                continue;
            }
            else if (!enoughArgsForOption){     //Last argument
                error = ERROR_LAST_OPTION_NO_VALUE;
                exit = TRUE;
                continue;
            }
            arg2 = argv[index++];
            readArgs++;
            inputIsValid = (boolean) p(arg1, arg2, userData);   //userData is unmodified
        }
        else{                                   //Parameters (not starting in '-')
            inputIsValid = (boolean) p(NULL, arg1, userData);   //userData is unmodified
        }
        if (!inputIsValid){
            error = ERROR_ARG_IS_NOT_VALID;
            exit = TRUE;
            continue;
        }
    }

    return ((error == 0) ? readArgs : error);
}