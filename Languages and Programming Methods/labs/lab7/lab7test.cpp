#include "lab7test.h"

#include <iostream>

using namespace std;

void top_left(Matrix matrix) {
    cout << "Элемент сверху слева:\"" << matrix[0][0] << "\"" << endl;
}

int main() {
    Matrix m(2);
    m[0][0]="a";
    m[0][1]="b";
    m[1][0]="c";
    m[1][1]="d";

    cout << "Размер матрицы:" << m.get_size() << endl;

    top_left(m);

    Matrix m2(2);
    m2 = m; 
    
    top_left(m2);

    for (int i=0; i<m.get_size(); ++i) {
        for (int j=0; j<m.get_size(); ++j) {
            if (m.saddle_point(i, j)) {
                cout<<"Элемент \"" << m.get_element(i, j) << "\" является седловой точкой" << endl;
            } else {
                cout<<"Элемент \"" << m.get_element(i, j) << "\" не является седловой точкой" << endl;
            }
        }
    }

    return 0;
}