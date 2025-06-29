#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

struct state{
    int num;
    state *parent;
    int depth;
};

struct Mealy{
    int n;
    int m;
    vector<vector<int>> tr;
    vector<vector<string>> ex;
};

int state_order=0;
int curr_state;
int minimized_curr_state;

void dfs(const vector<vector<int>>& tr, int state, vector<int>& visited, 
    vector<vector<int>>& order){

    visited[state]=state_order++;
    for(int x: order[state]){
        int to=tr[state][x];
        if (visited[to]==-1) {
            dfs(tr, to, visited, order);
        }
    }
}

state *find(state *curr){
    if(curr->parent!=curr){
        curr->parent=find(curr->parent);
    }
    return curr->parent;
}

void unite(state *q1, state *q2){
    state *p1=find(q1);
    state *p2=find(q2);
    
    if(p1==p2){
        return;
    }

    if(p1->depth < p2->depth){
        p1->parent=p2;
    } else {
        p2->parent=p1;
        if(p1->depth==p2->depth){
            p1->depth++;
        }
    }
}


vector<int> split1(vector<vector<int>> &tr,
    vector<vector<string>> &ex, int n, int m){
    
    int state_count=n;
    vector<state> states(n);
    for(int i=0; i<n; ++i){
        states[i].num=i;
        states[i].parent=&states[i];
        states[i].depth=0;
    }

    for(int i=0; i<n; ++i){
        for(int j=i+1; j<n; ++j){
            state *q1=&states[i];
            state *q2=&states[j];
            if(find(q1)!=find(q2)){
                bool eq=true;
                for(int x=0; x<m; ++x){
                    if(ex[i][x]!=ex[j][x]){
                        eq=false;
                        break;
                    }
                }
                if(eq){
                    unite(q1, q2);
                    --state_count;
                }
            }
        }
    }
    vector<int> res(n);
    for(int i=0; i<n; ++i){
        res[i]=find(&states[i])->num;
    }
    return res;
}

vector<int> split(vector<vector<int>> &tr,
    vector<vector<string>> &ex, int n, int m,
    vector<int> &after_split){

    int state_count=n;
    vector<state> states(n);

    for(int i=0; i<n; ++i){
        states[i].num=i;
        states[i].parent=&states[i];
        states[i].depth=0;
    }

    for(int i=0; i<n; ++i){
        for(int j=i+1; j<n; ++j){
            state *q1=&states[i];
            state *q2=&states[j];

            if(after_split[q1->num]==after_split[q2->num] && find(q1)!=find(q2)){
                bool eq=true;

                for(int x=0; x<m; ++x){
                    int w1=tr[q1->num][x];
                    int w2=tr[q2->num][x];
                    if(after_split[w1]!=after_split[w2]) {
                        eq=false;
                        break;
                    }
                }
                if(eq){
                    unite(q1, q2);
                    state_count--;
                }
            }
        }
    }

    vector<int> res(n);
    for(int i=0; i<n; ++i){
        res[i]=find(&states[i])->num;
    }
    
    return res;
}

Mealy AufenkampHohn(vector<vector<int>> &tr,
    vector<vector<string>> &ex, int n, int m){
    
    vector<int> prev_split=split1(tr, ex, n, m);

    while(true){
        vector<int> new_split=split(tr, ex, n, m, prev_split);

        bool eq=true;
        for(int i=0; i<n; ++i){
            if(prev_split[i]!=new_split[i]){
                eq=false;
                break;
            }
        }
        if(eq){
            break;
        }
        prev_split=new_split;
    }

    map<int, int> state_map;
    int state_count=0;
    for(int i=0; i<n; ++i){
        if(state_map.find(prev_split[i])==state_map.end()){
            state_map[prev_split[i]]=state_count++;
        }
    }
    minimized_curr_state=state_map[prev_split[curr_state]];
    
    vector<vector<int>> new_tr(state_count);
    vector<vector<string>> new_ex(state_count);
    for(int i=0; i<n; ++i){
        if(i<state_count){
            new_tr[i].resize(m);
            new_ex[i].resize(m);
        }

        int new_state=state_map[prev_split[i]];
        for(int x=0; x<m; ++x){
            int old_to=tr[i][x];
            int new_to=state_map[prev_split[old_to]];
            new_tr[new_state][x]=new_to;
            new_ex[new_state][x]=ex[i][x];
        }
    }
    
    Mealy res={state_count, m, new_tr, new_ex};
    return res;
}

void visualize_canon(Mealy aut){
    vector<int> visited(aut.n, -1);
    vector<vector<int>> order(aut.n);
    for (int i=0; i<aut.n; ++i){
        order[i].resize(aut.m);
        for(int j=0; j<aut.m; ++j) {
            order[i][j]=j;
        }
        sort(order[i].begin(), order[i].end());
    }
    dfs(aut.tr, minimized_curr_state, visited, order);

    vector<int> new_to_old(aut.n);
    for (int i=0; i<aut.n; ++i) {
        new_to_old[visited[i]]=i;
    }

    cout << "digraph {" << endl;
    cout << "    rankdir = LR" << endl;
    for(int i=0; i<aut.n; ++i){
        int old_state=new_to_old[i];
        for(int j=0; j<aut.m; ++j){
            char input='a'+j;
            cout << "    " << i << " -> " << visited[aut.tr[old_state][j]];
            cout << " [label = \"" << input << "(";
            cout << aut.ex[old_state][j] << ")\"]" << endl;
        }
    }
    cout << "}" << endl;
}

int main(){
    int n, m;
    cin >> n >> m >> curr_state;
    vector<vector<int>> tr(n);
    vector<vector<string>> ex(n);
    for(int i=0; i<n; ++i){
        tr[i].resize(m);
        for(int j=0; j<m; ++j){
            cin >> tr[i][j];
        }
    }
    for(int i=0; i<n; ++i){
        ex[i].resize(m);
        for(int j=0; j<m; ++j){
            cin >> ex[i][j];
        }
    }

    Mealy minimized=AufenkampHohn(tr, ex, n, m);
    visualize_canon(minimized);

    return 0;
}