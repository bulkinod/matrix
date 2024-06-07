//
// Created by Ackbar Cantaloupe on 2/9/24.
//
#include "../matrix_test.h"
TEST(functions_suite, mult_matrix_function_test_1) {
  double arr1[3][4] = {{1, 1, 2, 2}, {3, 3, 4, 4}, {5, 5, 6, 7}};
  double arr2[4][3] = {{1, 2, 3}, {5, 6, 7}, {9, 10, 1}, {4, 8, 2}};

  double expectedValues[3][3] = {{32, 44, 16}, {70, 96, 42}, {112, 156, 70}};

  Matrix A = Matrix(3, 4);
  fill_matrix(A, arr1);

  Matrix B = Matrix(4, 3);
  fill_matrix(B, arr2);

  Matrix expected_result = Matrix(3, 3);
  fill_matrix(expected_result, expectedValues);

  A.MulMatrix(B);

  EXPECT_TRUE(expected_result == A);
}

TEST(functions_suite, mult_matrix_function_test_2) {
  double arr1[3][4] = {{1, 1, 2, 2}, {3, 3, 4, 4}, {5, 5, 6, 7}};
  double arr2[4][2] = {{1, 2}, {5, 6}, {9, 10}, {4, 8}};

  double expectedValues[3][2] = {{32, 44}, {70, 96}, {112, 156}};

  Matrix A = Matrix(3, 4);
  fill_matrix(A, arr1);

  Matrix B = Matrix(4, 2);
  fill_matrix(B, arr2);

  Matrix expected_result = Matrix(3, 2);
  fill_matrix(expected_result, expectedValues);

  A.MulMatrix(B);

  EXPECT_TRUE(expected_result == A);
}

TEST(functions_suite, mult_matrix_function_test_3) {
  double arr1[3][4] = {{1, 1, 2, 2}, {3, 3, 4, 4}, {5, 5, 6, 7}};
  double arr2[3][4] = {{1, 2, 3}, {5, 6, 7}, {9, 10, 1}};

  Matrix A = Matrix(3, 4);
  fill_matrix(A, arr1);

  Matrix B = Matrix(3, 4);
  fill_matrix(B, arr2);

  EXPECT_THROW(A.MulMatrix(B), std::invalid_argument);
}