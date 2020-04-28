#### LC 1415 The k-th Lexicographical String of All Happy Strings of Length n

Math:

一个简单的观测：

| last_char | seq  | cur_char |
| --------- | :--- | -------- |
| **a**     | 1    | b        |
|           | 2    | c        |
| **b**     | 1    | a        |
|           | 2    | c        |
| **c**     | 1    | a        |
|           | 2    | b        |

seq 指的是组别：指的是它属于下分组的第一个大组还是第二个大组

我们拿 n = 3的时候举例：

```
Input: n = 3, k = 9
Output: "cab"
Explanation: There are 12 different happy string of length 3 ["aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb", "cab", "cac", "cba", "cbc"]. You will find the 9th string = "cab"
```

对于 a, b, c

```c++
#1 "aba", "abc", 
#2 "aca", "acb", 
#1 "bab", "bac", 
#2 "bca", "bcb", 
#1 "cab", "cac", 
#2 "cba", "cbc"
```

对于ab这一组

```
#1 "aba"
#2 "abc"
```

所以如果算出了 属于哪个大组， 再根据last_char 就能得出 当前是哪个字符

如果用cur表示当前属于哪个组

```c++
res += cur == 1 ? 'a' + (res.back() == 'a'): 'b' + (res.back() != 'c');
```

除此之外，不难发现

如果有n位数，就有3 * 2^n 个组合

也就是每一组有 2^n 个组合， 也就可以通过除法分出具体是哪个组



```c++
class Solution {
public:
    string getHappyString(int n, int k) {
        auto prem = 1 << (n - 1);
        if (k > 3 * prem)
            return "";
        int cur = (k-1)/prem;
        string res = string(1, 'a' + cur);
        for(int i = n; i >= 2; i--){
            k -= prem*cur;
            prem >>= 1;
            cur = (k-1)/prem;
            res += cur == 0 ? 'a' + (res.back() == 'a'): 'b' + (res.back() != 'c');
        }
        return res;
    }
};
```

---



Dfs:

标准的dfs的版子，这个是不用res记录结果的

```c++
class Solution {
public:
    string getHappyString(int n, int k) {
        if(k > 3*pow(2, n-1)) return "";
        string cur, res;
        dfs(cur, k, n, res);
        return res;
    }
    void dfs(string &cur, int &k, int n, string &res){
        if(res.size()|| cur.size() == n){
            if(--k == 0) res = cur;
            return;
        }
        for(int i = 0; i < 3; i++){
            auto ch = 'a' + i;
            if(!cur.empty() && ch == cur.back()) continue;
            cur.push_back(ch);
            dfs(cur, k, n, res);
            cur.pop_back();
        }
    }
};
```

用res记录结果，最基础的写法：

```c++
class Solution {
public:
    string getHappyString(int n, int k) {
        if(k > 3*pow(2, n-1)) return "";
        string cur = "";
        vector<char> chars{'a', 'b', 'c'};
        dfs(cur, chars, n, k);
        return res.back();
    }

    void dfs(string& cur, vector<char>& chars, int n, int k) {
        if(res.size() == k)
            return;
        if(cur.size() == n) {
            res.push_back(cur);
            return;
        }
        
        for(int i = 0; i < 3; ++i) {
            if(cur.empty() || (cur.back() != chars[i])) {
                cur.push_back(chars[i]);
                dfs(cur, chars, n, k);
                cur.pop_back();
            }
        }
    }
    
private:
    vector<string> res;
};
```

