#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    int n, m, curr;
    cin >> n >> m >> curr;
    vector<vector<int>> tr(n);
    vector<vector<string>> ex(n);
    for(int i=0; i<n; ++i){
        tr[i].resize(m);
        for(int j=0; j<m; ++j){
            cin >> tr[i][j];
        }
    }
    for(int i=0; i<n; ++i){
        ex[i].resize(m);
        for(int j=0; j<m; ++j){
            cin >> ex[i][j];
        }
    }

    cout << "digraph {" << endl;
    cout << "    rankdir = LR" << endl;
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            char input='a'+j;
            cout << "    " << i << " -> " << tr[i][j];
            cout << " [label = \"" << input << "(";
            cout << ex[i][j] << ")\"]" << endl;
        }
    }
    cout << "}" << endl;

    return 0;
}