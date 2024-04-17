#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <iostream>

class S21Matrix
{
private:
  int _rows, _cols;
  double **_matrix;
  void _S21Matrix_memory_allocate();
  void _destroy();
  S21Matrix _get_minor(int row, int col);
  S21Matrix _get_matrix_of_minors();

public:
  S21Matrix();
  S21Matrix(int rows);
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other); // copy
  S21Matrix(S21Matrix&& other); // move
  ~S21Matrix();

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  double& operator()(int row, int col);
  double& operator()(int row, int col) const;

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other); 
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  void fill(double* a, int size);
  void print_matrix();

};

#endif