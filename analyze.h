#ifndef ANALYZE_H
#define ANALYZE_H

#include "scan.h"

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(Node tree);

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(Node tree);

#endif
