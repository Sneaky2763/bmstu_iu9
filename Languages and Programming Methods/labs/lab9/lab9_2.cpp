#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class Frac {
private:
    int num;
    int denom;

public:
    void simplify() {
        if(denom<0) {
            num*=-1;
            denom*=-1;
        }
        
        int target=gcd(abs(num), abs(denom));
        if (target>1) {
            num/=target;
            denom/=target;
        }
    }
    Frac(int num=0, int denom=1): num(num), denom(denom){
        simplify();
    }
    int getnum() const {
        return num;
    }
    int getdenom() const {
        return denom;
    }

    Frac operator+(const Frac& other) const {
        int new_num=num*other.denom+other.num*denom;
        int new_den=denom*other.denom;
        return Frac(new_num, new_den);
    }

    Frac operator-(const Frac& other) const {
        int new_num=num*other.denom-other.num*denom;
        int new_den=denom*other.denom;
        return Frac(new_num, new_den);
    }

    Frac operator*(const Frac& other) const {
        int new_num=num*other.num;
        int new_den=denom*other.denom;
        return Frac(new_num, new_den);
    }

    Frac operator/(const Frac& other) const {
        int new_num=num*other.denom;
        int new_den=denom*other.num;
        return Frac(new_num, new_den);
    }
    bool operator==(const Frac& other) const {
        return num==other.num && denom==other.denom;
    }


    void print() const {
        cout << "(" << num << "/" << denom << ")";
    }
};


template<int N>
class PolyEq {
private:
    vector<Frac> coefficients;

public:
    PolyEq(): coefficients(N + 1) {}

    PolyEq(const vector<Frac>& coeffs): coefficients(coeffs) {
        if (coeffs.size()!=N+1) {
            throw invalid_argument("Invalid number of coefficients");
        }
    }

    Frac operator[](size_t index) const {
        return coefficients[index];
    }
    
    Frac& operator[](size_t index) {
        return coefficients[index];
    }

    PolyEq operator*(const Frac& k) const {
        PolyEq result;
        for (int i=0; i<=N; ++i) {
            result[i]=coefficients[i]*k;
        }
        return result;
    }


    PolyEq operator+(const PolyEq& other) const {
        PolyEq result;
        for (int i=0; i<=N; ++i) {
            result[i]=coefficients[i]+other.coefficients[i];
        }
        return result;
    }

    PolyEq<N-1> operator/(const PolyEq<1>& divisor) const {
        Frac a=divisor[0];
        Frac b=divisor[1];
    
        vector<Frac> quotient_coeffs(N);
        vector<Frac> dividend=coefficients;
    
        for (int i=0; i<N; ++i){
            quotient_coeffs[i]=dividend[i]/a;
            dividend[i+1]=dividend[i+1]-(quotient_coeffs[i]*b);
        }
    
        return PolyEq<N-1>(quotient_coeffs);
    }

    bool operator()(const Frac& x) const {
        Frac result(0);
        
        for (int i=0; i<=N; ++i) {
            result=result*x+coefficients[i];
        }
        
        return result==Frac(0);
    }

    void print() const {
        for(int i=0; i<N+1; ++i){
            coefficients[i].print();
            if(i!=N){
                cout << "x^" << N-i << " + ";
            }
        }
        cout << endl;
    }
};

int main() {
    Frac a(1, 2), b(3, 4), c(2, 3), d(1, 5), e(1, 8);

    PolyEq<2> poly1({a, b, c});
    PolyEq<2> poly2=poly1*Frac(3, 1);
    poly1.print();
    poly2.print();

    PolyEq<2> poly3=poly1+poly2;
    poly3.print();

    PolyEq<1> poly4({a, b});
    PolyEq<1> poly5=poly1/poly4;
    poly5.print();

    PolyEq<1> poly6({Frac(1), Frac(0)});
    poly6.print();
    cout << poly6(Frac(1, 2)) << endl;
    cout << poly6(Frac(0)) << endl;
    return 0;
}