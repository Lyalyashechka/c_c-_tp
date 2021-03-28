#include <unistd.h>
#include <assert.h>

#include <stdlib.h>
typedef struct argThread {
    int rows_start;
    int rows_end;
    int num_colons;
    double **matrix;
    double **transpose_matrix;
} argMatrix_t;
int transposition_parallel(double** matrix, double** transpose_matrix, int n, int m);
