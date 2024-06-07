//
// Created by ackbarca on 09.02.24.
//
#include "../matrix_test.h"
TEST(functions_suite, eq_function_test_1) {
  Matrix m1 = Matrix();
  Matrix m2 = Matrix(4, 3);
  Matrix m3 = Matrix(3, 4);

  EXPECT_FALSE(m1 == m2);
  EXPECT_FALSE(m1 == m3);
  EXPECT_FALSE(m2 == m3);
}
TEST(functions_suite, eq_function_test_2) {
  Matrix m1 = Matrix();
  Matrix m2 = Matrix();

  double arr1[3][3] = {
      {1.52, 2.135, 3.315},
      {4.316316136, 5.136136, 6.31531},
      {7.136, 8.1614, 9.64314},
  };

  fill_matrix(m1, arr1);
  fill_matrix(m2, arr1);

  EXPECT_TRUE(m1 == m2);
  m1(0, 0) = 10;
  EXPECT_FALSE(m1 == m2);
  m1(0, 0) = m2(0, 0);
  m1(1, 1) = 10;
  EXPECT_FALSE(m1 == m2);
  m1(1, 1) = m2(1, 1);
  m1(2, 2) = 10;
  EXPECT_FALSE(m1 == m2);
}