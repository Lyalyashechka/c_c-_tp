
#include "creating_matrix.h"
#define code_main_proc -1

int transpose_process(const double **matrix, double* transposed_matrix, int rows_start, int rows_end, int num_colons) {
    if (!matrix || !transposed_matrix)
        return code_error_array;
    
    for (int i = rows_start; i < rows_end; i++) {
        for (int j = 0; j < num_colons; j++) {
            transposed_matrix[i + num_colons * j] = matrix[i][j];
        }
    }
    _exit(0);
    return code_all_good;
}
int start_process(int num_process, int* process_started) {
    int i = 0;
    for (i = 0; i < num_process; ++i) {
        int pid = fork();
        if (pid == 0) return i;
        else if (pid == -1) return code_error_fork;
        else process_started[i] = pid;
    }
    return code_main_proc;
}
int transposition(const double** matrix, double* transposed_matrix, int n, int m) {
    printf("Hello from parallel\n");

    int num_process = sysconf(_SC_NPROCESSORS_ONLN);
    int count_row = n / num_process;
    int* process_started = (int*)malloc(num_process * sizeof(int));
    
    int id_proc = start_process(num_process, process_started);
    if (id_proc == code_error_fork) return code_error_fork;
    if (id_proc != code_main_proc) {
        if (id_proc == num_process - 1)
            transpose_process(matrix, transposed_matrix, id_proc * count_row, n, m);
        else
            transpose_process(matrix, transposed_matrix, id_proc * count_row, 
                                                        (id_proc+1) * count_row, m);
    }
    for (int i = 0; i != num_process; ++i ) {
        while (waitpid(process_started[i], NULL, 0) > 0 ) {} }
    return code_all_good;
    
}
