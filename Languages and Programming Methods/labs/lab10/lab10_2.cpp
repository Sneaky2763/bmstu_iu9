#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Frac{
private:
    int num;
    int denom;

public:
    void simplify(){
        if(denom<0){
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
    bool operator<(const Frac& other) const {
        Frac res=(*this)/other;
        return res.getnum()<res.getdenom();
    }
    bool operator==(const Frac& other) const {
        return num==other.num && denom==other.denom;
    }

    void print() const {
        cout << "(" << num << "/" << denom << ")";
    }
};

class FracMulOne {
private:
    set<Frac> fracs;
    vector<pair<Frac, Frac>> mul_one;
    
    bool check_mul(Frac a, Frac b){
        Frac res=a*b; 
        if(res.getnum()==1 && res.getdenom()==1){
            return true;
        }
        return false;
    }

    void initialize(vector<Frac> vals){
        for(int i=0; i<vals.size(); ++i){
            fracs.insert(vals[i]);
        }
        for(int i=1; i<fracs.size(); ++i){
            for(int j=0; j<i; ++j){
                Frac a=*next(fracs.begin(), i);
                Frac b=*next(fracs.begin(), j);

                if(check_mul(a, b)){
                    mul_one.push_back({a, b});
                }
            }
        }
    }

public:
    FracMulOne(vector<Frac> nums){
        initialize(nums);
    }

    class const_iterator{
    private:
        const vector<pair<Frac, Frac>> *mul_one;
        size_t index;
        
    public:
        const_iterator(const vector<pair<Frac, Frac>> *t, size_t i): mul_one(t), index(i) {}
            
        const pair<Frac, Frac>& operator*() const{
            return (*mul_one)[index];
        }
        
        const_iterator& operator++(){
            ++index;
            return *this;
        }
        
        bool operator!=(const const_iterator& other) const{
            return index!=other.index;
        }
    };
    
    const_iterator begin() const{
        return const_iterator(&mul_one, 0);
    }
    
    const_iterator end() const{
        return const_iterator(&mul_one, mul_one.size());
    }
};

int main(){
    vector<Frac> vals={Frac(1, 2), Frac(2, 1), Frac(5, 3), Frac(4, 5), Frac(3, 5), Frac(10, 11)};
    FracMulOne fracs(vals);
    
    cout << "Дроби, произведение которых равно 1: " << endl;
    for (auto it=fracs.begin(); it!=fracs.end(); ++it){
        auto [a, b]=*it;
        cout << "(";
        a.print();
        cout << ", ";
        b.print();
        cout << ")" << endl;
    }

    return 0;
}