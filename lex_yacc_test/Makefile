main: main.o mixins.o lex.yy.o grammar.tab.o
	gcc -o main main.o mixins.o lex.yy.o grammar.tab.o

grammar.tab.h grammar.tab.c: grammar.y
	bison -d grammar.y

lex.yy.c: grammar.tab.h
	flex grammar.l

grammar.tab.o: grammar.tab.c
	gcc -c -o grammar.tab.o grammar.tab.c

lex.yy.o: lex.yy.c
	gcc -c -o lex.yy.o lex.yy.c

main.o: grammar.tab.h main.c
	gcc -c -o main.o main.c

mixins.o: mixins.c
	gcc -c -o mixins.o mixins.c

clean:
	rm -rf *.o lex.yy.c grammar.tab.h grammar.tab.c main
