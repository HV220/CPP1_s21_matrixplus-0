#include "s21_matrix_oop.h"

using namespace src;

int main()
{
   S21Matrix *test = new S21Matrix(3, 3);
   S21Matrix test1 = S21Matrix(3, 3);
   test1.ChargeMatrix();
   test = new S21Matrix();

   return 0;
}

// test.SumMatrix(test);
// test.PrintMatrix();
// test1.PrintMatrix();
// // test.PrintMatrix();
// test.MulMatrix(test1);
// test.PrintMatrix();
// // test.PrintMatrix();