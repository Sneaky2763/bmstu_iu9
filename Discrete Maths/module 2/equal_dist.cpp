#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> bfs(vector<vector<int>> &graph, int v, int n){
    queue<int> q;
    vector<bool> visited(n, false);
    vector<int> dist(n, 1e9);

    visited[v]=true;
    dist[v]=1;
    q.push(v);
    while(!q.empty()){
        int v=q.front();
        q.pop();

        for(int to: graph[v]){
            if(!visited[to]){
                visited[to]=true;
                dist[to]=dist[v]+1;
                q.push(to);
            }
        }
    }

    return dist;
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for(int i=0; i<m; ++i){
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }
    
    int k;
    cin >> k;
    int ref_vert[k];
    for(int i=0; i<k; ++i){
        int v;
        cin >> v;
        ref_vert[i]=v;
    }

    vector<vector<int>> ref_dist;
    for(int i=0; i<k; ++i){
        ref_dist.emplace_back(bfs(graph, ref_vert[i], n));
    }

    vector<int> ans;
    for(int i=0; i<n; ++i){
        bool equal_dist=true;
        for(int j=1; j<k; ++j){
            if(ref_dist[j-1][i]!=ref_dist[j][i] || ref_dist[j-1][i]==1e9){
                equal_dist=false;
            }
        }
        if(equal_dist){
            ans.push_back(i);
        }
    }

    if(ans.size()==0){
        cout << "-";
    }
    for(int g: ans){
        cout << g << " ";
    }
    
    return 0;
}