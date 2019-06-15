
#include <stdarg.h>
#include "code.h"

#define GLOBAL_SCOPE  0

void emitComment(FILE *out, const char *msg, ...)
{
    va_list args;

    fprintf(out, "# ");

    va_start(args, msg);
    vfprintf(out, msg, args);
    va_end(args);

    fprintf(out, "\n");
}

void register_name(enum Storage reg, int reg_num, char* reg_name)
{
    char reg_prefix ;
    switch(reg)
    {
    case Temp:
        reg_prefix = 't';
        break;
    case SavedTemp:
        reg_prefix = 's';
        break;
    case Return:
        reg_prefix = 'v';
        break;
    case Argument:
        reg_prefix = 'a';
        break;
    default:
        reg_prefix = '0';
        break;
    }
    sprintf(reg_name, "%c%d", reg_prefix, reg_num);
}

void load_id(Node t, enum Storage reg, int reg_num)
{
    char reg_name[3];
    register_name(reg, reg_num, reg_name);

    if(t->record->scope == GLOBAL_SCOPE)
    {
        /* incomplete */
        fprintf(stdout, "la $%s, %s", "", "");
    }
    else if(t->expr == ExprConst)
    {
        fprintf(stdout, "li $%s, %d\n", reg_name, t->value.num);
    }
    else
    {
        int loc = t->record->loc;
        switch(t->storage) 
        {
        case Memory:
            fprintf(stdout, "lw $%s, %d($fp)\n", reg_name, loc);
            break;
        default:
            break;
        }
    }
}

void store_id(int loc, enum Storage reg, int reg_num)
{
    char reg_name[3];
    register_name(reg, reg_num, reg_name);
    fprintf(stdout, "lw $%s, %d($fp)\n", reg_name, loc);
}

void exec_binop(Node t,
                enum Storage rst_reg, int rst_reg_num,
                enum Storage opa_reg, int opa_reg_num,
                enum Storage opb_reg, int opb_reg_num)
{
    char opa_reg_name[3];
    char opb_reg_name[3];
    char rst_reg_name[3];
    register_name(opa_reg, opa_reg_num, opa_reg_name);
    register_name(opb_reg, opb_reg_num, opb_reg_name);
    register_name(rst_reg, rst_reg_num, rst_reg_name);

    switch(t->value.op)
    {
    case PLUS:
        fprintf(stdout,"addu $%s, $%s, $%s\n", rst_reg_name, opa_reg_name, opb_reg_name);
        break;
    default:
        break;
    }
}

