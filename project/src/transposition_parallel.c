
#include "transposition_parallel.h"

void transpose_process(double **matrix, double* transpose_matrix, int rows_start, int rows_end, int num_colons) {
    for (int i = rows_start; i < rows_end; i++) {
        for (int j = 0; j < num_colons; j++) {
            transpose_matrix[i + num_colons * j] = matrix[i][j];
        }
    }
    _exit(0);
}
int start_process(int num_process, int* process_started) {
    int i = 0;
    for (i = 0; i < num_process; ++i) {
        int pid = fork();
        if (pid == 0)
            return i;
        else
            process_started[i] = pid;
    }
    return -1;
}
double* transposition(double** matrix, int n, int m) {
    printf("Hello from parallel\n");
    double* transpose_matrix = mmap(NULL, m * n * sizeof(double), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int num_process = sysconf(_SC_NPROCESSORS_ONLN);
    int count_row = n / num_process;
    int* process_started = (int*)malloc(num_process * sizeof(int));
    int id_proc = start_process(num_process, process_started);
    if (id_proc != -1) {
        if (id_proc == num_process - 1)
            transpose_process(matrix, transpose_matrix, id_proc * count_row, n, m);
        else
            transpose_process(matrix, transpose_matrix, id_proc * count_row, (id_proc+1) * count_row, m);
              
    }
    for ( int i = 0; i != num_process; ++i ) {
        while ( waitpid(process_started[i], NULL, 0) > 0 ) {} }
    return transpose_matrix;
    
}
