#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>
#include <mcheck.h>
#include <stdio.h>
double* transposition(double** matrix, int n, int m);
