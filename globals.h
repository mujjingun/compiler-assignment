#ifndef GLOBALS_H
#define GLOBALS_H

#include "scan.h"
#include "parser.tab.h"

typedef enum yytokentype TokenType;

const char* tokenToString(TokenType t);

typedef void* yyscan_t;
void yyerror(yyscan_t scanner, char const* s);

#endif // GLOBALS_H
