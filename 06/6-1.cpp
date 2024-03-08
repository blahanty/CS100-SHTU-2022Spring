#include <cstddef>
#include <cmath>
#include <iostream>

class Matrix {
public:
    typedef double Scalar;
    typedef std::size_t Index;

    explicit Matrix(Index rows, Index cols) {
        row = rows;
        col = cols;
        mat = new Scalar *[row];
        for (int i = 0; i < row; i++) {
            mat[i] = new Scalar[col];
            for (int j = 0; j < col; j++)
                mat[i][j] = 0;
        }
    }

    Matrix(const Matrix &other) {
        row = other.row;
        col = other.col;
        mat = new Scalar *[row];
        for (int i = 0; i < row; i++) {
            mat[i] = new Scalar[col];
            for (int j = 0; j < col; j++)
                mat[i][j] = other.mat[i][j];
        }
    }

    Matrix &operator=(const Matrix &other) {
        if (this != &other) {
            for (int i = 0; i < row; i++)
                delete[] mat[i];
            delete[] mat;
            row = other.row;
            col = other.col;
            mat = new Scalar *[row];
            for (int i = 0; i < row; i++) {
                mat[i] = new Scalar[col];
                for (int j = 0; j < col; j++)
                    mat[i][j] = other.mat[i][j];
            }
        }
        return *this;
    }

    ~Matrix() {
        for (int i = 0; i < row; i++)
            delete[] mat[i];
        delete[] mat;
    }

    Index rows() const {
        return row;
    }

    Index cols() const {
        return col;
    }

    Scalar &at(Index r, Index c) {
        return mat[r][c];
    }

    const Scalar &at(Index r, Index c) const {
        return mat[r][c];
    }

    Matrix operator+(const Matrix &other) const {
        Matrix m(row, col);
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                m.mat[i][j] = this->mat[i][j] + other.mat[i][j];
        return m;
    }

    Matrix operator-(const Matrix &other) const {
        Matrix m(row, col);
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                m.mat[i][j] = this->mat[i][j] - other.mat[i][j];
        return m;
    }

    Matrix operator*(const Matrix &other) const {
        Matrix m(row, other.col);
        for (int i = 0; i < row; i++)
            for (int j = 0; j < other.col; j++)
                for (int k = 0; k < col; k++)
                    m.mat[i][j] += mat[i][k] * other.mat[k][j];
        return m;
    }

    Matrix transpose() const {
        Matrix m(col, row);
        for (int i = 0; i < col; i++)
            for (int j = 0; j < row; j++)
                m.mat[i][j] = mat[j][i];
        return m;
    }

    Matrix block(Index r, Index c, Index p, Index q) const { // Block of size p x q, starting at (r,c)
        Matrix m(p, q);
        for (int i = 0; i < p; i++)
            for (int j = 0; j < q; j++)
                m.mat[i][j] = mat[i + r][j + c];
        return m;
    }

    Scalar trace() const { // For square matrix
        Scalar tr = 0;
        for (int i = 0; i < row; i++)
            tr += mat[i][i];
        return tr;
    }

    Scalar determinant() const { // For square matrix
        return cal_det(*this);
    }

private:
// Define your private member variables and functions here
    Index row, col;
    Scalar **mat;

    Scalar cal_det(const Matrix &tar) const {
        if (tar.row == 1)
            return tar.mat[0][0];
        else {
            Matrix new_tar(tar.row - 1, tar.col - 1);
            int curC;
            Scalar det = 0;
            for (int i = 0; i < tar.col; i++) {
                for (int j = 0; j < tar.row - 1; j++) {
                    curC = 0;
                    for (int k = 0; k < tar.col - 1; k++) {
                        if (k == i)
                            curC++;
                        new_tar.mat[j][k] = tar.mat[j + 1][curC++];
                    }
                }
                det += pow(-1, i) * tar.mat[0][i] * cal_det(new_tar);
            }
            return det;
        }
    }
};
