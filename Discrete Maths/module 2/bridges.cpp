#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int timer=0, ans=0;

void dfs(vector<vector<int>> &graph, int v, int p, vector<int> &visited, vector<int> &tin, vector<int> &tup){
    visited[v]=1;
    tin[v]=timer++;
    tup[v]=tin[v];

    for(int to: graph[v]){
        if(to==p){
            continue;
        }
        if(visited[to]){
            tup[v]=min(tup[v], tin[to]);
        } else {
            dfs(graph, to, v, visited, tin, tup);
            tup[v]=min(tup[v], tup[to]);

            if(tup[to]>tin[v]){
                ans++;
            }
        }
    }
}

int main(){
    int n, m;
    cin >> n;
    cin >> m;
    vector<vector<int>> graph(n);
    for(int i=0; i<m; ++i){
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    vector<int> visited(n, 0);
    vector<int> tin(n), tup(n);
    for(int i=0; i<n; ++i){
        if(!visited[i]){
            dfs(graph, i, -1, visited, tin, tup);
        }
    }

    cout << ans << endl;
    return 0;
}