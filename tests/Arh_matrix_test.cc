#include "../Arh_matrix_oop.h"

#include <gtest/gtest.h>

// Gets & sets
TEST(ArhMatrixGets, Rows) {
  ArhMatrix mat(1, 1);
  EXPECT_EQ(mat.GetRows(), 1);
  EXPECT_EQ(ArhMatrix(3, 3).GetRows(), 3);
  EXPECT_EQ(ArhMatrix(5, 3).GetRows(), 5);
}

TEST(ArhMatrixGets, Cols) {
  ArhMatrix mat(1, 1);
  EXPECT_EQ(mat.GetCols(), 1);
  EXPECT_EQ(ArhMatrix(3, 3).GetCols(), 3);
  EXPECT_EQ(ArhMatrix(1, 4).GetCols(), 4);
}

TEST(ArhMatrixGets, MatrixNormal) {
  ArhMatrix mat;
  EXPECT_EQ(mat.GetMatrix(0, 0), 0);
}

TEST(ArhMatrixGets, MatrixFailer) {
  ArhMatrix mat;
  EXPECT_THROW(mat.GetMatrix(3, 3), std::length_error);
  EXPECT_THROW(mat.GetMatrix(-1, 0), std::length_error);
}

TEST(ArhMatrixSets, Rows) {
  ArhMatrix mat;
  EXPECT_EQ(mat.GetRows(), 2);
  mat.SetRows(5);
  EXPECT_EQ(mat.GetRows(), 5);
  EXPECT_EQ(mat(4, 0), 0);
}

TEST(ArhMatrixSets, RowsThrow) {
  ArhMatrix mat;
  EXPECT_THROW({ mat.SetRows(0); }, std::length_error);
}

TEST(ArhMatrixSets, Cols) {
  ArhMatrix mat;
  EXPECT_EQ(mat.GetCols(), 2);
  mat.SetCols(5);
  EXPECT_EQ(mat.GetCols(), 5);
  EXPECT_EQ(mat(0, 4), 0);
}

TEST(ArhMatrixSets, ColsThrow) {
  ArhMatrix mat;
  EXPECT_THROW({ mat.SetCols(0); }, std::length_error);
}

TEST(ArhMatrixOperatorRoundBrackets, Base) {
  ArhMatrix mat(2, 2);
  EXPECT_EQ(mat.GetMatrix(0, 0), mat(0, 0));
}

TEST(ArhMatrixOperatorRoundBrackets, Failer) {
  ArhMatrix mat(2, 2);
  EXPECT_THROW({ mat(2, 2) = 0; }, std::length_error);
}

TEST(ArhMatrixConstructions, Normal) {
  EXPECT_NO_THROW({
    ArhMatrix mat;
    EXPECT_EQ(mat.GetRows(), 2);
    EXPECT_EQ(mat.GetCols(), 2);
    EXPECT_EQ(mat(0, 0), 0);
    mat.FreeMatrix();
    EXPECT_EQ(mat.GetRows(), 0);
    EXPECT_EQ(mat.GetCols(), 0);
    EXPECT_EQ(mat.IsNullptrMat(), true);
  });
}

TEST(ArhMatrixConstructions, RowsCols) {
  EXPECT_NO_THROW({
    for (int i = 1; i < 20; ++i) {
      ArhMatrix mat(i, i + 1);
      EXPECT_EQ(mat.GetRows(), i);
      EXPECT_EQ(mat.GetCols(), i + 1);
      EXPECT_EQ(mat(i - 1, i), 0);
    }
  });
}

TEST(ArhMatrixConstructions, Failer) {
  EXPECT_THROW(ArhMatrix(0, 0);, std::length_error);
}

TEST(ArhMatrixConstructions, copy) {
  EXPECT_NO_THROW({
    ArhMatrix mat_first(1, 1);
    mat_first(0, 0) = -2;
    ArhMatrix mat_second(mat_first);
    EXPECT_EQ(mat_first(0, 0), mat_second(0, 0));
  });
}

// lvalue
TEST(ArhMatrixConstructions, Move) {
  EXPECT_NO_THROW({
    ArhMatrix mat_one(2, 2);
    mat_one(0, 0) = 43;
    mat_one(0, 1) = -3;
    mat_one(1, 0) = 2;
    mat_one(0, 1) = -1;

    ArhMatrix mat_two(mat_one + mat_one);
    EXPECT_EQ(mat_two(0, 0), 86);
  });
}

TEST(ArhMatrixDestructor, Normal) {

  ArhMatrix mat(3, 3);
  mat(0, 0) = 1;
  mat.~ArhMatrix();

  EXPECT_EQ(mat.GetRows(), 0);
  EXPECT_EQ(mat.GetCols(), 0);
  EXPECT_EQ(mat.IsNullptrMat(), true);
}

TEST(ArhMatrixOperatorAssig, Normal) {
  ArhMatrix mat_first(2, 2);
  ArhMatrix mat_second(2, 2);
  mat_first(0, 0) = 4;
  mat_first(0, 1) = 3;
  mat_first(1, 0) = 7;
  mat_first(1, 1) = 6;

  mat_second = mat_first;
  EXPECT_EQ(mat_second(0, 0), 4);
}

TEST(ArhMatrixEqMatrix, Equal) {
  ArhMatrix mat_first(2, 2);
  ArhMatrix mat_second(2, 2);
  EXPECT_EQ(mat_second.EqMatrix(mat_first), true);
}

TEST(ArhMatrixEqMatrix, NotEqual) {
  ArhMatrix mat_first(2, 2);
  ArhMatrix mat_second(2, 2);
  mat_second(0, 0) = 2;
  EXPECT_EQ(mat_second.EqMatrix(mat_first), false);
  mat_first.SetCols(3);
  mat_second(0, 0) = 0;
  EXPECT_EQ(mat_second.EqMatrix(mat_first), false);
}

TEST(ArhMatrixEqMatrix, EqualOp) {
  ArhMatrix mat_first(2, 2);
  ArhMatrix mat_second(2, 2);
  EXPECT_EQ(mat_second == mat_first, true);
}
TEST(ArhMatrixEqMatrix, NotEqualOp) {
  ArhMatrix mat_first(2, 2);
  ArhMatrix mat_second(2, 2);
  mat_second(0, 0) = 2;
  EXPECT_EQ(mat_second == mat_first, false);
  mat_first.SetCols(3);
  mat_second(0, 0) = 0;
  EXPECT_EQ(mat_second == mat_first, false);
}

TEST(ArhMatrixSumMatrix, NormalSit) {
  ArhMatrix mat_first(2, 2);
  ArhMatrix mat_second(2, 2);
  ArhMatrix check(2, 2);
  mat_first(0, 0) = 32;
  mat_first(0, 1) = 2;
  mat_first(1, 0) = 1;
  mat_first(1, 1) = -3;

  mat_second(0, 0) = 4;
  mat_second(0, 1) = -23;
  mat_second(1, 0) = 0.32;
  mat_second(1, 1) = 3;

  check(0, 0) = 36;
  check(0, 1) = -21;
  check(1, 0) = 1.32;
  check(1, 1) = 0;

  mat_first.SumMatrix(mat_second);
  EXPECT_EQ(check.EqMatrix(mat_first), true);
}

TEST(ArhMatrixSumMatrix, Failer) {
  EXPECT_THROW(
      {
        ArhMatrix mat_first(2, 2);
        ArhMatrix mat_second(3, 2);
        mat_first.SumMatrix(mat_second);
      },
      std::length_error);
}

TEST(ArhMatrixSumMatrix, NormalSitOp) {
  ArhMatrix mat_first(2, 2);
  ArhMatrix mat_second(2, 2);
  ArhMatrix res(2, 2);
  ArhMatrix check(2, 2);
  mat_first(0, 0) = 32;
  mat_first(0, 1) = 2;
  mat_first(1, 0) = 1;
  mat_first(1, 1) = -3;

  mat_second(0, 0) = 4;
  mat_second(0, 1) = -23;
  mat_second(1, 0) = 0.32;
  mat_second(1, 1) = 3;

  check(0, 0) = 36;
  check(0, 1) = -21;
  check(1, 0) = 1.32;
  check(1, 1) = 0;

  res = mat_first + mat_second;
  EXPECT_EQ(check.EqMatrix(res), true);
  mat_first += mat_second;
  EXPECT_EQ(check.EqMatrix(mat_first), true);
}

TEST(ArhMatrixSumMatrix, FailerOp) {
  EXPECT_THROW(
      {
        ArhMatrix mat_first(2, 2);
        ArhMatrix mat_second(3, 2);
        mat_first + mat_second;
        mat_first += mat_second;
      },
      std::length_error);
}

TEST(ArhMatrixSubMatrix, NormalSit) {

  for (int i = 0; i < 10; ++i) {
    ArhMatrix mat_first(i + 1, i + 2);
    ArhMatrix mat_second(i + 1, i + 2);
    ArhMatrix check(i + 1, i + 2);

    for (int r = 0; r < i + 1; ++r) {
      for (int c = 0; c < i + 2; ++c) {
        mat_first(r, c) = (2.3 + i) * pow(-1, i);
        mat_second(r, c) = (-1111.3 - i) * pow(-1, i);
        check(r, c) = mat_first(r, c) - mat_second(r, c);
      }
    }
    mat_first.SubMatrix(mat_second);
    EXPECT_EQ(check.EqMatrix(mat_first), true);
  }
}

TEST(ArhMatrixSubMatrix, Failer) {
  EXPECT_THROW(
      {
        ArhMatrix mat_first;
        ArhMatrix mat_second(3, 3);
        mat_first.SubMatrix(mat_second);
      },
      std::length_error);
}

TEST(ArhMatrixSubMatrix, NormalSitOp) {

  for (int i = 0; i < 10; ++i) {
    ArhMatrix mat_first(i + 1, i + 2);
    ArhMatrix mat_second(i + 1, i + 2);
    ArhMatrix check(i + 1, i + 2);
    ArhMatrix res(i + 1, i + 2);

    for (int r = 0; r < i + 1; ++r) {
      for (int c = 0; c < i + 2; ++c) {
        mat_first(r, c) = (2.3 + i) * pow(-1, i);
        mat_second(r, c) = (-1111.3 - i) * pow(-1, i);
        check(r, c) = mat_first(r, c) - mat_second(r, c);
      }
    }
    res = mat_first - mat_second;
    EXPECT_EQ(check.EqMatrix(res), true);
    mat_first -= mat_second;
    EXPECT_EQ(check.EqMatrix(mat_first), true);
  }
}

TEST(ArhMatrixSubMatrix, FailerOp) {
  EXPECT_THROW(
      {
        ArhMatrix mat_first;
        ArhMatrix mat_second(3, 3);
        mat_first - mat_second;
        mat_first -= mat_second;
      },
      std::length_error);
}

TEST(ArhMatrixMulNum, NormalSit) {
  ArhMatrix mat;
  mat(0, 0) = 10;
  mat(0, 1) = -23;
  mat(1, 0) = 6;
  mat(1, 1) = 5;
  mat.MulNumber(5);
  ArhMatrix check;
  check(0, 0) = 50;
  check(0, 1) = -115;
  check(1, 0) = 30;
  check(1, 1) = 25;
  EXPECT_EQ(check.EqMatrix(mat), true);
}

TEST(ArhMatrixMulNum, NormalSitOp) {
  ArhMatrix mat;
  ArhMatrix res;
  mat(0, 0) = 10;
  mat(0, 1) = -23;
  mat(1, 0) = 6;
  mat(1, 1) = 5;
  res = mat * 5;
  ArhMatrix check;
  check(0, 0) = 50;
  check(0, 1) = -115;
  check(1, 0) = 30;
  check(1, 1) = 25;
  EXPECT_EQ(check.EqMatrix(res), true);
  mat *= 5;
  EXPECT_EQ(check.EqMatrix(mat), true);
}

TEST(ArhMatrixMulMat, NormalSitOp) {
  ArhMatrix mat_first(3, 3);
  ArhMatrix mat_second(3, 3);
  ArhMatrix res(3, 3);

  ArhMatrix check(3, 3);

  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
      mat_first(r, c) = r + c + 7;
      mat_second(r, c) = c + 5 * r + 23;
    }
  }
  check(0, 0) = 682;
  check(0, 1) = 706;
  check(0, 2) = 730;

  check(1, 0) = 766;
  check(1, 1) = 793;
  check(1, 2) = 820;

  check(2, 0) = 850;
  check(2, 1) = 880;
  check(2, 2) = 910;

  res = mat_first * mat_second;

  EXPECT_EQ(check.EqMatrix(res), true);
  mat_first *= mat_second;
  EXPECT_EQ(check.EqMatrix(mat_first), true);
}

TEST(ArhMatrixMulMat, NormalSit) {
  ArhMatrix mat_first(2, 3);
  ArhMatrix mat_second(3, 2);

  mat_first(0, 0) = 1;
  mat_first(0, 1) = 2;
  mat_first(0, 2) = 3;

  mat_first(1, 0) = 6;
  mat_first(1, 1) = 4;
  mat_first(1, 2) = 5;

  mat_second(0, 0) = 1;
  mat_second(0, 1) = 8;

  mat_second(1, 0) = 7;
  mat_second(1, 1) = 6;

  mat_second(2, 0) = 4;
  mat_second(2, 1) = 2;

  ArhMatrix check(2, 2);

  check(0, 0) = 27;
  check(0, 1) = 26;

  check(1, 0) = 54;
  check(1, 1) = 82;

  mat_first.MulMatrix(mat_second);

  EXPECT_EQ(check.EqMatrix(mat_first), true);
}

TEST(ArhMatrixMulMat, FailerOp) {
  ArhMatrix mat_1;
  ArhMatrix mat_2(1, 1);
  EXPECT_THROW(
      {
        mat_1 *mat_2;
        mat_1 *= mat_2;
      },
      std::length_error);
}

TEST(ArhMatrixMulMat, Failer) {
  ArhMatrix mat_1;
  ArhMatrix mat_2(1, 1);
  EXPECT_THROW(mat_1.MulMatrix(mat_2), std::length_error);
}

TEST(ArhMatrixTranspose, Normal) {
  ArhMatrix mat(2, 2);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(1, 0) = 3;
  mat(1, 1) = 4;
  ArhMatrix check(2, 2);
  check(0, 0) = 1;
  check(0, 1) = 3;
  check(1, 0) = 2;
  check(1, 1) = 4;
  EXPECT_EQ(check.EqMatrix(mat.Transpose()), true);
}

TEST(ArhMatrixMinor, Normal) {
  ArhMatrix mat(3, 3);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(0, 2) = 3;
  mat(1, 0) = 0;
  mat(1, 1) = 4;
  mat(1, 2) = 2;
  mat(2, 0) = 5;
  mat(2, 1) = 2;
  mat(2, 2) = 1;
  ArhMatrix check(2, 2);
  check(0, 0) = 4;
  check(0, 1) = 2;
  check(1, 0) = 2;
  check(1, 1) = 1;

  mat = mat.Minor(0, 0);
  EXPECT_EQ(check == mat, true);
}

TEST(ArhMatrixMinor, Failer) {
  ArhMatrix mat(1, 1);
  EXPECT_THROW({ mat = mat.Minor(2, 2); }, std::length_error);
}

TEST(ArhMatrixCalcComplements, Normal) {
  ArhMatrix mat(3, 3);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(0, 2) = 3;
  mat(1, 0) = 0;
  mat(1, 1) = 4;
  mat(1, 2) = 2;
  mat(2, 0) = 5;
  mat(2, 1) = 2;
  mat(2, 2) = 1;

  ArhMatrix check(3, 3);

  check(0, 0) = 0;
  check(0, 1) = 10;
  check(0, 2) = -20;
  check(1, 0) = 4;
  check(1, 1) = -14;
  check(1, 2) = 8;
  check(2, 0) = -8;
  check(2, 1) = -2;
  check(2, 2) = 4;

  EXPECT_EQ(check == mat.CalcComplements(), true);
}

TEST(ArhMatrixCalcComplements, Failer) {
  ArhMatrix mat(3, 2);
  EXPECT_THROW({ mat = mat.CalcComplements(); }, std::length_error);
}

TEST(ArhMatrixDeterminant, Normal) {
  ArhMatrix mat(3, 3);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(0, 2) = 3;
  mat(1, 0) = 4;
  mat(1, 1) = 5;
  mat(1, 2) = 6;
  mat(2, 0) = 7;
  mat(2, 1) = 8;
  mat(2, 2) = 9;

  double check = 0;
  EXPECT_EQ(check, mat.Determinant());
}

TEST(ArhMatrixDeterminant, Failer) {
  ArhMatrix mat(3, 2);

  EXPECT_THROW({ mat.Determinant(); }, std::length_error);
}

TEST(ArhMatrixInverseMatrix, Normal) {
  ArhMatrix mat(3, 3);
  mat(0, 0) = 2;
  mat(0, 1) = 5;
  mat(0, 2) = 7;
  mat(1, 0) = 6;
  mat(1, 1) = 3;
  mat(1, 2) = 4;
  mat(2, 0) = 5;
  mat(2, 1) = -2;
  mat(2, 2) = -3;

  ArhMatrix check(3, 3);

  check(0, 0) = 1;
  check(0, 1) = -1;
  check(0, 2) = 1;
  check(1, 0) = -38;
  check(1, 1) = 41;
  check(1, 2) = -34;
  check(2, 0) = 27;
  check(2, 1) = -29;
  check(2, 2) = 24;

  EXPECT_NO_THROW({ EXPECT_EQ(check == mat.InverseMatrix(), true); });
}

TEST(ArhMatrixInverseMatrix, Failer) {
  ArhMatrix mat(3, 3);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(0, 2) = 3;
  mat(1, 0) = 4;
  mat(1, 1) = 5;
  mat(1, 2) = 6;
  mat(2, 0) = 7;
  mat(2, 1) = 8;
  mat(2, 2) = 9;
  EXPECT_THROW({ mat = mat.InverseMatrix(); }, std::length_error);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
