#include <stdio.h>
#include <assert.h>
#include "stdbool.h"

#define code_all_good 0
#define code_invalid_data 1
#define code_infinity_parab 2
#define code_impossible 3

#define size_matrix 3

struct pointer{
    float x, y;
};

bool string_is_double(const char* s);
float determenant(const float matrix[][3]);
void change_matrix(float matrix[][3], int position, float y1,float y2,float y3);
int coef_paraboly(struct pointer* coord, float *a, float *b, float *c);
