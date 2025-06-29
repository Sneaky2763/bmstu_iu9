#ifndef MATRIX_H
#define MATRIX_H

#include <string>

using namespace std;

class Matrix {
private:
    int n;
    int m;
    int **data;

public:
    Matrix(int n, int m);
    ~Matrix();
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    int get_rows();
    int get_cols();
    int& get_element(int i, int j);
    void multiply(int k);
    Matrix transpond();


    class Row {
    private:
        Matrix* matrix;
        int row;
    public:
        Row(Matrix* m, int r) : matrix(m), row(r) {}
        int& operator[](int col);
    };

    Row operator[](int row) {
        return Row(this, row);
    }
};

#endif