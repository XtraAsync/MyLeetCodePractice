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

另一种就是常见的快速排序， 写法很多， 这里就只写我习惯的一种排法

其中的helper函数也就是kth element中会用到的partition函数

快排之中会有一些细节的地方需要注意

首先是整体的算法：

```c++
1. [pivot, left, ..............................., right];
2. [lstart, ......., lend, pivot, rstart, ......., rend];
3. quicksort(lstart, lend)|pivot| quicksort(rstart,rend);      
```

然后细节上是边界条件：

标在代码的注释之中了，注意通过直接在while里做加减的方式， 保证了不会死循环

```c++
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        helper(nums, 0, nums.size()-1);
        return nums;
    }
    // left, right 为数组的左右边界
    void helper(vector<int>& nums, int left, int right){
        if(left >= right) return;
        // 这样设置pivot可以保证一定会进入循环
        // 才可以保证r一定是移动到了>=pivot的位置上
        // 防止出现 2，3 这样只有两个元素的情形，没进入循环导致交换变为 3，2
        int pivot = nums[left], l = left, r = right + 1;
        while(l < r){
            while(l < right && nums[++l] <= pivot);
            while(r > left && nums[--r] >= pivot);
            if(l < r) swap(nums[l], nums[r]);
        }
        swap(nums[left], nums[r]);
        helper(nums, left, r-1);
        helper(nums, r+1, right);
    }
};
```

可能一些人常用的左开右闭写法

```c++
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        helper(nums, 0, nums.size());
        return nums;
    }
    void helper(vector<int>& nums, int left, int right){
        if(left >= right-1) return;
        int pivot = nums[left], l = left, r = right;
        while(l < r){
            while(l < right-1 && nums[++l] <= pivot);
            while(r > left && nums[--r] >= pivot);
            if(l < r) swap(nums[l], nums[r]);
        }
        swap(nums[left], nums[r]);
        helper(nums, left, r);
        helper(nums, r+1, right);
    }
};
```





