#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

typedef struct stu {
    char   name[30];
    int    age;
    struct list_head  list;
}stu;

struct list_head  *test_head;


int main(int argc, char *argv[]) {
    stu *pos = NULL;
    stu *next = NULL;

    test_head = calloc(0, sizeof(struct list_head));

    INIT_LIST_HEAD(test_head);

    stu zhao = {"zhao", 1};
    stu qian = {"qian", 2};
    stu sun = {"sun", 3};
    stu li = {"li", 4};
    stu bao = {"bao", 5};

    list_add(&(zhao.list), test_head);
    list_add(&(qian.list), test_head);
    list_add(&(sun.list), test_head);
    list_add(&(li.list), test_head);
    list_add(&(bao.list), test_head);
    
    
    list_for_each_entry_safe(pos, next, test_head, list) {
        printf("name = %s, age = %d\n\n", pos->name, pos->age);
    }

    list_del(&bao.list);

    list_for_each_entry_safe(pos, next, test_head, list) {
        printf("name = %s, age = %d\n\n", pos->name, pos->age);
    }

    return 0;
}