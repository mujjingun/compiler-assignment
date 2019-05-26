#ifndef ANALYZE_H
#define ANALYZE_H

#include "scan.h"
#include "symtab.h"
#include <stdbool.h>

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
SymTable semanticAnalysis(Node tree, bool* error);

void printFormattedSymtab(SymTable tab);

#endif
