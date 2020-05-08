### LC 1104 Path In Zigzag Labelled Binary Tree:

---

对于每一层的树节点，存在着这样的关系：

当层节点的值的范围： cnt[i] ~ cnt[i+1]-1

由于相邻的两层之间是revert的

下面任意一种关系都是成立的

根据这两种关系式的任意一种，把答案写出来即可:

```c++
label = cnt[i]-1 - (label - cnt[i])/2;
label = (cnt[i+1] - 1 - label)/2 + cnt[i-1];
```

ps: 其中的 cnt[i]-1 是上层的最大值， cnt[i]是当前层的起始值

​					cnt[i+1] -1是当前层的最大值， cnt[i-1]是上一层的起始值

```c++
class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        vector<int> cnt{1};
        int cur = 1;
        while(cur <= label){
            cur *= 2;
            cnt.push_back(cur);
        }
        int level = cnt.size() - 1;
        vector<int> res(level);
        for(int i = level - 1; i >= 1; i --){
            res[i] = label;
            label = (cnt[i+1] - 1 - label)/2 + cnt[i-1];
        }
        res[0] = 1;
        return res;
    }
};
```



```c++
class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        vector<int> cnt{1};
        int cur = 1;
        while(cur <= label){
            cur *= 2;
            cnt.push_back(cur);
        }
        vector<int> res(cnt.size() - 1);
        for(int i = res.size() - 1; i >= 0; i --){
            res[i] = label;
            label = cnt[i]-1 - (label - cnt[i])/2;
        }
        return res;
    }
};
```

