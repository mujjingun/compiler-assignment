#include "scan.h"

#include <assert.h>
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
static Node allocNode(int lineno, enum NodeKind kind, int num_children)
{
    Node node = malloc(sizeof(struct NodeRec));
    node->kind = kind;
    node->lineno = lineno;
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

Node makeConstNode(int lineno, int num)
{
    Node node = allocNode(lineno, NodeConst, 0);
    node->value.num = num;

    return node;
}

Node makeVarNode(int lineno, char* name)
{
    Node node = allocNode(lineno, NodeId, 0);
    node->value.name = name;

    return node;
}

Node makeIndexNode(int lineno, char* id, Node index)
{
    Node node = allocNode(lineno, NodeIndex, 1);
    node->value.name = id;

    node->children[0] = index;

    return node;
}

Node makeCallNode(int lineno, char* func, Node args)
{
    Node node = allocNode(lineno, NodeCall, 1);
    node->value.name = func;

    node->children[0] = args;

    return node;
}

Node makeArgsNode(int lineno)
{
    return allocNode(lineno, NodeArgs, 0);
}

Node makeBinOpNode(int lineno, enum OpKind op, Node lhs, Node rhs)
{
    Node node = allocNode(lineno, NodeBinOp, 2);
    node->children[0] = lhs;
    node->children[1] = rhs;
    node->value.op = op;

    return node;
}

Node makeAssignNode(int lineno, Node lhs, Node rhs)
{
    Node node = allocNode(lineno, NodeAssign, 2);
    node->children[0] = lhs;
    node->children[1] = rhs;

    return node;
}

Node makeReturnNode(int lineno)
{
    return allocNode(lineno, NodeReturn, 0);
}

Node makeWhileNode(int lineno, Node cond, Node body)
{
    Node node = allocNode(lineno, NodeWhile, 2);
    node->children[0] = cond;
    node->children[1] = body;

    return node;
}

Node makeIfNode(int lineno, Node cond, Node body)
{
    Node node = allocNode(lineno, NodeIf, 2);
    node->children[0] = cond;
    node->children[1] = body;

    return node;
}

Node makeExprStmt(int lineno, Node expr)
{
    Node node = allocNode(lineno, NodeExprStmt, 1);
    node->children[0] = expr;

    return node;
}

Node makeStmtListNode(int lineno)
{
    return allocNode(lineno, NodeStmtList, 0);
}

Node makeCompoundStatement(int lineno)
{
    return allocNode(lineno, NodeCompoundStmt, 0);
}

Node makeParamListNode(int lineno)
{
    return allocNode(lineno, NodeParamList, 0);
}

Node makeParamNode(int lineno, enum TypeKind type, bool is_array, char* id)
{
    Node node = allocNode(lineno, NodeParam, 0);
    node->value.param.name = id;
    node->value.param.type = type;
    node->value.param.is_array = is_array;

    return node;
}

Node makeFunctionNode(int lineno, enum TypeKind return_type, char* id, Node params, Node body)
{
    Node node = allocNode(lineno, NodeFunction, 2);
    node->value.func.return_type = return_type;
    node->value.func.name = id;

    node->children[0] = params;
    node->children[1] = body;

    return node;
}

Node makeVarDeclNode(int lineno, enum TypeKind type, char* id)
{
    Node node = allocNode(lineno, NodeVar, 0);
    node->value.var.type = type;
    node->value.var.is_array = false;
    node->value.var.name = id;

    return node;
}

Node makeArrayDeclNode(int lineno, enum TypeKind type, int num, char* id)
{
    Node node = allocNode(lineno, NodeVar, 0);
    node->value.var.type = type;
    node->value.var.is_array = true;
    node->value.var.array_size = num;
    node->value.var.name = id;

    return node;
}

Node makeDeclListNode(int lineno)
{
    return allocNode(lineno, NodeDeclList, 0);
}

void freeNode(Node node)
{
    if (node->kind == NodeId
        || node->kind == NodeIndex
        || node->kind == NodeCall) {
        free(node->value.name);
    }
    if (node->kind == NodeVar) {
        free(node->value.var.name);
    }
    if (node->kind == NodeParam) {
        free(node->value.param.name);
    }
    if (node->kind == NodeFunction) {
        free(node->value.func.name);
    }

    free(node->children);
    free(node);
}

void freeNodeCascade(Node node)
{
    for (int i = 0; i < node->num_children; ++i) {
        freeNodeCascade(node->children[i]);
    }

    freeNode(node);
}
