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



第二种 dp的思路：

overlap的求法不变，

二维数组 dp，其中 dp\[i][j] 表示 mask 为i，且结尾是 A[j] 的超级串，**保存的是超级串本身**。

这里的 mask 跟上面解法中的 used 很像，利用二进制位来表示数组A中对应的字符串是否已经使用。

既然A中有n个数字，所以有n位的二进制数就是 2^n，这就是 mask 的大小范围

接下来是dp 数组初始化，因为数组中的每个字符串都有可能是超级串的开头，最开始我们只选中每个字符串本身，所以是mask里只有对应为为1，且以该字符串做结尾的数组 等于这个字符串的内容。

PS：因为目前只有一个字符串，所以直接用 1<<i 来表示 mask，并把 A[i] 加上对应位置上去。

```c++
for(int i = 0; i < len; i++) 
		dp[1<<i][i] = A[i];
```

更新部分:

要遍历 mask 的所有值，从1到 1<<n，这实际上是遍历数组A的所有子序列，对于每一个 mask 值，需要遍历其二进制每一个为1的对应位的字符串，变量j从0遍历到 n-1，假如 mask 的二进制数对应的j位上为0，则说明 A[j] 字符串未被使用，直接跳过。

如何更新 dp\[mask][j]，其表示的含义是使用了 mask 二进制对应位为1的所有的字符串组成的超级串，且最后一个位置是 A[j]的最短字符串，

为了更新它，需要分别让其他所有字符串依次当作结尾字符串， 加上这个A\[j]，并且减去重复的字符部分，最后取最短的那个即可。

我们设旧的字符串在 A 中的 index 为 endIndex，如果我们想更新新的那位， 新的结果一定是旧的字符串，加上删去了重复字符的新字符串

因为是去计算如果以新的字符串为结尾结果是什么，所以旧的字符串的mask不应包含这个新的字符串， 我们设新的字符串在A中的 index 为 i， 那么除去了 i 的mask的结果是 mask^(1<<i)

用较短的那个newStr来更新 dp\[mask][j] 即可

```c++
auto newStr = dp[mask^(1<<i)][endIndex] + // 旧的字符串
  						A[i].substr(overlap[endIndex][i]); // 删去重复字符的新字符串
```

最终的结果是保存在 mask 为 (1<<n)-1 的数组中的，因为所有的字符串都需要被使用，则 mask 二进制数的所有位都必须是1，在其对应的字符串数组中找到长度最短的那个返回即可

```c++
class Solution {
public:
    string shortestSuperstring(vector<string>& A) {
        int len = A.size();
        vector<vector<int>> overlap(len, vector<int>(len));
        vector<vector<string>> dp(1<<len, vector<string>(len));
        for(int i = 0; i < len; i++){
            for(int j = 0; j < len; j++){
                if(i == j) continue;
                string a = A[i], b = A[j];
                for(int k = min(a.size(), b.size()); k>=0; k--)
                    if(a.substr(a.size() - k) == b.substr(0, k)){
                        overlap[i][j] = k;
                        break;
                    }
            }
        }
        string output;
        for(int i = 0; i < len; i++) dp[1<<i][i] = A[i];
        for(int mask = 1; mask < (1<<len); mask++){
            for(int endIndex = 0; endIndex < len; endIndex++){
                if((mask & (1 << endIndex)) == 0) continue;
                for(int i = 0; i < len; i++){
                    // 新的字符串不能是旧的结尾， 同时也应该在这个mask里面
                    if(i == endIndex || ((mask&(1 << i)) == 0)) continue;
                    auto newStr = dp[mask^(1<<i)][endIndex] + A[i].substr(overlap[endIndex][i]);
                    if(dp[mask][i].empty() || newStr.size() < dp[mask][i].size())
                        dp[mask][i] = newStr;
                }
            }
        }
        int curMin = INT_MAX, minIndex = -1, last = (1<<len) - 1;
        for(int i = 0; i < len; i++){
            auto curLen = dp[last][i].size();
            if(curMin > curLen){
                curMin = curLen;
                minIndex = i;
            }
        }
        return dp[last][minIndex];
    }
};
```

