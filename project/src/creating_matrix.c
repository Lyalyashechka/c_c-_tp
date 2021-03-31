#include "creating_matrix.h"

int create_file_with_random_number_matrix(FILE* file_matrix, double** matrix, int size_n, int size_m) {
    if (!file_matrix) return code_error_file;
    for (int i = 0; i < size_n; i++) {
        for (int j = 0; j < size_m; j++) {
            matrix[i][j] = rand() % 100 + (rand() % 1000000) / 1000000.0;
            fprintf(file_matrix,"%lf ", matrix[i][j]);
        }
        fputc('\n', file_matrix);
    }
    fclose(file_matrix);
    return code_all_good;
}

int get_matrix_from_file(FILE* file_matrix, double** matrix, int size_n, int size_m) {
    if (!file_matrix) return code_error_file;
    if (!matrix) return code_error_array;
    for (int i = 0; i < size_n; i++) {
        for (int j = 0; j < size_m; j++) {
            if (!fscanf(file_matrix, "%lf", &matrix[i][j]))
                return code_error_size_matrix_in_file;
        }
    }
    return code_all_good;
}

void free_memory_to_matrix (double ** matrix, int n) {
    for (int i = 0; i < n; i++) free(matrix[i]);
    free (matrix);
}

