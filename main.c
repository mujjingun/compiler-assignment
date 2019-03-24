#include <stdio.h>

#include "globals.h"
#include "lex.yy.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage: %s <program.c>\n", argv[0]);
        return 0;
    }

    for (int i = 1; i < argc; ++i) {

        FILE* fp;
        if ((fp = fopen(argv[i], "r")) == NULL) {
            fprintf(stderr, "Error: Cannot open file \"%s\"\n", argv[i]);
            return 1;
        }

        if (argc > 2) {
            // print file name
            printf("%s:\n", argv[i]);
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

        fclose(fp);
    }

    return 0;
}
