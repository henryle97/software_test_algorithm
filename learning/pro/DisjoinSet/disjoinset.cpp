#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


class DisjoinSet
{
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;

public:
    void makeSet(vector<int> const &universe) {
        for (auto i: universe) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int Find(int k) {
        if (parent[k] == k) {
            return k;
        }
        return Find(parent[k]);

        // improve: Path compression : compress the height of the trees 
        // if (parent[k] != k) {
        //     parent[k] = Find(parent[k]);
        // }
        // return parent[k];

    }

    // perform union of two sets 
    void Union(int a, int b) {
        int root_a = Find(a);
        int root_b = Find(b);


        // Union by rank 
        if (root_a == root_b) {
            return;
        }

        if (rank[root_a] > rank[root_b]){
            parent[root_b] = root_a;
        } else if (rank[root_a] < rank[root_b]){
            parent[root_a] = root_b;
        } else {
            parent[root_a] = root_b;
            rank[root_b]++;
        }

    }

};

void printSets(vector<int> const &universe, DisjoinSet &ds) {
    for (auto i : universe) {
        cout << ds.Find(i) << " ";
    }
    cout << endl;
}



int main() {
    vector<int> universe = {1,2,3,4,5};
    DisjoinSet ds;
    ds.makeSet(universe);
    printSets(universe, ds);

    ds.Union(4, 3);
    printSets(universe, ds);

}