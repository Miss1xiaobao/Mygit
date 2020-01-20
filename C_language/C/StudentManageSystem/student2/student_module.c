#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student_control.h"
#include "student_dispatch.h"
#include "student.h"
#include "slist.h"
#include "student_module.h"

/**
 * @brief 这个文件主要是实现具体的功能：添加、删除、查找、修改学生信息等。提供具体的服务。
 * 1、添加学生信息。
 * 2、删除学生信息。
 * 3、查找学生信息。
 * 4、修改学生信息。
 * 
*/
extern struct student *handle;

stu_info_t *module_find_node_by_id(int id)
{
    stu_info_t *node = NULL, *next = NULL;

    list_for_each_entry_safe(node, next, handle->head, list) {
        if(id == node->id) {
            return node;
        }
    }
    return NULL;
}


void module_add_enent(control_req_t *req)
{
    int ret = -1;
    stu_info_t *entry = NULL;

    entry = module_find_node_by_id(req->id);
    if(entry != NULL) {
        printf("id = This student already exists\n");
        //print this stu info
        return;
    }

    entry = (stu_info_t *)calloc(1, sizeof(stu_info_t));
    if(entry == NULL){
        printf("entry calloc failed\n");
    }

    entry->id = req->id;
    entry->grade = req->param->grade;
    strncpy(entry->name, req->param->name, 50);
    strncpy(entry->teacher, req->param->teacher, 50);

    list_add(&entry->list, handle->head);
    //调用查询，查看是否执行成功；将req的双链表对应删除

    return;
}

void module_del_event(control_req_t *req)
{
    int ret = -1;
    stu_info_t *entry = NULL;

    entry = module_find_node_by_id(req->id);
    if(entry == NULL) {
        printf("This stu not exit\n");
        return;
    } else {
        list_del(&entry->list);
    }
    
}

void module_query_event(control_req_t *req)
{
    stu_info_t *node = NULL;

    node = module_find_node_by_id(req->id);

    if(node == NULL) {
        printf("This stu not exit!\n");
        return;
    }
    printf("%d:%s:%d:%s:%d\n", node->id, node->name, node->grade, node->teacher, node->flag);
}

void module_change_event(control_req_t *req)
{
    stu_info_t *node = NULL;

    node = module_find_node_by_id(req->id);
    if(node == NULL) {
        printf("This stu not exit\n");
        return;
    } else {
        strcpy(node->name, req->param->name); 
        node->grade = req->param->grade;
        strcpy(node->teacher, req->param->teacher);
    }
}

//打开文件
static FILE * module_open(const char *failname, const char *mode)
{
    // FILE * fd = fopen("info/student_infomation", "r+");
    FILE *fd = fopen(failname, mode);

    if(fd == NULL){
        perror("open file failed\n");
    }
    return fd;
}

static void getdate(char str[])
{
    stu_info_t *stu = calloc(1, sizeof(struct student_info_t));
    sscanf(str, "%d:%s:%d:%s:%d", &(stu->id), stu->name, &(stu->grade), stu->teacher, &(stu->flag));
    list_add(&stu->list, handle->head);

}

// 加载文件内容到双链表
void module_loading_init()
{
    if(handle == NULL) {
        printf("stu_info_head uninitialized!\n");
        return;
    }

    char str[80];
    
    FILE *fd = module_open("info/student_infomation", "r+");
    while(fgets(str, 80, fd) != NULL){
        getdate(str);
        memset(str, 0, 80);
    }
    fclose(fd);

    handle->running = 1;
}



//输出双链表的所有节点信息
void module_print_all_stu_info()
{
    stu_info_t *node = NULL, *next = NULL;

    list_for_each_entry_safe(node, next, handle->head, list){
        printf("%d:%s:%d:%s:%d\n", node->id, node->name, node->grade, node->teacher, node->flag);
    }
}

//释放双链表所有内存空间,将每个node从双链表删除，并且释放node动态申请的内存空间。
void free_all_student_info(struct list_head *head)
{
    stu_info_t *node = NULL, *next = NULL;

    list_for_each_entry_safe(node, next, head, list){
        list_del(&(node->list));
        free(node);        
    }
}

//退出系统，将双链表的内容打印到文件中，释放双链表；
void module_exit_system()
{
    char str[80] = {0};
    stu_info_t *node, *next;

    //将双链表的学生信息输出到文件
    if(handle == NULL) {
        printf("stu_info_head uninitialized!\n");
        return;
    }

    if(dispatch_get_sys_status() == 0) {
        printf("handle running == 0\n");
        return; 
    }

    FILE *fd = module_open("info/student_infomation", "w+");

    list_for_each_entry_safe(node, next, handle->head, list) {
        memset(str, 0, 80);
        snprintf(str, 80, "%d:%s:%d:%s:%d\n", node->id, node->name, node->grade, node->teacher, node->flag);
        fputs(str, fd);
    }

    fclose(fd);

    free_all_student_info(handle->head);
}
