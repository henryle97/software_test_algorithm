#include <iostream>
#include <vector>
#include <algorithm>



using namespace std;
int T;
int N, M, Q;

typedef pair<int, int> pi;
typedef long long ll;
vector<pair<pi, ll>> edges;
vector<ll> mst_weights;

ll K_list[400000];
unsigned long long result;

int parent[400000];
int rank_tree[400000];

int Find(int x) {
    if (parent[x] != x) {
        parent[x] = Find(parent[x]);
    }
    return parent[x];
}

int Union(int x, int y){  //O(logM)
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

bool myComp(pair<pi, ll> a, pair<pi, ll> b){
    return a.second < b.second;
}

ll kruskal(){
    int u, v;
    ll min_weight = 0;
    int num_edges = 0;

    for (int i = 0; i < N; i++) {
        parent[i] = i;
        rank_tree[i] = 0;
    }

    // sort edges increase: O(MlogM)
    sort(edges.begin(), edges.end(), myComp);

    // O(MlogN)
    for (auto edge : edges) {
        pi pair_uv = edge.first;
        ll weight_uv = edge.second;
        u = pair_uv.first;
        v = pair_uv.second;
        int status = Union(u, v);

        if (status == 1) { // not make cycle
            mst_weights.push_back(weight_uv);
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


void solve(){
    long long num_edges, upper_idx, num_edges_need;
    result = 0;
    ll mst_w = kruskal();

    // return -1;

    // O(Q * (V-1))
    for (int idx = 0; idx < Q; idx++) {
        ll k = K_list[idx];

        // O(N-1)
        // for (int i = 0; i < mst_edges.size(); i++){
        //     pair<pi, ll> edge = mst_edges[i];
        //     ll edge_w = edge.second;

        //     if (edge_w > k) {
        //         int num_edges_need = mst_edges.size() - i;
        //         result = result + (idx + 1) * num_edges_need;
        //         break;
        //     }

        // }
        // improve O(logN) -- binary search (upper_bound)
        // upper_bound() return iterator of first index that have value larger than x 
        vector<ll>::iterator upper_iter = upper_bound(mst_weights.begin(), mst_weights.end(), k);

        num_edges = mst_weights.size();
        upper_idx = upper_iter - mst_weights.begin();
        num_edges_need = max((long long) 0, num_edges - upper_idx);
        
        result += (unsigned long long) (idx + 1) * num_edges_need;

    }
    
}

int main() {
    
    ios_base::sync_with_stdio(0);
    int u, v;
    ll w;
    cin >> T;
    
    for (int test_id = 1; test_id <= T; test_id++){
        cin >> N >> M >> Q;
        edges.clear();
        mst_weights.clear();
        
        for (int i = 0; i < M; i++) {
            cin >> u >> v >> w;
            u--;
            v--;
            edges.push_back(make_pair(make_pair(u, v), w));
        }

        for (int i = 0; i < Q; i++) {
            cin >> K_list[i];
        }

        solve();
        cout << "#" << test_id << " " << result << endl;
    }
    
}