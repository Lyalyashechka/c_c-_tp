// Задачу решаю с помощью метода крамера для матрицы
// y1 = a * x1^2 + b * x1 + c
// y2 = a * x2^2 + b * x2 + c
// y3 = a * x3^2 + b * x3 + c
// метод позволяет рассматривать случаи, когда через точки невозможно провести
// параболу
#include "parab.h"

#define max_size_string 100

bool input(struct pointer coord[size_matrix]);
int main() {
    struct pointer coord[size_matrix];
    if (input(coord)) {
        float a, b, c;
        int checkError = coef_paraboly(coord, &a, &b, &c);
        switch (checkError) {
            case code_invalid_data:
                assert("Invalid data");
                break;
            case code_infinity_parab:
                assert("infinite number of parabols");
                break;
            case code_impossible:
                assert("It's imossible to draw parabols through these three points");
                break;
            case code_all_good:
                printf("%f %f %f", a, b, c);
                break;
        }
    }
}
bool input(struct pointer coord[size_matrix]) {
    char s[max_size_string];
    for (int i = 0; i < size_matrix; i++) {
        printf("Write x%d: ", i + 1);
        fgets(s, sizeof(s), stdin);
        if (string_is_double(s))
            coord[i].x = atof(s);
        else {
            printf("Incorrect data");
            return false;
        }
        printf("Write y%d: ", i + 1);
        fgets(s, sizeof(s), stdin);
        if (string_is_double(s))
            coord[i].y = atof(s);
        else {
            printf("Incorrect data");
            return false;
        }
    }
    return true;
}
