#include "lab7test.h"

#include <algorithm>

using namespace std;

Matrix::Matrix(int n) : n(n) {
    data=new string*[n];
    for (int i=0; i<n; ++i) {
        data[i]=new string[n];
    }
}

Matrix::~Matrix() {
    for (int i=0; i<n; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

Matrix::Matrix(const Matrix& m) : n(m.n) {
    data=new string*[n];
    for (int i=0; i<n; ++i) {
        data[i]=new string[n];
        for (int j=0; j<n; ++j) {
            data[i][j]=m.data[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& m) {
    for (int i=0; i<n; ++i) {
        delete[] data[i];
    }
    delete[] data;

    n=m.n;
    data=new string*[n];
    for (int i=0; i<n; ++i) {
        data[i]=new string[n];
        for (int j=0; j<n; ++j) {
            data[i][j]=m.data[i][j];
        }
    }

    return *this;
}

int Matrix::get_size(){
    return n;
}

string& Matrix::get_element(int i, int j){
    return data[i][j];
}

bool Matrix::saddle_point(int i, int j){
    bool min_row=true;
    for (int col=0; col<n; ++col) {
        if (data[i][col]<data[i][j]) {
            min_row=false;
            break;
        }
    }
    bool max_col=true;
    for (int row=0; row<n; ++row) {
        if (data[row][j]>data[i][j]) {
            max_col=false;
            break;
        }
    }

    return min_row && max_col;
}

string& Matrix::Row::operator[](int col) {
    return matrix->data[row][col];
}