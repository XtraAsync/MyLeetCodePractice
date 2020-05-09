#### LC 821 Shortest Distance to a Character

简单的2pass思路：

```c++
class Solution {
public:
    vector<int> shortestToChar(string S, char C) {
        int len = S.size(), last = -len;
        vector<int> res(S.size(), len);
        for(int i = 0; i < S.size(); i++){
            if(S[i] == C) last = i;
            res[i] = min(res[i], i - last);
        }
        last = 2*len;
        for(int i = S.size()-1; i>=0; i--){
            if(S[i] == C) last = i;
            res[i] = min(res[i], last - i);
        }
        return res;
    }
};
```

可以进一步的优化，因为第一次向右遍历之后的最后一个C后面的距离实际上已经确定好了， 所以第二次只需要直接从那个C往前遍历就好了

```c++
class Solution {
public:
    vector<int> shortestToChar(string S, char C) {
        int len = S.size(), last = -len;
        vector<int> res(S.size(), len);
        for(int i = 0; i < S.size(); i++){
            if(S[i] == C) last = i;
            res[i] = min(res[i], i - last);
        }
        for(int i = last-1; i>=0; i--){
            if(S[i] == C) last = i;
            res[i] = min(res[i], last - i);
        }
        return res;
    }
};
```

