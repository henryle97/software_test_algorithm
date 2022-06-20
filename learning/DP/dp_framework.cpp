// Source : *
// Author : Hoang Le
// Date   : 2022-06-15

/***************************************************************************************************** 
 *  Dynamic Programing framework
 * - The general form of a dynamic programming problem is maximal (involve finding the maximum value).
 * - The core problem of solving DP is exhaustion 
 * - Need to master recursive thingking 
 * 
 * - Three elemens of DP (***)
 * 
 *  + The overlapping subproblems ( subproblem is calculated twice)
 *  + Optimal substructures (the subproblems must be independent of each other + if an optimal solution can be constructed from optimal solutions of its subproblems) 
 *  + State transtition equaltions (most difficult): 
 *      * framework:  1. clear base case -> 2. clear state -> 3. clear choice -> 4. define the meaning of dp array)
 *  
 * 
 * 
 *  - General framework code:
 *    # top-down recursive DP
 *      def dp(state_1, state_2,...):
 *          for selection in all_possible_selections:
 *              # the state at this time has changed because of the selection
 *              result = find the most value(result, dp(state_1, state_2,...))
 *      
 * 
 * 
 *    # bottom-up iterative DP
 *      # initialize base case 
 *      dp[0][0][...] = base case 
 *      # make state trasition 
 *      for all_values_of_state_1 in state_1:
 *          for all_values_of_state_2 in state_2:
 *              for ...:
 *                  dp[state_1][state_2][...] = find the maximal value(state_1, state_2,...)      
 * 
 * 
 * - Example 1: Fibonaci calculate 
 *   + overlapping subproblems: f(x) is calculated twice 
 * 
 * - Example 2: 322. Coin change  

        You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

        Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

        You may assume that you have an infinite number of each kind of coin.

        

        Example 1:

        Input: coins = [1,2,5], amount = 11
        Output: 3
        Explanation: 11 = 5 + 5 + 1
        Example 2:

        Input: coins = [2], amount = 3
        Output: -1
        Example 3:

        Input: coins = [1], amount = 0
        Output: 0
        

        Constraints:

        1 <= coins.length <= 12
        1 <= coins[i] <= 231 - 1
        0 <= amount <= 104
 *  --> Solution:
 *  Step 1: This problem is a DP problem because it has an OPTIMAL SUBSTRUCTURE
 *  Step 2: State transition equation:
 *      + base case: amout = 0 -> return 0
 *      + state (variable that will change in the original problem and subproblems): amount 
 *      + choice: (the behavior that causes the state to change): face values of all coins 
 *      + definition of dp function: dp[state]=dp[amount]=min_coins (the return value of func is the question ask us)
 *            -> func dp[n] is the minimum number of coins that n needed 
 * 
 ******************************************************************************************************/



#include <iostream>
#include <vector>

using namespace std;


int minCoins(vector<int> coins, int amount) {
       // base cases 
	if (amount == 0) {
		return 0;
       
	}
	if (amount < 0) {
		return -1;
	}
	int result = INT32_MAX;

	// choose selections
	for (int coin : coins) {
		int res_subproblem = minCoins(coins, amount - coin);      // DP[amount] = 1 + DP[amoun-coin_x]
		if (res_subproblem == -1) continue;
		result = min(result, res_subproblem + 1);
		cout << coin << " " << result << endl;
	}

	return result == INT32_MAX ? -1 : result;
}

int coinChange(vector<int> coins, int amount) {
    return minCoins(coins, amount);
}



int minCoinWithDPBottomUp(vector<int> coins, int amount) {
	int dp[amount+1];
	for (int i = 0; i< sizeof(dp)/ sizeof(dp[0]); i++) {
		dp[i] = amount + 1;
	}
	dp[0] = 0;

	// for all states
	for (int sub_amount; sub_amount <= amount; sub_amount++) {
		// for all selection 
		for (int coin: coins) {
			if (sub_amount - coin < 0) continue;
			dp[sub_amount] = min(dp[sub_amount], 1 + dp[sub_amount-coin]);
		}
		return dp[amount] == amount + 1 ? -1 : dp[amount];
	}

	
}



int main() {
    //    int n;
	//    int amount;
    //    vector<int> coins;
    //    cin >> n >> amount;
    //    for (int i=0; i < n; i++) {
    //           cin >> coins[i];
    //    }
		vector<int> coins = {1,2,5};
		int amount = 11;
		int result = coinChange(coins, amount);
		cout << result << endl;
}