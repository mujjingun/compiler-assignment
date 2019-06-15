#ifndef ANALYZE_H
#define ANALYZE_H

#include "scan.h"
#include "symtab.h"
#include <stdbool.h>

enum VPFType {
    VPFVariable,
    VPFParam,
    VPFFunction,
};

struct ActivationRecord {
    int loc, scope;
    enum SymbolType kind;
    enum TypeKind type;
    enum VPFType vpf;

    union {
        struct {
            int num_params;
            enum SymbolType* param_types;
        } func;
        int arr_size;
    };

    // list of referenced line numbers
    int num_linenos;
    int* linenos;
};

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
bool semanticAnalysis(Node tree);

void printFormattedSymtab(SymTable tab);

#endif
