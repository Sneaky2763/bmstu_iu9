#ifndef RANGESET_H
#define RANGESET_H

#include <iostream>
#include <vector>

using namespace std;

template<int L, int H>
class RangeSet {
private:
    using use_type = typename conditional<
        (H-L+1) <= 256,
        unsigned char,
        typename conditional<
            (H-L+1) <= 65536,
            unsigned short,
            unsigned int
        >::type
    >::type;
    
    vector<pair<int, use_type>> intervals;

public:
    bool checkval(int val){
        if (val<L || val>H){
            return false;
        }
        for (auto& interval: intervals) {
            if (val>=interval.first && val<=interval.first+interval.second){
                return true;
            }
        }
        return false;
    }


    void add(int l, int len) {
        if (l>=L && l+len<=H){
            use_type type_len=static_cast<use_type>(len);
            intervals.emplace_back(l, type_len);
        }
    }
};

#endif