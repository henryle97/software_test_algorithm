#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int  parent[1000];  // root: parent[root] = root 
int  rank_tree[1000];
int N, M;
int a, b;


int Find(int x){
    if (parent[x] != x) {
        parent[x] = Find(x);
    }
    return parent[x];
}

void Union(int x, int y) {
    int root_x = Find(x);
    int root_y = Find(y);

    if (root_x == root_y) {
        return;
    }

    if (rank_tree[root_x] < rank_tree[root_y]) {
        parent[root_x] = root_y;
    } else if (rank_tree[root_x] > rank_tree[root_y]) {
        parent[root_y] = root_x;
    } else {
        parent[root_x] = root_y;
        rank_tree[root_y]++;
    }


}

void printDisjoinSet(){
    for (int i = 0; i < N; i++) {
        cout << parent[i] << " ";
    }
    cout << endl;
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> parent[i];
        rank_tree[i] = 0;
    }

    printDisjoinSet();
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        Union(a, b);
        printDisjoinSet();
    }
}