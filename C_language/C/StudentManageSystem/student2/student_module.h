#ifndef STUDENT_MODULE_H
#define STUDENT_MODULE_H

#include "student.h"

stu_info_t *module_find_node_by_id(int id);
void module_add_enent(control_req_t *req);
void module_del_event(control_req_t *req);
void module_query_event(control_req_t *req);
void module_change_event(control_req_t *req);


void module_loading_init();
void module_print_all_stu_info();
void module_exit_system();




#endif