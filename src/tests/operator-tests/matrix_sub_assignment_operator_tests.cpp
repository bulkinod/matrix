//
// Created by ackbarca on 13.02.24.
//
#include "../matrix_test.h"
TEST(operators_suite, sub_assignment_operator_test_1) {
  const int rowsCount = 3;
  const int columnsCount = 4;
  double arr1[3][4] = {{1, 1, 2, 2}, {3, 3, 4, 4}, {5, 5, 6, 7}};
  double arr2[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 1, 2}};

  double expectedValues[3][4] = {
      {0, -1, -1, -2}, {-2, -3, -3, -4}, {-4, -5, 5, 5}};

  Matrix A = Matrix(rowsCount, columnsCount);
  fill_matrix(A, arr1);

  Matrix B = Matrix(rowsCount, columnsCount);
  fill_matrix(B, arr2);

  Matrix expected_result = Matrix(rowsCount, columnsCount);
  fill_matrix(expected_result, expectedValues);

  EXPECT_TRUE((A -= B) == A);
  EXPECT_TRUE(expected_result == A);
}
TEST(operators_suite, sub_assignment_operator_test_2) {
  double arr1[3][4] = {{1, 1, 2, 2}, {3, 3, 4, 4}, {5, 5, 6, 7}};
  double arr2[3][3] = {{1, 2, 3}, {5, 6, 7}, {9, 10, 1}};

  Matrix A = Matrix(3, 4);
  fill_matrix(A, arr1);

  Matrix B = Matrix(3, 3);
  fill_matrix(B, arr2);

  EXPECT_THROW(A -= B, std::invalid_argument);
}
