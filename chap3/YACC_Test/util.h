#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef UTIL_H
#define UTIL_H

typedef char *string;
typedef char bool;

#define TRUE 1
#define FALSE 0

void *checked_malloc(int);
string String(char *);

#endif 