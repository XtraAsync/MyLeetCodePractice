

## LC 253

这道题有很多种变： LC 732 那道hard的日历， 实际上就是这道题换了一个样子， 与此同时字节跳动的一道面试题： 给出多个线程的开始时间和结束时间，求最大并发数，这些题目核心的思路都是这道Meeting rooms II

这道题有两种解决思路：

这一部分的代码实现如下：

经典的双排序做法：

一个核心的理解思路是： 当我们遇到 end > start 的时候，就代表着遇到了当前房间不够用的情况， end < start 的时候， 可以释放一个房间供下个任务使用

```c++
int calc(vector<pair<int, int>> tasks){
    vector<int> start, end;
    int res = 0;
    for(auto item: tasks){
        start.push_back(item.first);
        end.push_back(item.second);
    }
    sort(start.begin(), start.end());
    sort(end.begin(), end.end());
    int endPos = 0;
    for(int i = 0; i < tasks.size(); i++){
        if(start[i] < end[endPos]){
            res++;
        }else endPos++;
    }
    return res;
}
```

第二种思路是一种比较容易理解的思路， 使用一个map( 这里要用有序的map， 方便直接按照时间顺序排列 ) 来记录任务的起始时间和结束时间。 那对于每一个在map中的时间点， 遇到一个任务结束， 我们减去一个房间（这样被减掉的房间可以用于以后遇到新的房间时的增加），遇到一个任务开始， 我们增加一个房间， 记录整个遍历过程中出现的最大房间数， 就是答案。

```c++
int minMeetingRooms(vector<vector<int>>& tasks) {
        map<int, int> m;
        int res = 0, sum = 0;
        for(auto t: tasks){
            m[t[0]]++;
            m[t[1]]--;
        }
        for(auto it: m){
            sum+=it.second;
            res = max(res, sum);
        }
        return res;
    }
```



