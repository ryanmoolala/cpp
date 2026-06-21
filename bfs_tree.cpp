#include <iostream>
#include <queue>

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

void bfs(TreeNode* root) {
    queue<TreeNode*> myQueue;
    myQueue.push(root);
    while (!myQueue.empty()) {
        TreeNode* currentNode = myQueue.front();
        myQueue.pop();
        if (currentNode->leftChild) myQueue.push(currentNode->leftChild);
        if (currentNode->rightChild) myQueue.push(currentNode->rightChild);
        cout << currentNode->val << " ";
    }
}

int main() {
    //Create tree
    TreeNode* root = createTree();
    bfs(root);
    return 0;
}