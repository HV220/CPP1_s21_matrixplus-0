#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <limits>
#include <typeinfo>

#define SUCCESS 0
#define FAILURE 1
#define INCORRECT 2

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

    void SumMatrix(const S21Matrix &other)
    {
      if (this->CompareMatrix(other) && this->EmptyMatrix(other))
      {
        for (int i = 0; i < this->rows_; i++)
        {
          for (int j = 0; j < this->cols_; j++)
          {
            this->matrix_[i][j] = (this->matrix_[i][j] + other.matrix_[i][j]);
          }
        }
      }
    }

    bool EqMatrix(const S21Matrix &other)
    {
      int status = true;

      if (!this->CompareMatrix(other))
      {
        status = false;
        return status;
      }

      for (int i = 0; i < this->rows_; i++)
      {
        for (int j = 0; j < this->cols_; j++)
        {
          if (std::fabs(this->matrix_[i][j] - other.matrix_[i][j]) > std::numeric_limits<double>::epsilon())
          {
            status = false;
          }
        }
      }

      return status;
    }
    void SubMatrix(const S21Matrix &other)
    {
      if (this->CompareMatrix(other) && this->EmptyMatrix(other))
      {
        for (int i = 0; i < this->rows_; i++)
        {
          for (int j = 0; j < this->cols_; j++)
          {
            this->matrix_[i][j] = (this->matrix_[i][j] - other.matrix_[i][j]);
          }
        }
      }
    }

    void MulNumber(const double num)
    {
      if (this->EmptyMatrix(*this))
      {
        for (int i = 0; i < this->rows_; i++)
        {
          for (int j = 0; j < this->cols_; j++)
          {
            this->matrix_[i][j] = num * this->matrix_[i][j];
          }
        }
      }
    }

    void MulMatrix(const S21Matrix &other)
    {

      if (!this->EmptyMatrix(other))
      {
        return;
      }

      if (this->cols_ != other.rows_)
      {
        return;
      }

      S21Matrix *result = new S21Matrix(this->rows_, other.cols_);

      if (!result->GetMatrix())
      {
        return;
      }

      int tmp = 0;
      int tmp_columns = 0;

      for (int i = 0; i < result->rows_; i++, tmp++)
      {
        for (int j = 0; j < result->cols_; j++)
        {
          for (int k = 0; k < this->cols_; k++)
          {
            result->matrix_[i][j] += (this->matrix_[tmp][k]) *
                                     (other.matrix_[k][tmp_columns]);
          }
          tmp_columns++;
        }
        tmp_columns = 0;
      }

      this->cols_ = result->cols_;
      this->rows_ = result->rows_;
      this->RealisationCalloc();
      this->CopyMatrix(*result, this->rows_, this->cols_);
      delete (result);
    }

    S21Matrix Transpose()
    {

      S21Matrix *result = new S21Matrix(this->cols_, this->rows_);

      int tmp = 0;

      for (int i = 0; i < result->rows_; i++)
      {
        for (int j = 0; j < result->cols_; j++)
        {
          result->matrix_[i][j] = this->matrix_[j][tmp];
        }
        tmp++;
      }

      return *result;
    }

    S21Matrix CalcComplements()
    {
    }

    // double Determinant()
    // {
    //   double tmp = 0.0;

    //   if (!(this->rows_ != this->cols_) || !(this->EmptyMatrix()))
    //   {
    //     return NULL;
    //   }

    //   if (this->rows_ == 1)
    //   {
    //     tmp = this->matrix_[0][0];
    //   }

    //   if (this->rows_ == 2)
    //   {
    //     tmp = (this->matrix_[0][0] * this->matrix_[1][1]) -
    //           (this->matrix_[1][0] * this->matrix_[0][1]);
    //   }

    //   if (this->rows_ > 2)
    //   {
    //     S21Matrix *matrix = new S21Matrix();

    //     for (int i = 0; i < this->rows_; i++)
    //     {
    //       if (this->EqMatrixDeterminant(matrix, 0, i))
    //       {
    //         break;
    //       }
    //       matrix->Determinant(result);
    //       tmp += A->matrix[i][0] * pow(-1, i) * *result;
    //       s21_remove_matrix(&matrix);
    //     }
    //   }
    //   *result = tmp;
    //   return error;
    // }

    S21Matrix InverseMatrix();

    void PrintMatrix()
    {
      double **arr = this->GetMatrix();

      printf("\n--------------------------------\n");
      printf("%s\n", typeid(this).name());

      for (int i = 0; i < this->GetRows(); i++)
      {
        for (int j = 0; j < this->GetCols(); j++)
          printf("%lf  ", arr[i][j]);
        printf("\n");
      }

      printf("--------------------------------\n");
    };

    void ChargeMatrix()
    {
      for (int i = 0; i < this->rows_; i++)
      {
        for (int y = 0; y < this->cols_; y++)
        {
          this->matrix_[i][y] = y + 1;
        }
      }
    }

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

    int CompareMatrix(const S21Matrix &other)
    {
      int status = 0;

      if (this->cols_ == other.cols_ && this->rows_ == other.rows_)
      {
        status = 1;
      }

      return status;
    }

    int EmptyMatrix(const S21Matrix &other)
    {
      int status = 0;

      if ((this->cols_ > 0) && (other.cols_ > 0) && (this->matrix_) &&
          (other.matrix_))
      {
        status = 1;
      }

      return status;
    }

    int EmptyMatrix()
    {
      int status = 0;

      if ((this->matrix_ != NULL) && (this->cols_ > 0) && (this->rows_ > 0))
      {
        status = 1;
      }

      return status;
    }

    int EqMatrixDeterminant(const S21Matrix *other, int row, int column)
    {
      int status = 0;
      other = new S21Matrix(this->rows_ - 1, this->cols_ - 1);

      for (int i = 0, y = 0; i < this->rows_; i++)
      {
        if (i != column)
        {
          for (int j = 0, x = 0; j < this->rows_; j++)
          {
            if (j != row)
            {
              other->matrix_[y][x] = this->matrix_[i][j];
              x++;
            }
          }
          y++;
        }
      }
      return status;
    }
  };
}

#endif //  SRC_S21_MATRIX_OOP_H_
