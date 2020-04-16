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



