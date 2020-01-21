## C语言函数
> 说明：参考《Linux C 一站式编程》、菜鸟教程、等

### 1、简单函数
 >我们在完成一个C语言程序的时候，会使用到数学函数 < math.h >, 也会用到自定义函数：main 等函数
 
1、同一个函数可以被多次调用。     
2、可以用一个函数调用另一个函数，后者再去调第三个函数。    
3、通过自定义函数可以给一组复杂的操作起一个简单的名字，例如threeline。对于main函数来说，只需要通过threeline这个简单的名字来调用就行了，不必知道打印三个空行具体怎么做，所有的复杂操作都被隐藏在threeline这个名字后面。    
4. 使用自定义函数可以使代码更简洁，main函数在任何地方想打印三个空行只需调用一个简 单的threeline()，而不必每次都写三个printf("\n")。


- 函数的运行过程 、return

```c
#include <stdio.h>

void a()
{
}

void test()
{
    printf("testS\n");
    return a();
    printf("testE\n");
}

int main(int argc, char *argv[]) {
    printf("mainS\n");
    test();
    printf("mainE\n");
    return 0;
}

```
运算结果：
>mainS    
testS    
mainE    

### 2、隐式声明
- 自定义一个函数记得写函数声明


```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("mainS\n");
    test();
    printf("mainE\n");
    return 0;
}

int test()
{
    return 1;
}
```
编译时会报警告      

但仍然能编译通过。这里涉及到的规则称为函数的隐式声明(Implicit Declaration)，在main函数中调用test时并没有声明它，编译器认为此处隐式声明了int test(void);    

隐式声明的函数返回值类型都是int，由于我们调用这个函数时没有传任何参数，所以编译器认为这个隐式声明的参数类型是void，这样函数的参数和返回值类型都确定下来了，编译器根据这些信息为函数调用生成相应的指令。   
然后编译器接着往下看,看到先前的隐式声明的返回值类型不符，所以报警告。


### 3、传值、传指针
略
#### 3.1 传参数

```c
#include <stdio.h>

int test(int a, int b)
{
    return a + b;
}

int main(int argc, char *argv[]) {
    int i = 2;
    int j = 3;

    int tem = test(i, j);
    
    printf("tem = %d\n", tem);//5
    return 0;
}

```
在调用函数test的时候，传的参数相当于    
>int a = 2；    
int b = 3；

int变量i， j作右值，相当于把i， j里面的内存替换



### 4、作用域

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    
    int i = 4;
    {
        printf("i = %d\n", i);
        int i = 5;
        printf("i = %d\n", i);
    }
    printf("i = %d\n", i);
    return 0;
}

```
运行结果：
> i = 4   
i = 5    
i = 4   

### 5、回调函数