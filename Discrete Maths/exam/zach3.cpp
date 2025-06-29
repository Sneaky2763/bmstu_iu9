#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>

using namespace std;

struct aut {
    int n;
    int curr;
    vector<int> final;
    vector<vector<int>> tr;
};

int find_difference(aut &aut1, aut &aut2, int m) {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    queue<pair<pair<int, int>, string>> q;
    map<pair<int, int>, bool> visited;
    q.push({{aut1.curr, aut2.curr}, ""});
    
    while(!q.empty()){
        pair<pair<int, int>, string> current=q.front();
        q.pop();
        
        int state1=current.first.first;
        int state2=current.first.second;
        if(visited[{state1, state2}]){
            continue;
        }
        visited[{state1, state2}]=true;
        string curr_str=current.second;
        
        if (aut1.final[state1] != aut2.final[state2]) {
            return curr_str.length();
        }
        
        for (int i=0; i<m; ++i) {
            int next1=aut1.tr[state1][i];
            int next2=aut2.tr[state2][i];
            q.push({{next1, next2}, curr_str + alphabet[i]});
        }
    }
    
    return -1;
}

int main() {
    int m;
    cin >> m;

    int n1, curr1;
    cin >> n1 >> curr1;
    vector<vector<int>> tr1(n1);
    vector<int> final1(n1, 0);
    for (int i=0; i<n1; ++i) {
        char fin;
        cin >> fin;
        if(fin=='+'){
            final1[i]=1;
        }

        tr1[i].resize(m);
        for (int j=0; j<m; ++j) {
            cin >> tr1[i][j];
        }
    }
    aut aut1={n1, curr1, final1, tr1};

    int n2, curr2;
    cin >> n2 >> curr2;
    vector<vector<int>> tr2(n2);
    vector<int> final2(n2, 0);
    for (int i=0; i<n2; ++i) {
        char fin;
        cin >> fin;
        if(fin=='+'){
            final2[i]=1;
        }
        tr2[i].resize(m);
        for (int j=0; j<m; ++j) {
            cin >> tr2[i][j];
        }
    }
    aut aut2={n2, curr2, final2, tr2};

    int result=find_difference(aut1, aut2, m);

    if(result==-1){
        cout << "=" << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}