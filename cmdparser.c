/*
cmdparser.c - Parser de command line para paso de argumentos, detección de errores de sintaxis y comprobación de comandos por callback
Creado por el grupo 2 (Sofía Castro Murphy, Juan Ignacio Causse, Mariano Agustín Dolhare)
Instituto Tecnológico de Buenos Aires
Estructuras de Datos y Algoritmos 1C2021
*/

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
    unsigned short index = 1, readArgs = 0, optionsCounter = 0;
    short error = 0;
    boolean exit = ((argc > 1) ? FALSE : TRUE), enoughArgsForOption = TRUE, inputIsValid;
    char *arg1, *arg2;

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
            optionsCounter++;   //This is needed to count key + value (option) as 1 argument
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

    return ((error == 0) ? (readArgs - optionsCounter) : error);
}