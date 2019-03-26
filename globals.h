#ifndef GLOBALS_H
#define GLOBALS_H

#define TOKENS          \
    WRAP(ENDOFFILE)     \
    WRAP(ERROR)         \
    WRAP(IF)            \
    WRAP(ELSE)          \
    WRAP(INT)           \
    WRAP(RETURN)        \
    WRAP(VOID)          \
    WRAP(WHILE)         \
    WRAP(PLUS)          \
    WRAP(MINUS)         \
    WRAP(MULTIPLY)      \
    WRAP(DIVIDE)        \
    WRAP(LESSTHAN)      \
    WRAP(LESSTHANEQ)    \
    WRAP(GREATERTHAN)   \
    WRAP(GREATERTHANEQ) \
    WRAP(EQUAL)         \
    WRAP(NOTEQUAL)      \
    WRAP(ASSIGN)        \
    WRAP(SEMICOLON)     \
    WRAP(COMMA)         \
    WRAP(LPAREN)        \
    WRAP(RPAREN)        \
    WRAP(LBRACKET)      \
    WRAP(RBRACKET)      \
    WRAP(LBRACE)        \
    WRAP(RBRACE)        \
    WRAP(ID)            \
    WRAP(NUM)

enum Token {
#define WRAP(x) x,
    TOKENS
#undef WRAP
};

const char* enum_to_string(enum Token t);

struct Scanner {
    void* flex;
    const char* error_msg;
};

#endif // GLOBALS_H
