%{
#include <string.h>
#include "util.h"
#include "tokens.h"
#include "errormsg.h"

int charPos=1;
int comment_depth = 0;  // 用于跟踪嵌套注释的深度

int yywrap(void)
{
 charPos=1;
 return 1;
}


void adjust(void)
{
 EM_tokPos=charPos;
 charPos+=yyleng;
}

%}

%x COMMENT TYPEID_STATE

%%
"/*"                        { adjust(); comment_depth = 1; BEGIN(COMMENT); continue;}
<COMMENT>\n                 { adjust(); EM_newline(); continue;}
<COMMENT>"/*"               { adjust(); comment_depth++; continue;}
<COMMENT>"*/"               { adjust(); if (--comment_depth == 0) BEGIN(INITIAL); continue;}
<COMMENT>[^*\n]+            { adjust(); continue;}
<COMMENT>"*"                { adjust(); continue;}


" "	                        {adjust(); continue;}
\t	                        {adjust(); continue;}
\n	                        {adjust(); EM_newline(); continue;}
"="                         {adjust(); return EQ;}
","	                        {adjust(); return COMMA; }
":"                         {adjust(); return COLON; }
";"                         {adjust(); return SEMICOLON; }
"("                         {adjust(); return LPAREN; }
")"                         {adjust(); return RPAREN; }
"["                         {adjust(); return LBRACK; }
"]"                         {adjust(); return RBRACK; }
"{"                         {adjust(); return LBRACE; }
"}"                         {adjust(); return RBRACE; }
"."                         {adjust(); return DOT; }
"+"                         { adjust(); return PLUS; }  // 匹配加号
"-"                         { adjust(); return MINUS; }  // 匹配减号
"*"                         { adjust(); return TIMES; }  // 匹配乘号
"/"                         { adjust(); return DIVIDE; }  // 匹配除号
"="                         { adjust(); return EQ; }  // 匹配等号
"<>"                        { adjust(); return NEQ; }  // 匹配不等号
"<"                         { adjust(); return LT; }  // 匹配小于号
"<="                        { adjust(); return LE; }  // 匹配小于等于号
">"                         { adjust(); return GT; }  // 匹配大于号
">="                        { adjust(); return GE; }  // 匹配大于等于号
"&"                         { adjust(); return AND; }  // 匹配逻辑与
"|"                         { adjust(); return OR; }  // 匹配逻辑或
":="                        { adjust(); return ASSIGN; }  // 匹配赋值符号
array                       { adjust(); return ARRAY; }  // 匹配关键字 array
if                          { adjust(); return IF; }  // 匹配关键字 if
then                        { adjust(); return THEN; }  // 匹配关键字 then
else                        { adjust(); return ELSE; }  // 匹配关键字 else
while                       { adjust(); return WHILE; }  // 匹配关键字 while
for                         { adjust(); return FOR; }  // 匹配关键字 for
to                          { adjust(); return TO; }  // 匹配关键字 to
do                          { adjust(); return DO; }  // 匹配关键字 do
let                         { adjust(); return LET; }  // 匹配关键字 let
in                          { adjust(); return IN; }  // 匹配关键字 in
end                         { adjust(); return END; }  // 匹配关键字 end
of                          { adjust(); return OF; }  // 匹配关键字 of
break                       { adjust(); return BREAK; }  // 匹配关键字 break
nil                         { adjust(); return NIL; }  // 匹配关键字 nil
function                    { adjust(); return FUNCTION; }  // 匹配关键字 function
var                         { adjust(); return VAR; }  // 匹配关键字 var
type                        { adjust(); return TYPE; }  // 匹配关键字 type 并进入 TYPEID_STATE 状态
\"([^\\\"]|\\.)*\"          { adjust(); yylval.sval = strdup(yytext + 1); yylval.sval[strlen(yylval.sval) - 1] = '\0'; return STRING; }
[0-9]+                      { adjust(); yylval.ival = atoi(yytext); return INT; }  // 匹配整数
[a-zA-Z_][a-zA-Z0-9_]*      { adjust(); yylval.sval = strdup(yytext); return ID; }  // 匹配标识符
.                           { adjust(); EM_error(EM_tokPos, "illegal token"); }  // 匹配其他字符并报告错误


