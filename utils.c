#include "globals.h"
#include "lex.yy.h"

const char* tokenToString(TokenType t)
{
    switch (t) {
    case ERROR:
        return "ERROR";
    case IF:
        return "IF";
    case ELSE:
        return "ELSE";
    case INT:
        return "INT";
    case RETURN:
        return "RETURN";
    case VOID:
        return "VOID";
    case WHILE:
        return "WHILE";
    case PLUS:
        return "+";
    case MINUS:
        return "-";
    case MULTIPLY:
        return "*";
    case DIVIDE:
        return "/";
    case LESSTHAN:
        return "<";
    case LESSTHANEQ:
        return "<=";
    case GREATERTHAN:
        return ">";
    case GREATERTHANEQ:
        return ">=";
    case EQUAL:
        return "==";
    case NOTEQUAL:
        return "!=";
    case ASSIGN:
        return "=";
    case SEMICOLON:
        return ";";
    case COMMA:
        return ",";
    case LPAREN:
        return "(";
    case RPAREN:
        return ")";
    case LBRACKET:
        return "[";
    case RBRACKET:
        return "]";
    case LBRACE:
        return "{";
    case RBRACE:
        return "}";
    case ID:
        return "ID";
    case NUM:
        return "NUM";
    }
    return "Unknown";
}
