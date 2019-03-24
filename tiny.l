%{

#include "globals.h"

int lineno = 1;
const char* error_msg = "";

%}
%option reentrant
%option noyywrap
%option extra-type="struct Scanner *"
%option header-file="lex.yy.h"
%option outfile="lex.yy.c"

letter      [a-zA-Z]
digit       [0-9]
number      {digit}+
identifier  {letter}*
newline     \n
whitespace  (" "|\t)+

%%

<<EOF>>     { return ENDOFFILE; }

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

{identifier} { return ID; }
{number}     { return NUM; }

{newline}    { yylineno++; }

{whitespace} {}

.           {
    error_msg = "Unknown token";
    return ERROR;
}

%%
