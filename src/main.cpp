#include "s21_matrix_oop.h"

using namespace std;

int main() {
  S21Matrix matrix1(3);
  S21Matrix matrix2(3,3);

  double a[] = {3,2,3,4,5,6,7,8,9};
  matrix2.set_matrix(a, 9);
  double b = matrix2(3,3);

  matrix1 += matrix2;
  matrix2 *= 2;
  S21Matrix matrix3 = matrix1.InverseMatrix();
  matrix1.set_rows(2);
  matrix1.set_cols(2);
  matrix1.print_matrix();
  cout << endl;
  matrix2.print_matrix();
  cout << endl;
  matrix3.print_matrix();
  cout << endl;
  cout << b << endl;

  cout << (matrix1 == matrix2) << endl;

  return 0;
}