#ifndef ERRORMSG_H
#define ERRORMSG_H

#include "util.h"

extern int EM_tokPos;

void EM_newline(void);
void EM_error(int, char*, ...);
void EM_impossible(char*, ...);
void EM_reset(char* filename);

#endif