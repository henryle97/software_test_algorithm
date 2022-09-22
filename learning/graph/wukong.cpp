#include <iostream>
#include <queue>
#include <vector>
#include <bits/stdc++.h>


using namespace std;

typedef pair<int, int> pi;

bool myComp(pi item_1, pi item_2) {
    return (item_1.first < item_2.first);
}

priority_queue<int, vector<int>, greater<int>> min_q;   // min queue by time died of the monster , default


vector<pi> monsters;

int T;
int N, K;
int t, hp;
int time_die;
int min_waves;

void solve(){
    // sort monsters by non-decreasing time appear
    sort(monsters.begin(), monsters.end(), myComp);
    int time = 0;   // time appear = 1, hp = 7 -> time die = 8

    for (auto monster : monsters) {
        t = monster.first;
        hp = monster.second;
        time_die = t + hp;
        
        // remove died monster
        while(!min_q.empty() && min_q.top() <= t) {
            min_q.pop();
        }


        // use wave if monster > K 
        if (min_q.size() == K) {
            while(!min_q.empty()) {
                min_q.pop();
            }
            min_waves++;
        }

        min_q.push(time_die);
        
    }

}


int main() {
    cin >> T;
    for (int test_idx = 1; test_idx <= T; test_idx++) {
        // reset variable 
        monsters.clear();
        while (!min_q.empty()) { 
            min_q.pop();
        }
        min_waves = 0;


        cin >> N >> K;
        for (int i = 0; i < N; i++) {
            cin >> t >> hp;
            monsters.push_back(make_pair(t, hp));
        }
        solve();
        cout << "#" << test_idx << " " << min_waves << endl;
    }
}