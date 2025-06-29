#ifndef MATRIX_H
#define MATRIX_H

#include <string>

using namespace std;

class Matrix {
private:
    int n;
    string **data;

public:
    Matrix(int n);
    ~Matrix();
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    int get_size();
    string& get_element(int i, int j);
    bool saddle_point(int i, int j);

    class Row {
    private:
        Matrix* matrix;
        int row;
    public:
        Row(Matrix* m, int r) : matrix(m), row(r) {}
        string& operator[](int col);
    };

    Row operator[](int row) {
        return Row(this, row);
    }
};

#endif