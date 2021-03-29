#include <malloc.h>
#include <omp.h>
#include "creating_matrix.h"


int main(int argc, char* argv[]) {
    if (argc < 2) assert("Invalid arguments");
    //srand(time(NULL));
    FILE * file_matrix = fopen(argv[1],"r");
    if (!file_matrix) assert("Invalid file");
    
    int n = 0,
        m = 0;
    if (fscanf(file_matrix, "%d %d", &n, &m) != 2) 
        assert("Invalid size matrix in file");
    double **matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) matrix[i] = (double*)malloc(m * sizeof(double));

    int er_inicialization_matrix = get_matrix_from_file(file_matrix, matrix, n, m); 
    printf("%d", er_inicialization_matrix);
    double* transposed_matrix = mmap(NULL, n * m * sizeof(double), PROT_READ 
                                            | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    
    
    clock_t begin_synch = clock();
    er_inicialization_matrix = transposition((const double**)matrix, transposed_matrix, n, m);
    clock_t end_synch = clock();
    double time_spent_cons = (double)(end_synch - begin_synch) * 1000.0 / CLOCKS_PER_SEC;

    printf("%d %lf \n", er_inicialization_matrix, time_spent_cons);
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 1; j++) {
            printf("%lf ", transposed_matrix[i*m + j]);
        }
        printf("\n");
    }
    
    munmap(transposed_matrix, n * m * sizeof(double));
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
}
