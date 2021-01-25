#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"
#include "jogo.h"
#include "colors.h"
#define TAM 9
#define MAXIMO 3

void iniciar_jogo(int NIVEL, int A){
	int AUX, CORRIGIR = 0, INICIO = 0, FIM = 0, VALOR[MAXIMO], LINHA, COLUNA, TAB[TAM][TAM], TAB1[TAM][TAM], TAB2[TAM][TAM];

	inicializarTabuleiro(TAB, TAB1, TAB2, NIVEL, A);
	
	INICIO = (int)time(NULL);

	do{
		imprimir(TAB);
		AUX = pegarValores(VALOR, TAB);
		if(AUX == 1){
			confere(TAB, TAB1, TAB2, VALOR);

			if(compara(TAB, TAB1) == 0){
				CORRIGIR = 1;
			}
		} else{
			break;
		}
	}while(CORRIGIR != 1);

	FIM = (int)time(NULL);

	if(AUX != 0){
		novo_record(FIM - INICIO);
    	coordenadas();
	}
}

void inicializarTabuleiro(int TAB[][TAM], int TAB1[][TAM], int TAB2[][TAM], int NIVEL, int A){
	int LINHA, COLUNA, NUM, I, J, ALEAT;
	FILE *arq = NULL;
	if(A == 1){
		srand(time(NULL));
		ALEAT = rand()&100;
		
		if(ALEAT%2 == 0){
			arq = fopen("sudoku1.txt", "r");
		} else if(ALEAT%3 == 0){
			arq = fopen("sudoku2.txt", "r");
		} else if(ALEAT%5 == 0){
			arq = fopen("sudoku3.txt", "r");
		} else{
			arq = fopen("sudoku4.txt", "r");
		}
	} else if(A == 2){
		arq = fopen("meu_jogo.txt", "r");
	} else {
		printf("MODO DE JOGO NÃO EXISTENTE\n");
	}
	
	if(arq == NULL){
		printf("Problemas na abertura do arquivo\n");
        printf("Arquivo nao encontrado\n");
    } else {
    	for(LINHA=0; LINHA<TAM; LINHA++){
         	for(COLUNA=0; COLUNA<TAM; COLUNA++){
             	fscanf(arq, "%d", &TAB[LINHA][COLUNA]);
             	TAB2[LINHA][COLUNA] = TAB1[LINHA][COLUNA] = TAB[LINHA][COLUNA];  	
        	}    
		}
		if(NIVEL == 1){
			srand(time(NULL));
			for(NUM=0; NUM<20; NUM++){
				I=rand()%9;
				J=rand()%9;
				TAB2[I][J] = TAB[I][J]= -1;
			}
		} else if(NIVEL == 2){	srand(time(NULL));
			for(NUM=0; NUM<45; NUM++){
				I=rand()%9;
				J=rand()%9;
				TAB2[I][J] = TAB[I][J]= -1;
			}
		} else if(NIVEL == 3){	srand(time(NULL));
			for(NUM=0; NUM<68; NUM++){
				I=rand()%9;
				J=rand()%9;
				TAB2[I][J] = TAB[I][J]= -1;
			}
		}

	}
	fclose(arq);
}

int pegarValores(int VALOR[MAXIMO], int TAB[][TAM]){
   	int AUX = 0;

    do{
    	system("clear");
    	imprimir(TAB);
    	printf("DIGITE A LINHA: ");

    	VALOR[0] = coordenadas();

    	if(VALOR[0] == 48){
    		return 0;
    	}

    	if(VALOR[0] > 96 && VALOR[0] <122){
			VALOR[0] -= 32;
		}

		VALOR[0] -= 65;

    	if (VALOR[0]<0 || VALOR[0]>TAM){
        	printf("\nLINHA INEXISTENTE! DIGITE UMA LETRA DE A a I OU 0 PARA SAIR\n");
    	} else{
    		break;
    	}
    }while(AUX != 1);

    do{
    	system("clear");
    	imprimir(TAB);
    	printf("DIGITE A COLUNA: ");

    	VALOR[1] = coordenadas();

    	if(VALOR[1] == 48){
    		return 0;
    	}

    	if(VALOR[1] > 96 && VALOR[1] <122){
			VALOR[1] -= 32;
		}

		VALOR[1] -= 65;

    	if (VALOR[1]<0 || VALOR[1]>TAM){
        	printf("\nCOLUNA INEXISTENTE! DIGITE UMA LETRA DE A a I OU 0 PARA SAIR\n");
    	} else{
    		break;
    	}
    }while(AUX != 1);

    do{
    	system("clear");
    	imprimir(TAB);
    	printf("DIGITE O VALOR: ");
    	scanf("%d",&VALOR[2]);

    	if (VALOR[2]<-1 || VALOR[2]>TAM){
        	printf("\nVALOR DIGITADO É INVALIDO DIGITE UMA LETRA DE A a I OU 0 PARA SAIR\n");
    	} else if(VALOR[2] == 0){
    		return 0;
    	} else{
    		break;
    	}
    }while(AUX != 1);
    return 1;
}


void confere(int TAB[][TAM], int TAB1[][TAM], int TAB2[][TAM], int VALOR[MAXIMO]){
	int LINHA = VALOR[0], COLUNA = VALOR[1], AUX = VALOR[2];
	if(TAB2[LINHA][COLUNA] == -1){
		TAB[LINHA][COLUNA] = AUX;
		if(TAB[LINHA][COLUNA] == TAB1[LINHA][COLUNA]){
			foreground(GREEN);
		} else {
			foreground(RED);
		}
	}
}

int compara(int TAB[][TAM], int TAB1[][TAM]){
	int LINHA, COLUNA, AUX = 0;
	for(LINHA = 0; LINHA < TAM; LINHA++){
		for(COLUNA = 0; COLUNA < TAM; COLUNA++){
			if(TAB[LINHA][COLUNA]==TAB1[LINHA][COLUNA]){
				AUX++;
			}
		}
	}
	if(AUX == 81){
    	system("clear");
    	printf("PARABENS JOGO COMPLETADO COM SUCESSO!!! =D");
		return 0;
	}
	return 1;
}

int coordenadas(){
	char A[1];
	gets(A);
    setbuf(stdin,NULL);
	return A[0];
}

void imprimir(int TAB[][TAM]){
	system("clear");
	printf("\n| A | B | C | D | E | F | G | H | I |");
	printf("\n+===+===+===+===+===+===+===+===+===+ ===\n"); 
	for(int LINHA=0; LINHA<TAM; LINHA++){
        for(int COLUNA=0; COLUNA<TAM; COLUNA++){
        	if(TAB[LINHA][COLUNA] != -1){
          		printf("| %d ", TAB[LINHA][COLUNA]);
        	} else{
          		printf("|   ");
        	}
        }
        if(LINHA == 8){
        	printf("|  %c\n+===+===+===+===+===+===+===+===+===+ ===\n", LINHA+65);
        } else{   
        	printf("|  %c\n+---+---+---+---+---+---+---+---+---+ ===\n", LINHA+65);    
        }
	}
}