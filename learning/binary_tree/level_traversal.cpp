/*
- The recursive solution of binary tree problems can be divided into two types of ideas. 
    + Type 1: Traverse the binary tree to get the answer -> backtracking 
    + Type 2: calculate the answer by decomposing the problem -> dynamic programing 


Example: Maximum depth of binary tree 

        3
    /       \
   9         20                -> max depth = 3
            / \
          15  7  

 
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    struct TreeNode *left, *right = NULL;
};

TreeNode* addNode(int data){
    TreeNode* tmp = new TreeNode;
    tmp->data = data;
    tmp->left = tmp->right = NULL;
}

TreeNode* createTree() {
    TreeNode* root = addNode(3);
    root->left = addNode(9);
    root->right = addNode(20);
    root->right->left = addNode(15);
    root->right->right = addNode(7);
    return root;
}


// level-order traversal 
vector<vector<int>> levelOrderTraversal(TreeNode* root) {

    queue<TreeNode*> q;
    q.push(root);
    TreeNode* node;

    vector<vector<int>> result;

    while (!q.empty())
    {
        int num_node_in_layer = q.size();
        vector<int> level_nodes;
        for (int i=0; i < num_node_in_layer; i++){
            node = q.front();
            q.pop();
            level_nodes.push_back(node->data);
            // 
            if (node->left != NULL) {
                q.push(node->left);
                
            }
            if (node->right != NULL) {
                q.push(node->right);
            }
        }
        if (level_nodes.size() != 0) {
            result.push_back(level_nodes);
        }
        
    };
    return result;
    

}



int main(){
    TreeNode* root = createTree();
    levelOrderTraversal(root);

}
