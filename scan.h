#ifndef SCAN_H
#define SCAN_H

#include <stdbool.h>

typedef struct NodeRec* Node;

// scanner
struct Scanner {
    void* flex;
    const char* error_msg;
    Node tree;
};

enum NodeKind {
    NodeConst,
    NodeId,
    NodeIndex,
    NodeCall,
    NodeArgs,
    NodeBinOp,
    NodeAssign,

    NodeReturn,
    NodeWhile,
    NodeIf,
    NodeExprStmt,

    NodeStmtList,
    NodeCompoundStmt,
    NodeParamList,
    NodeParam,
    NodeFunction,
    NodeVar,
    NodeDeclList,
};

enum OpKind {
    OpLessThan,
    OpLessThanEq,
    OpGreaterThan,
    OpGreaterThanEq,
    OpEqual,
    OpNotEqual,
    OpAdd,
    OpSubtract,
    OpMultiply,
    OpDivide,
};

const char* opToString(enum OpKind op);

enum TypeKind {
    TypeInt,
    TypeVoid,
};

const char* typeToString(enum TypeKind t);

struct NodeRec {
    enum NodeKind kind;
    union {
        int num;
        char* name;
        enum OpKind op;
        struct {
            char* name;
            enum TypeKind type;
            bool is_array;
        } param;
        struct {
            enum TypeKind return_type;
            char* name;
        } func;
        struct {
            enum TypeKind type;
            char* name;
            bool is_array;
            int array_size;
        } var;
    } value;

    int lineno;

    int num_children;
    Node* children;
};

void addChildToNode(Node node, Node newchild);

// expressions
Node makeConstNode(int lineno, int num);
Node makeVarNode(int lineno, char* name);
Node makeIndexNode(int lineno, char* id, Node index);
Node makeCallNode(int lineno, char* func, Node args);
Node makeArgsNode(int lineno);
Node makeBinOpNode(int lineno, enum OpKind op, Node lhs, Node rhs);
Node makeAssignNode(int lineno, Node lhs, Node rhs);

// statements
Node makeReturnNode(int lineno);
Node makeWhileNode(int lineno, Node cond, Node body);
Node makeIfNode(int lineno, Node cond, Node body);
Node makeExprStmt(int lineno, Node expr);

Node makeStmtListNode(int lineno);
Node makeCompoundStatement(int lineno);

// declarations
Node makeParamListNode(int lineno);
Node makeParamNode(int lineno, enum TypeKind type, bool is_array, char* id);

Node makeFunctionNode(int lineno, enum TypeKind return_type, char* id, Node params, Node body);
Node makeVarDeclNode(int lineno, enum TypeKind type, char* id);
Node makeArrayDeclNode(int lineno, enum TypeKind type, int num, char* id);

Node makeDeclListNode(int lineno);

// free
void freeNode(Node node);
void freeNodeCascade(Node node);

#endif // SCAN_H