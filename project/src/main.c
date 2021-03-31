#include "creating_matrix.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        assert("Invalid arguments");
        exit(0);
    }
    FILE * file_matrix = fopen(argv[1],"r");
    if (!file_matrix) {
        assert("Invalid file");
        exit(0);
    }
    int n = 0,
        m = 0;
    if (fscanf(file_matrix, "%d %d", &n, &m) != 2) {
        assert("Invalid size matrix in file");
        fclose(file_matrix);
        exit(0);
    }

    double **matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) matrix[i] = (double*)malloc(m * sizeof(double));
    
    double* transposed_matrix = (double*)malloc(n*m*sizeof(double));

    int er_inicialization_matrix = get_matrix_from_file(file_matrix, matrix, n, m);
    fclose(file_matrix);

    switch (er_inicialization_matrix) {
    case code_error_file:
        free_memory_to_matrix(matrix, transposed_matrix, n);
        assert("Invalid file");
        exit(0);
        break;
    case code_error_array:
        free_memory_to_matrix(matrix, transposed_matrix, n);
        assert("Invalid array");
        exit(0);
        break;
    case code_error_size_matrix_in_file:
        free_memory_to_matrix(matrix, transposed_matrix, n);
        assert("True size of matrix != size in file");
        exit(0);
        break;
    default:
        break;
    }
    int er_transposition = transposition((const double**)matrix, transposed_matrix, n, m);

    switch (er_transposition)
    {
    case code_error_array:
        free_memory_to_matrix(matrix, transposed_matrix, n);
        assert("Invalid array");
        exit(0);
        break;
    case code_error_thread:
        free_memory_to_matrix(matrix, transposed_matrix, n);
        assert("Failed in thread");
        exit(0);
        break;
    default:
        break;
    }
    free_memory_to_matrix(matrix, transposed_matrix, n);
}
