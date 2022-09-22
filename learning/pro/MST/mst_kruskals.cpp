#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
int N, M;

typedef pair<int, int> pi;
vector<pair<pi, int>> edges;

int parent[1000];
int rank_tree[1000];

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

bool myComp(pair<pi, int> a, pair<pi, int> b){
    return a.second < b.second;
}

int kruskal(){
    int u, v;
    int min_weight = 0;
    int num_edges = 0;

    for (int i = 0; i < N; i++) {
        parent[i] = i;
        rank_tree[i] = 0;
    }

    // sort edges increase
    sort(edges.begin(), edges.end(), myComp);

    for (auto edge : edges) {
        pi pair_uv = edge.first;
        int weight_uv = edge.second;
        u = pair_uv.first;
        v = pair_uv.second;
        int status = Union(u, v);

        if (status == 1) { // not make cycle
            min_weight += weight_uv;
            num_edges++;
            if (num_edges == N - 1) {
                return min_weight;
            }
        } else {
            continue;
        }

    }

    return min_weight;

}

int main() {

    cin >> N >> M;
    // edges.resize(M);
    int u, v, w;
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> w;
        edges.push_back(make_pair(make_pair(u, v), w));
    }

    int weight_mst = kruskal();
    cout << weight_mst << endl;

}