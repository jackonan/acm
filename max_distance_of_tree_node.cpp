#include <iostream>
#include <tr1/unordered_map>

typedef unsigned int uint;

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    uint cost;

    TreeNode() :
        left(NULL),
        right(NULL),
        cost(0)
    {
    }
};

uint height(TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }

    static std::tr1::unordered_map<void*, uint> cache;

    typeof(cache.begin()) it = cache.find(root);
    if (it != cache.end()) {
        return it->second;
    }

    uint left = height(root->left);
    uint right = height(root->right);
    uint child = left > right ? left : right;

    uint ret = root->cost + child;
    cache.insert(std::make_pair(root, ret));

    return ret;
}

uint max_distance(TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }

    static std::tr1::unordered_map<void*, uint> cache;

    typeof(cache.begin()) it = cache.find(root);
    if (it != cache.end()) {
        return it->second;
    }

    uint leftCost = max_distance(root->left);
    uint rightCost = max_distance(root->right);

    uint leftHeight = height(root->left);
    uint rightHeight = height(root->right);

    uint childCost = leftCost > rightCost ? leftCost : rightCost;
    uint throughRoot = leftHeight + rightHeight + root->cost;

    uint ret = childCost > throughRoot ? childCost : throughRoot;
    cache.insert(std::make_pair(root, ret));

    return ret;
}

int main()
{
    TreeNode* root = new TreeNode;
    root->cost = 1;
    TreeNode* node1 = new TreeNode;
    node1->cost = 1;
    TreeNode* node2 = new TreeNode;
    node2->cost = 1;
    TreeNode* node3 = new TreeNode;
    node3->cost = 1;
    TreeNode* node4 = new TreeNode;
    node4->cost = 1;
    TreeNode* node5 = new TreeNode;
    node5->cost = 1;
    TreeNode* node6 = new TreeNode;
    node6->cost = 1;
    TreeNode* node7 = new TreeNode;
    node7->cost = 1;
    TreeNode* node8 = new TreeNode;
    node8->cost = 8;
    TreeNode* node9 = new TreeNode;
    node9->cost = 9;

    root->left = node1;
    root->right = node2;
    node1->left = node3;
    node2->left = node4;
    node2->right = node5;
    node3->left = node6;
    node4->left = node7;
    node5->left = node8;
    node5->right = node9;

    std::cout << max_distance(root) << std::endl;

    A* a = new B;
    a->f();

    return 0;
}
