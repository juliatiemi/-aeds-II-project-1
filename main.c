#include "TAD.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	int dimension;
	int row, column;
	double alpha;
	double **matrix;

	scanf("%d %lf", &dimension, &alpha);

	matrix = Allocate(dimension);
	while(scanf("%d %d", &row, &column) != EOF) {
		matrix[row][column] = 1;
	}

	IsItZero(matrix, dimension);

	StochasticMatrix(matrix, dimension);

	MatrixM(matrix, dimension, alpha);

	MatrixMultiplication(matrix, dimension);

	FreeMatrix(matrix, dimension);
	return 0;
}

	