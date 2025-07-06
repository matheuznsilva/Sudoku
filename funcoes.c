#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "jogo.h" // Inclui jogo.h para ter acesso às funções de jogo
#include "colors.h"

// Constante para o número de recordes a serem armazenados
#define NUM_RECORDE_MAX 10

// Função auxiliar para limpar o buffer do teclado
void limpar_buffer_teclado()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
}

void menu_modo_de_jogo()
{
	int escolha_menu_principal = 0;
	int nivel_dificuldade = 0;

	do
	{
		system("clear");
		foreground(WHITE);

		printf("\n============== MENU ==============");
		printf("\n| 1 - INICIAR UM JOGO ALEATÓRIO  |");
		printf("\n| 2 - CARREGAR UM JOGO           |");
		printf("\n|                                |");
		printf("\n| 0 - VOLTAR                     |");
		printf("\n==================================\n\n");
		printf("Digite sua escolha: ");

		if (scanf("%d", &escolha_menu_principal) != 1)
		{
			printf("Entrada inválida. Digite um número.\n");
			limpar_buffer_teclado();
			continue;
		}
		limpar_buffer_teclado();

		system("clear");

		if (escolha_menu_principal != 0)
		{
			printf("\n============== MENU ==============");
			printf("\n| 1 - FÁCIL                      |");
			printf("\n| 2 - INTERMEDIÁRIO              |");
			printf("\n| 3 - DIFÍCIL                    |");
			printf("\n|                                |");
			printf("\n| 0 - VOLTAR                     |");
			printf("\n==================================\n\n");
			printf("Digite sua escolha: ");

			if (scanf("%d", &nivel_dificuldade) != 1)
			{
				printf("Entrada inválida. Digite um número.\n");
				limpar_buffer_teclado();
				continue;
			}
			limpar_buffer_teclado();
		}

		if (nivel_dificuldade == 0)
		{
			escolha_menu_principal = 0;
		}

		switch (escolha_menu_principal)
		{
		case 1:
		{
			// CORRIGIDO AQUI:
			iniciar_novo_ou_carregar_jogo(nivel_dificuldade, escolha_menu_principal); // Inicia jogo aleatório
			break;
		}
		case 2:
		{
			// CORRIGIDO AQUI:
			iniciar_novo_ou_carregar_jogo(nivel_dificuldade, escolha_menu_principal); // Carrega jogo
			break;
		}
		case 0:
		{
			break;
		}
		default:
		{
			printf("Opção inválida. Tente novamente.\n");
			break;
		}
		}
		RESETALL;
	} while (escolha_menu_principal != 0);
}

void exibir_instrucoes()
{
	FILE *arquivo_instrucoes = fopen("instrucao.txt", "r");
	char linha[MAX_NOME_RECORDE]; // Usando MAX_NOME_RECORDE como buffer, pode ser renomeado para algo mais geral

	if (arquivo_instrucoes == NULL)
	{
		printf("Erro: Problemas na abertura do arquivo de instruções.\n");
		printf("Verifique se 'instrucao.txt' existe no mesmo diretório do executável.\n");
	}
	else
	{
		while (fgets(linha, MAX_NOME_RECORDE, arquivo_instrucoes) != NULL)
		{
			printf("%s", linha);
		}
		fclose(arquivo_instrucoes);
	}
}

void exibir_recordes()
{
	RecordeJogo recordes[NUM_RECORDE_MAX];
	FILE *arquivo_recordes = fopen("recorde.txt", "r");
	int hora, minuto, segundo;

	if (arquivo_recordes == NULL)
	{
		printf("Erro: Problemas na abertura do arquivo de recordes.\n");
		printf("Verifique se 'recorde.txt' existe ou crie um novo.\n");
		// Opcional: Criar um arquivo de recordes vazio se não existir
		// arquivo_recordes = fopen("recorde.txt", "w");
		// if (arquivo_recordes != NULL) fclose(arquivo_recordes);
		// return;
	}
	else
	{
		for (int i = 0; i < NUM_RECORDE_MAX; i++)
		{
			// Verifica se a leitura foi bem-sucedida para evitar lixo de memória
			if (fscanf(arquivo_recordes, "%49s", recordes[i].nome) != 1)
			{																	 // Limita a leitura para evitar estouro de buffer
				strcpy(recordes[i].nome, "N/A"); // Define um valor padrão
				recordes[i].tempo = 99999;			 // Define um tempo alto para ficar no final da lista
			}
			if (fscanf(arquivo_recordes, "%d", &recordes[i].tempo) != 1)
			{
				recordes[i].tempo = 99999; // Define um tempo alto
			}
		}
		fclose(arquivo_recordes);
	}

	printf("+=================================+\n");
	printf("                                   \n");
	printf("              RECORDE              \n");
	printf("                                   \n");

	for (int i = 0; i < NUM_RECORDE_MAX; i++)
	{
		hora = 0;
		minuto = 0;
		segundo = recordes[i].tempo;

		if (segundo > 59)
		{
			minuto = segundo / 60;
			segundo = segundo % 60;
			if (minuto > 59)
			{
				hora = minuto / 60;
				minuto = minuto % 60;
			}
		}
		printf("  %s ............. %02dh:%02dm:%02ds  \n", recordes[i].nome, hora, minuto, segundo);
	}
	printf("                                   \n");
	printf("+=================================+\n");
}

void adicionar_novo_recorde(int tempo_jogo)
{
	RecordeJogo recordes[NUM_RECORDE_MAX];
	FILE *arquivo_recordes = fopen("recorde.txt", "r");
	int i;

	// Carrega os recordes existentes
	if (arquivo_recordes == NULL)
	{
		printf("Aviso: Arquivo de recordes não encontrado. Criando um novo.\n");
		// Preenche com valores padrão se o arquivo não existe
		for (i = 0; i < NUM_RECORDE_MAX; i++)
		{
			strcpy(recordes[i].nome, "----------"); // Nome padrão
			recordes[i].tempo = 999999;							// Tempo alto para ser facilmente substituído
		}
	}
	else
	{
		for (i = 0; i < NUM_RECORDE_MAX; i++)
		{
			if (fscanf(arquivo_recordes, "%49s", recordes[i].nome) != 1)
			{
				strcpy(recordes[i].nome, "----------");
			}
			if (fscanf(arquivo_recordes, "%d", &recordes[i].tempo) != 1)
			{
				recordes[i].tempo = 999999;
			}
		}
		fclose(arquivo_recordes);
	}

	// Verifica se o tempo atual é um novo recorde
	for (i = NUM_RECORDE_MAX - 1; i >= 0; i--)
	{
		if (tempo_jogo < recordes[i].tempo)
		{
			// Desloca os recordes para abrir espaço para o novo recorde
			if (i < NUM_RECORDE_MAX - 1)
			{
				for (int j = NUM_RECORDE_MAX - 1; j > i; j--)
				{
					recordes[j] = recordes[j - 1];
				}
			}

			printf("\n\t\tPARABÉNS! NOVO RECORDE!\n");
			printf("DIGITE SEU PRIMEIRO NOME (até %d caracteres): ", MAX_NOME_RECORDE - 1);
			// setbuf(stdin, NULL); // Não é recomendado usar setbuf(stdin, NULL)
			fgets(recordes[i].nome, MAX_NOME_RECORDE, stdin);
			recordes[i].nome[strcspn(recordes[i].nome, "\n")] = 0; // Remove o newline character
			recordes[i].tempo = tempo_jogo;
			break; // Sai do loop após encontrar a posição e inserir
		}
	}

	// Abre o arquivo para escrita e salva os recordes atualizados
	arquivo_recordes = fopen("recorde.txt", "w");
	if (arquivo_recordes == NULL)
	{
		printf("Erro: Não foi possível salvar o recorde.\n");
	}
	else
	{
		for (i = 0; i < NUM_RECORDE_MAX; i++)
		{
			fprintf(arquivo_recordes, "%s\n", recordes[i].nome);	// Escreve o nome e quebra de linha
			fprintf(arquivo_recordes, "%d\n", recordes[i].tempo); // Escreve o tempo e quebra de linha
		}
		fclose(arquivo_recordes);
	}

	exibir_recordes();
	// A função coordenadas() parece estar relacionada à leitura de entrada para pausar.
	// Vamos chamar uma função mais genérica aqui para aguardar a entrada do usuário.
	printf("\n\nPressione ENTER para continuar...");
	limpar_buffer_teclado(); // Garante que o ENTER é lido e não interfere na próxima entrada
}