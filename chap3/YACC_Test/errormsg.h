#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "util.h"

#ifndef INTERPUTIL_H
#define INTERPUTIL_H

extern bool EM_anyErrors;

void EM_newline(void);

extern int EM_tokPos;

void EM_error(int, string,...);
void EM_impossible(string,...);
void EM_reset(string filename);

#endif