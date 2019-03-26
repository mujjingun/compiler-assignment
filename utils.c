#include "globals.h"

const char* enum_to_string(enum Token t)
{
    switch (t) {
#define WRAP(x) \
    case x:     \
        return #x;
        TOKENS
#undef WRAP
    }
    return "Unknown";
}
