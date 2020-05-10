#### LC 943 Find the Shortest Superstring

第一种思路是含有剪枝的暴力解法，首先是算出任意两个字符串拼接在一起时的重复字符数

剪枝也是最简单的剪枝：

第一个是如果当前长度已经超了，就直接cut

第二个是如果已经用上了所有单词，保存结果return

把overlap当作一个图每条边的权重的话， 题目就变成了给你一个图， 找出一种遍历所有地方的路线，使得权重最短，也就是旅行商问题

有了overlap数组，就变成了dfs求那种路径最短

下面这里面单独针对leetcode的一点是：

需要提前给curOrder分配全部的空间，而不是在每次的dfs中

```c++
curOrder.push_back(i);
helper();
curOrder.pop_back();
```

这种频繁的改变数组内元素个数的方式会超时

```c++
class Solution {
public:
    string shortestSuperstring(vector<string>& A) {
        int len = A.size();
        vector<vector<int>> overlap(len, vector<int>(len));
        for(int i = 0; i < len; i++){
            for(int j = 0; j < len; j++){
                if(i == j) continue;
                string a = A[i], b = A[j];
                int minLen = min(a.size(), b.size());
                for(int k = minLen; k>=0; k--){
                    if(a.substr(a.size() - k) == b.substr(0, k)){
                        // 因为是从k递减的， 所以第一个匹配的一定是最长的重复字符数
                        overlap[i][j] = k;
                        break;
                    }
                }
            }
        }
        // for(int i = 0; i < len; i++){
        //     for(int j = 0; j < len; j++){
        //         cout << A[i] << " " << A[j] << " " << overlap[i][j] << endl;
        //     }
        // }
        vector<int> curOrder(len), res;
        int used = 0, curBest = INT_MAX, curLen = 0, curSize = 0;
        helper(used, A, overlap, curOrder, res, curBest, curLen, curSize);
        string output = A[res.front()];
        // for(auto i: res) cout << A[i] << " ";
        for(int i = 1; i < res.size(); i++){
            auto m = res[i-1], n = res[i];
            output += A[n].substr(overlap[m][n]);
        }
        return output;
    }
    void helper(int used, vector<string> &A, vector<vector<int>> &overlap, vector<int>& curOrder, vector<int>& res, int &curBest, int curLen, int curSize){
        if(curLen >= curBest) return;
        if(curSize == A.size()){
            res = curOrder;
            curBest = curLen;
            return;
        }
        for(int i = 0; i < A.size(); i++){
            if(used & (1<<i)) continue;
            int nextLen = curLen + (curLen == 0? A[i].size(): A[i].size() - overlap[curOrder[curSize-1]][i]);
            curOrder[curSize] = i;
            helper(used | (1<<i), A, overlap, curOrder, res, curBest, nextLen, curSize+1);
        }
    }
};
```

