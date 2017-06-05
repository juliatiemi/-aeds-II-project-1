#ifndef PAGERANK
#define PAGERANK

//Aloca dinâmicamente uma matriz
double **Allocate(int a);

//Transforma uma linha nula em uma linha composta apenas por 1
void ZeroToOne(double *A, int b);

//Verifica se existem (e quais são as) linha nulas
void IsItZero(double **A, int a);

//As duas funcões abaixo transformam uma matriz qualquer em uma matriz estocástica
void StochasticMatrixPartTwo(double *A, int b, int c);
void StochasticMatrix(double **A, int a);

//Adiciona o Damping Factor ã matriz estocástica
void MatrixM(double **A, int a, double b);

//Imprime a saída
void PrintAnswer(double **A, int a);

//Multiplica a matriz por ela mesma até que ela convirja
double MatrixMultiplication(double **A, int a);

//Libera a memória alocada dinâmicamente
void FreeMatrix(double **A, int a);

#endif