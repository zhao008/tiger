%{
#include <stdio.h>
%}

%%

[0-9]+      { printf("NUMBER: %s\n", yytext); }
[a-zA-Z]+   { printf("WORD: %s\n", yytext); }
\n          { /* 忽略换行符 */ }
.           { printf("UNKNOWN: %s\n", yytext); }

%%

int main(int argc, char **argv)
{
    yylex();
    return 0;
}

int yywrap()
{
    // 重新开始扫描
    printf("yywrap\n"); 
    return 1;
}