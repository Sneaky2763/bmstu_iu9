#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct elem{
    int val, pos;
};

vector<int> findNeighbours(int pos, int n){
    vector<int> neighbours;
    if((pos+1)%n!=0){
        neighbours.push_back(pos+1);
    }
    if((pos-1)%n!=n-1){
        neighbours.push_back(pos-1);
    }
    if(pos+n<n*n){
        neighbours.push_back(pos+n);
    }
    if(pos-n>=0){
        neighbours.push_back(pos-n);
    }

    return neighbours;
}

void Dijkstra(vector<elem> &graph, int n){
    vector<int> dist(n*n, 1e9);
    dist[0]=graph[0].val;

    priority_queue<pair<int, int>> q;
    q.push({0, 0});
    while(!q.empty()){
        int curr_pos=q.top().second;
        int curr_dist=-q.top().first;
        q.pop();

        if(curr_dist>dist[curr_pos]){
            continue;
        }
        vector<int> neighbours=findNeighbours(curr_pos, n);
        for(int to: neighbours){
            if(dist[curr_pos]+graph[to].val<dist[to]){
                dist[to]=dist[curr_pos]+graph[to].val;
                q.push({-dist[to], to});
            }
        }
    }
    cout << dist[n*n-1] << endl;
}

int main(){
    int n;
    cin >> n;
    vector<elem> graph(n*n);
    for(int i=0; i<n*n; ++i){
        cin >> graph[i].val;
        graph[i].pos=i;
    }

    Dijkstra(graph, n);
    
    return 0;
}
