#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> res;
    vector<int> path;
    vector<bool> visited;
    
    
    void backtrack(vector<int>& nums){
        // selection - path - end condition 

        // end condition 
        if (path.size() == nums.size()) {
            res.push_back(path);
            return;
        }
        
        // selections 
        for (auto num : nums) {
            if (!visited[num]) {
                visited[num] = true;
                path.push_back(num);  // save path 
                
                backtrack(nums);
                
                path.pop_back();   // unselection 
                visited[num] = false;
                
            }
        }
    }
    
    
    vector<vector<int>> permute(vector<int>& nums) {
        visited.resize(nums.size(), false);
        backtrack(nums);
        
        
        return res;
    }

};


int main() {
    Solution sol = Solution();
    vector<int> inp = {1,2,3};
    vector<vector<int>> result = sol.permute(inp);
    cout << "Path " << result.size() << endl;
}