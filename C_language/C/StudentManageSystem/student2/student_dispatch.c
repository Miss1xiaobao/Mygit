#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "slist.h"
#include "student.h"
#include "student_control.h"
#include "student_dispatch.h"
#include "student_module.h"

/* 
* 1、头文件声明的顺序，因为student.h用到了student list_head，但是却没有声明， 
* 2、没有main函数编译不会通过；
* 3、指针和变量没有清楚；
* 4、书写错误“member”--> "number"
* 5、给全局变量赋值的时候，必须是已经知道的常量，calloc的不是；
* 6、变量作用域，//stu_info_head uninitialized!
* 7、clang: error: linker command failed with exit code 1 
    头文件被多次引用，造成重复，makefile文件里面生成 .o文件的时候是一个一个生成的，
    所以每个.o文件的中都包含了相同的某个头文件，
    处理头文件。
    
    ！！！头文件中的定义变量和函数定义
*/


extern struct student *handle;

dispatch_control_req_t dispatch_control_req_array[] = {
    {ADD_REQ, module_add_enent},
    {DEL_REQ, module_del_event},
    {QUERY_REQ, module_query_event},
    {CHANGE_REQ, module_change_event}
};

int dispatch_control_req_func(control_req_t *req)
{
    int ret = -1;
    int i, count;

    ret = dispatch_get_sys_status();
    if(ret == 0){
        ret = INVALID_OPERATION;
        return ret;
    }

    count = sizeof(dispatch_control_req_array)/sizeof(dispatch_control_req_t);
    for(i = 0; i < count; i++){
        if(dispatch_control_req_array[i].cmd == req->cmd) {
            dispatch_control_req_array[i].proc(req);
        }
    }
    ret = 0;

    return ret;
}

dispatch_req_t dispatch_req_array[] = {
    {PRINT_ALL_REQ, module_print_all_stu_info},
    {EXIT_REQ, module_exit_system},
    {INIT_REQ, module_loading_init},
};


int dispatch_req_func(req_t *req)
{
    int ret = -1;
    int i, count;

    // ret = dispatch_get_sys_status();
    // if(ret == 0){
    //     ret = INVALID_OPERATION;
    //     return ret;
    // }

    count = sizeof(dispatch_req_array)/sizeof(dispatch_req_t);
    for(i = 0; i < count; i++){
        if(dispatch_req_array[i].cmd == req->cmd) {
            dispatch_req_array[i].proc();
        }
    }
    
    ret = 0;
    return ret;
}

int dispatch_get_sys_status()
{
    return handle->running;
}


