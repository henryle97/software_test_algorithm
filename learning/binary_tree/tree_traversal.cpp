/*
Tree traversals: 
* the pre-middle-post-order is the three special time points at which each node is processed in the process of traversing the binary tree
- The code in the preorder position is executed when just entering a binary tree node;
    -> top-down
- The code in the post-order position is executed when it is about to leave a binary tree node;
    -> bottom-up
- The code in the inorder position is executed when the left subtree of a binary tree node has been traversed, and the right subtree is about to be traversed.

??? 
- Why the multi-fork tree does not have an in-order position ? Because each node of the binary tree will only switch the left subtree to the right subtree once,
and the multi-fork tree may have many child nodes, which will switch subtrees multiple times, to traverse, so there is no unique 
in-order traversal position for a multi-fork tree. 

--> 
- You only need to think about what each nodes should do separately.

*/


#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    struct TreeNode *left, *right;
};

TreeNode* newNode(int data){
    TreeNode* temp = new TreeNode;
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Tree traversal framework 
void traversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    cout << root->data << " ";  // print pre-order
    traversal(root->left);

    // inorder 
    // cout << root->data << " ";
    traversal(root->right);

    // postorder 
    // cout << root->data << " ";
}

int traversal_with_level(TreeNode* root, int level) {
    if (root == NULL) {
        return 0;
    }
    cout << root->data << " " << level << endl;
    int h_left = traversal_with_level(root->left, level+1);
    int r_left = traversal_with_level(root->right, level+1);
    return max(h_left, r_left) + 1;
}

int cal_nodes_in_subtrees(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int num_node_left = cal_nodes_in_subtrees(root->left);
    int num_node_right = cal_nodes_in_subtrees(root->right);
    cout << "root: " << root->data << ", node left: " << num_node_left << ",node right:" << num_node_right << endl;
    return num_node_left + num_node_right +1;
}




// void printPostOrder(TreeNode* node){
//     if (node == NULL) {
//         return;
//     }
//     printPostOrder(node->left);
//     printPostOrder(node->right);
//     cout << node->data << " ";
// }

int main() {
    TreeNode* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    
    traversal(root);
    cout << "Print level of nodes:" << endl;
    traversal_with_level(root, 1);

    cal_nodes_in_subtrees(root);
    return 0;
} 