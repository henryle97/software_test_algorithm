#include <iostream>
#include <vector>
#include <queue>


using namespace std; 


/***
 * 
 * There are n different online courses numbered from 1 to n. 
 * You are given an array courses where courses[i] = [durationi, lastDayi] 
 * indicate that the ith course should be taken continuously for durationi days
 * and must be finished before or on lastDayi.
 * You will start on the 1st day and you cannot take two or more courses simultaneously.
 * Return the maximum number of courses that you can take.
 * Input: courses = [[100,200],[200,1300],[1000,1250],[2000,3200]]
Output: 3
Explanation: 
There are totally 4 courses, but you can take 3 courses at most:
First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the 101st day.
Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day. 
Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day. 
The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
***/

class Solution {
public:

    typedef pair<int, int> pi;
    int scheduleCourse(vector<vector<int>>& courses) {
        priority_queue<pi, vector<pi>, greater<pi>> pq;

        for (auto course : courses) {
            int duration = course[0];
            int lastday = course[1];
            pq.push(make_pair(duration, lastday));
        }

        int currDay = 0;
        int numCourse = 0;
        while(!pq.empty()) {
            pi top = pq.top();
            if (top.second < currDay) {
                pq.pop();
                currDay += top.second;
                numCourse++;
            } else {
                pq.pop();
            }
        }


    }
};

