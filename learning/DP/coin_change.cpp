// Source : *
// Author : Hoang Le
// Date   : 2022-06-15

/***************************************************************************************************** 
 *  Counting bit
Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.
Example 1:

Input: n = 2
Output: [0,1,1]
Explanation:
0 --> 0
1 --> 1
2 --> 10
Example 2:

Input: n = 5
Output: [0,1,1,2,1,2]
Explanation:
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101
 
Constraints:
0 <= n <= 105
Follow up:

It is very easy to come up with a solution with a runtime of O(n log n). Can you do it in linear time O(n) and possibly in a single pass?
Can you do it without using any built-in function (i.e., like __builtin_popcount in C++)?

 * Solution:
 *
 * 6 = 110 -> 6*2=12=1100 (2 bit 1)
 * 8 = 1000
 * 7 = 111
 * 9 = 1001 
 * num_bit[x] = num_bit[x/2] if x is even else num_bit[x/2] + 1;
 * 
 ******************************************************************************************************/

class Solution {
public:
    // vector<int> countBits(int n) {
    //     // use rule 
    //     vector<int> bits(n+1);
    //     bits[0]=0;
    //     bits[1]=1;
    //     for (int i = 2; i <= n; i++) {
    //         if (i % 2 == 0) {
    //             bits[i] = bits[i/2];
    //         } else {
    //             bits[i] = bits[i/2] + 1;
    //         }
    //     }
    //     return bits;
    // }
};

