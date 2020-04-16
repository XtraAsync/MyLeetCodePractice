# 如何高效寻找素数

素数的定义看起来很简单，如果一个数如果只能被 1 和它本身整除，那么这个数就是素数。

常规写法

```
int countPrimes(int n) {
    int count = 0;
    for (int i = 2; i < n; i++)
        if (isPrim(i)) count++;
    return count;
}

// 判断整数 n 是否是素数
boolean isPrime(int n) {
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            // 有其他整除因子
            return false;
    return true;
}
```

这样写的话时间复杂度 O(log(n))

### 高效实现 `countPrimes`

我们可以反着使用上面的思路， 先把所有素数的倍数都直接干掉

2 -> 2 × 2 = 4, 3 × 2 = 6, 4 × 2 = 8... 都不可能是素数了。

3 -> 3 × 2 = 6, 3 × 3 = 9, 3 × 4 = 12... 也都不可能是素数了。

为什么只干掉素数的倍数？

因为其他的倍数，在其他的素数里已经干掉了， 没必要重复计算， 代码如下：

```c++
int countPrimes(int n) {
    vector<bool> isPrim(n, true);
    for (int i = 2; i * i < n; i++) 
        if (isPrim[i]) 
            // i 的倍数不可能是素数了
            for (int j = 2 * i; j < n; j += i) 
                    isPrim[j] = false;
    int count = 0;
    for (int i = 2; i < n; i++)
        if (isPrim[i]) count++;
    
    return count;
}
```

内层的 for 循环的一个优化：

```
for (int j = 2 * i; j < n; j += i) 
    isPrim[j] = false;
```

这样可以把 `i` 的整数倍都标记为 `false`，但是仍然存在计算冗余。

比如 `n = 25`，`i = 4` 时算法会标记 4 × 2 = 8，4 × 3 = 12 等等数字，但是这两个数字已经被 `i = 2` 和 `i = 3` 的 2 × 4 和 3 × 4 标记了。

**也就是说 2  -  i-1 都已经被计算过了**

我们可以稍微优化一下，让 `j` 从 `i` 的平方开始遍历，而不是从 `2 * i` 开始：

```
for (int j = i * i; j < n; j += i) 
    isPrim[j] = false;
```

这样，素数计数的算法就高效实现了，其实这个算法有一个名字，叫做 Sieve of Eratosthenes。

最终代码：

```
int countPrimes(int n) {
    boolean[] isPrim = new boolean[n];
    Arrays.fill(isPrim, true);
    for (int i = 2; i * i < n; i++) 
        if (isPrim[i]) 
            for (int j = i * i; j < n; j += i) 
                isPrim[j] = false;
    
    int count = 0;
    for (int i = 2; i < n; i++)
        if (isPrim[i]) count++;
    
    return count;
}
```

**该算法的时间复杂度比较难算**，显然时间跟这两个嵌套的 for 循环有关，其操作数应该是：

n/2 + n/3 + n/5 + n/7 + ... = n × (1/2 + 1/3 + 1/5 + 1/7...)

括号中是素数的倒数。其最终结果是 O(N * loglogN)



我提炼了一下对于我的思路， 完整的原文见下方连接：

原作者 labuladong：

github ref： [https://github.com/labuladong/fucking-algorithm/blob/master/%E9%AB%98%E9%A2%91%E9%9D%A2%E8%AF%95%E7%B3%BB%E5%88%97/%E6%89%93%E5%8D%B0%E7%B4%A0%E6%95%B0.md]