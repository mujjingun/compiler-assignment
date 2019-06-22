#include "cgen.h"
#include "analyze.h"
#include "code.h"
#include "scan.h"

#include <stdio.h>

static void expr_cgen(FILE* out, Node t, enum Storage reg, int reg_num)
{
    switch (t->expr) {
    case ExprConst:
    case ExprId:
        load_id(out, t, reg, reg_num);
        break;

    case ExprIndex:
        break;

    case ExprCall:
        //printSubTree(node->children[i], level + 1);
        //fprintf(out, "");
        break;

    case ExprArgs:
        // this should not appear
        break;

    case ExprBinOp:
        expr_cgen(out, t->children[0], Temp, reg_num);
        expr_cgen(out, t->children[1], Temp, reg_num + 1);
        exec_binop(out, t, Temp, reg_num, Temp, reg_num, Temp, reg_num + 1);
        t->storage = Temp;
        break;

    case ExprAssign: {
        expr_cgen(out, t->children[1], Temp, reg_num);
        if (t->children[0]->record->scope == 0) {
            // global store
            char reg_name[3], addr_reg_name[3];
            register_name(reg, reg_num, reg_name);
            register_name(reg, reg_num + 1, addr_reg_name);
            fprintf(out, "la $%s, %s\n", addr_reg_name, t->children[0]->value.name);
            fprintf(out, "sw $%s, 0($%s)\n", reg_name, addr_reg_name);
        } else {
            // local store
            int stackloc = t->children[0]->record->loc;
            store_id(out, stackloc, reg, reg_num);
        }
        break;
    }
    }
}

typedef struct codegenStateRec {
    FILE* out;
    FILE* data;
    int label_ctr;
} * codegenState;

static void cGen(Node t, codegenState state)
{
    FILE* out = state->out;
    FILE* data = state->data;

    switch (t->kind) {
    case NodeStmt: {
        switch (t->stmt) {
        case StmtVar:
            if (t->record->scope == 0) {
                // global declaration
                int size = 1;
                if (t->value.var.is_array) {
                    size = t->value.var.array_size;
                }
                fprintf(data, "%s: .word %d\n", t->value.var.name, size);
            }
            break;

        case StmtIf: {
            int else_label = state->label_ctr++;
            int end_label = state->label_ctr++;

            emitComment(out, "evaluate the condition");
            expr_cgen(out, t->children[0], Temp, 0);

            emitComment(out, "branch to else if the condition is false");
            fprintf(out, "beq $t0,$0,$_L%d\n\n", else_label);

            emitComment(out, "if block");
            cGen(t->children[1], state);

            emitComment(out, "jump to end");
            fprintf(out, "j $_L%d\n\n", end_label);

            emitComment(out, "else");
            fprintf(out, "$_L%d:\n", else_label);

            if (t->num_children == 3) {
                cGen(t->children[2], state);
            }

            emitComment(out, "end of if statement");
            fprintf(out, "$_L%d:\n\n", end_label);

            break;
        }

        case StmtWhile: {
            int loop_label = state->label_ctr++;
            int exit_label = state->label_ctr++;

            fprintf(out, "$_L%d: # loop\n", loop_label);

            emitComment(out, "evaluate the loop condition");
            expr_cgen(out, t->children[0], Temp, 0);

            emitComment(out, "exit if the condition is false");
            fprintf(out, "beq $t0,$0,$_L%d\n\n", exit_label);

            emitComment(out, "loop body");
            cGen(t->children[1], state);

            fprintf(out, "j $_L%d # loop\n", loop_label);

            fprintf(out, "$_L%d: # loop exit\n", exit_label);

            break;
        }

        case StmtReturn:
            expr_cgen(out, t->children[0], Temp, 0);
            fprintf(out, "move $v0, $t0 # set return value\n");
            break;

        case StmtDeclList: {
            for (int i = 0; i < t->num_children; i++) {
                cGen(t->children[i], state);
            }
            break;
        }

        case StmtExprStmt:
            for (int i = 0; i < t->num_children; i++) {
                cGen(t->children[i], state);
            }
            break;

        case StmtFunction: {
            fprintf(out, "%s:\n", t->value.func.name);

            emitComment(out, "set frame pointer");
            fprintf(out, "move $fp,$sp\n");

            emitComment(out, "push the return address");
            fprintf(out, "addiu $sp,$sp,%d\n", -4);
            fprintf(out, "sw $ra,0($sp)\n\n");

            for (int i = 0; i < t->num_children; i++) {
                cGen(t->children[i], state);
            }

            fprintf(out, "\n");
            emitComment(out, "restore return address");
            fprintf(out, "lw $ra,-4($fp)\n");

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
                cGen(t->children[i], state);
            }
            break;
        }

        case StmtCompoundStmt: {
            // calculate new stack size
            int size = 0;
            for (int i = 0; i < t->num_children; i++) {
                Node child = t->children[i];
                if (child->stmt == StmtVar) {
                    size += 4;
                }
            }

            // allocate stack for locals
            fprintf(out, "addiu $sp,$sp,%d # allocate locals\n\n", -size);

            for (int i = 0; i < t->num_children; i++) {
                cGen(t->children[i], state);
            }

            // pop stack
            fprintf(out, "addiu $sp,$sp,%d # free locals\n\n", size);
            break;
        }

        default:
            break;
        }
        break;
    }

    case NodeExpr: {
        expr_cgen(out, t, Temp, 0);
        break;
    }
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
    emitComment(out, "Source File: %s", filename);
    fputs(".align 2\n", out);
    fputs(".globl main\n\n", out);

    struct codegenStateRec rec;
    rec.out = out;
    rec.data = data;
    rec.label_ctr = 0;
    cGen(syntaxTree, &rec);

    // write standard procedures
    fputs("output:\n"
          "li $v0,1\n"
          "lw $a0,0($sp)\n"
          "syscall\n"
          "lw $fp,0($fp)\n"
          "j $ra\n\n",
        out);

    // write data
    fputs(".data\n", out);
    rewind(data);
    char buf[256];
    while (fgets(buf, 256, data)) {
        fputs(buf, out);
    }

    emitComment(out, "End of code.");

    printf("Generated assembly to: %s\n", filename);

    fclose(data);
fail:
    fclose(out);
}
