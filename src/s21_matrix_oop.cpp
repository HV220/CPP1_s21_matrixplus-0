#include "s21_matrix_oop.h"

using namespace src;

int main()
{
   S21Matrix test = S21Matrix(2, 3);
   S21Matrix test1 = S21Matrix(2, 3);
   test1.ChargeMatrix();
   test.ChargeMatrix();

   test.SumMatrix(test1);

   test.PrintMatrix();
   test.SubMatrix(test1);
   test.PrintMatrix();
   return 0;
}