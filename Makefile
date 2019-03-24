all:
	flex tiny.l
	gcc -o compiler main.c utils.c lex.yy.c

test: all
	./compiler test_files/test1.tny
	./compiler test_files/test2.tny

clean:
	rm ./compiler
	rm ./lex.yy.c
	rm ./lex.yy.h
