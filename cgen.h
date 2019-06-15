#ifndef CGEN_H
#define CGEN_H

#include "scan.h"

enum Storage {
    SavedTemp,
    Temp,
    Return,
    Argument,
    Memory
};

void codeGen(Node syntaxTree, const char* filename);

#endif
