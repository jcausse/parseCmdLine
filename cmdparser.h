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
else: number of args

#endif