#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define int unsigned int 

signed main(){
    int n;
    cin >> n;
    vector<int> dels;
    for (int d=1; d*d<=n; d++){
        if (n%d==0){
            dels.push_back(d);
            if (d!=n/d){
                dels.push_back(n/d);
            }
        }
    }
    cout << "graph {" << endl;
    sort(begin(dels), end(dels), greater<int>());
    for(auto g:dels){
        cout << "   " << g << "\n";
    }
    vector<int> used;
    for(int i=0; i<dels.size(); i++){
        for (int j=i+1; j<dels.size(); j++){
            if (dels[i]%dels[j]==0){
                bool need_out=1;
                for (int k=i+1; k<dels.size(); k++){
                    if (dels[i]%dels[k]==0 && dels[k]%dels[j]==0 && k!=j){
                        need_out=0;
                        break;
                    }
                }
                if (need_out){
                    cout << "   " << dels[i] << "--" << dels[j] << endl;
                }
            }
        }
    }
    cout << "}" << endl;
    return 0;
}
