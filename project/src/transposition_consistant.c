#include "creating_matrix.h"

int transposition(const double** matrix, double*transposed_matrix, int size_n, int size_m) {
    printf("Hello from naive\n"); 
    if (!matrix || !transposed_matrix)
        return code_error_array;   
    
    for (int i = 0; i < size_n; i++) {
        for (int j = 0; j < size_m; j++) {
            transposed_matrix[i + size_n * j] = matrix[i][j];
        }
    }
    return code_all_good;
}