#include <malloc.h>
#include <omp.h>
#include <dlfcn.h>
#include "creating_matrix.h"

int main() {
    srand(time(NULL));
    
    int n = 5000,
        m = 5000;
    double** matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) matrix[i] = (double*)malloc(m * sizeof(double));
    double* transposed_matrix_for_naive = (double*)malloc(n * m * sizeof(double));
    /*double* transposed_matrix_for_parallel = mmap(NULL, n * m * sizeof(double), PROT_READ 
                                            | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
*/
    double* transposed_matrix_for_parallel = (double*)malloc(n * m * sizeof(double));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 100 + (rand() % 1000000) / 1000000.0;
        }
    }
    void* library;
    int (*my_func)(const double** matrix, double* transposed_matrix, int size_n, int size_m);
    library = dlopen("libtranspose_parallel.so", RTLD_LAZY);
    
    *(int**)(&my_func) = dlsym(library, "transposition");
    clock_t begin_parall = clock();
    int result = (*my_func)((const double**)matrix, transposed_matrix_for_parallel, n, m);
    clock_t end_parall = clock();
    double time_spent_parall = (double)(end_parall - begin_parall) * 1000.0 / CLOCKS_PER_SEC;
    printf("PARAL: %lf \n", time_spent_parall);
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
    clock_t begin = clock();
    int result1 = transposition((const double**)matrix, transposed_matrix_for_naive, n, m);
    clock_t end = clock();
    double time = (double)(end - begin) * 1000.0 / CLOCKS_PER_SEC;
    printf("Synch: %lf \n", time);
    switch (result1)
    {
    case code_error_array:
        assert("Invalid array");
        break;
    default:
        break;
    }
    
    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);
    
    int error_transpose_detector = 0;
    for (int i = 0; i < 100; i++)
    {
        int rows = rand() % 5;
        int colons = rand() % 3;
        if (transposed_matrix_for_parallel[rows*n + colons] != transposed_matrix_for_naive[rows*n + colons])
            error_transpose_detector = 1;
        if (error_transpose_detector) {
            assert("Stress test failed");
            exit(0);
        }
    }
    printf("All good");   
    
    free(transposed_matrix_for_parallel);
    
 
}