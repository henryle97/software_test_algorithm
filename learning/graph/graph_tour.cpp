#include <bits/stdc++.h>

using namespace std;

vector<int> dfs(vector<vector<int>> graph, int V, int S) {
    vector<int> asc_path;
    vector<int> visited(V+1, false);
    stack<int> st;
    st.push(S);

    while(!st.empty()) {
        int cur_node = st.top();
        st.pop();

        // stack may contain same vertex twice 
        if (visited[cur_node]) {
            continue;
        }
        visited[cur_node] = true;
        asc_path.push_back(cur_node);
        
        vector<int> adj_nodes = graph[cur_node];
        sort(adj_nodes.begin(), adj_nodes.end(), greater<int>());   // sort desc 
        for (auto adj_node: adj_nodes) {
            if (!visited[adj_node]){
                st.push(adj_node);
            }
        }
        
    }

    return asc_path;
}

vector<int> bfs(vector<vector<int>> graph, int V, int S) {
    vector<int> asc_path;
    queue<int> q;
    q.push(S);
    vector<int> visited(V+1, false);


    while(!q.empty()) {
        int cur_node = q.front();
        q.pop();

        if (visited[cur_node]) {
            continue;
        }

        visited[cur_node] = true;
        asc_path.push_back(cur_node);
        vector<int> adj_nodes = graph[cur_node];
        sort(adj_nodes.begin(), adj_nodes.end());

        for (auto adj_node: adj_nodes)
        {
            if (!visited[adj_node])
            {
                q.push(adj_node);
            }
        }
        
    }

    return asc_path;
}





vector<vector<int>> solve(vector<vector<int>> graph, int V, int S) {
    vector<vector<int>> result;
    vector<int> asc_path_dfs = dfs(graph, V, S);
    vector<int> asc_path_bfs = bfs(graph, V, S);
    result.push_back(asc_path_dfs);
    result.push_back(asc_path_bfs);
    return result;
}




int main() {
    int T;
    int V, E, S;
    int x, y;
    

    cin >> T;
    for (int test_idx=1; test_idx <= T; test_idx++){
        cin >> V >> E >> S;
        vector<vector<int>> graph(V+1);
        for (int edge=0; edge < E; edge++) {
            cin >> x >> y;
            graph[x].push_back(y);
            graph[y].push_back(x);
        }
        vector<vector<int>> result = solve(graph, V, S);
        
        for (int idx=0; idx < result.size(); idx++) {
            if (idx == 0) {
                cout << "#" << test_idx << " ";
            }
            for (auto x : result[idx]) {
                cout << x << " ";
            }
            cout << endl;
        }


    }

}