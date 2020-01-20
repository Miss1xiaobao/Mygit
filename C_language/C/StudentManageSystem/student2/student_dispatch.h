#ifndef STUDENT_DISPATCH_H
#define STUDENT_DISPATCH_H

#include "student_control.h"
#include "student_module.h"

typedef void (*control_req_fun)(control_req_t * req);

typedef struct{
    int    cmd;
    control_req_fun  proc;
}dispatch_control_req_t;


// typedef void (*fun_t)(req_t * req);
typedef void (*fun_t)();

typedef struct{
    int    cmd;
    fun_t  proc;
}dispatch_req_t;


int dispatch_get_sys_status();
int dispatch_control_req_func(control_req_t *req);
int dispatch_req_func(req_t *req);





#endif