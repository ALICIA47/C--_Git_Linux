class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if(root==nullptr)return result;

        queue<TreeNode*>q;
        q.push(root);
        bool leftToright=true;
        
        while(!q.empty()){
            int levelsize=q.size();
            vector<int>currentlevel(levelsize);
            for(int i=0;i<levelsize;i++){
                TreeNode*Node=q.front();
                q.pop();

                int index=leftToright?i:(levelsize-1-i);
                currentlevel[index]=Node->val;
                
                if(Node->left!=nullptr)q.push(Node->left);
                if(Node->right!=nullptr)q.push(Node->right);
            }
            result.push_back(currentlevel);
            leftToright=!leftToright;
        }
        return result;
    }
};