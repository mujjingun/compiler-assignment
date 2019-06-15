#ifndef CODE_H
#define CODE_H

#include <stdio.h>
#include "scan.h"
#include "analyze.h"
#include "util.h"
#include "lex.yy.h"

#ifdef __GNUC__
__attribute__((__format__(__printf__, 2, 3)))
#endif
void emitComment(FILE* out, const char* msg, ...);

void register_name(enum Storage reg, int reg_num, char* reg_name);

void load_local(Node t, enum Storage reg, int reg_num);

void exec_binop(Node t,
                enum Storage rst_reg, int rst_reg_num,
                enum Storage opa_reg, int opa_reg_num,
                enum Storage opb_reg, int opb_reg_num);

#endif
