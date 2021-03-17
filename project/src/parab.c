#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parab.h"
#include "stdio.h"


float determenant(float matrix[][size_matrix]) {
    if (matrix == NULL)
       return code_invalid_data;
    return matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0]
        + matrix[1][0] * matrix[2][1] * matrix[0][2] - matrix[0][2] * matrix[1][1] * matrix[2][0] -
         matrix[0][0]*matrix[1][2] * matrix[2][1] - matrix[2][2] * matrix[0][1] * matrix[1][0];
}

void change_matrix(float matrix[][size_matrix], int position, float y1, float y2, float y3) {
    if (matrix == NULL)
        return;
    matrix[0][position] = y1;
    matrix[1][position] = y2;
    matrix[2][position] = y3;
    return;
}

int coef_paraboly(struct pointer* coord, float *a, float *b, float *c) {
    if (coord == NULL || a == NULL || b == NULL || c == NULL)
        return code_invalid_data;
    float main_matrix[size_matrix][size_matrix] = {{0, 0, 1}, {0, 0, 1}, {0, 0, 1}};
    main_matrix[0][0] = coord[0].x * coord[0].x;
    main_matrix[0][1] = coord[0].x;
    main_matrix[1][0] = coord[1].x * coord[1].x;
    main_matrix[1][1] = coord[1].x;
    main_matrix[2][0] = coord[2].x * coord[2].x;
    main_matrix[2][1] = coord[2].x;
    float a_matrix[3][3], b_matrix[3][3], c_matrix[3][3];
    memcpy(a_matrix, main_matrix, sizeof(a_matrix));
    memcpy(b_matrix, main_matrix, sizeof(b_matrix));
    memcpy(c_matrix, main_matrix, sizeof(c_matrix));
    float det_main = determenant(main_matrix);
    change_matrix(a_matrix, 0, coord[0].y, coord[1].y, coord[2].y);
    change_matrix(b_matrix, 1, coord[0].y, coord[1].y, coord[2].y);
    change_matrix(c_matrix, 2, coord[0].y, coord[1].y, coord[2].y);
    float det_c = determenant(c_matrix);
    float det_b = determenant(b_matrix);
    float det_a = determenant(a_matrix);
    if (det_main != 0) {
        *a = det_a / det_main;
        *b = det_b / det_main;
        *c = det_c / det_main;
        return code_all_good;
    }
    // две точки одинаковые, возможно построить только одну параболу, функция не обрабатывает этот случай
    else if (det_main == 0 && ((coord[0].x == coord[1].x && coord[0].y == coord[1].y) ||
                (coord[0].x == coord[2].x && coord[0].y == coord[2].y) ||
                (coord[1].x == coord[2].x && coord[1].y == coord[2].y)) && 
                !((coord[0].x == coord[1].x && coord[1].x == coord[2].x) &&
                 (coord[0].y == coord[1].y && coord[1].y == coord[2].y))) {
        printf("Invalid data");
        return code_invalid_data;
    }
    else if (det_main == 0 && det_a == 0 && det_b == 0 && det_c == 0) {
        printf("infinite number of parabols");
        return code_infinity_parab;
    }
    else {
        printf("it's impossible to draw parabolas through these three points");
        return code_impossible;
    }
}
bool string_is_double(char* s) {
    if (s == NULL)
        return false;
    if ((s[0]<'0' || s[0] > '9') && s[0] != '-')
        return false;
    if (s[0] == '-' && strlen(s) == 2)
        return false;
    int detected_more_1point = 0;
    for (int i = 1; i < strlen(s) - 1; i++) {
        if ((s[i]<'0' || s[i] > '9') && s[i] != '.')
            return false;
        if (s[i] == '.') {
            if (!detected_more_1point)
                detected_more_1point = 1;
            else
                return false;
        }
    }
    return true;
}

