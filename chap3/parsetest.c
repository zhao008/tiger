#include <stdio.h>
#include "util.h"
#include "errormsg.h"

FILE *yyin, *yyout;

extern int yyparse(void);

void parse(string fname) 
{EM_reset(fname);
 if (yyparse() == 0) /* parsing worked */
   fprintf(stderr,"Parsing successful!\n");
 else fprintf(stderr,"Parsing failed\n");
}


int main(int argc, char **argv) {
 if (argc!=2) {fprintf(stderr,"usage: a.out filename\n"); exit(1);}
 yyin = stdin;
 yyout = stdout;
 parse(argv[1]);
 return 0;
}
