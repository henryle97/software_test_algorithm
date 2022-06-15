/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// diameter = sum of max depth subtree left and subtree right 
class Solution {
public:
    int maxDiameter = 0;

    int traverse(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int leftDepth = traverse(root->left);
        int rightDepth = traverse(root->right);
        
        maxDiameter = max(maxDiameter, leftDepth+rightDepth);
        
        return max(leftDepth, rightDepth) + 1;
    }
    
    int diameterOfBinaryTree(TreeNode* root) {
        
        traverse(root);
        return maxDiameter;
    }
};