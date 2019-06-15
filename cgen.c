#include "cgen.h"
#include "code.h"

#include <stdio.h>

static void cGen(FILE* out, FILE* data, Node tree)
{
    switch (tree->kind) {
    case NodeStmt:
        switch (tree->stmt) {
        case StmtVar:
            break;
        }
        break;
    case NodeExpr:
        switch (tree->expr) {
        case ExprId:
            break;
        case ExprArgs:
            break;
        case ExprCall:
            break;
        case ExprBinOp:
            break;
        case ExprConst:
            break;
        case ExprIndex:
            break;
        case ExprAssign:
            break;
        }
        break;
    }
}

void codeGen(Node syntaxTree, const char* filename)
{
    FILE* out = fopen(filename, "w");
    if (!out) {
        fprintf(stderr, "Error: cannot open file '%s' for writing\n", filename);
        return;
    }

    FILE* data = tmpfile();
    if (!data) {
        fprintf(stderr, "Error: cannot open temporary file\n");
        goto fail;
    }

    emitComment(out, "C- Compilation to SPIM Code");
    emitComment(out, "File: %s", filename);

    cGen(out, data, syntaxTree);

    emitComment(out, "End of code.");

    printf("Generated assembly to: %s\n", filename);

    fclose(data);
fail:
    fclose(out);
}
