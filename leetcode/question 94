class Solution {
public:
    void inorderTraversalHelper(TreeNode* root, vector<int>& result) {
        if (root == nullptr) return;
        inorderTraversalHelper(root->left, result); 
        result.push_back(root->val); 
        inorderTraversalHelper(root->right, result); 
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorderTraversalHelper(root, result);
        return result;
    }
};