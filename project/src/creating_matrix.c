#include "creating_matrix.h"
int create_file_with_random_number_matrix(FILE* file_matrix, double** matrix, int size_n, int size_m) {
    if (!file_matrix)
        return code_error_file;
    for (int i = 0; i < size_n; i++) {
        for (int j = 0; j < size_m; j++) {
            matrix[i][j] = rand() % 100 + (rand() % 1000) / 1000.0;
            fprintf(file_matrix,"%lf ", matrix[i][j]);
        }
        fputc('\n', file_matrix);
    }
    fclose(file_matrix);
    return 0;
} 
