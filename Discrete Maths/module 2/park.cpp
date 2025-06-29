
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <math.h>
#include <iomanip>

using namespace std;

struct edge{
    double dist;
    int from;
    int to;
};

double find_dist(pair<int, int> a, pair<int, int> b){
    return pow(pow(a.first-b.first, 2)+pow(a.second-b.second, 2), 0.5);
}

bool sortfunc(const edge l, const edge r){
    return l.dist<r.dist;
}

int leader(vector<int> &p, int v){
    if(p[v]==v){
        return v;
    }
    return leader(p, p[v]);
}

void unite(vector<int> &p, vector<int> &s, int a, int b) {
    a = leader(p, a), b = leader(p, b);
    if (s[a] > s[b]){
        swap(a, b);
    }
    s[b] += s[a];
    p[a] = b;
}

void init(vector<int> &p, vector<int> &s, int n) {
    for (int i = 0; i < n; i++){
        p[i] = i;
        s[i] = 1;
    }
}


int main(){
    int n;
    cin >> n;
    vector<pair<int, int>> coords(n);
    for(int i=0; i<n; ++i){
        int x, y;
        cin >> x >> y;
        coords[i].first=x;
        coords[i].second=y;
    }

    vector<edge> graph;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(i!=j){
                graph.push_back({find_dist(coords[i], coords[j]), i, j});
            }
        }
    }

    sort(graph.begin(), graph.end(), &sortfunc);

    double ans=0;
    vector<int> p(n), s(n);
    init(p, s, n);
    for (auto [l, a, b]: graph) {
        if (leader(p, a)!=leader(p, b)) {
            ans+=l;
            unite(p, s, a, b);
        }
    }
    cout << fixed << setprecision(2) << ans; 
    return 0;
}