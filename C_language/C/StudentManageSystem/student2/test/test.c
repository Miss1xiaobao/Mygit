#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <malloc.h>
#include <math.h>
#define LEN sizeof(struct student)
struct student
{
    struct student *next;
    long num;
    char name[10];
    float c;
    float math;
    float english;
    float sum;
};
int n;
struct student *creat() //建立基础的学生信息库
{
    struct student *head, *p1, *p2;
    n = 0;
    p1 = p2 = (struct student *)malloc(LEN);
    printf("输入学生的学号为0时，停止录入。\n");

    if (p1->num != 0)
    {
        n += 1;
        if (n == 1)
        {
            head = p1;
        }
        else
        {
            p2->next = p1;
        }
        p2 = p1;
        p1 = (struct student *)malloc(LEN);
        printf("请输入学生学号");
        scanf("%ld", &p1->num);
        if (p1->num != 0)
        {
            printf("请输入学生姓名");
            scanf("%s", p1->name);
            printf("c语言:");
            scanf("%f", &p1->c);
            printf("高数:");
            scanf("%f", &p1->math);
            printf("英语:");
            scanf("%f", &p1->english);
            p1->sum = p1->english + p1->math + p1->c;
            printf("\n");
        }
    }
    p2->next = NULL;
    return head;
}
struct student *del(struct student *head, long num) //删除学生信息
{
    struct student *p1, *p2;
    if (head == NULL)
    {
        printf("\nlist null\n");
        return head;
    }
    p1 = head;
    while (num != p1->num && p1->next != NULL)
    {
        p2 = p1;
        p1 = p1->next;
    }
    if (num == p1->num)
    {
        if (p1 == head)
            head = p1->next;
        else
            p2->next = p1->next;
        printf("你删除的学生信息为:\n");
        printf("学号:%ld\n", p1->num);
        printf("姓名:%s\n", p1->name);
        printf("c语言:%5.2f\n", p1->c);
        printf("高数:%5.2f\n", p1->math);
        printf("英语:%5.2f\n", p1->english);
        p1->sum = p1->english + p1->math + p1->c;
        printf("总分:%5.2f\n", p1->sum);
        printf("\n");
        n = n - 1;
    }
    else
        printf("输入有误!\n");
    return head;
}
struct student *insert(struct student *head, struct student *student) //添加学生信息
{
    struct student *p0, *p1, *p2;
    p1 = head;
    p0 = student;
    if (head == NULL)
    {
        head = p0;
        p0->next = NULL;
    }
    else
        while ((p0->num > p1->num) && (p1->next != NULL))
        {
            p2 = p1;
            p1 = p1->next;
        }
    if (p0->num < p1->num)
    {
        if (head == p1)
            head = p0;
        else
            p2->next = p1;
    }
    else
    {
        p1->next = p0;
        p0->next = NULL;
    }
    n += 1;
    return head;
}
void sort(struct student *head) //排序
{
    struct student *p, *q, *max;
    long temp1;
    char temp2[4];
    float temp, temp3, temp4, temp5;
    p = head;
    while (p != NULL)
    {
        max = p;
        q = p->next;
        while (q != NULL)
        {
            if (max->sum < q->sum)
                max = q;
            q = q->next;
        }
        //交换值
        if (max != p)
        {
            temp = max->sum;
            max->sum = p->sum;
            p->sum = temp;
            temp1 = max->num;
            max->num = p->num;
            p->num = temp1;
            strcpy(temp2, max->name);
            strcpy(max->name, p->name);
            strcpy(p->name, temp2);
            temp3 = max->c;
            max->c = p->c;
            p->c = temp3;
            temp4 = max->math;
            max->math = p->math;
            p->math = temp4;
            temp5 = max->english;
            max->english = p->english;
            p->english = temp5;
        }
        p = p->next;
    }
    printf("排序以后的学生信息:\n");
    struct student *p1;
    p1 = head;
    int count = 1;
    while (p1 != NULL)
    {
        printf("第%d名:\n", count);
        printf("学号:%ld", p1->num);
        printf("姓名:%s", p1->name);
        printf("c语言:%5.3f", p1->c);
        printf("高数:%5.3f", p1->math);
        printf("英语:%5.3f", p1->english);
        printf("总分:%4.2f", p1->sum);
        printf("\n");
        count++;
        p1 = p1->next;
    }
}
float ave(struct student *head) //求平均数
{
    int i;
    float ave, sum = 0;
    struct student *p;
    p = head;
    for (i = 0; p != NULL; i++)
    {
        sum = sum + p->sum;
        p = p->next;
    }
    ave = sum / i;
    return ave;
}
void change(struct student *head, long num) //修改学生数据
{
    struct student *p;
    p = head;
    for (; p != NULL;)
    {
        if (p->num == num)
        {
            printf("请输入学生姓名:");
            scanf("%s", p->name);
            printf("c语言:");
            scanf("%f", &p->c);
            printf("高数:");
            scanf("%f", &p->math);
            printf("英语:");
            scanf("%f", &p->english);
            p->sum = p->c + p->math + p->english;
            printf("\n");
            break;
        }
        else
        {
            p = p->next;
        }
    }
}
struct student *locate(struct student *head, long num1) //按学号查找
{
    struct student *p1, *p2;
    p1 = head;
    if (head == NULL)
    {
        printf("\n链表为空！\n");
        return head;
    }
    else
    {
        /* == */
        while (num1 == p1->num && p1->next != NULL)
        {
            p2 = p1;
            p1 = p1->next;
        }
        if (p1->num == num1) //比较输入学号是否与链表中学号匹配
        {
            printf("查找的学生信息为:\n");
            printf("学号:%ld\n", p1->num);
            printf("姓名:%s\n", p1->name);
            printf("C语言:%5.3f\n", p1->c);
            printf("高数:%5.3f\n", p1->math);
            printf("英语:%5.3f\n", p1->english);
            p1->sum = p1->c + p1->math + p1->english;
            printf("总分:%5.3f\n", p1->sum);
            printf("\n");
            return head;
        }
        else
        {
            printf("无该学生数据\n");
            return head;
        }
    }
}
struct student *locate1(struct student *head) //按姓名查找
{
    char name[10];
    printf("请输入要查询学生的姓名:");
    scanf("%s", name);
    struct student *p1, *p2;
    p1 = head;
    if (head == NULL)
    {
        printf("\n链表为空\n");
        return head;
    }
    else
    {
        while (strcmp(name, p1->name) == 0 && p1->next != NULL)
        {
            p2 = p1;
            p1 = p1->next;
        }
        if (strcmp(name, p1->name) == 0) //比较输入姓名链表中姓名是否匹配
        {
            printf("查找的学生信息为:\n");
            printf("学号:%ld\n", p1->num);
            printf("姓名:%s\n", p1->name);
            printf("C语言:%5.3f\n", p1->c);
            printf("高数:%5.3f\n", p1->math);
            printf("英语:%5.3f\n", p1->english);
            p1->sum = p1->c + p1->math + p1->english;
            printf("总分:%5.3f\n", p1->sum);
            printf("\n");
            return head;
        }
        else
        {
            printf("无该学生数据\n");
            return head;
        }
    }
}
//输出学生信息
void print(struct student *head)
{
    struct student *p;
    p = head;
    printf("现在链表里的数据为:\n");
    while (p != NULL)
    {
        printf("学号:%ld\n", p->num);
        printf("姓名:%s\n", p->name);
        printf("C语言:%5.3f\n", p->c);
        printf("高数:%5.3f\n", p->math);
        printf("英语:%5.3f\n", p->english);
        printf("总分:%5.3f\n", p->sum);
        printf("\n");
        p = p->next;
    }
    printf("\n");
}
void sum(struct student *head)
{
    int n = 0;
    struct student *p, *p1;
    p = head;
    while (p != NULL)
    {
        if (p->c < 60)
        {
            n++;
        }
        p = p->next;
    }
    if (n == 0)
    {
        printf("本次C语言无人挂科。\n");
    }
    if (n > 0)
    {
        printf("本次C语言挂科人数有%d人\n", n);
        printf("挂科人员的学号，姓名如下\n");
    }
    p1 = head;
    while (p1 != NULL && p1->c < 60)
    {
        printf("学号:%ld", p1->num);
        printf("姓名:%s\n", p1->name);
        p1 = p1->next;
    }
    printf("\n");
}
int main()
{
    int choose = 1;
    long number, e;
    struct student *head, *p;
    char password[10] = "123456";
    char password1[10], password2[10], password3[10], password4[10], num[12];
    printf("请输入进入学生信息管理系统的管理员代号和密码:\n系统默认登陆密码为:123456.\n管理员代号");
    scanf("%s", num);
    printf("密码:");
    scanf("%s", password1);
    printf("\n");
    for (;;)
    {
        if (strcmp(password1, password) != 0)
        {
            printf("输入错误，请重新输入:\n管理员代号:");
            scanf("%s", num);
            printf("\n密码:");
            scanf("%s", password1);
            printf("\n");
        }
        else
        {
            printf("%s管理员成功登录\n", num);
            break;
        }
    }
    while (choose != 0)
    {

        printf("****欢迎使用学生成绩管理系统****\n");
        printf("---------------------------------------\n");
        printf("\t0.退出程序\n\t1.录入学生记录\n\t2.添加学生记录\n");
        printf("\t3.删除学生记录\n\t4.修改学生记录\n");
        printf("\t5.查找学生记录\n\t6.按总分对学生记录进行降序排序\n");
        printf("\t7.输出所有学生信息\n\t8.计算班级平均分\n");
        printf("\t9.修改管理员密码\n\t10.统计C语言挂科人数\n");
        printf("请输入一个数字:\n");
        scanf("%d", &choose);
        system("cls");
        switch (choose)
        {
        case 0:
            printf("\n");
            printf("****期待你的下次使用****");
            printf("\n");
            break;
        case 1:{
            head = creat();
            system("pause");
            system("cls");
            break;
        }
        case 2: {
            p = (struct student *)malloc(LEN);
            printf("请输入要添加的学生学号\n");
            printf("学号:\n");
            scanf("%ld", &p->num);
            if (p->num != 0)
            {
                printf("请输入学生姓名:");
                scanf("%s", p->name);
                printf("c语言:");
                scanf("%f", &p->c);
                printf("高数:");
                scanf("%f", &p->math);
                printf("英语:");
                scanf("%f", &p->english);
                p->sum = p->c + p->math + p->english;
                head = insert(head, p);
            }
            system("pause");
            system("cls");
            break;
        }
        case 3:{
            printf("输入你要删除的学号:\n");
            scanf("%ld", &e);
            if (e != 0)
                head = del(head, e);
            system("pause");
            system("cls");
            break;
        }
        case 4: {
            //num 相同的变量名重复定义
            int num;
            printf("请输入密码:\n");
            scanf("%s", password4);
            while (strcmp(password, password4) != 0)
            {
                printf("输入有误，请重试:\n");
                scanf("%s", password4);
            }
            printf("输入密码正确!\n");
            printf("请输入要修改的学生学号:");
            //num是int， 不是个用%ld
            scanf("%d", &num);
            //类型不同
            change(head, (long)num);
            system("pause");
            system("cls");
            break;
        }
        case 5: {
            //use of undeclared identifier
            //expected expression
            int ch;
            printf("输入你要查找的学生的内容:\n1、按学号查询\n2、按姓名查询\n");
            scanf("%d", &ch);
            if (ch == 1)
            {
                printf("请输入要查询的学生学号:");
                scanf("%ld", &number);
                head = locate(head, number);
                printf("\n");
            }
            if (ch == 2)
            {
                head = locate1(head);
                printf("\n");
            }
            system("pause");
            system("cls");
            break;
        }
        case 6: {
            sort(head);
            system("pause");
            system("cls");
            break;
        }
        case 7:
            print(head);
            system("pause");
            system("cls");
            break;
        case 8:{
            float aver;
            aver = ave(head);
            printf("该班平均分为:%4.3f\n", aver);
            system("pause");
            system("cls");
            break;
        }
        case 9:
            printf("旧密码:");
            scanf("%s", password1);
            printf("新密码:");
            scanf("%s", password2);
            printf("请你确定新密码:");
            scanf("%s", password3);
            for (;;)
            {
                if (strcmp(password, password1) != 0)
                {
                    printf("输入的旧密码有误\n");
                    printf("旧密码:");
                    scanf("%s", password1);
                    printf("新密码:");
                    scanf("%s", password2);
                    printf("请你确定新密码:");
                    scanf("%s", password3);
                }
                if (strcmp(password2, password3) != 0)
                {
                    printf("输入的新密码与确认的新密码不一致\n");
                    printf("旧密码:");
                    scanf("%s", password1);
                    printf("新密码:");
                    printf("请确认新密码:");
                    scanf("%s", password3);
                }
                if (strcmp(password1, password) == 0 && strcmp(password2, password3) == 0)
                {
                    printf("成功修改密码.\n");
                    break;
                }
            }
            strcpy(password, password2);
            system("pause");
            system("cls");
            break;
        case 10:
            sum(head);
            system("pause");
            system("cls");
            break;
        }
    }
    return 0;
}
