#include "lab7.h"

#include <algorithm>

using namespace std;

Matrix::Matrix(int n, int m) : n(n), m(m) {
    data=new int*[n];
    for (int i=0; i<n; ++i) {
        data[i]=new int[m];
    }
}

Matrix::~Matrix() {
    for (int i=0; i<n; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

Matrix::Matrix(const Matrix& matrix) : n(matrix.n), m(matrix.m) {
    data=new int*[n];
    for (int i=0; i<n; ++i) {
        data[i]=new int[m];
        for (int j=0; j<m; ++j) {
            data[i][j]=matrix.data[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& matrix) {
    for (int i=0; i<n; ++i) {
        delete[] data[i];
    }
    delete[] data;

    n=matrix.n;
    m=matrix.m;
    data=new int*[n];
    for (int i=0; i<n; ++i) {
        data[i]=new int[m];
        for (int j=0; j<m; ++j) {
            data[i][j]=matrix.data[i][j];
        }
    }

    return *this;
}

int Matrix::get_rows(){
    return n;
}

int Matrix::get_cols(){
    return m;
}

int& Matrix::get_element(int i, int j){
    return data[i][j];
}

void Matrix::multiply(int k){
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            data[i][j]*=k;
        }
    }
}

Matrix Matrix::transpond(){
    Matrix t(m, n);
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            t.data[j][i]=data[i][j];
        }
    }
    return t;
}

int& Matrix::Row::operator[](int col) {
    return matrix->data[row][col];
}