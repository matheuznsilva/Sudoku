#ifndef FUNCOES_H
#define FUNCOES_H

#define MAX_NOME_RECORDE 50 // Renomeado MAX para ser mais descritivo

// Estrutura para armazenar informações de recorde de jogo
typedef struct {
    char nome[MAX_NOME_RECORDE];
    int tempo;
} RecordeJogo; // Renomeado 'info' para 'RecordeJogo'

// Protótipos das funções auxiliares
void menu_modo_de_jogo(); // Renomeado para seguir um padrão de nomeclatura
void exibir_instrucoes(); // Renomeado para ser mais descritivo
void exibir_recordes();   // Renomeado para ser mais descritivo
void adicionar_novo_recorde(int tempo_jogo); // Renomeado para ser mais descritivo e indicar o parâmetro

#endif /* FUNCOES_H */