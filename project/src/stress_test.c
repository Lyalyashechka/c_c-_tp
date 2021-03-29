#include <malloc.h>
#include <omp.h>
#include <dlfcn.h>
#include "creating_matrix.h"

int main() {
    srand(time(NULL));
    FILE * file_matrix;
    file_matrix = fopen("../test.txt", "w+");

    int n = 10,
        m = 10;
    

    double **matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) matrix[i] = (double*)malloc(m * sizeof(double));

    int er = create_file_with_random_number_matrix(file_matrix, matrix, n, m);
    void* library;
    double* (*my_func)(double** matrix, int size_n, int size_m);
    library = dlopen("libtranspose_parallel.so", RTLD_LAZY);
    
    *(double**)(&my_func) = dlsym(library, "transposition");
    double* result = (*my_func)(matrix, n, m);
    
    dlclose(library);
    printf("%d ", er);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", result[i*m + j]);
        }
        printf("\n");
    }
    double* result1 = transposition(matrix, n, m);
    printf("\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", result1[i*m + j]);
        }
        printf("\n");
    }
}