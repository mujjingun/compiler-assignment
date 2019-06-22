#include "util.h"
#include "lex.yy.h"

#include <stdarg.h>

const char* tokenToString(TokenType t)
{
    switch (t) {
    case ERROR:
        return "ERROR";
    case IF:
        return "IF";
    case ELSE:
        return "ELSE";
    case INT:
        return "INT";
    case RETURN:
        return "RETURN";
    case VOID:
        return "VOID";
    case WHILE:
        return "WHILE";
    case PLUS:
        return "+";
    case MINUS:
        return "-";
    case MULTIPLY:
        return "*";
    case DIVIDE:
        return "/";
    case LESSTHAN:
        return "<";
    case LESSTHANEQ:
        return "<=";
    case GREATERTHAN:
        return ">";
    case GREATERTHANEQ:
        return ">=";
    case EQUAL:
        return "==";
    case NOTEQUAL:
        return "!=";
    case ASSIGN:
        return "=";
    case SEMICOLON:
        return ";";
    case COMMA:
        return ",";
    case LPAREN:
        return "(";
    case RPAREN:
        return ")";
    case LBRACKET:
        return "[";
    case RBRACKET:
        return "]";
    case LBRACE:
        return "{";
    case RBRACE:
        return "}";
    case ID:
        return "ID";
    case NUM:
        return "NUM";
    }
    return "Unknown";
}

#ifdef __GNUC__
__attribute__((__format__(__printf__, 2, 3)))
#endif
static int
iprintf(int level, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    for (int i = 0; i < level; ++i) {
        printf("  ");
    }
    int result = vprintf(fmt, args);
    va_end(args);
    return result;
}

static void printSubTree(Node node, int level)
{
    if (node->kind == NodeExpr) {
        switch (node->expr) {
        case ExprConst:
            iprintf(level, "Const : %d\n", node->value.num);
            break;

        case ExprId:
            iprintf(level, "Id : %s\n", node->value.name);
            break;

        case ExprIndex:
            iprintf(level, "Index id: %s\n", node->value.name);
            printSubTree(node->children[0], level + 1);
            break;

        case ExprCall:
            iprintf(level, "Call id: %s\n", node->value.name);
            for (int i = 0; i < node->num_children; ++i) {
                printSubTree(node->children[i], level + 1);
            }
            break;

        case ExprBinOp:
            iprintf(level, "Op %s\n", opToString(node->value.op));
            for (int i = 0; i < node->num_children; ++i) {
                printSubTree(node->children[i], level + 1);
            }
            break;

        case ExprAssign:
            iprintf(level, "Assign\n");
            for (int i = 0; i < node->num_children; ++i) {
                printSubTree(node->children[i], level + 1);
            }
            break;
        }
    } else {
        switch (node->stmt) {
        case StmtReturn:
            iprintf(level, "Return\n");
            if (node->num_children == 1) {
                printSubTree(node->children[0], level + 1);
            }
            break;

        case StmtWhile:
            iprintf(level, "While\n");
            for (int i = 0; i < node->num_children; ++i) {
                printSubTree(node->children[i], level + 1);
            }
            break;

        case StmtIf:
            iprintf(level, "If\n");
            for (int i = 0; i < node->num_children; ++i) {
                printSubTree(node->children[i], level + 1);
            }
            break;

        case StmtExprStmt:
            printSubTree(node->children[0], level);
            break;

        case StmtCompoundStmt:
            iprintf(level, "Compound Statement\n");
            for (int i = 0; i < node->num_children; ++i) {
                printSubTree(node->children[i], level + 1);
            }
            break;

        case StmtParamList:
            iprintf(level, "Parameters\n");
            if (node->num_children == 0) {
                iprintf(level + 1, "(Void)\n");
            } else {
                for (int i = 0; i < node->num_children; ++i) {
                    printSubTree(node->children[i], level + 1);
                }
            }
            break;

        case StmtParam:
            if (node->value.param.is_array) {
                iprintf(level, "Parameter id : %s\tType : %s[]\n",
                    node->value.param.name,
                    typeToString(node->value.param.kind));
            } else {
                iprintf(level, "Parameter id : %s\tType : %s\n",
                    node->value.param.name,
                    typeToString(node->value.param.kind));
            }
            break;

        case StmtFunction:
            iprintf(level, "Function id : %s\tType : %s\n",
                node->value.func.name,
                typeToString(node->value.func.return_type));

            // parameter
            printSubTree(node->children[0], level + 1);

            // body
            printSubTree(node->children[1], level + 1);
            break;

        case StmtVar:
            if (node->value.var.is_array) {
                iprintf(level, "Variable id : %s\tType : %s[%d]\n",
                    node->value.var.name,
                    typeToString(node->value.var.kind),
                    node->value.var.array_size);
            } else {
                iprintf(level, "Variable id : %s\tType : %s\n",
                    node->value.var.name,
                    typeToString(node->value.var.kind));
            }
            break;

        case StmtDeclList:
            iprintf(level, "Syntax Tree:\n");
            for (int i = 0; i < node->num_children; ++i) {
                printSubTree(node->children[i], level + 1);
            }
            break;
        }
    }
}

void printTree(Node node)
{
    printSubTree(node, 0);
}

static void printSubTreeLatex(Node node, int level)
{
    if (node->kind == NodeExpr) {
        switch (node->expr) {
        case ExprConst:
            iprintf(level, "[{%d}]\n", node->value.num);
            break;

        case ExprId:
            iprintf(level, "[{%s}]\n", node->value.name);
            break;

        case ExprIndex:
            iprintf(level, "[{Index %s}\n", node->value.name);
            printSubTreeLatex(node->children[0], level + 1);
            iprintf(level, "]\n");
            break;

        case ExprCall:
            iprintf(level, "[{Call %s}\n", node->value.name);
            for (int i = 0; i < node->num_children; ++i) {
                printSubTreeLatex(node->children[i], level + 1);
            }
            iprintf(level, "]\n");
            break;

        case ExprBinOp:
            iprintf(level, "[{%s}\n", opToString(node->value.op));
            for (int i = 0; i < node->num_children; ++i) {
                printSubTreeLatex(node->children[i], level + 1);
            }
            iprintf(level, "]\n");
            break;

        case ExprAssign:
            iprintf(level, "[{Assign}\n");
            for (int i = 0; i < node->num_children; ++i) {
                printSubTreeLatex(node->children[i], level + 1);
            }
            iprintf(level, "]\n");
            break;
        }
    } else {
        switch (node->stmt) {
        case StmtReturn:
            iprintf(level, "[{Return}\n");
            if (node->num_children == 1) {
                printSubTreeLatex(node->children[0], level + 1);
            }
            iprintf(level, "]\n");
            break;

        case StmtWhile:
            iprintf(level, "[{While}\n");
            for (int i = 0; i < node->num_children; ++i) {
                printSubTreeLatex(node->children[i], level + 1);
            }
            iprintf(level, "]\n");
            break;

        case StmtIf:
            iprintf(level, "[{If}\n");
            for (int i = 0; i < node->num_children; ++i) {
                printSubTreeLatex(node->children[i], level + 1);
            }
            iprintf(level, "]\n");
            break;

        case StmtExprStmt:
            printSubTreeLatex(node->children[0], level);
            break;

        case StmtCompoundStmt:
            iprintf(level, "[{Compound Statement}\n");
            for (int i = 0; i < node->num_children; ++i) {
                printSubTreeLatex(node->children[i], level + 1);
            }
            iprintf(level, "]\n");
            break;

        case StmtParamList:
            iprintf(level, "[{Parameters}\n");
            if (node->num_children == 0) {
                iprintf(level + 1, "[{(Void)}]\n");
            } else {
                for (int i = 0; i < node->num_children; ++i) {
                    printSubTreeLatex(node->children[i], level + 1);
                }
            }
            iprintf(level, "]\n");
            break;

        case StmtParam:
            if (node->value.param.is_array) {
                iprintf(level, "[{%s : %s[]}]\n",
                    node->value.param.name,
                    typeToString(node->value.param.kind));
            } else {
                iprintf(level, "[{%s : %s}]\n",
                    node->value.param.name,
                    typeToString(node->value.param.kind));
            }
            break;

        case StmtFunction:
            iprintf(level, "[{Fun %s : %s}\n",
                node->value.func.name,
                typeToString(node->value.func.return_type));

            // parameter
            printSubTreeLatex(node->children[0], level + 1);

            // body
            printSubTreeLatex(node->children[1], level + 1);

            iprintf(level, "]\n");
            break;

        case StmtVar:
            if (node->value.var.is_array) {
                iprintf(level, "[{Var %s : %s[%d]}]\n",
                    node->value.var.name,
                    typeToString(node->value.var.kind),
                    node->value.var.array_size);
            } else {
                iprintf(level, "[{Var %s : %s}]\n",
                    node->value.var.name,
                    typeToString(node->value.var.kind));
            }
            break;

        case StmtDeclList:
            iprintf(level, "[{Program}\n");
            for (int i = 0; i < node->num_children; ++i) {
                printSubTreeLatex(node->children[i], level + 1);
            }
            iprintf(level, "]\n");
            break;
        }
    }
}

void printTreeLatex(Node node)
{
    printSubTreeLatex(node, 0);
}
