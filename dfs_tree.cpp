#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* leftChild;
    TreeNode* rightChild;
    TreeNode(int v) : val(v), leftChild(nullptr), rightChild(nullptr) {}
};

TreeNode* createTree() {
    TreeNode* root = new TreeNode(1);
    root->leftChild = new TreeNode(2);
    root->rightChild = new TreeNode(3);
    root->leftChild->leftChild = new TreeNode(4);
    root->leftChild->rightChild = new TreeNode(5);
    root->rightChild->rightChild = new TreeNode(6);
    root->leftChild->rightChild->leftChild = new TreeNode(7);
    return root;
}

void dfs(TreeNode* root) {
    if (root == nullptr) {
        return; 
    }
    cout << root->val << " ";
    dfs(root->leftChild);
    dfs(root->rightChild);
}

int main() {
    //Create tree
    TreeNode* root = createTree();
    dfs(root);
    return 0;
}