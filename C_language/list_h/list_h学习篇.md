## list.h学习篇

<span  style="color: #ff3d00; ">参考资料:</span>
    
在我的linux系统的这个目录下有list.h文件
>/usr/src/linux-headers-5.0.0-23/include/linux
>
> - 网上有许多关于list的文章

### 一、说明

测试运行需要使用linux系统。

> 1、我测试使用的不是linux系统里面的list.h文件，是一个简写版；具体的功能、函数和宏定义功能是一样的，可以说明这个文件的主要功能；（简写可以不在）

> 2、list.h主要是双链表的处理和应用，也有助于理解指针和宏定义；

> 3、在我的学生管理系统中：系统初始化的时候，将学生信息从文件中读取，处理，保存到结构体，“student”结构体就是使用list.h中的接口、宏处理的。



### 二、demo

demo主要是对这两个宏和list.h头文件中的函数和使用。应用和处理需要用到双链表。。。


```c
#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

typedef struct stu {
    char   name[30];
    int    age;
    struct list_head  list;
}stu;

struct list_head  *test_head;

int main(int argc, char *argv[]) {
    stu *pos = NULL;
    stu *next = NULL;
    
	//双链表头申请内存空间
    test_head = calloc(0, sizeof(struct list_head));
    
	//初始化双链表头
    INIT_LIST_HEAD(test_head);
    
	//准备结构体数据
    stu zhao = {"zhao", 1};
    stu qian = {"qian", 2};
    stu sun = {"sun", 3};
    stu li = {"li", 4};
    stu bao = {"bao", 5};
    
	//将结构体加入 test_head 的链表
    list_add(&(zhao.list), test_head);
    list_add(&(qian.list), test_head);
    list_add(&(sun.list), test_head);
    list_add(&(li.list), test_head);
    list_add(&(bao.list), test_head);
    
     //遍历双链表
    list_for_each_entry_safe(pos, next, test_head, list) {
        printf("name = %s, age = %d\n\n", pos->name, pos->age);
    }
    
	//删除双链表entry
    list_del(&bao.list);

    list_for_each_entry_safe(pos, next, test_head, list) {
        printf("name = %s, age = %d\n\n", pos->name, pos->age);
    }

    return 0;
}

运行结果：

name = bao, age = 5

name = li, age = 4

name = sun, age = 3

name = qian, age = 2

name = zhao, age = 1

name = li, age = 4

name = sun, age = 3

name = qian, age = 2

name = zhao, age = 1

```

#### 三、宏解读

详细解读宏和函数

> 这两个宏，完成遍历双链表遍历的功能。

```c
@brief 通过结构体成员的地址，结构体的类型，找到该结构体的首地址

双链表每个entry的指针
/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 */
 
#define list_entry(ptr, type, member)               \
   ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))



//遍历双链表
/**
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop counter.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
 
#define list_for_each_entry_safe(pos, n, head, member)            \
    for (pos = list_entry((head)->next, typeof(*pos), member),    \
        n = list_entry(pos->member.next, typeof(*pos), member);   \
        &pos->member != (head);                                   \
        pos = n, n = list_entry(n->member.next, typeof(*n), member) \
    )

#endif
```

#### 知识点1
1、pos 是 head（双链表头）的第一个结构体entry ；n 是 pos 的下一个结构体entry   ；判断是否便利结束（循环双链表）；将pos 赋值给n， n读取下一个结构体entry；
   
2、list_entry 宏 ：结构体的成员名字 + 结构体的类型 + 结构体成员的地址 --->这个结构体的首地址。

3、双链表中的数据（结构体）不一定要是一样的， 只要有struct list_head的结构体就可以。```list_entry可以找到```

4、ptr------指向 双链表entry（结构体）的list成员;       
type------ 双链的 一个entry的类型(不是类型的指针) ;  
这个类型必须是结构体或者联合体;

5、member-------你的每个结构体entry都有的那个成员的名字;(list)

6、返回值就是stu结构体首地址；



#### 知识点2

- (char *)(ptr)      
 **为什么要强制转换为(char *)?**

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    int array[5] = {1, 2, 3, 4, 5};
    int *p = &array[0];

    printf("p = %p\n", (p + 0));
    printf("p = %p\n", (p + 1));
    printf("p = %p\n", (p + 2));
    
    printf("p = %p\n", ((char *)p + 4));
    //printf("p = %p\n", ((char *)p + (unsigned long)1));
       
    return 0;
}
```
运行:

> bao:day10141 bao$ gcc -o test1 test1.c        
bao:day10141 bao$ ./test1       
p = 0x7ffee68deb40      
p = 0x7ffee68deb44              
p = 0x7ffee68deb48       
p = 0x7ffee68deb44       


- list_entry宏demo

```c
#include <stdio.h>

#define list_entry(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

typedef struct test {
    char name[20];
}test;

typedef struct student {
    test test1;
    int age;
    int flag;
} student;

int main(int argc, char *argv[]) {
    student zhao = {"zhao", 20, 0};
    student *p = &zhao;

    test *pname = {0};
    printf("%p\n", p);
    printf("zhao name is = %s, zhao age is = %d\n", zhao.test1.name, zhao.age);
    
    printf("zhao name is = %p, zhao age is = %p\n", zhao.test1.name, &(zhao.age));

    pname = list_entry(p, typeof(test), name);
    printf("\n%s\n", (char *)pname);
    printf("\n%p\n", (char *)pname);
    
    return 0;
}

```

运行结果
>bao:day1014 bao$ gcc -o test2 test2.c       
bao:day1014 bao$ ./test2       
0x7ffeea7d5b38        
zhao name is = zhao, zhao age is = 20       
zhao name is = 0x7ffeea7d5b38, zhao age is = 0x7ffeea7d5b4c        
>
>**zhao**
>
>0x7ffeea7d5b38       
bao:day1014 bao$ 
> 

#### 知识点3
1、整个数组是连续的存储空间;但是结构体不是(可能有填充字节)；      
2、在计算机中，要访问一个地址空间，必先知道他的地址， 然后才访问他对应的空间；      
3、一个int变量占4个字节,每个字节都有一个地址；但是只有一个地址表示这个变量的地址;但是这4个字节是有4个地址的；            
4、将一个int强制转换为char是,存储这个数据的储存空间大小变小了;          
>将一个int * 强制转换成char  *,都是4个字节(好像现在不是了,姑且这么说).存储这两个指针的存储空间的大小都是一样的; 
>       
> 改变的是它们指向的那块存储空间的 "读取数据能力";      
假设他们的首地址一样,一个是从首地址对应的那个存储空间读取4个字节,一个是读取1个字节;

5、 (unsigned long)(&((type *)0)->member)) 
这个最后的结果是(unsigned long)类型的一个数;(这个是在代码编译的过程中就算出来的);

就是结构体student的首地址到成员member的偏移量;

6、通过这个命令`getconf LONG_BIT`   可知道 (unsigned long)是64位       
  64位 = 8个字节     
7、&((type *)0)->member)-----将来是一个指针,int的范围太小,不足以保存这个转换过来的地址.      

------------


- &((type *)0)->member)         
1、运算符的优先级 & <  ->          
2、(test *)0)----将0强制转换成结构体test的指针类型；      
这个在C语言是可以的.
这不是空指针?不报段错误?

demo

```c
#include <stdio.h>

struct student {
    char name[20];
    int age;
    int flag;
};

int main(int argc, char *argv[]) {
    struct student zhao = {"zhao", 20, 0};
    struct student *p = &zhao;

    printf("zhao name is = %s, zhao age is = %d\n", zhao.name, zhao.age);
    
    // printf("p = %p\n", p);
    // printf("%p\n", p.name);
    
    printf("%p\n", (&((struct student *)0)->name));
    printf("%p\n", (&((struct student *)1)->name));
    printf("%p\n", (&((struct student *)-1)->name));

    printf("%p\n", (&((struct student *)0)->age));
    printf("%p\n", (&((struct student *)1)->age));
    printf("%p\n", (&((struct student *)-1)->age));

    printf("p = %p\n", p);
    printf("%ld\n", (unsigned long)p);
    printf("%ld\n", (unsigned long) (&((struct student *)0)->age));
    printf("%d\n", (int) (&((struct student *)0)->age));
    printf("%ld\n",  (unsigned long)(&((struct student *)1)->age));
    printf("%ld\n",  (unsigned long)(&((struct student *)-1)->age));
    printf("1 = %p\n", (void *)1);
   return 0;
}
```

运行结果:
>bao:day1014 bao$ ./test3       
zhao name is = zhao, zhao age is = 20        
0x0      
0x1       
0xffffffffffffffff        
0x14       
0x15       
0x13       
p = 0x7ffeece89b38       
140732873087800      
20      
20       
21      
19       
1 = 0x1    

1、这里主要的作用是计算偏移量,不是去取这个这个指针所指向存储空间的内容.不然就会有段错误.      



- 一个指向 NULL 的 type* 类型 指针 和 这里的 (type*)0 是等价的（ansi/iso-c99 标准规定 NULL 指针为 0x00000000， 即内存中的“第 0 号地址”）


```c
#include <stdio.h>

/* 
    1、char ch1[5] = {0};只能给数组的第一个元素赋值;---局部变量赋值--没意义;
    2、0-- 一个指针.这里的0不是int, 而是一个地址; #define 定义
 */
int main(int argc, char *argv[]) {
    char *p1 = 0;
    // char *p2 = 1;


    char ch1[5] = {0};
    char ch2[5] = {1};
    printf("ch2 = %c, %c, %c, %c, %c\n", ch2[0], ch2[1], ch2[2], ch2[3],ch2[4]);
    printf("ch2 = %d, %d, %d, %d, %d\n", ch2[0], ch2[1], ch2[2], ch2[3],ch2[4]);
    printf("ch2 = 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", ch2[0], ch2[1], ch2[2], ch2[3],ch2[4]);

    int num1[5] = {0};
    int num2[5] = {1};
    printf("num2 = %d, %d, %d, %d, %d\n", num2[0], num2[1], num2[2], num2[3],num2[4]);

    return 0;
}
```
运行结果:
> bao:day1014 bao$ ./test5       
ch2 = , , , ,         
ch2 = 1, 0, 0, 0, 0      
ch2 = 0x1, 0x0, 0x0, 0x0, 0x0       
num2 = 1, 0, 0, 0, 0      

------
--------
![在这里插入图片描述](https://img-blog.csdnimg.cn/2019101423515472.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NDk2NjkwMA==,size_16,color_FFFFFF,t_70)




