#include <iostream>
#include "lab8_2.h"

using namespace std;

int main() {
    FixNum<2, 7> a(1.5);
    FixNum<2, 7> b(2.75);
    FixNum<2, 7> c=a+b;
    
    cout << "a=" << (double)(a) << endl;
    cout << "b=" << (double)(b) << endl;
    cout << "a+b=" << (double)(c) << endl;

    FixNum<1, 16> d(3.14159);
    FixNum<1, 16> e(2.71828);
    FixNum<1, 16> f=d+e;
    
    cout << "d=" << (double)(d) << endl;
    cout << "e=" << (double)(e) << endl;
    cout << "d+e=" << (double)(f) << endl;
    
    return 0;
}