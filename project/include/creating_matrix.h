#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <time.h>


#define code_all_good 0
#define code_error_file 1
#define code_error_pointer 2
#define code_error_thread 3
#define code_error_array 4
#define code_error_size_matrix_in_file 5


int create_file_with_random_number_matrix(FILE* file_matrix, double** matrix, int size_n, int size_m);
int get_matrix_from_file(FILE* file_matrix, double** matrix, int size_n, int size_m);
int transposition(const double** matrix, double* transposed_matrix, int size_n, int size_m);
void free_memory_to_matrix (double ** matrix, int n);