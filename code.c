#include "code.h"

#include <stdarg.h>

void emitComment(FILE *out, const char *msg, ...)
{
    va_list args;

    fprintf(out, "# ");

    va_start(args, msg);
    vfprintf(out, msg, args);
    va_end(args);

    fprintf(out, "\n");
}
