#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

int INF=1e9;

struct edge{
    int from, to, dist;
};

vector<int> bfs(vector<vector<int>> &graph, int v, int n){
    int iter_count=0;
    queue<int> q;
    vector<bool> visited(n, false);
    vector<int> dist(n, 1e9);

    visited[v]=true;
    dist[v]=1;
    q.push(v);
    while(!q.empty()){
        iter_count++;
        if(iter_count>1000000){
            cout << "cycle" << endl;
            return {};
        }
        int v=q.front();
        q.pop();

        for(int to: graph[v]){
            visited[to]=true;
            dist[to]=dist[v]+1;
            q.push(to);
        }
    }

    return dist;
}
vector<int> BellmanFord(vector<edge> graph, int n, vector<int> no_prep){
    vector<int> min_dist(n, -INF);
    int m=graph.size();
    for(int i=0; i<no_prep.size(); ++i){
        min_dist[no_prep[i]]=1;
    }
    min_dist[0]=1;
	for(int i=0; i<n-1; ++i){
        for (int j=0; j<m; ++j){
            if (min_dist[graph[j].from]>-INF){
                min_dist[graph[j].to]=max(min_dist[graph[j].to],
                    min_dist[graph[j].from] + graph[j].dist);
            }
        }
    }
    return min_dist;
}

int main(){
    int n;
    cin >> n;

    vector<vector<int>> graph_for_bfs(n);
    vector<edge> graph;
    vector<int> no_prep;
    for(int i=0; i<n; ++i){
        int m;
        cin >> m;
        if(m==0){
            no_prep.push_back(i);
        }
        for(int j=0; j<m; ++j){
            int kurs;
            cin >> kurs;
            graph.push_back({kurs-1, i, 1});

            graph_for_bfs[kurs-1].push_back(i);
        }
    }

    for(int i=0; i<n; ++i){
        if(bfs(graph_for_bfs, i, n).size()==0){
            return 0;
        }
    }

    int ans=0;
    for(auto g: BellmanFord(graph, n, no_prep)){
        ans=max(g, ans);
    }
    cout << ans << endl;
    return 0;
}