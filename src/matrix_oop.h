#ifndef MATRIXPLUS_MATRIX_OOP_H
#define MATRIXPLUS_MATRIX_OOP_H

#define MATRIXPLUS_MATRIX_OOP_H
#include <algorithm>
#include <cstring>
#include <iostream>
class Matrix {
 private:
  // Attributes
  int rows_ = 0, cols_ = 0;  // Rows and columns
  double** matrix_ =
      nullptr;  // Pointer to the memory where the matrix is allocated

 public:
  Matrix();  // Default constructor
  Matrix(int rows, int cols);

  Matrix(const Matrix& other);

  Matrix(Matrix&& other) noexcept;

  ~Matrix();  // Destructor

  // mutators
  void SetCols(int val);
  void SetRows(int val);
  // accessors
  [[nodiscard]] int GetCols() const { return cols_; }
  [[nodiscard]] int GetRows() const { return rows_; }

  // Functions

  void SumMatrix(const Matrix& other);

  bool EqMatrix(const Matrix& other);

  void SubMatrix(const Matrix& other);

  void MulNumber(double num);

  void MulMatrix(const Matrix& other);

  Matrix Transpose();

  Matrix CalcComplements();

  double Determinant();

  Matrix InverseMatrix();

  // operators
  Matrix& operator=(const Matrix& b);
  Matrix& operator+=(const Matrix& b);
  Matrix& operator-=(const Matrix& b);
  Matrix& operator*=(const Matrix& b);
  Matrix& operator*=(const double& b);

  double& operator()(int i, int j);
  double operator()(int i, int j) const;
  bool operator==(const Matrix& other) { return EqMatrix(other); }

 private:
  double CalcComplement(int i, int j);
  void ClearMatrix();
  void InitMatrix();
};
std::ostream& operator<<(std::ostream& os, const Matrix& d);

Matrix operator+(const Matrix& m1, const Matrix& m2);
Matrix operator-(const Matrix& m1, const Matrix& m2);
Matrix operator*(const Matrix& m1, const Matrix& m2);
Matrix operator*(const Matrix& m1, const double& number);
Matrix operator*(const double& number, const Matrix& m1);

#endif  // MATRIXPLUS_MATRIX_OOP_H
