#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge{
    int to;
    int color;
};

struct Node{
    int ind;
    vector<int> colors;
};

void bfs(vector<vector<Edge>> &graph, int start, int n) {
    vector<int> dist(n, -1);
    vector<vector<int>> paths(n);
    queue<Node> q;
    
    dist[start]=0;
    q.push({start, {}});
    
    while (!q.empty()) {
        Node curr=q.front();
        q.pop();

        sort(graph[curr.ind].begin(), graph[curr.ind].end(), 
            [](const Edge& a, const Edge& b) { return a.color < b.color; });
        
        for(Edge& e: graph[curr.ind]) {
            vector<int> new_colors=curr.colors;
            new_colors.push_back(e.color);
            
            if(dist[e.to]==-1){
                dist[e.to]=dist[curr.ind]+1;
                paths[e.to]=new_colors;
                q.push({e.to, new_colors});
            } else if (dist[e.to]==dist[curr.ind]+1){
                if(lexicographical_compare(new_colors.begin(), new_colors.end(),
                paths[e.to].begin(), paths[e.to].end())){
                    
                    paths[e.to]=new_colors;
                    q.push({e.to, new_colors});
                }
            }
        }
    }

    cout << dist[n-1] << endl;
    for(int color: paths[n-1]){
        cout << color << " ";
    }
    cout << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> graph(n);
    
    for(int i=0; i<m; ++i){
        int a, b, c;
        cin >> a >> b >> c;
        graph[a-1].push_back({b-1, c});
        graph[b-1].push_back({a-1, c});
    }
    
    bfs(graph, 0, n);
    
    return 0;
}