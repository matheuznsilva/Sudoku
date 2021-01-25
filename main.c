#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#include "jogo.h"
#include "colors.h"

int main(){
	int a=0, tecla;
    printf("\n\t\t\tBEM VINDO AO SUDOKU\n\n");
    sleep(1);
    do{
        system("clear");
        printf("\n============= MENU =============");
        printf("\n| 1 - INICIAR UM JOGO          |"
    	       "\n| 2 - INSTRUÇÕES               |"
    	       "\n| 3 - RECORDE                  |"
    	       "\n|                              |"
    	       "\n| 0 - SAIR                     |");
        printf("\n================================\n\n");
        printf("Digite sua escolha: ");
        scanf("%d", &a);
        system("clear");

        switch(a){
            case 1:{ 
                modo_de_jogo();
                break;
            }
            case 2:{
                instrucoes();
                printf("\n\nDIGITE ENTER PARA VOLTAR ");
                setbuf(stdin,NULL);
                coordenadas();
                break;
            }
            case 3:{
                imprimeRecord();
                printf("\n\n DIGITE ENTER PARA VOLTAR ");
                setbuf(stdin,NULL);
                coordenadas();
            }
            default:{
                break;
            }
        } 
    }while(a!=0);
    system("clear");
    return 0;
}

