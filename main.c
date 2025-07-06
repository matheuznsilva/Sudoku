#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para sleep()
#include "funcoes.h"
#include "jogo.h"
#include "colors.h"

// Função auxiliar declarada em funcoes.c
extern void limpar_buffer_teclado();

int main() {
    int escolha_menu_principal = 0;
    
    printf("\n\t\t\tBEM VINDO AO SUDOKU\n\n");
    sleep(1); // Pausa de 1 segundo

    do {
        system("clear");
        printf("\n============= MENU PRINCIPAL =============");
        printf("\n| 1 - INICIAR UM JOGO                  |");
        printf("\n| 2 - INSTRUÇÕES                       |");
        printf("\n| 3 - RECORDES                         |");
        printf("\n|                                      |");
        printf("\n| 0 - SAIR                             |");
        printf("\n========================================\n\n");
        printf("Digite sua escolha: ");

        if (scanf("%d", &escolha_menu_principal) != 1) {
            printf("Entrada inválida. Digite um número.\n");
            limpar_buffer_teclado(); // Limpa o buffer
            continue; // Volta para o início do loop
        }
        limpar_buffer_teclado(); // Limpa o buffer após scanf

        system("clear");

        switch (escolha_menu_principal) {
            case 1: {
                menu_modo_de_jogo(); // Chama o menu de seleção de modo de jogo
                break;
            }
            case 2: {
                exibir_instrucoes(); // Exibe as instruções do jogo
                printf("\n\nPressione ENTER para voltar ao menu...");
                limpar_buffer_teclado(); // Aguarda o usuário pressionar ENTER
                break;
            }
            case 3: {
                exibir_recordes(); // Exibe a lista de recordes
                printf("\n\nPressione ENTER para voltar ao menu...");
                limpar_buffer_teclado(); // Aguarda o usuário pressionar ENTER
                break;
            }
            case 0: {
                // Sair do programa
                break;
            }
            default: {
                printf("Opção inválida. Por favor, digite um número entre 0 e 3.\n");
                printf("\nPressione ENTER para continuar...");
                limpar_buffer_teclado(); // Aguarda o usuário pressionar ENTER
                break;
            }
        }
    } while (escolha_menu_principal != 0);

    system("clear");
    printf("\nObrigado por jogar! Até a próxima!\n\n");
    return 0;
}