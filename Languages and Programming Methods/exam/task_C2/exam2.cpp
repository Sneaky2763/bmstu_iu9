#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class SubNums {
private:
    vector<int> numbers;
    vector<vector<int>> good;
    
    void initialize(vector<int> nums){
        for(int i=0; i<nums.size(); ++i){
            numbers.push_back(nums[i]);
        }
        
        for(int i=0; i<numbers.size(); ++i){
            vector<int> curr_sub={};
            int curr_sum=0;

            for(int j=i; j<numbers.size(); ++j){
                if(curr_sum+nums[j]>21){
                    break;
                } else {
                    curr_sum+=numbers[j];
                    curr_sub.push_back(numbers[j]);
                }
            }
            if(curr_sub.size()!=0){
                good.emplace_back(curr_sub);
            }
        }
    }

public:
    SubNums(vector<int> nums){
        initialize(nums);
    }

    class const_iterator{
    private:
        const vector<vector<int>> *good;
        size_t index;
        
    public:
        const_iterator(const vector<vector<int>> *t, size_t i): good(t), index(i) {}
            
        const vector<int>& operator*() const{
            return (*good)[index];
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
        return const_iterator(&good, 0);
    }
    
    const_iterator end() const{
        return const_iterator(&good, good.size());
    }
};

int main(){
    vector<int> nums={2, 3, 4, 5, 10, 15, 100, 6, 8};
    SubNums good(nums);
    
    cout << "Подпоследовательности, сумма элементов которых не превышает 21: " << endl;
    for (auto it=good.begin(); it!=good.end(); ++it){
        for(auto g: *it){
            cout << g << " ";
        }
        cout << endl;
    }

    return 0;
}