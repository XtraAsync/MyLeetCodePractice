

所以最基本形式的解法如下

时间复杂度 o(kn^2)

空间复杂度 o(kn)

```c++
class Solution {
public:
    int maxProfit(int num, vector<int>& prices) {
        if(prices.size() == 0) return 0;
        vector<vector<int>> dp(num+1, vector<int>(prices.size(), 0));
        for(int k = 1; k <= num; k++){
            for(int i = 1; i < prices.size(); i++){
                int tmp = -prices[0];
                for(int j = 1; j <= i; j++){
                    tmp = max(tmp, dp[k-1][j-1] - prices[j]);
                }
                dp[k][i] = max(dp[k][i-1], prices[i] + tmp);
            }
        }
        return dp[num][prices.size()-1];
    }
};
```

这上面的代码可以做初步的优化：

```c++
int tmp = -prices[0];
for(int j = 1; j <= i; j++)
    tmp = max(tmp, dp[k-1][j-1] - prices[j]);
```

其中对于每个 j 要计算 从 0 计算到 i-1

所以其实是可以合并的，因为这些都是重复的计算

比如 i = 3时 计算了0-2的， i = 4时计算了0-3的

这期间重复计算了0-2的部分， 因为式子是与 i 无关的

时间复杂度 o(kn)

空间复杂度 o(kn)

```c++
class Solution {
public:
    int maxProfit(int num, vector<int>& prices) {
        if(prices.size() == 0) return 0;
        vector<vector<int>> dp(num+1, vector<int>(prices.size(), 0));
        for(int k = 1; k <= num; k++){
            int tmp = -prices[0];
            for(int i = 1; i < prices.size(); i++){
                tmp = max(tmp, dp[k-1][i-1] - prices[i]);
                dp[k][i] = max(dp[k][i-1], prices[i] + tmp);
            }
        }
        return dp[num][prices.size()-1];
    }
};
```



```c++

```





```c++
class Solution {
public:
    int maxProfit(int num, vector<int>& prices) {
        if(prices.size() == 0) return 0;
        if(num > prices.size()/2) return quickSolve(prices);
        vector<int> dp(num+1, 0);
        vector<int> tmp(num+1, -prices[0]);
        for(int i = 1; i < prices.size(); i++){
            for(int k = 1; k <= num; k++){
                tmp[k] = max(tmp[k], dp[k-1] - prices[i]);
                dp[k] = max(dp[k], prices[i] + tmp[k]);
            }
        }
        return dp[num];
    }
    
    int quickSolve(vector<int>& prices) {
        int len = prices.size(), profit = 0;
        for (int i = 1; i < len; i++)
            // as long as there is a price gap, we gain a profit.
            if (prices[i] > prices[i - 1]) profit += prices[i] - prices[i - 1];
        return profit;
    }
};
```

