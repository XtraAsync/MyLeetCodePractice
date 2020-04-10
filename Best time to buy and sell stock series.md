这个系列最难的是三四题， 其实本质是一样的， 第四题是第三题的推广， 前两题解法比较显而易见

直接看一下第四题的解法即可

```c++
dp[k, i] = max(dp[k, i-1], prices[i] - prices[j] + dp[k-1, j-1]), j=[0..i-1]
```

最基本形式的解法如下

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

我们发现，每一次新的dp\[k][i] 只和 dp\[k][i-1] 以及 dp\[k-1][i] 有关， 即在dp表中只与上面的值和左面的值有关，所以我们可以通过这种方式 省去一个维度的空间，一般来说对于本题的场景：price明显还是比k长的， 因此我们希望是向下遍历的， 所以需要交换一下两个for循环的顺序

由于本题目的时间限制卡的比较严格， 因此需要在额外给一个corner case的快速优化过程，防止TLE

这里面我们主要考虑 有大量的允许的transcation 的情况， 那这里我们只需要把这道题退化到

best time to buy and sell... II 的情形

![](https://github.com/crVainglory/MyLeetCodePractice/blob/master/images/best%20time%20to%20buy%20and%20sell%20stock.jpg)

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

