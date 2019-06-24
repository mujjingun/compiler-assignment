#ifndef CGEN_H
#define CGEN_H

#include <stdio.h>
#include "scan.h"

void codeGen(Node syntaxTree, const char* filename,
	     bool debugSymbols, FILE* source);

#endif
