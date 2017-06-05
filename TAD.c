#include "TAD.h"
#include <stdio.h>
#include <stdlib.h>

//Aloca dinâmicamente uma matriz
double **Allocate(int d) {
	int i;
	double **A;
	A = (double**) calloc(d , sizeof (double));
	for(i = 0; i < d; i++) {
		A[i] = (double*) calloc(d , sizeof (double));
	}
	return A;
}

//Transforma uma linha nula em uma linha composta apenas por 1
//Recebe a linha de uma matriz e seu tamanho, passa por seus elementos, atribuindo 1
void ZeroToOne(double *A, int d) {
	int i;
	for(i = 0; i < d; i++) {
		A[i] = 1;
	}
}

//Verifica se existem (e quais são as) linha nulas
//Verifica se todos os elementos de uma linha são 0. Se a contagem de elementos nulos for igual ao tamanho da matriz, chama a funcão de substituicão de 0 por 1.
void IsItZero(double **A, int d) {
	int i, j, count;
	for(i = 0; i < d; i++) {
		count = 0;
		for(j = 0; j < d; j++) {
			if(A[i][j] != 0) {
				break;
			}
			else {
				count++;
			}
		}
		if(count == d) {
			ZeroToOne(A[i], d);
		}		
	}
}

//As duas funcões abaixo transformam uma matriz qualquer em uma matriz estocástica
//Divide o total somado pelo número de elementos não nulos, atingindo o total de 1 por soma de elementos da linha
void StochasticMatrixPartTwo(double *A, int d, int count) {
	int i;
	for(i = 0; i < d; i++) {
		A[i] = A[i] / count;
	}
}
//Conta quantos 1 estão presentes em uma linha e chama a parte dois da funcão
void StochasticMatrix(double **A, int d) {
	int i, j, count;
	for(i = 0; i < d; i++) {
		count = 0;
		for(j = 0; j < d; j++) {
			count += A[i][j];
		}
		StochasticMatrixPartTwo(A[i], d, count);
	}
}

//Adiciona o Damping Factor ã matriz estocástica
//Utiliza a fórmula descrita na especificação do trabalho prático
void MatrixM(double **A, int d, double alpha) {
	int i, j;
	for(i = 0; i < d; i++) {
		for(j = 0; j < d; j++) {
			A[i][j] = (1 - alpha) * A[i][j] + alpha/d;
		}
	}
}

//Imprime a saída
//Primeiro o número da coluna (representando uma página), seguido por sua importância, com quatro casas decimais
void PrintAnswer(double **A, int d) {
	int i;
	for (i = 0; i < d; i++){
		printf("%d %.4lf ", i, A[0][i]);
		printf("\n");
	}
}

//Multiplica a matriz por ela mesma até que ela convirja
double MatrixMultiplication(double **A, int d) {
	int i, j, k;
	double **B, **C;
	double sum = 0, norm = 0;
	//Aloca outras duas matrizes auxiliares
	B = Allocate(d);
	C = Allocate(d);
	//Faz B = A²
	for(i = 0; i < d; i++) {
		for(j = 0; j < d; j++) {
			sum = 0;
			for(k = 0; k < d; k++) {
				sum = sum + A[i][k] * A[k][j];
			}
			B[i][j] = sum;
		}
	}
	//Faz C = B - A e a norma de C
	for(i = 0; i < d; i++) {
		for(j = 0; j < d; j++) {
			C[i][j] = B[i][j] - A[i][j];
			norm += C[i][j] * C[i][j];
		}
	}
	//Checa se a matriz já convergiu, comparando sua norma com 10⁻¹²
	if(norm <= 0.000000000001) {
		PrintAnswer(B, d);
		FreeMatrix(B, d);
		FreeMatrix(C, d);
		return 0;
	}
	//Caso não tenha convergido, retorna a própria funcão recursivamente
	else {
		MatrixMultiplication(B, d);
		FreeMatrix(B, d);
		FreeMatrix(C, d);
		return 0;
	}
}

//Libera a memória alocada dinâmicamente
void FreeMatrix(double **A, int d) {
	int i;
	for(i = 0; i < d; i++) {
		free(A[i]);
	}
	free(A);
}