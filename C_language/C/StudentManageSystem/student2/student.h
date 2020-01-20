#ifndef STUDENT_H
#define STUDENT_H

#include "slist.h"
#include "student_control.h"

/* 错误码 */
#define OK                 0
#define INVALID_OPERATION -1
#define FAILED            -2

/* 请求码 */
#define   ADD_REQ        0X01
#define   DEL_REQ        0x02
#define   QUERY_REQ      0x03
#define   CHANGE_REQ     0x04

/* 请求码 */
#define   PRINT_ALL_REQ  0x01
#define   EXIT_REQ       0x02
#define   INIT_REQ       0x03  

enum type_event{
    EXIT_EVENT = 0,
    ADD_EVENT,
    DEL_EVENT,
    QUERY_EVENT,
    CHANGE_EVENT,
    PRINT_ALL_EVENT,
};

/**
 * @brief handle
 * @element head  双链表的头节点
 * @element reqs  
*/
struct student{
    struct list_head *head;  //学生双链表头
    struct list_head *reqs;  //所有的请求链表；
    int   running;
};


/**
 * @brief 学生信息结构体
 * @element id      学号
 * @element name    姓名
 * @element grade   成绩
 * @element teacher 老师
 * @element flag    标志（预留）
 * @element list    链表node点
*/
typedef struct student_info_t
{  
    int    id;          //学号
    char   name[50];    //姓名
    // int    age;      //年龄
    int    grade;       //成绩
    char   teacher[50]; //老师
    int    flag;        //S、T、root
    struct list_head list;
}stu_info_t;


#endif