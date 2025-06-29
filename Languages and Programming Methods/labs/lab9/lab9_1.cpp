#include <iostream>
#include <vector>
#include <stack>

using namespace std;

template<typename T>
class PtrStack{
private:
    stack<T*> pointers;

public:
    PtrStack& operator<<(T* ptr){
        pointers.push(ptr);
        return *this;
    }
    PtrStack& operator>>(T*& ptr){
        if(!pointers.empty()){
            ptr=pointers.top();
            pointers.pop();
        }
        return *this;
    }
    bool empty(){
        return pointers.empty();
    }
    T& operator*(){
        return *(pointers.top());
    }
    T* operator->(){
        return pointers.top();
    }
};

struct Point {
    int x, y;
    void print(){
         cout << "(" << x << ", " << y << ")" << endl;
    }
};

int main() {
    PtrStack<Point> stack;
    Point p1{1, 2};
    Point p2{3, 4};
    
    stack << &p1 << &p2;
    
    (*stack).print();

    Point* ptr;
    stack >> ptr;
    ptr->print();

    stack->print();
    
    return 0;
}