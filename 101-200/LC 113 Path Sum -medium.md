#### LC 113 Path Sum:

这道题就是边存路径变继续dfs的一道题：

使用一个temp保存中途访问的点，其中注意一点是：如果题目中所有的值都是正整数，可以做sum剪枝，但是这道题里存在负数，所以不做剪枝

注意 pop_back

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 * 		int val;
 * 		TreeNode *left;
 * 		TreeNode *right;
 * 		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

   class Solution {
   public:
   vector<vector<int>> pathSum(TreeNode* root, int sum) {
       vector<vector<int>> res;
       vector<int> tmp;
       helper(root, 0, tmp, sum, res);
       return res;
   }
   void helper(TreeNode* root, int cur, vector<int>& tmp, int sum, vector<vector<int>>& res){
       if(!root) return;
       cur += root->val;
       // if(cur > sum) return;
       tmp.push_back(root->val);
       if(cur == sum && !root->left && !root->right){
           res.push_back(tmp);
       }else{
           if(root->left){
               helper(root->left, cur, tmp, sum, res);
           }
           if(root->right){
               helper(root->right, cur, tmp, sum, res);
           }
       }
       tmp.pop_back();
   }
};
```

删掉一些没必要的代码：

```c++
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        vector<int> tmp;
        helper(root, 0, tmp, sum, res);
        return res;
    }
    void helper(TreeNode* root, int cur, vector<int>& tmp, int sum, vector<vector<int>>& res){
        if(!root) return;
        cur += root->val;
        tmp.push_back(root->val);
        if(cur == sum && !root->left && !root->right){
            res.push_back(tmp);
        }
        helper(root->left, cur, tmp, sum, res);
        helper(root->right, cur, tmp, sum, res);
        tmp.pop_back();
    }
};
```

这道题还有迭代的解法：



