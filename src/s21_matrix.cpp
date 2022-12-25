#include "s21_matrix.h"

using namespace src;

S21Matrix::S21Matrix() { initMatrix(); }

void S21Matrix::initMatrix() {
  this->cols_ = 0;
  this->rows_ = 0;
  this->matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 0 || cols < 0) {
    throw std::logic_error("rows или cols имеет отрицательное значение");
  } else {
    this->rows_ = rows;
    this->cols_ = cols;

    this->createCallocMatrix();
  }
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  if (this != &other) {
    this->cols_ = other.cols_;
    this->rows_ = other.rows_;
    this->matrix_ = new double *[other.rows_];
    for (int i = 0; i < other.rows_; i++) {
      matrix_[i] = new double[cols_];
    }
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  if (other.checkMatrix() && this != &other) {
    this->cols_ = other.cols_;
    this->rows_ = other.rows_;
    this->matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
}

bool S21Matrix::checkMatrix() const {
  return (cols_ > 0 && rows_ > 0 && matrix_ != nullptr);
}

S21Matrix::~S21Matrix() { deleteMatrix(); }

void S21Matrix::deleteMatrix() {
  if (this->matrix_) {
    for (int i = 0; i < this->rows_; i++) {
      delete this->matrix_[i];
    }
    delete this->matrix_;
  }
  this->rows_ = 0;
  this->cols_ = 0;
}

int S21Matrix::getRows() const { return this->matrix_ ? this->rows_ : 0; }

int S21Matrix::getCols() const { return this->matrix_ ? this->cols_ : 0; }

double S21Matrix::mulValueMatrix(int i, int j, int num) {
  matrix_[i][j] *= num;
  return matrix_[i][j];
}

void S21Matrix::setRows(int rows) {
  if (rows != this->rows_ && this->matrix_) {
    S21Matrix matrix_tmp(rows, this->cols_);
    for (int i = 0; i < (rows < this->rows_ ? rows : this->rows_); i++) {
      for (int j = 0; j < this->cols_; j++) {
        matrix_tmp.matrix_[i][j] = this->matrix_[i][j];
      }
    }
    deleteMatrix();
    this->rows_ = rows;
    this->cols_ = matrix_tmp.cols_;
    this->matrix_ = matrix_tmp.matrix_;
    matrix_tmp.matrix_ = nullptr;
  }
}

void S21Matrix::setCols(int cols) {
  if (cols != this->cols_ && this->matrix_) {
    S21Matrix matrix_tmp(this->rows_, cols);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < (cols < this->cols_ ? cols : this->cols_); j++) {
        matrix_tmp.matrix_[i][j] = this->matrix_[i][j];
      }
    }
    deleteMatrix();
    this->rows_ = matrix_tmp.rows_;
    this->cols_ = cols;
    this->matrix_ = matrix_tmp.matrix_;
    matrix_tmp.matrix_ = nullptr;
  }
}

bool S21Matrix::equalSize(const S21Matrix &other) const {
  return this->cols_ == other.cols_ && this->rows_ == other.rows_;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (!(equalSize(other))) {
    return false;
  } else if (this == &other) {
    return true;
  }
  bool result = true;
  for (int i = 0; i < rows_ && result; ++i) {
    for (int j = 0; j < cols_ && result; ++j) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-07) {
        result = false;
      }
    }
  }
  return result;
}

bool S21Matrix::matrixIsExist() const {
  return (this->cols_ > 0 && this->rows_ > 0 && this->matrix_ != nullptr);
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (!equalSize(other)) {
    throw std::out_of_range("Разного размера матрицы!");
  }
  if (this->matrixIsExist() && other.matrixIsExist()) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (!equalSize(other)) {
    throw std::out_of_range("Разного размера матрицы!");
  }
  if (this->matrixIsExist() && other.matrixIsExist()) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (this->matrixIsExist()) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] *= num;
      }
    }
  }
}

void S21Matrix::copyMatrix(const S21Matrix &other) {
  for (int i = 0; i < other.getRows(); i++) {
    for (int j = 0; j < other.getCols(); j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->rows_ != other.cols_) {
    throw std::logic_error(
        "число столбцов первой матрицы не равно числу строк второй матрицы");
  }
  if (this->matrixIsExist() && other.matrixIsExist()) {
    S21Matrix temp_result(this->rows_, other.cols_);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        for (int k = 0; k < this->cols_; k++) {
          temp_result.matrix_[i][j] +=
              this->matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
    this->setCols(temp_result.cols_);
    this->setRows(temp_result.rows_);
    this->createCallocMatrix();
    this->copyMatrix(temp_result);
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix transposed_matrix(cols_, rows_);
  if (matrixIsExist()) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        transposed_matrix.matrix_[j][i] = matrix_[i][j];
      }
    }
  }
  return transposed_matrix;
}

void S21Matrix::getMatrixForDeterminant(const S21Matrix &other, int row,
                                        int column) {
  for (int i = 0, x = 0; i < other.rows_; i++) {
    if (i != row) {
      for (int j = 0, y = 0; j < other.cols_; j++) {
        if (j != column) {
          matrix_[x][y] = other.matrix_[i][j];
          y++;
        }
      }
      x++;
    }
  }
}

double S21Matrix::Determinant() {
  double result = 0;
  double temp_result = 0.0;
  if (rows_ != cols_) {
    throw std::logic_error("Матрица не квадратной формы!");
  }
  if (matrixIsExist()) {
    if (this->rows_ == 1) {
      temp_result = matrix_[0][0];
    } else if (this->rows_ == 2) {
      temp_result =
          (matrix_[0][0] * matrix_[1][1]) - (matrix_[1][0] * matrix_[0][1]);
    } else {
      S21Matrix temp_matrix(this->rows_ - 1, this->cols_ - 1);
      for (int i = 0; i < this->cols_; ++i) {
        temp_matrix.getMatrixForDeterminant(*this, 0, i);
        result = temp_matrix.Determinant();
        temp_result += matrix_[0][i] * pow(-1, i) * result;
      }
    }
    result = temp_result;
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result(rows_, cols_);
  if (rows_ != cols_) {
    throw std::logic_error("Матрица не квадратной формы!");
  }
  if (matrixIsExist()) {
    S21Matrix temp_matrix(rows_ - 1, cols_ - 1);
    double temp_result;
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        temp_matrix.getMatrixForDeterminant(*this, i, j);
        temp_result = temp_matrix.Determinant();
        result.matrix_[i][j] += pow(-1, i + j) * temp_result;
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix temp_matrix(rows_, cols_);
  double deter = Determinant();
  if (deter == 0) {
    throw std::invalid_argument("Определитель равен 0!");
  }
  if (matrixIsExist() && (rows_ == cols_)) {
    temp_matrix = CalcComplements();
    temp_matrix = temp_matrix.Transpose();
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        temp_matrix.matrix_[i][j] = 1 / deter * temp_matrix.matrix_[i][j];
      }
    }
  }
  return temp_matrix;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix new_matrix(*this);
  new_matrix.SumMatrix(other);
  return new_matrix;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix new_matrix(*this);
  new_matrix.SubMatrix(other);
  return new_matrix;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix new_matrix(*this);
  new_matrix.MulNumber(num);
  return new_matrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix new_matrix(*this);
  new_matrix.MulMatrix(other);
  return new_matrix;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    deleteMatrix();
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->matrix_ = new double *[rows_];
    for (int i = 0; i < this->rows_; ++i) {
      this->matrix_[i] = new double[this->cols_];
    }
    for (int i = 0; i < this->rows_; ++i) {
      for (int j = 0; j < this->cols_; ++j) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

double &S21Matrix::operator()(int i, int j) {
  if (!(rows_ >= i && i >= 0 && cols_ >= j && j >= 0)) {
    throw std::out_of_range("Разного размера матрицы!");
  }
  return matrix_[i][j];
}

void S21Matrix::fillMatrix() {
  double temp = 0;
  for (int i = 0; i < getRows(); ++i) {
    for (int j = 0; j < getCols(); ++j) {
      matrix_[i][j] = temp;
      temp++;
    }
  }
}

void S21Matrix::createCallocMatrix() {
  this->matrix_ = new double *[this->rows_];

  for (int i = 0; i < this->rows_; i++) {
    this->matrix_[i] = new double[this->cols_];
  }
}

void S21Matrix::randomValueMatrix(bool random) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      if (!random) {
        this->matrix_[i][j] = j + i;
      } else {
        this->matrix_[i][j] = std::rand();
      }
    }
  }
}