#include "s21_matrix_oop.h"
#include <cmath> 

using namespace std;

/// @brief Выделяет память для матрицы
void S21Matrix::_S21Matrix_memory_allocate() {
  if(_rows <= 0 || _cols <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  _matrix = new double*[_rows]();
  if(!_matrix) {
    throw bad_alloc();
  }

  for(int i = 0; i < _rows; i++) {
    _matrix[i] = new double[_cols]();
    if(!_matrix[i]) {
      for (int j = 0; j < i; j++) {
        delete[] _matrix[j];
      }
      delete[] _matrix;
      throw bad_alloc();
    }
  }
}

/// @brief освобождение памяти под матрицу
void S21Matrix::_destroy() {
  for(int i = 0; i < _rows; i++) {
    delete[] _matrix[i];
  }
  delete[] _matrix;
}

/// @brief Возвращает минор матрицы
/// @param row строка для которой вычисляется минор 
/// @param col столбец для которого вычисляется минор
/// @return результирующую матрицу
S21Matrix S21Matrix::_get_minor(int row, int col) {
  S21Matrix tmp(_rows - 1, _cols - 1);
  if (_rows > 1) {
    for (int i = 0; i < _rows; i++) {
      for (int ii = 0; ii < _cols; ii++) {
        if (i < row && ii < col) {
          tmp._matrix[i][ii] = _matrix[i][ii];
        } else if (i > row && ii < col) {
          tmp._matrix[i - 1][ii] = _matrix[i][ii];
        } else if (i < row && ii > col) {
          tmp._matrix[i][ii - 1] = _matrix[i][ii];
        } else if (i > row && ii > col) {
          tmp._matrix[i - 1][ii - 1] = _matrix[i][ii];
        }
      }
    }
  }
  return tmp;
}

/// @brief Получить матрицу миноров
/// @return матрицу миноров
S21Matrix S21Matrix::_get_matrix_of_minors() {
  S21Matrix result(_rows, _cols);
  S21Matrix minor_matrix;

  for (int i = 0; i < _rows; i++) {
    for (int ii = 0; ii < _cols; ii++) {
      minor_matrix = _get_minor(i, ii);
      result._matrix[i][ii] = minor_matrix.Determinant();
    }
  }

  return result;
}

S21Matrix::S21Matrix() : _rows(3), _cols(3) {
  try {
    _S21Matrix_memory_allocate();
  } catch (const bad_alloc& e) {
    cerr << "Memory allocation error";
    exit(1);
  }
}

S21Matrix::S21Matrix(int rows) : _rows(rows), _cols(rows) {
  try {
    _S21Matrix_memory_allocate();
  } catch (const bad_alloc& e) {
    cerr << "Memory allocation error";
    exit(1);
  }
}

S21Matrix::S21Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
  try {
    _S21Matrix_memory_allocate();
  } catch (const bad_alloc& e) {
    cerr << "Memory allocation error";
    exit(1);
  }
}

// copy
S21Matrix::S21Matrix(const S21Matrix& other) : _rows(other._rows), _cols(other._cols) {
  try {
    _S21Matrix_memory_allocate();
  } catch (const bad_alloc& e) {
    cerr << "Memory allocation error";
    exit(1);
  }

  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
        _matrix[i][j] = other._matrix[i][j];
    }
  }
}

// move
S21Matrix::S21Matrix(S21Matrix&& other) {
  _rows = other._rows;
  _cols = other._cols;
  _matrix = other._matrix;

  other._rows = 0;
  other._cols = 0;
  other._matrix = nullptr;
}

S21Matrix::~S21Matrix() {
  _destroy();
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if(!(EqMatrix(other))) {
    if(_matrix != nullptr) {
      _destroy();
    }
    _rows = other._rows;
    _cols = other._cols;
    try {
      _S21Matrix_memory_allocate();
    } catch (const bad_alloc& e) {
      cerr << "Memory allocation error";
      exit(1);
    }
    for (int i = 0; i < _rows; ++i) {
      for (int j = 0; j < _cols; ++j) {
          _matrix[i][j] = other._matrix[i][j];
      }
    }
  }

  return *this;
}


bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if(_matrix == nullptr || other._matrix == nullptr) {
    throw invalid_argument("Matrix missing");
  }
  if(_rows <= 0 || _cols <= 0 || other._rows <= 0 || other._cols <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  int isEqual = 1;
  if(_rows != other._rows || _cols != other._cols) {
    isEqual = 0;
  }
  if (isEqual) {
      for (int i = 0; i < _rows; i++) {
        for (int ii = 0; ii < _cols; ii++) {
      
          if(_matrix[i][ii] != other._matrix[i][ii]) {
            isEqual = 0;
          }
        }
      }
  }

  return isEqual ? true : false;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if(_matrix == nullptr || other._matrix == nullptr) {
    throw invalid_argument("Matrix missing");
  }
  if(_rows <= 0 || _cols <= 0 || other._rows <= 0 || other._cols <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  if(_rows != other._rows || _cols != other._cols) {
    throw invalid_argument("The dimensions of the matrices are not equal");
  }

  for (int i = 0; i < _rows; i++) {
    for (int ii = 0; ii < _cols; ii++) {
      _matrix[i][ii] = _matrix[i][ii] + other._matrix[i][ii];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if(_matrix == nullptr || other._matrix == nullptr) {
    throw invalid_argument("Matrix missing");
  }
  if(_rows <= 0 || _cols <= 0 || other._rows <= 0 || other._cols <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  if(_rows != other._rows || _cols != other._cols) {
    throw invalid_argument("The dimensions of the matrices are not equal");
  }

  for (int i = 0; i < _rows; i++) {
    for (int ii = 0; ii < _cols; ii++) {
      _matrix[i][ii] = _matrix[i][ii] - other._matrix[i][ii];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if(_matrix == nullptr) {
    throw invalid_argument("Matrix missing");
  }
  if(_rows <= 0 || _cols <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  for (int i = 0; i < _rows; i++) {
    for (int ii = 0; ii < _cols; ii++) {
      _matrix[i][ii] = _matrix[i][ii] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if(_matrix == nullptr) {
    throw invalid_argument("Matrix missing");
  }
  if(_rows <= 0 || _cols <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  if (_cols != other._rows) {
    throw invalid_argument("the count of columns of the first matrix is ​​not equal to the count of rows of the second matrix");
  }
  S21Matrix tmp(_rows, other._cols);
  for (int i = 0; i < _rows; i++) {
    for (int ii = 0; ii < other._cols; ii++) {
      tmp._matrix[i][ii] = 0;
      for (int iii = 0; iii < other._rows; iii++) {
        tmp._matrix[i][ii] += _matrix[i][iii] * other._matrix[iii][ii];
      }
    }
  }

  *this = move(tmp);
}

S21Matrix S21Matrix::Transpose() {
  if(_matrix == nullptr) {
    throw invalid_argument("Matrix missing");
  }
  if(_rows <= 0 || _cols <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  S21Matrix tmp(*this);

  for (int i = 0; i < _rows; i++) {
    for (int ii = 0; ii < _cols; ii++) {
      tmp._matrix[ii][i] = _matrix[i][ii];
    }
  }

  return tmp;
}

/// @brief Вычисление определителя матрицы.
/// @return определитель матрицы
double S21Matrix::Determinant() {
  if(_matrix == nullptr) {
    throw invalid_argument("Matrix missing");
  }
  if(_rows <= 0 || _cols <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  if(_rows != _cols) {
    throw invalid_argument("The matrix is ​​not square.");
  }

  double tmp_result = 0;
  double tmp_determenant;

  if (_rows == 1) {
    tmp_result = this->_matrix[0][0];
  } else {
    S21Matrix minor_matrix;
    for (int i = 0; i < _rows; i++) {
      minor_matrix = this->_get_minor(i, 0);
      tmp_determenant = minor_matrix.Determinant();

      if (i % 2) {
        tmp_result -= this->_matrix[i][0] * tmp_determenant;
      } else {
        tmp_result += this->_matrix[i][0] * tmp_determenant;
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
  if(_matrix == nullptr) {
    throw invalid_argument("Matrix missing");
  }
  if(_rows <= 0 || _cols <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  if(_rows != _cols) {
    throw invalid_argument("The matrix is ​​not square.");
  }
  
  S21Matrix result;
  result = _get_matrix_of_minors();
  
  for (int i = 0; i < _rows; i++) {
    for (int ii = 0; ii < _cols; ii++) {
      if (result._matrix[i][ii] != 0.0) {
        result._matrix[i][ii] *= pow(-1, i + ii);
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
    if (_matrix == nullptr) {
        throw invalid_argument("Matrix missing");
    }
    if (_rows <= 0 || _cols <= 0) {
        throw invalid_argument("The count of matrix columns and rows must be greater than zero");
    }
    if (_rows != _cols) {
        throw invalid_argument("The matrix is ​​not square.");
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

void S21Matrix::fill(double* a, int size) {
  int index = 0;
  for(int i = 0; i < _rows; i++) {
    for(int ii = 0; ii < _cols; ii++) {
      if(index < size) {
        _matrix[i][ii] = a[index++];
      }
    }
  }
}

void S21Matrix::print_matrix() {
  for (int i = 0; i < _rows; i++) {
    for (int ii = 0; ii < _cols; ii++) {
      cout << _matrix[i][ii] << " ";
    }
    cout << endl;
  }
}