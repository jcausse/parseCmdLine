/*
cmdparser.h - Parser de command line para paso de argumentos, detección de errores de sintaxis y comprobación de comandos por callback
Creado por el grupo 2 (Sofía Castro Murphy, Juan Ignacio Causse, Mariano Agustín Dolhare)
Instituto Tecnológico de Buenos Aires
Estructuras de Datos y Algoritmos 1C2021
*/

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

typedef int (*pCallback) (char *key, char *value, void *userData);          //User-defined Callback for data processing (key, value, command line value for key)
/*Key and value are unmodified*/
/*Parser user must define Callback function "pCallback" with given prototype*/
int parseCmdLine(int argc, char *argv[], pCallback p, void *userData);      //Command line parser
/*
parseCmdLine returns:
-1 if there is an option without key
-2 if last option has no value
-3 if callback returned error
else: number of options (key + value) + number of args
*/

#endif