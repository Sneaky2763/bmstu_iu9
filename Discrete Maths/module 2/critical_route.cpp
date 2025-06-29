#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

struct Node{
    int time0;
    int time1;
    int color;
    int mark;
    vector<Node*> parents;
    string name;
};

class Graph{
private:
    vector<Node*> vertices;
    vector<Node*> main_vertices;
    map<string, Node*> vertex_by_name;
    map<Node*, vector<Node*>> adjacency;

public:
    vector<Node*> dfs(Node* node){
        node->mark=1;
        vector<Node*> result;

        for (Node* neighbor: adjacency[node]) {
            if (neighbor->mark==0) {
                auto sub_result=dfs(neighbor);
                result.insert(result.end(), sub_result.begin(), sub_result.end());
            }
            if (neighbor->mark==1) {
                result.push_back(neighbor);
            }
        }

        node->mark=2;
        return result;
    }

    void bfs(int n){
        queue<Node*> q;

        for(Node* vertex : main_vertices){
            if (vertex->time1==-1 && vertex->color!=2){
                vertex->time1=vertex->time0;
                q.push(vertex);
            }

            while(!q.empty()){
                Node* current=q.front();
                q.pop();

                for(Node* neighbor: adjacency[current]){
                    if (neighbor->color==2){
                        continue;
                    }

                    int new_time=current->time1+neighbor->time0;

                    if(neighbor->time1==-1 || neighbor->time1<new_time){
                        neighbor->time1=new_time;
                        neighbor->parents={current};
                    } else if (neighbor->time1==new_time){
                        neighbor->parents.push_back(current);
                    }

                    q.push(neighbor);
                }
            }
        }
    }

    void color_graph(Node* node, int color){
        node->color=color;
        vector<Node*> nodes;
        if(color==1){
            nodes=node->parents;
        } else {
            nodes=adjacency[node];
        }

        for(Node* neighbor: nodes){
            if(neighbor->color != color){
                color_graph(neighbor, color);
            }
        }
    }

    Node* add_node(Node* node, Node* root) {
        if(vertex_by_name.find(node->name)==vertex_by_name.end()){
            vertices.push_back(node);
            vertex_by_name[node->name]=node;
        } 
        else {
            node=vertex_by_name[node->name];
        }

        if (root!=nullptr) {
            adjacency[root].push_back(node);
        }

        return node;
    }

    vector<Node*>& get_vertices(){
        return vertices;
    }
    vector<Node*>& get_main_vertices(){
        return main_vertices;
    }
    map<Node*, vector<Node*>>& get_adjacency(){
        return adjacency;
    }
};

pair<vector<vector<int>>, vector<vector<string>>> parse_input(const string& input){
    vector<vector<string>> names(1);
    vector<vector<int>> times(1);
    string current_name;
    int current_time=0;
    bool reading_time=false;
    int group=0;

    for (char c: input) {
        if (c=='(' || c==')') {
            reading_time = true;
            continue;
        } else if (c=='<' || c==';') {
            names[group].push_back(current_name);
            times[group].push_back(current_time/10);
            current_name.clear();
            current_time=0;
            reading_time=false;

            if (c==';') {
                names.emplace_back();
                times.emplace_back();
                group++;
            }
            continue;
        }

        if (reading_time){
            current_time=(current_time+(c-'0'))*10;
        } else {
            current_name+=c;
        }
    }

    if(!current_name.empty()){
        names[group].push_back(current_name);
        times[group].push_back(current_time/10);
    }

    return {times, names};
}

int main() {
    Graph graph;
    string input_line;
    string full_input;

    while(getline(cin, input_line)){
        if(input_line.empty()){
            break;
        }
        full_input+=input_line;
    }

    full_input.erase(remove_if(full_input.begin(), full_input.end(), ::isspace), full_input.end());

    auto[times, names]=parse_input(full_input);

    for (int i=0; i<times.size(); i++) {
        Node* root=nullptr;
        for (int j=0; j<times[i].size(); j++) {
            Node* node=new Node{times[i][j], -1, 0, 0, {}, names[i][j]};
            root=graph.add_node(node, root);
            if (j==0){
                graph.get_main_vertices().push_back(root);
            }
        }
    }

    for (Node* vertex: graph.get_main_vertices()){
        if(vertex->mark!=2){
            auto cycle_nodes=graph.dfs(vertex);
            for (Node* node: cycle_nodes){
                graph.color_graph(node, 2);
            }
        }
    }

    graph.bfs(graph.get_vertices().size());

    vector<Node*> max_nodes;
    for (Node* vertex: graph.get_vertices()){
        if (vertex->color!=2){
            if (max_nodes.empty() || max_nodes[0]->time1<vertex->time1){
                max_nodes = {vertex};
            } else if (max_nodes[0]->time1 == vertex->time1) {
                max_nodes.push_back(vertex);
            }
        }
    }

    for (Node* vertex: max_nodes){
        graph.color_graph(vertex, 1);
    }

    cout << "digraph {\n";
    for (Node* vertex: graph.get_vertices()){
        cout << "    " << vertex->name << " [label = \"" << vertex->name; 
        cout << "(" << vertex->time0 << ")\"";
        
        if (vertex->color == 1) {
            cout << ", color = \"red\"";
        }
        else if (vertex->color == 2) {
            cout << ", color = \"blue\"";
        }
        
        cout << "]\n";
    }

    for (auto& [from, neighbors]: graph.get_adjacency()){
        for (Node* to: neighbors) {
            cout << "    " << from->name << " -> " << to->name;
            
            if (from->color == 1 && to->color == 1 && 
                from->time1 + to->time0 == to->time1) {
                cout << " [color = \"red\"]";
            }
            else if (from->color == 2 && to->color == 2) {
                cout << " [color = \"blue\"]";
            }
            
            cout << "\n";
        }
    }

    cout << "}\n";

    for (Node* node: graph.get_vertices()){
        delete node;
    }

    return 0;
}