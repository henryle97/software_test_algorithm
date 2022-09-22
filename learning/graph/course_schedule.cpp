#include <iostream>
#include <vector>
using namespace std; 

class Solution {
    
    
    // have dependence --> directed graph 
    // check have cycle in a graph problem 
    
    // Solution 1: traverse all path in graph -> return false else true 
    public:
        
        vector<bool> onPath;
        vector<bool> visited;
        bool hasCycle;
        
        // dfs with non-recursion 
    //     void dfs(vector<vector<int>> graph, int s, int V) {
    //         stack<int> st;
    //         st.push(s);
    //         vector<int> visited;
    //         visited.resize(V ,0);   // 0 - non visited; 1 - visited; -1 visited and end of path
    //         bool hasCycle = false;
    //         int curr_node;
            
    //         bool isAppended;
    //         while(!st.empty()) {
                
    //             curr_node = st.top();
    //             st.pop();
                
    //             isAppended = false;
    //             for (auto adj_node : graph[curr_node]) {
    //                 if (visited[adj_node] == 0) {
    //                     st.push(adj_node);
    //                     isAppended = true;
    //                 } 
                
    //             if (isAppended) {
    //                 visited[curr_node] = 1;
    //             } else {
    //                 visited[curr_node] = -1;
    //             }
                
                
                
    //         }
    //     }
        
    //     // dfs with recursion 
        void traverse(vector<vector<int>> graph, int s) {
            
            if (onPath[s]) {
                
                hasCycle = true;
            }
            
            if (visited[s] || hasCycle) {
                return;
            }
            
            visited[s] = true;
            onPath[s] = true;
            for (auto adj_node: graph[s]) {
                
                traverse(graph, adj_node);
            }
            onPath[s] = false;
            
        }
        
        
        bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
            // create graph
            vector<vector<int>> graph;
            graph.resize(numCourses);
            
            
            for (auto prerequisite : prerequisites) {
                graph[prerequisite[1]].push_back(prerequisite[0]);
            }
            
            int i;
            for (i = 0; i < numCourses; i++) {
                visited.resize(numCourses, false);
                onPath.resize(numCourses, false);
                hasCycle = false;
                
                traverse(graph, i);
                if (hasCycle) {
                    for (int idx = 0; idx < numCourses; idx + 1) {
                        if (onPath[idx]) {
                            cout << idx << " ";
                        }
                    }

                    return false;
                }
            }
            return !hasCycle;
        }
};

int main() {
    Solution sol = Solution();
    
    int numCourses = 2;
    vector<vector<int>> prequires = {{1,0}, {0,1}};

    bool result = sol.canFinish(numCourses, prequires);
    cout << "Can finish ? : " << result << endl;
}