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

__attribute__((__format__(__printf__, 2, 3))) static int iprintf(int level, const char* fmt, ...)
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
        case NodeConst:
            iprintf(level, "Const : %d\n", node->value.num);
            break;

        case NodeId:
            iprintf(level, "Id : %s\n", node->value.name);
            break;

        case NodeIndex:
            iprintf(level, "Index id: %s\n", node->value.name);
            for (int i = 0; i < node->num_children; ++i) {
                printSubTree(node->children[i], level + 1);
            }
            break;

        case NodeCall:
            iprintf(level, "Call id: %s\n", node->value.name);
            for (int i = 0; i < node->num_children; ++i) {
                printSubTree(node->children[i], level + 1);
            }
            break;

        case NodeArgs:
            iprintf(level, "Arguments\n");
            for (int i = 0; i < node->num_children; ++i) {
                printSubTree(node->children[i], level + 1);
            }
            break;

        case NodeBinOp:
            iprintf(level, "Op %s\n", opToString(node->value.op));
            for (int i = 0; i < node->num_children; ++i) {
                printSubTree(node->children[i], level + 1);
            }
            break;

        case NodeAssign:
            iprintf(level, "Assign\n");
            for (int i = 0; i < node->num_children; ++i) {
                printSubTree(node->children[i], level + 1);
            }
            break;
        }
    } else {
        switch (node->stmt) {
        case NodeReturn:
            iprintf(level, "Return\n");
            printSubTree(node->children[0], level + 1);
            break;

        case NodeWhile:
            iprintf(level, "While\n");
            for (int i = 0; i < node->num_children; ++i) {
                printSubTree(node->children[i], level + 1);
            }
            break;

        case NodeIf:
            iprintf(level, "If\n");
            for (int i = 0; i < node->num_children; ++i) {
                printSubTree(node->children[i], level + 1);
            }
            break;

        case NodeExprStmt:
            printSubTree(node->children[0], level);
            break;

        case NodeStmtList:
            // this should not appear
            break;

        case NodeCompoundStmt:
            iprintf(level, "Compound Statement\n");
            for (int i = 0; i < node->num_children; ++i) {
                printSubTree(node->children[i], level + 1);
            }
            break;

        case NodeParamList:
            iprintf(level, "Parameters\n");
            if (node->num_children == 0) {
                iprintf(level + 1, "(Void)\n");
            } else {
                for (int i = 0; i < node->num_children; ++i) {
                    printSubTree(node->children[i], level + 1);
                }
            }
            break;

        case NodeParam:
            if (node->value.param.is_array) {
                iprintf(level, "Parameter id : %s\tType : %s[]\n",
                    node->value.param.name,
                    typeToString(node->value.param.type));
            } else {
                iprintf(level, "Parameter id : %s\tType : %s\n",
                    node->value.param.name,
                    typeToString(node->value.param.type));
            }
            break;

        case NodeFunction:
            iprintf(level, "Function id : %s\tType : %s\n",
                node->value.func.name,
                typeToString(node->value.func.return_type));

            // parameter
            printSubTree(node->children[0], level + 1);

            // body
            printSubTree(node->children[1], level + 1);
            break;

        case NodeVar:
            if (node->value.var.is_array) {
                iprintf(level, "Variable id : %s\tType : %s[%d]\n",
                    node->value.var.name,
                    typeToString(node->value.var.type),
                    node->value.var.array_size);
            } else {
                iprintf(level, "Variable id : %s\tType : %s\n",
                    node->value.var.name,
                    typeToString(node->value.var.type));
            }
            break;

        case NodeDeclList:
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
