#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "util.h"
#include "errormsg.h"

int EM_tokPos = 0;

static char* fileName = "";
static int lineNum = 1;

typedef struct intList {int i; struct intList* rest;} *IntList;

static IntList intList(int i, IntList rest) {
    IntList l = checked_malloc(sizeof(*l));
    l->i = i;
    l->rest = rest;
    return l;
}

static IntList linePos = NULL;

void EM_newline(void) {
    lineNum++;
    linePos = intList(EM_tokPos, linePos);
}

void EM_error(int pos, char* message, ...) {
    va_list ap;
    IntList lines = linePos;
    int num = lineNum;

    while (lines && lines->i >= pos) {
        lines = lines->rest;
        num--;
    }

    if (fileName) fprintf(stderr, "%s:", fileName);
    if (lines) fprintf(stderr, "%d.%d: ", num, pos - lines->i);
    va_start(ap, message);
    vfprintf(stderr, message, ap);
    va_end(ap);
    fprintf(stderr, "\n");
}

void EM_impossible(char* message, ...) {
    va_list ap;
    va_start(ap, message);
    vfprintf(stderr, message, ap);
    va_end(ap);
    fprintf(stderr, "\n");
    exit(1);
}

void EM_reset(char* fname) {
    fileName = fname;
    lineNum = 1;
    linePos = intList(0, NULL);
    EM_tokPos = 0;
}