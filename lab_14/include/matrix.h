#ifndef LAB14_MATRIX_H_INCLUDED
#define LAB14_MATRIX_H_INCLUDED

#include <assert.h>
#include <string.h>
#include <vector>
#include <array>
#include <iosfwd>

class MatrixException final {
public:
    enum class Error {
        mul_error,
        add_error,
        index_error,
        file_error,
        load_error
    };

    explicit MatrixException(Error error) noexcept;
    const char * message() const noexcept;
private:
    Error error_; 
};

class Matrix final {
public:
    explicit Matrix (int32_t rows = 0, int32_t cols = 0);
    Matrix (const Matrix &);
    Matrix & operator+= (const Matrix &);
    Matrix & operator*= (const Matrix &);
    Matrix & operator= (Matrix );
    void swap (Matrix &);
    int32_t get_elem (int32_t i, int32_t j) const;
    std::ostream& operator<< (std::ostream& os) const;
    std::ifstream& operator>> (std::ifstream& ifs);  
private:
    int32_t rows_;
    int32_t cols_;
    std::vector<std::vector<int32_t>> matrix_;
};

std::ostream& operator<< (std::ostream& os, const Matrix & matrix);
std::ifstream& operator>> (std::ifstream& ifs,  Matrix & matrix);


class MatrixArray final {
public:
    void print (size_t i) const;
    void load (size_t i, const std::string & filename);
    void add (size_t i, size_t j);
    void mul (size_t i, size_t j);
    void elem (size_t i, int32_t row, int32_t col) const;
private:
    static constexpr size_t size_ = 10;
    std::array<Matrix, size_> storage_;
};

#endif