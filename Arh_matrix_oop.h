#ifndef CPP1_Arh_MATRIXPLUS_1_SRC_Arh_MATRIX_OOP_H_
#define CPP1_Arh_MATRIXPLUS_1_SRC_Arh_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

class ArhMatrix {
public:
  // constructions
  ArhMatrix();
  ArhMatrix(int rows, int cols);
  ArhMatrix(const ArhMatrix &other);
  ArhMatrix(ArhMatrix &&other) noexcept;

  // assignment operators
  ArhMatrix &operator=(ArhMatrix &other);
  ArhMatrix &operator=(const ArhMatrix &&other);
  ArhMatrix &operator+=(const ArhMatrix &other);
  ArhMatrix &operator-=(const ArhMatrix &other);
  ArhMatrix &operator*=(const ArhMatrix &other);
  ArhMatrix &operator*=(const double num);

  // destructor
  ~ArhMatrix();
  void FreeMatrix();

  // gets & sets
  int GetRows() const noexcept;
  int GetCols() const noexcept;
  double GetMatrix(int r, int c) const;
  void SetRows(const int rows);
  void SetCols(const int cols);

  // public methods
  bool EqMatrix(const ArhMatrix &other) const;
  void SumMatrix(const ArhMatrix &other);
  void SubMatrix(const ArhMatrix &other);
  void MulNumber(const double num);
  void MulMatrix(const ArhMatrix &other);
  ArhMatrix Transpose();
  ArhMatrix CalcComplements();
  double Determinant();
  ArhMatrix InverseMatrix();
  ArhMatrix Minor(int row, int col);

  // operators overloads
  ArhMatrix operator+(const ArhMatrix &other);
  ArhMatrix operator-(const ArhMatrix &other);
  ArhMatrix operator*(const ArhMatrix &other);
  ArhMatrix operator*(double num);
  bool operator==(const ArhMatrix &other) const;

  // additional
  void ShowMatrix();
  bool IsNullptrMat() const noexcept;

  // atributes
  double &operator()(int i, int j);
  double operator()(int i, int j) const;

private:
  void CopyMatrix(const ArhMatrix &other);
  void AllocMatrix(int rows, int cols);

  // atributes
  int rows_, cols_;
  double **matrix_;
};

#endif // CPP1_Arh_MATRIXPLUS_1_SRC_Arh_MATRIX_OOP_H_