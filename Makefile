all:
	flex tiny.l
	$(CC) -o 20171634 main.c utils.c lex.yy.c

test: all
	./compiler test_files/test1.tny
	./compiler test_files/test2.tny

clean:
	rm ./20171634
	rm ./lex.yy.c
	rm ./lex.yy.h
