#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "EP3utils.h"

#define false 0
#define true 1



int main(int argc, char const *argv[]) {


	printf("Running unit tests:\n");

	// +-------------------------+
	// |  Testes adjacentExists  |
	// +-------------------------+

	// teste "caminho feliz"
	assert(adjacentExists(2, 3, -1, -1, 5, 5) == true);

	// teste skip x_i e y_i = 0
	assert(adjacentExists(2, 3, 0, 0, 5, 5) == false);

	// teste fora da borda pra baixo, x
	assert(adjacentExists(0, 0, -1, 1, 5, 5) == false);

	// teste fora da borda pra baixo, y
	assert(adjacentExists(0, 0, 1, -1, 5, 5) == false);

	// teste fora da borda pra cima, x
	assert(adjacentExists(4, 3, 1, 1, 5, 5) == false);

	// teste fora da borda pra cima, y
	assert(adjacentExists(3, 4, 1, 1, 5, 5) == false);

	
	printf("\t>> adjacentExists tests passed. \n");

	// +-----------------------+
	// |  Testes openPosition  |
	// +-----------------------+

	// teste simples: abrir ponto adjacente a minas

	char mBoard_1[5][5] = {
		{'.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.'}
	};
	int mMines_1[5][5] = {
		{ 1,  1,  0,  0,  0},
		{-1,  2,  0,  1,  1},
		{-1,  2,  1,  2, -1},
		{ 2,  2,  2, -1,  2},
		{ 1, -1,  2,  1,  1},
	};
	char mBoardResult_1[5][5] = {
		{'.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.'},
		{'.', '.', ' ', '.', '.'},
		{'.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.'}
	};

	openPosition(5, 5, mMines_1, mBoard_1, 2, 2);
	assert(isMatrixEqual(5, 5, mBoard_1, mBoardResult_1));

	// teste recursivo: abrir ponto não-adjacente a minas (recursivo)
	char mBoard_2[5][5] = {
		{'.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.'}
	};
	char mBoardResult_2[5][5] = {
		{'.', ' ', ' ', ' ', ' '},
		{'.', ' ', ' ', ' ', ' '},
		{'.', ' ', ' ', ' ', '.'},
		{'.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.'}
	};

	openPosition(5, 5, mMines_1, mBoard_2, 1, 2);
	assert(isMatrixEqual(5, 5, mBoard_2, mBoardResult_2));


	printf("\t>> openPosition tests passed. \n");

	// +---------------------+
	// |  Testes printBoard  |
	// +---------------------+

	int mMines_3[5][5] = {
		{ 1,  1,  0,  0,  0},
		{-1,  2,  0,  1,  1},
		{-1,  2,  1,  2, -1},
		{ 2,  2,  2, -1,  2},
		{ 1, -1,  2,  1,  1},
	};

	char mBoard_3[5][5] = {
		{'.', ' ', ' ', ' ', ' '},
		{'.', ' ', ' ', ' ', ' '},
		{'.', ' ', ' ', ' ', '.'},
		{'.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.'}
	};

	printBoard(5, 5, mMines_3, mBoard_3, 0);
	printBoard(5, 5, mMines_3, mBoard_3, 1);

	printf("\t>> printBoard tests passed. \n");

	// +------------------------------+
	// |  Testes calculateMinesMatrix |
	// +------------------------------+

	int mMines_4[5][5] = {
		{ 0,  0,  0,  0,  0},
		{-1,  0,  0,  0,  0},
		{-1,  0,  0,  0, -1},
		{ 0,  0,  0, -1,  0},
		{ 0, -1,  0,  0,  0},
	};

	calculateMinesMatrix(5, 5, mMines_4);
	assert(isMatrixEqual(5, 5, mMines_3, mMines_4));

	return 0;
}