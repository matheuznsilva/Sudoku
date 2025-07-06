#ifndef JOGO_H
#define JOGO_H

#define TAMANHO_SUDOKU 9
#define MAX_VALORES_ENTRADA 3

void iniciar_novo_ou_carregar_jogo(int nivel_dificuldade, int tipo_jogo);
void inicializar_tabuleiros(int tabuleiro_principal[][TAMANHO_SUDOKU], int tabuleiro_solucao[][TAMANHO_SUDOKU], int tabuleiro_fixo[][TAMANHO_SUDOKU], int nivel_dificuldade, int tipo_jogo);
int obter_valores_entrada(int tabuleiro_principal[][TAMANHO_SUDOKU], int valores_entrada[MAX_VALORES_ENTRADA], int tabuleiro_fixo[][TAMANHO_SUDOKU]);
void verificar_e_aplicar_jogada(int tabuleiro_principal[][TAMANHO_SUDOKU], int tabuleiro_fixo[][TAMANHO_SUDOKU], int valores_entrada[MAX_VALORES_ENTRADA]);
int verificar_vitoria(int tabuleiro_principal[][TAMANHO_SUDOKU], int tabuleiro_solucao[][TAMANHO_SUDOKU]);
int ler_caractere_coordenada();
void imprimir_tabuleiro(int tabuleiro[][TAMANHO_SUDOKU]);

#endif /* JOGO_H */