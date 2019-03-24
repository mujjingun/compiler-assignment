all:
	flex tiny.l
	gcc -o compiler main.c utils.c ./lex.yy.c

test: all
	./compiler

clean:
	rm ./compiler
	rm ./lex.yy.c
	rm ./lex.yy.h
