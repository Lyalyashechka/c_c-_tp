#include <pthread.h>

#include "creating_matrix.h"

typedef struct thread_data
{
    const double** matrix;
    double* transposed_matrix;
    int rows_start;
    int rows_end;
    int num_colons;
    int num_colons_in_transposed_matrix;
} thread_data;

void* transpose_thread(void* data);
int transposition(const double** matrix, double* transposed_matrix, int n, int m);



void* transpose_thread(void* data) {
    const int code_error_pointer_for_pointer = 2;
    const int code_all_good_for_pointer = 0;
    int *status_retern_thread = calloc(1, sizeof(int));
    if (!data) {
        *status_retern_thread = code_error_pointer_for_pointer;
        return status_retern_thread;
    }
    thread_data thr = *(thread_data*) data;
    for (int i=thr.rows_start; i < thr.rows_end; i++) {
        for (int j=0; j < thr.num_colons; j++) {
            thr.transposed_matrix[i + thr.num_colons_in_transposed_matrix * j] = thr.matrix[i][j];
        }
    }

    *status_retern_thread = code_all_good_for_pointer;
    return status_retern_thread;
}

int transposition(const double** matrix, double* transposed_matrix, int n, int m) {
    printf("Hello from parallel\n");
    if (!matrix || !transposed_matrix) return code_error_array;
    int num_thread = sysconf(_SC_NPROCESSORS_ONLN);
    int count_row = n / num_thread;
    pthread_t* pthread_started = (pthread_t*)malloc(num_thread * sizeof(pthread_t));
    thread_data* data_all_thread = (thread_data*)malloc(num_thread * sizeof(thread_data)); 
    for (int i = 0; i < num_thread; i++) {
        
        if (i == num_thread - 1)
            data_all_thread[i].rows_end = n;
        else
            data_all_thread[i].rows_end = (i + 1) * count_row;
        data_all_thread[i].rows_start = i * count_row;
        data_all_thread[i].matrix = matrix;
        data_all_thread[i].transposed_matrix = transposed_matrix;
        data_all_thread[i].num_colons = m;
        data_all_thread[i].num_colons_in_transposed_matrix = n;
        pthread_create(&pthread_started[i], NULL, transpose_thread, &data_all_thread[i]);
    }
    for (int i = 0; i < num_thread; ++i) {
       if (pthread_join(pthread_started[i], NULL) != 0) {
            free(pthread_started);
            free(data_all_thread);
            return code_error_thread;
        }
    }
    free(pthread_started);
    free(data_all_thread);
    return code_all_good;
    
}
