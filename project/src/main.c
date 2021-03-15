//Задачу решаю с помощью метода крамера для матрицы
//y1 = a * x1^2 + b * x1 + c
//y2 = a * x2^2 + b * x2 + c
//y3 = a * x3^2 + b * x3 + c
//метод позволяет рассматривать случаи, когда через точки невозможно провести 
//параболу 

#include <stdio.h>
#include <stdlib.h>
#include "../include/parab.h"
int input(struct pointer coord[3]);
int main()
{
    struct pointer coord[3];
    if (input(coord)){
        float a, b, c;
        int checkError = coef_paraboly(coord, &a, &b, &c);
        printf("%d %f %f %f", checkError, a, b, c);
    }
}
int input(struct pointer coord[3]){    
    char s[100];
    for(int i = 0; i < 3; i++){
        printf("Write x%d: ", i + 1);
        fgets(s, sizeof(s), stdin);
        if (string_is_double(s))
            coord[i].x = atof(s);
        else{
            printf("Incorrect data");
            return 0;
        }
        printf("Write y%d: ", i + 1);
        fgets(s, sizeof(s), stdin);
        if(string_is_double(s))
            coord[i].y = atof(s);
        else{
            printf("Incorrect data");
            return 0;
        }
    }
    return 1;
};
