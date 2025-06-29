#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<char>> all;

char invert(int c) {
    if(c==1){
        return 2;
    }
    return 1;
}

vector<char> inverse(vector<char> color){
    for(int i=0; i<color.size(); ++i){
        color[i]=invert(int(color[i]));
    }
    return color;
}

bool is_valid(int v, char c, const vector<vector<int>> &graph, vector<char> &color) {
    color[v]=c;

    for (int u: graph[v]) {
        if (color[u]==0) {
            if (!is_valid(u, invert(c), graph, color)) {
                return false;
            }
        } else if (color[u]==c) {
            return false;
        }
    }
    return true;
}

void find_all(int v, vector<vector<int>> &graph, vector<char> &color) {
    if (v==graph.size()) {
        all.emplace_back(color);
        all.emplace_back(inverse(color));
        return;
    }

    color[v] = 1;
    if (is_valid(v, 1, graph, color)) {
        find_all(v+1, graph, color);
    }
    color[v] = 0;

    color[v] = 2;
    if (is_valid(v, 2, graph, color)) {
        find_all(v+1, graph, color);
    }
    color[v] = 0;
}

int count_ones(vector<char> a){
    int cnt=0;
    for(int i=0; i<a.size(); ++i){
        if (a[i]==1){
            cnt++;
        }
    }
    return cnt;
}

int absolute(int a){
    if (a<0){
        return -a;
    }
    return a;
}

void print_ans(vector<vector<char>> all, int n){
    vector<char> ans=all[0];
    int mid_deviation = absolute(n/2-count_ones(ans));

    for(int i=0; i<all.size(); ++i){
        if(absolute(n/2-count_ones(all[i]))<mid_deviation){
            ans=all[i];
            mid_deviation = absolute(n/2-count_ones(ans));
        } else if(absolute(n/2-count_ones(all[i]))==mid_deviation && count_ones(all[i])<count_ones(ans)){
            ans=all[i];
            mid_deviation = absolute(n/2-count_ones(ans));
        }else if(absolute(n/2-count_ones(all[i]))==mid_deviation && count_ones(all[i])==count_ones(ans)){
            for(int j=0; j<n; ++j){
                if(all[i][j]-ans[j]<0){
                    ans=all[i];
                    mid_deviation = absolute(n/2-count_ones(ans));
                    break;
                }
                if(all[i][j]-ans[j]>0){
                    break;
                }
            }
        }
    }

    for(int i=0; i<n; ++i){
        if(ans[i]==1){
            cout << i+1 << " ";
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<char> color(n, 0);
    vector<vector<int>> graph(n);

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            char val;
            cin >> val;
            if(val=='+' && i!=j){
                graph[i].push_back(j);
            }
        }
    }

    find_all(0, graph, color);

    if (all.size()==0){
        cout << "No solution" << endl;
        return 0; 
    }
    print_ans(all, n);

    return 0;
}