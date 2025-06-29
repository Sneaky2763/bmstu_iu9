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
int curr_state1, curr_state2;
int minimized_curr_state1, minimized_curr_state2;

void dfs(const vector<vector<int>> &tr, int state, vector<int> &visited, 
    vector<vector<int>> &order){

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
    vector<vector<string>> &ex, int n, int m, int num){
    
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
    if(num==1){
        minimized_curr_state1=state_map[prev_split[curr_state1]];
    } else {
        minimized_curr_state2=state_map[prev_split[curr_state2]];
    }
    
    
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

string canon(Mealy aut, int num){
    vector<int> visited(aut.n, -1);
    vector<vector<int>> order(aut.n);
    for (int i=0; i<aut.n; ++i){
        order[i].resize(aut.m);
        for(int j=0; j<aut.m; ++j) {
            order[i][j]=j;
        }
        sort(order[i].begin(), order[i].end());
    }
    if(num==1){
        dfs(aut.tr, minimized_curr_state1, visited, order);
    } else {
        dfs(aut.tr, minimized_curr_state2, visited, order);
    }
    vector<int> new_to_old(aut.n);
    for (int i=0; i<aut.n; ++i) {
        new_to_old[visited[i]]=i;
    }

    string res="";
    for(int i=0; i<aut.n; ++i){
        int old_state=new_to_old[i];
        for(int j=0; j<aut.m; ++j){
            char input='a'+j;
            res+="    " + to_string(i) + " -> " + to_string(visited[aut.tr[old_state][j]]);
            res+=" [label = \"" + to_string(input) + "(";
            res+=aut.ex[old_state][j] + ")\"]";
        }
    }
    state_order=0;
    return res;
}

int main(){
    int n1, m1;
    cin >> n1 >> m1 >> curr_state1;
    vector<vector<int>> tr1(n1);
    vector<vector<string>> ex1(n1);
    for(int i=0; i<n1; ++i){
        tr1[i].resize(m1);
        for(int j=0; j<m1; ++j){
            cin >> tr1[i][j];
        }
    }
    for(int i=0; i<n1; ++i){
        ex1[i].resize(m1);
        for(int j=0; j<m1; ++j){
            cin >> ex1[i][j];
        }
    }

    int n2, m2;
    cin >> n2 >> m2 >> curr_state2;
    vector<vector<int>> tr2(n2);
    vector<vector<string>> ex2(n2);
    for(int i=0; i<n2; ++i){
        tr2[i].resize(m2);
        for(int j=0; j<m2; ++j){
            cin >> tr2[i][j];
        }
    }
    for(int i=0; i<n2; ++i){
        ex2[i].resize(m2);
        for(int j=0; j<m2; ++j){
            cin >> ex2[i][j];
        }
    }

    Mealy minimized1=AufenkampHohn(tr1, ex1, n1, m1, 1);
    Mealy minimized2=AufenkampHohn(tr2, ex2, n2, m2, 2);
    string res1=canon(minimized1, 1);
    string res2=canon(minimized2, 2);
    if(res1==res2){
        cout << "EQUAL" << endl;
        return 0;
    }
    cout << "NOT EQUAL" << endl;
    return 0;
}