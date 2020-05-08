第一种贴近直觉的解决方案：

For each soldier, count how many soldiers on the left and right have `less` and `greater` ratings.

This soldier can form `less[left] * greater[right] + greater[left] * less[right]` teams.

```C++
class Solution {
public:
    int numTeams(vector<int>& rating) {
        int len = rating.size(), res = 0;
        for(int i = 0; i < len; i++){
            int lless = 0, lgreater = 0, rless = 0, rgreater = 0;
            for(int j = 0; j < i; j++){
                rating[i] > rating[j]?lless++:lgreater++;
            }
            for(int j = len-1; j>i; j--){
                rating[i] < rating[j]?rgreater++:rless++;
            }
            res+= lless*rgreater+lgreater*rless;
        }
        return res;
    }
};
```



第二种空间换时间，利用BST打到nlogn的时间复杂度

这段代码看起来比较复杂，实际上主要做的是，把计数这个操作变成 logn， 实际上利用的是BST的有序性

为了方便的完成计数这个操作， 需要加入一个cnt_left 变量

```c++
class Solution {
public:
    struct bnode{
        bnode *left, *right;
        int val, cnt_left;
        bnode():left(nullptr), right(nullptr), cnt_left(0), val(0){};
        bnode(int v): left(nullptr), right(nullptr), cnt_left(0){ val = v; };
    };

    int count(bnode* root, int v){
        if(!root) return 0;
        if(root->val > v) return count(root->left, v);
        else return 1 + root->cnt_left + count(root->right, v);
    }
    
    bnode* insert(bnode* root, int v){
        if(!root) return new bnode(v);
        if(root->val > v){
            root->cnt_left++;
            root->left = insert(root->left, v);
        }
        else
            root->right = insert(root->right, v);
        return root;
    }
    bnode* remove(bnode* root, int v){
        if(!root) return nullptr;
        if(root->val < v)
            root->right = remove(root->right, v);
        else if(root->val == v){
            bnode* right_most = root->left;
            if(!right_most) return root->right;
            while(right_most->right){
                right_most = right_most->right;
            }
            right_most->right = root->right;
            return root->left;
        }else{
            root->cnt_left--;
            root->left = remove(root->left, v);
        }
        return root;
    }
    int numTeams(vector<int>& rating) {
        int len = rating.size(), res = 0;
        auto left = new bnode(rating.front()), right = new bnode(rating.back());
        for(int i = 1; i < len - 1; i++){
            insert(right, rating[i]);
        }
        for(int i = 1; i < len - 1; i++){
            remove(right, rating[i]);
            int l_sm = count(left, rating[i]), l_gr = i - l_sm;
            int r_sm = count(right, rating[i]), r_gr = len - i - 1 - r_sm;
            res += l_gr * r_sm + r_gr * l_sm;
            insert(left, rating[i]);
        }
        return res;
    }
};
```

