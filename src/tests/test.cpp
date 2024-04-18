#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

using namespace std;

TEST(TestMatrixConstructors, Subtest_1) {
  // Arrange
  S21Matrix matrix;

  // Act

  // Assert
  ASSERT_GT(matrix.get_rows(), 0);
  ASSERT_GT(matrix.get_cols(), 0);
}

TEST(TestMatrixConstructors, Subtest_2) {
  // Arrange
  S21Matrix matrix(4, 4);

  // Act

  // Assert
  ASSERT_EQ(matrix.get_rows(), 4);
  ASSERT_EQ(matrix.get_cols(), 4);
}

TEST(TestMatrixConstructors, Subtest_3) {
  // Arrange
  S21Matrix matrix(5);

  // Act

  // Assert
  ASSERT_TRUE(matrix.get_rows() == 5);
  ASSERT_TRUE(matrix.get_cols() == 5);
}

TEST(TestMatrixConstructors, Subtest_4) {
  // Arrange
  S21Matrix matrix(2, 4);

  // Act

  // Assert
  ASSERT_TRUE(matrix.get_rows() == 2);
  ASSERT_TRUE(matrix.get_cols() == 4);
}

TEST(TestMatrixConstructors, Subtest_5) {
  ASSERT_THROW(S21Matrix matrix(0, 0), invalid_argument);
}

TEST(TestMatrixConstructors, Subtest_6) {
  ASSERT_THROW(S21Matrix matrix(-2, 0), invalid_argument);
}

// COPY
TEST(TestMatrixConstructors, Subtest_7) {
  // Arrange
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(matrix1);

  // Act

  // Assert
  ASSERT_EQ(matrix1.get_rows(), 2);
  ASSERT_EQ(matrix1.get_cols(), 4);
  ASSERT_EQ(matrix2.get_rows(), 2);
  ASSERT_EQ(matrix2.get_cols(), 4);
}

// MOVE
TEST(TestMatrixConstructors, Subtest_8) {
  // Arrange
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(move(matrix1));

  // Act

  // Assert
  ASSERT_EQ(matrix1.get_rows(), 0);
  ASSERT_EQ(matrix1.get_cols(), 0);
  ASSERT_EQ(matrix2.get_rows(), 2);
  ASSERT_EQ(matrix2.get_cols(), 4);
}

TEST(TestMatrixOperators, Subtest_operator_plus_1) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(matrix1);
  S21Matrix result;

  // Act
  matrix1.set_matrix(arr, 8);
  result = matrix1 + matrix2;

  // Assert
  ASSERT_EQ(matrix1.EqMatrix(result), true);
}

TEST(TestMatrixOperators, Subtest_operator_plus_2) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(matrix1);
  S21Matrix result;

  // Act
  matrix1.set_matrix(arr, 8);
  matrix2.set_matrix(arr, 8);
  result = matrix1 + matrix2;

  // Assert
  ASSERT_EQ(result(0, 0), matrix1(0, 0) + matrix2(0, 0));
  ASSERT_EQ(result(0, 2), matrix1(0, 2) + matrix2(0, 2));
  ASSERT_EQ(result(1, 3), matrix1(1, 3) + matrix2(1, 3));
}

TEST(TestMatrixOperators, Subtest_operator_plus_3) {
  // Arrange
  double arr[] = {1.0001, 2, 3.1415, 4, 5, 6, 7, -8.4};
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(matrix1);
  S21Matrix result;

  // Act
  matrix1.set_matrix(arr, 8);
  matrix2.set_matrix(arr, 8);
  result = matrix1 + matrix2;

  // Assert
  ASSERT_EQ(result(0, 0), matrix1(0, 0) + matrix2(0, 0));
  ASSERT_EQ(result(0, 2), matrix1(0, 2) + matrix2(0, 2));
  ASSERT_EQ(result(1, 3), matrix1(1, 3) + matrix2(1, 3));
}

TEST(TestMatrixOperators, Subtest_operator_plus_4) {
  // Arrange
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(4);

  // Act

  // Assert
  ASSERT_THROW(matrix1 + matrix2, invalid_argument);
}

TEST(TestMatrixOperators, Subtest_operator_plus_eq_1) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(matrix1);

  // Act
  matrix2.set_matrix(arr, 8);
  matrix1 += matrix2;

  // Assert
  ASSERT_EQ(matrix1.EqMatrix(matrix2), true);
}

TEST(TestMatrixOperators, Subtest_operator_plus_eq_2) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(matrix1);

  // Act
  matrix1.set_matrix(arr, 8);
  matrix2.set_matrix(arr, 8);
  matrix1 += matrix2;

  // Assert
  ASSERT_EQ(matrix1(0, 0), matrix2(0, 0) * 2);
  ASSERT_EQ(matrix1(0, 2), matrix2(0, 2) * 2);
  ASSERT_EQ(matrix1(1, 3), matrix2(1, 3) * 2);
}

TEST(TestMatrixOperators, Subtest_operator_plus_eq_3) {
  // Arrange
  double arr[] = {1.0001, 2, 3.1415, 4, 5, 6, 7, -8.4};
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(matrix1);
  S21Matrix result;

  // Act
  matrix1.set_matrix(arr, 8);
  matrix2.set_matrix(arr, 8);
  matrix1 += matrix2;

  // Assert
  ASSERT_EQ(matrix1(0, 0), matrix2(0, 0) * 2);
  ASSERT_EQ(matrix1(0, 2), matrix2(0, 2) * 2);
  ASSERT_EQ(matrix1(1, 3), matrix2(1, 3) * 2);
}

TEST(TestMatrixOperators, Subtest_operator_plus_eq_4) {
  // Arrange
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(4);

  // Act

  // Assert
  ASSERT_THROW(matrix1 += matrix2, invalid_argument);
}

// MINUS //

TEST(TestMatrixOperators, Subtest_operator_minus_1) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(matrix1);
  S21Matrix result;

  // Act
  matrix1.set_matrix(arr, 8);
  result = matrix1 - matrix2;

  // Assert
  ASSERT_EQ(matrix1.EqMatrix(result), true);
}

TEST(TestMatrixOperators, Subtest_operator_minus_2) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(matrix1);
  S21Matrix result;

  // Act
  matrix1.set_matrix(arr, 8);
  matrix2.set_matrix(arr, 8);
  result = matrix1 - matrix2;

  // Assert
  ASSERT_EQ(result(0, 0), matrix1(0, 0) - matrix2(0, 0));
  ASSERT_EQ(result(0, 2), matrix1(0, 2) - matrix2(0, 2));
  ASSERT_EQ(result(1, 3), matrix1(1, 3) - matrix2(1, 3));
}

TEST(TestMatrixOperators, Subtest_operator_minus_3) {
  // Arrange
  double arr[] = {1.0001, 2, 3.1415, 4, 5, 6, 7, -8.4};
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(matrix1);
  S21Matrix result;

  // Act
  matrix1.set_matrix(arr, 8);
  matrix2.set_matrix(arr, 8);
  result = matrix1 - matrix2;

  // Assert
  ASSERT_EQ(result(0, 0), matrix1(0, 0) - matrix2(0, 0));
  ASSERT_EQ(result(0, 2), matrix1(0, 2) - matrix2(0, 2));
  ASSERT_EQ(result(1, 3), matrix1(1, 3) - matrix2(1, 3));
}

TEST(TestMatrixOperators, Subtest_operator_minus_4) {
  // Arrange
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(4);

  // Act

  // Assert
  ASSERT_THROW(matrix1 - matrix2, invalid_argument);
}

TEST(TestMatrixOperators, Subtest_operator_minus_eq_1) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(matrix1);

  // Act
  matrix2.set_matrix(arr, 8);
  matrix1 -= matrix2;

  // Assert
  ASSERT_EQ(matrix1(0, 0), -1);
  ASSERT_EQ(matrix1(1, 1), -6);
  ASSERT_EQ(matrix1(1, 3), -8);
}

TEST(TestMatrixOperators, Subtest_operator_minus_eq_2) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(matrix1);

  // Act
  matrix1.set_matrix(arr, 8);
  matrix2.set_matrix(arr, 8);
  matrix1 -= matrix2;

  // Assert
  ASSERT_EQ(matrix1(0, 0), 0);
  ASSERT_EQ(matrix1(0, 2), 0);
  ASSERT_EQ(matrix1(1, 3), 0);
}

TEST(TestMatrixOperators, Subtest_operator_minus_eq_3) {
  // Arrange
  double arr[] = {1.0001, 2, 3.1415, 4, 5, 6, 7, -8.4};
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(matrix1);
  S21Matrix result;

  // Act
  matrix1.set_matrix(arr, 8);
  matrix2.set_matrix(arr, 8);
  matrix1 -= matrix2;

  // Assert
  ASSERT_EQ(matrix1(0, 0), 0);
  ASSERT_EQ(matrix1(0, 2), 0);
  ASSERT_EQ(matrix1(1, 3), 0);
}

TEST(TestMatrixOperators, Subtest_operator_minus_eq_4) {
  // Arrange
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(4);

  // Act

  // Assert
  ASSERT_THROW(matrix1 -= matrix2, invalid_argument);
}

// MULNUMBER

TEST(TestMatrixOperators, Subtest_operator_mulnumber_1) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  double num = 3.4;
  S21Matrix matrix1(2, 4);
  S21Matrix result;

  // Act
  matrix1.set_matrix(arr, 8);
  result = matrix1 * num;

  // Assert
  ASSERT_EQ(result(0, 0), matrix1(0, 0) * num);
  ASSERT_EQ(result(0, 2), matrix1(0, 2) * num);
  ASSERT_EQ(result(1, 3), matrix1(1, 3) * num);
}

TEST(TestMatrixOperators, Subtest_operator_mulnumber_2) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  double num = -3.4;
  S21Matrix matrix1(2, 4);
  S21Matrix result;

  // Act
  matrix1.set_matrix(arr, 8);
  result = matrix1 * num;

  // Assert
  ASSERT_EQ(result(0, 0), matrix1(0, 0) * num);
  ASSERT_EQ(result(0, 2), matrix1(0, 2) * num);
  ASSERT_EQ(result(1, 3), matrix1(1, 3) * num);
}

TEST(TestMatrixOperators, Subtest_operator_mulnumber_3) {
  // Arrange
  double arr[] = {1.0001, 2, 3.1415, 4, 5, 6, 7, -8.4};
  double num = 0;
  S21Matrix matrix1(2, 4);
  S21Matrix result;

  // Act
  matrix1.set_matrix(arr, 8);
  result = matrix1 * num;

  // Assert
  ASSERT_EQ(result(0, 0), matrix1(0, 0) * num);
  ASSERT_EQ(result(0, 2), matrix1(0, 2) * num);
  ASSERT_EQ(result(1, 3), matrix1(1, 3) * num);
}

TEST(TestMatrixOperators, Subtest_operator_mulnumber_4) {
  // Arrange
  double arr[] = {1.0001, 2, 3.1415, 4, 5, 6, 7, -8.4};
  double num = 0;
  S21Matrix matrix1(2, 4);
  S21Matrix result;

  // Act
  matrix1.set_matrix(arr, 8);
  result = num * matrix1;

  // Assert
  ASSERT_EQ(result(0, 0), matrix1(0, 0) * num);
  ASSERT_EQ(result(0, 2), matrix1(0, 2) * num);
  ASSERT_EQ(result(1, 3), matrix1(1, 3) * num);
}

TEST(TestMatrixOperators, Subtest_operator_mulnumber_eq_1) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  double num = 3.4;
  S21Matrix matrix1(2, 4);

  // Act
  matrix1.set_matrix(arr, 8);
  matrix1 *= num;

  // Assert
  ASSERT_EQ(matrix1(0, 0), arr[0] * num);
  ASSERT_EQ(matrix1(0, 2), arr[2] * num);
  ASSERT_EQ(matrix1(1, 3), arr[7] * num);
}

TEST(TestMatrixOperators, Subtest_operator_mulnumber_eq_2) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  double num = -3.4;
  S21Matrix matrix1(2, 4);

  // Act
  matrix1.set_matrix(arr, 8);
  matrix1 *= num;

  // Assert
  ASSERT_EQ(matrix1(0, 0), arr[0] * num);
  ASSERT_EQ(matrix1(0, 2), arr[2] * num);
  ASSERT_EQ(matrix1(1, 3), arr[7] * num);
}

TEST(TestMatrixOperators, Subtest_operator_mulnumber_eq_3) {
  // Arrange
  double arr[] = {1.0001, 2, 3.1415, 4, 5, 6, 7, -8.4};
  double num = 0;
  S21Matrix matrix1(2, 4);

  // Act
  matrix1.set_matrix(arr, 8);
  matrix1 *= num;

  // Assert
  ASSERT_EQ(matrix1(0, 0), arr[0] * num);
  ASSERT_EQ(matrix1(0, 2), arr[2] * num);
  ASSERT_EQ(matrix1(1, 3), arr[7] * num);
}

// MULMATRIX

TEST(TestMatrixOperators, Subtest_operator_mulmatrix_1) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  double ref[] = {13, 16, 19, 4,  5,  27, 34, 41, 12, 15,
                  41, 52, 63, 20, 25, 55, 70, 85, 28, 35};
  S21Matrix matrix1(4, 2);
  S21Matrix matrix2(2, 5);
  S21Matrix result;
  S21Matrix ref_matrix(4, 5);

  // Act
  matrix1.set_matrix(arr, 8);
  matrix2.set_matrix(arr, 8);
  result = matrix1 * matrix2;
  ref_matrix.set_matrix(ref, 20);

  // Assert
  ASSERT_TRUE(ref_matrix == result);
}

TEST(TestMatrixOperators, Subtest_operator_mulmatrix_2) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  double ref[] = {11, 14, 17, 20, 23, 30, 37, 44,
                  35, 46, 57, 68, 47, 62, 77, 92};
  S21Matrix matrix1(4, 2);
  S21Matrix matrix2(2, 4);
  S21Matrix result;
  S21Matrix ref_matrix(4, 4);

  // Act
  matrix1.set_matrix(arr, 8);
  matrix2.set_matrix(arr, 8);
  result = matrix1 * matrix2;
  ref_matrix.set_matrix(ref, 20);

  // Assert
  ASSERT_TRUE(ref_matrix == result);
}

TEST(TestMatrixOperators, Subtest_operator_mulmatrix_3) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  double ref[] = {30, 36, 15, 66, 81, 42, 39, 54, 69};
  S21Matrix matrix1(3);
  S21Matrix matrix2(3);
  S21Matrix result;
  S21Matrix ref_matrix(3);

  // Act
  matrix1.set_matrix(arr, 8);
  matrix2.set_matrix(arr, 8);
  result = matrix1 * matrix2;
  ref_matrix.set_matrix(ref, 20);

  // Assert
  ASSERT_TRUE(ref_matrix == result);
}

TEST(TestMatrixOperators, Subtest_operator_mulmatrix_4) {
  // Arrange
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(2, 4);

  // Act

  // Assert
  ASSERT_THROW(matrix1 * matrix2, invalid_argument);
}

TEST(TestMatrixOperators, Subtest_operator_mulmatrix_eq_1) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  double ref[] = {13, 16, 19, 4,  5,  27, 34, 41, 12, 15,
                  41, 52, 63, 20, 25, 55, 70, 85, 28, 35};
  S21Matrix matrix1(4, 2);
  S21Matrix matrix2(2, 5);
  S21Matrix ref_matrix(4, 5);

  // Act
  matrix1.set_matrix(arr, 8);
  matrix2.set_matrix(arr, 8);
  matrix1 *= matrix2;
  ref_matrix.set_matrix(ref, 20);

  // Assert
  ASSERT_TRUE(ref_matrix == matrix1);
}

TEST(TestMatrixOperators, Subtest_operator_mulmatrix_eq_2) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  double ref[] = {11, 14, 17, 20, 23, 30, 37, 44,
                  35, 46, 57, 68, 47, 62, 77, 92};
  S21Matrix matrix1(4, 2);
  S21Matrix matrix2(2, 4);
  S21Matrix ref_matrix(4, 4);

  // Act
  matrix1.set_matrix(arr, 8);
  matrix2.set_matrix(arr, 8);
  matrix1 *= matrix2;
  ref_matrix.set_matrix(ref, 20);

  // Assert
  ASSERT_TRUE(ref_matrix == matrix1);
}

TEST(TestMatrixOperators, Subtest_operator_mulmatrix_eq_3) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  double ref[] = {30, 36, 15, 66, 81, 42, 39, 54, 69};
  S21Matrix matrix1(3);
  S21Matrix matrix2(3);
  S21Matrix ref_matrix(3);

  // Act
  matrix1.set_matrix(arr, 8);
  matrix2.set_matrix(arr, 8);
  matrix1 *= matrix2;
  ref_matrix.set_matrix(ref, 20);

  // Assert
  ASSERT_TRUE(ref_matrix == matrix1);
}

TEST(TestMatrixOperators, Subtest_operator_mulmatrix_eq_4) {
  // Arrange
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(2, 4);

  // Act

  // Assert
  ASSERT_THROW(matrix1 *= matrix2, invalid_argument);
}

// EqMatrix

TEST(TestMatrixEqMatrix, Subtest_EqMatrix_1) {
  // Arrange
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(2, 4);

  // Act

  // Assert
  ASSERT_EQ(matrix1.EqMatrix(matrix2), true);
}

TEST(TestMatrixEqMatrix, Subtest_EqMatrix_2) {
  // Arrange
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(2, 4);
  double arr[] = {1, 2};

  // Act
  matrix1.set_matrix(arr, 2);

  // Assert
  ASSERT_EQ(matrix1.EqMatrix(matrix2), false);
}

TEST(TestMatrixEqMatrix, Subtest_EqMatrix_3) {
  // Arrange
  S21Matrix matrix1(2, 4);
  S21Matrix matrix2(4, 2);

  // Act

  // Assert
  ASSERT_EQ(matrix1.EqMatrix(matrix2), false);
}

// Transpose

TEST(TestMatrixTranspose, Subtest_Transpose_1) {
  // Arrange
  S21Matrix matrix1(4, 2);
  S21Matrix result;

  // Act
  result = matrix1.Transpose();

  // Assert
  ASSERT_EQ(result.get_rows(), 2);
  ASSERT_EQ(result.get_cols(), 4);
}

TEST(TestMatrixTranspose, Subtest_Transpose_2) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  double arr2[] = {1, 3, 5, 7, 2, 4, 6, 8};
  S21Matrix matrix1(4, 2);
  S21Matrix result;
  S21Matrix ref(2, 4);

  // Act
  matrix1.set_matrix(arr, 8);
  ref.set_matrix(arr2, 8);
  result = matrix1.Transpose();

  // Assert
  ASSERT_TRUE(result == ref);
}

TEST(TestMatrixTranspose, Subtest_Transpose_3) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  double arr2[] = {1, 4, 7, 2, 5, 8, 3, 6};
  S21Matrix matrix1(3);
  S21Matrix result;
  S21Matrix ref(3);

  // Act
  matrix1.set_matrix(arr, 8);
  ref.set_matrix(arr2, 8);
  result = matrix1.Transpose();

  // Assert
  ASSERT_TRUE(result == ref);
}

// CalcComplements

TEST(TestMatrixCalcComplements, Subtest_CalcComplements_1) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  double arr2[] = {-48, 42, -3, 24, -21, 6, -3, 6, -3};
  S21Matrix matrix1(3);
  S21Matrix result;
  S21Matrix ref(3);

  // Act
  matrix1.set_matrix(arr, 8);
  ref.set_matrix(arr2, 9);
  result = matrix1.CalcComplements();

  // Assert
  ASSERT_TRUE(result == ref);
}

TEST(TestMatrixCalcComplements, Subtest_CalcComplements_2) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  S21Matrix matrix1(4, 3);

  // Act
  matrix1.set_matrix(arr, 9);

  // Assert
  ASSERT_THROW(matrix1.CalcComplements(), invalid_argument);
}

// DETERMINANT

TEST(TestMatrixDeterminant, Subtest_Determinant_1) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  S21Matrix matrix1(4, 3);

  // Act
  matrix1.set_matrix(arr, 9);

  // Assert
  ASSERT_THROW(matrix1.Determinant(), invalid_argument);
}

TEST(TestMatrixDeterminant, Subtest_Determinant_2) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  S21Matrix matrix1(3, 3);
  double ref = 0;

  // Act
  matrix1.set_matrix(arr, 9);

  // Assert
  ASSERT_EQ(matrix1.Determinant(), ref);
}

TEST(TestMatrixDeterminant, Subtest_Determinant_3) {
  // Arrange
  double arr[] = {3, 2, 3, 4, 5, 6, 7, 8, 9};
  S21Matrix matrix1(3, 3);
  double ref = -6;

  // Act
  matrix1.set_matrix(arr, 9);

  // Assert
  ASSERT_EQ(matrix1.Determinant(), ref);
}

TEST(TestMatrixDeterminant, Subtest_Determinant_4) {
  // Arrange
  double arr[] = {3, -2, 3, -4, 5, 6, 7, 8, -9};
  S21Matrix matrix1(3, 3);
  double ref = -492;

  // Act
  matrix1.set_matrix(arr, 9);

  // Assert
  ASSERT_EQ(matrix1.Determinant(), ref);
}

// InverseMatrix

TEST(TestMatrixInverseMatrix, Subtest_InverseMatrix_1) {
  // Arrange
  double arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  S21Matrix matrix1(3, 3);

  // Act
  matrix1.set_matrix(arr, 9);

  // Assert
  ASSERT_THROW(matrix1.InverseMatrix(), invalid_argument);  // determinant == 0;
}

TEST(TestMatrixInverseMatrix, Subtest_InverseMatrix_2) {
  // Arrange
  double arr[] = {3, 2, 3, 4, 5, 6, 7, 8, 9};
  S21Matrix matrix1(4, 3);

  // Act
  matrix1.set_matrix(arr, 9);

  // Assert
  ASSERT_THROW(matrix1.InverseMatrix(), invalid_argument);
}

TEST(TestMatrixInverseMatrix, Subtest_InverseMatrix_3) {
  // Arrange
  double arr[] = {3, 2, 3, 4, 1, 2, 1, 2, 3};
  double arr_ref[] = {0.5, 0, -0.5, 5, -3, -3, -3.5, 2, 2.5};
  S21Matrix matrix1(3, 3);
  S21Matrix ref(3, 3);
  S21Matrix result(3, 3);

  // Act
  matrix1.set_matrix(arr, 9);
  ref.set_matrix(arr_ref, 9);
  result = matrix1.InverseMatrix();

  // Assert
  ASSERT_TRUE(ref.EqMatrix(result));
}

TEST(TestMatrixSet, Subtest_Set_1) {
  // Arrange
  double arr[] = {3, 2, 3, 4, 1, 2, 1, 2, 3};
  double arr2[] = {3, 2, 3, 0,
                  4, 1, 2, 0,
                  1, 2, 3, 0,
                  0, 0, 0, 0};
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(4, 4);

  // Act
  matrix1.set_matrix(arr, 9);
  matrix1.set_rows(4);
  matrix1.set_cols(4);
  matrix2.set_matrix(arr2, 16);

  // Assert
  ASSERT_TRUE(matrix1 == matrix2);
}

TEST(TestMatrixSet, Subtest_Set_2) {
  // Arrange
  double arr[] = {3, 2, 3, 4, 1, 2, 1, 2, 3};
  double arr2[] = {3, 2,
                   4, 1};
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(2, 2);

  // Act
  matrix1.set_matrix(arr, 9);
  matrix1.set_rows(2);
  matrix1.set_cols(2);
  matrix2.set_matrix(arr2, 4);

  // Assert
  ASSERT_TRUE(matrix1 == matrix2);
}

TEST(TestMatrixSet, Subtest_Set_3) {
  // Arrange
  S21Matrix matrix1(3, 3);
  

  // Act

  // Assert
  ASSERT_THROW(matrix1.set_rows(0), invalid_argument);
  ASSERT_THROW(matrix1.set_cols(0), invalid_argument);
}

TEST(TestMatrixGet, Subtest_Get_1) {
  // Arrange
  double arr[] = {3, 2, 3, 4, 1, 2, 1, 2, 3};
  S21Matrix matrix1(3, 3);
  double ref = 3;

  // Act
  matrix1.set_matrix(arr, 9);


  // Assert
  ASSERT_EQ(matrix1(0,0), ref);
}

TEST(TestMatrixGet, Subtest_Get_2) {
  // Arrange
  double arr[] = {3, 2, 3, 4, 1, 2, 1, 2, 3};
  S21Matrix matrix1(3, 3);

  // Act
  matrix1.set_matrix(arr, 9);


  // Assert
  ASSERT_THROW(matrix1(3,3), invalid_argument);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}