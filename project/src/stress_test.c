#include <malloc.h>
#include <omp.h>
#include <dlfcn.h>
#include "creating_matrix.h"

int main() {
    srand(time(NULL));
    
    int n = 10000,
        m = 5000;
    double** matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) matrix[i] = (double*)malloc(m * sizeof(double));
    double* transposed_matrix_for_naive = (double*)malloc(n * m * sizeof(double));
    double* transposed_matrix_for_parallel = mmap(NULL, n * m * sizeof(double), PROT_READ 
                                            | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 100 + (rand() % 1000000) / 1000000.0;
        }
    }
    void* library;
    int (*my_func)(const double** matrix, double* transposed_matrix, int size_n, int size_m);
    library = dlopen("libtranspose_parallel.so", RTLD_LAZY);
    
    *(int**)(&my_func) = dlsym(library, "transposition");
    int result = (*my_func)((const double**)matrix, transposed_matrix_for_parallel, n, m);
    dlclose(library);
    switch (result)
    {
    case code_error_array:
        assert("Invalid array");
        break;
    case code_error_fork:
        assert("Failed in create new fork");
        break;
    default:
        break;
    }
 
    int result1 = transposition((const double**)matrix, transposed_matrix_for_naive, n, m);
    switch (result1)
    {
    case code_error_array:
        assert("Invalid array");
        break;
    case code_error_fork:
        assert("Failed in create new fork");
        break;
    default:
        break;
    }
 
    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);
    int error_transpose_detector = 0;
    for (int i = 0; i < 100; i++)
    {
        int rows = rand() % 7500;
        int colons = rand() % 15000;
        if (transposed_matrix_for_parallel[rows*n + colons] != transposed_matrix_for_naive[rows*n + colons])
            error_transpose_detector = 1;
        if (error_transpose_detector) {
            assert("Stress test failed");
            exit(0);
        }
    }
    printf("All good");   

    munmap(transposed_matrix_for_parallel, n * m * sizeof(double));
    free(transposed_matrix_for_naive);
}