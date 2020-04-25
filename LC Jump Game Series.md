#### LC Jump Game Series

---

**LC 55 & 45**

动态规划系列：

LC 55 比较简单：

第一种可以用动态规划的思路：

dp[i]表示当前位置剩下的**跳跃能力**

那么上一个格子时拥有的跳跃能力， 花费掉到这个格子需要的1费，就是当前格子的跳跃能力了

在上一个格子选择经过接着走： dp[i-1] -1

在上一个格子落地重新跳：nums[i-1] - 1

```c++
class Solution {
public:
    bool canJump(vector<int>& nums) {
        vector<int> dp(nums.size(), 0);
        for (int i = 1; i < nums.size(); ++i) {
            dp[i] = max(dp[i - 1], nums[i - 1]) - 1;
            if (dp[i] < 0) return false;
        }
        return true;
    }
};
```

这道题里 它的贪心算法也很好理解：

其实它的贪心算法也可以理解，因为如果中途有其他的格子能让你跳的更远， 就停下来获得更远的能力一定是没有错的。 因为你停下来获得的新跳跃能力，一定是比你之前能够跳的更远的

```c++
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int reach = 0, len = nums.size();
        for(int i = 0; i < len; i++){
            if(reach < i || reach >= len-1) break;
            reach = max(reach, i + nums[i]);
        }
        return reach >= len - 1;
    }
};
```



---

jump game 2 如果使用dp的话需要额外的剪枝， 否则过不了case

memo[i] 到达当前点所需要的最少的步数

lastMax表示，以前的点能到达最远的地方

因为每次从当前位置起跳，起跳这一过程本身需要额外的步数， 所以如果这次能到的地方之前已经能到了，从这里走需要的步数一定不可能比之前少。

所以只需要更新能新reach的范围即可

他跳能到我跳也能到，step相同。

从之前的点



```c++
class Solution{
public:
    int jump(vector<int>& nums){
        int len = nums.size();
        if(len == 0) return 0;
        vector<int> memo(len);
        int lastMax = 0;
        for(int i=0; i < len-1; i++){
            int steps = memo[i]+1;
            int curMax = i + nums[i];
            // this jump can already reach the end
            if(curMax >= len-1) return steps;
            // this further jump's result is no better than no jump
            if(lastMax >= curMax) continue;
            // the new points can all reach by this cur jump
            for(int k = curMax; k > lastMax; k--)
                memo[k] = steps;
            lastMax = curMax;
        }
        return 0;
    }
};
```

