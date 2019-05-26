#ifndef ANALYZE_H
#define ANALYZE_H

#include "scan.h"
#include <stdbool.h>

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
bool semanticAnalysis(Node tree);

void printFormattedSymtab();

#endif
