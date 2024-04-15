#include "s21_matrix_oop.h"

using namespace std;

void S21Matrix::_S21Matrix_memory_allocate(int rows, int cols, double**& matrix) {
  if(rows <= 0 || cols <= 0) {
    throw invalid_argument("The count of matrix columns and rows must be greater than zero");
  }
  matrix = new double*[rows]();
  if(!matrix) {
    throw bad_alloc();
  }

  for(int i = 0; i < rows; i++) {
    matrix[i] = new double[cols]();
    if(!matrix[i]) {
      for (int j = 0; j < i; j++) {
        delete[] matrix[j];
      }
      delete[] matrix;
      throw bad_alloc();
    }
  }
}

void S21Matrix::_destroy() {
  for(int i = 0; i < _rows; i++) {
    delete[] _matrix[i];
  }
  delete[] _matrix;
}

S21Matrix::S21Matrix() : _rows(3), _cols(3) {
  try {
    _S21Matrix_memory_allocate(_rows, _cols, _matrix);
  } catch (const bad_alloc& e) {
    cerr << "Memory allocation error";
    exit(1);
  }
}

S21Matrix::S21Matrix(int rows) : _rows(rows), _cols(rows) {
  try {
    _S21Matrix_memory_allocate(_rows, _cols, _matrix);
  } catch (const bad_alloc& e) {
    cerr << "Memory allocation error";
    exit(1);
  }
}

S21Matrix::S21Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
  try {
    _S21Matrix_memory_allocate(_rows, _cols, _matrix);
  } catch (const bad_alloc& e) {
    cerr << "Memory allocation error";
    exit(1);
  }
}

// copy
S21Matrix::S21Matrix(const S21Matrix& other) : _rows(other._rows), _cols(other._cols) {
  try {
    _S21Matrix_memory_allocate(_rows, _cols, _matrix);
  } catch (const bad_alloc& e) {
    cerr << "Memory allocation error";
    exit(1);
  }

  for(int i = 0; i < _rows; i++) {
    memcpy(_matrix[i], other._matrix[i], _cols * sizeof(double));
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
    _destroy();

    _rows = other._rows;
    _cols = other._cols;
    try {
      _S21Matrix_memory_allocate(_rows, _cols, _matrix);
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
  for (int i = 0; i < _rows; i++) {
    for (int ii = 0; ii < _cols; ii++) {
      
      if(_matrix[i][ii] != other._matrix[i][ii]) {
        isEqual = 0;
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