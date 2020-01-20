#include <stdio.h>
#include <stdlib.h>

#include "slist.h"
#include "student.h"
#include "student_control.h"

struct student *handle;

int main(int argc, char *argv[]) {
    handle = calloc(1, sizeof(struct student));
    handle->head = calloc(1, sizeof(struct list_head));

    printf("handle = %p\n", handle);
    printf("handle->head = %p\n", handle->head);

    INIT_LIST_HEAD(handle->head);
    
    printf("handle = %p\n", handle);
    printf("handle->head = %p\n", handle->head);

    control_student_init();
    return 0;
}
