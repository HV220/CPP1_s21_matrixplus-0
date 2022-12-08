#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_
#include <stdlib.h>
#include <stdio.h>

namespace src
{
  class S21Matrix
  {
  private:
    int rows_, cols_;
    double **matrix_;

  public:
    S21Matrix()
    {
      this->rows_ = 1;
      this->cols_ = 1;

      if (int status = this->RealisationCalloc())
      {
        exit(status);
      }
    }

    ~S21Matrix()
    {
      if (this->matrix_ != NULL)
      {
        for (int j = 0; j < this->rows_; j++)
        {
          if (this->matrix_[j] != NULL)
          {
            free(this->matrix_[j]);
          }
        }
        free(this->matrix_);
      }
    }

    S21Matrix(int rows, int cols)
    {
      if (rows > 0 && cols > 0)
      {
        this->rows_ = rows;
        this->cols_ = cols;

        if (int status = this->RealisationCalloc())
        {
          exit(status);
        }
      }
    }

    S21Matrix(const S21Matrix &other)
    {
      this->rows_ = other.rows_;
      this->cols_ = other.cols_;

      if (int status = this->RealisationCalloc())
      {
        exit(status);
      }

      this->CopyMatrix(other, other.rows_, other.cols_);
    }

    S21Matrix(S21Matrix &&other)
    {
      this->cols_ = other.cols_;
      this->rows_ = other.rows_;
      this->matrix_ = this->matrix_;
    }

    int GetRows()
    {
      return this->rows_;
    }

    int GetCols()
    {
      return this->cols_;
    }

    double **GetMatrix()
    {
      return this->matrix_;
    }

    void SumMatrix(const S21Matrix &other);
    bool EqMatrix(const S21Matrix &other);
    void SubMatrix(const S21Matrix &other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix &other);
    S21Matrix Transpose();
    S21Matrix CalcComplements();
    double Determinant();
    S21Matrix InverseMatrix();

    void PrintMatrix()
    {
      double **arr = this->GetMatrix();
      for (int i = 0; i < this->GetRows(); i++)
      {
        for (int j = 0; j < this->GetCols(); j++)
          printf("%lf  ", arr[i][j]);
        printf("\n");
      }
    };

  private:
    int RealisationCalloc()
    {
      int status = 0;

      this->matrix_ = (double **)calloc(this->rows_, sizeof(double *));

      if (!this->matrix_)
      {
        status = 1;
      }
      else
      {
        for (int i = 0; i < this->rows_; i++)
        {
          if (((this->matrix_[i] = (double *)calloc(this->cols_, sizeof(double))) == NULL))
          {
            status = 2;
            break;
          }
        }
      }
      return status;
    }

    void CopyMatrix(const S21Matrix &other, int rows, int cols)
    {
      for (int i = 0; i < rows; i++)
      {
        for (int y = 0; y < cols; y++)
        {
          this->matrix_[i][y] = other.matrix_[i][y];
        }
      }
    }
  };

}
#endif //  SRC_S21_MATRIX_OOP_H_
