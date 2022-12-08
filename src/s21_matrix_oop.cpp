#include "s21_matrix_oop.h"

using namespace src;

int main()
{
   S21Matrix test = S21Matrix(3, 5);
   S21Matrix test1 = S21Matrix(test);
   test1.PrintMatrix();
   return 0;
}