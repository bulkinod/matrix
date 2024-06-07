//
// Created by ackbarca on 13.02.24.
//
#include "../matrix_test.h"
TEST(accessors_suite, get_rows_test_1) {
  Matrix result = Matrix(4, 4);
  EXPECT_TRUE(result.GetRows() == 4);
}
TEST(accessors_suite, get_cols_test_1) {
  Matrix result = Matrix(4, 4);
  EXPECT_TRUE(result.GetCols() == 4);
}