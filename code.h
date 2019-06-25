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

#ifdef __GNUC__
__attribute__((__format__(__printf__, 2, 3)))
#endif
void emitInstruction(FILE* out, const char* msg, ...);

int resetInstrCnt(void);

void register_name(enum Storage reg, int reg_num, char* reg_name);

void load_local(FILE* out, Node t, enum Storage reg, int reg_num);

void exec_binop(FILE* out, Node t,
                enum Storage rst_reg, int rst_reg_num,
                enum Storage opa_reg, int opa_reg_num,
                enum Storage opb_reg, int opb_reg_num);

void load_id(FILE* out, Node t, enum Storage reg, int reg_num);

void store_id(FILE* out, int loc, enum Storage reg, int reg_num);

void fetchSourceLine(FILE* fp, int n, char* output, int maxLength);


#endif
