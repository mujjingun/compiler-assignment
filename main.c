#include <stdio.h>

#include "globals.h"
#include "lex.yy.h"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: %s <program.c>\n", argv[0]);
        return 0;
    }

    FILE* fp;
    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Error: Cannot open file \"%s\"\n", argv[1]);
        return 1;
    }

    struct Scanner scanner;

    // set input stream
    yylex_init(&scanner.flex);
    yyset_in(fp, scanner.flex);
    yyset_extra(&scanner, scanner.flex);

    puts(" line number    token         lexeme    ");
    puts("-----------------------------------------");

    enum Token result;
    do {
        result = yylex(scanner.flex);
        printf("%4d            ", yyget_lineno(scanner.flex));
        printf("%-10s  ", enum_to_string(result));
        if (result == ERROR) {
            printf("%s\n", scanner.error_msg);
        }
        else {
            printf("%s\n", yyget_text(scanner.flex));
        }
    } while (result != ENDOFFILE);

    yylex_destroy(scanner.flex);

    return 0;
}
