all:
	flex lex.l
	bison -Wall -rall parser.y
	gcc -Wall -Wextra -std=c99 -o project3_16 main.c scan.c util.c lex.yy.c parser.tab.c symtab.c analyze.c

test: all
	./project3_16 test_files/test1.tny test_files/test2.tny test_files/test3.tny test_files/test4.tny

clean:
	rm ./project3_16
	rm ./lex.yy.c
	rm ./lex.yy.h
	rm ./parser.tab.c
	rm ./parser.tab.h
	rm ./parser.output

