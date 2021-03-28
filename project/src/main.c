#include <malloc.h>
#include <time.h>
#include "creating_matrix.h"
#include "transposition_consistant.h"
#include "transposition_parallel.h"
int main() {
    srand(time(NULL));
    FILE * file_matrix;
    file_matrix = fopen("../test.txt", "w+");

    int n = 0,
        m = 0;
    scanf("%d %d", &n, &m);

    double **matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) matrix[i] = (double*)malloc(m * sizeof(double));
    double **transpose_matrix = (double**)malloc(m * sizeof(double*));
    for (int i = 0; i < m; i++) transpose_matrix[i] = (double*)malloc(n * sizeof(double));

    int er = create_file_with_random_number_matrix(file_matrix, matrix, n, m);
    er = transposition_parallel(matrix, transpose_matrix, n, m);
    printf("%d \n", er);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", transpose_matrix[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    for (int i = 0; i < m; i++) {
        free(transpose_matrix[i]);
    }
    free(transpose_matrix);
}
