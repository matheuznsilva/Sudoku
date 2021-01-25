main:	main.o	funcoes.o	jogo.o
	gcc main.o funcoes.o jogo.o -o main

main.o:	main.c
	gcc -c main.c

funcoes.o:	funcoes.c	funcoes.h
	gcc -c funcoes.c

jogo.o:	jogo.c	jogo.h
	gcc -c jogo.c

clean:
	rm *.o
