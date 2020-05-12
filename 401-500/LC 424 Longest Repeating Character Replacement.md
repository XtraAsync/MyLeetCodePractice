#### LC 424 Longest Repeating Character Replacement

sliding window 的题目

理解一个核心的点之后，这道题就不复杂了

怎么判断当前字符串能不能在经过k个替换之后，变成字符全一样的字符串呢

只需要判断字符串的总长度减去字符串中出现频率最高的字符是否 <= k 即可

因为最节省替换次数的方法一定是保留字符串中频率出现最高的字符

这样我们就有了收缩左边界的条件，代码如下

```c++
class Solution {
public:
    int characterReplacement(string s, int k) {
        int maxLen = 0, maxCnt = 0, start = 0;
        vector<int> count(26, 0);
        char cur;
        for(int i = 0; i < s.size(); i++){
            maxCnt = max(maxCnt, ++count[s[i] - 'A']);
            while(i - start - maxCnt + 1 > k){
                --count[s[start++] - 'A'];
                maxCnt = *max_element(count.begin(), count.end());
            }
            maxLen = max(maxLen, i - start + 1);
        }
        return maxLen;
    }
};
```



论坛上的一种解法：比较难懂 理一下思路：

还是O(n) 只是省去了遍历26数组的过程

这里面res，记录的是最长的长度

这里的res没有用max去维护， 是因为要么当前的这次循环能让窗口变大， 要么非法我们只平移窗口，所以要么变大要么不变

它的思路是这样的

我们可以把 i 看做当前sliding window的end，循环每进行一次， end右移一次

把每次end的右移当作一次试探，如果可以扩大后满足替换次数小于k， 那窗口理所当然的变大一格

如果不能，那么对应的我们不改变窗口的大小，只是向右平移一格即可，所以在else分支里面 res不变， 只需要更新由于左边界的平移导致的 -- 当前字符串频率最高的字符的出现次数

如果只是不断的扩大的窗口，那么下一次进入循环的maxf一定是当前最大频数

另外一种情况是平移窗口时，我们只修改了count却没更新maxf

因为这个更新是使得一个字符的count--， 再进入下次迭代之后只有两种情况

1. 新加入的这个元素会成为新窗口中的主流元素，maxf的值被修改为当前字符串中最大频率，这就是这行代码做的事情

   ```c++
   maxf = max(maxf, ++count[s[i]]);
   ```

2. 新加入的这个元素不会成为新窗口的主流元素，那么上面这行代码不会改变maxf的值，

   因为新的元素不是主流元素，所以新加入的这个元素是要被替换掉的，而我们已经是在平移窗口了，换句话说，一定是当前字符串的主流元素的个数已经不能满足替换次数了，那我们可以一直维持这个虚高的maxf, 因为这个虚高的maxf一直维持着使 res - maxf < k 的状态， 所以窗口一直不会扩张，可以导致窗口扩张的只有两种情形：

   我们拿 k = 1 时的AAABB举例：走到最后一个b的时候 窗口大小为4， 窗口里有两个A，两个B， maxf依然是3

   1. 新加入的元素成为了主流元素，出现了AAABBBB， 这个时候窗口的大小应该可以增加到5，但此时B的元素个数为4， 超过了原先虚高的为3的maxf， maxf已经被正确的更新为4， res-maxf = 0，更新
   2. 原先的主流元素又逐渐多了回来 AAABBAAAA， A的新个数也超过了maxf， 也可以正确的更新

   换言之， **如果窗口可以扩张，那一定是某个元素的个数重新变到足够大**， 大到res-个数 重新 < k。

   此时一定会出发maxf的更新，也就可以正确的扩张， 因为此时maxf已经等于实际的最大频数了



```c++
int characterReplacement(string s, int k) {
    int res = 0, maxf = 0;
    unordered_map<int, int> count;
    for (int i = 0; i < s.length(); ++i) {
      	maxf = max(maxf, ++count[s[i]]);
        if (res - maxf < k)
          	res++;
        else
          	count[s[i - res]]--;
    }
    return res;
}
```

