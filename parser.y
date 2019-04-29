%{
#include <stdio.h>
#include "globals.h"
#include "lex.yy.h"
#include "scan.h"
%}

%output  "parser.tab.c"
%defines "parser.tab.h"
%define parse.error verbose
%define api.pure full
%union {
    Node node;
    int num;
    enum OpKind op;
    enum TypeKind type;
}

%lex-param   { void *sc }
%parse-param { void *sc }

%token ERROR IF ELSE RETURN WHILE
%token INT VOID
%token PLUS MINUS MULTIPLY DIVIDE
%token LESSTHAN LESSTHANEQ GREATERTHAN GREATERTHANEQ EQUAL NOTEQUAL
%token ASSIGN SEMICOLON COMMA
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE ID NUM

%type<node> var factor expression call args arg_list simple_expression additive_expression term
%type<node> return_stmt iteration_stmt selection_stmt expression_stmt statement statement_list
%type<node> compound_stmt local_declarations var_declaration
%type<node> params param param_list fun_declaration program declaration_list declaration
%type<node> ID NUM
%type<op> mulop addop relop
%type<type> type_specifier

%%

program             : declaration_list { yyget_extra(sc)->tree = $1; }
                    ;

declaration_list    : declaration_list declaration { $$ = $1; addChildToNode($$, $2); }
                    | declaration { $$ = makeDeclListNode(); }
                    ;

declaration         : var_declaration { $$ = $1; }
                    | fun_declaration { $$ = $1; }
                    ;

var_declaration     : type_specifier ID SEMICOLON { $$ = makeVarDeclNode($1, $2); }
                    | type_specifier ID LBRACKET NUM RBRACKET SEMICOLON { $$ = makeArrayDeclNode($1, $4->value.num, $2); }
                    ;

type_specifier      : INT { $$ = TypeInt; }
                    | VOID { $$ = TypeVoid; }
                    ;

fun_declaration     : type_specifier ID LPAREN params RPAREN compound_stmt { $$ = makeFunctionNode($1, $2, $4, $6); }
                    ;

params              : param_list { $$ = $1; }
                    | VOID { $$ = makeParamListNode(); }
                    ;

param_list          : param_list COMMA param { $$ = $1; addChildToNode($$, $3); }
                    | param { $$ = makeParamListNode(); addChildToNode($$, $1); }
                    ;

param               : type_specifier ID { $$ = makeParamNode($1, false, $2); }
                    | type_specifier ID LBRACKET RBRACKET { $$ = makeParamNode($1, true, $2); }
                    ;

compound_stmt       : LBRACE local_declarations statement_list RBRACE {
                            $$ = $2;
                            for (int i = 0; i < $3->num_children; ++i) {
                                addChildToNode($$, $3->children[i]);
                            }
                            freeNode($3);
                        }
                    ;

local_declarations  : local_declarations var_declaration { $$ = $1; addChildToNode($$, $2); }
                    | { $$ = makeCompoundStatement(); }
                    ;

statement_list      : statement_list statement { $$ = $1; if ($2) { addChildToNode($$, $2); } }
                    | { $$ = makeStmtListNode(); }
                    ;

statement           : expression_stmt { $$ = $1; }
                    | compound_stmt { $$ = $1; }
                    | selection_stmt { $$ = $1; }
                    | iteration_stmt { $$ = $1; }
                    | return_stmt { $$ = $1; }
                    ;

expression_stmt     : expression SEMICOLON { $$ = makeExprStmt($1); }
                    | SEMICOLON { $$ = NULL; }
                    ;

selection_stmt      : IF LPAREN expression RPAREN statement { $$ = makeIfNode($3, $5); }
                    | IF LPAREN expression RPAREN statement ELSE statement { $$ = makeIfNode($3, $5); addChildToNode($$, $7); }
                    ;

iteration_stmt      : WHILE LPAREN expression RPAREN statement { $$ = makeWhileNode($3, $5); }

return_stmt         : RETURN SEMICOLON { $$ = makeReturnNode(); }
                    | RETURN expression SEMICOLON { $$ = makeReturnNode(); addChildToNode($$, $2); }
                    ;

expression          : var ASSIGN expression { $$ = makeAssignNode($1, $3); }
                    | simple_expression { $$ = $1; }
                    ;

var                 : ID { $$ = $1; }
                    | ID LBRACKET expression RBRACKET { $$ = makeIndexNode($1, $3); }
                    ;

simple_expression   : additive_expression relop additive_expression { $$ = makeBinOpNode($2, $1, $3); }
                    | additive_expression { $$ = $1; }
                    ;

relop               : LESSTHAN { $$ = OpLessThan; }
                    | LESSTHANEQ { $$ = OpLessThanEq; }
                    | GREATERTHAN { $$ = OpGreaterThan; }
                    | GREATERTHANEQ { $$ = OpGreaterThanEq; }
                    | EQUAL { $$ = OpEqual; }
                    | NOTEQUAL { $$ = OpNotEqual; }
                    ;

additive_expression : additive_expression addop term { $$ = makeBinOpNode($2, $1, $3); }
                    | term { $$ = $1; }
                    ;

addop               : PLUS { $$ = OpAdd; }
                    | MINUS { $$ = OpSubtract; }
                    ;

term                : term mulop factor { $$ = makeBinOpNode($2, $1, $3); }
                    | factor { $$ = $1; }
                    ;

mulop               : MULTIPLY { $$ = OpMultiply; }
                    | DIVIDE { $$ = OpDivide; }
                    ;

factor              : LPAREN expression RPAREN { $$ = $2; }
                    | var { $$ = $1; }
                    | call { $$ = $1; }
                    | NUM { $$ = $1; }
                    ;

call                : ID LPAREN args RPAREN { $$ = makeCallNode($1, $3); }
                    ;

args                : arg_list { $$ = $1; }
                    | { $$ = makeArgsNode(); }
                    ;

arg_list            : arg_list COMMA expression { $$ = $1; addChildToNode($$, $3); }
                    | expression { $$ = makeArgsNode(); addChildToNode($$, $1); }
                    ;
