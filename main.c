#include <stdio.h>

#include "globals.h"
#include "lex.yy.h"
#include "scan.h"

void yyerror(yyscan_t scanner, char const* s)
{
    fprintf(stderr, "Parse error(%d): %s\n", yyget_lineno(scanner), s);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage: %s <source> [<source2> ...]\n", argv[0]);
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

        int parse_result = yyparse(scanner.flex);
        if (parse_result != 0) {
            fprintf(stderr, "Error: Parse failed\n");
        }
        else {
            printTree(scanner.tree);
            freeNodeCascade(scanner.tree);
        }

        yylex_destroy(scanner.flex);

        fclose(fp);
    }

    return 0;
}
