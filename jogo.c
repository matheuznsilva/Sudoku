#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h" // Para RecordeJogo, adicionar_novo_recorde, exibir_recordes
#include "jogo.h"
#include "colors.h"

// Define o tamanho do Sudoku e o máximo de valores de entrada, conforme jogo.h
#define TAMANHO_SUDOKU 9
#define MAX_VALORES_ENTRADA 3

// Declaração de função auxiliar (para limpar buffer, se ainda necessário aqui)
extern void limpar_buffer_teclado(); // Declaração para usar a função de funcoes.c

void iniciar_novo_ou_carregar_jogo(int nivel_dificuldade, int tipo_jogo)
{
	int tabuleiro_principal[TAMANHO_SUDOKU][TAMANHO_SUDOKU];
	int tabuleiro_solucao[TAMANHO_SUDOKU][TAMANHO_SUDOKU];
	int tabuleiro_fixo[TAMANHO_SUDOKU][TAMANHO_SUDOKU];
	int valores_jogada[MAX_VALORES_ENTRADA];
	int jogada_valida = 0;
	time_t tempo_inicio, tempo_fim;

	inicializar_tabuleiros(tabuleiro_principal, tabuleiro_solucao, tabuleiro_fixo, nivel_dificuldade, tipo_jogo);

	tempo_inicio = time(NULL);

	do
	{
		imprimir_tabuleiro(tabuleiro_principal); // Imprime o estado atual do tabuleiro

		// MUDANÇA AQUI: Passar tabuleiro_principal como primeiro argumento
		jogada_valida = obter_valores_entrada(tabuleiro_principal, valores_jogada, tabuleiro_fixo);

		if (jogada_valida == 0)
		{
			break;
		}

		verificar_e_aplicar_jogada(tabuleiro_principal, tabuleiro_fixo, valores_jogada);

	} while (verificar_vitoria(tabuleiro_principal, tabuleiro_solucao) != 0); // Loop enquanto o jogo não for completado

	tempo_fim = time(NULL); // Fim da contagem de tempo

	if (jogada_valida != 0)
	{ // Se o jogo foi completado (não saiu)
		adicionar_novo_recorde((int)(tempo_fim - tempo_inicio));
	}

	// Pausa após o jogo, seja por vitória ou saída
	printf("\n\nPressione ENTER para continuar...");
	limpar_buffer_teclado(); // Garante que o ENTER é lido
}

void inicializar_tabuleiros(int tabuleiro_principal[][TAMANHO_SUDOKU], int tabuleiro_solucao[][TAMANHO_SUDOKU], int tabuleiro_fixo[][TAMANHO_SUDOKU], int nivel_dificuldade, int tipo_jogo)
{
	FILE *arquivo_sudoku = NULL;
	int linha, coluna;
	char nome_arquivo[50]; // Buffer para o nome do arquivo

	// Escolhe o arquivo de sudoku baseado no tipo de jogo
	if (tipo_jogo == 1)
	{ // Novo jogo aleatório
		srand(time(NULL));
		int aleatorio = rand() % 100;

		if (aleatorio % 2 == 0)
		{
			strcpy(nome_arquivo, "sudoku1.txt");
		}
		else if (aleatorio % 3 == 0)
		{
			strcpy(nome_arquivo, "sudoku2.txt");
		}
		else if (aleatorio % 5 == 0)
		{
			strcpy(nome_arquivo, "sudoku3.txt");
		}
		else
		{
			strcpy(nome_arquivo, "sudoku4.txt");
		}
	}
	else if (tipo_jogo == 2)
	{ // Carregar jogo
		strcpy(nome_arquivo, "meu_jogo.txt");
	}
	else
	{
		printf("ERRO: Modo de jogo não existente.\n");
		return; // Retorna para evitar tentar abrir um arquivo inválido
	}

	arquivo_sudoku = fopen(nome_arquivo, "r");

	if (arquivo_sudoku == NULL)
	{
		printf("Erro: Problemas na abertura do arquivo de Sudoku '%s'.\n", nome_arquivo);
		printf("Verifique se o arquivo existe no mesmo diretório do executável.\n");
		// Inicializa tabuleiros com zeros para evitar lixo de memória e permitir que o programa continue (mas o jogo será inviável)
		for (linha = 0; linha < TAMANHO_SUDOKU; linha++)
		{
			for (coluna = 0; coluna < TAMANHO_SUDOKU; coluna++)
			{
				tabuleiro_principal[linha][coluna] = 0;
				tabuleiro_solucao[linha][coluna] = 0;
				tabuleiro_fixo[linha][coluna] = 0;
			}
		}
		return;
	}

	// Carrega o tabuleiro do arquivo
	for (linha = 0; linha < TAMANHO_SUDOKU; linha++)
	{
		for (coluna = 0; coluna < TAMANHO_SUDOKU; coluna++)
		{
			if (fscanf(arquivo_sudoku, "%d", &tabuleiro_principal[linha][coluna]) != 1)
			{
				printf("Erro de leitura no arquivo de Sudoku. O arquivo pode estar corrompido.\n");
				fclose(arquivo_sudoku);
				return;
			}
			tabuleiro_solucao[linha][coluna] = tabuleiro_principal[linha][coluna]; // Copia para o tabuleiro solução
			tabuleiro_fixo[linha][coluna] = tabuleiro_principal[linha][coluna];		 // Inicialmente, todos são fixos
		}
	}
	fclose(arquivo_sudoku);

	// Remove células para criar a dificuldade
	int num_celulas_remover = 0;
	if (nivel_dificuldade == 1)
	{ // EASY
		num_celulas_remover = 20;
	}
	else if (nivel_dificuldade == 2)
	{ // INTERMEDIARY
		num_celulas_remover = 45;
	}
	else if (nivel_dificuldade == 3)
	{ // HARD
		num_celulas_remover = 68;
	}
	else
	{
		printf("Nível de dificuldade inválido. Usando nível padrão (INTERMEDIÁRIO).\n");
		num_celulas_remover = 45;
	}

	srand(time(NULL)); // Garante uma nova semente para cada inicialização
	for (int i = 0; i < num_celulas_remover; i++)
	{
		int r_linha = rand() % TAMANHO_SUDOKU;
		int r_coluna = rand() % TAMANHO_SUDOKU;
		tabuleiro_principal[r_linha][r_coluna] = -1; // -1 representa uma célula vazia
		tabuleiro_fixo[r_linha][r_coluna] = -1;			 // Marca como célula não fixa
	}
}

int obter_valores_entrada(int tabuleiro_principal[][TAMANHO_SUDOKU], int valores_entrada[MAX_VALORES_ENTRADA], int tabuleiro_fixo[][TAMANHO_SUDOKU])
{
	int linha_char_ascii, coluna_char_ascii;
	int linha_idx, coluna_idx, valor_digitado;

	// Loop para obter a linha
	do
	{
		system("clear");
		imprimir_tabuleiro(tabuleiro_principal);
		printf("DIGITE A LINHA (A-I) ou 0 para sair: ");
		linha_char_ascii = ler_caractere_coordenada();

		if (linha_char_ascii == '0')
			return 0; // Usuário deseja sair

		linha_idx = linha_char_ascii - 'A';

		if (linha_idx < 0 || linha_idx >= TAMANHO_SUDOKU)
		{
			printf("\nLINHA INEXISTENTE! Digite uma letra de A a I ou 0 para sair.\n");
			limpar_buffer_teclado();
		}
		else
		{
			break;
		}
	} while (1);

	// Loop para obter a coluna
	do
	{
		system("clear");
		imprimir_tabuleiro(tabuleiro_principal);
		printf("LINHA SELECIONADA: %c\n", (char)(linha_idx + 'A'));
		printf("DIGITE A COLUNA (A-I) ou 0 para sair: ");
		coluna_char_ascii = ler_caractere_coordenada();

		if (coluna_char_ascii == '0')
			return 0; // Usuário deseja sair

		coluna_idx = coluna_char_ascii - 'A';

		if (coluna_idx < 0 || coluna_idx >= TAMANHO_SUDOKU)
		{
			printf("\nCOLUNA INEXISTENTE! Digite uma letra de A a I ou 0 para sair.\n");
			limpar_buffer_teclado();
		}
		else
		{
			break;
		}
	} while (1);

	// Loop para obter o valor
	do
	{
		system("clear");
		// MUDANÇA AQUI: imprimir o tabuleiro principal
		imprimir_tabuleiro(tabuleiro_principal);
		printf("LINHA: %c, COLUNA: %c\n", (char)(linha_idx + 'A'), (char)(coluna_idx + 'A'));
		printf("DIGITE O VALOR (1-9) ou 0 para apagar ou -1 para sair: ");

		if (scanf("%d", &valor_digitado) != 1)
		{
			printf("\nVALOR INVÁLIDO! Digite um número de 1 a 9, 0 para apagar, ou -1 para sair.\n");
			limpar_buffer_teclado();
			continue;
		}
		limpar_buffer_teclado();

		if (valor_digitado == -1)
			return 0;

		if (valor_digitado < 0 || valor_digitado > TAMANHO_SUDOKU)
		{
			printf("\nVALOR DIGITADO É INVÁLIDO! Digite um número de 1 a 9, 0 para apagar, ou -1 para sair.\n");
		}
		else
		{
			break;
		}
	} while (1);

	valores_entrada[0] = linha_idx;
	valores_entrada[1] = coluna_idx;
	valores_entrada[2] = valor_digitado;

	return 1;
}

void verificar_e_aplicar_jogada(int tabuleiro_principal[][TAMANHO_SUDOKU], int tabuleiro_fixo[][TAMANHO_SUDOKU], int valores_entrada[MAX_VALORES_ENTRADA])
{
	int linha = valores_entrada[0];
	int coluna = valores_entrada[1];
	int valor = valores_entrada[2];

	if (tabuleiro_fixo[linha][coluna] != -1)
	{
		printf("\nVocê não pode alterar uma célula pré-definida do tabuleiro!\n");
		printf("Pressione ENTER para continuar...");
		limpar_buffer_teclado();
		return;
	}

	if (valor == 0)
	{
		tabuleiro_principal[linha][coluna] = -1;
		return;
	}

	tabuleiro_principal[linha][coluna] = valor;
}

int verificar_vitoria(int tabuleiro_principal[][TAMANHO_SUDOKU], int tabuleiro_solucao[][TAMANHO_SUDOKU])
{
	int linha, coluna;
	for (linha = 0; linha < TAMANHO_SUDOKU; linha++)
	{
		for (coluna = 0; coluna < TAMANHO_SUDOKU; coluna++)
		{
			if (tabuleiro_principal[linha][coluna] != tabuleiro_solucao[linha][coluna])
			{
				return 1; // Jogo ainda não completado
			}
		}
	}
	system("clear");
	printf("\n\t\tPARABÉNS! JOGO COMPLETADO COM SUCESSO!!! =D\n");
	return 0; // Jogo completado
}

int ler_caractere_coordenada()
{
	char entrada_char[10]; // Buffer maior para ler a linha
	if (fgets(entrada_char, sizeof(entrada_char), stdin) == NULL)
	{
		return EOF; // Erro de leitura
	}
	// Remove o newline, se houver
	entrada_char[strcspn(entrada_char, "\n")] = 0;

	if (strlen(entrada_char) == 1)
	{
		char c = entrada_char[0];
		// Converte para maiúscula se for minúscula
		if (c >= 'a' && c <= 'z')
		{
			return c - ('a' - 'A');
		}
		return c; // Retorna o caractere (já maiúsculo ou número)
	}
	return -1; // Indica entrada inválida (mais de um caractere ou vazio)
}

void imprimir_tabuleiro(int tabuleiro[][TAMANHO_SUDOKU])
{
	system("clear");
	printf("\n");
	printf("   A   B   C   D   E   F   G   H   I\n");
	printf(" +---+---+---+---+---+---+---+---+---+\n");

	for (int linha = 0; linha < TAMANHO_SUDOKU; linha++)
	{
		printf("%c|", (char)('A' + linha)); // Imprime a letra da linha
		for (int coluna = 0; coluna < TAMANHO_SUDOKU; coluna++)
		{
			// Verifica a célula em tabuleiro_fixo para saber se é um número inicial
			// Usamos 'tabuleiro_fixo' para decidir a cor original.
			// Para a refatoração completa, 'tabuleiro_fixo' precisa ser passado para esta função.
			// Por simplicidade aqui, vamos apenas imprimir o valor.
			// No entanto, para ter cores diferentes para números fixos e inseridos,
			// ou para números corretos/incorretos, seria necessário passar o tabuleiro_solucao e tabuleiro_fixo.
			// Como isso aumentaria a complexidade da assinatura da função, vamos manter uma versão simplificada
			// e assumir que a coloração é feita em `verificar_e_aplicar_jogada` ou `imprimir_tabuleiro`
			// teria acesso a todos os tabuleiros necessários.

			if (tabuleiro[linha][coluna] != -1)
			{
				// Aqui você pode adicionar lógica para colorir com base na correção
				// Ex: if (tabuleiro[linha][coluna] == tabuleiro_solucao[linha][coluna]) { FOREGREEN; } else { FORERED; }
				// E depois RESETALL;
				printf(" %d ", tabuleiro[linha][coluna]);
			}
			else
			{
				printf("   "); // Célula vazia
			}
			printf("|");
		}
		printf("\n +---+---+---+---+---+---+---+---+---+\n");
	}
	printf("\n"); // Adiciona uma nova linha final para melhor espaçamento
	RESETALL;			// Garante que a cor é resetada após a impressão do tabuleiro
}