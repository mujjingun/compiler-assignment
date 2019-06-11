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

    node->attr.kind = SymUnknown;
    node->attr.type = TypeVoid;
    node->attr.func.num_params = 0;
    node->attr.func.param_types = NULL;

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
    Node node = allocNode(lineno, NodeExpr, 0);
    node->expr = ExprConst;
    node->value.num = num;

    return node;
}

Node makeVarNode(int lineno, char* name)
{
    Node node = allocNode(lineno, NodeExpr, 0);
    node->expr = ExprId;
    node->value.name = name;

    return node;
}

Node makeIndexNode(int lineno, char* id, Node index)
{
    Node node = allocNode(lineno, NodeExpr, 1);
    node->expr = ExprIndex;
    node->value.name = id;

    node->children[0] = index;

    return node;
}

Node makeCallNode(int lineno, char* func)
{
    Node node = allocNode(lineno, NodeExpr, 0);
    node->expr = ExprCall;
    node->value.name = func;

    return node;
}

Node makeArgsNode(int lineno)
{
    Node node = allocNode(lineno, NodeExpr, 0);
    node->expr = ExprArgs;

    return node;
}

Node makeBinOpNode(int lineno, enum OpKind op, Node lhs, Node rhs)
{
    Node node = allocNode(lineno, NodeExpr, 2);
    node->expr = ExprBinOp;
    node->children[0] = lhs;
    node->children[1] = rhs;
    node->value.op = op;

    return node;
}

Node makeAssignNode(int lineno, Node lhs, Node rhs)
{
    Node node = allocNode(lineno, NodeExpr, 2);
    node->expr = ExprAssign;
    node->children[0] = lhs;
    node->children[1] = rhs;

    return node;
}

Node makeReturnNode(int lineno)
{
    Node node = allocNode(lineno, NodeStmt, 0);
    node->stmt = StmtReturn;

    return node;
}

Node makeWhileNode(int lineno, Node cond, Node body)
{
    Node node = allocNode(lineno, NodeStmt, 2);
    node->stmt = StmtWhile;
    node->children[0] = cond;
    node->children[1] = body;

    return node;
}

Node makeIfNode(int lineno, Node cond, Node body)
{
    Node node = allocNode(lineno, NodeStmt, 2);
    node->stmt = StmtIf;
    node->children[0] = cond;
    node->children[1] = body;

    return node;
}

Node makeExprStmt(int lineno, Node expr)
{
    Node node = allocNode(lineno, NodeStmt, 1);
    node->stmt = StmtExprStmt;
    node->children[0] = expr;

    return node;
}

Node makeStmtListNode(int lineno)
{
    Node node = allocNode(lineno, NodeStmt, 0);
    node->stmt = StmtStmtList;
    return node;
}

Node makeCompoundStatement(int lineno)
{
    Node node = allocNode(lineno, NodeStmt, 0);
    node->stmt = StmtCompoundStmt;
    node->value.is_function_body = false;

    return node;
}

Node makeParamListNode(int lineno)
{
    Node node = allocNode(lineno, NodeStmt, 0);
    node->stmt = StmtParamList;

    return node;
}

Node makeParamNode(int lineno, enum TypeKind type, bool is_array, char* id)
{
    Node node = allocNode(lineno, NodeStmt, 0);
    node->stmt = StmtParam;
    node->value.param.name = id;
    node->value.param.kind = type;
    node->value.param.is_array = is_array;

    return node;
}

Node makeFunctionNode(int lineno, enum TypeKind return_type, char* id, Node params, Node body)
{
    Node node = allocNode(lineno, NodeStmt, 2);
    node->stmt = StmtFunction;
    node->value.func.return_type = return_type;
    node->value.func.name = id;

    node->children[0] = params;

    body->value.is_function_body = true;
    node->children[1] = body;

    return node;
}

Node makeVarDeclNode(int lineno, enum TypeKind type, char* id)
{
    Node node = allocNode(lineno, NodeStmt, 0);
    node->stmt = StmtVar;
    node->value.var.kind = type;
    node->value.var.is_array = false;
    node->value.var.name = id;

    return node;
}

Node makeArrayDeclNode(int lineno, enum TypeKind type, int num, char* id)
{
    Node node = allocNode(lineno, NodeStmt, 0);
    node->stmt = StmtVar;
    node->value.var.kind = type;
    node->value.var.is_array = true;
    node->value.var.array_size = num;
    node->value.var.name = id;

    return node;
}

Node makeDeclListNode(int lineno)
{
    Node node = allocNode(lineno, NodeStmt, 0);
    node->stmt = StmtDeclList;

    return node;
}

void freeNode(Node node)
{
    if (node->kind == NodeExpr) {
        if (node->expr == ExprId
            || node->expr == ExprIndex
            || node->expr == ExprCall) {
            free(node->value.name);
        }
    } else {
        if (node->stmt == StmtVar) {
            free(node->value.var.name);
        }
        if (node->stmt == StmtParam) {
            free(node->value.param.name);
        }
        if (node->stmt == StmtFunction) {
            free(node->value.func.name);
        }
    }

    free(node->children);
    free(node);
}

void freeTree(Node node)
{
    for (int i = 0; i < node->num_children; ++i) {
        freeTree(node->children[i]);
    }

    freeNode(node);
}
