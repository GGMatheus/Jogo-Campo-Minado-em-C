#include <stdio.h>
#include <stdlib.h>
#include "EP3utils.h"
#define true 1
#define false 0


int adjacentExists(int x, int y, int x_i, int y_i, int h, int w) {
	int x_a = x + x_i;
	int y_a = y + y_i;
	return (x_a >= 0) && (x_a < w) && (y_a >= 0) && (y_a < h) && ((x_i != 0) || (y_i != 0));
}


int markerCount(int h, int w, char mBoard[h][w]){
	int count = 0;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (mBoard[i][j] == '*') {
				count++;
			}
		}
	}
	return count;
}


int freeCount(int h, int w, char mBoard[h][w]){
	int count = 0;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (mBoard[i][j] != ' ') {
				count++;
			}
		}
	}
	return count;
}


int mineCount(int h, int w, int mMines[h][w]){
	int count = 0;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (mMines[i][j] == -1) {
				count++;
			}
		}
	}
	return count;
}


int markPosition(int h, int w, char mBoard[h][w], int x, int y, int mines) {

	if (mBoard[x][y] == '*') return 0;
	else if (mBoard[x][y] == ' ') return 0;
	else if (markerCount(h, w, mBoard) == mines) return 0;
	else {
		mBoard[x][y] = '*';
		return 1;
	}
}


int unmarkPosition(int h, int w, char mBoard[h][w], int x, int y) {

	if (mBoard[x][y] == '.') return 0;
	else if (mBoard[x][y] == ' ') return 0;
	else {
		mBoard[x][y] = '.';
		return 1;
	}
}


int openPosition(int h, int w, int mMines[h][w], char mBoard[h][w], int x, int y) {

	if (mMines[x][y] ==  -1) {
		// perdeu o jogo
		return 0;
	}
	else if (mBoard[x][y] != '.') {
		// caminho já aberto
		return 1;
	}
	else {
		int x_i, y_i, r;
		// abre caminho
		mBoard[x][y] = ' ';
		// verificação dos pontos adjacentes
		if (mMines[x][y] == 0) {
			for (x_i = -1; x_i < 2; x_i++) {
				for (y_i = -1; y_i < 2; y_i++) {
					if (adjacentExists(x, y, x_i, y_i, h, w)) openPosition(h, w, mMines, mBoard, x + x_i, y + y_i);
				}
			}
			
		}
		return 1;					
	}
}


void printHeader(int w) {

	int i;

	printf("       ");
	for (i = 0; i < w; i++) printf("%-3d", i + 1);
	printf("\n    +--");
	for (i = 0; i < w; i++) printf("---");
	printf("+");
}


void printFooter(int w) {

	int i;

	printf("\n    +--");
	for (i = 0; i < w; i++) printf("---");
	printf("+\n       ");
	for (i = 0; i < w; i++) printf("%-3d", i + 1);
}


void printBoard(int w, int h, int mMines[h][w], char mBoard[h][w], int mode) {

	// modes:
	// 0 -> não imprime nenhuma mensagem
	// 1 -> imprime mensagem padrão
	// 2 -> imprime mensagem de "game over"
	// 3 -> imprime mensagem de "venceu o jogo"

	if (mode == 1) {
		printf("Por enquanto: %d/%d marcadas, %d livres.\n", 
			   markerCount(w, h, mBoard), 
			   mineCount(w, h, mMines),
			   freeCount(w, h, mBoard));
	}
	else if (mode == 2) {
		printf("BOOOOM! Voce acaba de pisar numa mina!\n");
	}
	else if (mode == 3) {
		printf("Parabens! Voce encontrou todas as minas!\n");
	}

	printHeader(w);

	for (int i = 0; i < w; i++) {
		printf("\n  %-2d|  ", i + 1);
		for (int j = 0; j < h; j++) {
			if (mode > 1) {
				if (mMines[i][j] == -1) printf("%c  ", mode == 2? '@': '*');
				else printf("%-3d", mMines[i][j]);
			}
			else {
				if (mBoard[i][j] == ' ') printf("%-3d", mMines[i][j]); // space means position is open
				else printf("%-3c", mBoard[i][j]);
			}
		}
		printf("|%2d", i + 1);
	}

	printFooter(w);
	printf("\n\n");
}


int isMatrixEqual(int w, int h, char matrix1[h][w], char matrix2[h][w]) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (matrix1[i][j] != matrix2[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}


void calculateMinesMatrix(int w, int h, int mMines[h][w]) {

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {

			int adjacentMines = 0;

			if (mMines[i][j] == -1) continue; // skip mines

			for (int x_i = -1; x_i < 2; x_i++) {
				for (int y_i = -1; y_i < 2; y_i++) {
					if ((adjacentExists(i, j, x_i, y_i, h, w)) && (mMines[i + x_i][j + y_i] == -1)) adjacentMines++;
				}
			}

			mMines[i][j] = adjacentMines;
		}
	}
}

void printMatrix(int w, int h, char mMatrix[h][w]) {

	for (int i = 0; i < h; i++) {
		printf("\n");
		for (int j = 0; j < w; j++) {
			printf("%-3c", mMatrix[i][j]);
		}
	}
	printf("\n");
}


void populateMines(int w, int h, int mMines[h][w], int x_i, int y_i, int z) {

	while (mineCount(w, h, mMines) < z) {
		int numero = rand();
		int i = numero % w + 1;
        int j = (numero / w) % h + 1;
        if ((i != x_i) && (j != y_i)) {
        	mMines[i][j] = -1;
        }
	}
}

void initializeBoard(int w, int h, char mBoard[h][w]) {

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			mBoard[i][j] = '.';
		}
	}
}