#include <stdio.h>
#include "transposition_consistant.h"
int transposition_consistant(double** matrix, double** transposition_matrix, int size_n, int size_m) {
    for (int i = 0; i < size_n; i++) {
        for (int j = 0; j < size_m; j++) {
            transposition_matrix[j][i] = matrix[i][j];
        }
    }
    
    return 0;
}