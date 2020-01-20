#ifndef STUDENT_CONTROL_H
#define STUDENT_CONTROL_H

#include "student.h"
#include "slist.h"


typedef struct param_t{
    // int id;
    char   name[50];
    int    grade;
    char   teacher[50];
}param_t;

/**
 * @brief 请求结构体（第三方接口）
 */
typedef struct control_req_t
{
    int      cmd;
    // int      type;     //操作类型123450
    int      id;
    param_t    *param;   //
    struct list_head list;
}control_req_t;

/**
 * @brief 请求结构体
 */
typedef struct req_t
{
    int      cmd;

    struct list_head list;
}req_t;



/**
 * @brief 添加一个学生的信息
 * @param id      学生学号（主键）
 * @param name    学生姓名
 * @param grade   成绩（可扩展为指针，多个成绩）
 * @param teacher 老师（可扩展为指针，多个老师）
 * @return 成功返回0，失败返回<0
 */
int control_add_student(int id, char name[], int grade, char teacher[]);


/**
 * @brief 删除一个学生的信息
 * @param id  学生学号（主键）
 * @return 成功返回0，失败返回<0
 */
int control_delete_student(int id);


/**
 * @brief 查询一个学生的信息
 * @param id  学生学号（主键）
 * @return 成功返回0，失败返回<0
 */
int control_query_student(int id);


/**
 * @brief 修改一个学生的信息
 * @param id      学生学号（主键）
 * @param name    学生姓名
 * @param grade   成绩
 * @param teacher 老师
 * @return 成功返回0，失败返回<0
 */
int control_change_student(int id, char name[], int grade, char teacher[]);


/**
 * @brief 打印所有学生信息
 * @param 无
 * @return 成功返回0，失败返回<0
 */
int control_print_student();


/**
 * @brief 退出系统
 * 
 */
int control_exit_system();

/**
 * @brief 初始化系统
 */
void control_student_init();







#endif