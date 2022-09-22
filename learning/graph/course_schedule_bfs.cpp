#include <iostream>
#include <vector>
#include <queue>


using namespace std; 

class Solution {
    
    
    // have dependence --> directed graph 
    // check have cycle ~ traverse all path in graph -> return false else true 
    // solution 2: bfs + indegree nodes 
    
public:
    
    
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        queue<int> q;
        vector<vector<int>> graph(numCourses);
        // create indegree list 
        vector<int> indegree(numCourses, 0);
        for (auto prerequisite : prerequisites){
            int course = prerequisite[0];
            int pre_course = prerequisite[1];
            indegree[course]++;
            graph[pre_course].push_back(course);
        }

        int count = 0;
        for (int i=0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
                count++;
            }
        }

        while (!q.empty()) {
            int curr_node = q.front();
            q.pop();
            

            for (auto adj_node : graph[curr_node]) {
                indegree[adj_node]--;
                if (indegree[adj_node] == 0) {
                    q.push(adj_node);
                    count++;
                }
            }


        }

        return count == numCourses ? true : false;

        
    }
};


int main() {
    Solution sol = Solution();
    
    int numCourses = 2;
    vector<vector<int>> prequires = {{1,0}, {0,1}};

    bool result = sol.canFinish(numCourses, prequires);
    cout << "Can finish ? : " << result << endl;
}