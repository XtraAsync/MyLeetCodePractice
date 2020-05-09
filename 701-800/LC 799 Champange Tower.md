

一道掌握代码逻辑就比较清晰的题：

我们可以在下一层计算上一层杯子的状态

```c++
res[j] = max(0.0, (res[j] - 1)/2);
res[j+1] += res[j]
```

第一句使用max的原因是，上一层的杯子内的水有可能不足够流出来，那么要防止加上一个负数

上一层的杯子一般流给了res[j], 一半流给了res[j+1]

所以res[j+1] 增加的一样多，只需要在下一层算上一层流出的量就可以

```c++
class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        vector<double> res(102);
        res[0] = poured;
        for(int i = 1; i <= query_row; i++){
            for(int j = i; j >=0; j--){
                res[j+1] += res[j] = max(0.0, (res[j] - 1)/2);
            }
        }
        return min(1.0, res[query_glass]);
    }
};
```

