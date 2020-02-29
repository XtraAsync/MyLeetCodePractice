### Array Sort

最近在写数据库的外部排序， 所以最先想到的是merge sort，在这里面温习一下常用的排序算法：

#### Merge Sort

具体的算法流程：

```c++
// 对于这一步来说， 它是等价于 (left + right)/2的
// 之所以选择这样， 是为了防止过大的left和right导致的整形溢出
1. int mid = left + (right - left)/2;
2. mergeSort(left, mid);
3. mergeSort(mid+1, right);
// 递归的分割成两个有序的小数组 [left, mid], [mid+1, right]之后
// 再按照merge sorted list 的思路去合并就好了
4. merge(left, right, mid);
```

首先写的这种merge sort的空间复杂度是 o(n) 的， 之后再实现一种in place的

```c++
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        mergeSort(nums, 0, nums.size()-1);
        return nums;
    }
    void mergeSort(vector<int>& nums, int l, int r){
        if(l >= r) return;
        int m = l + (r-l)/2;
        mergeSort(nums, l, m);
        mergeSort(nums, m+1, r);
        merge(nums, l, r, m);
    }
    void merge(vector<int>& nums, int left, int right, int mid){
        vector<int> res(right - left + 1);
        int index = 0, l = left, r = mid+1;
        while(l <= mid && r <= right){
            if(nums[l] <= nums[r]){
                res[index++] = nums[l++];
            }else{
                res[index++] = nums[r++];
            }
        }
        while(l <= mid) res[index++] = nums[l++];
        while(r <= right) res[index++] = nums[r++];
        // 注意不能直接 nums = res， 否则会影响其他的排序过程
        for(int i = left, index = 0; i <= right; i++, index++){
            nums[i] = res[index];
        }
    } 
};
```





