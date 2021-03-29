#include <stdio.h>
#include <stdlib.h>
#include "transposition_consistant.h"
double* transposition(double** matrix, int size_n, int size_m) {
    printf("Hello from naive\n");
    double *transposition_matrix = (double*)malloc(size_n * size_m * sizeof(double*));
    for (int i = 0; i < size_n; i++) {
        for (int j = 0; j < size_m; j++) {
            transposition_matrix[i + size_m * j] = matrix[i][j];
        }
    }
    return transposition_matrix;
}