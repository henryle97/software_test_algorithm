#include <bits/stdc++.h>

using namespace std;


int T, N, M;
int tmp;
vector<vector<int>> zones;
priority_queue<int> pq;

int maxRes;

void solve() {
    for (int zone_idx = N-1; zone_idx >= 0; zone_idx--) {
        for (auto value : zones[zone_idx]) {
            pq.push(value);
        }
        maxRes = maxRes + pq.top();
        pq.pop();

    }
}


int main() {
    cin >> T;
    for (int test_case = 1; test_case <= T; test_case++) {
        zones.clear();
        while(!pq.empty()){
            pq.pop();
        }
        maxRes = 0;
        cin >> N;
        for (int i = 0; i < N; i++){
            cin >> M;
            vector<int> tmp_list;
            for (int j = 0; j < M; j++) {
                cin >> tmp;
                tmp_list.push_back(tmp);
            }
            zones.push_back(tmp_list);
            tmp_list.clear();
        }
        solve();
        cout << "#" << test_case << " " << maxRes << endl;
    }
}