#include <stdio.h>
#include <stdlib.h>
#include "EP3utils.h"
#define MMAX 90
#define NMAX 90




int main(int argc, char const *argv[])
{
	
	int m, n, z, r, semente;
    int i, j, numero, x, y;
    int valendo = 1;
    int monta_matriz;
    int minas_marcadas, minas_a_marcar, minas;
    char mBoard[MMAX][NMAX];
    int mMines[MMAX][NMAX];
    char comando;

    printf("De o numero de linhas do tabuleiro do jogo: ");
    scanf("%d", &m);
    if(m < 3 || MMAX > 90) {
        printf("Redigite o numero de linhas do tabuleiro dentro do intervalo permitido (3 <= m <= 90): ");
        scanf("%d", &m);
    }

    printf("De o numero de colunas do tabuleiro do jogo: ");
    scanf("%d", &n);
    if(n < 3 || n > NMAX) {
        printf("Redigite o numero de colunas do tabuleiro dentro do intervalo permitido (3 <= n <= 90): ");
        scanf("%d", &n);
    }

    printf("De o numero de minas: ");
    scanf("%d", &z);
    if(z < 1 || z > 16) {
        printf("Redigite o numero de minas do tabuleiro dentro do intervalo permitido (1 <= z <= 16): ");
        scanf("%d", &z);
    }

    printf("De a semente: ");
    scanf("%d", &semente);
    if(semente < 1 || semente > 65535) {
        printf("Redigite o numero da semente dentro do intervalo permitido (1 <= s <= 65535): ");
        scanf("%d", &semente);
    }

    printf("Numero de linhas (3 <= m <= 90): %d\n"
            "Numero de colunas (3 <= n <= 90): %d\n"
            "Numero de minas (1 <= z <= 16): %d\n"
            "Semente (1 <= s <= 65535): %d\n"
            "Bem vindo ao BuscaMinas!\n", m, n, z, semente);

    initializeBoard(n, m, mBoard);
    printBoard(n, m, mMines, mBoard, 0);

    srand(semente);
    printf("Proximo chute: ");
    scanf(" %c %d %d", &comando, &x, &y);

    populateMines(n, m, mMines, x - 1, y - 1, z);
    calculateMinesMatrix(n, m, mMines);
    openPosition(n, m, mMines, mBoard, x - 1, y - 1);
	printBoard(n, m, mMines, mBoard, 1);

    while (valendo) {

    	printf("Proximo chute: ");
    	scanf(" %c %d %d", &comando, &x, &y);

    	if ((x > m) || (y > n)) {
    		printf("Sem efeito.\n\n");
    		continue;
    	}

    	int freeCountPrev = freeCount(n, m, mBoard);

    	if ((comando == 'a') || (comando == 'A')) {
    		if (!openPosition(n, m, mMines, mBoard, x - 1, y - 1)) {
    			valendo = 0;
    			printBoard(n, m, mMines, mBoard, 2);
    		}
    		else {
    			if (freeCount(n, m, mBoard) == freeCountPrev) {
    				printf("Sem efeito.\n\n");
    			}
    			else {
    				printBoard(n, m, mMines, mBoard, 1);	
    			}
    		}
    	}
    	else if ((comando == 'm') || (comando == 'M')) {
    		r = markPosition(n, m, mBoard, x - 1, y - 1, z);
    		if (r) {
    			printBoard(n, m, mMines, mBoard, 1);
    		}
    		else {
    			printf("Sem efeito.\n\n");
    		}
    	}
    	else if ((comando == 'd') || (comando == 'D')) {
    		r = unmarkPosition(n, m, mBoard, x - 1, y - 1);
    		if (r) {
    			printBoard(n, m, mMines, mBoard, 1);
    		}
    		else {
    			printf("Sem efeito.\n\n");
    		}
    	}
    	else {
    		printf("Sem efeito.\n\n");
    	}

    	if (freeCount(n, m, mBoard) == mineCount(n, m, mMines)) {
    		// venceu!
    		valendo = 0;
    		printBoard(n, m, mMines, mBoard, 3);
    	}
    }

	return 0;
}