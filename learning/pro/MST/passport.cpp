#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef pair<long, long> pll;

// global variables
long T;
long N, M;
long long result;
vector<pair<pll, long>> edges;


// variables for disjoinset 
long long parent[150000];
long long rank_tree[150000];

long Find(long x) {
    if (parent[x] != x) {
        parent[x] = Find(parent[x]);
    }
    return parent[x];
}

long Union(long x, long y) {
    long root_x = Find(x);
    long root_y = Find(y);

    if (root_x == root_y) {
        return -1;
    } else{
        if (rank_tree[root_x] < rank_tree[root_y]) {
            parent[root_x] = root_y;
        } else if (rank_tree[root_x] > rank_tree[root_y]){
            parent[root_y] = root_x;
        } else {
            parent[root_x] =  root_y;
            rank_tree[root_y]++;
        }
    }

    return 1;
}

bool myComp(pair<pll, long> a, pair<pll, long> b){
    return a.second < b.second;
}

vector<pll> get_mst(vector<pair<pll, long>> roads) {
    vector<pll> edge_mst;
    for (long i = 0; i < N; i++) {
            parent[i] = i;
            rank_tree[i] = 0;
    }
    // sort 
    sort(roads.begin(), roads.end(), myComp);

    for (auto road : roads) {
        long status = Union(road.first.first, road.first.second);

        if (status == 1) {
            edge_mst.push_back(road.first);
        }
    }

    return edge_mst;

}

void solve(){
    // reset_all();
    long long u,v;
    set<pll> not_duplicate_roads;

    // sort edges: blue roads at first O(MlogM)
    sort(edges.begin(), edges.end(), myComp);
//
    // MST with only red + blue 
    vector<pair<pll, long>> red_blue_roads;
    for (auto edge : edges){    //O(N*logN)

        pll road_uv = edge.first;
        u = road_uv.first;
        v = road_uv.second;
        if (u > v) {
            road_uv = make_pair(v, u);
        }
        if (not_duplicate_roads.find(road_uv) != not_duplicate_roads.end()) {  // if found this road in set, skip
            continue;
        }

        long road_type = edge.second;
        if (road_type == 0 || road_type == 1) {
            long weight = road_type == 0 ? 1 : 2; // blue -> red/yellow
            red_blue_roads.push_back(make_pair(road_uv, weight));
        }
    }
    if (red_blue_roads.size() < N-1) {
        result = -1;
        return;
    }
    vector<pll> red_blue_mst = get_mst(red_blue_roads);  // O(NlogN)
    if (red_blue_mst.size() != N-1){
        result = -1;
        return;
    }


    // MST with only yellow + blue 
    not_duplicate_roads.clear();
    vector<pair<pll, long>> yellow_blue_roads;
    for (auto edge : edges){
        pll road_uv = edge.first;
        u = road_uv.first;
        v = road_uv.second;
        if (u > v) {
            road_uv = make_pair(v, u);
        }
        if (not_duplicate_roads.find(road_uv) != not_duplicate_roads.end()) {
            continue;
        }

        long road_type = edge.second;
        if (road_type == 0 || road_type == 2) {
            long weight = road_type == 0 ? 1 : 2; // blue -> red/yello
            yellow_blue_roads.push_back(make_pair(road_uv, weight));
        }
    }
    if (yellow_blue_roads.size() < N-1) {
        result = -1;
        return;
    }
    vector<pll> yellow_blue_mst = get_mst(yellow_blue_roads);


    // combine two MST 
    if (yellow_blue_mst.size() != N-1){
        result = -1;
        return;
    }

    // combine two vector
    vector<pll> combine_mst = red_blue_mst;
    combine_mst.insert(combine_mst.end(), yellow_blue_mst.begin(), yellow_blue_mst.end());
    set<pll> combine_mst_set(combine_mst.begin(), combine_mst.end());
    result = combine_mst_set.size();

}


int main() {
    ios_base::sync_with_stdio(0);

    cin >> T;
    long long u,v;
    long type;
    for (long testcase = 1; testcase <= T; testcase++){
        // clear global variable 


        edges.clear();
        cin >> N >> M;
        for (long i = 0; i < M; i++){
            cin >> u >> v >> type;
            u--;
            v--;
            edges.push_back(make_pair(make_pair(u, v), type));
        }
        solve();
        cout << "#" << testcase << " " << result << endl;
    }
    
    


}