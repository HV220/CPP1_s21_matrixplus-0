#ifndef SRC/S21_MATRIX_OOP_H_
#define SRC/S21_MATRIX_OOP_H_
#include <stdlib.h>

namespace src {
class S21Matrix {
    private:
        int rows_, cols_;
        double **matrix_;

    public:
        S21Matrix()
        {
            this->rows_ = 1;
            this->cols_ = 1;
  
          this->matrix_ = (double **)calloc(this->rows_, sizeof(double *));

          if (!this->matrix_) exit(1);

          for (int i = 0; i <  this->rows_; i++)
          {
            if (((this->matrix_[i] = (double *)calloc(this->cols_, sizeof(double))) == NULL)) 
            {
                 for (int j = 0; j < i; j++) free(this->matrix_[i]);
                
                 free(this->matrix_);
            }
          }
        } 
        
        ~S21Matrix(); 
        S21Matrix(int rows, int cols);
        S21Matrix(const S21Matrix& other);
        S21Matrix(S21Matrix&& other);

        void SumMatrix(const S21Matrix& other); 
        bool EqMatrix(const S21Matrix& other);
        void SubMatrix(const S21Matrix& other);
        void MulNumber(const double num);
        void MulMatrix(const S21Matrix& other);
        S21Matrix Transpose();
        S21Matrix CalcComplements();
        double Determinant();
        S21Matrix InverseMatrix();  
};
}
#endif //  SRC/S21_MATRIX_OOP_H_
