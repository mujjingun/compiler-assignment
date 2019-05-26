#include "analyze.h"
#include "globals.h"
#include "symtab.h"
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct ActivationRecord {
    int loc, scope;
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
};

static Record makeRecord(Node node, int loc, int scope)
{
    Record rec = malloc(sizeof(struct ActivationRecord));
    rec->loc = loc;
    rec->scope = scope;

    assert(node->kind == NodeStmt
        && (node->stmt == StmtVar || node->stmt == StmtFunction || node->stmt == StmtParam));

    if (node->stmt == StmtVar) {
        if (node->value.var.kind == TypeVoid) {
            rec->kind = SymUnknown;
        } else if (node->value.var.is_array) {
            rec->kind = SymArray;
        } else {
            rec->kind = SymVariable;
        }
        rec->type = node->value.var.kind;
    } else if (node->stmt == StmtFunction) {
        rec->kind = SymFunction;
        rec->type = node->value.func.return_type;

        Node params = node->children[0];
        rec->func.num_params = params->num_children;
        rec->func.param_types = malloc(sizeof(enum SymbolType) * rec->func.num_params);
        for (int i = 0; i < rec->func.num_params; ++i) {
            Node param = params->children[i];
            if (param->value.param.is_array) {
                rec->func.param_types[i] = SymArray;
            } else {
                rec->func.param_types[i] = SymVariable;
            }
        }
    } else if (node->stmt == StmtParam) {
        if (node->value.param.kind == TypeVoid) {
            rec->kind = SymUnknown;
        } else if (node->value.param.is_array) {
            rec->kind = SymArray;
        } else {
            rec->kind = SymVariable;
        }
        rec->type = node->value.param.kind;
    }

    rec->num_linenos = 1;
    rec->linenos = malloc(sizeof(int) * 1);
    rec->linenos[0] = node->lineno;
    return rec;
}

static void RecordAddLineno(Record Record, int lineno)
{
    Record->num_linenos++;
    Record->linenos = realloc(Record->linenos, sizeof(int) * Record->num_linenos);
    Record->linenos[Record->num_linenos - 1] = lineno;
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

    return result;
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

    return result;
}

typedef struct SemanticCheckStateRec {
    int functionLocCounter;
    int paramLocCounter;
    int localLocCounter;
    int globalLocCounter;
    int scopeLevel;
    enum TypeKind currReturnType;
    SymTable sym;
} * SemanticCheckState;

static bool buildSymtabImpl(Node t, SemanticCheckState state)
{
    Record result;

    bool error = false;

    switch (t->kind) {
    case NodeStmt:
        switch (t->stmt) {
        case StmtVar:
            if ((result = st_lookup(state->sym, t->value.var.name)) && result->scope == state->scopeLevel) {
                // aready in table
                idError(t, "Identifier '%s' already declared on line %d",
                    t->value.var.name, result->linenos[0]);
                error = true;
            } else {
                // not yet in table
                int loc, size;
                if (t->value.var.is_array) {
                    size = t->value.var.array_size * 4;
                } else {
                    size = 4;
                }
                if (state->scopeLevel == 0) {
                    loc = (state->globalLocCounter += size);
                } else {
                    loc = (state->localLocCounter -= size);
                }
                Record rec = makeRecord(t, loc, state->scopeLevel);
                st_insert(state->sym, t->value.var.name, rec);
            }
            break;
        case StmtFunction:
            if ((result = st_lookup(state->sym, t->value.func.name))) {
                // already in table
                idError(t, "Identifier '%s' already declared on line %d",
                    t->value.func.name, result->linenos[0]);
                error = true;
            } else {
                // not yet in table
                Record rec = makeRecord(t, state->functionLocCounter, state->scopeLevel);
                st_insert(state->sym, t->value.func.name, rec);

                state->functionLocCounter++;
            }

            // enter scope
            st_enter_scope(state->sym);
            state->scopeLevel++;

            // initialize loc counters
            state->localLocCounter = -4;
            state->paramLocCounter = t->children[0]->num_children * 4;
            break;
        case StmtParam:
            if ((result = st_lookup(state->sym, t->value.param.name))) {
                // already in table
                idError(t, "Identifier '%s' already declared on line %d",
                    t->value.param.name, result->linenos[0]);
                error = true;
            } else {
                // loc is set in reverse
                Record rec = makeRecord(t, state->paramLocCounter, state->scopeLevel);
                st_insert(state->sym, t->value.param.name, rec);

                state->paramLocCounter -= 4;
            }
            break;
        case StmtCompoundStmt:
            // enter scope
            if (!t->value.is_function_body) {
                st_enter_scope(state->sym);
                state->scopeLevel++;
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
            if ((result = st_lookup(state->sym, t->value.name))) {
                // already in table, so ignore location,
                // add line number of use only
                RecordAddLineno(result, t->lineno);
            } else {
                // Usage of an undeclared identifier
                idError(t, "Unknown identifier '%s'", t->value.name);
                error = true;
            }
            break;
        default:
            break;
        }
        break;
    }

    switch (t->kind) {
    case NodeStmt:
        switch (t->stmt) {
        case StmtFunction:
            if ((result = st_lookup(state->sym, t->value.func.name))) {
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

    // recursive traversal
    for (int i = 0; i < t->num_children; i++) {
        error = buildSymtabImpl(t->children[i], state) || error;
    }

    switch (t->kind) {
    case NodeStmt:
        switch (t->stmt) {
        case StmtFunction:
            st_exit_scope(state->sym);
            state->scopeLevel--;
            break;
        case StmtCompoundStmt:
            // exit scope
            if (!t->value.is_function_body) {
                st_exit_scope(state->sym);
                state->scopeLevel--;
            }
            break;
        default:
            break;
        }
        break;
    case NodeExpr:
        break;
    }

    switch (t->kind) {
    case NodeExpr:
        switch (t->expr) {
        case ExprBinOp:
        case ExprAssign:
            if (t->children[0]->attr.kind != SymVariable || t->children[1]->attr.kind != SymVariable) {
                typeError(t, "Operands are not int");
                error = true;
            }
            t->attr.kind = SymVariable;
            break;
        case ExprConst:
            t->attr.kind = SymVariable;
            break;
        case ExprId:
            if ((result = st_lookup(state->sym, t->value.name))) {
                t->attr.kind = result->kind;
            } else {
                t->attr.kind = SymUnknown;
            }
            break;
        case ExprIndex:
            if (t->children[0]->attr.kind != SymVariable) {
                typeError(t, "Array subscript is not int");
                error = true;
            }
            if ((result = st_lookup(state->sym, t->value.name))) {
                if (result->kind != SymArray) {
                    typeError(t, "'%s' is not an array", t->value.name);
                    error = true;
                }
            }
            t->attr.kind = SymVariable;
            break;
        case ExprCall:
            if ((result = st_lookup(state->sym, t->value.name))) {
                if (result->kind != SymFunction) {
                    typeError(t, "'%s' is not a function", t->value.name);
                    error = true;
                } else {
                    int min_count = t->num_children;
                    if (min_count > result->func.num_params) {
                        min_count = result->func.num_params;
                    }

                    for (int i = 0; i < min_count; ++i) {
                        enum SymbolType param_type = result->func.param_types[i];
                        enum SymbolType arg_type = t->children[i]->attr.kind;
                        if (param_type != arg_type) {
                            typeError(t, "Type of parameter #%d does not match type of argument", i + 1);
                            error = true;
                        }
                    }

                    if (t->num_children != result->func.num_params) {
                        typeError(t, "%d arguments passed to function '%s' with %d parameters",
                            t->num_children, t->value.name, result->func.num_params);
                        error = true;
                    }
                }
                if (result->type == TypeVoid) {
                    t->attr.kind = SymUnknown;
                } else {
                    t->attr.kind = SymVariable;
                }
            } else {
                t->attr.kind = SymUnknown;
            }
            break;
        default:
            break;
        }
        break;
    case NodeStmt:
        switch (t->stmt) {
        case StmtIf:
        case StmtWhile:
            if (t->children[0]->attr.kind != SymVariable) {
                typeError(t, "Condition must be int");
                error = true;
            }
            break;
        case StmtParam:
            if (t->value.param.kind == TypeVoid) {
                idError(t, "Parameter cannot be void");
                error = true;
            }
            break;
        case StmtFunction:
            if (strcmp(t->value.func.name, "main") == 0) {
                if (t->value.func.return_type != TypeVoid) {
                    typeError(t, "Return type of main should always be void");
                    error = true;
                }
                if (t->children[0]->num_children != 0) {
                    typeError(t, "main() should have exactly 0 parameters");
                    error = true;
                }
            }
            break;
        case StmtVar:
            if (t->value.var.kind == TypeVoid) {
                typeError(t, "Variable cannot be declared with type void");
                error = true;
            }
            break;
        case StmtReturn:
            if (t->num_children > 0 && t->children[0]->attr.kind != SymVariable) {
                typeError(t, "Return value must be int");
                error = true;
            }

            if (state->currReturnType == TypeVoid) {
                typeError(t, "Return statement not allowed in a void function");
                error = true;
            }
            break;
        case StmtDeclList:
            if (t->num_children == 0) {
                typeError(t, "Program is empty");
                error = true;
            } else {
                Node last = t->children[t->num_children - 1];
                if (last->kind != NodeStmt || last->stmt != StmtFunction
                    || strcmp(last->value.func.name, "main") != 0) {
                    typeError(t, "Program must end with main()");
                    error = true;
                }
            }
        default:
            break;
        }
        break;
    default:
        break;
    }

    return error;
}

static void freeRecord(Record rec)
{
    if (rec->kind == SymFunction) {
        free(rec->func.param_types);
    }

    free(rec->linenos);
    free(rec);
}

/* Function buildSymtab constructs the symbol
 * table by preorder traversal of the syntax tree
 */
SymTable semanticAnalysis(Node t, bool* error)
{
    struct SemanticCheckStateRec state;
    state.functionLocCounter = 0;
    state.globalLocCounter = 0;
    state.scopeLevel = 0;
    state.sym = st_init(freeRecord);

    *error = buildSymtabImpl(t, &state);

    return state.sym;
}

static void printActivationRecord(const char* name, Record rec)
{
    printf("%s\t%d\t%d\n", name, rec->loc, rec->scope);
}

void printFormattedSymtab(SymTable tab)
{
    puts("Name\tLoc\tScope");
    puts("-------------------------");
    printSymTab(tab, printActivationRecord);
}
