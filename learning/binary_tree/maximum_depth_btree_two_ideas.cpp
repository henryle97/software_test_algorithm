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



// Sol 1: traversal tree 
int curDepth = 0;
int maxDepth = 0;

// traversal framework 

void traversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // add condition 
    curDepth++;
    cout << root->data << " " << curDepth << endl;
    if (root->left == NULL && root->right == NULL) {
        
        maxDepth = max(maxDepth, curDepth);
    }
    // 


    traversal(root->left);
    traversal(root->right);
    curDepth--;

}

int calMaxDepthWithTraversal(TreeNode* root) {
    traversal(root);
    return maxDepth;

}

int calMaxDepthWithDecomposing(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int left_h = calMaxDepthWithDecomposing(root->left);
    int right_h = calMaxDepthWithDecomposing(root->right);
    return max(left_h, right_h) + 1;

}



int main(){
    TreeNode* root = createTree();
    int result = calMaxDepthWithTraversal(root);
    cout << result << endl;
    cout << calMaxDepthWithDecomposing(root) << endl;

}
