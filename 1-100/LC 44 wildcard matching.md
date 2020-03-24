### LC 44 wildcard matching

lc上一道难度为hard的题目

其实对于 ？的处理方式还是很简单的，主要的难点在于 \*，因为 \* 可以匹配任意长度的字符串，甚至包括空字符串， 这就要求我们要能记录 \* 的位置

举个例子：

s:  ababab

p: *bab

在这个例子之中， p的星号可以匹配s中的 a 或者 aba

但是当 \* 匹配了 s 中的 a 的时候，循环发现直到连续匹配完后三位的 bab 之后，才发现失配了，此时要回到p和s最开始 \* 的位置上重新匹配， **因此要记录 \* 的位置**

我们用istar表示 上一个p中的 \* 所读到的字符串的位置， 在例子中是a的位置，这样在之后的遍历中发现失配的时候可以直接跳回这个位置

jstar 表示p中的 \* 的位置

所以写出来循环的代码如下：

```c++
class Solution {
public:
    bool isMatch(string s, string p) {
       int i = 0, j = 0, iStar = -1, jStar = -1, m = s.size(), n = p.size();
        while (i < m) {
            // 当遇到两者字符串相等的时候 同时前进
            if (j < n && (s[i] == p[j] || p[j] == '?')) {
                ++i; ++j;
            }
            // 当遇到p有*的时候，记录此时双方index的位置
            else if(j < n && p[j] == '*'){
                jStar = j++;
                iStar = i;
            }
            // 进入到这种情况的时候，表示当前s[i] 仍然和 p[j]不匹配， 而且p中是存在过*的 因此可以把s中的一整段全按照p中的*的匹配段落来处理
            // 在例子中就是， s中匹配到abab的时候，发现后面仍有ab, 失配 因此把aba 全用来匹配 *
            // 此时 j也需要回到上一个*的下一位处
            else if(iStar >= 0){
                j = jStar + 1;
                i = ++iStar;
            }
            else return false;
        }
        while(j < n && p[j] == '*') ++j;
        return j == n;
    }
};
```

