#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int,int> pint;
enum status {
    NOT_VISITED,
    BROADING,
    VISITED_NOT_BROAD,
    VISITED_BROADED,
};


status visited[600][600];  // 0 - not yet visited, 1 - visited + not yet broad, 2- visited+broaded, -1: broading
long long A[600][600];


/**
 * It's a function object that compares two pairs of integers and returns true if the second element of
 * the first pair is greater than the second element of the second pair.
 * 
 * Now, let's use this type to sort a vector of pairs of integers.
 * 
 */
struct myComp {
    bool operator() (const pair<pint, int>& a, const pair<pint, int>& b)
    {
        return a.second > b.second;
    }

};

priority_queue<pair<pint, int>, vector<pair<pint, int>>, myComp> pq;  // min heap
int time_max = 0;
int num_cell_max = 0;

/**
 * The function iterates through the grid, and for each cell that is not visited, it checks if the cell
 * is alive, and if it is, it adds the cell to the priority queue, and marks the cell as visited. 
 * 
 * The function also iterates through the grid, and for each cell that is marked as visited, it marks
 * the cell as visited and not broaded. 
 * 
 * The function also removes all the cells that have died from the priority queue. 
 * 
 * The function also checks if the number of cells in the priority queue is greater than the maximum
 * number of cells in the priority queue, and if it is, it updates the maximum number of cells in the
 * priority queue and the time at which the maximum number of cells in the priority queue occurs. 
 * 
 * The function also checks if the grid has been broaded, and if it hasn't, it breaks out of the while
 * loop.
 * 
 * @param A the array of the input
 * @param N the number of rows in the grid
 * @param M the number of columns in the grid
 */
void solve(int N, int M) {
    int broaded_row, broaded_col;
    int t = 0;
    int die_time = 0;
    bool is_broaded;
    
    while (1){
        t++; 
        is_broaded = false;
        for(int cur_row = 0; cur_row < N; cur_row++) {
            for (int cur_col = 0; cur_col < M; cur_col++) {  // O(n)

                // skip if no food or visited +broaded
                if(A[cur_row][cur_col]== 0 || visited[cur_row][cur_col] == VISITED_BROADED) {
                    continue;
                }
                else if  (visited[cur_row][cur_col] == VISITED_NOT_BROAD) {  // visited + not yet broad
                    visited[cur_row][cur_col] = VISITED_BROADED;
                    
                    vector<pair<int, int>> moves = {
                        make_pair(cur_row-1, cur_col),  // top
                        make_pair(cur_row+1, cur_col),  // bottom
                        make_pair(cur_row, cur_col-1),  // left
                        make_pair(cur_row, cur_col+1)   // right
                    };

                    // check up : O(1)
                    for (auto pair : moves) {
                        broaded_row = pair.first;
                        broaded_col = pair.second;
                    
                        // isvalid(move);
                        if (broaded_row >= 0 && broaded_row <= N-1 && broaded_col >= 0 && broaded_col <= M-1) {  // in range of table
                            if (A[broaded_row][broaded_col] != 0 && visited[broaded_row][broaded_col] == NOT_VISITED) {
                                    die_time = t + A[broaded_row][broaded_col]+1;
                                    pq.push(make_pair(make_pair(broaded_row, broaded_col), die_time));  // O(Heigh of heap)
                                    visited[broaded_row][broaded_col] = BROADING;
                                    is_broaded = true;
                            }
                        }
                    }
                }

            }
        }

        // mask the boxes just visit from -1 to 1 
        for(int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (visited[i][j] == BROADING) {
                    visited[i][j] = VISITED_NOT_BROAD;  // visited + not yet broaded
                }
            }
        }


        // remove cell died in queue
        while(!pq.empty() && pq.top().second <= t) {
            pq.pop();
        }
        if (pq.size() > num_cell_max) {
            time_max = t;
            num_cell_max = pq.size();
        }
        if (!is_broaded) {
            break;
        }

    };
    
}


int main() {
    int T;
    int N, M, K;
    int col, row;
    int die_time;
    
    cin >> T;

    for (int test_idx = 0; test_idx < T; test_idx++) {
        time_max = 0;
        num_cell_max = 0;
        while ((!pq.empty()))
        {
            pq.pop();
        }
        
        cin >> N >> M >> K;
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                visited[i][j] = NOT_VISITED;
            }
        }
        
        for (int i = 0; i < N; i++) {
            for (int j=0; j < M; j++) {
                cin >> A[i][j];
            }
        }
        
        for (int i=0; i < K; i++) {
            cin >> row >> col; 
            visited[row-1][col-1] = VISITED_NOT_BROAD;
            die_time = A[row-1][col-1]+1;

            pq.push(make_pair(make_pair(row, col), die_time));
        }
        num_cell_max = K;
        solve(N, M);
        cout << "#" << test_idx+1 << " " << num_cell_max << " " << time_max << endl;

    }

    

    return 0;

}