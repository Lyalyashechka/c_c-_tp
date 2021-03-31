#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <time.h>
#include <pthread.h>

#define code_all_good 0
#define code_error_array -4


typedef struct thread_data
{
    const double** matrix;
    double* transposed_matrix;
    int rows_start;
    int rows_end;
    int num_colons;
} thread_data;

void* transpose_thread(void* data);
int transposition_parallel(const double** matrix, double* transposed_matrix, int n, int m);
int transposition_consistant(const double** matrix, double*transposed_matrix, int size_n, int size_m);

#define size_n 5000
#define size_m 5000

int main () {
    struct timespec mt1, mt2, mt3, mt4;
    double** matrix = (double**)malloc(size_n * sizeof(double*));
    for (int i = 0; i < size_n; i++) matrix[i] = (double*)malloc(size_m * sizeof(double));
    double* transposed_matrix_for_naive = (double*)malloc(size_n * size_m * sizeof(double));
    double* transposed_matrix_for_parallel = (double*)malloc(size_n * size_m * sizeof(double));
    for (int i = 0; i < size_n; i++) {
        for (int j = 0; j < size_m; j++) {
            matrix[i][j] = 10*i + j;
        }
    }
    long tt;
    
    clock_gettime(CLOCK_MONOTONIC, &mt1);
    int result1 = transposition_consistant((const double**)matrix, transposed_matrix_for_naive, size_n, size_m);
    clock_gettime(CLOCK_MONOTONIC, &mt2);
    tt=1000000000*(mt2.tv_sec - mt1.tv_sec)+(mt2.tv_nsec - mt1.tv_nsec);
    printf("Naive: %ld \n", tt);
    printf("%d \n", result1);

    clock_gettime(CLOCK_MONOTONIC, &mt3);
    int result2 = transposition_parallel((const double**)matrix, transposed_matrix_for_parallel, size_n, size_m);
     clock_gettime(CLOCK_MONOTONIC, &mt4);
    tt=1000000000*(mt4.tv_sec - mt3.tv_sec)+(mt4.tv_nsec - mt3.tv_nsec);
    printf("PARAL: %ld \n", tt);
    printf("%d \n", result2);
    
    for (int i = 0; i < size_n; i++) free(matrix[i]);
    free(matrix);
    free(transposed_matrix_for_parallel);
    free(transposed_matrix_for_naive);
}

void* transpose_thread(void* data) {
    thread_data thr = *(thread_data*) data;
    for (int i=thr.rows_start; i < thr.rows_end; i++) {
        for (int j=0; j < thr.num_colons; j++) {
            //printf("%d %d \n", i, j);
            thr.transposed_matrix[i + thr.num_colons * j] = thr.matrix[i][j];
        }
    }
    return 0;
}

int transposition_parallel(const double** matrix, double* transposed_matrix, int n, int m) {
    printf("Hello from parallel\n");
    int num_thread = sysconf(_SC_NPROCESSORS_ONLN);
    int count_row = n / num_thread;
    printf("count row%d \n", count_row);
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
        pthread_create(&pthread_started[i], NULL, transpose_thread, &data_all_thread[i]);
    }
    for (int i = 0; i < num_thread; ++i) {
        pthread_join(pthread_started[i],NULL);
    }
    free(pthread_started);
    free(data_all_thread);
    return code_all_good;
    
}

int transposition_consistant(const double** matrix, double*transposed_matrix, int n, int m) {
  if (!matrix || !transposed_matrix)
        return code_error_array;   
    printf("Hello from naive\n"); 
    for (int i = 0; i < size_n; i++) {
        for (int j = 0; j < size_m; j++) {
            transposed_matrix[i + size_n * j] = matrix[i][j];
        }
    }
    return code_all_good;
}