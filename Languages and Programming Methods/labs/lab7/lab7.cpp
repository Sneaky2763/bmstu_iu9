#include "lab7.h"

#include <iostream>

using namespace std;

void print(Matrix matrix) {
    cout << "Элементы текущей матрицы:" << endl;
    for(int i=0; i<matrix.get_rows(); ++i){
        for(int j=0; j<matrix.get_cols(); ++j){
            cout << matrix.get_element(i, j) << " ";
        }
        cout << endl;
    }
}

int main() {
    Matrix m(2, 3);
    m[0][0]=1;
    m[0][1]=2;
    m[0][2]=3;
    m[1][0]=4;
    m[1][1]=5;
    m[1][2]=6;
    
    print(m);
    cout << "Количество строк: " << m.get_rows() << endl;
    cout << "Количество столбцов: " << m.get_cols() << endl;

    m.multiply(3);
    print(m);

    Matrix m2=m.transpond();
    print(m2);

    return 0;
}