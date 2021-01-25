#define TAM 9
#define MAXIMO 3

void iniciar_jogo(int NIVEL, int A);

void inicializarTabuleiro(int TAB[][TAM], int TAB1[][TAM], int TAB2[][TAM], int NIVEL, int A);

int pegarValores(int VALOR[MAXIMO], int TAB[][TAM]);

void confere(int TAB[][TAM], int TAB1[][TAM], int TAB2[][TAM], int VALOR[MAXIMO]);

int compara(int TAB[][TAM], int TAB1[][TAM]);

int coordenadas();

void imprimir(int TAB[][TAM]);