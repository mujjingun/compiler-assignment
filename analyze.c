/****************************************************/
/* File: analyze.c                                  */
/* Semantic analyzer implementation                 */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "analyze.h"
#include "globals.h"
#include "symtab.h"
#include <string.h>

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(Node t)
{
    static int location = 0;

    switch (t->kind) {
    case NodeStmt:
        switch (t->stmt) {
        case StmtVar:
            if (st_lookup(t->value.var.name) == -1)
                /* not yet in table, so treat as new definition */
                st_insert(t->value.var.name, t->lineno, location++);
            else
                /* already in table, so ignore location,
                       add line number of use only */
                st_insert(t->value.var.name, t->lineno, 0);
            break;
        default:
            break;
        }
        break;
    case NodeExpr:
        switch (t->expr) {
        case ExprId:
            if (st_lookup(t->value.name) == -1)
                /* not yet in table, so treat as new definition */
                st_insert(t->value.name, t->lineno, location++);
            else
                /* already in table, so ignore location,
                       add line number of use only */
                st_insert(t->value.name, t->lineno, 0);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    // pre-order traversal
    for (int i = 0; i < t->num_children; i++) {
        buildSymtab(t->children[i]);
    }
}

static void typeError(Node t, char* message)
{
    fprintf(stderr, "Type error at line %d: %s\n", t->lineno, message);
    //Error = TRUE;
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
        default:
            break;
        }
        break;
    case NodeStmt:
        switch (t->stmt) {
        case StmtFunction:
            if (strcmp(t->value.func.name, "main") == 0) {
                if (t->value.func.return_type != TypeVoid) {
                    typeError(t, "Return type of main should always be void");
                }
                if (t->children[0]->num_children != 0) {
                    typeError(t, "main() should have exactly 0 parameters");
                }
            }
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
