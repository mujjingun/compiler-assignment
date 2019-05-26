#ifndef SCAN_H
#define SCAN_H

#include <stdbool.h>

typedef struct NodeRec* Node;

// scanner
struct Scanner {
    void* flex;
    Node tree;
};

enum NodeKind {
    NodeStmt,
    NodeExpr
};

enum ExprKind {
    ExprConst,
    ExprId,
    ExprIndex,
    ExprCall,
    ExprArgs,
    ExprBinOp,
    ExprAssign,
};

enum StmtKind {
    StmtReturn,
    StmtWhile,
    StmtIf,
    StmtExprStmt,

    StmtStmtList,
    StmtCompoundStmt,
    StmtParamList,
    StmtParam,
    StmtFunction,
    StmtVar,
    StmtDeclList,
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

enum SymbolType {
    SymUnknown,
    SymVariable,
    SymArray,
    SymFunction,
};

struct NodeRec {

    union {
        enum ExprKind expr;
        enum StmtKind stmt;
    };
    enum NodeKind kind;

    union {
        int num;
        char* name;
        enum OpKind op;
        struct {
            char* name;
            enum TypeKind kind;
            bool is_array;
        } param;
        struct {
            enum TypeKind return_type;
            char* name;
        } func;
        struct {
            enum TypeKind kind;
            char* name;
            bool is_array;
            int array_size;
        } var;
        bool is_function_body;
    } value;

    union {
        struct {
            enum SymbolType kind;
        };
    } attr;

    int lineno;

    int num_children;
    Node* children;
};

void addChildToNode(Node node, Node newchild);

// expressions
Node makeConstNode(int lineno, int num);
Node makeVarNode(int lineno, char* name);
Node makeIndexNode(int lineno, char* id, Node index);
Node makeCallNode(int lineno, char* func);
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
