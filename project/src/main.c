#include <malloc.h>
#include <time.h>
#include <omp.h>
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
    double* shared_mem = mmap(NULL, m * n * sizeof(double), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
 
    

    int er = create_file_with_random_number_matrix(file_matrix, matrix, n, m);
    clock_t begin_synch = clock();
    er = transposition_consistant(matrix, transpose_matrix, n, m);
    clock_t end_synch = clock();
    double time_spent_cons = (double)(end_synch - begin_synch) * 1000.0 / CLOCKS_PER_SEC;

    clock_t begin_parall = clock();
    er = transposition_parallel(matrix, shared_mem, n, m);
    clock_t end_parall = clock();
    double time_spent_parall = (double)(end_parall - begin_parall) * 1000.0 / CLOCKS_PER_SEC;
    printf("%d %lf %lf \n", er, time_spent_cons, time_spent_parall);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", shared_mem[i*m + j]);
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
