#include <iostream>
#include <cassert>
#include "matrix.hpp"

using namespace std;

// Constructors

Matrix :: Matrix(int rows, int cols){
    (*this).rows = rows;
    (*this).cols = cols;
    data.resize(rows * cols);
}

Matrix :: Matrix(const Matrix &other){
    (*this).rows = other.rows;
    (*this).cols = other.cols;
    (*this).data = other.data;
}

// Getters for the number of rows and columns

int Matrix :: numRows() const{
    return rows;
}

int Matrix :: numCols() const{
    return cols;
}

// Basic access

double Matrix :: get(int i, int j) const{
    return data.at( i * cols + j );
}

void Matrix :: set(int i, int j, double value){
    data.at( i * cols + j ) = value;
}

// Fill the entire matrix with a single value.

void Matrix :: fill(double value){
    data.assign(rows * cols, value);
}

// Elementary operations

Matrix Matrix :: operator+(const Matrix &other) const{

    assert(rows == other.rows && cols == other.cols);

    Matrix temp (rows, cols);

    for (int i = 0; i < rows * cols ; i++)
    {
        temp.data[i] = data[i] + other.data[i];
    }
    
    return temp;
}

// Elementary operations

Matrix Matrix :: operator-(const Matrix &other) const{

    assert(rows == other.rows && cols == other.cols);

    Matrix temp (rows, cols);

    for (int i = 0; i < rows * cols ; i++)
    {
        temp.data[i] = data[i] - other.data[i];
    }
    
    return temp;
}

Matrix Matrix :: operator*(const Matrix &other) const{

    assert(cols == other.rows);

    Matrix temp (rows, other.cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < other.cols; j++)
        { 
            double sum = 0.;
            for (int k = 0; k < cols; k++)
            {
                sum += data[i * cols + k] * other.data[k * other.cols + j];
            }
            temp.data[i * other.cols + j] = sum;
        }
        
    }

    return temp;

}

Matrix Matrix :: operator*(double scalar) const{

    Matrix temp (rows, cols);

    for (int i = 0; i < rows * cols; i++)
    {
        temp.data[i] = data[i] * scalar;
    }
    
    return temp;
}

// Transpose

Matrix Matrix :: transpose() const{

    Matrix temp (cols, rows);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            temp.data[j * rows + i] = data[i * cols + j];
        }   
    }
    
    return temp;
}

Matrix Matrix :: apply(const std::function<double(double)> &func) const{

    Matrix temp (rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            temp.set(i, j, func(get(i, j)));
        }
    }
    return temp;
}

void Matrix :: sub_mul(double scalar, const Matrix &other){
    *this = *this - (other * scalar);
}