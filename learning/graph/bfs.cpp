#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Graph
{
    int V; // num of vertices 
    vector<vector<int>> adj;  // list of list adjacency vertices 

    public:
        Graph(int V);  // constructor 
        void addEdge(int u, int v);
        void BDF(int s); // bdf from s vertice 
        void DFS(int s);
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
}

// Time complexity: O(V+E), V is #nodes, E is #edges
// Space: O(V)
void Graph::BDF(int s) {
    queue<int> q;
    vector<bool> visited;
    visited.resize(V, false);
    int curr_node;

    q.push(s);
    cout << "Start node: " << s << endl;
    visited[s] = true;

    while(!q.empty()) {
        curr_node = q.front();
        cout  << curr_node << " ";
        q.pop();
        visited[curr_node] = true;
        for (auto adj_node : adj[curr_node]) {
            if (!visited[adj_node]) {
                visited[adj_node] = true;
                q.push(adj_node);
            }
        }

    }
}

void Graph::DFS(int s) {
    stack<int> st;
    int curr_node;
    vector<bool> visited;
    visited.resize(V, false);

    st.push(s);
    visited[s] = true;

    while(!st.empty()) {
        curr_node = st.top();
        st.pop();
        cout << curr_node << " ";
        visited[curr_node] = true;

        for (auto adj_node : adj[curr_node]) {
            if (!visited[adj_node]) {
                
                visited[adj_node] = true;
                st.push(adj_node);
            }
        }
    }

}


int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    cout << "BFS: " << endl;
    g.BDF(2);
    cout << "DFS:  " << endl;
    g.DFS(2);
}
