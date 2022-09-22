/***
 * 
 * 
 * 
 ***/

#include <iostream>
#include <queue>
#include <vector>


using namespace std;


typedef pair<int, int> pi;
int T, R, C, r_start, c_start;
char OFF[110][110];
bool visited[110][110];
int dist_from_start[110][110];
bool no_found_door;
int min_time;

vector<pi> key_positions;
vector<int> time_find_keys;

vector<vector<int>> moves {
    {0, 1}, // right
    {0, -1}, //left 
    {1, 0}, // down
    {-1, 0}, // up     
};

bool isValid(int x, int y, bool haveKey) {
    if (x >= 0 && x < R && y >= 0 && y < C && !visited[x][y] && OFF[x][y] != 'X') {
        if (OFF[x][y] == 'A') {
            return haveKey;
        } else {
            return true;
        }
    } else {
        return false;
    }
}


void bfs(bool isFindKey, int indexKey){
    
    for (int row = 0; row < R; row++) {
        for (int col = 0; col < C; col++) {
            visited[row][col] = false;
        }
    }

    queue<pi> q;    // queu store cell position
    int start_x, start_y;
    // if findkey, start path = position of that people 
    if (isFindKey) {
        start_x = r_start;
        start_y = c_start;

    } else {
        // if not findkey, start find path from key position
        
        start_x = key_positions[indexKey].first;
        start_y = key_positions[indexKey].second;
    }

    q.push(make_pair(start_x, start_y));
    visited[start_x][start_y] = true;
    dist_from_start[start_x][start_y] = 0;


    while(!q.empty()) {
        pi curr_pos = q.front();
        q.pop();
        
        int curr_x = curr_pos.first;
        int curr_y = curr_pos.second;
        
        for (int i = 0; i < 4; i++) {
            vector<int> move = moves[i];
            int next_x = curr_x + move[0];
            int next_y = curr_y + move[1];
            
            bool haveKey = indexKey != -1;
            bool valid_position = isValid(next_x, next_y, haveKey);
            if (valid_position) {
                q.push(make_pair(next_x, next_y));
                visited[next_x][next_y] = true;
                dist_from_start[next_x][next_y] = dist_from_start[curr_x][curr_y] + 1;

                if (isFindKey) {
                    // found key 
                    if (OFF[next_x][next_y] == 'a') {
                        key_positions.push_back(make_pair(next_x, next_y));
                        time_find_keys.push_back(dist_from_start[next_x][next_y]);
                    }
                    
                    // reach exit 
                    if (OFF[next_x][next_y] == 'O') {
                        no_found_door = true;
                        min_time = dist_from_start[next_x][next_y];
                        return;
                    }
                }
                else {
                    // reach exit 
                    if (OFF[next_x][next_y] == 'O') {
                        min_time = min(min_time, dist_from_start[next_x][next_y] + time_find_keys[indexKey]);
                        return;
                    }
                }
                
            }
        }
    }

}

int solve(){
    
    // MUST: reset all global variable
    min_time = INT16_MAX;
    key_positions.clear();
    time_find_keys.clear();
    no_found_door = false;


    // check have any door before reach exit door.
    // get key positions 
    bfs(true, -1);
    if (no_found_door) {
        return min_time;
    }
    // get min path from keys to O 
    for (int key_index = 0; key_index < key_positions.size(); key_index++) {
        bfs(false, key_index);
    }
    return min_time;

}



int main() {
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cin >> R >> C;
        cin >> r_start >> c_start;
        // convert to 0-index
        r_start--;
        c_start--;

        for (int row = 0; row < R; row++) {
            for (int col = 0; col < C; col++) {
                cin >> OFF[row][col];
            }
        }
        
        int result = solve();

        // must format output when have exception (no found path)
        if (result == INT16_MAX) result = -1;
        
        cout << "#" << i << " " << result << endl;
    }    

}