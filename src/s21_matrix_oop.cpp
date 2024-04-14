#include "s21_matrix_oop.h"

using namespace std;

void _S21Matrix_memory_allocate(int rows, int cols, double** matrix) {
  if(rows <= 0 || cols <= 0) {
    throw invalid_argument("Количество столбцов и строк матрицы должны быть больше нуля");
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

S21Matrix::S21Matrix() : _rows(3), _cols(3) {
  try {
    _S21Matrix_memory_allocate(_rows, _cols, _matrix);
  } catch (const bad_alloc& e) {
    cerr << "Ошибка выделения памяти";
    exit(1);
  }
}

S21Matrix::S21Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
  try {
    _S21Matrix_memory_allocate(_rows, _cols, _matrix);
  } catch (const bad_alloc& e) {
    cerr << "Ошибка выделения памяти";
    exit(1);
  }
}

S21Matrix::S21Matrix(const S21Matrix& o) : _rows(o._rows), _cols(o._cols) {
  try {
    _S21Matrix_memory_allocate(_rows, _cols, _matrix);
  } catch (const bad_alloc& e) {
    cerr << "Ошибка выделения памяти";
    exit(1);
  }

  for(int i = 0; i < _rows; i++) {
    memcpy(_matrix[i], o._matrix[i], _cols * sizeof(double));
  }
}

S21Matrix::S21Matrix(S21Matrix&& o) : _rows(o._rows), _cols(o._cols), _matrix(o._matrix) {
  o._rows = 0;
  o._cols = 0;
  o._matrix = nullptr;
}

S21Matrix::~S21Matrix() {
  for(int i = 0; i < _rows; i++) {
    delete[] _matrix[i];
  }
  delete[] _matrix;
}

void S21Matrix::sum_matrix(const S21Matrix& o) {
  if(_matrix == nullptr || o._matrix == nullptr) {
    throw invalid_argument("Матрица отсутствует");
  }
  if(_rows <= 0 || _cols <= 0 || o._rows <= 0 || o._cols <= 0) {
    throw invalid_argument("Количество столбцов и строк матрицы должны быть больше нуля");
  }
  if(_rows != o._rows || _cols != o._cols) {
    throw invalid_argument("размерность матриц не равна");
  }

  for (int i = 0; i < _rows; i++) {
    for (int ii = 0; ii < _cols; ii++) {
      _matrix[i][ii] = _matrix[i][ii] + o._matrix[i][ii];
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