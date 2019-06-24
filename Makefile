all:
	flex lex.l
	bison -Wall -rall parser.y
	gcc -Wall -Wextra -std=c99 -o project4_16 main.c scan.c util.c lex.yy.c parser.tab.c symtab.c analyze.c code.c cgen.c

clean:
	rm ./project4_16
	rm ./lex.yy.c
	rm ./lex.yy.h
	rm ./parser.tab.c
	rm ./parser.tab.h
	rm ./parser.output

