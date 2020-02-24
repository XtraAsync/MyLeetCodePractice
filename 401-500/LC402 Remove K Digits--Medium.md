[Problem Link](https://leetcode.com/problems/remove-k-digits/)

## LC 402

Given a non-negative integer *num* represented as a string, remove *k* digits from the number so that the new number is the smallest possible.

**Note:**

- The length of *num* is less than 10002 and will be ≥ *k*.
- The given *num* does not contain any leading zero.



Example 1:

```
Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
```

Example 2:

```
Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
```

Example 3:

```
Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.
```

---

这道题让我们在删去k位数字之后，得到一个字符串使得这个字符串表示的数字最小

根据数字的特点， 越靠前的位权重越大，因此可以一个核心的点是让前面的数字尽量的小

所以有这样一个思路，我们从左向右的遍历这个字符串， 每遇到一个数字就先放到一个结果中， 当遇到的数字比结果中的最后一位数字小的时候，那当前数字明显比结果中已经有的数字更应该作为结果的头部。

在此时如果还有可以删去的次数---即 k!=0 的时候， 我们就可以删去结果中目前所有比当前数字大的数字，因为只要比当前的数字大 就不会比当前的数字更适合来做头部

这一部分的代码实现如下：

```
for(auto n: num){
    while(k && !res.empty() && res.back() > n){
        res.pop_back();
        k--;
    }
    res.push_back(n);
}
```

实际上这样的操作是单调栈的一个应用， 我们在还有k的情形下尽可能为维护一个递增栈

在这道题中直接用字符串代替栈即可

然后就是一些corner case：

1. 对于10345 这类的数字，在遇到零的时候会弹出res中的1， 装入0， 但是0开头的数字显然不是一个合法的数字, 因此我们在装入数字的时候可以做一个判断，在装入0的时候要判断是不是第一位， 如果是则不装入

   ```
   if(res.size() || n != '0'){
   	res.push_back(n);
   }
   ```

2. 同时，如果这个字符串是个比较良好的递增字符串， 那我们一直没有机会删去数字，那最后只需要把最后的k位删掉即可：

   ```
   while(k-- > 0 && res.size()){
   	res.pop_back();
   }
   ```

3. 也存在整个字符串都被删掉的情况， 或者是字符串删完之后只剩下个0， 但是因为他是res中的第一位所以我们没有装入的情况， 所以在结尾判断一下res是否是空的， 如果是空的返回个0

   ```
   return res.empty() ? "0": res;
   ```



那们整个流程下来的代码如下：

```
class Solution {
public:
    string removeKdigits(string num, int k) {
        string res;
        for(auto n: num){
            while(k && !res.empty() && res.back() > n){
                res.pop_back();
                k--;
            }
            if(res.size() || n != '0'){
                res.push_back(n);
            }
        }
        while(k-- > 0 && res.size()){
            res.pop_back();
        }
        return res.empty() ? "0": res;
    }
};
```



