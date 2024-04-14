#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <iostream>

class S21Matrix
{
private:
  int _rows, _cols;
  double **_matrix;
  void _S21Matrix_memory_allocate(int rows, int cols, double** matrix);

public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& o); // copy
  S21Matrix(S21Matrix&& o); // move
  ~S21Matrix();

  S21Matrix& operator+(const S21Matrix& o);
  S21Matrix& operator+=(const S21Matrix& o);
  S21Matrix& operator-(const S21Matrix& o);
  S21Matrix& operator-=(const S21Matrix& o);
  S21Matrix& operator*(const S21Matrix& o);
  S21Matrix& operator*=(const S21Matrix& o);
  S21Matrix& operator=(const S21Matrix& o);
  S21Matrix& operator==(const S21Matrix& o);
  int& operator()(int row, int col);
  int& operator()(int row, int col) const;

  bool eq_matrix(const S21Matrix& o);
  void sum_matrix(const S21Matrix& o); 
  void sub_matrix(const S21Matrix& o);


  void print_matrix();
};

#endif