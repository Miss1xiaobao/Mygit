#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "slist.h"
#include "student.h"
#include "student_control.h"
#include "student_dispatch.h"

/**
 * @brief 这个文件主要是实现用户调用接口：添加、删除、查找、修改学生信息等。
 * 1、添加学生信息。
 * 2、删除学生信息。
 * 3、查找学生信息。
 * 4、修改学生信息。
 * 5、打印所有学生的信息。
 * 0、退出系统（将学生信息存到文件中，删除申请的内存）
 * 
*/
extern struct student *handle;

int control_add_student(int id, char name[], int grade, char teacher[])
{
    int              ret   = -1;
    control_req_t    *req  = NULL;
    param_t          *param = NULL;
    
    req = calloc(1, sizeof(req_t));
    if(req == NULL) {
        printf("Failed to calloc [req] memory\n");
        return ret;
    }
    req->cmd = ADD_REQ;
    req->id = id;
    
    param = (param_t *)calloc(1, sizeof(param_t));
    if(param == NULL) {
        printf("Failed to calloc [param] memory\n");
        return ret;
    }

    memset(param->name, 0, 50);
    memset(param->teacher, 0, 50);

    param->grade = grade;
    strncpy(param->name, name, 50);
    strncpy(param->teacher, teacher, 50);

    req->param = param;

    ret = dispatch_control_req_func(req);
    printf("ret = %d\n", ret);
    // free(param);
    // free(req);
    return ret;
}


int control_delete_student(int id)
{
    int ret = -1;
    control_req_t *req = NULL;

    req = calloc(1, sizeof(req_t));
    if(req == NULL) {
        printf("Failed to calloc [req] memory\n");
        return ret;
    }
    req->id = id;
    req->cmd = DEL_REQ;

    ret = dispatch_control_req_func(req);
    
    // free(req);
    return ret;
}


int control_query_student(int id)
{
    int ret = -1;
    control_req_t *req = NULL;

    req = calloc(1, sizeof(req_t));
    if(req == NULL) {
        printf("Failed to calloc [req] memory\n");
        return ret;
    }
    req->id = id;
    req->cmd = QUERY_REQ;

    ret = dispatch_control_req_func(req);
    
    // free(req);
    return ret;
}


int control_change_student(int id, char name[], int grade, char teacher[])
{
    int      ret   = -1;
    control_req_t    *req  = NULL;
    param_t  *param = NULL;
    
    req = calloc(1, sizeof(req_t));
    if(req == NULL) {
        printf("Failed to calloc [req] memory\n");
        return ret;
    }
    req->cmd = CHANGE_REQ;
    req->id = id;
    
    param = (param_t *)calloc(1, sizeof(param_t));
    if(param == NULL) {
        printf("Failed to calloc [param] memory\n");
        return ret;
    }

    memset(param->name, 0, 50);
    memset(param->teacher, 0, 50);
    
    param->grade = grade;
    strcpy(param->name, name);
    strcpy(param->teacher, teacher);
    req->param = param;

    ret = dispatch_control_req_func(req);

    // free(param);
    // free(req);
    return ret;
}


int control_print_student()
{
    int ret = -1;
    req_t *req = NULL;

    req = calloc(1, sizeof(req_t));
    if(req == NULL) {
        printf("Failed to calloc [req] memory\n");
        return ret;
    }

    req->cmd = PRINT_ALL_REQ;

    ret = dispatch_req_func(req);
    
    // free(req);
    return ret;

}


int control_exit_system()
{
    int ret = -1;
    req_t *req = NULL;

    req = calloc(1, sizeof(req_t));
    if(req == NULL) {
        printf("Failed to calloc [req] memory\n");
        return ret;
    }

    req->cmd = EXIT_REQ;

    ret = dispatch_req_func(req);
    
    // free(req);
    return ret;

}

int control_config_init()
{
    int ret = -1;
    req_t *req = NULL;

    req = calloc(1, sizeof(req_t));
    if(req == NULL) {
        printf("Failed to calloc [req] memory\n");
        return ret;
    }

    req->cmd = INIT_REQ;

    ret = dispatch_req_func(req);
    
    // free(req);
    return ret;
}

void control_student_init()
{
    int operation = 0;
    int ret = -1;

    printf("Welcome to XiaoBao Student Information Manage System!!!\n");
    printf("Loading Resources...\n");

    ret = control_config_init();
    if(ret == -1) {
        printf("-1\n");
        return;
    }
    
    printf("Loading Resources Completed\n");

    
    while (1) {
        printf("\n");
        printf("********************************\n");
        printf("添加学生信息请输入 【 1 】\n");
        printf("删除学生信息请输入 【 2 】\n");
        printf("查找学生信息请输入 【 3 】\n");
        printf("修改学生信息请输入 【 4 】\n");
        printf("打印 所有 学生信息 【 5 】\n");
        printf("退出系统请输入    【 0 】\n");
        printf("********************************\n");
        printf("\n");
        printf("请输入您的操作：");
        scanf("%d", &operation);

        switch (operation)
        {
        //add
        case 1 :{
            int   ret = -1; 
            int   id  = -1;
            char  name[50];
            int   grade = 0;
            char  teacher[50];

            printf("id name grade teacher\n");
            scanf("%d %s %d %s", &id, name, &grade, teacher);

            ret = control_add_student(id, name, grade, teacher);
            if(ret < 0) {
                printf("\n\nadd failed!\n\n\n");
                control_print_student();
                break;
            }
            //printf_all
            control_print_student();
            printf("\n\nadd success!\n\n\n");
            break;
        }

        //delete
        case 2 : {
            int ret = -1;
            int id  = -1;

            printf("id\n");
            scanf("%d", &id);

            ret = control_delete_student(id);
            if(ret == 0) {
                //printf_all
                control_print_student();
                printf("\n\n\n");
                break;
            }
            printf("del failed!\n\n\n");
            break; 
        }

        //query
        case 3 : {  
            int ret = -1;
            int id  = -1;

            printf("id\n");
            scanf("%d", &id);

            ret = control_query_student(id);
            if(ret == 0) {
                printf("query success!\n\n\n");
                break;
            }
            printf("query failed!\n\n\n");
            break; 
        }

        //change
        case 4 : {
            int   ret = -1; 
            int   id  = -1;
            char  name[50];
            int   grade = 0;
            char  teacher[50];

            printf("id \n");
            scanf("%d", &id);
            printf("name grade teacher\n");
            scanf("%s %d %s", name, &grade, teacher);

            ret = control_change_student(id, name, grade, teacher);
            
            if(ret == 0) {
                //query
                control_query_student(id);
                printf("\n\n\n");
                break;
            }
            printf("change failed!\n\n\n");
            break;
        }
        
        //print_all_stu_info
        case 5 : {
            int ret = -1;
            ret = control_print_student();
            if(ret < 0) {
                printf("print all student info failed!\n\n\n");
            }
            break;
        }
        
        //exit
        case 0 : {
            int ret = -1;
            ret = control_exit_system();
            if(ret < 0) {
                printf("exit failed\n\n\n");
            }
            break;
        }
        default:
            printf("Invalid input\n\n");
            break;
        }

    }
}


/**
 * 1、student.h头文件没有include “student_control.h",不识别“student_control.h"中的结构体类型
 * 2、sizeof写错--->siezof()   student_control.c:35:34: warning: implicit declaration of function 'siezof' is invalid in C99 
 * 3、int dispatch_req_func(req_t *req) 没有在头文件“。。。dispatch。。。”声明，在本文件添加对应的头文件也没用
 * 4、case没有加{}, 使ret变量多次重复定义；
 * 5、
 */