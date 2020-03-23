#include <iostream>
#include <fstream>
#include <assert.h>
#include "matrix.h"

MatrixException::MatrixException(Error error) noexcept : error_(error) {}

const char * MatrixException::message() const noexcept {
    switch (error_) {
        case Error::mul_error:
             return "MUL: #arg1.columns != #arg2.rows.\n";
        case Error::add_error:
            return "ADD: dimensions do not match.\n";
        case Error::index_error:
            return "ACCESS: bad index.\n";
        case Error::file_error:
            return "LOAD: invalid file format.\n";
        case Error::load_error:
            return "LOAD: unable to open file.\n";
    }
    assert (false);
    return nullptr;
}

void MatrixArray::print (size_t i) const {
    std::cout << storage_[i];
}

void MatrixArray::add (size_t i, size_t j) {
    storage_[i] += storage_[j];
}

void MatrixArray::mul (size_t i, size_t j) {
    storage_[i] *= storage_[j];
}

void MatrixArray::elem(size_t i, int32_t row, int32_t col) const {
    std::cout << storage_[i].get_elem(row, col) << '\n';
}

void MatrixArray::load(size_t i, const std::string & filename) {
    std::ifstream fin;
    fin.open(filename);
    if (!fin) {
        throw MatrixException(MatrixException::Error::load_error);
    }
    fin >> storage_[i];
    fin.close();
}

Matrix::Matrix(int32_t rows, int32_t cols) 
    : rows_(rows)
    , cols_(cols)
    , matrix_(std::vector<std::vector<int32_t>> (rows, std::vector<int32_t>(cols, 0))) {}

Matrix::Matrix(const Matrix & other) 
    : rows_(other.rows_)
    , cols_(other.cols_)
    , matrix_(other.matrix_) {}

Matrix & Matrix::operator+= (const Matrix & add) {
    if (this->rows_ != add.rows_ || this->cols_ != add.cols_) {
        throw MatrixException(MatrixException::Error::add_error);
    }
    for (int32_t i = 0; i < rows_; i++) {
        for (int32_t j = 0; j < cols_; j++) {
             this->matrix_[i][j] += add.matrix_[i][j];
        }
    }
    return *this;
}

Matrix & Matrix::operator*= (const Matrix & add) {
    if (this->cols_ != add.rows_) {
        throw MatrixException(MatrixException::Error::mul_error);
    }
    int32_t res_rows = this->rows_;
    int32_t res_cols = add.cols_;
    Matrix tmp(res_rows, res_cols);
    for (int32_t i = 0; i < res_rows; i++) {
        for (int32_t j = 0; j < res_cols; j++) {
            for (int32_t k = 0; k < this->cols_; k++) {
                tmp.matrix_[i][j] += this->matrix_[i][k] * add.matrix_[k][j];
            }
        }
    }
    swap(tmp);
    return *this; 
}

void Matrix::swap(Matrix & other) {
    std::swap(other.matrix_, this->matrix_);
    std::swap(other.rows_, this->rows_);
    std::swap(other.cols_, this->cols_);
}

Matrix & Matrix::operator= (Matrix other) {
    swap(other);
    return *this;
}

int32_t Matrix::get_elem(int32_t i, int32_t j) const {
    if (i >= rows_ || i < 0 || j >= cols_ || j < 0) {
        throw MatrixException(MatrixException::Error::index_error);
    }
    return matrix_[i][j];
}

std::ifstream & operator>>(std::ifstream & ifs,  Matrix & matrix) {
    return matrix >> ifs;
} 

std::ifstream & Matrix::operator>>(std::ifstream & ifs) {
    Matrix tmp;
    ifs >> tmp.rows_ >> tmp.cols_;
    if (ifs.bad() || ifs.fail()) {
        throw MatrixException(MatrixException::Error::file_error);
    }
    tmp.matrix_.resize(tmp.rows_, std::vector<int32_t>(tmp.cols_));
    for (int32_t i = 0; i < tmp.rows_; i++) {
        for (int32_t j = 0; j < tmp.cols_; j++) {
            ifs >> tmp.matrix_[i][j];
        }
    } 
    if (ifs.bad() || ifs.fail()) {
        throw MatrixException(MatrixException::Error::file_error);
    }  
    swap(tmp);
    return ifs;
}

std::ostream & operator<<(std::ostream & os, const Matrix & matrix) {
    return matrix << os;
}

std::ostream & Matrix::operator<<(std::ostream & os) const {
    for (int32_t i = 0; i < rows_; i++) {
        for (int32_t j = 0; j < cols_; j++) {
             os << matrix_[i][j] << ' ';
        }
        os << '\n';
    }   
    return os;
}

