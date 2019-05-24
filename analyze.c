#include "analyze.h"
#include "globals.h"
#include "symtab.h"
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

enum SymbolType {
    SymVariable,
    SymArray,
    SymFunction,
};

typedef struct ActivationRecord {
    int loc;
    enum SymbolType kind;
    enum TypeKind type;

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
        entry->type = node->value.var.type;
    } else if (node->stmt == StmtFunction) {
        entry->kind = SymFunction;
        entry->type = node->value.func.return_type;
    } else if (node->stmt == StmtParam) {
        if (node->value.param.is_array) {
            entry->kind = SymArray;
        } else {
            entry->kind = SymVariable;
        }
        entry->type = node->value.param.type;
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

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(Node t)
{
    // post-order traversal
    for (int i = 0; i < t->num_children; i++) {
        checkNode(t->children[i]);
    }

    Entry result;

    switch (t->kind) {
    case NodeExpr:
        switch (t->expr) {
        case ExprBinOp:
            if ((t->children[0]->attr.type != TypeInt) || (t->children[1]->attr.type != TypeInt)) {
                typeError(t, "Op applied to non-integer");
            }
            t->attr.type = TypeInt;
            break;
        case ExprConst:
        case ExprId:
            t->attr.type = TypeInt;
            break;
        case ExprIndex:
            t->attr.type = TypeInt;
            break;
        case ExprCall:
            if ((result = st_lookup(t->value.name))) {
                if (result->kind != SymFunction) {
                    typeError(t, "%s is not a function", t->value.name);
                }
                t->attr.type = result->type;
            }
            break;
        default:
            break;
        }
        break;
    case NodeStmt:
        switch (t->stmt) {
        case StmtParam:
            if (t->value.param.type == TypeVoid) {
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
            if (t->value.var.type == TypeVoid) {
                typeError(t, "Variable cannot be declared with type void");
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
    checkNode(syntaxTree);
}
