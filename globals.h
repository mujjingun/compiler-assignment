#ifndef GLOBALS_H
#define GLOBALS_H

#include "scan.h"
#include "parser.tab.h"

typedef enum yytokentype TokenType;

typedef void* yyscan_t;
void yyerror(yyscan_t scanner, char const* s);

#endif // GLOBALS_H
