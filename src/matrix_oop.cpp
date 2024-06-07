#include "matrix_oop.h"

#include <cmath>
#include <stdexcept>
//      CONSTRUCTORS && DESTRUCTORS
Matrix::Matrix() : rows_(3), cols_(3) { InitMatrix(); }

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) throw std::out_of_range("Incorrect matrix size!");
  InitMatrix();
}

Matrix::Matrix(const Matrix &other) : Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < other.rows_; ++i) {
    std::copy(other.matrix_[i], other.matrix_[i] + other.cols_, matrix_[i]);
  }
}

Matrix::Matrix(Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

Matrix::~Matrix() { ClearMatrix(); }

//      ACCESSORS && MUTATORS

void Matrix::SetCols(int val) {
  if (cols_ == val) return;
  if (val < 1) throw std::out_of_range("Invalid columns count!");
  int cpy_length = val > cols_ ? cols_ : val;
  for (int i = 0; i < rows_; ++i) {
    double *last_row = matrix_[i];
    auto new_row = new double[val];
    std::copy(last_row, last_row + cpy_length, new_row);
    matrix_[i] = new_row;
    delete[] last_row;
  }
  cols_ = val;
}

void Matrix::SetRows(int val) {
  if (val == rows_) return;
  if (val < 1) throw std::out_of_range("Invalid rows count!");
  int cpy_length = val > rows_ ? rows_ : val;
  auto new_matrix = new double *[val];
  std::copy(matrix_, matrix_ + cpy_length, new_matrix);

  if (val > rows_) {
    for (int i = cpy_length; i < val; ++i) {
      new_matrix[i] = new double[cols_];
    }
  }
  if (val < rows_) {
    for (int i = val; i < rows_; ++i) {
      delete[] matrix_[i];
    }
  }
  delete[] matrix_;
  matrix_ = new_matrix;
  rows_ = val;
}

//      PUBLIC METHODS

bool Matrix::EqMatrix(const Matrix &other) {
  if (other.rows_ != rows_ || other.cols_ != cols_) return false;

  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) >=
          std::numeric_limits<double>::epsilon())
        return false;
    }
  }
  return true;
}

void Matrix::SumMatrix(const Matrix &other) {
  if (cols_ != other.cols_ || rows_ != other.rows_)
    throw std::invalid_argument(
        "The size of the other matrix does not match the current one!");

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
  }
}

void Matrix::SubMatrix(const Matrix &other) {
  if (cols_ != other.cols_ || rows_ != other.rows_)
    throw std::invalid_argument(
        "The size of the other matrix does not match the current one!");

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
  }
}

void Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void Matrix::MulMatrix(const Matrix &other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix.");

  Matrix thisCopy = Matrix(*this);

  SetCols(other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0;
      for (int k = 0; k < thisCopy.cols_; k++) {
        matrix_[i][j] += (thisCopy.matrix_[i][k] * other.matrix_[k][j]);
      }
    }
  }
}

Matrix Matrix::Transpose() {
  Matrix result = Matrix(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

double Matrix::Determinant() {
  double result = 1;
  if (rows_ != cols_) throw std::logic_error("The matrix is not a square!");
  int size = rows_;

  Matrix temp_matrix = Matrix(*this);

  for (int i = 0; i < size; ++i) {
    int k = i;
    for (int j = k + 1; j < size; ++j)
      if (fabs(temp_matrix.matrix_[k][i]) < fabs(temp_matrix.matrix_[j][i]))
        k = j;

    std::swap(temp_matrix.matrix_[i], temp_matrix.matrix_[k]);

    if (i != k) result = -result;
    result *= temp_matrix.matrix_[i][i];

    for (int j = i + 1; j < size; ++j) {
      temp_matrix.matrix_[i][j] /= temp_matrix.matrix_[i][i];
    }

    for (int j = 0; j < size; ++j) {
      if (j != i && fabs(temp_matrix.matrix_[j][i]) >=
                        std::numeric_limits<double>::epsilon())
        for (k = i + 1; k < size; k++)
          temp_matrix.matrix_[j][k] -=
              temp_matrix.matrix_[j][i] * temp_matrix.matrix_[i][k];
    }
  }
  return result;
}

Matrix Matrix::CalcComplements() {
  if (rows_ != cols_) throw std::logic_error("The matrix is not a square!");

  Matrix complementsMatrix = Matrix(rows_, cols_);

  if (rows_ == 1 && cols_ == 1) {
    complementsMatrix.matrix_[0][0] = 1;
    return complementsMatrix;
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      complementsMatrix.matrix_[i][j] = CalcComplement(i, j);
    }
  }
  return complementsMatrix;
}

Matrix Matrix::InverseMatrix() {
  if (rows_ != cols_) throw std::logic_error("The matrix is not a square!");
  double determinant = Determinant();
  if (fabs(determinant) < std::numeric_limits<double>::epsilon())
    throw std::runtime_error("The determinant is zero!");
  Matrix adjacent_matrix = CalcComplements().Transpose();
  adjacent_matrix.MulNumber(1 / determinant);
  return adjacent_matrix;
}

Matrix &Matrix::operator=(const Matrix &b) {
  if (this == &b) return *this;
  ClearMatrix();
  rows_ = b.rows_;
  cols_ = b.cols_;
  InitMatrix();
  for (int i = 0; i < rows_; ++i) {
    std::copy(b.matrix_[i], b.matrix_[i] + b.cols_, matrix_[i]);
  }
  return *this;
}

void Matrix::ClearMatrix() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

void Matrix::InitMatrix() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
  }
}

//      OPERATORS

double &Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_)
    throw std::out_of_range("The index is out of range!");
  return matrix_[i][j];
}

double Matrix::operator()(int i, int j) const {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_)
    throw std::out_of_range("The index is out of range!");
  return matrix_[i][j];
}

std::ostream &operator<<(std::ostream &os, const Matrix &d) {
  for (int i = 0; i < d.GetRows(); ++i) {
    for (int j = 0; j < d.GetCols(); ++j) {
      std::cout << d(i, j) << '\t';
    }
    std::cout << std::endl;
  }
  return os;
}

Matrix operator*(const double &number, const Matrix &m1) {
  Matrix result = Matrix(m1);
  result.MulNumber(number);
  return result;
}

Matrix operator+(const Matrix &m1, const Matrix &m2) {
  Matrix result = Matrix(m1);
  result.SumMatrix(m2);
  return result;
}
Matrix operator-(const Matrix &m1, const Matrix &m2) {
  Matrix result = Matrix(m1);
  result.SubMatrix(m2);
  return result;
}
Matrix operator*(const Matrix &m1, const Matrix &m2) {
  Matrix result = Matrix(m1);
  result.MulMatrix(m2);
  return result;
}

Matrix operator*(const Matrix &m1, const double &number) {
  Matrix result = Matrix(m1);
  result.MulNumber(number);
  return result;
}

//      PRIVATE METHODS

double Matrix::CalcComplement(int i, int j) {
  Matrix minorMatrix = Matrix(rows_ - 1, cols_ - 1);
  for (int k = 0; k < rows_; ++k) {
    for (int l = 0; l < cols_; ++l) {
      if (k != i && l != j) {
        int new_i = k > i ? k - 1 : k;
        int new_j = l > j ? l - 1 : l;
        minorMatrix.matrix_[new_i][new_j] = matrix_[k][l];
      }
    }
  }
  double result = minorMatrix.Determinant() * pow(-1, i + j);
  return result;
}

Matrix &Matrix::operator+=(const Matrix &b) {
  SumMatrix(b);
  return *this;
}
Matrix &Matrix::operator-=(const Matrix &b) {
  SubMatrix(b);
  return *this;
}
Matrix &Matrix::operator*=(const Matrix &b) {
  MulMatrix(b);
  return *this;
}
Matrix &Matrix::operator*=(const double &b) {
  MulNumber(b);
  return *this;
}
