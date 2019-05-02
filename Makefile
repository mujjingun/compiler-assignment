all:
	flex lex.l
	bison parser.y
	gcc -Wall -Wextra -std=c99 -o 20171634 main.c scan.c util.c lex.yy.c parser.tab.c

test: all
	./20171634 test_files/test1.tny test_files/test2.tny test_files/test3.tny test_files/test4.tny

clean:
	rm ./20171634
	rm ./lex.yy.c
	rm ./lex.yy.h
	rm ./parser.tab.c
	rm ./parser.tab.h
