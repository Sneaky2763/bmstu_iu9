#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class PythagoreanTriples {
private:
    set<int> numbers;
    vector<tuple<int, int, int>> triples;
    
    bool check_triple(int a, int b, int c){
        if(a*a+b*b==c*c || a*a+c*c==b*b || b*b+c*c==a*a){
            return true;
        }
        return false;
    }

    void initialize(vector<int> nums){
        for(int i=0; i<nums.size(); ++i){
            numbers.insert(nums[i]);
        }

        for(int i=2; i<numbers.size(); ++i){
            for(int j=1; j<i; ++j){
                for(int k=0; k<j; ++k){
                    int a=*next(numbers.begin(), i);
                    int b=*next(numbers.begin(), j);
                    int c=*next(numbers.begin(), k);

                    if(check_triple(a, b, c)){
                        triples.push_back({a, b, c});
                    }
                }
            }
        }
    }

public:
    PythagoreanTriples(vector<int> nums){
        initialize(nums);
    }

    class const_iterator{
    private:
        const vector<tuple<int, int, int>> *triples;
        size_t index;
        
    public:
        const_iterator(const vector<tuple<int, int, int>> *t, size_t i): triples(t), index(i) {}
            
        const tuple<int, int, int>& operator*() const{
            return (*triples)[index];
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
        return const_iterator(&triples, 0);
    }
    
    const_iterator end() const{
        return const_iterator(&triples, triples.size());
    }
};

int main(){
    vector<int> nums={2, 3, 4, 5, 10, 15, 6, 8};
    PythagoreanTriples triples(nums);
    
    cout << "Пифагоровы тройки: " << endl;
    for (auto it=triples.begin(); it!=triples.end(); ++it){
        auto [a, b, c]=*it;
        cout << "(" << a << ", " << b << ", " << c << ")\n";
    }

    return 0;
}