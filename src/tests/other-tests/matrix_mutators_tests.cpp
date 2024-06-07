//
// Created by ackbarca on 13.02.24.
//
#include "../matrix_test.h"
TEST(mutators_suite, set_row_test_1) {
  Matrix result;
  result.SetRows(5);
  EXPECT_TRUE(result.GetRows() == 5);
}

TEST(mutators_suite, set_row_test_2) {
  Matrix result = Matrix(3, 3);
  result.SetRows(5);
  EXPECT_TRUE(result.GetRows() == 5);
}

TEST(mutators_suite, set_row_test_3) {
  Matrix result = Matrix(5, 5);
  result.SetRows(3);
  EXPECT_TRUE(result.GetRows() == 3);
}

TEST(mutators_suite, set_cols_test_1) {
  Matrix result;
  result.SetCols(5);
  EXPECT_TRUE(result.GetCols() == 5);
}

TEST(mutators_suite, set_cols_test_2) {
  Matrix result = Matrix(3, 3);
  result.SetCols(5);
  EXPECT_TRUE(result.GetCols() == 5);
}

TEST(mutators_suite, set_cols_test_3) {
  Matrix result = Matrix(5, 5);
  result.SetCols(3);
  EXPECT_TRUE(result.GetCols() == 3);
}