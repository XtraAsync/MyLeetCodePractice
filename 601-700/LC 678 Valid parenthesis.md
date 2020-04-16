Given a string containing only three types of characters: '(', ')' and '*', write a function to check whether this string is valid. We define the validity of a string by these rules:

1. Any left parenthesis `'('` must have a corresponding right parenthesis `')'`.
2. Any right parenthesis `')'` must have a corresponding left parenthesis `'('`.
3. Left parenthesis `'('` must go before the corresponding right parenthesis `')'`.
4. `'*'` could be treated as a single right parenthesis `')'` or a single left parenthesis `'('` or an empty string.
5. An empty string is also valid.



**Example 1:**

```
Input: "()"
Output: True
```

**Example 2:**

```
Input: "(*)"
Output: True
```

**Example 3:**

```
Input: "(*))"
Output: True
```

**Note:**

1. The string size will be in the range [1, 100].



#### Notes

---

在做这道题之前， 要解决一下这道题新引入的难处理的那个点

在之前的那个valid parenthesis中， 只有左右括号 很简单， 维护一个cnt就可以

这道题引入*之后， 一些单向遍历的解法往往能处理大部分的情况， 除了这种

*(

所以一种不直观的解法， 是记录一下*号的位置， 遍历的时候把\* 当作自由人处理， 需要用到的时候扣一个。 然后在结束的时候，比对星号和左括号的位置，保证星号是在左括号的右边， 能够满足消掉所有的左括号即可。

下面说的这种思路，也是通过了反向遍历这一过程， 消除了这种corner case问题

---

首先最直接的思路：

维护cnt， 左括号+ 右括号-， 先把所有的*当作左括号， 从左到右遍历一遍， 如果中间cnt < 0 的话 return false， 因为这代表着即使所有的\*都当作左括号的情形下， 仍然不能匹配右括号的数量

如果 cnt 在结束的时候大于 0， 需要进一步判断， 因为有可能有的* 不应该是左括号的

然后反向走一遍： 把所有的*当作右括号， 中间 cnt 小于0 直接 return false， 结束了直接return true。

小于零return false的原因和上面一样， 结束的时候有两种情况， 等于0不用说肯定对

大于零的时候：

因为之前正向遍历的时候，我们的左括号多了，

左括号多有两种情况：是星号变的，或是本身就多的左括号。

本身就多的左括号这种情况会在反向遍历时被检测出来。 因此如果能够走到结束，说明多余的左括号一定是星号变的。

而这些星号在反向遍历时又变做了右括号，最终导致了右括号有剩余，所以当这些星号都当作空的时候，左右括号都是对应的，即是合法的。

右括号是不会多的，多的右括号过不了第一遍的正向遍历

```c++
class Solution {
public:
    bool checkValidString(string s) {
        int cnt = 0;
        for(auto c: s){
            if(c == '(' || c == '*') cnt++;
            else cnt--;
            if(cnt < 0) return false;
        }
        if(cnt == 0) return true;
        cnt = 0;
        for(int i = s.size()-1; i>=0; i--){
            if(s[i] == ')' || s[i] == '*') cnt++;
            else cnt--;
            if(cnt < 0) return false;
        }
        return true;
    }
};
```

---

第二种思路是论坛上的高票解法：

因为我觉得说的蛮清晰的， 还是直接搬原文了

大体的思想是， 每遇到一个*， 维护所有的可能，

星号如果代表左括号， 则需要匹配的右括号数量要加一

如果代表右括号， 那么需要匹配的右括号数量就减一，

如果是empty， 那cnt不变， 所以你发现这是一个连续的期间， 所以只需要维护这个区间的最大值和最小值即可

The idea is to similar to validate a string only contains '(' and ')'. But extend it to tracking the lower and upper bound of valid '(' counts. My thinking process is as following.



scan from left to right, and record counts of unpaired ‘(’ for all possible cases. For ‘(’ and ‘)’, it is straightforward, just increment and decrement all counts, respectively.
When the character is '*', there are three cases, ‘(’, empty, or ‘)’, we can think those three cases as three branches in the ongoing route.
Take “(**())” as an example. There are 6 chars:
----At step 0: only one count = 1.
----At step 1: the route will be diverted into three branches.
so there are three counts: 1 - 1, 1, 1 + 1 which is 0, 1, 2, for ‘)’, empty and ‘(’ respectively.
----At step 2 each route is diverged into three routes again. so there will be 9 possible routes now.
-- For count = 0, it will be diverted into 0 – 1, 0, 0 + 1, which is -1, 0, 1, but when the count is -1, that means there are more ‘)’s than ‘(’s, and we need to stop early at that route, since it is invalid. we end with 0, 1.
-- For count = 1, it will be diverted into 1 – 1, 1, 1 + 1, which is 0, 1, 2
-- For count = 2, it will be diverted into 2 – 1, 2, 2 + 1, which is 1, 2, 3
To summarize step 2, we end up with counts of 0,1,2,3
----At step 3, increment all counts --> 1,2,3,4
----At step 4, decrement all counts --> 0,1,2,3
----At step 5, decrement all counts --> -1, 0,1,2, the route with count -1 is invalid, so stop early at that route. Now we have 0,1,2.
In the very end, we find that there is a route that can reach count == 0. Which means all ‘(’ and ‘)’ are cancelled. So, the original String is valid.

Another finding is counts of unpaired ‘(’ for all valid routes are consecutive integers. So we only need to keep a lower and upper bound of that consecutive integers to save space.
One case doesn’t show up in the example is: if the upper bound is negative, that means all routes have more ‘)’ than ‘(’ --> all routes are invalid --> stop and return false.

```java
public boolean checkValidString(String s) {
    int low = 0, high = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s.charAt(i) == '(') {
            low++;
            high++;
        } else if (s.charAt(i) == ')') {
            if (low > 0) low--;
            high--;
        } else {
            if (low > 0) low--;
            high++;
        }
        if (high < 0) return false;
    }
    return low == 0;
}
```



