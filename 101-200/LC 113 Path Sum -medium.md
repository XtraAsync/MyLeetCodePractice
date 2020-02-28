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

实际上使用的是迭代写法的中序遍历：

要取出路径上的结点值，所以用一个 vector 来代替 stack

首先用 while 循环找到最左子结点，在找的过程中，把路径中的结点值都加起来，这时候取出 vector 中的尾元素，如果为叶节点都不存在且当前累加值正好等于 sum 了，将这条路径取出来存入结果 res 中，

下面的部分是和一般的迭代中序写法有所不同的地方，由于中序遍历的特点，遍历到当前结点的时候，是有两种情况的，

1）有可能此时是从左子结点跳回来的，此时正要去右子结点，则当前的结点值还是算在路径中的， 也就是**经历了while(cur)**

2）注意： 第二种情况的时候实际上左根右中的根节点已经访问过了（根节点的访问是第一种情况）

当前访问完了右子树，也就是访问完毕了当前根的整个子树，此时直接跳回根的父节点结点，此时就要减去当前结点值，因为其已经不属于路径中的结点了。**这种情况指的是，通过 !cur && !s.empty() 跳到的**，也就是右半部分已经遍历完了

为了区分这两种情况，这里使用一个额外指针 pre 来指向前一个结点，如果右子结点存在且不等于 pre，直接将指针移到右子结点，反之更新 pre 为 cur，cur 重置为空，val 减去当前结点，st 删掉最后一个结点

先回顾一下二叉树中序遍历的迭代写法：

```c++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        vector<int> res;
        TreeNode* cur = root;
        while(cur || !s.empty()){
            while(cur){
                s.push(cur);
                cur = cur->left;
            }
            auto tmp = s.top(); s.pop();
            res.push_back(tmp->val);
            cur = tmp->right;
        }
        return res;
    }
};
```

加一些改动：

1. 程序在向左子不断遍历的时候， 除了要入栈，还要修改当前的累积和
2. 原先中序遍历打印节点的地方， 我们称为访问一个点，如上文所说这个地方有两种情形
3. 这里面第一次访问根的时候不pop出来，第二次才会， 因为要保存当前子树根的val值

```c++
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        vector<TreeNode*> s;
        int curVal = 0;
        TreeNode* cur = root, *pre = nullptr;
        while(cur || !s.empty()){
            while(cur){
                s.push_back(cur);
                curVal += cur->val;
                cur = cur->left;
            }
            cur = s.back();
            if(curVal == sum && !cur->left && !cur->right){
                vector<int> tmp;
                for(auto v: s) tmp.push_back(v->val);
                res.push_back(tmp);
            }
            // - 正常访问右子节点 -
            if(cur->right && pre != cur->right){
                cur = cur->right;
            }
          	// - 已经遍历完了右边 -
          	else {
                pre = cur;
                curVal -= cur->val;
                cur = nullptr;
                s.pop_back();
            } 
        }
        return res;
    }
};
```

