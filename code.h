#ifndef CODE_H
#define CODE_H

#include <stdio.h>

#ifdef __GNUC__
__attribute__((__format__(__printf__, 2, 3)))
#endif
void emitComment(FILE* out, const char* msg, ...);

#endif
