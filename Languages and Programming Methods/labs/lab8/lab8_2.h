#ifndef FIXNUM_H
#define FIXNUM_H

#include <array>
#include <cmath>

using namespace std;

template<int N, int M>
class FixNum {
private:
    array<int, N> data{};

public:
    FixNum(){
        array<int, N> data{};
    }

    FixNum(double value){
        int intpart=floor(value);
        data[0]=(int)(intpart) << M;
        data[0]|=(int)((value-intpart)*(1 << M));
    }

    FixNum operator+(const FixNum& other){
        FixNum result;
        int carry=0;
        for (int i=N-1; i>=0; --i) {
            long long sum=(long long)(data[i])+other.data[i]+carry;
            result.data[i]=(int)(sum);
            carry=(int)(sum >> 32);
        }
        return result;
    }

    operator double(){
        double result = 0;
        for (int val: data) {
            result+=(val >> M)+(double)(val & ((1 << M) - 1)) / (1 << M);
        }
        return result;
    }
};

template<int M>
class FixNum<1, M> {
private:
    int value=0;

public:
    FixNum(){
        value=0;
    }

    FixNum(double val) {
        int intpart=floor(val);
        value=(int)(intpart) << M;
        value|=(int)((val-intpart)*(1 << M));
    }

    FixNum<1, M> operator+(FixNum<1, M>& other){
        return FixNum<1, M>((double)(*this)+(double)(other));
    }

    operator double(){
        return (value >> M)+(double)(value & ((1 << M) - 1)) / (1 << M);
    }
};

#endif