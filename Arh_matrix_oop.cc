#include "Arh_matrix_oop.h"

void ArhMatrix::AllocMatrix(int rows, int cols) {
  cols_ = cols;
  rows_ = rows;
  matrix_ = new (std::nothrow) double *[rows_];
  for (int r = 0; r < rows_ && matrix_ != nullptr; ++r) {
    matrix_[r] = new (std::nothrow) double[cols_];
  }
  for (int r = 0; r < rows_; ++r) {
    for (int c = 0; c < cols_; ++c) {
      matrix_[r][c] = +0.0;
    }
  }
}

ArhMatrix::ArhMatrix() : ArhMatrix(2, 2) {}

ArhMatrix::ArhMatrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0)
    throw std::length_error("rows > 0 && cols > 0");
  AllocMatrix(rows, cols);
}

ArhMatrix::ArhMatrix(const ArhMatrix &other)
    : ArhMatrix(other.rows_, other.cols_) {
  if (other.matrix_ == nullptr || other.matrix_[0] == nullptr)
    throw std::length_error("other is nullptr");
  for (int r = 0; r < rows_; ++r) {
    for (int c = 0; c < cols_; ++c) {
      matrix_[r][c] = other.matrix_[r][c];
    }
  }
}

ArhMatrix::ArhMatrix(ArhMatrix &&other) noexcept {
  FreeMatrix();
  std::swap(cols_, other.cols_);
  std::swap(rows_, other.rows_);
  std::swap(matrix_, matrix_);
}

ArhMatrix::~ArhMatrix() { FreeMatrix(); }

void ArhMatrix::FreeMatrix() {
  for (int r = 0; r < rows_; ++r) {
    delete[] matrix_[r];
  }
  delete[] matrix_;
  matrix_ = nullptr;

  rows_ = 0;
  cols_ = 0;
}

void ArhMatrix::ShowMatrix() {
  if (matrix_ == nullptr || matrix_[0] == nullptr)
    throw std::length_error("other is nullptr");
  for (int r = 0; r < rows_; ++r) {
    for (int c = 0; c < cols_; ++c) {
      std::cout << matrix_[r][c] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

double &ArhMatrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_)
    throw std::length_error("Index is outside the matrix!");

  return matrix_[i][j];
}

double ArhMatrix::operator()(int i, int j) const {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_)
    throw std::length_error("Index is outside the matrix!");
  return matrix_[i][j];
}

int ArhMatrix::GetRows() const noexcept { return rows_; }

int ArhMatrix::GetCols() const noexcept { return cols_; }

double ArhMatrix::GetMatrix(int r, int c) const {
  if (r >= rows_ || c >= cols_ || r < 0 || c < 0)
    throw std::length_error("Index is outside the matrix!");
  return matrix_[r][c];
}

void ArhMatrix::SetRows(const int rows) {
  if (matrix_ == nullptr || matrix_[0] == nullptr)
    throw std::length_error("this is nullptr");
  if (rows <= 0)
    throw std::length_error("rows > 0");
  ArhMatrix save_mat(rows_, cols_);

  save_mat = *this;

  AllocMatrix(rows, save_mat.cols_);
  int new_rows = rows < save_mat.rows_ ? rows : save_mat.rows_;

  for (int r = 0; r < new_rows; ++r) {
    for (int c = 0; c < save_mat.cols_; ++c) {
      matrix_[r][c] = save_mat.matrix_[r][c];
    }
  }
}

bool ArhMatrix::IsNullptrMat() const noexcept {
  return matrix_ == nullptr || matrix_[0] == nullptr;
}

void ArhMatrix::SetCols(const int cols) {
  if (matrix_ == nullptr || matrix_[0] == nullptr)
    throw std::length_error("this is nullptr");
  if (cols <= 0)
    throw std::length_error("cols > 0");

  ArhMatrix save_mat(rows_, cols_);

  save_mat = *this;

  AllocMatrix(save_mat.rows_, cols);

  int new_cols = cols < save_mat.cols_ ? cols : save_mat.cols_;

  for (int r = 0; r < save_mat.rows_; ++r) {
    for (int c = 0; c < new_cols; ++c) {
      matrix_[r][c] = save_mat.matrix_[r][c];
    }
  }
}

ArhMatrix &ArhMatrix::operator=(ArhMatrix &other) {
  if (this != &other) {
    FreeMatrix();
    std::swap(cols_, other.cols_);
    std::swap(rows_, other.rows_);
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}

ArhMatrix &ArhMatrix::operator=(const ArhMatrix &&other) {
  if (this != &other) {
    FreeMatrix();
    AllocMatrix(other.rows_, other.cols_);
    CopyMatrix(other);
  }
  return *this;
}

void ArhMatrix::CopyMatrix(const ArhMatrix &other) {
  if (cols_ != other.cols_ && rows_ != other.rows_)
    throw std::length_error("cols or rows are not equal");
  if (other.matrix_ == nullptr || matrix_ == nullptr)
    throw std::length_error("other or this are nullptr");
  for (int r = 0; r < rows_; ++r) {
    for (int c = 0; c < cols_; ++c) {
      (*this)(r, c) = other(r, c);
    }
  }
}

bool ArhMatrix::EqMatrix(const ArhMatrix &other) const {

  bool code = true;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int r = 0; r < rows_ && code != false; ++r) {
      for (int c = 0; c < cols_ && code != false; ++c) {
        if (fabs(fabs((*this)(r, c)) - fabs(other(r, c))) <= 0.e-7) {
          code = true;
        } else {
          code = false;
        }
      }
    }
  } else {
    code = false;
  }
  return code;
}

ArhMatrix ArhMatrix::operator+(const ArhMatrix &other) {
  if (other.matrix_ == nullptr || matrix_ == nullptr)
    throw std::length_error("other or this are nullptr");
  ArhMatrix res(*this);

  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int r = 0; r < other.rows_; ++r) {
      for (int c = 0; c < other.cols_; ++c) {
        res(r, c) += other(r, c);
      }
    }
  } else {
    throw std::length_error("rows and cols are not equal");
  }

  return res;
}

ArhMatrix ArhMatrix::operator-(const ArhMatrix &other) {
  if (other.matrix_ == nullptr || matrix_ == nullptr)
    throw std::length_error("other or this are nullptr");
  ArhMatrix res(*this);
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int r = 0; r < other.rows_; ++r) {
      for (int c = 0; c < other.cols_; ++c) {
        res(r, c) -= other(r, c);
      }
    }
  } else {
    throw std::length_error("rows and cols are not equal");
  }
  return res;
}

ArhMatrix ArhMatrix::operator*(const ArhMatrix &other) {
  if (other.matrix_ == nullptr || matrix_ == nullptr)
    throw std::length_error("other or this are nullptr");
  ArhMatrix res(rows_, other.cols_);

  if (rows_ == other.cols_) {
    for (int r = 0; r < res.rows_; ++r) {
      for (int c = 0; c < other.cols_; ++c) {
        for (int i = 0; i < other.rows_; ++i) {
          res(r, c) += (*this)(r, i) * other(i, c);
        }
      }
    }
  } else {
    throw std::length_error("res cols are not equal other rows");
  }
  return res;
}

ArhMatrix ArhMatrix::operator*(double num) {
  if (matrix_ == nullptr)
    throw std::length_error("this is a nullptr");
  ArhMatrix res(rows_, cols_);
  for (int r = 0; r < res.rows_; ++r) {
    for (int c = 0; c < res.cols_; ++c) {
      res(r, c) = (*this)(r, c) * num;
    }
  }

  return res;
}

bool ArhMatrix::operator==(const ArhMatrix &other) const {
  return EqMatrix(other);
}

void ArhMatrix::SumMatrix(const ArhMatrix &other) { *this = *this + other; }

void ArhMatrix::SubMatrix(const ArhMatrix &other) { *this = *this - other; }

void ArhMatrix::MulNumber(const double num) { *this = *this * num; }

void ArhMatrix::MulMatrix(const ArhMatrix &other) { *this = *this * other; }

ArhMatrix ArhMatrix::Transpose() {
  if (matrix_ == nullptr)
    throw std::length_error("this is a nullptr");
  ArhMatrix res(cols_, rows_);
  if (res.matrix_ == nullptr)
    throw std::length_error("res is a nullptr");
  for (int r = 0; r < rows_; ++r) {
    for (int c = 0; c < cols_; ++c) {
      res(c, r) = (*this)(r, c);
    }
  }
  return res;
}

ArhMatrix ArhMatrix::Minor(int row, int col) {
  if (matrix_ == nullptr)
    throw std::length_error("this is a nullptr");
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::length_error("uncorrect row or col");
  ArhMatrix result(rows_ - 1, cols_ - 1);

  for (int r = 0, r_res = 0; r < rows_; ++r) {
    if (r == row)
      continue;
    for (int c = 0, c_res = 0; c < cols_; ++c) {
      if (c == col)
        continue;
      result(r_res, c_res) = (*this)(r, c);
      ++c_res;
    }
    ++r_res;
  }
  return result;
}

double ArhMatrix::Determinant() {
  if (matrix_ == nullptr)
    throw std::length_error("this is a nullptr");
  if (rows_ != cols_)
    throw std::length_error("The matrix must be square.");

  ArhMatrix minor_saver;
  double result = 0;
  if (rows_ == 1)
    result = (*this)(0, 0);
  else if (rows_ == 2)
    result = (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
  else if (rows_ >= 3) {
    double returned_det = 0;
    for (int c = 0; c < cols_; ++c) {
      minor_saver = this->Minor(0, c);
      returned_det = minor_saver.Determinant();
      result += (*this)(0, c) * (pow((-1), c) * returned_det);
    }
  }

  return result;
}

ArhMatrix ArhMatrix::CalcComplements() {
  if (matrix_ == nullptr)
    throw std::length_error("this is a nullptr");
  if (rows_ != cols_)
    throw std::length_error("The matrix must be square.");
  if (rows_ == 1)
    throw std::length_error("rows > 1");

  ArhMatrix minor_saver;
  ArhMatrix result(rows_, cols_);

  for (int r = 0; r < rows_; ++r) {
    for (int c = 0; c < cols_; ++c) {
      double tmp = +0.0;
      minor_saver = this->Minor(r, c);
      tmp = minor_saver.Determinant();
      result(r, c) = tmp * pow(-1, r + c);
    }
  }

  return result;
}

ArhMatrix ArhMatrix::InverseMatrix() {
  if (matrix_ == nullptr)
    throw std::length_error("this is a nullptr");
  if (rows_ != cols_)
    throw std::length_error("The matrix must be square.");

  double det = Determinant();
  if (fabs(det) < 1e-7)
    throw std::length_error("Matrix determinant is 0.");

  ArhMatrix transp;
  ArhMatrix res;
  transp = (CalcComplements()).Transpose();

  res = transp * (1 / det);
  // 1/|A| * M^T.
  return res;
}

ArhMatrix &ArhMatrix::operator+=(const ArhMatrix &other) {
  if (matrix_ == nullptr || other.matrix_ == nullptr)
    throw std::length_error("other or this are nullptr");

  SumMatrix(other);
  return *this;
}

ArhMatrix &ArhMatrix::operator-=(const ArhMatrix &other) {
  if (matrix_ == nullptr || other.matrix_ == nullptr)
    throw std::length_error("other or this are nullptr");

  SubMatrix(other);
  return *this;
}

ArhMatrix &ArhMatrix::operator*=(const ArhMatrix &other) {
  if (matrix_ == nullptr || other.matrix_ == nullptr)
    throw std::length_error("other or this are nullptr");

  MulMatrix(other);
  return *this;
}
ArhMatrix &ArhMatrix::operator*=(const double num) {
  if (matrix_ == nullptr)
    throw std::length_error("other or this are nullptr");

  MulNumber(num);
  return *this;
}