#include <bits/stdc++.h>

using namespace std;

int totalParties=0;
int largestMem=-1;
vector<bool> visited;

int dfs(vector<vector<int>> graph, int V, int S) {
    vector<int> mems;
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
        mems.push_back(cur_node);
        
        for (auto adj_node: graph[cur_node]) {
            if (!visited[adj_node]){
                st.push(adj_node);
            }
        }
        
    }

    return mems.size();
}

void solve(vector<vector<int>> graph, int N) {
    
    for (int start=1; start <= N; start++) {
        if (!visited[start]){
            int numMems = dfs(graph, N, start);
            if (numMems == 1) {
                continue;
            } else {
                totalParties++;
                if (numMems > largestMem) {
                    largestMem = numMems;
                }
            }

        }
    }
}




int main() {
    int T;
    int N, K;
    int x, y;
    

    cin >> T;
    for (int test_idx=1; test_idx <= T; test_idx++){
        cin >> N >> K;
        vector<vector<int>> graph(N+1);
        visited.resize(N+1);
        visited.assign(N+1, false);


        totalParties=0;
        largestMem=-1;

        for (int edge=0; edge < K; edge++) {
            cin >> x >> y;
            graph[x].push_back(y);
            graph[y].push_back(x);
        }

        solve(graph, N);        
        cout << "#" << test_idx << " " << totalParties << " " << largestMem << endl;
    

    }

}