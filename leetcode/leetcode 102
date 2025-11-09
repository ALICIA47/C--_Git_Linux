class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if(root==nullptr)return result;

        queue<TreeNode*>q;
        q.push(root);
        while(!q.empty()){
            int levelsize=q.size();
            vector<int> currentlevel;

            for(int i=0;i<levelsize;i++){
                TreeNode*Node=q.front();
                q.pop();
                currentlevel.push_back(Node->val);

                if(Node->left!=nullptr)q.push(Node->left);
                if(Node->right!=nullptr)q.push(Node->right);
            }
            result.push_back(currentlevel);
        }
        return result;
    }
};