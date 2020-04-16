Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

**Example 1:**

```
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
```

**Example 2:**

```
Input: [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
```

**Note:** The length of the given binary array will not exceed 50,000.



这道题找 1 和 0 出现次数相同的最大子数组， 那其实可以这么考虑

我们认为1 是1， 0 是-1， 那出现次数相同的子数组序列和一定是0

开个unordered_Map 保存一下历史 的sum

如果出现了sum相同的情况， 那当前这一大段的序列和一定为0

```c++
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int sum = 0, res = 0;
        unordered_map<int, int> umap;
        for(int i = 0; i < nums.size(); i++){
            sum += nums[i] == 1? 1: -1;
            if(sum == 0) res = i + 1;
            if(umap.count(sum)) res = max(res, i - umap[sum]);
            else umap[sum] = i;
        }
        return res;
    }
};
```

