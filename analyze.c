
#include "analyze.h"
#include "globals.h"
#include "symtab.h"
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static Record makeRecord(Node node, int loc, int scope)
{
    Record rec = malloc(sizeof(struct ActivationRecord));
    rec->loc = loc;
    rec->scope = scope;

    assert(node->kind == NodeStmt
        && (node->stmt == StmtVar || node->stmt == StmtFunction || node->stmt == StmtParam));

    if (node->stmt == StmtVar) {
        rec->vpf = VPFVariable;
        if (node->value.var.kind == TypeVoid) {
            rec->kind = SymUnknown;
        } else if (node->value.var.is_array) {
            rec->kind = SymArray;
            rec->arr_size = node->value.var.array_size;
        } else {
            rec->kind = SymVariable;
        }
        rec->type = node->value.var.kind;
    } else if (node->stmt == StmtFunction) {
        rec->vpf = VPFFunction;
        rec->kind = SymFunction;
        rec->type = node->value.func.return_type;

        Node params = node->children[0];
        rec->func.num_params = params->num_children;
        rec->func.param_types = NULL;
        if (rec->func.num_params > 0) {
            rec->func.param_types = malloc(sizeof(enum SymbolType) * rec->func.num_params);
            for (int i = 0; i < rec->func.num_params; ++i) {
                Node param = params->children[i];
                if (param->value.param.is_array) {
                    rec->func.param_types[i] = SymArray;
                } else {
                    rec->func.param_types[i] = SymVariable;
                }
            }
        }
    } else if (node->stmt == StmtParam) {
        rec->vpf = VPFParam;
        if (node->value.param.kind == TypeVoid) {
            rec->kind = SymUnknown;
        } else if (node->value.param.is_array) {
            rec->kind = SymArray;
        } else {
            rec->kind = SymVariable;
        }
        rec->type = node->value.param.kind;
    }

    // set attributes
    node->attr.kind = rec->kind;
    node->attr.type = rec->type;

    rec->num_linenos = 1;
    rec->linenos = malloc(sizeof(int) * 1);
    rec->linenos[0] = node->lineno;
    return rec;
}

static void RecordAddLineno(Record rec, int lineno)
{
    if (rec->linenos[rec->num_linenos - 1] != lineno) {
        rec->num_linenos++;
        rec->linenos = realloc(rec->linenos, sizeof(int) * rec->num_linenos);
        rec->linenos[rec->num_linenos - 1] = lineno;
    }
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

typedef struct BuildSymtabStateRec {
    int functionLocCounter;
    int paramLocCounter;
    int lastLocalLoc;
    int localLocCounter;
    int globalLocCounter;
    int scopeLevel;
    enum TypeKind currReturnType;
    SymTable sym;
} * BuildSymtabState;

static bool buildSymtabImpl(Node t,
			    BuildSymtabState state,
			    bool printSymbolTable)
{
    Record result;

    bool error = false;

    switch (t->kind) {
    case NodeStmt:
        switch (t->stmt) {
        case StmtVar:
            if ((result = st_lookup(state->sym, t->value.var.name))
		&& result->scope == state->scopeLevel) {
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
                t->record = rec;
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
                Record rec = makeRecord(t, state->functionLocCounter,
					state->scopeLevel);
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
            if ((result = st_lookup(state->sym, t->value.param.name)) && result->scope == state->scopeLevel) {
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

            state->lastLocalLoc = state->localLocCounter;
            break;
        default:
            break;
        }
        break;
    case NodeExpr:
        switch (t->expr) {
        case ExprId:
        case ExprIndex:
            if ((result = st_lookup(state->sym, t->value.name))) {
                // already in table, so ignore location,
                // add line number of use only
                RecordAddLineno(result, t->lineno);

                // set attributes
                t->record = result;
                t->storage = Memory;
                t->attr.kind = result->kind;
                t->attr.type = result->type;
            } else {
                // Usage of an undeclared identifier
                idError(t, "Unknown identifier '%s'", t->value.name);
                error = true;
            }
            break;
        case ExprCall:
            if ((result = st_lookup(state->sym, t->value.name))) {
                if (result->kind != SymFunction) {
                    idError(t, "'%s' is not a function", t->value.name);
                    error = true;
                    break;
                }

                // already in table, so ignore location,
                // add line number of use only
                RecordAddLineno(result, t->lineno);

                // set attributes
                t->attr.kind = result->kind;
                t->attr.type = result->type;
                t->attr.func.num_params = result->func.num_params;
                if (t->attr.func.num_params > 0) {
                    t->attr.func.param_types = malloc(sizeof(enum SymbolType) * t->attr.func.num_params);
                    for (int i = 0; i < t->attr.func.num_params; ++i) {
                        t->attr.func.param_types[i] = result->func.param_types[i];
                    }
                }
            } else {
                // Usage of an undeclared identifier
                idError(t, "Unknown function identifier '%s'", t->value.name);
                error = true;
            }
            break;
        default:
            break;
        }
        break;
    }

    // recursive traversal
    for (int i = 0; i < t->num_children; i++) {
        error = buildSymtabImpl(t->children[i], state,
				printSymbolTable) || error;
    }

    switch (t->kind) {
    case NodeStmt:
        switch (t->stmt) {
        case StmtFunction:
	    if(printSymbolTable)
		printFormattedSymtab(state->sym);
            st_exit_scope(state->sym);
            state->scopeLevel--;
            break;
        case StmtCompoundStmt:
            // exit scope
            if (!t->value.is_function_body) {
		if(printSymbolTable)
		    printFormattedSymtab(state->sym);
                st_exit_scope(state->sym);
                state->scopeLevel--;
            }

            state->localLocCounter = state->lastLocalLoc;
            break;
        default:
            break;
        }
        break;
    case NodeExpr:
        break;
    }

    return error;
}

typedef struct TypeCheckStateRec {
    enum TypeKind currReturnType;
} * TypeCheckState;

static bool typeCheckImpl(Node t,
			  TypeCheckState state)
{
    bool error = false;

    switch (t->kind) {
    case NodeStmt:
        switch (t->stmt) {
        case StmtFunction:
            state->currReturnType = t->attr.type;
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
        error = typeCheckImpl(t->children[i], state) || error;
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
        case ExprIndex: {
            if (t->children[0]->attr.kind != SymVariable) {
                typeError(t, "Array subscript is not int");
                error = true;
            }
            if (t->attr.kind != SymArray) {
                typeError(t, "'%s' is not an array", t->value.name);
                error = true;
            }
            t->attr.kind = SymVariable;
        } break;
        case ExprCall: {
            int min_count = t->num_children;
            if (min_count > t->attr.func.num_params) {
                min_count = t->attr.func.num_params;
            }

            for (int i = 0; i < min_count; ++i) {
                enum SymbolType param_type = t->attr.func.param_types[i];
                enum SymbolType arg_type = t->children[i]->attr.kind;
                if (param_type != arg_type) {
                    typeError(t, "Type of parameter #%d does not match type of argument", i + 1);
                    error = true;
                }
            }

            if (t->num_children != t->attr.func.num_params) {
                typeError(t, "%d arguments passed to function '%s' with %d parameters",
                    t->num_children, t->value.name, t->attr.func.num_params);
                error = true;
            }
            if (t->attr.type == TypeVoid) {
                t->attr.kind = SymUnknown;
            } else {
                t->attr.kind = SymVariable;
            }
        } break;
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
            if (t->num_children > 0) {
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

/* Function semanticAnalysis constructs the symbol
 * table by preorder traversal of the syntax tree
 */
bool semanticAnalysis(Node t, bool printSymTable)
{
    struct BuildSymtabStateRec state;
    state.functionLocCounter = 0;
    state.globalLocCounter = 0;
    state.scopeLevel = 0;

    // build the symbol table
    state.sym = st_init(freeRecord);

    // add standard procedures
    {
        Record rec = malloc(sizeof(struct ActivationRecord));
        rec->loc = -1;
        rec->scope = 0;

        rec->vpf = VPFFunction;
        rec->kind = SymFunction;
        rec->type = TypeVoid;

        rec->func.num_params = 1;
        rec->func.param_types = malloc(sizeof(enum SymbolType) * 1);
        rec->func.param_types[0] = SymVariable;

        rec->num_linenos = 1;
        rec->linenos = malloc(sizeof(int) * 1);
        rec->linenos[0] = -1;
        st_insert(state.sym, "output", rec);
    }
    {
        Record rec = malloc(sizeof(struct ActivationRecord));
        rec->loc = -1;
        rec->scope = 0;

        rec->vpf = VPFFunction;
        rec->kind = SymFunction;
        rec->type = TypeInt;

        rec->func.num_params = 0;
        rec->func.param_types = NULL;

        rec->num_linenos = 1;
        rec->linenos = malloc(sizeof(int) * 1);
        rec->linenos[0] = -1;
        st_insert(state.sym, "input", rec);
    }

    bool error = buildSymtabImpl(t, &state, printSymTable);

    if(printSymTable)
	printFormattedSymtab(state.sym);

    st_free(state.sym);

    // type checking
    struct TypeCheckStateRec typeCheckState;
    error = typeCheckImpl(t, &typeCheckState) || error;

    return error;
}

static void printActivationRecord(const char* name, Record rec)
{
    printf("%s\t%d\t%d\t", name, rec->scope, rec->loc);

    switch (rec->vpf) {
    case VPFVariable:
        printf("Var\t");
        break;
    case VPFParam:
        printf("Param\t");
        break;
    case VPFFunction:
        printf("Func\t");
        break;
    }

    if (rec->kind == SymArray) {
        printf("Yes\t");
    } else {
        printf("No\t");
    }

    if (rec->vpf == VPFVariable && rec->kind == SymArray) {
        printf("%d\t", rec->arr_size);
    } else {
        printf("-\t");
    }

    if (rec->kind == SymArray) {
        printf("array\t");
    } else {
        printf("%s\t", typeToString(rec->type));
    }

    for (int i = 0; i < rec->num_linenos; ++i) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", rec->linenos[i]);
    }
    puts("");
}

void printFormattedSymtab(SymTable tab)
{
    const char* heading = "Name\tScope\tLoc\tV/P/F\tArray?\tArrSize\tType\tLine numbers\n"
                          "--------------------------------------------------------------------";
    printSymTab(tab, heading, printActivationRecord);
}
