#include "globals.h"

const char* enum_to_string(enum Token t)
{
#define WRAP(x) \
    case x:     \
        return #x;
    switch (t) {
        TOKENS
    }
#undef WRAP
    return "Unknown";
}
