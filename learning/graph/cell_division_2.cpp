#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int T, N, M, K;
int max_cells, max_time;

long long spaces[550][550];
int visited[550][550]; // empty: 0 / occupied: 1  / tmp_occupied: -1

vector<pi> first_cells;
priority_queue<int, vector<int>, greater<int>> min_queue;
vector<vector<int>> moves{
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}};

vector<vector<pi>> group_cells;

bool is_valid(int x, int y)
{
    if (x >= 0 && x < N && y >= 0 && y < M && spaces[x][y] > 0 && visited[x][y] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void solve()
{
    int next_x, next_y;
    int curr_time = 0;
    int time_die;
    for (auto occupied_cell : first_cells)
    {
        next_x = occupied_cell.first;
        next_y = occupied_cell.second;
        visited[next_x][next_y] = 1; // mark as occupied cell
        time_die = curr_time + spaces[next_x][next_y] + 1;
        min_queue.push(time_die);
    }
    int size_q = min_queue.size();
    max_cells = max(max_cells, size_q);
    max_time = curr_time;
    group_cells.push_back(first_cells);

    while (true)
    {

        int row, col;
        bool is_divide = false;
        curr_time++;
        vector<pi> new_cells;
        vector<pi> pre_cells = group_cells.back();

        for (auto cell : pre_cells)
        {
            row = cell.first;
            col = cell.second;
            if (visited[row][col] == 1)
            { // occupied cell
                for (auto move : moves)
                {
                    next_x = row + move[0];
                    next_y = col + move[1];
                    if (is_valid(next_x, next_y))
                    {
                        visited[next_x][next_y] = 1;
                        int time_die = curr_time + spaces[next_x][next_y] + 1;
                        min_queue.push(time_die);
                        is_divide = true;
                        new_cells.push_back(make_pair(next_x, next_y));
                    }
                }
            }
        }

        if (!is_divide)
        {
            return;
        }

        group_cells.push_back(new_cells);

        // remove die cells
        while (!min_queue.empty() && min_queue.top() <= curr_time)
        {
            min_queue.pop();
        }

        int size_q = min_queue.size();
        if (size_q > max_cells)
        {
            max_cells = size_q;
            max_time = curr_time;
        }
    }
}

int main()
{
    cin >> T;
    for (int test_case = 1; test_case <= T; test_case++)
    {

        first_cells.clear();
        group_cells.clear();
        while (!min_queue.empty())
        {
            min_queue.pop();
        }

        cin >> N >> M >> K;
        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < M; col++)
            {
                cin >> spaces[row][col];
            }
        }
        int x, y;
        for (int i = 0; i < K; i++)
        {
            cin >> x >> y;

            // NOTE: MUST reformat to 0-index
            x--;
            y--;
            first_cells.push_back(make_pair(x, y));
        }

        max_cells = INT32_MIN;
        max_time = 0;
        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < M; col++)
            {
                visited[row][col] = 0;
            }
        }

        solve();

        cout << "#" << test_case << " " << max_cells << " " << max_time << endl;
    }
}