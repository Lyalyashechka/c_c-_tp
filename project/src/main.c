#include <malloc.h>
#include <omp.h>
#include "creating_matrix.h"


int main(int argc, char* argv[]) {
    if (argc < 2) assert("Invalid arguments");
    FILE * file_matrix = fopen(argv[1],"r");
    if (!file_matrix) assert("Invalid file");
    
    int n = 0,
        m = 0;
    if (fscanf(file_matrix, "%d %d", &n, &m) != 2) 
        assert("Invalid size matrix in file");

    double **matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) matrix[i] = (double*)malloc(m * sizeof(double));

    int er_inicialization_matrix = get_matrix_from_file(file_matrix, matrix, n, m);
    fclose(file_matrix);

    switch (er_inicialization_matrix) {
    case code_error_file:
        assert("Invalid file");
        break;
    case code_error_array:
        assert("Invalid array");
        break;
    case code_error_size_matrix_in_file:
        assert("True size of matrix != size in file");
        break;
    default:
        break;
    }
    
    /*double* transposed_matrix = mmap(NULL, n * m * sizeof(double), PROT_READ 
                                            | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);*/
    double* transposed_matrix = (double*)malloc(n*m*sizeof(double)); 
    clock_t begin = clock();
    int er_transposition = transposition((const double**)matrix, transposed_matrix, n, m);
    clock_t end = clock();
    double time_spent_cons = (double)(end - begin) * 1000.0 / CLOCKS_PER_SEC;
    printf("%lf", time_spent_cons);
    switch (er_transposition)
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
    
    munmap(transposed_matrix, n * m * sizeof(double));
    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);
    
}
