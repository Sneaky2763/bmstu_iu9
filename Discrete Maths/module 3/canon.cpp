#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int state_order=0;

void dfs(vector<vector<int>> &tr, int state, vector<int> &visited){
    visited[state]=state_order;
    state_order++;
    
    for(int to: tr[state]){
        if(visited[to]==-1){
            dfs(tr, to, visited);
        }
    }
}

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

    vector<int> visited(n, -1);
    dfs(tr, curr, visited);
    cout << n << "\n" << m << "\n" << 0 << "\n";

    vector<int> new_to_old(n);
    for (int i=0; i<n; ++i) {
        new_to_old[visited[i]]=i;
    }
    for (int i=0; i<n; ++i) {
        int old_state=new_to_old[i];
        for (int j=0; j<m; ++j) {
            cout << visited[tr[old_state][j]] << " ";
        }
        cout << endl;
    }
    
    for (int i=0; i<n; ++i) {
        int old_state=new_to_old[i];
        for (int j=0; j<m; ++j) {
            cout << ex[old_state][j] << " ";
        }
        cout << endl;
    }

    return 0;
}