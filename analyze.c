#include "analyze.h"
#include "globals.h"
#include "symtab.h"
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct ActivationRecord {
    int loc;
    enum SymbolType kind;
    enum TypeKind type;

    union {
        struct {
            int num_params;
            enum SymbolType* param_types;
        } func;
    };

    // list of referenced line numbers
    int num_linenos;
    int* linenos;
} * Entry;

static Entry makeEntry(Node node, int loc)
{
    Entry entry = malloc(sizeof(struct ActivationRecord));
    entry->loc = loc;

    assert(node->kind == NodeStmt
        && (node->stmt == StmtVar || node->stmt == StmtFunction || node->stmt == StmtParam));

    if (node->stmt == StmtVar) {
        if (node->value.var.is_array) {
            entry->kind = SymArray;
        } else {
            entry->kind = SymVariable;
        }
        entry->type = node->value.var.kind;
    } else if (node->stmt == StmtFunction) {
        entry->kind = SymFunction;
        entry->type = node->value.func.return_type;

        Node params = node->children[0];
        entry->func.num_params = params->num_children;
        entry->func.param_types = malloc(sizeof(enum SymbolType) * entry->func.num_params);
        for (int i = 0; i < entry->func.num_params; ++i) {
            Node param = params->children[i];
            if (param->value.param.is_array) {
                entry->func.param_types[i] = SymArray;
            } else {
                entry->func.param_types[i] = SymVariable;
            }
        }
    } else if (node->stmt == StmtParam) {
        if (node->value.param.is_array) {
            entry->kind = SymArray;
        } else {
            entry->kind = SymVariable;
        }
        entry->type = node->value.param.kind;
    }

    entry->num_linenos = 1;
    entry->linenos = malloc(sizeof(int) * 1);
    entry->linenos[0] = node->lineno;
    return entry;
}

static void entryAddLineno(Entry entry, int lineno)
{
    entry->num_linenos++;
    entry->linenos = realloc(entry->linenos, sizeof(int) * entry->num_linenos);
    entry->linenos[entry->num_linenos - 1] = lineno;
}

#ifdef __GNUC__
__attribute__((__format__(__printf__, 2, 3)))
#endif
static int
idError(Node t, const char* fmt, ...)
{
    fprintf(stderr, "Identifier error at line %d: ", t->lineno);
    va_list args;
    va_start(args, fmt);
    int result = vfprintf(stderr, fmt, args);
    va_end(args);

    fprintf(stderr, "\n");

    //printSymTab(stderr);

    //Error = TRUE;

    return result;
}

typedef struct SemanticCheckStateRec {
    int functionLocCounter;
} * SemanticCheckState;

static void buildSymtabImpl(Node t, SemanticCheckState state)
{
    Entry result;

    switch (t->kind) {
    case NodeStmt:
        switch (t->stmt) {
        case StmtVar:
            if ((result = st_lookup(t->value.var.name))) {
                // aready in table
                idError(t, "Identifier '%s' already declared on line %d",
                    t->value.var.name, result->linenos[0]);
            } else {
                // not yet in table
                // TODO: set loc to appropriate value
                Entry rec = makeEntry(t, 0);
                st_insert(t->value.var.name, rec);
            }
            break;
        case StmtFunction:
            if ((result = st_lookup(t->value.func.name))) {
                // already in table
                idError(t, "Identifier '%s' already declared on line %d",
                    t->value.func.name, result->linenos[0]);
            } else {
                // not yet in table
                Entry rec = makeEntry(t, state->functionLocCounter++);
                st_insert(t->value.func.name, rec);
            }
            // enter scope
            st_enter_scope();
            break;
        case StmtParam:
            if ((result = st_lookup(t->value.param.name))) {
                // already in table
                idError(t, "Identifier '%s' already declared on line %d",
                    t->value.param.name, result->linenos[0]);
            } else {
                // TODO: set loc to appropriate value
                Entry rec = makeEntry(t, 0);
                st_insert(t->value.param.name, rec);
            }
            break;
        default:
            break;
        }
        break;
    case NodeExpr:
        switch (t->expr) {
        case ExprId:
        case ExprCall:
            if ((result = st_lookup(t->value.name))) {
                // already in table, so ignore location,
                // add line number of use only
                entryAddLineno(result, t->lineno);
            } else {
                // Usage of an undeclared identifier
                idError(t, "Unknown identifier '%s'", t->value.name);
            }
            break;
        default:
            break;
        }
        break;
    }

    // recursive traversal
    for (int i = 0; i < t->num_children; i++) {
        buildSymtabImpl(t->children[i], state);
    }

    switch (t->kind) {
    case NodeStmt:
        switch (t->stmt) {
        case StmtFunction:
            st_exit_scope();
            break;
        default:
            break;
        }
        break;
    case NodeExpr:
        break;
    }
}

/* Function buildSymtab constructs the symbol
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(Node t)
{
    st_init();

    struct SemanticCheckStateRec state;
    state.functionLocCounter = 0;

    buildSymtabImpl(t, &state);
}

// Report type error
#ifdef __GNUC__
__attribute__((__format__(__printf__, 2, 3)))
#endif
static int
typeError(Node t, const char* fmt, ...)
{
    fprintf(stderr, "Type error at line %d: ", t->lineno);
    va_list args;
    va_start(args, fmt);
    int result = vfprintf(stderr, fmt, args);
    va_end(args);

    fprintf(stderr, "\n");

    //Error = TRUE;

    return result;
}

typedef struct TypeCheckStateRec {
    int functionLocCounter;
    enum TypeKind currReturnType;
} * TypeCheckState;

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(Node t, TypeCheckState state)
{
    Entry result;

    switch (t->kind) {
    case NodeStmt:
        switch (t->stmt) {
        case StmtFunction:
            if ((result = st_lookup(t->value.func.name))) {
                state->currReturnType = result->type;
            }
            break;
        default:
            break;
        }
        break;
    case NodeExpr:
        break;
    }

    // post-order traversal
    for (int i = 0; i < t->num_children; i++) {
        checkNode(t->children[i], state);
    }

    switch (t->kind) {
    case NodeExpr:
        switch (t->expr) {
        case ExprBinOp:
            t->attr.kind = SymVariable;
            break;
        case ExprConst:
            t->attr.kind = SymVariable;
            break;
        case ExprId:
            if ((result = st_lookup(t->value.name))) {
                t->attr.kind = result->kind;
            } else {
                t->attr.kind = SymUnknown;
            }
            break;
        case ExprIndex:
            if ((result = st_lookup(t->value.name))) {
                if (result->kind != SymArray) {
                    typeError(t, "%s is not an array", t->value.name);
                }
            }
            t->attr.kind = SymVariable;
            break;
        case ExprCall:
            if ((result = st_lookup(t->value.name))) {
                if (result->kind != SymFunction) {
                    typeError(t, "%s is not a function", t->value.name);
                } else {
                    int min_count = t->num_children;
                    if (min_count > result->func.num_params) {
                        min_count = result->func.num_params;
                    }

                    for (int i = 0; i < min_count; ++i) {
                        enum SymbolType param_type = result->func.param_types[i];
                        enum SymbolType arg_type = t->children[i]->attr.kind;
                        if (param_type != arg_type) {
                            typeError(t, "Type of parameter %d does not match type of argument", i);
                        }
                    }

                    if (t->num_children != result->func.num_params) {
                        typeError(t, "%d arguments passed to function %s with %d parameters",
                            t->num_children, t->value.name, result->func.num_params);
                    }
                }
                if (result->type == TypeVoid) {
                    t->attr.kind = SymUnknown;
                } else {
                    t->attr.kind = SymVariable;
                }
            }
            break;
        default:
            break;
        }
        break;
    case NodeStmt:
        switch (t->stmt) {
        case StmtParam:
            if (t->value.param.kind == TypeVoid) {
                idError(t, "Parameter cannot be void");
            }
            break;
        case StmtFunction:
            if (strcmp(t->value.func.name, "main") == 0) {
                if (t->value.func.return_type != TypeVoid) {
                    typeError(t, "Return type of main should always be void");
                }
                if (t->children[0]->num_children != 0) {
                    typeError(t, "main() should have exactly 0 parameters");
                }
            }
            break;
        case StmtVar:
            if (t->value.var.kind == TypeVoid) {
                typeError(t, "Variable cannot be declared with type void");
            }
            break;
        case StmtReturn:
            if (state->currReturnType == TypeVoid) {
                typeError(t, "Return statement not allowed in a void function");
            }
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(Node syntaxTree)
{
    struct TypeCheckStateRec state;

    checkNode(syntaxTree, &state);

    if (syntaxTree->num_children <= 0) {
        typeError(syntaxTree, "Program is empty");
    } else {
        Node last = syntaxTree->children[syntaxTree->num_children - 1];
        if (last->kind != NodeStmt || last->stmt != StmtFunction || strcmp(last->value.func.name, "main") != 0) {
            typeError(last, "Program does not end with main()");
        }
    }
}
