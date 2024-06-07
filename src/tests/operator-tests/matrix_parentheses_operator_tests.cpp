//
// Created by ackbarca on 09.02.24.
//
#include "../matrix_test.h"

TEST(operators_suite, parentheses_operators_test_1) {
  Matrix matrix = Matrix();
  matrix(1, 1) = 10.123;
  EXPECT_DOUBLE_EQ(((const Matrix)matrix)(1, 1), 10.123);
}
TEST(operators_suite, parentheses_operator_test_2) {
  Matrix matrix = Matrix(3, 4);
  EXPECT_THROW(matrix(0, 4) = 10.132, std::out_of_range);
  const Matrix const_matrix = Matrix(4, 3);
  EXPECT_THROW(const_matrix(0, 4), std::out_of_range);
}

TEST(operators_suite, parentheses_operator_test_3) {
  Matrix matrix = Matrix(4, 3);
  EXPECT_THROW(matrix(4, 0) = 10.132, std::out_of_range);
  const Matrix const_matrix = Matrix(4, 3);
  EXPECT_THROW(const_matrix(4, 0), std::out_of_range);
}