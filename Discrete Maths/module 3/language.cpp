

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct hash_func{
    size_t operator()(const pair<int, string>& p) const{
        size_t h1=hash<int>{}(p.first);
        size_t h2=hash<string>{}(p.second);
        return h1^h2;
    }
};

set<string> all;
unordered_map<pair<int, string>, bool, hash_func> visited;

void find_all(vector<vector<int>> &tr, vector<vector<string>> &ex,
    int state, string curr, int M){
    if(visited[{state, curr}]){
        return;
    }
    visited[{state, curr}]=true;
    if(curr.length()<=M && curr.length()!=0){
        all.insert(curr);
    }
    if(curr.length()==M){
        return;
    }
    for(int i=0; i<2; ++i){
        string next=curr;
        if(ex[state][i]!="-"){
            find_all(tr, ex, tr[state][i], next+ex[state][i], M);
        } else {
            find_all(tr, ex, tr[state][i], next, M);
        }
    }
}

int main(){
    int n;
    cin >> n;
    int m=2;

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

    int state, M;
    cin >> state >> M;
    find_all(tr, ex, state, "", M);
    for(auto word: all){
        cout << word << " ";
    }
    cout << endl;
    return 0;
}

