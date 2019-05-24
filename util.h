#ifndef UTIL_H
#define UTIL_H

#include "scan.h"
#include "globals.h"

const char* tokenToString(TokenType t);

// print
void printTree(Node node);
void printTreeLatex(Node node);

#endif
