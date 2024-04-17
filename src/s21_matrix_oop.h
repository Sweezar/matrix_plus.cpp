#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <iostream>

class S21Matrix
{
private:
  int rows_, cols_;
  double **matrix_;
  void S21Matrix_memory_allocate_();
  void destroy_();
  S21Matrix get_minor_(int row, int col);
  S21Matrix get_matrix_of_minors_();

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
  friend S21Matrix operator*(double a, S21Matrix& matrix);
  friend S21Matrix operator*(S21Matrix& matrix, double a);
  S21Matrix& operator*=(const S21Matrix& other);
  friend S21Matrix& operator*=(double a, S21Matrix& matrix);
  friend S21Matrix& operator*=(S21Matrix& matrix, double a);
  S21Matrix& operator=(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  double& operator()(int row, int col);

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other); 
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  void print_matrix();
  int get_rows();
  void set_rows(int rows);
  int get_cols();
  void set_cols(int cols);
  void set_matrix(double* a, int size);
  void set_matrix(double** a, int rows, int cols);
};

S21Matrix operator*(double a, S21Matrix& matrix);
S21Matrix operator*(S21Matrix& matrix, double a);
S21Matrix& operator*=(double a, S21Matrix& matrix);
S21Matrix& operator*=(S21Matrix& matrix, double a);

#endif