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
        char *name;
        enum OpKind op;
        struct {
            enum TypeKind type;
            bool is_array;
        } param;
        enum TypeKind return_type;
        struct {
            enum TypeKind type;
            bool is_array;
            int array_size;
        } var;
    } value;

    int num_children;
    Node* children;
};

void addChildToNode(Node node, Node newchild);

// expressions
Node makeConstNode(int num);
Node makeIdNode(const char* name);
Node makeIndexNode(Node var, Node index);
Node makeCallNode(Node func, Node args);
Node makeArgsNode(void);
Node makeBinOpNode(enum OpKind op, Node lhs, Node rhs);
Node makeAssignNode(Node lhs, Node rhs);

// statements
Node makeReturnNode(void);
Node makeWhileNode(Node cond, Node body);
Node makeIfNode(Node cond, Node body);
Node makeExprStmt(Node expr);

Node makeStmtListNode(void);
Node makeCompoundStatement(void);

// declarations
Node makeParamListNode(void);
Node makeParamNode(enum TypeKind type, bool is_array, Node id);

Node makeFunctionNode(enum TypeKind return_type, Node id, Node params, Node body);
Node makeVarDeclNode(enum TypeKind type, Node id);
Node makeArrayDeclNode(enum TypeKind type, int num, Node id);

Node makeDeclListNode(void);

// free
void freeNode(Node node);
void freeNodeCascade(Node node);

// print
void printTree(Node node);

#endif // SCAN_H
