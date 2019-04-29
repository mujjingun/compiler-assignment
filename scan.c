#include "scan.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* opToString(enum OpKind op)
{
    switch (op) {
    case OpLessThan:
        return "<";
    case OpLessThanEq:
        return "<=";
    case OpGreaterThan:
        return ">";
    case OpGreaterThanEq:
        return ">=";
    case OpEqual:
        return "==";
    case OpNotEqual:
        return "!=";
    case OpAdd:
        return "+";
    case OpSubtract:
        return "-";
    case OpMultiply:
        return "*";
    case OpDivide:
        return "/";
    }
    return "Unknown";
}

const char* typeToString(enum TypeKind t)
{
    return t == TypeInt ? "int" : "void";
}

// Allocate a node
static Node allocNode(enum NodeKind kind, int num_children)
{
    Node node = malloc(sizeof(struct NodeRec));
    node->kind = kind;
    node->num_children = num_children;

    if (num_children > 0) {
        node->children = malloc(sizeof(Node) * num_children);
    } else {
        node->children = NULL;
    }
    return node;
}

void addChildToNode(Node node, Node newChild)
{
    node->num_children++;
    node->children = realloc(node->children, sizeof(Node) * node->num_children);
    node->children[node->num_children - 1] = newChild;
}

Node makeConstNode(int num)
{
    Node node = allocNode(NodeConst, 0);
    node->value.num = num;

    return node;
}

Node makeIdNode(const char* name)
{
    Node node = allocNode(NodeId, 0);
    node->value.name = malloc(strlen(name) + 1);
    strcpy(node->value.name, name);

    return node;
}

Node makeIndexNode(Node var, Node index)
{
    Node node = allocNode(NodeIndex, 2);
    node->children[0] = var;
    node->children[1] = index;

    return node;
}

Node makeCallNode(Node func, Node args)
{
    Node node = allocNode(NodeCall, 2);
    node->children[0] = func;
    node->children[1] = args;

    return node;
}

Node makeArgsNode(void)
{
    return allocNode(NodeArgs, 0);
}

Node makeBinOpNode(enum OpKind op, Node lhs, Node rhs)
{
    Node node = allocNode(NodeBinOp, 2);
    node->children[0] = lhs;
    node->children[1] = rhs;
    node->value.op = op;

    return node;
}

Node makeAssignNode(Node lhs, Node rhs)
{
    Node node = allocNode(NodeAssign, 2);
    node->children[0] = lhs;
    node->children[1] = rhs;

    return node;
}

Node makeReturnNode(void)
{
    return allocNode(NodeReturn, 0);
}

Node makeWhileNode(Node cond, Node body)
{
    Node node = allocNode(NodeWhile, 2);
    node->children[0] = cond;
    node->children[1] = body;

    return node;
}

Node makeIfNode(Node cond, Node body)
{
    Node node = allocNode(NodeIf, 2);
    node->children[0] = cond;
    node->children[1] = body;

    return node;
}

Node makeExprStmt(Node expr)
{
    Node node = allocNode(NodeExprStmt, 1);
    node->children[0] = expr;

    return node;
}

Node makeStmtListNode(void)
{
    return allocNode(NodeStmtList, 0);
}

Node makeCompoundStatement(void)
{
    return allocNode(NodeCompoundStmt, 0);
}

Node makeParamListNode()
{
    return allocNode(NodeParamList, 0);
}

Node makeParamNode(enum TypeKind type, bool is_array, Node id)
{
    Node node = allocNode(NodeParam, 1);
    node->value.param.type = type;
    node->value.param.is_array = is_array;

    node->children[0] = id;

    return node;
}

Node makeFunctionNode(enum TypeKind return_type, Node id, Node params, Node body)
{
    Node node = allocNode(NodeFunction, 3);
    node->value.return_type = return_type;

    node->children[0] = id;
    node->children[1] = params;
    node->children[2] = body;

    return node;
}

Node makeVarDeclNode(enum TypeKind type, Node id)
{
    Node node = allocNode(NodeVar, 1);
    node->value.var.type = type;
    node->value.var.is_array = false;

    node->children[0] = id;

    return node;
}

Node makeArrayDeclNode(enum TypeKind type, int num, Node id)
{
    Node node = allocNode(NodeVar, 1);
    node->value.var.type = type;
    node->value.var.is_array = true;
    node->value.var.array_size = num;

    node->children[0] = id;

    return node;
}

Node makeDeclListNode()
{
    return allocNode(NodeDeclList, 0);
}

void freeNode(Node node)
{
    if (node->kind == NodeId) {
        free(node->value.name);
    }

    free(node->children);
    free(node);
}

void freeNodeCascade(Node node)
{
    for (int i = 0; i < node->num_children; ++i) {
        freeNode(node->children[i]);
    }

    freeNode(node);
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
    switch (node->kind) {
    case NodeConst:
        iprintf(level, "Const : %d\n", node->value.num);
        break;

    case NodeId:
        iprintf(level, "Id : %s\n", node->value.name);
        break;

    case NodeIndex:
        iprintf(level, "Index\n");
        for (int i = 0; i < node->num_children; ++i) {
            printSubTree(node->children[i], level + 1);
        }
        break;

    case NodeCall:
        iprintf(level, "Call\n");
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
        assert(false);
        break;

    case NodeCompoundStmt:
        iprintf(level, "Compound Statement\n");
        for (int i = 0; i < node->num_children; ++i) {
            printSubTree(node->children[i], level + 1);
        }
        break;

    case NodeParamList:
        iprintf(level, "Parameters\n");
        for (int i = 0; i < node->num_children; ++i) {
            printSubTree(node->children[i], level + 1);
        }
        break;

    case NodeParam:
        assert(node->children[0]->kind == NodeId);
        iprintf(level, "Parameter id : %s\tType : %s\n",
            node->children[0]->value.name,
            typeToString(node->value.param.type));
        break;

    case NodeFunction:
        assert(node->children[0]->kind == NodeId);
        iprintf(level, "Function id : %s\tType : %s\n",
            node->children[0]->value.name,
            typeToString(node->value.return_type));

        // parameter
        printSubTree(node->children[1], level + 1);

        // body
        printSubTree(node->children[2], level + 1);
        break;

    case NodeVar:
        iprintf(level, "Variable\n");
        assert(node->children[0]->kind == NodeId);
        iprintf(level + 1, "id : %s\tType : %s\n",
            node->children[0]->value.name,
            typeToString(node->value.var.type));
        break;

    case NodeDeclList:
        iprintf(level, "Syntax Tree:\n");
        for (int i = 0; i < node->num_children; ++i) {
            printSubTree(node->children[i], level + 1);
        }
        break;
    }
}

void printTree(Node node)
{
    printSubTree(node, 0);
}
