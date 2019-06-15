#include <stdbool.h>
#include <stdio.h>

#include "analyze.h"
#include "globals.h"
#include "lex.yy.h"
#include "scan.h"
#include "symtab.h"
#include "util.h"

void yyerror(yyscan_t scanner, char const* s)
{
    fprintf(stderr, "Parse error(%d): %s\n", yyget_lineno(scanner), s);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage: %s [--ast] [--latex] <source> [<source2> ...]\n", argv[0]);
        return 0;
    }

    bool printLatex = false;
    bool printAst = false;

    int i = 1;
    for (; i < argc; ++i) {
        if (strlen(argv[i]) > 2 && strncmp(argv[i], "--", 2) == 0) {
            if (strcmp(argv[i], "--latex") == 0) {
                printLatex = true;
            } else if (strcmp(argv[i], "--ast") == 0) {
                printAst = true;
            }
        } else {
            break;
        }
    }

    for (; i < argc; ++i) {
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
        } else {

            // Print AST
            if (printLatex) {
                printTreeLatex(scanner.tree);
            } else if (printAst) {
                printTree(scanner.tree);
            }

            // Semantic analysis
            bool error = semanticAnalysis(scanner.tree);

            if (!error) {
                // TODO: Code generation
            }

            freeTree(scanner.tree);
        }

        yylex_destroy(scanner.flex);

        fclose(fp);

        // print newline
        puts("");
    }

    return 0;
}
