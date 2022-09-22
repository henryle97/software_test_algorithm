#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std; 

typedef pair<int, int> pi;    

int T, N, M, X;
int dist_from_party[2000];
int dist_from_src[2000];   //shortest path from src by using dijiktra algorithm 
vector<vector<pi>> graph;

struct compare 
{
    bool operator() (const pi& a, const pi& b) {
        return a.second > b.second; // min heap
    }
};

priority_queue<pi, vector<pi>, compare> pq;     // item <node, dist from src>


void dijiktra(int N, int src) {
    // save min_dist from source to all other vertical
    //reset dist_from_src
     for (int i = 0; i < N; i++) {
        dist_from_src[i] = INT32_MAX; 
    }
    vector<bool> visited;
    visited.resize(N, false);


    dist_from_src[src] = 0;
    pq.push(make_pair(src, dist_from_src[src]));

    while(!pq.empty()) {
        pi curr_pair = pq.top();
        pq.pop();
        
        int curr_point = curr_pair.first;
        visited[curr_point] = true;
        for (auto adj_pair: graph[curr_point]) {
            
            if (visited[adj_pair.first]) continue;
            dist_from_src[adj_pair.first] = min(dist_from_src[curr_point] + adj_pair.second, dist_from_src[adj_pair.first]);
            
            
            pq.push(make_pair(adj_pair.first, dist_from_src[adj_pair.first]));
        }

        
    }
}


void reverse_graph(int V){
    vector<vector<pi>> reverse_graph;
    reverse_graph.resize(V);
    int v, w;
    for (int u = 0; u < V; u++) {
        vector<pi> adj_edges = graph[u];
        for (auto pair: adj_edges) {
            v = pair.first;
            w = pair.second;
            reverse_graph[v].push_back(make_pair(u, w));
        }
    }
    graph = reverse_graph;
}


int main(){
    cin >> T;
    int test_index, road_idx;
    int u, v, w;
    int party_index, num_cows;
    for (test_index = 0; test_index < T; test_index++) {
        cin >> N >> M >> X;

        party_index = X-1;
        num_cows = N;
        graph.resize(num_cows);

        for (int i = 0; i < N; i++) {
            dist_from_party[i] = INT32_MAX;
            dist_from_src[i] = INT32_MAX; 
        }



        for (road_idx = 0; road_idx < M; road_idx++) {
            cin >> u >> v >> w;
            graph[u-1].push_back(make_pair(v-1, w));
        }
        
        int longest_dist = INT32_MIN;

        // find the shortest paths from X to all other farms.
        // return array[i] = min_dist(X->i);
        dijiktra(num_cows, party_index);
        for (int i = 0; i < N; i++) {
            dist_from_party[i] = dist_from_src[i];
        }

        reverse_graph(N);
        dijiktra(num_cows, party_index);


        // Iter: find the shortest path from ith farm to X: min_dist(i, X), if min_dist(i, X) + min_dist(X, i) > MAX_CURR_DIST -> save longest time that cow i taken.
        for (int cow_idx = 0; cow_idx < N; cow_idx++) {
            if (cow_idx == party_index) continue;
            int shortest_dist_from_cow_to_party = dist_from_party[cow_idx] + dist_from_src[cow_idx];
            if (shortest_dist_from_cow_to_party > longest_dist) {
                longest_dist = shortest_dist_from_cow_to_party;
            }
        }
        
        cout << "#" << test_index + 1 << " " << longest_dist << endl;
    
    }

}