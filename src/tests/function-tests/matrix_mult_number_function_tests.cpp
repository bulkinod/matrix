//
// Created by Ackbar Cantaloupe on 2/9/24.
//
#include "../matrix_test.h"

TEST(functions_suite, mult_number_function_test_1) {
  const int rowsCount = 3;
  const int columnsCount = 4;
  double arr1[3][4] = {{1, 1, 2, 2}, {3, 3, 4, 4}, {5, 5, 6, 7}};

  double expectedValues[3][4] = {
      {-3, -3, -6, -6}, {-9, -9, -12, -12}, {-15, -15, -18, -21}};
  double number = -3;

  Matrix A = Matrix(rowsCount, columnsCount);
  fill_matrix(A, arr1);

  Matrix expected_result = Matrix(rowsCount, columnsCount);
  fill_matrix(expected_result, expectedValues);

  A.MulNumber(number);
  EXPECT_TRUE(expected_result == A);
}