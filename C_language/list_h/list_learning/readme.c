#include <slist.h>
list_for_each_entry_safe(pos, n, &loop->io, list)

//取链表的 每一个元素; pos链表的头节点指针, n链表的头指针的下一个节点指针; 
//有没有到链表的末尾; (链表的最后一个节点的next的地址就是开头的节点的地址)
//将“第一个”节点的地址赋值给pos, n链表的头指针的下一个节点指针.


#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
		n = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, typeof(*n), member))


//最后返回的是type 类型的指针.
//(char *)(ptr)-----转换成(char *)
//编译时期,编译器计算好的,不涉及栈什么的;
// 指针 - 偏移量 = 指针;
//如果你用在结构体上面, 注意结构体的成员之间的存储空间是不是有填充字符, 要用的放在结构体的第一个成员;
// 在计算机中，要访问一个地址空间，必先知道他的地址， 然后才访问他对应的空间；
#define list_entry(ptr, type, member)
        ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

/*  
    int num[5] = {9, 8, 7, 6, 5};
    int *pnum0 = &num[0];一个整形占4个字符;
    int *pnum1 = pnum0++;使指向的地址加4,而不是加1;类型是int *;pnum++这个指针所指向的空间就是数组的第二个元素;也就是num[1]; 
    num[2] == *(num + 2) == *(pnum0 + 2)
    punm1 - pnum0 = 4;这数组之间才是有效的,
    一个字节,一个地址;
*/
//int *----4个字节; char * -----一个字节

//(&((type *)0)->member)))------最后的结果是一个整形,
//type 必须是一个结构体或者联合体的类型,(不是结构体的指针类型)
//一个指向 NULL 的 type* 类型 指针 和 这里的 (type*)0 是等价的（ansi/iso-c99 标准规定 NULL 指针为 0x00000000， 即内存中的“第 0 号地址”）
//C语言中 (type*)X 表示将操作 X 强制类型转换为 type* 类型（即 type* 类型指针）。
// 这里是将 0 强制类型转换为 type* 类型， 0 成为 type* 类型。

// getconf LONG_BIT       64位 = 8个字节

/* 
    (unsigned long)(&((type *)0)->member)))
    1、& 和 -> 的优先级问题.
    2、(&((type *)0)->member))  最后是一个地址.你要取的结构体的地址.
    3、(unsigned long)强转换成这个类型,?不是int,结构体的字节填充问题.
 */




    ((typeof(*pos) *)((char *)((head)->next) - (unsigned long)(&((typeof(*pos) *)0)->member)))

    ((typeof(*pos) *)((char *)(pos->member.next) - (unsigned long)(&((typeof(*pos) *)0)->member)))

    ((typeof(*n) *)((char *)(n->member.next) - (unsigned long)(&((typeof(*n) *)0)->member)))


<----------------------------------------------------->

