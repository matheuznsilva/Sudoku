#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "jogo.h"
#include "colors.h"
#define MAX 50
#define T 10


void modo_de_jogo(){
	int a=0, NIVEL, JOGO;
	do{
        foreground(WHITE);
		system("clear");
        printf("\n============== MENU ==============");
        printf("\n| 1 - INICIAR UM JOGO ALEATÓRIO  |"
    	       "\n| 2 - CARREGAR UM JOGO           |"
    	       "\n|                                |"
    	       "\n| 0 - VOLTAR                     |");
        printf("\n==================================\n\n");
        printf("Digite sua escolha: ");
        scanf("%d", &a);
        system("clear");
        if(a != 0){
        	printf("\n============== MENU ==============");
        	printf("\n| 1 - EASY                       |"
    	    	   "\n| 2 - INTERMEDIARY               |"
    	    	   "\n| 3 - HARD                       |"
    	    	   "\n|                                |"
    	    	   "\n| 0 - VOLTAR                     |");
        	printf("\n==================================\n\n");
        	printf("Digite sua escolha: ");
     		scanf("%d", &NIVEL);
        }
        if(NIVEL == 0){
            a = 0;
        }
        switch(a){
            case 1:{
                iniciar_jogo(NIVEL, a);
                break;
            }
            case 2:{
                iniciar_jogo(NIVEL, a);
                break;
            }
            default:{
                break;
            }
        } 
	}while(a!=0);
};

void instrucoes(){
	FILE *arq = fopen("instrucao.txt", "r");
    char c[MAX];
    if(arq == NULL){ 
        printf("Problemas na abertura do arquivo\n");
        printf("Arquivo nao encontrado\n");
    } else {
    	while(fgets(c, MAX, arq) != NULL){
    			printf("%s", c);
    	}
    }
    fclose(arq);
};

void imprimeRecord(){
    struct info record[T];
    int HORA, MIN, SEG;
	FILE *arq = fopen("recorde.txt", "r");

    if(arq == NULL){ 
        printf("Problemas na abertura do arquivo\n");
        printf("Arquivo nao encontrado\n");
    } else {
        for(int i=0; i<T; i++){   
            fscanf(arq, "%s", &record[i].nome); 
            fscanf(arq, "%d", &record[i].tempo);
        }
    }
    printf("+=================================+\n"
           "                                   \n"
           "              RECORDE              \n"
           "                                   \n");
    for(int i=0; i<T; i++){
        HORA = 0, MIN = 0, SEG = 0;
        SEG = record[i].tempo;
        if(SEG > 59){
            MIN = SEG / 60;
            SEG = SEG % 60;
            if(MIN > 59){
                HORA = MIN / 60;
                MIN = MIN % 60; 
            }
        }   
        printf("  %s ............. %dh:%dm:%ds  \n", record[i].nome, HORA, MIN, SEG); 
    }
    printf("                                   \n"
           "+=================================+\n");
    fclose(arq);
};

void novo_record(int R){
    struct info record[T];
    int i;
    FILE *arq = fopen("recorde.txt", "r");

    if(arq == NULL){ 
        printf("Problemas na abertura do arquivo\n");
        printf("Arquivo nao encontrado\n");
    } else {
        for(i=0; i<T; i++){   
            fscanf(arq, "%s", &record[i].nome); 
            fscanf(arq, "%d", &record[i].tempo);
        }

        fclose(arq);

        i=T-1;
        do{
            printf("teste\n");
            if(R < record[i].tempo){
                printf("\n\t\tPARABENS NOVO RECORD\nDIGITE O SEU PRIMEIRO NOME");
                printf("\nNOME: ");
                setbuf(stdin, NULL);
                fgets(record[i].nome, MAX, stdin);
                record[i].tempo = R;
                break;
            }
            i--;
        }while(i>0);

        arq = fopen("recorde.txt", "w");
        
        for(i=0; i<T; i++){
            fputs(record[i].nome, arq);
            //fprintf(arq, "%s ", record[i].nome);       
            fprintf(arq, "%d\n", record[i].tempo);       
       }
        imprimeRecord();
        coordenadas();  
    }
    fclose(arq);
}
