#pragma once

#include "inc.h"
#include "vector.h"



class Matrix{
private:
size_t rows;
size_t cols;
vector<double> data;

size_t index(size_t i, size_t j) const {
    return i * cols + j;
}



public:
    Matrix(size_t n_rows, size_t n_cols, double init = 0.0)
        : rows(n_rows), cols(n_cols), data(n_rows * n_cols, init) {}


    size_t numRows() const {return rows;}
    size_t numCols() const {return cols;}

    double& operator()(size_t i, size_t j) {
        return data[index(i, j)];
    }
    const double& operator()(size_t i, size_t j) const {
        return data[index(i, j)];
    }




    void print() const {
        for (size_t i = 0; i < rows; ++i) {
            std::cout << "[";
            for (size_t j = 0; j < cols; ++j) {
                std::cout << (*this)(i, j);
                if (j != cols - 1) std::cout << ", ";
            }
            std::cout << "]\n";
        }
    }



    
    Vector operator*(const Vector& vec) const {
        assert(vec.size() == cols);
        Vector result(rows);
        for (size_t i = 0; i < rows; ++i) {
            double sum = 0.0;
            for (size_t j = 0; j < cols; ++j) {
                sum += (*this)(i, j) * vec[j];
            }
            result[i] = sum;
        }
        return result;
    }

    Vector getRow(size_t i) const {
        Vector result(cols);
        for (size_t j = 0; j < cols; ++j)
            result[j] = (*this)(i, j);
        return result;
    }

    void setRow(size_t i, const Vector& vec) {
        assert(vec.size() == cols);
        for (size_t j = 0; j < cols; ++j)
            (*this)(i, j) = vec[j];
    }




};