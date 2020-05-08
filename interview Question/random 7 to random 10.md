使用random 7 生成 random 10



给定API random7() 返回 1,2,3,4,5,6,7

经过加减乘除这类的运算至少应该是扩充到比10大的数据范围，才能进行取模运算

那么应该想到7*(random7()-1)+random7() 可以扩充到1-49而且是等概率的

比49小的最大的能被10整除的是40，那么大于40的就舍弃



```c++
int random7(){
    return rand()%7+1;
}

int random10(){
    int x=49;
    while(x>40){
      	// 1-49
        x = 7 * (random7()-1)+random7();
    }
    return x%10+1;
}
```



```c++
x = random7()*(random7()-1)+random7();
// 实际上就是生成一个七进制的二位的数 只不过形式上转换为了十进制数
```





类似的思路也可以生成 random 9

45是9的倍数 所以大于45舍去即可

```c++
int random9(){
    int x= 49;
    while(x>45){
        x=random7()*(random7()-1)+random7();
    }
    return x%9+1;
}
```

