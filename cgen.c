#include "cgen.h"
#include "analyze.h"
#include "code.h"
#include "scan.h"

#include <stdio.h>

static void expr_cgen(Node t, enum Storage reg, int reg_num)
{
    switch (t->expr) {
    case ExprConst:
        break;

    case ExprId:
        break;

    case ExprIndex:
        break;

    case ExprCall:
        //printSubTree(node->children[i], level + 1);
        fprintf(stdout, "");
        break;

    case ExprArgs:
        // this should not appear
        break;

    case ExprBinOp:
        //printSubTree(node->children[i], level + 1);
        if(t->children[0]->storage != Temp)
        {
            expr_cgen(t->children[0], Temp, reg_num); 
        }

        if(t->children[1]->storage != Temp)
        {
            expr_cgen(t->children[0], Temp, reg_num + 1); 
        }
        exec_binop(t, Temp, reg, Temp, reg, Temp, reg + 1);
        t->storage = Temp;
        break;

    case ExprAssign:
        break;
    }
}

static void cGen(FILE* out, FILE* data, Node t)
{
    switch (t->kind) {
    case NodeStmt:
        switch (t->stmt) {
        case StmtVar: {
            if (t->record->scope == 0) {
                // global declaration
            } else {
                emitComment(out, "allocate storage for '%s'", t->value.var.name);
                fprintf(out, "addiu $sp,$sp,%d\n\n", -4);
            }
            break;
        }

        case StmtIf:
            break;

        case StmtParam:
            break;

        case StmtWhile:
            break;

        case StmtReturn:
            break;

        case StmtDeclList: {
            for (int i = 0; i < t->num_children; i++) {
                cGen(out, data, t->children[i]);
            }
            break;
        }

        case StmtExprStmt:
            break;

        case StmtFunction: {
            fprintf(out, "%s:\n", t->value.func.name);

            emitComment(out, "set frame pointer");
            fprintf(out, "move $fp,$sp\n");

            emitComment(out, "push the return address");
            fprintf(out, "addiu $sp,$sp,%d\n", -4);
            fprintf(out, "sw $ra,0($sp)\n\n");

            Node body = t->children[1];
            for (int i = 0; i < body->num_children; i++) {
                cGen(out, data, body->children[i]);
            }

            fprintf(out, "\n");
            emitComment(out, "restore return address");
            fprintf(out, "lw $ra,4($fp)\n");

            emitComment(out, "copy the fp to the sp");
            fprintf(out, "move $sp,$fp\n");

            emitComment(out, "load the control link into the fp");
            fprintf(out, "lw $fp,0($fp)\n");

            emitComment(out, "jump to the return address");
            fprintf(out, "j $ra\n\n");
            break;
        }

        case StmtStmtList: {
            for (int i = 0; i < t->num_children; i++) {
                cGen(out, data, t->children[i]);
            }
            break;
        }

        case StmtParamList:
            break;

        case StmtCompoundStmt: {
            for (int i = 0; i < t->num_children; i++) {
                cGen(out, data, t->children[i]);
            }
            break;
        }
        }
        break;
    case NodeExpr:
        expr_cgen(t, Temp, 0);
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
    fputs(".align 2\n", out);
    fputs(".globl main\n\n", out);

    cGen(out, data, syntaxTree);

    emitComment(out, "End of code.");

    printf("Generated assembly to: %s\n", filename);

    fclose(data);
fail:
    fclose(out);
}
