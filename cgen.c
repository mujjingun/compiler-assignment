#include "cgen.h"
#include "analyze.h"
#include "code.h"
#include "scan.h"

#include <stdio.h>

typedef struct debugSymbolsStateRec {
    FILE* source;
    int currentlineo;
    char buffer[128];
} debugSymbolState;

static void printSourceLine(FILE* out, debugSymbolState* debugSyms, int n)
{
    int offset = n - debugSyms->currentlineo;
    if (offset != 0) {
        memset(debugSyms->buffer, 0, sizeof(debugSyms->buffer));
        fetchSourceLine(debugSyms->source, offset, debugSyms->buffer,
            sizeof(debugSyms->buffer));
        debugSyms->currentlineo = n;
        debugSyms->buffer[strcspn(debugSyms->buffer, "\n")] = 0;
    }
    fprintf(out, "\n# %s\n", debugSyms->buffer);
}

static void expr_cgen(FILE* out, Node t, enum Storage reg,
    int reg_num, bool is_addr,
    debugSymbolState* debugSymbols)
{
    switch (t->expr) {
    case ExprConst: {
        char reg_name[3];
        register_name(reg, reg_num, reg_name);

        fprintf(out, "li    $%s, %d\n", reg_name, t->value.num);
        break;
    }

    case ExprId: {
        char reg_name[3];
        register_name(reg, reg_num, reg_name);

        if (is_addr) {
            if (t->record->scope == 0) {
                fprintf(out, "la    $%s, %s\n", reg_name, t->value.name);
            } else {
                int loc = t->record->loc;
                switch (t->storage) {
                case Memory:
                    fprintf(out, "addiu $%s, $fp, %d\n", reg_name, loc);
                    break;
                default:
                    break;
                }
            }
        } else {
            if (t->record->scope == 0) {
                if (t->record->kind == SymArray) {
                    fprintf(out, "la    $%s, %s\n", reg_name, t->value.name);
                } else {
                    fprintf(out, "la    $%s, %s\n", reg_name, t->value.name);
                    fprintf(out, "lw    $%s, 0($%s)\n", reg_name, reg_name);
                }
            } else {
                int loc = t->record->loc;
                switch (t->storage) {
                case Memory:
                    if (loc < 0) {
                        if (t->record->kind == SymArray) {
                            // local array
                            fprintf(out, "addiu $%s, $fp, %d\n", reg_name, loc);
                        } else {
                            // local var
                            fprintf(out, "lw    $%s, %d($fp)\n", reg_name, loc);
                        }
                    } else {
                        // argument
                        char other_reg_name[3];
                        register_name(Argument, loc, other_reg_name);
                        fprintf(out, "move  $%s, $%s\n", reg_name, other_reg_name);
                    }
                    break;
                default:
                    break;
                }
            }
        }
        break;
    }

    case ExprIndex: {
        if (debugSymbols)
            printSourceLine(out, debugSymbols, t->lineno);

        char idx_reg_name[3];
        register_name(reg, reg_num + 1, idx_reg_name);
        expr_cgen(out, t->children[0], Temp, reg_num + 1, false, debugSymbols);
        fprintf(out, "sll   $%s,$%s,2\n", idx_reg_name, idx_reg_name);

        char reg_name[3];
        register_name(reg, reg_num, reg_name);

        if (is_addr) {
            if (t->record->scope == 0) {
                fprintf(out, "la    $%s, %s\n", reg_name, t->value.name);
                fprintf(out, "addu  $%s, $%s, $%s\n", reg_name, reg_name, idx_reg_name);
            } else {
                int loc = t->record->loc;
                switch (t->storage) {
                case Memory:
                    if (loc < 0) {
                        fprintf(out, "addu  $%s, $fp, $%s\n", reg_name, idx_reg_name);
                        fprintf(out, "addiu $%s, $%s, %d\n", reg_name, reg_name, loc);
                    } else {
                        char other_reg_name[3];
                        register_name(Argument, loc, other_reg_name);
                        fprintf(out, "addu  $%s, $%s, $%s\n", reg_name, other_reg_name, idx_reg_name);
                    }
                    break;
                default:
                    break;
                }
            }
        } else {
            if (t->record->scope == 0) {
                fprintf(out, "la    $%s, %s\n", reg_name, t->value.name);
                fprintf(out, "addu  $%s, $%s, $%s\n", reg_name, reg_name, idx_reg_name);
                fprintf(out, "lw    $%s, 0($%s)\n", reg_name, reg_name);
            } else {
                int loc = t->record->loc;
                switch (t->storage) {
                case Memory:
                    if (loc < 0) {
                        fprintf(out, "addu  $%s, $fp, $%s\n", reg_name, idx_reg_name);
                        fprintf(out, "lw    $%s, %d($%s)\n", reg_name, loc, reg_name);
                    } else {
                        char other_reg_name[3];
                        register_name(Argument, loc, other_reg_name);
                        fprintf(out, "addu  $%s, $%s, $%s\n", reg_name, other_reg_name, idx_reg_name);
                        fprintf(out, "lw    $%s, 0($%s)\n", reg_name, reg_name);
                    }
                    break;
                default:
                    break;
                }
            }
        }
        break;
    }

    case ExprCall: {
        if (debugSymbols)
            printSourceLine(out, debugSymbols, t->lineno);

        char ret_reg_name[3];
        register_name(reg, reg_num, ret_reg_name);
        char reg_name[3];
        register_name(reg, reg_num + 4, reg_name);

        // push temporary, current argument registers
        fprintf(out, "addiu $sp, $sp,%d\n", -56);
        for (int i = 0; i < 10; ++i) {
            fprintf(out, "sw    $t%d, %d($sp)\n", i, i * 4);
        }
        for (int i = 0; i < 4; ++i) {
            fprintf(out, "sw    $a%d, %d($sp)\n", i, (i + 10) * 4);
        }

        // $t[reg_num:reg_num+4] = calculate_argments()
        // $a[0:4]               = $t[reg_num:reg_num+4]
        for (int i = 0; i < t->num_children; ++i) {
            expr_cgen(out, t->children[i], Temp, reg_num + i,
                false, debugSymbols);
            //fprintf(out, "move  $t%d, $%s\n", reg_num + i, reg_name);
        }
        for (int i = 0; i < t->num_children; ++i) {
            fprintf(out, "move  $a%d, $t%d\n", i, reg_num + i);
        }

        // push the control link
        fprintf(out, "addiu $sp,$sp,%d\n", -4);
        fprintf(out, "sw    $fp,0($sp) # push control link\n");

        // jump to the procedure
        fprintf(out, "jal   %s\n", t->value.name);

        // pop the control link
        fprintf(out, "sw    $fp,0($sp) # pop control link\n");
        fprintf(out, "addiu $sp,$sp,%d\n", 4);

        // pop temporary registers
        for (int i = 0; i < 10; ++i) {
            fprintf(out, "lw    $t%d, %d($sp)\n", i, i * 4);
        }
        for (int i = 0; i < 4; ++i) {
            fprintf(out, "lw    $a%d, %d($sp)\n", i, (i + 10) * 4);
        }
        fprintf(out, "addiu $sp,$sp,%d\n", 56);

        // return value
        fprintf(out, "move  $%s,$v0\n", ret_reg_name);
        break;
    }

    case ExprBinOp:
        if (debugSymbols)
            printSourceLine(out, debugSymbols, t->lineno);

        expr_cgen(out, t->children[0], Temp, reg_num, false, debugSymbols);
        expr_cgen(out, t->children[1], Temp, reg_num + 1, false, debugSymbols);
        exec_binop(out, t, Temp, reg_num, Temp, reg_num, Temp, reg_num + 1);
        t->storage = Temp;
        break;

    case ExprAssign: {
        if (debugSymbols)
            printSourceLine(out, debugSymbols, t->lineno);

        char addr_reg_name[3], reg_name[3];
        register_name(reg, reg_num, addr_reg_name);
        register_name(reg, reg_num + 1, reg_name);

        if (t->children[0]->expr == ExprId && t->children[0]->record->loc > 0) {
            // special-case argument as lhs
            int loc = t->children[0]->record->loc;
            char other_reg_name[3];
            register_name(Argument, loc, other_reg_name);

            // value
            expr_cgen(out, t->children[1], Temp, reg_num + 1, false, debugSymbols);

            fprintf(out, "move $%s, $%s\n", other_reg_name, reg_name);
        } else {
            // asignee address
            expr_cgen(out, t->children[0], Temp, reg_num, true, debugSymbols);

            // value
            expr_cgen(out, t->children[1], Temp, reg_num + 1, false, debugSymbols);

            fprintf(out, "sw    $%s, 0($%s)\n", reg_name, addr_reg_name);
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

static void cGen(Node t, codegenState state, debugSymbolState* debugSymbols)
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
            expr_cgen(out, t->children[0], Temp, 0, false, debugSymbols);

            emitComment(out, "branch to else if the condition is false");
            fprintf(out, "beq   $t0,$0,$_L%d\n\n", else_label);

            emitComment(out, "if block");
            cGen(t->children[1], state, debugSymbols);

            emitComment(out, "jump to end");
            fprintf(out, "j     $_L%d\n\n", end_label);

            emitComment(out, "else");
            fprintf(out, "$_L%d:\n", else_label);

            if (t->num_children == 3) {
                cGen(t->children[2], state, debugSymbols);
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
            expr_cgen(out, t->children[0], Temp, 0, false, debugSymbols);

            emitComment(out, "exit if the condition is false");
            fprintf(out, "beq   $t0,$0,$_L%d\n\n", exit_label);

            emitComment(out, "loop body");
            cGen(t->children[1], state, debugSymbols);

            fprintf(out, "j     $_L%d # loop\n", loop_label);

            fprintf(out, "$_L%d: # loop exit\n", exit_label);

            break;
        }

        case StmtReturn:
            expr_cgen(out, t->children[0], Temp, 0, false, debugSymbols);
            fprintf(out, "move  $v0, $t0 # set return value\n");

            emitComment(out, "restore return address");
            fprintf(out, "lw    $ra,-4($fp)\n");

            emitComment(out, "copy the fp to the sp");
            fprintf(out, "move  $sp,$fp\n");

            emitComment(out, "load the control link into the fp");
            fprintf(out, "lw    $fp,0($fp)\n");

            emitComment(out, "jump to the return address");
            fprintf(out, "j     $ra\n\n");
            break;

        case StmtDeclList: {
            for (int i = 0; i < t->num_children; i++) {
                cGen(t->children[i], state, debugSymbols);
            }
            break;
        }

        case StmtExprStmt:
            for (int i = 0; i < t->num_children; i++) {
                cGen(t->children[i], state, debugSymbols);
            }
            break;

        case StmtFunction: {
            fprintf(out, "%s:\n", t->value.func.name);

            emitComment(out, "set frame pointer");
            fprintf(out, "move  $fp,$sp\n");

            emitComment(out, "push the return address");
            fprintf(out, "addiu $sp,$sp,%d\n", -4);
            fprintf(out, "sw    $ra,0($sp)\n\n");

            for (int i = 0; i < t->num_children; i++) {
                cGen(t->children[i], state, debugSymbols);
            }

            fprintf(out, "\n");
            emitComment(out, "restore return address");
            fprintf(out, "lw    $ra,-4($fp)\n");

            emitComment(out, "copy the fp to the sp");
            fprintf(out, "move  $sp,$fp\n");

            emitComment(out, "load the control link into the fp");
            fprintf(out, "lw    $fp,0($fp)\n");

            emitComment(out, "jump to the return address");
            fprintf(out, "j     $ra\n\n");
            break;
        }

        case StmtCompoundStmt: {
            // calculate new stack size
            int size = 0;
            for (int i = 0; i < t->num_children; i++) {
                Node child = t->children[i];
                if (child->stmt == StmtVar) {
                    if (child->value.var.is_array) {
                        size += child->value.var.array_size * 4;
                    } else {
                        size += 4;
                    }
                }
            }

            // allocate stack for locals
            fprintf(out, "addiu $sp,$sp,%d # allocate locals\n\n", -size);

            for (int i = 0; i < t->num_children; i++) {
                cGen(t->children[i], state, debugSymbols);
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
        expr_cgen(out, t, Temp, 0, false, debugSymbols);
        break;
    }
    }
}

void codeGen(Node syntaxTree, const char* filename,
    bool writeDebug, FILE* source)
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

    debugSymbolState debugSymbols;
    if (writeDebug) {
        debugSymbols.currentlineo = 0;
        debugSymbols.source = source;
    }

    struct codegenStateRec rec;
    rec.out = out;
    rec.data = data;
    rec.label_ctr = 0;
    cGen(syntaxTree, &rec, writeDebug ? &debugSymbols : NULL);

    // write standard procedures
    fputs("output:\n"
          "li    $v0,1\n"
          "syscall\n"
          "li    $v0,4\n"
          "la    $a0,_Newline\n"
          "syscall\n"
          "j     $ra\n\n",
        out);
    fputs("input:\n"
          "li    $v0,5\n"
          "syscall\n"
          "j     $ra\n\n",
        out);

    // write data
    fputs(".data\n"
          "_Newline: .asciiz \"\\n\"\n",
        out);
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
