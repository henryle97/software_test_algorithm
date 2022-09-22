#include <iostream>
#include <vector>

using namespace std; 

vector<vector<int>> g;

int parent[1000];
int rank_tree[1000];


int N, M;


int Find(int x) {
    if (parent[x] != x) {
        parent[x] = Find(parent[x]);
    }
    return parent[x];
}

int Union(int x, int y){
    int root_x = Find(x);
    int root_y = Find(y);

    if (root_x == root_y){
        return -1;
    } else{
        if (rank_tree[root_x] > rank_tree[root_y]) {
            parent[root_y] = root_x;
        } else if (rank_tree[root_x] < rank_tree[root_y]) {
            parent[root_x] = root_y;
        } else {
            parent[root_x] = root_y;
            rank_tree[root_y]++;
        }
    }
    return 1;
}

int solve(){
    for (int i = 0; i < N; i++) {
        parent[i] = i;
        rank_tree[i] = 0;
    }
    for (int i = 0; i < N; i++) {
        for (auto adj_node: g[i]){
            int status = Union(i, adj_node);
            if (status == -1) {
                return status;
            }
        }
    }


}

int main(){
    int u, v;
    cin >> N >> M;
    g.resize(N);
    for (int i = 0; i < M; i++) {
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
    }
    int res = solve();
    if (res == -1) {
        cout << "Detect cycle" <<endl;
    } else {
        cout << "Not found cycle" << endl;
    }

}