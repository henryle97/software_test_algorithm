
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    
    // path = status of the rows , selection: index of queen in a row 
    vector<vector<string>> res;
    
    bool isValid(vector<string> board, int row, int col) {
        for (int idx = 0; idx < row; idx++) {
            cout << board[idx][col] << " " <<  board[row][col] << endl;
            if (board[idx][col].compare("Q")) {
                return false;
            }
        }
        
        return true;
    }
    
    void backtrack(vector<string> board, int row) {
        if (row == board.size()) {
            res.push_back(board);
            return;
        }
        for (int col = 0; col < board[0].length(); col++ ) {
            
            if (!isValid(board, row, col)){
                continue;
            }
            
            board[row][col] = 'Q';
            backtrack(board, row+1);
            board[row][col] = '.';
  
            
        }
        
    }        
    
    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        
        backtrack(board, 0);
        
        return res;
    }
};


int main() {
    int n = 8;
    Solution sol = Solution();
    vector<vector<string>> res = sol.solveNQueens(n);
    cout << res.size();
}