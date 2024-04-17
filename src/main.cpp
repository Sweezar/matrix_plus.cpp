#include "s21_matrix_oop.h"

using namespace std;

int main() {
  S21Matrix matrix1(3);
  S21Matrix matrix2(3,3);

  double a[] = {3,2,3,4,5,6,7,8,9};
  matrix2.fill(a, 9);

  matrix1.SumMatrix(matrix2);
  matrix2.MulMatrix(matrix1);
  S21Matrix matrix3 = matrix1.InverseMatrix();
  matrix1.print_matrix();
  cout << endl;
  matrix2.print_matrix();
  cout << endl;
  matrix3.print_matrix();
  cout << endl;

  cout << matrix1.EqMatrix(matrix2) << endl;

  return 0;
}