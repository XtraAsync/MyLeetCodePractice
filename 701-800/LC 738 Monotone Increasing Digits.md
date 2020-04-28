#### LC 738 Monotone Increasing Digits

观察规律：

2200 -  1999

1234 - 1234

1200 - 1199

不难发现，如果原数字保持递增 >=， 直接返回原数字即可

否则 把最后一次> 位置的数字减一， 后面的数字都变成9 即可

1200：1 < 2, 2 > 0, 2--, 后面全换为9

2200： 2 <= 2， 第一个2--， 后面全换为9

```c++
class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        vector<int> arr;
        while(N>0){
            arr.push_back(N%10);
            N/=10;
        }
        int last = arr.size()-1, res = 0;
        for(int i = arr.size()-2; i>=0 && arr[i] >= arr[i+1]; i--){
            if(arr[i]> arr[i+1]){
                last = i;
            }
        }
        if(last != 0){
            arr[last]--;
            for(int i = 0; i <= last - 1; i++)
                arr[i] = 9;
        }
        for(int i = 0, carry = 1; i < arr.size(); i++){
            res += arr[i]*carry;
            carry*=10;
        }
        return res;
    }
};
```



调整一下遍历的顺序， 可以把数字减一的操作放入循环内：

```c++
class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        vector<int> arr;
        while(N>0){
            arr.push_back(N%10);
            N/=10;
        }
        int last = -1, res = 0;
        for(int i = 0; i < arr.size()-1; i++){
            if(arr[i] < arr[i+1]){
                last = i;
                arr[i+1]--;
            }
        }
        for(int i = 0; i <= last; i++)
            arr[i] = 9;
        for(int i = 0, carry = 1; i < arr.size(); i++){
            res += arr[i]*carry;
            carry*=10;
        }
        return res;
    }
};
```



实际上我们可以省去这个arr数组， 直接用字符串去处理，代码显得更简洁一些：

思路基本一致，代码如下

```c++
class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        string n_str = to_string(N);
        
        int marker = n_str.size();
        for(int i = n_str.size()-1; i > 0; i --) {
            if(n_str[i] < n_str[i-1]) {
                marker = i;
                n_str[i-1] = n_str[i-1]-1;
            }
        }
        
        for(int i = marker; i < n_str.size(); i ++) n_str[i] = '9';
        
        return stoi(n_str);
    }
};
```

