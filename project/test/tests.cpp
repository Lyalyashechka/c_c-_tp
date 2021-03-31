#include "gtest/gtest.h"

extern "C" {
    #include "creating_matrix.h"
}

TEST(test_transpose, test_square_matrix) {
    const int n = 3;
    const int m = 3;
    double **matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) matrix[i] = (double*)malloc(m * sizeof(double));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matrix[i][j] = rand() % 100;
    double *transposed_matrix = (double*)malloc(n * m * sizeof(double));
    int er = transposition((const double**)matrix, transposed_matrix, n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ASSERT_FLOAT_EQ(transposed_matrix[i + n * j], matrix[i][j]);
        }
    }
    EXPECT_EQ(er,0);
    free_memory_to_matrix(matrix, transposed_matrix, n);
} 

TEST(test_transpose, n_low_m) {
    const int n = 1;
    const int m = 5;
    double **matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) matrix[i] = (double*)malloc(m * sizeof(double));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matrix[i][j] = rand() % 100;
    double *transposed_matrix = (double*)malloc(n * m * sizeof(double));
    int er = transposition((const double**)matrix, transposed_matrix, n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ASSERT_FLOAT_EQ(transposed_matrix[i + n * j], matrix[i][j]);
        }
    }
    EXPECT_EQ(er,0);
    free_memory_to_matrix(matrix, transposed_matrix, n);
    
}
TEST(test_transpose, m_low_n) {
    const int n = 10;
    const int m = 5;
    double **matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) matrix[i] = (double*)malloc(m * sizeof(double));
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matrix[i][j] = rand() % 100;

    double *transposed_matrix = (double*)malloc(n * m * sizeof(double));
    int er = transposition((const double**)matrix, transposed_matrix, n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ASSERT_FLOAT_EQ(transposed_matrix[i + n * j], matrix[i][j]);
        }
    }
    EXPECT_EQ(er,0);
    free_memory_to_matrix(matrix, transposed_matrix, n);
    
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}