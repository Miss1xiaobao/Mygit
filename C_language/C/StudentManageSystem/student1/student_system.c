/* 
* 学生信息管理系统；
*  功能介绍：
* 1、查询（id）学生信息
* 2、增加学生 （id）学生信息
* 3、删除学生信息
* 4、修改学生信息；
* 5、打印所有学生信息；

学生信息主键  “id”
 id值 为 正整数，

 */

#include <stdio.h>
#include <stdlib.h>

void query_stu();
int  query_stu_exist(int id);
int add_stu();
void insert_stu(int stuid);
int delete_stu();
int change_stu();
void init();
void print_db();
void print_students();
void print_stu(int id);



struct student{
    int id;  //学生id
    char name[50];  //学生姓名
    float grade;
    int lim;  //权限
} stu[1000];

int array_length = 0;   //数组长度
int students_length = 0;  //学生个数


//查询学生信息--id
void query_stu()
{
    int i = 0;
    int stuid = -1;
    int flag = -1;

    printf("请输入你要查询的学生ID号：");
    scanf("%d", &stuid);

    for (i = 0; i < array_length; i++) {
        if (stuid == stu[i].id) {
            printf("This学生存在\n");
            print_stu(stuid);
            flag = 1;
           // return stuid;  //返回学生的id号
        }
    }
    if (flag != 1){
        printf("id = %d 的学生还没有录入。\n", stuid);
    }
    
    // return 0;
}

//查询学生是否存在(id)，返回 数组下标。--id
int  query_stu_exist(int id)
{
    for (int i = 0; i < array_length; i++) {
        if (id == stu[i].id) {
            return i;
        }
    }
    printf("id = %d 的学生还没有录入\n", id);
    return -1;
}

/* //查询学生是否存在，返回学生的 id值。
int  query_stu_exist2(int id)
{
    for (int i = 0; i < array_length; i++) {
        if (id == stu[i].id) {
            return i;
        }
    }
    printf("id = %d 的学生还没有录入\n", id);
    return -1;

} */

//增加学生信息--id
int add_stu()
{
    int stuid = -1;
    int i = 0;
    printf("请输入你的学生ID号：");
    scanf("%d", &stuid);

    if((i = query_stu_exist(stuid)) == -1){
        insert_stu(stuid);
        return 0;
    } else {
        printf("查询结果有误！！！\n");
        return -1;
    }
    
}

//插入一个学生的记录。根据学生的id号；
void insert_stu(int stuid)
{
    if (1000 == array_length) {
        printf("满员\n");
        exit(1);
    } else {
        stu[array_length].id = stuid;
        printf("请输入学生姓名：");
        scanf("%s", stu[array_length].name);
        printf("\n请输入学生成绩：");
        scanf("%f", &stu[array_length].grade);
        printf("\n请输入学生权限：");
        scanf("%d", &stu[array_length].lim);
        array_length++;
        students_length++;
        printf("id = %d 的学生录入成功！\n", stuid);
}
}

//删除学生信息--id
int delete_stu()
{
    int stuid = -1;
    int i = -1;
    printf("请输入你要查询的学生ID号：");
    scanf("%d", &stuid);

    if((i = query_stu_exist(stuid)) == -1){
        printf("查询结果有误！！！\n");
        return -1;
    } else {
        stu[i].id = -2;
        printf("id = %d 的学生删除成功！\n", stuid);
        students_length--;
    }
    return 0;
}

//修改学生信息--id
int change_stu()
{
    int stuid = -1;
    int i = -1;
    printf("请输入你的学生ID号：");
    scanf("%d", &stuid);

    if((i = query_stu_exist(stuid)) == -1){
        printf("查询结果有误！！！\n");
        return -1;
    } else {
        printf("请输入学生姓名：");
        scanf("%s", stu[i].name);
        printf("\n请输入学生成绩：");
        scanf("%f", &stu[i].grade);
        printf("\n请输入学生权限：");
        scanf("%d", &stu[i].lim);
        printf("id = %d 的学生修改成功！\n", stuid);
    }
    return 0;

}

//初始化
void init()
{
    int count = 0;
    int operation = -1;
    while (1) {
        printf("\n");
        printf("********************************\n");
        printf("欢迎来到小豹学生信息管理系统：\n");
        printf("查询学生信息请输入 【 1 】\n");
        printf("修改学生信息请输入 【 2 】\n");
        printf("删除学生信息请输入 【 3 】\n");
        printf("添加学生信息请输入 【 4 】\n");
        printf("打印  数据库  数据 【 5 】\n");
        printf("打印 所有 学生信息 【 6 】\n");
        printf("********************************\n");
        printf("\n");
        printf("请输入您的操作：");
        scanf("%d", &operation);

        switch (operation) {
        case 1:
            query_stu();
            break;
        case 2:
            change_stu();
            break;
        case 3:
            delete_stu();
            break;
        case 4:
            add_stu();
            break;
        case 5:
            print_db();
            break;
        case 6:
            print_students();
            break;
        
        default:
            printf("您的输入有误，请重新输入您的operation：");
            count++;
            break;
        }

        if (5 == count) {
                printf("滚、、、\n");
                count = 0;
                break;
            }
    }   
}

//打印数据库
void print_db()
{
    printf("共插入有%d条记录！\n", array_length);
    for (int i = 0; i < array_length; i++) {
        printf("id = %d, name = %s, grade = %f, lim = ** \n",
            stu[i].id, stu[i].name, stu[i].grade);
    }  
}

//打印所有学生信息
void print_students()
{
    printf("共有%d个学生记录在小豹系统中！\n", students_length);
    for (int i = 0; i < array_length; i++) {
        if (-2 != stu[i].id) {
            printf("id = %d, name = %s, grade = %f, lim = ** \n",
            stu[i].id, stu[i].name, stu[i].grade);
        }   
    }  
}

//打印一个学生的信息。。。
void print_stu(int id)
{
    printf("id = %d, name = %s, grade = %f, lim = ** \n",
            stu[id].id, stu[id].name, stu[id].grade);

}

int main(int argc, char const *argv[])
{

    init();
 
    return 0;
}
