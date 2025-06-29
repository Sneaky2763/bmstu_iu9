#include "lab8.h"

#include <stdio.h>

int main(){
    RangeSet<1, 100> s1;
    
    s1.add(2, 5);
    s1.add(4, 1);
    s1.add(6, 6);

    cout << s1.checkval(8) << endl;
    cout << s1.checkval(10) << endl;
    cout << s1.checkval(1) << endl;
    cout << s1.checkval(15) << endl;
}