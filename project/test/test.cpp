#include "gtest/gtest.h"
extern "C" {
    #include "../include/parab.h"
}
//Вычисление определителя
TEST(determenant,test_1){
    float matrix[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 1}};
    float matrix_1[3][3] = {{10, 3, 4}, {40, 10, 6}, {73, 8, 9}};
    float matrix_2[3][3] = {{7, 28, 43}, {40, 5, 63}, {73, 8, 9}};
    float det = determenant(matrix);
    float det_1 = determenant(matrix_1);
    float det_2 = determenant(matrix_2);
    ASSERT_FLOAT_EQ(det, 0);
    ASSERT_FLOAT_EQ(det_1, -986);    
    ASSERT_FLOAT_EQ(det_2, 113544);
} 
//Проверка замены столбца матрицы
TEST(change_matrix, test_1){
    float matrix[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    change_matrix(matrix, 0, 1, 1, 1);
    ASSERT_FLOAT_EQ(matrix[0][0], 1);
    ASSERT_FLOAT_EQ(matrix[1][0], 1);
    ASSERT_FLOAT_EQ(matrix[2][0], 1);
}
//Проверка строки на то является ли она числом 
//Во всех тестах 0 в конце эмитирует символ конца строки, который считается
//strlen только если строка была получена из stdin'a
TEST(string_is_double, one_minus){
    char* s = "-0";
    EXPECT_EQ(string_is_double(s), 0);
}
TEST(string_is_double, two_point_in_number){
    char* s = "0.545.4340";
    EXPECT_EQ(string_is_double(s), 0);
}
TEST(string_is_double, one_word){
    char* s = "3543.2432a0";
    EXPECT_EQ(string_is_double(s), 0);
}
TEST(string_is_double, all_right){
    char* s = "4343.3223";
    EXPECT_EQ(string_is_double(s), 1);
}
//Проверка главной функции
TEST(coef_paraboly, one_point){
    struct pointer t1[3];
    t1[0].x = t1[0].y = t1[1].x = t1[1].y = t1[2].x = t1[2].y = 0;
    float a, b, c;
    EXPECT_EQ(coef_paraboly(t1, &a, &b, &c), 2);
}
//функция не обрабатывает случай когда поданы две одинаковые точки
TEST(coef_paraboly, two_point){
    struct pointer t2[3];
    t2[0].x = t2[1].x = t2[0].y = t2[1].y = 1;
    t2[2].x = t2[2].y = 0;
    float a, b, c;
    EXPECT_EQ(coef_paraboly(t2, &a, &b, &c), 1);
}
TEST(coef_paraboly, typical1){   
    struct pointer t2[3];
    t2[0].x = t2[0].y = 0;
    t2[1].x = t2[1].y = 1;
    t2[2].x = -100;
    t2[2].y = 1;
    float a, b, c;
    EXPECT_EQ(coef_paraboly(t2, &a, &b, &c), 0);
    ASSERT_FLOAT_EQ(a, 0.01);
    ASSERT_FLOAT_EQ(b, 0.99);
    ASSERT_FLOAT_EQ(c, 0);
}
TEST(coef_paraboly, typical2){   
    struct pointer t2[3];
    t2[0].x = t2[0].y = 0;
    t2[1].x = t2[1].y = 1;
    t2[2].x = t2[2].y = -3;
    float a, b, c;
    EXPECT_EQ(coef_paraboly(t2, &a, &b, &c), 0);
    ASSERT_FLOAT_EQ(a, 0);
    ASSERT_FLOAT_EQ(b, 1);
    ASSERT_FLOAT_EQ(c, 0);
}
    
int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

