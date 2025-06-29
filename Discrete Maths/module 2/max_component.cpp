#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct component_rank{
    int num, v, e;
};
struct edge_output{
    int from, to;
};

void dfs(vector<vector<int>> &graph, int v, vector<int> &visited, int component){
    visited[v]=component;

    for(int to: graph[v]){
        if(!visited[to]){
            dfs(graph, to, visited, component);
        }
    }

}
bool sortfunc(component_rank const& l, component_rank const& r) {
    if (l.v!=r.v){
        return l.v<r.v;
    }
    if(l.e!=r.e){
        return l.e<r.e;
    }
    return l.num>r.num;
}

int find_max_comp(vector<int> &visited, vector<int> &edges_count, vector<edge_output> edges, int n, int m){
    vector<component_rank> components(n+1);
    for(int i=1; i<n+1; ++i){
        components[i]={i, 0, 0};
    }
    for(int i=0; i<n; ++i){
        components[visited[i]].v++;
        components[visited[i]].e+=edges_count[i];
    }

    sort(components.begin(), components.end(), &sortfunc);

    cout << "graph {" << endl;

    for(int i=0; i<n; ++i){
        cout << "   " << i;
        if(components[n].num==visited[i]){
            cout << " [color = red]";
        }
        cout << endl;
    }

    for(int i=0; i<m; ++i){
        cout << "   " << edges[i].from << " -- " << edges[i].to;
        if(visited[edges[i].from] == components[n].num){
            cout << " [color = red]";
        }
        cout << endl;
    }
    cout << "}" << endl;
    return 0;
}

int main(){
    int n, m;
    cin >> n;
    cin >> m;
    vector<vector<int>> graph(n);
    vector<int> edges_count(n, 0);
    vector<edge_output> edges(m);

    for(int i=0; i<m; ++i){
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to);
        graph[to].push_back(from);
        edges_count[from]++;
        edges[i]={from, to};
    }
    
    vector<int> visited(n, 0);
    int curr_component=1;
    for(int i=0; i<n; ++i){
        if(visited[i]==0){
            dfs(graph, i, visited, curr_component);
            curr_component++;
        }
    }

    find_max_comp(visited, edges_count, edges, n, m);
}