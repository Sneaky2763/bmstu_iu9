


#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int t=1, cnt=1;

struct vert{
    int index;
    int T1;
    int comp;
    int low;
};

vector<vert> v;

void VisitVertex_Tarjan(vector<vector<int>> &graph, vector<vert> &v, int i, stack<vert> &s);

void Tarjan(vector<vector<int>> graph, int n){
    for(int i=0; i<n; ++i){
        vert new_vert;
        new_vert.index=i;
        new_vert.T1=0;
        new_vert.low=0;
        new_vert.comp=0;
        v.push_back(new_vert);
    }
    
    stack<vert> s;
    for(int i=0; i<n; ++i){
        if(v[i].T1==0){
            VisitVertex_Tarjan(graph, v, i, s);
        }
    }
}

void VisitVertex_Tarjan(vector<vector<int>> &graph, vector<vert> &v, int i, stack<vert> &s){
    v[i].T1=t;
    v[i].low=t;
    t++;
    s.push(v[i]);

    for(int u: graph[i]){
        if(v[u].T1==0){
            VisitVertex_Tarjan(graph, v, u, s);
        }
        if(v[u].comp==0 && v[i].low>v[u].low){
            v[i].low=v[u].low;
        }
    }
    
    if(v[i].T1==v[i].low){
        int curr_index=-1;
        do{
            vert u=s.top();
            s.pop();
            v[u.index].comp = cnt;
            curr_index=u.index;
        }
        while (curr_index!=i);
        cnt++;
    }
}

void BaseSearch(vector<vector<int>> &cond, vector<vert> &v);

void Condensation(vector<vector<int>> graph, vector<vert> &v, int n){
    vector<vector<int>> cond(cnt-1);
    for(int i=0; i<n; ++i){
        for(int u: graph[i]){
            if(v[u].comp!=v[i].comp){
                cond[v[i].comp-1].push_back(v[u].comp);
            }
        }
    }
    
    BaseSearch(cond, v);
}

void BaseSearch(vector<vector<int>> &cond, vector<vert> &v){
    vector<bool> seen(cnt-1);
    for(int i=0; i<cnt-1; ++i){
        seen[i]=false;
    }
    for(int i=0; i<cond.size(); ++i){
        for(int u: cond[i]){
            seen[u-1]=true;
        }
    }
    for(int i=0; i<v.size(); ++i){
        if(!seen[v[i].comp-1]){
            cout << i << " ";
            seen[v[i].comp-1]=true;
        }
    }
    cout << endl;
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);

    for(int i=0; i<m; ++i){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    Tarjan(graph, n);
    Condensation(graph, v, n);

    return 0;
}