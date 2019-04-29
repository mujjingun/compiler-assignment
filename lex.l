%{
#include "globals.h"
#include "scan.h"

// workaround for warning
int fileno(FILE *stream);
%}

%option reentrant
%option bison-bridge
%option extra-type="struct Scanner *"
%option header-file="lex.yy.h"
%option outfile="lex.yy.c"
%option nounput

letter      [a-zA-Z]
digit       [0-9]
number      {digit}+
identifier  {letter}*
newline     \n
whitespace  (" "|\t)+

%%

<<EOF>>     { return 0; }

"if"        { return IF; }
"else"      { return ELSE; }
"int"       { return INT; }
"return"    { return RETURN; }
"void"      { return VOID; }
"while"     { return WHILE; }

"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MULTIPLY; }
"/"         { return DIVIDE; }
"<"         { return LESSTHAN; }
"<="        { return LESSTHANEQ; }
">"         { return GREATERTHAN; }
">="        { return GREATERTHANEQ; }
"=="        { return EQUAL; }
"!="        { return NOTEQUAL; }
"="         { return ASSIGN; }
";"         { return SEMICOLON; }
","         { return COMMA; }
"("         { return LPAREN; }
")"         { return RPAREN; }
"["         { return LBRACKET; }
"]"         { return RBRACKET; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
"/*"        {
    int c;
    while (1) {
        c = input(yyscanner);
        if (c == 0) {
            yyextra->error_msg = "Comment error";
            return ERROR;
        }
        if (c == '\n') {
            yylineno++;
        }
        while (c == '*') {
            c = input(yyscanner);
            if (c == 0) {
                yyextra->error_msg = "Comment error";
                return ERROR;
            }
            if (c == '\n') {
                yylineno++;
            }
            if (c == '/') {
                goto ignore;
            }
        }
    }
ignore:
    ;
}

{letter}+{number} { yyextra->error_msg = "Invalid identifier"; return ERROR; }
{number}{letter}+ { yyextra->error_msg = "Invalid identifier"; return ERROR; }

{identifier} {
    yylval->node = makeIdNode(yytext);
    return ID;
}

{number}     {
    yylval->node = makeConstNode(atoi(yytext));
    return NUM;
}

{newline}    { yylineno++; }

{whitespace} {}

.           {
    yyextra->error_msg = "Unknown token";
    return ERROR;
}

%%

int yywrap(yyscan_t scanner) {
    (void)scanner;
    return 1;
}
