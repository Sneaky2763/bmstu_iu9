#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int INF=1e9;

struct edge{
    int v, len;
};

struct lens{
    int len;
    bool changeable; 
};

void MST_prim(vector<vector<edge>> graph){
    int ans=0;

    vector<lens> len_edge(graph.size());
    for(int i=0; i<graph.size(); ++i){
        len_edge[i].len=INF;
        len_edge[i].changeable=true;
    }
    len_edge[0].len=0;
    set<pair<int,int>> q;
    q.insert({0, 0});
    
    while(q.size()) {
        int v=q.begin()->second;
        len_edge[v].changeable=false;
        q.erase(q.begin());

        for (auto e: graph[v]) {
            int to=e.v;
            int len=e.len;

            if (len<len_edge[to].len && len_edge[to].changeable) {
                q.erase({len_edge[to].len, to});
                len_edge[to].len=len;
                q.insert({len_edge[to].len, to});
            }
        }
    }
    for(auto g: len_edge){
        ans+=g.len;
    }
    cout << ans << endl;
}

int main(){
    int n, m;
    cin >> n;
    cin >> m;

    vector<vector<edge>> graph(n);
    for (int i=0; i<m; ++i){
        int u, v, len;
        cin >> u >> v >> len;
        graph[u].push_back({v, len});
        graph[v].push_back({u, len});
    }

    MST_prim(graph);

    return 0;
}