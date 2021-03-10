#ifndef PARSER_H
#define PARSER_H

typedef int (*pCallback) (char *key, char *value, void *userData);          //User-defined Callback for data processing (key, value, command line value for key)
/*Parser user must define Callback function "pCallback" with given prototype*/
int parseCmdLine(int argc, char *argv[], pCallback p, void *userData);      //Command line parser

#endif