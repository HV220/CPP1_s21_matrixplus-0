#ifndef CPP1_S21_MATRIXPLUS_S21_MATRIX_H_
#define CPP1_S21_MATRIXPLUS_S21_MATRIX_H_

#include <cmath>
#include <iostream>

namespace src {
class S21Matrix {
private:
  int rows_, cols_;
  double **matrix_;

public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  void initMatrix();
  bool checkMatrix() const;
  void deleteMatrix();
  void copyMatrix(const S21Matrix &other);
  int getRows() const;
  int getCols() const;
  double mulValueMatrix(int i, int j, int num);
  void setRows(int rows);
  void setCols(int cols);
  void createCallocMatrix();
  void randomValueMatrix(bool random);

  bool equalSize(const S21Matrix &other) const;
  bool EqMatrix(const S21Matrix &other);
  bool matrixIsExist() const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  void getMatrixForDeterminant(const S21Matrix &other, int row, int column);
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const double num);
  S21Matrix operator*(const S21Matrix &other);
  bool operator==(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix operator+=(const S21Matrix &other);
  S21Matrix operator-=(const S21Matrix &other);
  S21Matrix operator*=(const double num);
  S21Matrix operator*=(const S21Matrix &other);
  double &operator()(int i, int j);
  void fillMatrix();
};
} // namespace src

#endif //  CPP1_S21_MATRIXPLUS_S21_MATRIX_H_