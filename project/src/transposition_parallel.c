#include <pthread.h>
#include <mcheck.h>
#include <stdio.h>
#include "transposition_parallel.h"

void* transpose_thread(void *argThread) {
    argMatrix_t * mrx = (argMatrix_t*) argThread;
    for (int i = mrx->rows_start; i < mrx->rows_end; i++) {
        for (int j = 0; j < mrx->num_colons; j++) {
            mrx->transpose_matrix[j][i] = mrx->matrix[i][j];
        }
    }
    return NULL;
}

int transposition_parallel(double** matrix, double** transpose_matrix, int n, int m) {
    //опеределяем количество потоков в зависимости от системы
    long num_thread = sysconf(_SC_NPROCESSORS_ONLN);
    assert(num_thread >= 1);

    pthread_t* threads = (pthread_t*)malloc(num_thread * sizeof(pthread_t));
    argMatrix_t* threads_data = (argMatrix_t*)malloc(num_thread * sizeof(argMatrix_t));
    //находим количество строк обрабатываемые одним потоком 
    int count_row = n / num_thread;
    int i = 0;
    for (i = 0; i < num_thread; i++) {
        if (i == num_thread - 1) threads_data[i].rows_end = n;
        else threads_data[i].rows_end = (i + 1) * count_row;
        threads_data[i].rows_start = i * count_row;
        threads_data[i].num_colons = m;
        threads_data[i].matrix = matrix;
        threads_data[i].transpose_matrix = transpose_matrix;
        pthread_create(&(threads[i]), NULL, transpose_thread, &threads_data[i]);
    }


    for(int i = 0; i < num_thread; i++) {
	    pthread_join(threads[i], NULL);
    }
    free(threads_data);
    free(threads);
    return 0;
}