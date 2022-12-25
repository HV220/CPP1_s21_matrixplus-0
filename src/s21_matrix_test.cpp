#include "s21_matrix.h"
#include <gtest/gtest.h>

using namespace src;
using namespace std;

TEST(S21MatrixConstructor, trueTest) {
  S21Matrix matrix_1;
  S21Matrix matrix_2 = S21Matrix(4, 5);

  EXPECT_ANY_THROW(S21Matrix matrix_3(3, -1));
  EXPECT_EQ(matrix_1.getRows(), 0);
  EXPECT_EQ(matrix_1.getCols(), 0);
  EXPECT_EQ(matrix_2.getRows(), 4);
  EXPECT_EQ(matrix_2.getCols(), 5);
}

TEST(S21MatrixCopyConstructor, trueTest) {
  S21Matrix matrix_1(4, 7);
  S21Matrix matrix_2(matrix_1);

  EXPECT_EQ(matrix_1.getRows(), 4);
  EXPECT_EQ(matrix_1.getCols(), 7);
  EXPECT_EQ(matrix_2.getRows(), 4);
  EXPECT_EQ(matrix_2.getCols(), 7);
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_2));
  matrix_2.randomValueMatrix(1);
  EXPECT_FALSE(matrix_2.EqMatrix(matrix_1));
}

TEST(S21MatrixCopyConstructor, emptyTest) {
  S21Matrix matrix_1;
  S21Matrix matrix_2(matrix_1);

  EXPECT_EQ(matrix_1.getRows(), 0);
  EXPECT_EQ(matrix_1.getCols(), 0);
  EXPECT_EQ(matrix_2.getRows(), 0);
  EXPECT_EQ(matrix_2.getCols(), 0);
  EXPECT_TRUE(matrix_2.EqMatrix(matrix_1));
}

TEST(S21MatrixMoveConstructor, trueTest) {
  S21Matrix matrix_1(4, 5);
  S21Matrix matrix_2(move(matrix_1));

  EXPECT_EQ(matrix_1.getRows(), 0);
  EXPECT_EQ(matrix_1.getCols(), 0);
  EXPECT_EQ(matrix_2.getRows(), 4);
  EXPECT_EQ(matrix_2.getCols(), 5);
}

TEST(setRowsCols, trueTest) {
  S21Matrix matrix_1(3, 3);
  matrix_1.setRows(5);
  matrix_1.setCols(7);

  EXPECT_EQ(matrix_1.getRows(), 5);
  EXPECT_EQ(matrix_1.getCols(), 7);
  matrix_1.setRows(0);
  matrix_1.setCols(0);
  EXPECT_EQ(matrix_1.getRows(), 0);
  EXPECT_EQ(matrix_1.getCols(), 0);
}

TEST(EqMatrix, trueTest) {
  S21Matrix matrix_1(4, 3);
  S21Matrix matrix_2(4, 3);

  matrix_1.fillMatrix();
  matrix_2.fillMatrix();

  EXPECT_TRUE(matrix_1.EqMatrix(matrix_2));
  EXPECT_TRUE(matrix_2.EqMatrix(matrix_1));
  EXPECT_TRUE(matrix_1 == matrix_2);
  EXPECT_TRUE(matrix_2 == matrix_1);
}

TEST(EqMatrix, falseTest) {
  S21Matrix matrix_1(4, 3);
  S21Matrix matrix_2(4, 3);

  matrix_1.fillMatrix();
  matrix_2.randomValueMatrix(1);

  EXPECT_FALSE(matrix_1.EqMatrix(matrix_2));
  EXPECT_FALSE(matrix_2.EqMatrix(matrix_1));
  EXPECT_FALSE(matrix_1 == matrix_2);
  EXPECT_FALSE(matrix_2 == matrix_1);
}

TEST(EqMatrix, emptyOneMatrixTest) {
  S21Matrix matrix_1(3, 3);
  S21Matrix matrix_2;

  EXPECT_TRUE(!matrix_1.EqMatrix(matrix_2));
}

TEST(EqMatrix, emptyTwoMatrixTest) {
  S21Matrix matrix_1;
  S21Matrix matrix_2;

  EXPECT_TRUE(matrix_1.EqMatrix(matrix_2));
}

TEST(SumMatrix, trueTest) {
  S21Matrix matrix_1(5, 4);
  S21Matrix matrix_2(5, 4);
  S21Matrix tmpMatrix(5, 4);

  matrix_1.fillMatrix();
  matrix_2.fillMatrix();
  tmpMatrix.fillMatrix();
  matrix_1.SumMatrix(tmpMatrix);
  matrix_2.SumMatrix(tmpMatrix);

  EXPECT_TRUE(matrix_1.EqMatrix(matrix_2));
}

TEST(SumMatrix, assertThrow) {
  S21Matrix matrix_1(5, 3);
  S21Matrix matrix_2(3, 4);

  matrix_1.fillMatrix();
  matrix_2.fillMatrix();

  ASSERT_THROW(matrix_1.SumMatrix(matrix_2), std::out_of_range);
}

TEST(SubMatrix, trueTest) {
  S21Matrix matrix_1(5, 4);
  S21Matrix matrix_2(5, 4);
  S21Matrix tmpMatrix(5, 4);

  matrix_1.fillMatrix();
  matrix_2.fillMatrix();
  tmpMatrix.fillMatrix();
  matrix_1.SubMatrix(tmpMatrix);
  matrix_2.SubMatrix(tmpMatrix);

  EXPECT_TRUE(matrix_1.EqMatrix(matrix_2));
}

TEST(SubMatrix, assertThrow) {
  S21Matrix matrix_1(5, 3);
  S21Matrix matrix_2(3, 4);

  matrix_1.fillMatrix();
  matrix_2.fillMatrix();

  ASSERT_THROW(matrix_1.SubMatrix(matrix_2), std::out_of_range);
}

TEST(MulNumber, trueTest) {
  S21Matrix matrix_1(3, 3);
  S21Matrix matrix_2(3, 3);

  matrix_1.fillMatrix();
  matrix_2.fillMatrix();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix_1.mulValueMatrix(i, j, 3);
    }
  }
  matrix_2.MulNumber(3);

  EXPECT_TRUE(matrix_1.EqMatrix(matrix_2));
}

TEST(MulNumber, emptyTest) {
  S21Matrix matrix_1;
  S21Matrix matrix_2;

  matrix_1.MulNumber(9);

  EXPECT_TRUE(matrix_1.EqMatrix(matrix_2));
}

TEST(MulMatrix, trueTest) {
  S21Matrix matrix_1(4, 3);
  S21Matrix matrix_2(3, 4);
  S21Matrix result(4, 4);

  matrix_1.fillMatrix();
  matrix_2.fillMatrix();
  result(0, 0) = 20;
  result(0, 1) = 23;
  result(0, 2) = 26;
  result(0, 3) = 29;
  result(1, 0) = 56;
  result(1, 1) = 68;
  result(1, 2) = 80;
  result(1, 3) = 92;
  result(2, 0) = 92;
  result(2, 1) = 113;
  result(2, 2) = 134;
  result(2, 3) = 155;
  result(3, 0) = 128;
  result(3, 1) = 158;
  result(3, 2) = 188;
  result(3, 3) = 218;
  matrix_1.MulMatrix(matrix_2);

  EXPECT_TRUE(matrix_1.EqMatrix(result));
}

TEST(MulMatrix_suite, exceptional_test) {
  S21Matrix matrix_1(7, 10);
  S21Matrix matrix_2(3, 4);

  matrix_1.fillMatrix();
  matrix_2.fillMatrix();

  ASSERT_THROW(matrix_1.MulMatrix(matrix_2), std::logic_error);
}

TEST(TransposeMatrix, trueTest) {
  S21Matrix matrix_1(4, 3);
  S21Matrix result(3, 4);

  matrix_1.fillMatrix();
  matrix_1 = matrix_1.Transpose();
  result(0, 0) = 0;
  result(0, 1) = 3;
  result(0, 2) = 6;
  result(0, 3) = 9;
  result(1, 0) = 1;
  result(1, 1) = 4;
  result(1, 2) = 7;
  result(1, 3) = 10;
  result(2, 0) = 2;
  result(2, 1) = 5;
  result(2, 2) = 8;
  result(2, 3) = 11;

  EXPECT_TRUE(matrix_1.EqMatrix(result));
}

TEST(CalcComplement_suite, trueTest) {
  S21Matrix matrix_1(3, 3);
  S21Matrix result(3, 3);

  matrix_1.fillMatrix();
  matrix_1 = matrix_1.CalcComplements();
  result(0, 0) = -3.000000;
  result(0, 1) = 6.000000;
  result(0, 2) = -3.000000;
  result(1, 0) = 6.000000;
  result(1, 1) = -12.000000;
  result(1, 2) = 6.000000;
  result(2, 0) = -3.000000;
  result(2, 1) = 6.000000;
  result(2, 2) = -3.000000;

  EXPECT_TRUE(matrix_1.EqMatrix(result));
}

TEST(CalcComplement, assertThrow) {
  S21Matrix matrix_1(3, 4);

  matrix_1.fillMatrix();
  ASSERT_THROW(matrix_1.CalcComplements(), std::logic_error);
}

TEST(Determinant, trueTest) {
  S21Matrix matrix_1(4, 4);

  matrix_1.fillMatrix();
  matrix_1(0, 0) = 13;
  matrix_1(1, 1) = 15;
  EXPECT_TRUE(matrix_1.Determinant() == -520);
}

TEST(Determinant, oneMatrixTest) {
  S21Matrix matrix_1(1, 1);

  matrix_1(0, 0) = 1;

  EXPECT_TRUE(matrix_1.Determinant() == 1);
}

TEST(Determinant, assertThrow) {
  S21Matrix first_matrix(3, 4);

  first_matrix.fillMatrix();

  ASSERT_THROW(first_matrix.Determinant(), std::logic_error);
}

TEST(InverseMatrix, trueTest) {
  S21Matrix matrix_1(3, 3);
  S21Matrix result(3, 3);

  matrix_1.fillMatrix();
  matrix_1(1, 1) = 6;
  matrix_1 = matrix_1.InverseMatrix();
  result(0, 0) = -0.54166666667;
  result(0, 1) = -0.25;
  result(0, 2) = 0.291666666667;
  result(1, 0) = -0.25;
  result(1, 1) = 0.5;
  result(1, 2) = -0.25;
  result(2, 0) = 0.625;
  result(2, 1) = -0.25;
  result(2, 2) = 0.125;

  EXPECT_EQ(result(1, 1), matrix_1(1, 1));
}

TEST(InverseMatrix, assertThrow) {
  S21Matrix matrix_1(3, 3);

  matrix_1.fillMatrix();
  ASSERT_THROW(matrix_1.InverseMatrix(), std::invalid_argument);
}

TEST(OperatorPlus, trueTest) {
  S21Matrix matrix_1(3, 3);
  S21Matrix result(3, 3);
  matrix_1.fillMatrix();
  result.fillMatrix();
  matrix_1.operator+(matrix_1);

  printf("\n%f \t %f", matrix_1(0, 1), result(0, 1));

  EXPECT_TRUE(matrix_1(0, 1) == result(0, 1));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}