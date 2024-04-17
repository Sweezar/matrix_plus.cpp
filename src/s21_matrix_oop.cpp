#include "s21_matrix_oop.h"
#include <cmath> 

using namespace std;

/// @brief Выделяет память для матрицы
void S21Matrix::S21Matrix_memory_allocate_() {
  if(rows_ <= 0 || cols_ <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  matrix_ = new double*[rows_]();
  if(!matrix_) {
    throw bad_alloc();
  }

  for(int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
    if(!matrix_[i]) {
      for (int j = 0; j < i; j++) {
        delete[] matrix_[j];
      }
      delete[] matrix_;
      throw bad_alloc();
    }
  }
}

/// @brief освобождение памяти под матрицу
void S21Matrix::destroy_() {
  for(int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

/// @brief Возвращает минор матрицы
/// @param row строка для которой вычисляется минор 
/// @param col столбец для которого вычисляется минор
/// @return результирующую матрицу
S21Matrix S21Matrix::get_minor_(int row, int col) {
  S21Matrix tmp(rows_ - 1, cols_ - 1);
  if (rows_ > 1) {
    for (int i = 0; i < rows_; i++) {
      for (int ii = 0; ii < cols_; ii++) {
        if (i < row && ii < col) {
          tmp.matrix_[i][ii] = matrix_[i][ii];
        } else if (i > row && ii < col) {
          tmp.matrix_[i - 1][ii] = matrix_[i][ii];
        } else if (i < row && ii > col) {
          tmp.matrix_[i][ii - 1] = matrix_[i][ii];
        } else if (i > row && ii > col) {
          tmp.matrix_[i - 1][ii - 1] = matrix_[i][ii];
        }
      }
    }
  }
  return tmp;
}

/// @brief Получить матрицу миноров
/// @return матрицу миноров
S21Matrix S21Matrix::get_matrix_of_minors_() {
  S21Matrix result(rows_, cols_);
  S21Matrix minor_matrix;

  for (int i = 0; i < rows_; i++) {
    for (int ii = 0; ii < cols_; ii++) {
      minor_matrix = get_minor_(i, ii);
      result.matrix_[i][ii] = minor_matrix.Determinant();
    }
  }

  return result;
}

S21Matrix::S21Matrix() : rows_(3), cols_(3) {
  try {
    S21Matrix_memory_allocate_();
  } catch (const bad_alloc& e) {
    cerr << "Memory allocation error";
    exit(1);
  }
}

S21Matrix::S21Matrix(int rows) : rows_(rows), cols_(rows) {
  try {
    S21Matrix_memory_allocate_();
  } catch (const bad_alloc& e) {
    cerr << "Memory allocation error";
    exit(1);
  }
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  try {
    S21Matrix_memory_allocate_();
  } catch (const bad_alloc& e) {
    cerr << "Memory allocation error";
    exit(1);
  }
}

// copy
S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
  try {
    S21Matrix_memory_allocate_();
  } catch (const bad_alloc& e) {
    cerr << "Memory allocation error";
    exit(1);
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// move
S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  destroy_();
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
    S21Matrix result = *this;
    result.SumMatrix(other);
    return result;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
    return *this = *this + other;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
    S21Matrix result = *this;
    result.SubMatrix(other);
    return result;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
    return *this = *this - other;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
    S21Matrix result = *this;
    result.MulMatrix(other);
    return result;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
    return *this = *this * other;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if(!(EqMatrix(other))) {
    if(matrix_ != nullptr) {
      destroy_();
    }
    rows_ = other.rows_;
    cols_ = other.cols_;
    try {
      S21Matrix_memory_allocate_();
    } catch (const bad_alloc& e) {
      cerr << "Memory allocation error";
      exit(1);
    }
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
          matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }

  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) {
    return this->EqMatrix(other);
}

double& S21Matrix::operator()(int row, int col) {
  if (row > rows_ || col > cols_ || row <= 0 || col <= 0) {
      throw invalid_argument("invalid argument value");
  }
  return matrix_[row - 1][col - 1];
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if(matrix_ == nullptr || other.matrix_ == nullptr) {
    throw invalid_argument("Matrix missing");
  }
  if(rows_ <= 0 || cols_ <= 0 || other.rows_ <= 0 || other.cols_ <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  int isEqual = 1;
  if(rows_ != other.rows_ || cols_ != other.cols_) {
    isEqual = 0;
  }
  if (isEqual) {
      for (int i = 0; i < rows_; i++) {
        for (int ii = 0; ii < cols_; ii++) {
      
          if(matrix_[i][ii] != other.matrix_[i][ii]) {
            isEqual = 0;
          }
        }
      }
  }

  return isEqual ? true : false;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if(matrix_ == nullptr || other.matrix_ == nullptr) {
    throw invalid_argument("Matrix missing");
  }
  if(rows_ <= 0 || cols_ <= 0 || other.rows_ <= 0 || other.cols_ <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  if(rows_ != other.rows_ || cols_ != other.cols_) {
    throw invalid_argument("The dimensions of the matrices are not equal");
  }

  for (int i = 0; i < rows_; i++) {
    for (int ii = 0; ii < cols_; ii++) {
      matrix_[i][ii] = matrix_[i][ii] + other.matrix_[i][ii];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if(matrix_ == nullptr || other.matrix_ == nullptr) {
    throw invalid_argument("Matrix missing");
  }
  if(rows_ <= 0 || cols_ <= 0 || other.rows_ <= 0 || other.cols_ <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  if(rows_ != other.rows_ || cols_ != other.cols_) {
    throw invalid_argument("The dimensions of the matrices are not equal");
  }

  for (int i = 0; i < rows_; i++) {
    for (int ii = 0; ii < cols_; ii++) {
      matrix_[i][ii] = matrix_[i][ii] - other.matrix_[i][ii];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if(matrix_ == nullptr) {
    throw invalid_argument("Matrix missing");
  }
  if(rows_ <= 0 || cols_ <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  for (int i = 0; i < rows_; i++) {
    for (int ii = 0; ii < cols_; ii++) {
      matrix_[i][ii] = matrix_[i][ii] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if(matrix_ == nullptr) {
    throw invalid_argument("Matrix missing");
  }
  if(rows_ <= 0 || cols_ <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  if (cols_ != other.rows_) {
    throw invalid_argument("the count of columns of the first matrix is not equal to the count of rows of the second matrix");
  }
  S21Matrix tmp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int ii = 0; ii < other.cols_; ii++) {
      tmp.matrix_[i][ii] = 0;
      for (int iii = 0; iii < other.rows_; iii++) {
        tmp.matrix_[i][ii] += matrix_[i][iii] * other.matrix_[iii][ii];
      }
    }
  }

  *this = move(tmp);
}

S21Matrix S21Matrix::Transpose() {
  if(matrix_ == nullptr) {
    throw invalid_argument("Matrix missing");
  }
  if(rows_ <= 0 || cols_ <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  S21Matrix tmp(*this);

  for (int i = 0; i < rows_; i++) {
    for (int ii = 0; ii < cols_; ii++) {
      tmp.matrix_[ii][i] = matrix_[i][ii];
    }
  }

  return tmp;
}

/// @brief Вычисление определителя матрицы.
/// @return определитель матрицы
double S21Matrix::Determinant() {
  if(matrix_ == nullptr) {
    throw invalid_argument("Matrix missing");
  }
  if(rows_ <= 0 || cols_ <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  if(rows_ != cols_) {
    throw invalid_argument("The matrix is not square.");
  }

  double tmp_result = 0;
  double tmp_determenant;

  if (rows_ == 1) {
    tmp_result = this->matrix_[0][0];
  } else {
    S21Matrix minor_matrix;
    for (int i = 0; i < rows_; i++) {
      minor_matrix = this->get_minor_(i, 0);
      tmp_determenant = minor_matrix.Determinant();

      if (i % 2) {
        tmp_result -= this->matrix_[i][0] * tmp_determenant;
      } else {
        tmp_result += this->matrix_[i][0] * tmp_determenant;
      }
    }
  }

  return tmp_result;
}

/// @brief
/// Вычисление матрицы алгебраических дополнений.
/// Алгебраическим дополнением элемента матрицы является значение минора
/// умноженное на - 1 ^ (i + j).
/// @return
/// результирующая матрица
S21Matrix S21Matrix::CalcComplements() {
  if(matrix_ == nullptr) {
    throw invalid_argument("Matrix missing");
  }
  if(rows_ <= 0 || cols_ <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  if(rows_ != cols_) {
    throw invalid_argument("The matrix is not square.");
  }
  
  S21Matrix result;
  result = get_matrix_of_minors_();
  
  for (int i = 0; i < rows_; i++) {
    for (int ii = 0; ii < cols_; ii++) {
      if (result.matrix_[i][ii] != 0.0) {
        result.matrix_[i][ii] *= pow(-1, i + ii);
      }
    }
  }

  return result;
}

/// @brief
/// Обратная матрица .
/// Матрицу A в степени - 1 называют обратной к квадратной матрице А, если
/// произведение этих матриц равняется единичной матрице.Обратной матрицы не
/// существует, если определитель равен 0. 
/// @return результирующая матрица
S21Matrix S21Matrix::InverseMatrix() {
    if (matrix_ == nullptr) {
        throw invalid_argument("Matrix missing");
    }
    if (rows_ <= 0 || cols_ <= 0) {
        throw invalid_argument("The count of matrix columns and rows must be greater than zero");
    }
    if (rows_ != cols_) {
        throw invalid_argument("The matrix is not square.");
    }
    
    double determinant = Determinant();
    S21Matrix complements_matrix;
    S21Matrix transpose_complements_matrix;
    if (0 == determinant) {
        throw invalid_argument("matrix for which calculations cannot be done");
    } else {
        complements_matrix = CalcComplements();
        transpose_complements_matrix = complements_matrix.Transpose();
        transpose_complements_matrix.MulNumber(1.0 / determinant);
    }

    return transpose_complements_matrix;
}

void S21Matrix::print_matrix() {
  for (int i = 0; i < rows_; i++) {
    for (int ii = 0; ii < cols_; ii++) {
      cout << matrix_[i][ii] << " ";
    }
    cout << endl;
  }
}

int S21Matrix::get_rows() {
  return rows_;
}

void S21Matrix::set_rows(int rows) {
  if (rows <= 0) {
    throw invalid_argument("The count of matrix rows must be greater than zero");
  }
  S21Matrix tmp = *this;
  this->destroy_();
  this->rows_ = rows;
  this->cols_ = tmp.cols_;
  this->S21Matrix_memory_allocate_();
  this->set_matrix(tmp.matrix_, tmp.rows_, tmp.cols_);
}

int S21Matrix::get_cols() {
  return cols_;
}

void S21Matrix::set_cols(int cols) {
  if (cols <= 0) {
    throw invalid_argument("The count of matrix rows must be greater than zero");
  }
  S21Matrix tmp = *this;
  this->destroy_();
  this->rows_ = tmp.rows_;
  this->cols_ = cols;
  this->S21Matrix_memory_allocate_();
  this->set_matrix(tmp.matrix_, tmp.rows_, tmp.cols_);
}

void S21Matrix::set_matrix(double* a, int size) {
  int index = 0;
  for(int i = 0; i < rows_; i++) {
    for(int ii = 0; ii < cols_; ii++) {
      if(index < size) {
        matrix_[i][ii] = a[index++];
      }
    }
  }
}

void S21Matrix::set_matrix(double** a, int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw invalid_argument("The count of matrix rows and columns must be greater than zero");
  }
  for(int i = 0; i < rows_; i++) {
    for(int ii = 0; ii < cols_; ii++) {
      if (rows > i && cols > ii) {
        matrix_[i][ii] = a[i][ii];
      }
    }
  }
}

S21Matrix operator*(double a, S21Matrix& matrix) {
  S21Matrix result = matrix;
  result.MulNumber(a);
  return result;
}

S21Matrix operator*(S21Matrix& matrix, double a) {
  S21Matrix result = matrix;
  result.MulNumber(a);
  return result;
}

S21Matrix& operator*=(double a, S21Matrix& matrix) {
  matrix.MulNumber(a);
  return matrix;
}

S21Matrix& operator*=(S21Matrix& matrix, double a) {
  matrix.MulNumber(a);
  return matrix;
}